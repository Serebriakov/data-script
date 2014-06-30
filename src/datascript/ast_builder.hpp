#ifndef __DATASCRIPT_AST_BUILDER_HPP__
#define __DATASCRIPT_AST_BUILDER_HPP__

#include <stdio.h>
#include "datascript/datascript_api.h"
#include "datascript/parser/ast.h"

DATASCRIPT_SCANNER_NS_BEGIN

DATASCRIPT_API ast* build_ast (FILE* fp);
DATASCRIPT_API ast* build_ast (const char* text);

DATASCRIPT_SCANNER_NS_END

#endif
