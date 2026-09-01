/* udcLocal.c - Minimal local-file-only replacement for udc.c, net.c, https.c.
 *
 * The real udc.c pulls in net.c -> https.c -> OpenSSL, which is not available
 * on offline HPC systems without development packages.  faToTwoBit,
 * twoBitToFa and twoBitInfo only access remote files through UDC when the
 * file name contains a protocol (http://, https://, ftp:// ...).  On a
 * compute cluster without network access that code path is useless, so this
 * stub implements the UDC interface as plain stdio wrappers on local files
 * and aborts if a remote URL is requested.
 *
 * It also provides hasProtocol() (normally in net.c) needed by twoBit.c.
 *
 * Compile this INSTEAD of lib/udc.c - never together with it.
 */

/* Copyright (C) 2013 The Regents of the University of California
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "udc.h"
#include "dystring.h"
#include "errAbort.h"
#include <sys/types.h>

struct udcFile
/* Handle to an open file.  The real struct is private to udc.c. */
    {
    FILE *f;			/* Open stdio file. */
    char *url;			/* File name for error messages. */
    };

static char *defaultDir = NULL;

boolean hasProtocol(char *urlOrPath)
/* Return TRUE if it looks like it has http://, ftp:// etc. */
{
return stringIn("://", urlOrPath) != NULL;
}

char *udcDefaultDir()
/* Get default directory for cache */
{
if (defaultDir == NULL)
    defaultDir = "~/udcCache";
return defaultDir;
}

void udcSetDefaultDir(char *path)
/* Set default directory for cache. */
{
defaultDir = cloneString(path);
}

static struct udcFile *localOpen(char *url)
/* Open a local file, aborting on remote URLs. */
{
if (hasProtocol(url))
    errAbort("This build of %s has no network support, can not open remote file %s",
             "twoBit utilities", url);
struct udcFile *file;
AllocVar(file);
file->f = mustOpen(url, "rb");
file->url = cloneString(url);
return file;
}

struct udcFile *udcFileMayOpen(char *url, char *cacheDir)
/* Open up a file.  Return NULL if file doesn't exist. */
{
if (hasProtocol(url) || !fileExists(url))
    return NULL;
return localOpen(url);
}

struct udcFile *udcFileOpen(char *url, char *cacheDir)
/* Open up a file. Abort if file doesn't exist. */
{
return localOpen(url);
}

void udcFileClose(struct udcFile **pFile)
/* Close down file. */
{
struct udcFile *file = *pFile;
if (file != NULL)
    {
    carefulClose(&file->f);
    freeMem(file->url);
    freeMem(file);
    }
*pFile = NULL;
}

int udcGetChar(struct udcFile *file)
/* Get next character from file or die trying. */
{
int c = getc(file->f);
if (c == -1)
    errAbort("couldn't read char from %s", file->url);
return c;
}

char *udcReadLine(struct udcFile *file)
/* Read a line of any size.  Returns NULL at EOF.  Do not free. */
{
static struct dyString *dy = NULL;
int c;
if (dy == NULL)
    dy = dyStringNew(256);
else
    dyStringClear(dy);
while ((c = getc(file->f)) != -1)
    {
    if (c == '\n')
	break;
    dyStringAppendC(dy, c);
    }
if (c == -1 && dy->stringSize == 0)
    return NULL;
return dy->string;
}

boolean udcIsLocal(char *url)
/* Return TRUE if url is a local file rather than a remote URL. */
{
return !hasProtocol(url);
}

bits64 udcRead(struct udcFile *file, void *buf, bits64 size)
/* Read a block from file.  Return amount actually read. */
{
return fread(buf, 1, size, file->f);
}

void udcMustRead(struct udcFile *file, void *buf, bits64 size)
/* Read a block from file.  Abort if any problem, including EOF before size is read. */
{
bits64 sizeRead = udcRead(file, buf, size);
if (sizeRead < size)
    errAbort("couldn't read %llu bytes from %s, did read %llu",
	     (unsigned long long)size, file->url, (unsigned long long)sizeRead);
}

bits64 udcReadBits64(struct udcFile *file, boolean isSwapped)
/* Read and optionally byte-swap 64 bit entity. */
{
bits64 val;
udcMustRead(file, &val, sizeof(val));
if (isSwapped)
    val = byteSwap64(val);
return val;
}

bits32 udcReadBits32(struct udcFile *file, boolean isSwapped)
/* Read and optionally byte-swap 32 bit entity. */
{
bits32 val;
udcMustRead(file, &val, sizeof(val));
if (isSwapped)
    val = byteSwap32(val);
return val;
}

bits16 udcReadBits16(struct udcFile *file, boolean isSwapped)
/* Read and optionally byte-swap 16 bit entity. */
{
bits16 val;
udcMustRead(file, &val, sizeof(val));
if (isSwapped)
    val = byteSwap16(val);
return val;
}

boolean udcFastReadString(struct udcFile *f, char buf[256])
/* Read a string into buffer, which must be long enough
 * to hold it.  String is in 'writeString' format. */
{
UBYTE bLen;
int len;
if (udcRead(f, &bLen, 1) == 0)
    return FALSE;
len = bLen;
if (len > 0)
    udcMustRead(f, buf, len);
buf[len] = 0;
return TRUE;
}

void udcSeek(struct udcFile *file, bits64 offset)
/* Seek to a particular position in file. */
{
if (fseeko(file->f, (off_t)offset, SEEK_SET) < 0)
    errAbort("udcSeek failed on %s", file->url);
}

void udcSeekCur(struct udcFile *file, bits64 offset)
/* Seek to a particular position in file, relative to current position. */
{
if (fseeko(file->f, (off_t)offset, SEEK_CUR) < 0)
    errAbort("udcSeekCur failed on %s", file->url);
}

bits64 udcTell(struct udcFile *file)
/* Return current file position. */
{
return (bits64)ftello(file->f);
}
