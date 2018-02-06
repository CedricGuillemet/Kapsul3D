/* $Header: C:/cvs/Repository/Kapsul3D/src/ImageLib/Sources/Sources\040Tiff/tif_msrc.c,v 1.1 2002/03/29 05:06:26 khurley Exp $ */

/*
 * Copyright (c) 1988-1996 Sam Leffler
 * Copyright (c) 1991-1996 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

// Adapted to TIFFs in memory regions by U.v.Zadow

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tiffiop.h"
#include "tif_msrc.h"

static tsize_t
_tiffReadProc(thandle_t fd, tdata_t buf, tsize_t size)
{
	MemSrcTIFFInfo * pInfo = (MemSrcTIFFInfo *) fd;

  // Make sure we don't run over the end of the file.
  if (size+pInfo->CurPos > pInfo->FileSize)
    size = pInfo->FileSize-pInfo->CurPos;

  memcpy ((void *)buf, (void *)(pInfo->pData+pInfo->CurPos), size);
  pInfo->CurPos += size;

	return (tsize_t) size;
}

static tsize_t
_tiffWriteProc(thandle_t fd, tdata_t buf, tsize_t size)
{
  TIFFError ("TIFFOpen", "Function disabled.");
	return 0;
}

static toff_t
_tiffSeekProc(thandle_t fd, toff_t off, int whence)
{
  MemSrcTIFFInfo * pInfo = (MemSrcTIFFInfo *) fd;

	switch(whence)
	  {
	    case 1:
		    pInfo->CurPos += off;
		    break;
	    case 2:
        pInfo->CurPos = pInfo->FileSize-off;
		    break;
	    case 0:
	    default:
        pInfo->CurPos = off;
		    break;
	  }
	return pInfo->CurPos;
}

static int
_tiffCloseProc(thandle_t fd)
{
  MemSrcTIFFInfo * pInfo = (MemSrcTIFFInfo *) fd;
  free (pInfo);

	return 0;
}

static toff_t
_tiffSizeProc(thandle_t fd)
{
  MemSrcTIFFInfo * pInfo = (MemSrcTIFFInfo *) fd;
	return ((toff_t)(pInfo->FileSize));
}

static int
_tiffDummyMapProc(thandle_t fd, tdata_t* pbase, toff_t* psize)
{
	return(0);
}

static void
_tiffDummyUnmapProc(thandle_t fd, tdata_t base, toff_t size)
{
	return;
}

TIFF*
TIFFOpenMem (unsigned char * pData, int FileSize)
{
	TIFF* tif;
  MemSrcTIFFInfo * pInfo;

  pInfo = (MemSrcTIFFInfo *) malloc (sizeof (MemSrcTIFFInfo));
  pInfo->pData = pData;
  pInfo->CurPos = 0;
  pInfo->FileSize = FileSize;

	tif = TIFFClientOpen ("MemSource", "r", (thandle_t)pInfo,
	                     _tiffReadProc, _tiffWriteProc,
	                     _tiffSeekProc, _tiffCloseProc, _tiffSizeProc,
		                   _tiffDummyMapProc, _tiffDummyUnmapProc);
	if (tif)
		tif->tif_fd = (int)pInfo;
	return (tif);
}

tdata_t
_TIFFmalloc(tsize_t s)
{
	return ((tdata_t)malloc (s));
}

void
_TIFFfree(tdata_t p)
{
	free (p);
	return;
}

tdata_t
_TIFFrealloc(tdata_t p, tsize_t s)
{
  return realloc (p, s);
}

void
_TIFFmemset(void* p, int v, tsize_t c)
{
	memset(p, v, c);
}

void
_TIFFmemcpy(void* d, const tdata_t s, tsize_t c)
{
	memcpy (d, s, c);
}

int
_TIFFmemcmp(const tdata_t p1, const tdata_t p2, tsize_t c)
{
  return memcmp (p1, p2, c);
}

TIFFErrorHandler _TIFFerrorHandler = NULL;
TIFFErrorHandler _TIFFwarningHandler = NULL;

