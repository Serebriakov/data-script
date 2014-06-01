#ifndef __DATASCRIPT_PARSER_SCANNER_HPP__
#define __DATASCRIPT_PARSER_SCANNER_HPP__

#include "datascript/datascript_api.h"
#include "datascript/scanner/scanner_iface.h"

DATASCRIPT_SCANNER_NS_BEGIN

class DATASCRIPT_API lexer
{
public:
  lexer (input_buffer_t* input);
  token_t scan ();
private:
  input_buffer_t* m_input;
  lexeme_t m_lex;
};

DATASCRIPT_SCANNER_NS_END
#endif
