#include <string>

#include "datascript/scanner/lexer.hpp"
#include "datascript/scanner/libscanner/libscanner.h"
#include "datascript/scanner/libscanner/reader.h"

DATASCRIPT_EXTERN_C scanstate* datascript_scanner_attach (scanstate *ss);

DATASCRIPT_SCANNER_NS_BEGIN

lexer::lexer (FILE* f)
{
	ss = dynscan_create (DEFAULT_BUFFER_LENGTH, 1);
	readfp_attach (ss, f);
	datascript_scanner_attach (ss);
}
// -----------------------------------------------------------------------------
lexer::lexer (const char* string)
{
	ss = dynscan_create (0, 0);
	const std::size_t len = strlen (string);
	readmem_attach (ss, string, len+1);
	datascript_scanner_attach (ss);
}
// -----------------------------------------------------------------------------
lexer::~lexer ()
{
	dynscan_free (ss);
}
// -----------------------------------------------------------------------------
token_t lexer::scan (char_ptr_t& begin, char_ptr_t& end)
{
	const int token = scan_next_token (ss);
	if (token < 0)
	{
		begin = end = 0;
		return eIO_ERROR;
	}
	if (token > eEND_OF_FILE)
	{
		begin = end = 0;
	}
	else
	{
		begin = scan_token_start (ss);
		end = scan_token_end (ss);
	}
	return (token_t)token;
}

DATASCRIPT_SCANNER_NS_END
