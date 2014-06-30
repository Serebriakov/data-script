#include <stdlib.h>
#include <sstream>
#include <stdexcept>

#include "datascript/parser/parser.hpp"
#include "datascript/parser/parserfwd.h"

#include "dsparser.h"

DATASCRIPT_SCANNER_NS_BEGIN

parser::parser ()
{
	m_lemon_parser = datascript_parserAlloc (malloc);
}
// --------------------------------------------------------------------
parser::~parser ()
{
	datascript_parserFree (m_lemon_parser, free);
}
// --------------------------------------------------------------------
void parser::operator () (token_t token, _parser_token* pt)
{

	int lemon_token = -1;

	switch (token)
	{
	case ePACKAGE:
		lemon_token = DS_PACKAGE;
		break;
	case eID:
		lemon_token = DS_ID;
		break;
	case eSEMICOLON:
		lemon_token = DS_SEMICOLON;
		break;
	case eDOT:
		lemon_token = DS_DOT;
		break;
	case eEND_OF_FILE:
		lemon_token = DS_END_OF_FILE;
		break;
		
	default:
	{
		std::ostringstream os;
		os << "UNMAPPED TOKEN: " << token;
		throw std::runtime_error (os.str ());
	}
	};

	datascript_parser (m_lemon_parser, lemon_token, pt, 0);

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

DATASCRIPT_SCANNER_NS_END

