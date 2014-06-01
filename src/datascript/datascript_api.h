#ifndef __DATASCRIPT_API_H__
#define __DATASCRIPT_API_H__

#include "datascript/compiler.h"


#if defined(DATASCRIPT_AS_STATIC_LIB)
#   define DATASCRIPT_API
#else
#   if defined(DATASCRIPT_CREATE_SHARED_LIBRARY) || defined(DATASCRIPT64_CREATE_SHARED_LIBRARY)
#      define DATASCRIPT_API DATASCRIPT_PROPER_EXPORT
#   else
#      define DATASCRIPT_API DATASCRIPT_PROPER_IMPORT
#   endif
#endif

#if defined(__cplusplus)
#define DATASCRIPT_SCANNER_NS_BEGIN namespace datascript { namespace scanner {
#define DATASCRIPT_SCANNER_NS_END } }
#else
#define DATASCRIPT_SCANNER_NS_BEGIN 
#define DATASCRIPT_SCANNER_NS_END 
#endif

#endif
