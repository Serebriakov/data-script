#ifndef __DATASCRIPT_PARSER_IO_HPP__
#define __DATASCRIPT_PARSER_IO_HPP__

#include "datascript/datascript_api.h"
#include "datascript/scanner/scanner_iface.h"

DATASCRIPT_SCANNER_NS_BEGIN

DATASCRIPT_API input_buffer_t* DATASCRIPT_CALLSPEC open_file (const char* path, size_t buffer_size);
DATASCRIPT_API input_buffer_t* DATASCRIPT_CALLSPEC open_string (const char* string);

DATASCRIPT_SCANNER_NS_END

#endif
