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
create_new_project( char *p_root );

void
create_initial_folder_structure( char *p_root );

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
  create_initial_folder_structure( p_root );
}

void
create_initial_folder_structure( char *p_root )
{
  if( p_root )
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
