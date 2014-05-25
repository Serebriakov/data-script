#include <iostream>

#include "parser/token.hpp"

const char* token_to_string (token_t token)
{
  switch (token)
    {
    case eNUMBER:
      return "NUMBER";
    case eSIMPLE_TYPE:
      return "SIMPLE_TYPE";
    };
}


std::ostream& operator << (std::ostream& os, token_t token)
{
  os << token_to_string (token);
  return os;
}

