#include "datascript/ast_builder.hpp"
#include "datascript/parser/parser.hpp"
#include "datascript/scanner/lexer.hpp"

DATASCRIPT_SCANNER_NS_BEGIN

static void build_ast (lexer& ds_lexer, parser& ds_parser)
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
}
// ----------------------------------------------------------------
syntax_tree* build_ast (FILE* fp)
{
	lexer ds_scanner (fp);
	ast* state = ast_create ();
	parser ds_parser (state);
	//ds_parser.enable_debug (stderr, "--yy-- ");
	build_ast (ds_scanner, ds_parser);
	syntax_tree* result = (syntax_tree*)ast_content (state);
	ast_free (state);
	return result;
}
// ----------------------------------------------------------------
syntax_tree* build_ast (const char* text)
{
	lexer ds_scanner (text);
	ast* state = ast_create ();
	parser ds_parser (state);
	ds_parser.enable_debug (stderr, "--yy-- ");
	build_ast (ds_scanner, ds_parser);
	syntax_tree* result = (syntax_tree*)ast_content (state);
	ast_free (state);
	return result;
}

DATASCRIPT_SCANNER_NS_END