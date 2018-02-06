/////////////////////////////////////////////////////
// Fonctions de travail sur fichier direct et non sur mémoire
/////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tiffiop.h"

static tsize_t
_tiffReadProcFile(thandle_t fd, tdata_t buf, tsize_t size)
{
	DWORD dwSizeRead;
	if (!ReadFile(fd, buf, size, &dwSizeRead, NULL))
		return(0);
	return ((tsize_t) dwSizeRead);
}

static tsize_t
_tiffWriteProcFile(thandle_t fd, tdata_t buf, tsize_t size)
{
	DWORD dwSizeWritten;
	if (!WriteFile(fd, buf, size, &dwSizeWritten, NULL))
		return(0);
	return ((tsize_t) dwSizeWritten);
}

static toff_t
_tiffSeekProcFile(thandle_t fd, toff_t off, int whence)
{
	DWORD dwMoveMethod;
	switch(whence)
	{
	case 0:
		dwMoveMethod = FILE_BEGIN;
		break;
	case 1:
		dwMoveMethod = FILE_CURRENT;
		break;
	case 2:
		dwMoveMethod = FILE_END;
		break;
	default:
		dwMoveMethod = FILE_BEGIN;
		break;
	}
	return ((toff_t)SetFilePointer(fd, off, NULL, dwMoveMethod));
}

static int
_tiffCloseProcFile(thandle_t fd)
{
	return (CloseHandle(fd) ? 0 : -1);
}

static toff_t
_tiffSizeProcFile(thandle_t fd)
{
	return ((toff_t)GetFileSize(fd, NULL));
}

static int
_tiffDummyMapProcFile(thandle_t fd, tdata_t* pbase, toff_t* psize)
{
	return (0);
}

/*
 * From "Hermann Josef Hill" <lhill@rhein-zeitung.de>:
 *
 * Windows uses both a handle and a pointer for file mapping,
 * but according to the SDK documentation and Richter's book
 * "Advanced Windows Programming" it is safe to free the handle
 * after obtaining the file mapping pointer
 *
 * This removes a nasty OS dependency and cures a problem
 * with Visual C++ 5.0
 */
static int
_tiffMapProcFile(thandle_t fd, tdata_t* pbase, toff_t* psize)
{
	toff_t size;
	HANDLE hMapFile;

	if ((size = _tiffSizeProcFile(fd)) == (toff_t)-1)
		return (0);
	hMapFile = CreateFileMapping(fd, NULL, PAGE_READONLY, 0, size, NULL);
	if (hMapFile == NULL)
		return (0);
	*pbase = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
	CloseHandle(hMapFile);
	if (*pbase == NULL)
		return (0);
	*psize = size;
	return(1);
}

static void
_tiffDummyUnmapProcFile(thandle_t fd, tdata_t base, toff_t size)
{
}

static void
_tiffUnmapProcFile(thandle_t fd, tdata_t base, toff_t size)
{
	UnmapViewOfFile(base);
}

TIFF*
TIFFFdOpen(int ifd, const char* name, const char* mode)
{
	TIFF* tif;
	BOOL fSuppressMap = (mode[1] == 'u' || mode[2] == 'u');

	tif = TIFFClientOpen(name, mode,
		 (thandle_t)ifd,
	    _tiffReadProcFile, _tiffWriteProcFile,
	    _tiffSeekProcFile, _tiffCloseProcFile, _tiffSizeProcFile,
		 fSuppressMap ? _tiffDummyMapProcFile : _tiffMapProcFile,
		 fSuppressMap ? _tiffDummyUnmapProcFile : _tiffUnmapProcFile);
	if (tif)
		tif->tif_fd = ifd;
	return (tif);
}

