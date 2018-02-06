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

CKMesh *daMesh;
extern "C" CKScene *GScene;
int k,l;

void CTerraLight::GenerateLight(CTerra *pTerrain, double dAngle,BYTE bAmbiantVal,BYTE bSunVal)
{
	double t,u,v;
    int x,y;
    float HeightMax;
    BYTE bPrev;

	if (GScene==NULL) return;
    dAngle*=3,14159265358979323846;
    dAngle/=180;

    LPBITMAPINFOHEADER BiTerrain=(LPBITMAPINFOHEADER)GlobalLock(pTerrain->m_hDib);
    LPBITMAPINFOHEADER BiLight=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);


    BYTE *lpBitsTer = ((BYTE*)BiTerrain)+sizeof(BITMAPINFOHEADER);
    BYTE *lpBitsLig = ((BYTE*)BiLight)+sizeof(BITMAPINFOHEADER);

    
    for (y=0;y<pTerrain->GetHeight();y++)
    {
        


        for (x=0;x<pTerrain->GetWidth();x++)
        {

HeightMax=0;
        bPrev=*lpBitsTer;

		Vertex ro,rd;
		ro.vx=(float)x*4.0f;//1.5f;//*2;///16.0f;
		ro.vy=(float)y*4.0f;//1.5f;//*2;///16.0f;
		float tmpx=(*lpBitsTer);
		ro.vz=tmpx;
		rd.vx=1;
		rd.vy=0;
		rd.vz=sin(dAngle);
		rd.Normalize();

					bool Intersect=false;
					for (daMesh=GScene->FirstMesh;(daMesh!=NULL);daMesh=daMesh->Next)
					{
						for (k=0;(k<daMesh->nb2poly);k++)
						{
							for (l=0;(l<daMesh->pl[k].nb2vert-2);l++)
							{
								/*
								if (&daMesh->pl[k]!=CurrentPolygon)
								{

									if (CurrentPolygon->GetDist(dalight->Source)<0)
										goto finished;
										*/

									
									if (intersect_triangle(ro,rd,daMesh->pv[daMesh->pl[k].nbvert[0]],
										daMesh->pv[daMesh->pl[k].nbvert[l+1]],
										daMesh->pv[daMesh->pl[k].nbvert[l+2]],&t,&u,&v))

									{
										//DMPOutputString(" %5.2f \r\n",t);

										//if (t<0) //(t>-0.99)&&(t<0))
										{
											
											Intersect=true;
											l=(daMesh->pl[k].nb2vert-2);
											k=daMesh->nb2poly;
					(*lpBitsLig++)=100;//bAmbiantVal;
                    (*lpBitsLig++)=100;bAmbiantVal;
                    (*lpBitsLig++)=100;bAmbiantVal;

											goto finished;
										}

									}
									/*
								}
							}
							*/
						}
					}
					}
					

             if (!Intersect)
			 {
				 
				 (*lpBitsLig++)=255;//bAmbiantVal;
                    (*lpBitsLig++)=255;//bAmbiantVal;
                    (*lpBitsLig++)=255;//bAmbiantVal;
					
			 }
			 
			 
						

            //float modulate=fsinit*16;
/*
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
			 }
			 */
			
finished:;
			/*
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
*/
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
