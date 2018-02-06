// TerraTex.cpp: implementation of the CTerraTex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <headers.h>
#include "Terra.h"
#include "TerraTex.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern "C" CTexture deftex;
CTerraTex::CTerraTex()
{
    /*
    iGridY=1024;
    iGridX=1024;
    */
}

CTerraTex::~CTerraTex()
{

}

int CTerraTex::GetImg(MAPSINFO *lpMaps,BYTE bHeight,float slope)
{
    int i;

    for (i=0;i<8;i++)
    {
        if ((bHeight>lpMaps[i].iStart)&&(bHeight<=lpMaps[i].iEnd)&&(slope>=lpMaps[i].SlopMin)&&(slope<=lpMaps[i].SlopMax))
            return i;
    }

    return NULL;
}

void CTerraTex::GenerateMap(MAPSINFO *lpMaps,CTerra *pTerrain,CTerraLight *pLight)
{
    int x,y,sc;
    BYTE *imgBits;
    int bMod;

    LPBITMAPINFOHEADER BiMap=(LPBITMAPINFOHEADER)GlobalLock(pTerrain->m_hDib);
    LPBITMAPINFOHEADER BiTex=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
    LPBITMAPINFOHEADER BiLight=(LPBITMAPINFOHEADER)GlobalLock(pLight->m_hDib);


    BYTE *lpBitsLight = ((BYTE*)BiLight)+sizeof(BITMAPINFOHEADER);


    BYTE *lpBitsMaps = ((BYTE*)BiMap)+sizeof(BITMAPINFOHEADER);
    BYTE *lpBitsMaps2=lpBitsMaps;

    BYTE *lpBitsTex = ((BYTE*)BiTex)+sizeof(BITMAPINFOHEADER);

    
    for (y=0;y<pTerrain->iGridY;y++)
    {
        for (x=0;x<pTerrain->iGridX;x++)
        {

			float heights[4];
            int xav,xap,yav,yap;
            xav=( ((x-1)>0)?(x-1):(x) );
            yav=( ((y-1)>0)?(y-1):(y) );
            xap=( ((x+1)<pTerrain->iGridX)?(x+1):(x) );
            yap=( ((y+1)<pTerrain->iGridY)?(y+1):(y) );

            float normalZ ;

            if ( (x>0)&&(x<(pTerrain->iGridX-1))&&(y>0)&&(y<(pTerrain->iGridY-1)) )
            {
            int tmp;
            /*
            BYTE *tmpb;

            tmpb=lpBitsMaps;
            tmpb+=3;
            */
            tmp=(xap*3)+(y*pTerrain->iGridX*3);
			heights[0] = lpBitsMaps2[tmp];//GetPixel(&imgHeightmap, (x+1)/SIZE_FAC, (y)/SIZE_FAC);
            tmp=(xav*3)+(y*pTerrain->iGridX*3);
            heights[1] = lpBitsMaps2[tmp];//GetPixel(&imgHeightmap, (x-1)/SIZE_FAC, (y)/SIZE_FAC);
			tmp=(x*3)+(yap*pTerrain->iGridX*3);
            heights[2] = lpBitsMaps2[tmp];//GetPixel(&imgHeightmap, (x)/SIZE_FAC, (y+1)/SIZE_FAC);
			tmp=(x*3)+(yav*pTerrain->iGridX*3);
            heights[3] = lpBitsMaps2[tmp];//GetPixel(&imgHeightmap, (x)/SIZE_FAC, (y-1)/SIZE_FAC);

			float slopeX = 160.f * (heights[0] - heights[1]) / (2.f*1000.f/(256.f));
			float slopeY = 160.f * (heights[2] - heights[3]) / (2.f*1000.f/(256.f));
			float slopeZ = 1.f;

			normalZ = 1.f/(float)sqrt(slopeX * slopeX + slopeY*slopeY + slopeZ*slopeZ);

            }
            else
                normalZ =0;




            sc=GetImg(lpMaps,(*lpBitsMaps),normalZ);
            imgBits=lpMaps[sc].lpBits;

            imgBits+=((y%lpMaps[sc].iSizeY)*(lpMaps[sc].iSizeX*3)+((x%lpMaps[sc].iSizeX)*3));

            bMod=(*imgBits++)*(*lpBitsLight);
            (*lpBitsTex++)=(bMod>>8);

            bMod=(*imgBits++)*(*lpBitsLight);
            (*lpBitsTex++)=(bMod>>8);

            bMod=(*imgBits++)*(*lpBitsLight);
            (*lpBitsTex++)=(bMod>>8);

/*
            (*lpBitsTex++)=(*imgBits++);
            (*lpBitsTex++)=(*imgBits++);
*/
            lpBitsLight+=3;
            lpBitsMaps+=3;

        }

    }

    GlobalUnlock(BiLight);
    GlobalUnlock(BiMap);
    GlobalUnlock(BiTex);

	//deftex.UnLoad();
	deftex.Type=TEXTURE_IMAGE;
	deftex.daImg=this;
	deftex.Load();
}
