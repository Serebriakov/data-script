#ifndef __DATASCRIPT_AST_BUILDER_HPP__
#define __DATASCRIPT_AST_BUILDER_HPP__

#include <stdio.h>
#include "datascript/datascript_api.h"
#include "datascript/syntax_tree.hpp"

namespace datascript
{

	DATASCRIPT_API grammar::syntax_tree* build_ast (FILE* fp);
	DATASCRIPT_API grammar::syntax_tree* build_ast (const char* text);

} // ns datascript

#endif
