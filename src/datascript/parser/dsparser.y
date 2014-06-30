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

input ::= program END_OF_FILE.
program ::= package_definition.
program ::= qname.


/* -------------------------------------------------------- */
%type qname { qname* }
%destructor qname { qname_free ($$); }

qname (RESULT) ::= ID (A). {RESULT = qname_create (A);}
qname (RESULT) ::= ID (A) DOT qname (B). {RESULT = qname_append (A, B);}

/* -------------------------------------------------------- */

package_definition ::= PACKAGE qname(A) SEMICOLON. {ast_define_package (ast, A);} 



