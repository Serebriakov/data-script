#ifndef __DATASCRIPT_PARSER_IO_HPP__
#define __DATASCRIPT_PARSER_IO_HPP__

#include "parser/scanner_iface.h"

input_buffer_t* open_file (const char* path, size_t buffer_size);
input_buffer_t* open_string (const char* string);


#endif
