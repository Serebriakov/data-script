#include <vector>
#include <stdio.h>
#include <string.h>
#include "datascript/scanner/io.hpp"

struct file_buffer_struct 
{
  std::vector <char> buffer;
  FILE *handle;
};
// ---------------------------------------------------------------------
static char* DATASCRIPT_CALLSPEC file_buffer (void* buff)
{
  return &((file_buffer_struct*)buff)->buffer [0];
}
// ---------------------------------------------------------------------
static const char* DATASCRIPT_CALLSPEC file_end (void* buff)
{
  file_buffer_struct* fb = (file_buffer_struct*)buff;
  return &fb->buffer [0] + fb->buffer.size ();
}
// ---------------------------------------------------------------------
static size_t DATASCRIPT_CALLSPEC file_size (void* buff)
{
  return ((file_buffer_struct*)buff)->buffer.size ();
}
// ---------------------------------------------------------------------
static size_t DATASCRIPT_CALLSPEC file_read (void *ptr, size_t size, size_t nmemb, void* buff)
{
  file_buffer_struct* fb = (file_buffer_struct*)buff;
  return fread (ptr, size, nmemb, fb->handle);
}
// ---------------------------------------------------------------------
static void DATASCRIPT_CALLSPEC file_resize (size_t newsize, void* buff)
{
  file_buffer_struct* fb = (file_buffer_struct*)buff;
  fb->buffer.resize (newsize);
}
// ---------------------------------------------------------------------
static int DATASCRIPT_CALLSPEC file_eof (void* buff)
{
  file_buffer_struct* fb = (file_buffer_struct*)buff;
  return feof (fb->handle);
}
// ---------------------------------------------------------------------
static void DATASCRIPT_CALLSPEC file_destructor (struct input_buffer_s* fb)
{
  file_buffer_struct* ufb = (file_buffer_struct*)fb->user;
  fclose (ufb->handle);
  delete ufb;
  delete fb;
}
// ---------------------------------------------------------------------
DATASCRIPT_SCANNER_NS_BEGIN

input_buffer_t* DATASCRIPT_CALLSPEC open_file (const char* path, size_t buffer_size)
{
  FILE* handle = fopen (path, "rb");
  if (handle) 
    {
      file_buffer_struct* fb = new file_buffer_struct;
      fb->buffer.resize (buffer_size);
      size_t read = fread(&fb->buffer [0], 1, buffer_size, handle);
      if (read != buffer_size)
	{
	  fclose (handle);
	  delete fb;
	  return 0;
	}
      if (feof (handle)) {
	
	/*
	 * will need to put the null character at the end, that way the lexer
	 * can check for the null character as the end-of-file
	 */
	fb->buffer[read] = 0;
      }
      fb->handle = handle;

      input_buffer_t* ret = new input_buffer_t;
      
      ret->buffer     = file_buffer;
      ret->end        = file_end;
      ret->size       = file_size;
      ret->read       = file_read;
      ret->resize     = file_resize;
      ret->eof        = file_eof;
      ret->destructor = file_destructor;
      ret->user       = fb;
      return ret;
    }
  return 0;
}

DATASCRIPT_SCANNER_NS_END
// -----------------------------------------------------------------------
struct string_buffer_struct 
{
  std::vector <char> buffer;
};

static char* DATASCRIPT_CALLSPEC string_buffer (void* buff)
{
  return &((string_buffer_struct*)buff)->buffer [0];
}
// ---------------------------------------------------------------------
static const char* DATASCRIPT_CALLSPEC string_end (void* buff)
{
  string_buffer_struct* fb = (string_buffer_struct*)buff;
  return &fb->buffer [0] + fb->buffer.size ();
}
// ---------------------------------------------------------------------
static size_t DATASCRIPT_CALLSPEC string_size (void* buff)
{
  return ((string_buffer_struct*)buff)->buffer.size ();
}
// ---------------------------------------------------------------------
static void DATASCRIPT_CALLSPEC string_destructor (struct input_buffer_s* fb)
{
  string_buffer_struct* ufb = (string_buffer_struct*)fb->user;
  delete ufb;
  delete fb;
}
// ---------------------------------------------------------------------
DATASCRIPT_SCANNER_NS_BEGIN

input_buffer_t* DATASCRIPT_CALLSPEC open_string (const char* string)
{
  size_t n = strlen (string);
  string_buffer_struct* fb = new string_buffer_struct;
  fb->buffer.resize (n+1);
  memcpy (&fb->buffer [0], string, n);
  fb->buffer [n] = 0;


  input_buffer_t* ret = new input_buffer_t;
  memset (ret, 0, sizeof (input_buffer_t));

  ret->buffer     = string_buffer;
  ret->end        = string_end;
  ret->size       = string_size;
  ret->resize     = 0;
  ret->eof        = 0;
  ret->destructor = string_destructor;
  ret->user       = fb;
  return ret;
}

DATASCRIPT_SCANNER_NS_END
