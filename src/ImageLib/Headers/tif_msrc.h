//! Custom data source for libtiff. Assumes all data is in memory at
//! start.

extern TIFF*
TIFFOpenMem (unsigned char * pData, int FileSize);


typedef struct
{
  unsigned char * pData;
  int    FileSize;
  int    CurPos;
} MemSrcTIFFInfo;
