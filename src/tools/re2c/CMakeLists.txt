INCLUDE (CheckIncludeFiles)
INCLUDE (CheckFunctionExists) 
INCLUDE (CheckTypeSize) 
INCLUDE (CheckSymbolExists) 
INCLUDE (CheckCSourceCompiles)

CHECK_INCLUDE_FILES (inttypes.h HAVE_INTTYPES_H)
CHECK_INCLUDE_FILES (memory.h HAVE_MEMORY_H)
CHECK_INCLUDE_FILES (stdbool.h HAVE_STDBOOL_H)
CHECK_INCLUDE_FILES (stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES (strings.h HAVE_STRINGS_H)
CHECK_INCLUDE_FILES (string.h HAVE_STRING_H)
CHECK_INCLUDE_FILES ("sys/param.h" HAVE_SYS_PARAM_H)
CHECK_INCLUDE_FILES ("sys/stat.h" HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES ("sys/types.h" HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES (unistd.h HAVE_UNISTD_H)
CHECK_INCLUDE_FILES ("stddef.h; stdlib.h" HAVE_STDC_HEADERS)
CHECK_FUNCTION_EXISTS (getpagesize HAVE_GETPAGESIZE)
CHECK_FUNCTION_EXISTS (memset HAVE_MEMSET)
CHECK_FUNCTION_EXISTS (mmap HAVE_MMAP)
CHECK_FUNCTION_EXISTS (munmap HAVE_MUNMAP)
CHECK_FUNCTION_EXISTS (strdup HAVE_STRDUP)
CHECK_FUNCTION_EXISTS (strndup HAVE_STRNDUP)

CHECK_TYPE_SIZE (char SIZEOF_CHAR)
CHECK_TYPE_SIZE (int SIZEOF_INT)
CHECK_TYPE_SIZE (long SIZEOF_LONG)
CHECK_TYPE_SIZE (short SIZEOF_SHORT)

check_c_source_compiles("
# include <stddef.h>
int main() {
size_t x = 0;
return 0;
}
" HAVE_SIZE_T_IN_TYPE)

check_c_source_compiles("
int main() {
volatile int x = 0;
return x;
}
" HAVE_VOLATILE)

check_c_source_compiles("
int
main ()
{
/* FIXME: Include the comments suggested by Paul. */
#ifndef __cplusplus
  /* Ultrix mips cc rejects this.  */
  typedef int charset[2];
  const charset cs;
  /* SunOS 4.1.1 cc rejects this.  */
  char const *const *pcpcc;
  char **ppc;
  /* NEC SVR4.0.2 mips cc rejects this.  */
  struct point {int x, y;};
  static struct point const zero = {0,0};
  /* AIX XL C 1.02.0.0 rejects this.
     It does not let you subtract one const X* pointer from another in
     an arm of an if-expression whose if-part is not a constant
     expression */
  const char *g = \"string\";
  pcpcc = &g + (g ? g-g : 0);
  /* HPUX 7.0 cc rejects these. */
  ++pcpcc;
  ppc = (char**) pcpcc;
  pcpcc = (char const *const *) ppc;
  { /* SCO 3.2v4 cc rejects this.  */
    char *t;
    char const *s = 0 ? (char *) 0 : (char const *) 0;

    *t++ = 0;
    if (s) return 0;
  }
  { /* Someone thinks the Sun supposedly-ANSI compiler will reject this.  */
    int x[] = {25, 17};
    const int *foo = &x[0];
    ++foo;
  }
  { /* Sun SC1.0 ANSI compiler rejects this -- but not the above. */
    typedef const int *iptr;
    iptr p = 0;
    ++p;
  }
  { /* AIX XL C 1.02.0.0 rejects this saying
       \"k.c\", line 2.27: 1506-025 (S) Operand must be a modifiable lvalue. */
    struct s { int j; const int *ap[3]; };
    struct s *b; b->j = 5;
  }
  { /* ULTRIX-32 V3.1 (Rev 9) vcc rejects this */
    const int foo = 10;
    if (!foo) return 0;
  }
  return !cs[0] && !zero.x;
#endif

  ;
  return 0;
}" HAVE_CONST)



macro(CHECK_C_INLINE RESULT)
 
   if(NOT DEFINED HAVE_INLINE)
 
   # initialize to empty
   set(${RESULT} "")
 
   # test candidates to find one that works
   foreach(INLINE "inline" "__inline__" "__inline")
     if(NOT HAVE_INLINE)
       string(TOUPPER "HAVE_${INLINE}_KEYWORD" HAVE_INLINE_KEYWORD)
  
        set(PRE_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
        set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -Dinline=${INLINE}")
  
        check_c_source_compiles("typedef int foo_t;
                                 static inline foo_t
                                 static_foo() {
                                   return 0;
                                 }
                                 foo_t
                                 foo() {
                                   return 0;
                                 }
                                 int
                                 main(int argc, char *argv[]) {
                                   return 0;
                                 }" ${HAVE_INLINE_KEYWORD})
  
        set(CMAKE_REQUIRED_FLAGS "${PRE_CMAKE_REQUIRED_FLAGS}")
  
        if(${HAVE_INLINE_KEYWORD})
          set(HAVE_INLINE "${INLINE}" CACHE INTERNAL "C compiler provides inlining support")
        endif(${HAVE_INLINE_KEYWORD})
      endif(NOT HAVE_INLINE)
    endforeach(INLINE)
    endif(NOT DEFINED HAVE_INLINE)
  
    if(NOT DEFINED HAVE_INLINE)
     set(HAVE_INLINE "" CACHE INTERNAL "C compiler does not provide inlining support")
   endif(NOT DEFINED HAVE_INLINE)
 
   # return the final verdict
   set(${RESULT} ${HAVE_INLINE})
 
endmacro(CHECK_C_INLINE)

CHECK_C_INLINE(INLINE_KEYWORD)


CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set (src 
  code.cc
  dfa.cc
  main.cc
  parser.cc
  actions.cc
  substr.cc
  translate.cc
  scanner.cc
  mbo_getopt.cc
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions (-DHAVE_CONFIG_H)

add_executable (re2c-bin ${src})