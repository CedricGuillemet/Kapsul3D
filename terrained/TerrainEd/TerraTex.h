// TerraTex.h: interface for the CTerraTex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERRATEX_H__5D387115_0088_46F4_A0B7_8DAFE1DB2588__INCLUDED_)
#define AFX_TERRATEX_H__5D387115_0088_46F4_A0B7_8DAFE1DB2588__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "TerraLight.h"

typedef struct
{
    CImage *img;
    int iStart,iEnd;
    int iSizeX,iSizeY;
    BYTE *lpBits;
    float SlopMin;
    float SlopMax;
} MAPSINFO;


class CTerraTex : public CImage  
{
public:
	void GenerateMap(MAPSINFO *lpMaps,CTerra *pTerrain,CTerraLight *pLight);
    int GetImg(MAPSINFO *lpMaps,BYTE bHeight,float slope);
	CTerraTex();
	virtual ~CTerraTex();

};

#endif // !defined(AFX_TERRATEX_H__5D387115_0088_46F4_A0B7_8DAFE1DB2588__INCLUDED_)
