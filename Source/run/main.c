#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main( int argc, char* argv[ argc + 1 ] )
{
  if( argc > 1 )
  {
    if( strcmp( argv[ 1 ], "new" ) == 0 )
    {
      if( argc == 3 )
      {
        fprintf( stdout, "Creating new project: %s\n", argv[ 2 ] );
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

  return EXIT_SUCCESS;
}
