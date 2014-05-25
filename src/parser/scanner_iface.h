#ifndef __DATASCRIPT_PARSER_SCANNER_IFACE_HPP__
#define __DATASCRIPT_PARSER_SCANNER_IFACE_HPP__

#include "parser/tokens.h"

#include <stddef.h>

#if defined(__cplusplus)
#define __EXTERN_C__ extern "C"
#else
#define __EXTERN_C__
#endif

typedef struct lexeme_s
{
  char* start;
  char* current;
  char* ptr;
  int   line_no;
} lexeme_t;

/**
 * input callbacks
 */
struct input_buffer_s;

typedef char* (*buffer_fn_t) (void* buff);
typedef const char* (*end_fn_t) (void* buff);
typedef size_t      (*buffer_size_fn_t) (void* buff);
typedef size_t      (*buffer_read_fn_t) (void *ptr, size_t size, size_t nmemb, void* buff); 
typedef void        (*buffer_resize_fn_t) (size_t newsize, void* buff);
typedef int         (*eof_fn_t)(void* buff);
typedef void        (*destructor_fn_t)(struct input_buffer_s*);

struct input_buffer_s 
{
  buffer_fn_t      buffer;
  end_fn_t         end;
  buffer_size_fn_t size;
  buffer_read_fn_t read;
  buffer_resize_fn_t resize;
  eof_fn_t           eof;
  destructor_fn_t    destructor;
  void* user;
  
};
typedef struct input_buffer_s input_buffer_t;


__EXTERN_C__ void fill_buffer (input_buffer_t* input, lexeme_t* lexeme); 


__EXTERN_C__ void bind_lexeme (input_buffer_t* input, lexeme_t* lexeme); 
__EXTERN_C__ void close_lexeme (lexeme_t* lexeme); 
__EXTERN_C__ void close_buffer (input_buffer_t* input);

__EXTERN_C__ token_t next_token (input_buffer_t* input, lexeme_t* lexeme); 



#endif
