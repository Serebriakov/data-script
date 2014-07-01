#include <stdlib.h>
#include <sstream>
#include <stdexcept>

#include "datascript/parser/parser.hpp"
#include "datascript/parser/parserfwd.h"

#include "dsparser.h"


namespace datascript
{
	namespace analyzer
	{
		parser::parser (ast* state)
			: m_state (state)
		{
			m_lemon_parser = datascript_parserAlloc (malloc);
		}
		// --------------------------------------------------------------------
		parser::~parser ()
		{
			datascript_parserFree (m_lemon_parser, free);
		}
		// --------------------------------------------------------------------
		void parser::operator () (scanner::token_t token, _parser_token* pt)
		{

			int lemon_token = -1;

			switch (token)
			{
			case scanner::ePACKAGE:
				lemon_token = DS_PACKAGE;
				break;
			case scanner::eID:
				lemon_token = DS_ID;
				break;
			case scanner::eSEMICOLON:
				lemon_token = DS_SEMICOLON;
				break;
			case scanner::eDOT:
				lemon_token = DS_DOT;
				break;
			case scanner::eEND_OF_FILE:
				lemon_token = DS_END_OF_FILE;
				break;
			case scanner::eIMPORT:
				lemon_token = DS_IMPORT;
				break;
			default:
			{
				std::ostringstream os;
				os << "UNMAPPED TOKEN: " << token;
				throw std::runtime_error (os.str ());
			}
			};

			datascript_parser (m_lemon_parser, lemon_token, pt, m_state);

		}
		// --------------------------------------------------------------------
		void parser::finish ()
		{
			datascript_parser (m_lemon_parser, 0, 0, 0);
		}
		// --------------------------------------------------------------------
		void parser::enable_debug (FILE* fp, const char* prefix)
		{
			datascript_parserTrace (fp, prefix);
		}

	} // ns analyzer
} // ns datascript


