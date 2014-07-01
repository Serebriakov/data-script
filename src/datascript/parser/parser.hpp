#ifndef __DATASCRIPT_PARSER_H__
#define __DATASCRIPT_PARSER_H__

#include "datascript/datascript_api.h"
#include "datascript/scanner/lexeme.hpp"
#include "datascript/parser/parser_procs.h"

struct _parser_token;

namespace datascript
{
	namespace analyzer
	{

		class DATASCRIPT_API parser
		{
		public:
			parser (ast* state);
			~parser ();

			void operator () (scanner::token_t token, _parser_token* pt);
			void finish ();
			void enable_debug (FILE* fp, const char* prefix);
		private:
			parser (const parser&);
			parser& operator = (const parser&);
		private:
			void* m_lemon_parser;
			ast* m_state;
		};

	} // ns analyzer
} // ns datascript

#endif
