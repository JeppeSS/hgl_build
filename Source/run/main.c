#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <sys/types.h>


bool
is_directory( const char *directory );

void
new_project( const char *p_root );

int
main( int argc, char* argv[ argc + 1 ] )
{
  if( argc > 1 )
  {
    if( strcmp( argv[ 1 ], "new" ) == 0 )
    {
      if( argc == 3 )
      {
        new_project( argv[ 2 ] ); 
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
new_project( const char *p_root )
{
  if( p_root )
  {
    if( !is_directory( p_root ) )
    {
      if( mkdir( p_root ) == 0 )
      {
        fprintf( stdout, "Creating new project: %s...\n", p_root );

        const size_t root_length = strlen( p_root );
        const size_t path_length = root_length + strlen( "/Source" );
        const size_t total_length = root_length + path_length;

        char *p_path = strncpy( malloc( sizeof( char[ total_length ] ) ),
                                p_root, total_length - 1 );
            
        p_path = strncat( p_path, "/Source", path_length );
        p_path[ total_length - 1 ] = '\0';
            
        if( mkdir( p_path ) == 0 )
        {
        }
        else
        {
          fprintf( stdout, "Could not create directory.\n" );
        }                     
      }
      else
      {
        fprintf( stdout, "Could not create directory.\n" );
      }
    }
    else
    {
      fprintf( stdout, "Folder already exists.\n" );
    }
  }
  else
  {
    fprintf( stdout, "Folder already exists.\n" );
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
