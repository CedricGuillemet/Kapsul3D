// LightCalc.h: interface for the CLightCalc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHTCALC_H__E736338B_9F4F_450C_8FCE_143ED5B2EC78__INCLUDED_)
#define AFX_LIGHTCALC_H__E736338B_9F4F_450C_8FCE_143ED5B2EC78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vertex.h"
#include "../entity/Entities/light.h"
#include "KPolygon.h"
class  __declspec(dllexport) CLightCalc  
{
public:
	void CalcLightmap(Vertex &Origin,Vertex &scx,Vertex &scy,BYTE *lpBits,int sx,int sy, CLight *dalight);
	inline void ComputeLumelSpot(Vertex &lumel,CLight *dalight,BYTE &R,BYTE &G,BYTE &B);
    inline void ComputeLumelOmni(Vertex &lumel,CLight *dalight,BYTE &R,BYTE &G,BYTE &B);

    inline void AddLight(float factor,BYTE &R,BYTE &G,BYTE &B,CLight *dalight);
    inline double dist_Point_to_Segment( Vertex &P, Vertex &S0,Vertex &S1,int &type,double &d);

	CLightCalc();
	virtual ~CLightCalc();
    //BYTE Buffer[65536];
    //CLight light;

/*
    double v1[3]={0,0,0};
    double v2[3]={10,0,0};
    double v3[3]={0,10,0};
*/
    Vertex ro,rd;
	CKScene *m_Scene;
    double t,u,v;
};

#endif // !defined(AFX_LIGHTCALC_H__E736338B_9F4F_450C_8FCE_143ED5B2EC78__INCLUDED_)
