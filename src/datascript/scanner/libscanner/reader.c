#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "datascript/scanner/libscanner/reader.h"




/** Rearrange the scan buffer. Only called by readprocs.
 *
 * This moves all in-flight data to the bottom of the buffer
 * to free up more room.
 *
 * Your readproc should read as much as it can between ss->limit
 * and ss->buf+ss->bufsiz. It should adjust ss->limit to point
 * to the new end of data (the end of the buffer if it was able to
 * execute a complete read).
 *
 * Returns the number of bytes available to read in the buffer.
 */

/* cnt tells how many bytes need to be shifted downward.
   The bytes that need to be shifted are those between the token
   and the limit. */

static ssize_t read_shiftbuf(scanstate *ss)
{
  const char *min;
  ssize_t cnt;

  min = ss->token;
  if(ss->marker && ss->marker < min) {
    min = ss->marker;
  }

  /* this tells how many bytes need to be shifted. */
  cnt = ss->limit - min;
  if(cnt) {
    ssize_t delta = min - ss->bufptr;
    memmove((void*)ss->bufptr, min, (size_t)cnt);
    ss->cursor -= delta;
    ss->token -= delta;
    if(ss->marker) ss->marker -= delta;
    ss->limit -= delta;

    assert(ss->limit >= ss->bufptr);
    assert(ss->cursor >= ss->bufptr);
    assert(ss->cursor <= ss->limit);
  } else {
    /* nothing to shift so we reset the buffer to maximum size. */
    ss->cursor = ss->bufptr;
    ss->token = ss->bufptr;
    if(ss->marker) ss->marker = ss->bufptr;
    ss->limit = ss->bufptr;
  }

  return ((long)ss->bufsiz - ((long)ss->limit - (long)ss->bufptr));
}




static ssize_t readfp_read(scanstate *ss)
{
  ssize_t avail;
  size_t n;

  avail = read_shiftbuf(ss);
  n = fread((void*)ss->limit, 1, (size_t)avail, ss->readref);
  ss->limit += n;

  if(n == 0) {
    if(feof(ss->readref)) {
      return 0;
    }
    if(ferror(ss->readref)) {
      return -1;
    }
       
    /* this implies some sort of internal consistency error */
    assert(!"Not eof or error. I have no idea what happened!");
    return -3;
  }

  return (ssize_t)n;
}


scanstate* readfp_attach(scanstate *ss, FILE *fp)
{
  if(!ss || !fp) {
    return 0;
  }

  ss->readref = fp;
  ss->read = readfp_read;
  return ss;
}


/** Creates a scanstate object that can read from the given file.
 * Returns NULL and prints to STDERR if an error ocurrs.
 * Ensure that you call readfp_close() when you're finished.
 * Uses the given buffer size, or BUFSIZ if bufsiz is 0.
 * Ensure that the buffer size will fit into a signed
 * int on the current machine architecture.
 *
 * This call is the approximate equivalent to:
 * - dynscan_create(bufsiz);
 * - readfp_attach(ss, fopen(path));
 */

/**
 * The internal function that performs the read. You never call
 * it directly. Instead, it is called automatically by the scanner
 * whenever it needs more data.
 */

static ssize_t readfd_read(scanstate *ss)
{
  ssize_t n;
  ssize_t avail;

  avail = read_shiftbuf(ss);

  /* ensure we get a full read */
  do {
    n = read((int)(intptr_t)ss->readref, (void*)ss->limit, (size_t)avail);
  } while(n < 0 && errno == EINTR);
  ss->limit += n;

  return n;
}


/** Attaches the existing fd to the existing scanstate object.
 * Note that this routine checks the fd and if it's less than 0
 * (indicating an error) it returns null.
 *
 * If you pass this routine valid arguments, there's no way for it to fail.
 *
 * Note that the re2c library does not work very well with file descriptors
 * that may return short reads such as pipes and sockets. You may want to
 * try to use the new re2c push model to fix this.
 */

scanstate* readfd_attach(scanstate *ss, int fd)
{
  intptr_t pfd = fd;

  if(!ss || fd < 0) {
    return 0;
  }
  
  ss->readref = (void*)pfd;
  ss->read = readfd_read;
  return ss;
}


/* Opens the file and creates a new scanner to scan it.
 * This is just a convenience routine. You can create a scanner
 * yourself and attach to it using readfd_attach().
 *
 * If you do use this routine, you should call readfd_close() to close
 * the file and deallocate the scanner.
 *
 * Bufsiz tells how big in bytes the scan buffer will be. No single
 * token may be larger than bufsiz.
 *
 * This is the approximate equivalent to:
 * - dynscan_create(bufsiz);
 * - readfd_attach(ss, open(path));
 */

scanstate* readfd_open(const char *path, size_t bufsiz)
{
  scanstate *ss;
  int fd;

  fd = open(path, O_RDONLY);
  if(fd < 0) {
    return NULL;
  }

  ss = dynscan_create(bufsiz);
  if(!ss) {
    close(fd);
    return NULL;
  }

  return readfd_attach(ss, fd);
}


/**
 * Closes the file and deallocates the memory allocated by readfd_open().
 */

void readfd_close(scanstate *ss)
{
  close((int)(intptr_t)ss->readref);
  dynscan_free(ss);
}


scanstate* readfp_open(const char *path, size_t bufsiz)
{
  scanstate *ss;
  FILE *fp;

  /* open the file */
  fp = fopen(path, "r");
  if(!fp) {
    return NULL;
  }

  /* create the dynamic scanstate */
  ss = dynscan_create(bufsiz);
  if(!ss) {
    fclose(fp);
    return NULL;
  }

  return readfp_attach(ss, fp);
}


/** Releases the resources allocated by readfp_open()
 */

void readfp_close(scanstate *ss)
{
  fclose(ss->readref);
  dynscan_free(ss);
}




/** Returns EOF because we're out of data.
 */

static ssize_t readmem_read(scanstate *ss)
{
  DATASCRIPT_UNUSED (ss);
  return 0;
}


/** Initializes the given scanstate to read from the given string.
 */

scanstate* readmem_init(scanstate *ss, const char *data, size_t len)
{
  scanstate_init(ss, data, len);
  ss->limit = ss->bufptr + ss->bufsiz;
  ss->read = readmem_read;
  return ss;
}


/** Attaches the scanner to the given string. Use this
 * if you've already malloc'd a scanstate. It calls scanstate_init
 * so it will blow everything already in the scanstate away.
 *
 * TODO: this is unlike all other attach routines, none of whom
 * blow away the scanstate. CHANGE THIS.
 */

scanstate* readmem_attach(scanstate *ss, const char *data, size_t len)
{
  /* ensure we don't stomp on a pre-existing buffer */
  if(ss->bufsiz) {
    return NULL;
  }

  return readmem_init(ss, data, len);
}

