#ifndef __DATASCRIPT_PARSER_SCANNER_HPP__
#define __DATASCRIPT_PARSER_SCANNER_HPP__

#include "parser/scanner_iface.h"


class scanner 
{
public:
  scanner (input_buffer_t* input);
  token_t scan ();
private:
  input_buffer_t* m_input;
  lexeme_t m_lex;
};


#endif
