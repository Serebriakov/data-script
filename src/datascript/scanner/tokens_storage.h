#ifndef __DATASCRIPT_SCANNER_TOKENS_STORAGE_H__
#define __DATASCRIPT_SCANNER_TOKENS_STORAGE_H__

#include "datascript/compiler.h"

struct _tokens_storage;
struct _parser_token;

DATASCRIPT_EXTERN_C struct _tokens_storage* create_tokens_storage ();
DATASCRIPT_EXTERN_C void free_tokens_storage (struct _tokens_storage* ts);
DATASCRIPT_EXTERN_C struct _parser_token* create_parser_token (struct _tokens_storage* ts, int token_id, const char* start, const char* end);
DATASCRIPT_EXTERN_C void free_parser_token (struct _parser_token* victim);
DATASCRIPT_EXTERN_C void persist_tokens (struct _tokens_storage* ts);
DATASCRIPT_EXTERN_C int get_token_data (const struct _parser_token* tok, const char** begin, const char** end);


#endif
