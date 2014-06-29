#include <iostream>
#include <string>

#include "datascript/parser/ast.h"

void ast_define_package (struct _ast* ast, const parser_token* tok)
{
  std::string s (tok->begin, tok->end);

  std::cout << "PACKAGE " << s << std::endl;
}
