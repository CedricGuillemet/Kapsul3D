// Polygon.h: interface for the Polygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGON_H__CE588C7F_FA35_4583_AC46_21DA99D9A807__INCLUDED_)
#define AFX_POLYGON_H__CE588C7F_FA35_4583_AC46_21DA99D9A807__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Kapsul3D.h"

class KAPSUL_DESC CKPolygon  
{
public:
    int FirstIndex;
    int nb2vert;

    bool Selected;
	BYTE Smoothing;	//smoothing group


	Vertex Normale;
	double D;
	CKTexture *Maps[4];
	unsigned int Tag;
	bool TweakUV;
	float ScaleU,ScaleV,Rotate,TransU,TransV;
public:

	// -- Constructor ---------------------------------------------------------

	inline CKPolygon()
	{
		FirstIndex=0;
		Selected=false;
		
		//Tex=new int*[4];
	
		nb2vert=0;
		ScaleU=0;
		ScaleV=0;
		Rotate=0;
		TransU=0;
		TransV=0;
		Smoothing=0;
		
	}
	/*
	inline CKPolygon(int v1,int v2,int v3) //volatile. DO NOT use.
	{
		nb2vert=3;
		nbvert=(int*)malloc(sizeof(int)*3);
		nbvert[0]=v1;
		nbvert[1]=v2;
		nbvert[2]=v3;
		Selected=false;
		
		//Tex=new int*[4];
		
		
		Tex[0]=NULL;
		Tex[1]=NULL;
		Tex[2]=NULL;
		Tex[3]=NULL;
		
		nb2vert=0;
		
	}
	*/
	// -- Destructor ----------------------------------------------------------

	inline virtual ~CKPolygon()
	{
		/*
		for (int i=0;i<4;i++)
			if (Tex[i]!=NULL) free(Tex[i]);

		//delete [] Tex;
		free(nbvert);
		*/
	}

	// -- Allocate ------------------------------------------------------------

    inline int Allocate(CKMesh *daObj,int nbv);

	// -- Calc plan -----------------------------------------------------------

	void inline CalcPlan(Vertex *pv,int *pIndices)
	{
		Normale.Cross(pv[pIndices[FirstIndex+1]]-pv[pIndices[FirstIndex]], pv[pIndices[FirstIndex+2]]-pv[pIndices[FirstIndex]]);
		Normale.Normalize();
		D = -pv[pIndices[FirstIndex+2]].Dot(Normale);
	};

	// -- Distance ------------------------------------------------------------

	double inline GetDist(Vertex &vt)
	{
		return Normale.Dot(vt) + D;
	};

	// -- Copy ----------------------------------------------------------------
/*
	void inline IsCopyOf(CKMesh *Obj,CKPolygon *cmpt)
	{
		int i,j;

		Normale=cmpt->Normale;
		Allocate(Obj,1,cmpt->nb2vert);
		nb2vert=cmpt->nb2vert;

		Tag=cmpt->Tag;

		for (i=0;i<cmpt->nb2vert;i++)
		{
			for (j=0;j<4;j++)
				if (Tex[j]!=NULL)
					Tex[j][i]=cmpt->Tex[j][i];
			nbvert[i]=cmpt->nbvert[i];
		}

		D=cmpt->D;

		Selected=false;//cmpt->Selected;
	};
*/
	// flip wise
	void FlipWise(int *pIndices)
	{
		int i,dummy;
		double dif=floor( (double)nb2vert/2.0f );


		for (i=0;i<(int)dif;i++)
		{
			dummy=pIndices[FirstIndex+nb2vert-i-1];
			pIndices[FirstIndex+nb2vert-i-1]=pIndices[FirstIndex+i];
			pIndices[FirstIndex+i]=dummy;
/*
			dummy=Tex[0][nb2vert-i-1];
			Tex[0][nb2vert-i-1]=Tex[0][i];
			Tex[0][i]=dummy;	
*/
		}

	}

};

#endif // !defined(AFX_POLYGON_H__CE588C7F_FA35_4583_AC46_21DA99D9A807__INCLUDED_)
