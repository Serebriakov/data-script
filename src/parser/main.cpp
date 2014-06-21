#include <string>
#include <iostream>
#include "datascript/scanner/lexer.hpp"

static const char* txt = "0xDEADBEEF\n"
  "076\n"
  "123\n"
  "01011b"
  "\"zopa \n popa\"\n"
  "int8 int16 int32 int64\n"
  "uint8 uint16 uint32 uint64\n"
  "MySequence\n"
  "{\n"
    "bit:4    a;\n"
    "uint8    b;\n"
    "bit:4    c;\n"
  "};";



int main (int argc, char* argv [])
{
  std::cout << txt << std::endl;
  
  DATASCRIPT_SCANNER_NS lexer ds_scanner (txt);
  while (true)
    {
	  const char* s = 0;
	  const char* e = 0;
	  
	  DATASCRIPT_SCANNER_NS token_t tok = ds_scanner.scan (s, e);
	  std::string lex (s, e);
      std::cout << tok << " --- " << lex << std::endl;

	  if (tok >= DATASCRIPT_SCANNER_NS eEND_OF_FILE)
	{
	  break;
	}
    }
  
  return 0;
}
