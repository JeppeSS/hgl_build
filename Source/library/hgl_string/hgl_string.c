#include <stdlib.h>
#include <string.h>

#include "hgl_string.h"



char *
hgl_string_new( const char *p_init_string )
{
  if( p_init_string )
  {
    // +1 for null-termination symbol.
    const size_t length = strlen( p_init_string ) + 1;
    char *p_hgl_string = strncpy( malloc( sizeof( char[ length ] ) ),
                                  p_init_string, length - 1 );

    if( p_hgl_string )
    {
      p_hgl_string[ length ] = '\0';
      return p_hgl_string;
    }

  }

  return 0;
}

size_t
hgl_string_length( char *p_hgl_string )
{
  if( p_hgl_string )
  {
    return strlen( p_hgl_string );
  }

  return 0;
}

char *
hgl_string_concat( char *p_string_head, char *p_string_tail )
{
  if( p_string_head && p_string_tail )
  {
    const size_t head_length  = hgl_string_length( p_string_head );
    const size_t tail_length  = hgl_string_length( p_string_tail );
    const size_t total_length = head_length + tail_length;
    char *p_new_string = strncpy( malloc( sizeof( char[ total_length ] ) ),
                                  p_string_head, total_length - 1 );

    if( p_new_string )
    {
      p_new_string = strncat( p_new_string, p_string_tail, tail_length );
      p_new_string[ total_length ] = '\0';
      return p_new_string;
    }
  }

  return 0;
}



void
hgl_string_destroy( char *p_hgl_string )
{
  if( p_hgl_string )
  {
    free( p_hgl_string );
  }
}
