#include <stdio.h>
#include <string>
#include <iostream>
#include "datascript/ast_builder.hpp"

int main (int argc, char* argv [])
{
  if (argc != 2)
    {
      std::cout << "USAGE: " << argv [0] << " <infile>" << std::endl;
      return 0;
    }
  
  
  const char* fname = argv [1];
  FILE* f = fopen (fname, "rb");

  datascript::grammar::syntax_tree* abstract_syntax_tree = datascript::build_ast (f);
  delete abstract_syntax_tree;
  fclose (f);
  return 0;
}
