#include <stdlib.h>
#include <sstream>
#include <stdexcept>

#include "datascript/parser/parser.h"

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
void parser::operator () (token_t token, const char* begin, const char* end)
{
  parser_token* tok = new parser_token;
  tok->begin = begin;
  tok->end = end;

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
    default:
      {
	std::ostringstream os;
	os << "UNMAPPED TOKEN: " << token;
	throw std::runtime_error (os.str ());
      }
    };

  datascript_parser (m_lemon_parser, lemon_token, tok, 0);

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

