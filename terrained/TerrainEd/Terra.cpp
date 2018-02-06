// Terra.cpp: implementation of the CTerra class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <headers.h>
#include "Terra.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAXP 1048576
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTerra::CTerra()
{
    iGridX=1024;
    iGridY=1024;
    WaterLevel=64;
}

CTerra::~CTerra()
{

}
void CTerra::SetPix2(int x,int y,int val,BYTE *lpBits)
{
    
    if (val>WaterLevel)
    {
    
        lpBits[((x==0?0:x-1)*3)+((y==0?0:y-1)*iGridX*3)]=val;
        lpBits[((x==0?0:x-1)*3)+((y==0?0:y-1)*iGridX*3+1)]=val;
        lpBits[((x==0?0:x-1)*3)+((y==0?0:y-1)*iGridX*3+2)]=val;
       
    }
    else
    {
        
        float temp=((255.0f/(float)WaterLevel)*(float)val);
        char tmp2=temp;
        tmp2&=255;


        lpBits[((x==0?0:x-1)*3)+((y==0?0:y-1)*iGridX*3)]=tmp2;//(temp);//temp;
        lpBits[((x==0?0:x-1)*3)+(((y==0?0:y-1)*iGridX*3)+1)]=0;//(val)/2;
        lpBits[((x==0?0:x-1)*3)+(((y==0?0:y-1)*iGridX*3)+2)]=val;//(val)/2;
    }
    

}


#define GETPIX(x,y) lpBits[(((x==0?0:x-1)*3)+((y==0?0:y-1)*iGridX*3))+2]

unsigned char CTerra::GetPix(int x,int y,BYTE *lpBits)
{
    return GETPIX(x,y);
}
float Modere(float iHalfVal)
{

    return (rand()*(iHalfVal/2)/RAND_MAX)-(iHalfVal/4);

}

void CTerra::FractalHalf(int iHalfValX,int iHalfValY,BYTE *lpBits)
{
    int x,y;

    if (iHalfValX==1) return;

    for (y=0;y<iGridY;y+=iHalfValY)
    {
        for (x=0;x<iGridX;x+=iHalfValX)
        {
/*
            SetPix2((x+(iHalfValX/2)),y,((GETPIX(x,y)+GETPIX((x+iHalfValX-1),y))/2));

            SetPix2(x,(y+(iHalfValY/2)),( GETPIX(x,y) + GETPIX(x,(y+(iHalfValY-1)))) /2);
            SetPix2((x+(iHalfValX/2)),(y+(iHalfValY/2)),(GETPIX(x,y)+GETPIX((x+iHalfValX-1),y)+GETPIX((x+iHalfValX-1),(y+iHalfValY-1))+GETPIX(x,(y+iHalfValY-1)))/4);
            SetPix2((x+(iHalfValX-1)),(y+(iHalfValY/2)),((GETPIX(x,y)+GETPIX(x,(y+(iHalfValY-1))))/2));

            SetPix2((x+(iHalfValX/2)),(y+(iHalfValY-1)),((GETPIX(x,(y+(iHalfValY-1)))+GETPIX((x+iHalfValX-1),(y+(iHalfValY-1))))/2));
*/

            SetPix2((x+(iHalfValX/2)),y,( (GETPIX(x,y)+GETPIX((x+iHalfValX),y)) /2+Modere(iHalfValX) ) ,lpBits);

            SetPix2(x,(y+(iHalfValY/2)),( (GETPIX(x,y) + GETPIX(x,(y+iHalfValY)))/2+Modere(iHalfValX)),lpBits);
            SetPix2((x+(iHalfValX/2)),(y+(iHalfValY/2)),(((GETPIX(x,y)+GETPIX((x+iHalfValX),y)+GETPIX((x+iHalfValX),(y+iHalfValY))+GETPIX(x,(y+iHalfValY)))/4+Modere(iHalfValX))),lpBits);
            SetPix2( (x+iHalfValX) , (y+(iHalfValY/2)) ,( (GETPIX(x,y)+GETPIX(x,(y+iHalfValY)))/2+Modere(iHalfValX)),lpBits);

            SetPix2((x+(iHalfValX/2)),(y+(iHalfValY)),( (GETPIX(x,(y+iHalfValY))+GETPIX((x+iHalfValX),(y+iHalfValY)))/2+Modere(iHalfValX)),lpBits);


        }
    }

    FractalHalf(iHalfValX/2,iHalfValY/2,lpBits);
}

void CTerra::GenerateFractal()
{
    LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);			


    BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);

    SetPix2(0,0,(rand()&255),lpBits);

    SetPix2((iGridX),0,(rand()&255),lpBits);

    SetPix2(0,(iGridY),(rand()&255),lpBits);

    SetPix2((iGridX),(iGridY),(rand()&255),lpBits);

    FractalHalf(iGridX,iGridY,lpBits);

    GlobalUnlock(BiDest);

}

void CTerra::ReEvaluateWater(BYTE bThres)
{
    int x,y;

    WaterLevel=bThres;

    LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);			


    BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);

    BYTE val;

    for (y=0;y<iGridY;y++)
    {
        for (x=0;x<iGridX;x++)
        {
            val=(*(lpBits+2));

            if (val>WaterLevel)
            {
                *lpBits++=val;
                *lpBits++=val;
                *lpBits++=val;
            }
            else
            {
                *lpBits++=((255.0f/(float)WaterLevel)*(float)val);
                *lpBits++=0;
                *lpBits++=val;
            }
        }
    }

    GlobalUnlock(BiDest);
}

double CTerra::FindHeightAt(double X,double Y)
{

    double difx,dify;

    if ( (X<0)||(X>1024)||(Y<0)||(Y>1024) )
        return 0;

    LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);			


    BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);

    
    difx=fmod(X,1);
    dify=fmod(Y,1);

    int dx,dy;

    dx=X;
    dy=Y;

    unsigned char h1=lpBits[dx*3+(dy*1024*3)];
    unsigned char h2=lpBits[(dx+1)*3+(dy*1024*3)];
    unsigned char h3=lpBits[dx*3+((dy+1)*1024*3)];


    double h1b=(double)(h1)+((double)h2-(double)(h1))*difx;
    double h2b=(double)(h1)+((double)h3-(double)(h1))*dify;

    double val=((h1b+h2b)/2.0f);


    GlobalUnlock(BiDest);
    return val;

}