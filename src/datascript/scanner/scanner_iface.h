#ifndef __DATASCRIPT_PARSER_SCANNER_IFACE_HPP__
#define __DATASCRIPT_PARSER_SCANNER_IFACE_HPP__

#include "datascript/scanner/tokens.h"

#include <stddef.h>

struct lexeme_tag
{
  char* start;
  char* current;
  char* ptr;
  int   line_no;
};

typedef struct lexeme_tag lexeme_t;

/**
 * input callbacks
 */
struct input_buffer_s;

typedef char*       (DATASCRIPT_CALLSPEC *buffer_fn_t) (void* buff);
typedef const char* (DATASCRIPT_CALLSPEC *end_fn_t) (void* buff);
typedef size_t      (DATASCRIPT_CALLSPEC *buffer_size_fn_t) (void* buff);
typedef size_t      (DATASCRIPT_CALLSPEC *buffer_read_fn_t) (void *ptr, size_t size, size_t nmemb, void* buff);
typedef void        (DATASCRIPT_CALLSPEC *buffer_resize_fn_t) (size_t newsize, void* buff);
typedef int         (DATASCRIPT_CALLSPEC *eof_fn_t)(void* buff);
typedef void        (DATASCRIPT_CALLSPEC *destructor_fn_t)(struct input_buffer_s*);

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


DATASCRIPT_EXTERN_C void fill_buffer (input_buffer_t* input, lexeme_t* lexeme); 


DATASCRIPT_EXTERN_C void bind_lexeme (input_buffer_t* input, lexeme_t* lexeme);
DATASCRIPT_EXTERN_C void close_lexeme (lexeme_t* lexeme);
DATASCRIPT_EXTERN_C void close_buffer (input_buffer_t* input);

DATASCRIPT_EXTERN_C token_t next_token (input_buffer_t* input, lexeme_t* lexeme);



#endif
