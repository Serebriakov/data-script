#include <iostream>
#include "parser/scanner.hpp"
#include "parser/io.hpp"

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
  input_buffer_t* input = open_string (txt);
  scanner ds_scanner (input);
  while (true)
    {
      token_t tok = ds_scanner.scan ();

      std::cout << tok << std::endl;

      if (tok >= eEND_OF_FILE)
	{
	  break;
	}
    }
  close_buffer (input);
  return 0;
}
