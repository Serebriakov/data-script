#include "parser/scanner.hpp"

scanner::scanner (input_buffer_t* input)
  : m_input (input)
{
  bind_lexeme (input, &m_lex);
}

token_t scanner::scan ()
{
  return next_token (m_input, &m_lex);
}
