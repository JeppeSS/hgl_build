#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <sys/types.h>

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
create_initial_folder_structure( char *p_root );

void
create_gitignore_file( char *p_root );

void
create_readme_file( char *p_root );

void
create_main_file( char *p_root );

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
