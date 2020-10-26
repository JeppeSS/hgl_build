#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <dirent.h>

#include "../library/hgl_string/hgl_string.h"


bool
is_directory( const char *directory );

void
new_project( char *p_root );

void
write_to_file( const char *p_file_name, char *p_content );

void
create_new_project( char *p_root );

void
build_project( void );

void
create_initial_folder_structure( char *p_root );

void
create_gitignore_file( char *p_root );

void
create_readme_file( char *p_root );

void
create_main_file( char *p_root );




typedef struct
{
  char    **pp_folders;
  uint8_t capacity;
  uint8_t size;

} folder_stack;

folder_stack *
folder_stack_init( folder_stack *p_stack, uint8_t capacity );

void
folder_stack_push( folder_stack *p_stack, char *p_folder );

char *
folder_stack_pop( folder_stack *p_stack );

bool
folder_stack_is_empty( folder_stack *p_stack );

void
folder_stack_destroy( folder_stack *p_stack );

int
main( int argc, char* argv[ argc + 1 ] )
{
  if( argc > 1 )
  {
    if( strcmp( argv[ 1 ], "new" ) == 0 )
    {
      if( argc == 3 )
      {
        create_new_project( argv[ 2 ] ); 
      }
      else
      {
        fprintf( stdout, "Missing argument for project name.\n" );
      }
    }
    else if( strcmp( argv[ 1 ], "build" ) == 0 )
    {
      build_project();
    }
    else
    {
      fprintf( stdout, "Invalid command: %s\n", argv[ 1 ] );
    }
  }
  else
  {
    fprintf( stdout, "Missing command.\n" );
  }

  return EXIT_SUCCESS;
}


void
create_new_project( char *p_root )
{
  if( p_root )
  {
    create_initial_folder_structure( p_root );
    create_gitignore_file( p_root );
    create_readme_file( p_root );
    create_main_file( p_root );
  }
}

void
create_initial_folder_structure( char *p_root )
{
  if( !is_directory( p_root ) )
  {
    char *p_source_path = hgl_string_concat( p_root, "/Source" );
    char *p_run_path    = hgl_string_concat( p_source_path, "/run" );
       
    if( mkdir( p_root )        == 0 &&
        mkdir( p_source_path ) == 0 &&
        mkdir( p_run_path )    == 0 )
    {
      fprintf( stdout, "Folder structure complete.\n" );
    }
    else
    {
      // TODO[Jeppe]: Add cleanup procedure.
      fprintf( stdout, "Something went wrong, could not create folders.\n" );
    }
      
    hgl_string_destroy( p_source_path );
    hgl_string_destroy( p_run_path );
  }
}

void
write_to_file( const char *p_file_name, char *p_content )
{
  FILE *p_file = fopen( p_file_name, "w" );
  if( p_file )
  {
    fprintf( p_file, p_content );
    fclose( p_file );
  }
}

void
create_gitignore_file( char *p_root )
{
  char *p_gitignore_path = hgl_string_concat( p_root, "/.gitignore" );
  write_to_file( p_gitignore_path,
                 "# Executables\n*.exe\n*.out\n\n# Libraries\nlibrary/" ); 
  hgl_string_destroy( p_gitignore_path ); 
}

void
create_readme_file( char *p_root )
{
  char *p_readme_path = hgl_string_concat( p_root, "/README.md" );
  char *p_content = hgl_string_concat("# ", p_root );
  write_to_file( p_readme_path, p_content );
  hgl_string_destroy( p_content );
  hgl_string_destroy( p_readme_path ); 
}

void
create_main_file( char *p_root )
{
  char *p_main_path = hgl_string_concat( p_root, "/Source/run/main.c" );
  write_to_file( p_main_path, "#include <stdio.h>\n#include <stdlib.h>\n\nint\nmain( void )\n{\n  fprintf( stdout, \"Hello, World!\" );\n\n  return EXIT_SUCCESS;\n}" ); 
  hgl_string_destroy( p_main_path ); 
}

bool
is_directory( const char *directory )
{
  if( directory )
  {
    struct stat stats;
    return stat( directory, &stats ) == 0 && S_ISDIR( stats.st_mode );
  }

  return false;
}

void
build_project( void )
{
  folder_stack *p_folder_stack = folder_stack_init( malloc( sizeof( folder_stack ) ),
                                                    20 );

  folder_stack *p_file_stack = folder_stack_init( malloc( sizeof( folder_stack ) ),
                                                  50 );

  folder_stack_push(p_folder_stack, "Source");
  while( !folder_stack_is_empty( p_folder_stack ) )
  {
    char *p_folder = folder_stack_pop( p_folder_stack );
    
    if( is_directory( p_folder ) )
    {
      struct dirent *p_dp;
      DIR *p_dir = opendir( p_folder );
      while( ( p_dp = readdir( p_dir ) ) != NULL )
      {
        char *p_tmp_path = hgl_string_concat( p_folder, "/" );
        char *p_sub_path = hgl_string_concat( p_tmp_path, p_dp->d_name );
        if( strcmp( p_dp->d_name , "." ) != 0 && strcmp( p_dp->d_name, ".." ) != 0 )
        {
          folder_stack_push( p_folder_stack, p_sub_path ); 
        }
        hgl_string_destroy( p_tmp_path );
        hgl_string_destroy( p_sub_path );
      } 
    }
    else
    {
      size_t file_length = hgl_string_length( p_folder );
      if( file_length >= 2 && p_folder[ file_length-1 ] == 'c' )
      {
        folder_stack_push( p_file_stack, p_folder );
      }
    }

    hgl_string_destroy( p_folder );
  }

  char *c_files = hgl_string_new( "");
  while( !folder_stack_is_empty( p_file_stack ) )
  {
    char *file = folder_stack_pop( p_file_stack );
 
    char *combine = hgl_string_concat( file, " " );   
    char *tmp = hgl_string_concat( c_files, combine );
    
    
    hgl_string_destroy( c_files );

    c_files = hgl_string_concat( tmp, "" );

    hgl_string_destroy( file );    
    hgl_string_destroy( tmp );
    hgl_string_destroy( combine );
  }

  char *p_command = hgl_string_concat( "gcc -Wall -Wextra ", c_files );

  system( p_command );

  hgl_string_destroy( p_command );
  

}



folder_stack *
folder_stack_init( folder_stack *p_stack, uint8_t capacity )
{
  if( p_stack )
  {
    *p_stack = ( folder_stack ) {
      .pp_folders = malloc( capacity * sizeof( char * ) ),
      .capacity   = capacity,
      .size       = 0
    };
    
    if( !p_stack->pp_folders )
    {
      p_stack->capacity = 0;
    }
  }

  return p_stack;
}

void
folder_stack_push( folder_stack *p_stack, char *p_folder )
{
  if( p_stack )
  {
    if( p_stack->capacity > p_stack->size )
    {
      p_stack->pp_folders[ p_stack->size ] = hgl_string_new( p_folder );
      p_stack->size = p_stack->size + 1;
    }
  }
}

char *
folder_stack_pop( folder_stack *p_stack )
{
  if( p_stack )
  {
    if( p_stack->size > 0 )
    {
      p_stack->size = p_stack->size - 1;
      return p_stack->pp_folders[ p_stack->size ];
    }
  }
  return 0;
}

bool
folder_stack_is_empty( folder_stack *p_stack )
{
  if( p_stack )
  {
    return p_stack->size == 0;
  }

  return true;
}

void
folder_stack_destroy( folder_stack *p_stack )
{
  if( p_stack )
  {
    for( uint8_t i = 0; i < p_stack->size; i++ )
    {
      hgl_string_destroy( p_stack->pp_folders[ i ] );
    }

    free( p_stack->pp_folders );
    free( p_stack );
  }
}
