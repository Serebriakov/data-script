#include "datascript/ast_builder.hpp"
#include "datascript/parser/parser.hpp"
#include "datascript/scanner/lexer.hpp"

DATASCRIPT_SCANNER_NS_BEGIN

static ast* build_ast (lexer& ds_lexer, parser& ds_parser)
{
	while (true)
	{
		token_t token_type;
		_parser_token* token = ds_lexer.scan (token_type);
		if (token_type > eEND_OF_FILE)
		{
			break;
		}
		if (token_type == eWHITESPACE)
		{
			continue;
		}
		ds_parser (token_type, token);
		if (token_type == eEND_OF_FILE)
		{
			break;
		}
	}
	return 0;
}
// ----------------------------------------------------------------
ast* build_ast (FILE* fp)
{
	lexer ds_scanner (fp);
	parser ds_parser;
	ds_parser.enable_debug (stderr, "--yy-- ");
	return build_ast (ds_scanner, ds_parser);
}
// ----------------------------------------------------------------
ast* build_ast (const char* text)
{
	lexer ds_scanner (text);
	parser ds_parser;
	ds_parser.enable_debug (stderr, "--yy-- ");
	return build_ast (ds_scanner, ds_parser);
}

DATASCRIPT_SCANNER_NS_END