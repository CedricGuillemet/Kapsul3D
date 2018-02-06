// Terra.h: interface for the CTerra class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERRA_H__63A0C5D0_1618_479D_97AA_2940ED442ADA__INCLUDED_)
#define AFX_TERRA_H__63A0C5D0_1618_479D_97AA_2940ED442ADA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <headers.h>

class CTerra : public CImage  
{
public:
	void ReEvaluateWater(BYTE bThres);
	void GenerateFractal();
	CTerra();
	virtual ~CTerra();
    int iGridX,iGridY;
    void FractalHalf(int iHalfValX,int iHalfValY,BYTE *lpBits);
    void SetPix2(int x,int y,int val,BYTE *lpBits);
    int WaterLevel;
    unsigned char *PrecalcX;
    unsigned char *PrecalcY;
    double FindHeightAt(double X,double Y);
    unsigned char GetPix(int x,int y,BYTE *lpBits);
    int StartX,StartY;
};

#endif // !defined(AFX_TERRA_H__63A0C5D0_1618_479D_97AA_2940ED442ADA__INCLUDED_)
