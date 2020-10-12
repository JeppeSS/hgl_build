#ifndef _HGL_STRING_H_
#define _HGL_STRING_H_
/*
 * ============================================================================
 *      @Filename:  hgl_string.h
 *
 *   @Description:
 *       
 *   Functionality to easily and safely manipulate character sequences.
 *
 *      @Version:  0.1
 *      @Created:  09/08/20
 *
 *      @Author:  Jeppe S. Skov, jsskov92@gmail.com
 *
 * ============================================================================
*/

/*
 * === @FUNCTION ==============================================================
 * @Name: hgl_string_new
 *
 * @Description:
 * 
 * Allocates and fills a char pointer with a sequence of characters the
 * pointer will be null-terminated. 
 *
 * @Param: p_init_string - The char sequence.
 *
 * @Return: A pointer to a sequence of characters.
 * ============================================================================
*/
char *
hgl_string_new( const char *p_init_string );

/*
 * === @FUNCTION ==============================================================
 * @Name: hgl_string_length
 *
 * @Description:
 *
 * Length of a character sequence excluding the null-termination symbol.
 *
 * @Param: p_hgl_string - The char sequence.
 *
 * @Return: The length of the character sequence.
 * ============================================================================
*/
size_t
hgl_string_length( char *p_hgl_string );

/*
 * === @FUNCTION ==============================================================
 * @Name: hgl_string_concat
 *
 * @Description:
 *
 * Concatenates two character sequences into a single character sequence,
 * the sequence will be null-terminated.
 *
 * @Param: p_string_head - The beginning of the new sequence.
 * @Param: p_string_tail - The end of the new sequence.
 *
 * @Return: A new character sequence.
 * ============================================================================
*/
char *
hgl_string_concat( char *p_string_head, char *p_string_tail );

/*
 * === @FUNCTION ==============================================================
 * @Name: hgl_string_destroy
 *
 * @Description:
 *
 * Free allocated memory for a given character sequence.
 *
 * @Param: p_hgl_string - The char pointer that should be freed.
 * ============================================================================
*/
void
hgl_string_destroy( char *p_hgl_string );

#endif
