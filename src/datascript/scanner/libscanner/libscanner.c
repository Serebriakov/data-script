#include <assert.h>
#include <stdlib.h>

#include "datascript/scanner/libscanner/libscanner.h"

/** Initializes the scanstate structure.
*
* @param ss The scanstate structure to initialize.
* @param bufptr The buffer that the scanner should use.
* @param bufsiz The size in bytes of the buffer passed in bufptr.
*
* Initializes the given scanstate structure and tells it to use
* the provided buffer.
*
* If you don't need to buffer the data
* (for instance, when using readmem.h), pass NULL for bufptr
* and 0 for bufsiz.
*
* You probably want to attach a reader after calling this routine.
*
* Also see scanstate_reset() and dynscan_create().
*/

void scanstate_init(scanstate *ss, const char *bufptr, size_t bufsiz)
{
    ss->cursor = bufptr;
    ss->limit = bufptr;
    ss->marker = NULL;
    ss->token = bufptr;
    ss->line = 0;
    ss->last_read = 1;
    ss->bufptr = bufptr;
    ss->bufsiz = bufsiz;
    ss->readref = NULL;
    ss->read = NULL;
    ss->scanref = NULL;
    ss->state = NULL;
    ss->userref = NULL;
    ss->userproc = NULL;
}


/** Resets the given scanstate as if it was just created but doesn't
* modify the scanner or the readproc.
*
* Doesn't modify:
* - the reader or the readref.
* - the scanner or the scanref.
* - the userproc or userref.
* - the buffer or buffer size
*
* If you want to reset the reader and scanner, you probably want
* to detach and reattach them.
*/

void scanstate_reset(scanstate *ss)
{
    ss->cursor = ss->bufptr;
    ss->limit = ss->bufptr;
    ss->marker = NULL;
    ss->token = ss->bufptr;
    ss->line = 0;
    ss->last_read = 1;
}


/** Dynamically allocates a new scanstate data structure
*
* Allocates a buffer of the given size for the scanner using malloc.
* Note that the size is an int: the number of bytes in the buffer
* must fit into a signed integer on the current architecture.
* Returns the new scanstate or NULL if there was a memory allocation problem.
*
* Remember to call dynscan_free() when you're done scanning.
*/

scanstate* dynscan_create(size_t bufsiz)
{
    scanstate *ss;
    char *bufptr;
    
    ss = malloc(sizeof(scanstate));
    if(!ss) {
        return NULL;
    }

    if(bufsiz) {
        bufptr = malloc(bufsiz);
        if(!bufptr) {
            free(ss);
            return NULL;
        }
    } else {
        bufptr = 0;
    }

    scanstate_init(ss, bufptr, bufsiz);
    return ss;
}


/** Frees a scanstate allocated by dynscan_create().
*/

void dynscan_free(scanstate *ss)
{
    if(ss->bufptr) {
        free((void*)ss->bufptr);
    }

    free(ss);
}

