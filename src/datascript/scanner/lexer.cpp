#include <string>

#include "datascript/scanner/lexer.hpp"
#include "datascript/scanner/libscanner/libscanner.h"
#include "datascript/scanner/libscanner/reader.h"

DATASCRIPT_EXTERN_C scanstate* datascript_scanner_attach (scanstate *ss);

DATASCRIPT_SCANNER_NS_BEGIN

static void signal_invalidate (void* ctx)
{
	persist_tokens ((_tokens_storage*)ctx);
}

lexer::lexer (FILE* f)
{
	storage = create_tokens_storage ();

	ss = dynscan_create (DEFAULT_BUFFER_LENGTH, 1);
	ss->signal_invalidate_ctx = storage;
	ss->signal_invalidate = signal_invalidate;
	readfp_attach (ss, f);
	datascript_scanner_attach (ss);
}
// -----------------------------------------------------------------------------
lexer::lexer (const char* string)
{
	storage = create_tokens_storage ();
	ss = dynscan_create (0, 0);
	ss->signal_invalidate_ctx = storage;
	ss->signal_invalidate = signal_invalidate;
	const std::size_t len = strlen (string);
	readmem_attach (ss, string, len+1);
	datascript_scanner_attach (ss);
}
// -----------------------------------------------------------------------------
lexer::~lexer ()
{
	dynscan_free (ss);
	free_tokens_storage (storage);
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
// ----------------------------------------------------------------------------
_parser_token* lexer::scan (token_t& token_id)
{
	const char* begin = 0;
	const char* end = 0;
	token_id = scan (begin, end);
	switch (token_id)
	{
	case eHEX_NUMBER:
	case eDECIMAL_NUMBER:
	case eBINARY_NUMBER:
	case eID:
		return create_parser_token (storage, (int)token_id, begin, end);
	default:
		return 0;
	}
}
DATASCRIPT_SCANNER_NS_END
