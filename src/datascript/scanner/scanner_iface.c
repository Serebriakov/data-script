#include <string.h>
#include "datascript/scanner/scanner_iface.h"


void fill_buffer(input_buffer_t *buffer, lexeme_t *lexeme) 
{
  const size_t originalSize = buffer->size (buffer->user);
  const size_t lexemeStartIndex = (size_t)(lexeme->start - buffer->buffer (buffer->user));
  const size_t lexemeCurrentIndex = (size_t)(lexeme->current - buffer->buffer (buffer->user));
  const size_t newSize = originalSize * 2;
  const size_t lexemeLength = (size_t)(lexeme->current - lexeme->start + 1);
  size_t read = 0;
  size_t to_read = 0;
  if (buffer->read == 0)
    {
      return;
    }
  if (lexeme->start > buffer->buffer (buffer->user)) 
    {
      /* scenario 1, make room by overwriting the beginning of buffer. */
      memcpy(buffer->buffer (buffer->user), lexeme->start, lexemeLength);
      lexeme->start = buffer->buffer (buffer->user);
      lexeme->current = buffer->buffer (buffer->user) + lexemeLength;
      to_read = buffer->size (buffer->user) - lexemeLength;
      read = buffer->read(lexeme->current, 1, to_read , buffer->user);
    }
  else 
    {
      
      /*
       * scenario 2: need a new buffer to hold more of the current lexeme.
       * create a new, bigger buffer and copy the contents
       * of the smaller buffer into the one
       */
      buffer->resize (newSize, buffer->user);
      
      /*
       * read the contents of the the file into the second half of the new buffer.
       */
      read = buffer->read(buffer->buffer (buffer->user) + originalSize, 1, originalSize, buffer->user);
      /*
       * now fix all the pointers; they are currently pointing to the buffer that was just
       * freed
       */
      
      lexeme->start = (buffer->buffer (buffer->user)) + lexemeStartIndex;
      lexeme->current = (buffer->buffer (buffer->user) + lexemeCurrentIndex);
    }
    if (buffer->eof(buffer->user)) 
      {
	
        /*
         * will need to put the null character at the end, that way the lexer
         * can check for the null character as the end-of-file
         */
        buffer->buffer (buffer->user)[originalSize + read] = 0;
      }
}
/* ------------------------------------------------------------------ */
void bind_lexeme (input_buffer_t* input, lexeme_t* lexeme)
{
  lexeme->start   = input->buffer (input->user);
  lexeme->current = lexeme->start;
  lexeme->ptr     = lexeme->current;
  lexeme->line_no = 0;
}
/* ------------------------------------------------------------------ */
void close_lexeme (lexeme_t* lexeme)
{
  lexeme->start   = 0;
  lexeme->current = 0;
  lexeme->ptr     = 0;
}
/* ------------------------------------------------------------------ */
void close_buffer (input_buffer_t* input)
{
  input->destructor (input);
}
