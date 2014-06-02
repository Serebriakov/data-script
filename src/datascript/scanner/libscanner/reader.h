#ifndef __DATASCRIPT_SCANNER_LIBSCANNER_READER_H__
#define __DATASCRIPT_SCANNER_LIBSCANNER_READER_H__

#include <string.h>
#include <stdio.h>
#include "datascript/scanner/libscanner/libscanner.h"



/** Sets the scanner to scan the data contained in the given file descriptor.
*
* @param ss The scanner to manipulate.
* @param fd The file descriptor that the scanner should pull data from.
*/

DATASCRIPT_EXTERN_C scanstate* readfd_attach(scanstate *ss, int fd);


/** Creates a scanner to scan the given file.
*
* This routine dynamically allocates the scanstate and its buffer.
* It then opens the given Unix file and attaches it to the scanner.
*
* @param path The Unix path to the file to scan.
* @param bufsiz The size in bytes of the scanner buffer to allocate.
*/

DATASCRIPT_EXTERN_C scanstate* readfd_open(const char *path, size_t bufsiz);

/** Disposes of the scanner created by readfd_open().
*
* This routine closes the file and deallocates the scanner and buffer.
* It frees all resourcs allocated by readfd_open().
*
* @param ss The scanner to destroy.
*/

DATASCRIPT_EXTERN_C void readfd_close(scanstate *ss);


DATASCRIPT_EXTERN_C scanstate* readfp_attach(scanstate *ss, FILE *fp);
DATASCRIPT_EXTERN_C scanstate* readfp_open(const char *filename, size_t bufsiz);
DATASCRIPT_EXTERN_C void readfp_close(scanstate *ss);


DATASCRIPT_EXTERN_C scanstate* readmem_init(scanstate *ss, const char *data, size_t len);
DATASCRIPT_EXTERN_C scanstate* readmem_attach(scanstate *ss, const char *data, size_t len);


/**
* Initializes a readmem from a C string. The string must exist for
* as long as the scanner -- the scanner doesn't make a copy.
*/

#define readmem_init_str(ss,str) readmem_init(ss,str,strlen(str))



#endif
