#include <stdio.h>
#include <string>
#include <iostream>
#include "datascript/scanner/lexer.hpp"
#include "datascript/parser/parser.h"


int main (int argc, char* argv [])
{
  if (argc != 2)
    {
      std::cout << "USAGE: " << argv [0] << " <infile>" << std::endl;
      return 0;
    }
  
  
  const char* fname = argv [1];
  FILE* f = fopen (fname, "rb");

  DATASCRIPT_SCANNER_NS lexer ds_scanner (f);
  DATASCRIPT_SCANNER_NS parser ds_parser;
  ds_parser.enable_debug (stderr, "--yy-- ");

  while (true)
    {
	  const char* s = 0;
	  const char* e = 0;
	  
	  DATASCRIPT_SCANNER_NS token_t tok = ds_scanner.scan (s, e);
	  
	  if (tok == DATASCRIPT_SCANNER_NS eEND_OF_FILE)
	    {
	      ds_parser.finish ();
	      break;
	    }

	  if (tok >= DATASCRIPT_SCANNER_NS eEND_OF_FILE)
	    {
	      break;
	    }
	  if (tok == DATASCRIPT_SCANNER_NS eWHITESPACE)
	    {
	      continue;
	    }
	  // std::string str (s,e);
	  //std::cout <<"[" << tok << " -- " << str << "]" << std::endl;
	  ds_parser (tok, s, e);
    }
  fclose (f);
  return 0;
}
