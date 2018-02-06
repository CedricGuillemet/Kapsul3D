// Polygon.h: interface for the Polygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGON_H__CE588C7F_FA35_4583_AC46_21DA99D9A807__INCLUDED_)
#define AFX_POLYGON_H__CE588C7F_FA35_4583_AC46_21DA99D9A807__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Vertex.h"
class __declspec( dllexport ) KPolygon  
{
public:
    int *nbvert;
    bool Selected;
    int *Tex[4];
    int nb2vert;
	Vertex Normale;
	double D;
public:

	// -- Constructor ---------------------------------------------------------

	inline KPolygon()
	{
		nbvert=0;
		Selected=false;
		
		//Tex=new int*[4];
		
		
		Tex[0]=NULL;
		Tex[1]=NULL;
		Tex[2]=NULL;
		Tex[3]=NULL;
		
		nb2vert=0;
	}

	// -- Destructor ----------------------------------------------------------

	inline virtual ~KPolygon()
	{
		
		for (int i=0;i<4;i++)
			if (Tex[i]!=NULL) free(Tex[i]);

		//delete [] Tex;
		free(nbvert);
		
	}

	// -- Allocate ------------------------------------------------------------

    inline bool Allocate(int nbCanal,int nbv)
	{
		if (nbv!=0)
		{
			if (nb2vert!=0)
			{
				if (nbv!=nb2vert)
					nbvert=(int*)realloc(nbvert,sizeof(int)*nbv);

				for (int i=0;i<nbCanal;i++)
				{
					if (Tex[i]!=NULL)
					{
						if (nbv!=nb2vert)
							Tex[i]=(int*)realloc(Tex[i],sizeof(int)*nbv);
					}
					else
					{
						if ((Tex[i]==NULL)&&(i<nbCanal))
							Tex[i]=(int*)malloc(sizeof(int)*nbv);
					}
				}
			}
			else
			{
				nbvert=(int*)malloc(sizeof(int)*nbv);

				for (int i=0;i<nbCanal;i++)
					Tex[i]=(int*)malloc(sizeof(int)*nbv);
			}

			if (nbv!=0)
			{
				nb2vert=nbv;
			}
		}

		return true;
	}

	// -- Calc plan -----------------------------------------------------------

	void inline CalcPlan(Vertex *pv)
	{
		Normale.Cross(pv[nbvert[1]]-pv[nbvert[0]], pv[nbvert[2]]-pv[nbvert[0]]);
		Normale.Normalize();
		D = -pv[nbvert[2]].Dot(Normale);
	};

	// -- Distance ------------------------------------------------------------

	double inline GetDist(Vertex &vt)
	{
		return Normale.Dot(vt) + D;
	};

	// -- Copy ----------------------------------------------------------------

	void inline IsCopyOf(KPolygon *cmpt)
	{
		int i,j;

		Normale=cmpt->Normale;
		Allocate(1,cmpt->nb2vert);
		nb2vert=cmpt->nb2vert;

		for (i=0;i<cmpt->nb2vert;i++)
		{
			for (j=0;j<4;j++)
				if (Tex[j]!=NULL)
					Tex[j][i]=cmpt->Tex[j][i];
			nbvert[i]=cmpt->nbvert[i];
		}

		D=cmpt->D;

		Selected=cmpt->Selected;
	};

};

#endif // !defined(AFX_POLYGON_H__CE588C7F_FA35_4583_AC46_21DA99D9A807__INCLUDED_)
