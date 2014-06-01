#ifndef __DATASCRIPT_COMPILER_H__
#define __DATASCRIPT_COMPILER_H__

# if defined(__BEOS__) || defined(__HAIKU__)
#  if defined(__GNUC__)
#   define DATASCRIPT_PROPER_EXPORT __declspec(dllexport)
#  else
#   define DATASCRIPT_PROPER_EXPORT __declspec(export)
#  endif
# elif defined(__WIN32__) || defined(_WIN32) || defined (WIN32) || defined (WIN64) || defined (_WIN64)
#  ifdef __BORLANDC__
#    define DATASCRIPT_PROPER_EXPORT
#    define DATASCRIPT_PROPER_IMPORT     __declspec(dllimport)
#  else
#   define DATASCRIPT_PROPER_EXPORT      __declspec(dllexport)
#   define DATASCRIPT_PROPER_IMPORT      __declspec(dllimport)
#  endif
# elif defined(__OS2__)
#  ifdef __WATCOMC__
#    define DATASCRIPT_PROPER_EXPORT     __declspec(dllexport)
#    define DATASCRIPT_PROPER_IMPORT
#  elif defined (__GNUC__) && __GNUC__ < 4
#    define DATASCRIPT_PROPER_EXPORT    __declspec(dllexport)
#    define DATASCRIPT_PROPER_IMPORT
#  else
#   define DATASCRIPT_PROPER_EXPORT
#   define DATASCRIPT_PROPER_IMPORT
#  endif
# else
#  if defined(__GNUC__) && __GNUC__ >= 4
#   define DATASCRIPT_PROPER_EXPORT      __attribute__ ((visibility("default")))
#   define DATASCRIPT_PROPER_IMPORT      __attribute__ ((visibility ("default")))
#  else
#   define DATASCRIPT_PROPER_EXPORT
#   define DATASCRIPT_PROPER_IMPORT
#  endif
# endif

# if (defined(__WIN32__) || defined(_WIN32) || defined (WIN32) || defined (WIN64) || defined (_WIN64) )&& !defined(__GNUC__)
#  define DATASCRIPT_CALLSPEC __cdecl
# elif defined(__OS2__)
#  if defined (__GNUC__) && __GNUC__ < 4
#   define DATASCRIPT_CALLSPEC _cdecl
#  else
#   define DATASCRIPT_CALLSPEC _System
#  endif
# else
#  define DATASCRIPT_CALLSPEC
# endif

#ifdef __SYMBIAN32__
#ifndef EKA2
#undef DATASCRIPT_PROPER_IMPORT
#define DATASCRIPT_PROPER_IMPORT
#undef DATASCRIPT_PROPER_EXPORT
#define DATASCRIPT_PROPER_EXPORT
#elif !defined(__WINS__)
#undef DATASCRIPT_PROPER_EXPORT
#define DATASCRIPT_PROPER_EXPORT __declspec(dllexport)
#endif /* !EKA2 */
#endif /* __SYMBIAN32__ */



#if !defined(DATASCRIPT_PROPER_EXPORT)
#error "DATASCRIPT_PROPER_EXPORT is undefined"
#endif

#if !defined(DATASCRIPT_PROPER_IMPORT)
#error "DATASCRIPT_PROPER_EXPORT is undefined"
#endif

#if !defined(DATASCRIPT_CALLSPEC)
#error "DATASCRIPT_CALLSPEC is undefined"
#endif

#if defined(__cplusplus)
#define DATASCRIPT_EXTERN_C extern "C"
#else
#define DATASCRIPT_EXTERN_C
#endif


#endif
