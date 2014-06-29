%token_type { parser_token* }  
   
      
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
#define IN_LEMON
#include "datascript/parser/parser.h"

}  
    
%name datascript_parser
%token_prefix DS_
%extra_argument { struct _ast* ast }
     
%syntax_error {  
   printf( "Syntax error!\n");
}   
	      
program ::= package_definition.

/* -------------------------------------------------------- */

package_definition ::= PACKAGE ID(A) SEMICOLON. {ast_define_package (ast, A);} 

