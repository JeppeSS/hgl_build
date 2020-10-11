#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/stat.h>


bool
isDirectory( const char *directory );

int
main( int argc, char* argv[ argc + 1 ] )
{
  if( argc > 1 )
  {
    if( strcmp( argv[ 1 ], "new" ) == 0 )
    {
      if( argc == 3 )
      {
        if( !isDirectory( argv[ 2 ] ) )
        {
          fprintf( stdout, "Creating new project: %s\n", argv[ 2 ] );
        }
        else
        {
          fprintf( stdout, "Folder already exists.\n" );
        }
        
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

bool
isDirectory( const char *directory )
{
  if( directory )
  {
    struct stat stats;
    if( stat( directory, &stats ) == 0 &&
        S_ISDIR( stats.st_mode ) )
    {
      return true;
    }
  }

  return false;
}
