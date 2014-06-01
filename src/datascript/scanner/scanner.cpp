#include "datascript/scanner/scanner.hpp"

DATASCRIPT_SCANNER_NS_BEGIN

lexer::lexer (input_buffer_t* input)
  : m_input (input)
{
  bind_lexeme (input, &m_lex);
}

token_t lexer::scan ()
{
  return next_token (m_input, &m_lex);
}

DATASCRIPT_SCANNER_NS_END
