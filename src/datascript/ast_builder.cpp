#include "datascript/ast_builder.hpp"
#include "datascript/parser/parser.hpp"
#include "datascript/scanner/lexer.hpp"

namespace datascript
{
	static void build_ast (scanner::lexer& ds_lexer, analyzer::parser& ds_parser)
	{
		while (true)
		{
			scanner::token_t token_type;
			_parser_token* token = ds_lexer.scan (token_type);
			if (token_type > scanner::eEND_OF_FILE)
			{
				break;
			}
			if (token_type == scanner::eWHITESPACE)
			{
				continue;
			}
			ds_parser (token_type, token);
			if (token_type == scanner::eEND_OF_FILE)
			{
				break;
			}
		}
	}
	// ----------------------------------------------------------------
	grammar::syntax_tree* build_ast (FILE* fp)
	{
		scanner::lexer ds_scanner (fp);
		ast* state = ast_create ();
		analyzer::parser ds_parser (state);
		//ds_parser.enable_debug (stderr, "--yy-- ");
		build_ast (ds_scanner, ds_parser);
		grammar::syntax_tree* result = (grammar::syntax_tree*)ast_content (state);
		ast_free (state);
		return result;
	}
	// ----------------------------------------------------------------
	grammar::syntax_tree* build_ast (const char* text)
	{
		scanner::lexer ds_scanner (text);
		ast* state = ast_create ();
		analyzer::parser ds_parser (state);
		ds_parser.enable_debug (stderr, "--yy-- ");
		build_ast (ds_scanner, ds_parser);
		grammar::syntax_tree* result = (grammar::syntax_tree*)ast_content (state);
		ast_free (state);
		return result;
	}
} // ns datascript
