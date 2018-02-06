// TerraLight.cpp: implementation of the CTerraLight class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Math.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>

#include "TerraLight.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTerraLight::CTerraLight()
{

}

CTerraLight::~CTerraLight()
{

}

void CTerraLight::GenerateLight(CTerra *pTerrain, double dAngle,BYTE bAmbiantVal,BYTE bSunVal)
{
    int x,y;
    float HeightMax;
    BYTE bPrev;

    dAngle*=3,14159265358979323846;
    dAngle/=180;

    LPBITMAPINFOHEADER BiTerrain=(LPBITMAPINFOHEADER)GlobalLock(pTerrain->m_hDib);
    LPBITMAPINFOHEADER BiLight=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);


    BYTE *lpBitsTer = ((BYTE*)BiTerrain)+sizeof(BITMAPINFOHEADER);
    BYTE *lpBitsLig = ((BYTE*)BiLight)+sizeof(BITMAPINFOHEADER);

    
    for (y=0;y<pTerrain->iGridY;y++)
    {
        HeightMax=0;
        bPrev=*lpBitsTer;

        

        for (x=0;x<pTerrain->iGridX;x++)
        {
            //float modulate=fsinit*16;

            if (*lpBitsTer>HeightMax)
            {
                if (*lpBitsTer<pTerrain->WaterLevel)
                {
                    (*lpBitsLig++)=(bSunVal);
                    (*lpBitsLig++)=0;
                    (*lpBitsLig++)=0;
                }
                else
                {
                    (*lpBitsLig++)=bSunVal;
                    (*lpBitsLig++)=bSunVal;
                    (*lpBitsLig++)=bSunVal;
                }
                HeightMax=(float)(*lpBitsTer);
            }
            else
            {
                if (*lpBitsTer<pTerrain->WaterLevel)
                {
                    (*lpBitsLig++)=bAmbiantVal;
                    (*lpBitsLig++)=0;
                    (*lpBitsLig++)=0;
                }
                else
                {

                    (*lpBitsLig++)=bAmbiantVal;
                    (*lpBitsLig++)=bAmbiantVal;
                    (*lpBitsLig++)=bAmbiantVal;
                }
                

            }

            bPrev=*lpBitsTer;


            if (HeightMax>0) HeightMax-=sin(dAngle);


            lpBitsTer+=3;
            //lpBitsLig+=3;
        }

    }

    //
    GlobalUnlock(m_hDib);
    GlobalUnlock(pTerrain->m_hDib);
}
