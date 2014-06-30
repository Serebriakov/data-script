%include {   
#include <stdio.h>  
#include <assert.h>

#if defined (__clang__)
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wunused-parameter"

#elif defined(__GNUC__) 
	#if (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 6)
		#pragma GCC diagnostic ignored "-Wmissing-prototypes"
		#pragma GCC diagnostic ignored "-Wunused-parameter"	
	#endif
#endif

#include "datascript/parser/parserfwd.h"
#include "datascript/scanner/tokens_storage.h"
}  
    
%name datascript_parser
%token_prefix DS_
%extra_argument { struct _ast* ast }
     
%syntax_error {  
   printf( "Syntax error!\n");
}   

%token_type { parser_token* }  	      
%token_destructor { free_parser_token($$); }		  

input ::= cmdlist.

cmdlist ::= ecmd cmdlist.
cmdlist ::= ecmd.

ecmd ::= END_OF_FILE.
ecmd ::= package_definition .
ecmd ::= import_stmt .
ecmd ::= declaration .

/* -------------------------------------------------------- */

package_definition ::= PACKAGE qname(A) SEMICOLON. {ast_define_package (ast, A);} 

/* -------------------------------------------------------- */

import_stmt ::= IMPORT qname (A) SEMICOLON. {ast_import (ast, A); }

/* -------------------------------------------------------- */

declaration ::= const_definition .

const_definition ::= CONST primitive_type(A) ID(B) EQUALS value(C) SEMICOLON. {ast_const_definition (ast, A, B, C);}

primitive_type ::= INT8 .
primitive_type ::= INT16 .
primitive_type ::= INT32 .
primitive_type ::= INT64 .
primitive_type ::= UINT8 .
primitive_type ::= UINT16 .
primitive_type ::= UINT32 .
primitive_type ::= UINT64 .

/* -------------------------------------------------------- */

%type value { value* }
%destructor value { value_free ($$); }

value(RESULT) ::= DEC_NUMBER(A) . { RESULT = create_value_numeric (ast, A); }
value(RESULT) ::= HEX_NUMBER(A) . { RESULT = create_value_numeric (ast, A); }
value(RESULT) ::= OCT_NUMBER(A) . { RESULT = create_value_numeric (ast, A); }
value(RESULT) ::= qname(A) .      { RESULT = create_value_qname (ast, A); }

/* -------------------------------------------------------- */

%type qname { qname* }
%destructor qname { qname_free ($$); }

qname (RESULT) ::= ID (A). {RESULT = qname_create (A);}
qname (RESULT) ::= ID (A) DOT qname (B). {RESULT = qname_append (A, B);}
