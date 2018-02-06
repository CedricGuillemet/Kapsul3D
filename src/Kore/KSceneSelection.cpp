//---------------------------------------------------------------------------
#include "stdafx.h"

//#include "memmgr/mmgr.h"
extern CKOption *KOption2;

#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2]; 

#define TEST_CULL

inline int intersect_triangle( double orig[3], double dir[3],
                    double vert0[3], double vert1[3], double vert2[3],
                    double *t, double *u, double *v)
{
   double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
   double det,inv_det;

   /* find vectors for two edges sharing vert0 */
   SUB(edge1, vert1, vert0);
   SUB(edge2, vert2, vert0);

   /* begin calculating determinant - also used to calculate U parameter */
   CROSS(pvec, dir, edge2);

   /* if determinant is near zero, ray lies in plane of triangle */
   det = DOT(edge1, pvec);

#ifdef TEST_CULL           /* define TEST_CULL if culling is desired */
   if (det < EPSILON)
      return 0;

   /* calculate distance from vert0 to ray origin */
   SUB(tvec, orig, vert0);

   /* calculate U parameter and test bounds */
   *u = DOT(tvec, pvec);
   if (*u < 0.0 || *u > det)
      return 0;

   /* prepare to test V parameter */
   CROSS(qvec, tvec, edge1);

    /* calculate V parameter and test bounds */
   *v = DOT(dir, qvec);
   if (*v < 0.0 || *u + *v > det)
      return 0;

   /* calculate t, scale parameters, ray intersects triangle */
   *t = DOT(edge2, qvec);
   inv_det = 1.0 / det;
   *t *= inv_det;
   *u *= inv_det;
   *v *= inv_det;
#else                    /* the non-culling branch */
   if (det > -EPSILON && det < EPSILON)
     return 0;
   inv_det = 1.0 / det;

   /* calculate distance from vert0 to ray origin */
   SUB(tvec, orig, vert0);

   /* calculate U parameter and test bounds */
   *u = DOT(tvec, pvec) * inv_det;
   if (*u < 0.0 || *u > 1.0)
     return 0;

   /* prepare to test V parameter */
   CROSS(qvec, tvec, edge1);

   /* calculate V parameter and test bounds */
   *v = DOT(dir, qvec) * inv_det;
   if (*v < 0.0 || *u + *v > 1.0)
     return 0;

   /* calculate t, ray intersects triangle */
   *t = DOT(edge2, qvec) * inv_det;
#endif
   return 1;
}

#define PUTVERTEX(X,Y,Z) {if ((!X->Selected)&&(AddIt)) AddBufVert(X,Y,Z); \
							X->Selected=AddIt; \
							HasBeenSel=true; }

CKSkeleton *daTmpSkel;
CKSceneSelection::CKSceneSelection()
{
    //m_Scene=(CKSceneSelection*)daScene;
    
	//Sec = new double [100];

}
CKSceneSelection::~CKSceneSelection()
{
	//delete [] Sec;
}

// -- Tools --------------------------------------------------------------------

void CKSceneSelection::GetEndShapeVert(CKShape **DstShp,CKSegment **DstSeg,CKSegment *Else,int X,int Y)
{
	Vertex Clickhui;
	MYPOINT spt;
    CKShape *daShape;
	MYPOINT sdeb;

	m_Precision=KOption2->Precision();

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	(*DstShp)=NULL;
	(*DstSeg)=NULL;

	// shape 
	daShape=FirstShape;
	while (daShape!=NULL)	
	{
		if ((daShape->NextSegment->Next!=daShape->FirstSegment)&&(daShape->NextSegment!=Else))
		{
			sdeb=Get2D(daShape->NextSegment->Dot);

			if (Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<m_Precision)
			{
				(*DstShp)=daShape;
				(*DstSeg)=daShape->FirstSegment;
			}
		
		}
        daShape=daShape->Next;
    }
}



void CKSceneSelection::GetStartShapeVert(CKShape **DstShp,CKSegment **DstSeg,CKSegment *Else,int X,int Y)
{
	Vertex Clickhui;
	MYPOINT sdeb,spt;
    CKShape *daShape;

	m_Precision=KOption2->Precision();

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	(*DstShp)=NULL;
	(*DstSeg)=NULL;

	// shape 
	daShape=FirstShape;
	while (daShape!=NULL)	
	{
		if ((daShape->NextSegment->Next!=daShape->FirstSegment)&&(daShape->FirstSegment!=Else))
		{
			sdeb=Get2D(daShape->FirstSegment->Dot);

			if (Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<m_Precision)
			{
				(*DstShp)=daShape;
				(*DstSeg)=daShape->NextSegment;
			}
		
		}
        daShape=daShape->Next;
    }
}


void CKSceneSelection::GetShapeVert(CKShape **DstShp,CKSegment **DstSeg,CKSegment *Else,int X,int Y)
{
	Vertex Clickhui;
	MYPOINT sdeb,spt;
    CKShape *daShape;
	CKSegment *daSeg;

	m_Precision=KOption2->Precision();

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	(*DstShp)=NULL;
	(*DstSeg)=NULL;

	// shape 
	daShape=FirstShape;
	while (daShape!=NULL)	
	{

		daSeg=daShape->FirstSegment;
		while (daSeg!=NULL)
		{

			if (daSeg!=Else)
			{
				sdeb=Get2D(daSeg->Dot);

				if (Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<m_Precision)
				{
					(*DstShp)=daShape;
					(*DstSeg)=daSeg;
				}
			}

			daSeg=daSeg->Next;

            if (daSeg==daShape->FirstSegment) break;
			
		}
        daShape=daShape->Next;
    }


}


void CKSceneSelection::GetShapeSeg(CKShape **DstShp,CKSegment **DstSeg,CKSegment *Else,int X,int Y)
{
	Vertex Clickhui;
	MYPOINT sdeb,sfin,spt;
    CKShape *daShape;
	CKSegment *daSeg;

	m_Precision=KOption2->Precision();

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	(*DstShp)=NULL;
	(*DstSeg)=NULL;

	// shape 
	daShape=FirstShape;
	while (daShape!=NULL)	
	{

		daSeg=daShape->FirstSegment;
		while (daSeg!=NULL)
		{

			if (daSeg!=Else)
			{
				sdeb=Get2D(daSeg->Dot);
				sfin=Get2D(daSeg->Next->Dot);

		        if (SegDistance(sdeb,sfin,spt)<m_Precision)
				{
					(*DstShp)=daShape;
					(*DstSeg)=daSeg;
				}
			}

			daSeg=daSeg->Next;

            if ((daSeg==daShape->FirstSegment)||(daSeg->Next==NULL)) break;
			
		}
        daShape=daShape->Next;
    }
}

CKSegment * CKSceneSelection::Collapse(CKShape *daShp,Vertex *daVert)
{
    //int nbSect=0;
    MYPOINT sdeb,spt;
    CKSegment *daSeg;
    //

	if (daShp==NULL) return NULL;

    spt=Get2D((*daVert));

    daSeg=daShp->FirstSegment;

    // -- Height array ---------------------------------------------------------

    while (daSeg!=NULL)
    {

        sdeb=Get2D(daSeg->Dot);

        if ((Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<10) && (daSeg!=daShp->NextSegment) )
            return daSeg;

        if (daSeg->Next==daShp->FirstSegment) break;

        daSeg=daSeg->Next;
    }

    return NULL;
}

MYPOINT CKSceneSelection::Get2D(Vertex daVert)
{
    Vertex temp;
    MYPOINT value;

    m_Renderer->Project((Vertex*)&daVert,(Vertex*)&temp,Active);
    value.x=temp.x;
    value.y=temp.y;
    return value;
}

bool CKSceneSelection::IsVertInBuf(Vertex *daVert)
{
	for (VertBuf *daVB=FirstBufVert;daVB!=NULL;daVB=daVB->Next)
        if (daVB->Dest==daVert)
            return true;

    return false;
}

bool CKSceneSelection::RemoveVert(Vertex *daVert)
{
    /*
    VertBuf *daVB;

    daVB=FirstBufVert;
    while(daVB!=NULL)
    {
        if (daVB->Dest==daVert)
        {
            if (FirstBufVert==daVB)
                FirstBufVert=FirstBufVert->Next;

            if (NextBufVert==daVB)
                NextBufVert=daVB->Prev;

            if (daVB->Prev!=NULL)
                daVB->Prev->Next=daVB->Next;

            if (daVB->Next!=NULL)
                daVB->Next->Prev=daVB->Prev;

            delete daVB;

            return true;
        }

        daVB=daVB->Next;
    }
*/
    return false;
}

Vertex CKSceneSelection::GetCenterOfSel(Vertex *daMin,Vertex *daMax)
{
    VertBuf *daVB;
    Vertex Min,Max,Value;

    daVB=FirstBufVert;
    if (daVB!=NULL)
    {
        Min=daVB->AncVal;
        Max=daVB->AncVal;
    }

    while(daVB!=NULL)
    {
        Min.GetMinOf(daVB->AncVal);
        Max.GetMaxOf(daVB->AncVal);

        daVB=daVB->Next;
    }

    Value.x=Min.x+((Max.x-Min.x)/2);
    Value.y=Min.y+((Max.y-Min.y)/2);
    Value.z=Min.z+((Max.z-Min.z)/2);

	if (daMin!=NULL) *daMin=Min;
	if (daMax!=NULL) *daMax=Max;

    return Value;
}



// -- Camera -------------------------------------------------------------------



bool CKSceneSelection::SelectCam(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
{
	bool HasBeenSel=false;
	bool daAddIt,daAddIt1,daAddIt2;
	MYPOINT sdeb,sfin;

	Vertex Clickhui=m_Renderer->GetIsoCoord(dx,dy,Active);
	MYPOINT spt=Get2D(Clickhui);

	Vertex Clickhui2=m_Renderer->GetIsoCoord(X,Y,Active);
	MYPOINT spt2=Get2D(Clickhui2);

	double Length=Pythagore((X-dx),(Y-dy));

	if (TypeSel==SELECT_SINGLE)
	{
		// Single Camera
		if (WholeSelect==SELECT_WHOLE) 
		{
			CKCamera *daCam=GetCamera(X,Y);
			if (daCam!=NULL)
			{
				PUTVERTEX((&daCam->Source),daCam,0);
				PUTVERTEX((&daCam->Dest),daCam,1);
				daCam->Selected=AddIt;
			}
		}
		else
		{
			// single camera vertex
			for (CKCamera *daCam=FirstCam;daCam!=NULL;daCam=daCam->Next)
			{
				sdeb=Get2D(daCam->Source);
				sfin=Get2D(daCam->Dest);

				if (Pythagore((sdeb.x-spt2.x),(sdeb.y-spt2.y))<10)
					PUTVERTEX((&daCam->Source),daCam,0);

				if (Pythagore((sfin.x-spt2.x),(sfin.y-spt2.y))<10)
					PUTVERTEX((&daCam->Dest),daCam,1);
			}
		}
	}
	else
	{
		for (CKCamera *daCam=FirstCam;daCam!=NULL;daCam=daCam->Next)
		{
			daAddIt=false;

			sdeb=Get2D(daCam->Source);
			sfin=Get2D(daCam->Dest);

			// switch Selction Type

			switch(TypeSel)
			{
				case SELECT_CIRCLE:
					daAddIt1= (Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<Length);
					daAddIt2= (Pythagore((sfin.x-spt.x),(sfin.y-spt.y))<Length);
					break;

				case SELECT_QUAD:
					daAddIt1= (((sdeb.x>=spt.x)&&(sdeb.x<=spt2.x))||((sdeb.x<=spt.x)&&(sdeb.x>=spt2.x)))&&
					(((sdeb.y>=spt.y)&&(sdeb.y<=spt2.y))||((sdeb.y<=spt.y)&&(sdeb.y>=spt2.y)));
                    daAddIt2= (((sfin.x>=spt.x)&&(sfin.x<=spt2.x))||((sfin.x<=spt.x)&&(sfin.x>=spt2.x)))&&
					(((sfin.y>=spt.y)&&(sfin.y<=spt2.y))||((sfin.y<=spt.y)&&(sfin.y>=spt2.y)));
					break;
				case SELECT_FENCE:
					daAddIt1=( daSh->IsVertInShape(daCam->Source,m_Renderer));
					daAddIt2=( daSh->IsVertInShape(daCam->Dest,m_Renderer));
					break;
			}

			if (WholeSelect==SELECT_WHOLE) 
			{
				if (Crossing) daAddIt=daAddIt1 || daAddIt2;
					else daAddIt=daAddIt1 && daAddIt2;

				// Add it if OK!
				if (daAddIt)
				{
					PUTVERTEX((&daCam->Source),daCam,0);
					PUTVERTEX((&daCam->Dest),daCam,1);
					daCam->Selected=AddIt;
				}
			}
			else
			{
				if (daAddIt1) PUTVERTEX((&daCam->Source),daCam,0);
				if (daAddIt2) PUTVERTEX((&daCam->Dest),daCam,1);
			}
		} // Next camera
	}
	RemoveBufUnselected();
    return HasBeenSel;
}

// -- Object -------------------------------------------------------------------

bool CKSceneSelection::SelectMesh(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
{
    int i,j,ii,ik;
	bool daAddIt,daAddIt2,HasBeenSel=false;
	MYPOINT sdot;

	m_Precision=KOption2->Precision();

    Vertex Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    MYPOINT spt=Get2D(Clickhui);

    Vertex Clickhui2=m_Renderer->GetIsoCoord(dx,dy,Active);
    MYPOINT spt2=Get2D(Clickhui2);

    double Length=Pythagore((spt2.x-spt.x),(spt2.y-spt.y));
	if ((TypeSel==SELECT_SINGLE)&&(WholeSelect==SELECT_FACE))
	{
		int FaceNb=-1;
		CKMesh *daMesh=GetMeshByTriangle(X,Y,false,&FaceNb);
		if (FaceNb!=-1)
		{	
			daMesh->pl[FaceNb].Selected=AddIt;
			for (i=0;i<daMesh->pl[FaceNb].nb2vert;i++)
			{
				PUTVERTEX((&daMesh->pv[daMesh->pl[FaceNb].nbvert[i]]),daMesh,daMesh->pl[FaceNb].nbvert[i]); 
			}
		}
	}
	else
	if ((TypeSel==SELECT_SINGLE)&&(WholeSelect==SELECT_WHOLE))
	{
		if (!GetCentroid())
		{
			CKMesh *daMesh=GetMeshByTriangle(X,Y,false);
			if (daMesh!=NULL)
			{
				//AddIt=!daMesh->Selected;
				for (ii=0;ii<daMesh->nb2vert;ii++)
					PUTVERTEX((&daMesh->pv[ii]),daMesh,ii);

				daMesh->Selected=AddIt;
			}
		}
		else
		{
			// centroid
			for (CKMesh *daMesh=FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
			{
				Vertex MeshCenter=daMesh->Min+(daMesh->Max-daMesh->Min)/2;

				sdot=Get2D((MeshCenter));
					
				daAddIt=(Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<m_Precision);
				if (daAddIt)
				{
					for (i=0;i<daMesh->nb2poly;i++)
					{
						for (ik=0;ik<daMesh->pl[i].nb2vert;ik++) 
							PUTVERTEX((&daMesh->pv[daMesh->pl[i].nbvert[ik]]),daMesh,ik);

						daMesh->pl[i].Selected=AddIt;
					}
				}
			}
		}
	}
	else
	{
		for (CKMesh *daMesh=FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			// Select vertex and whole
			if ((WholeSelect==SELECT_WHOLE)||(WholeSelect==SELECT_VERTEX))
			{
				daAddIt2=!Crossing;

				for (i=0;i<daMesh->nb2vert;i++)
				{
					sdot=Get2D((daMesh->pv[i]));
					
					// test it
					switch(TypeSel)
					{
						case SELECT_SINGLE:
							daAddIt=(Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<m_Precision);
							break;
						case SELECT_QUAD:
							daAddIt=( ( (((sdot.x>=spt.x)&&(sdot.x<=spt2.x))||((sdot.x<=spt.x)&&(sdot.x>=spt2.x)))&&
								(((sdot.y>=spt.y)&&(sdot.y<=spt2.y))||((sdot.y<=spt.y)&&(sdot.y>=spt2.y))) ) );
							break;
						case SELECT_CIRCLE:
							daAddIt=(Pythagore((sdot.x-spt2.x),(sdot.y-spt2.y))<=Length);
							break;
						case SELECT_FENCE:
							daAddIt=daSh->IsVertInShape((daMesh->pv[i]),m_Renderer);
							break;
					}
					// Set it
					if (WholeSelect==SELECT_WHOLE)
					{
						if (Crossing)
						{
							if (daAddIt)
							{
								daAddIt2=true;
								i=daMesh->nb2vert;
							}
						}
						else
						{
							daAddIt2&=daAddIt;
						}
					}

					if (WholeSelect==SELECT_VERTEX)
						if (daAddIt)
						{
							PUTVERTEX((&daMesh->pv[i]),daMesh,i);
							if (TypeSel==SELECT_SINGLE) return HasBeenSel;
						}
				}
				if (WholeSelect==SELECT_WHOLE)
				{
					if (daAddIt2)
					{
						for (ii=0;ii<daMesh->nb2vert;ii++)
							PUTVERTEX((&daMesh->pv[ii]),daMesh,ii); 

						daMesh->Selected=AddIt;
					}
				}
			}
			else
			{
				// select Face 
				for (i=0;i<daMesh->nb2poly;i++)
				{
					daAddIt2=!Crossing;

					for (j=0;j<daMesh->pl[i].nb2vert;j++)
					{
						

						sdot=Get2D((daMesh->pv[daMesh->pl[i].nbvert[j]]));
						switch(TypeSel)
						{
						case SELECT_SINGLE:
								daAddIt=(Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<m_Precision);
								break;
							case SELECT_QUAD:
								daAddIt=( ( (((sdot.x>=spt.x)&&(sdot.x<=spt2.x))||((sdot.x<=spt.x)&&(sdot.x>=spt2.x)))&&
									(((sdot.y>=spt.y)&&(sdot.y<=spt2.y))||((sdot.y<=spt.y)&&(sdot.y>=spt2.y))) ) );
								break;
							case SELECT_CIRCLE:
								daAddIt=(Pythagore((sdot.x-spt2.x),(sdot.y-spt2.y))<=Length);
								break;
							case SELECT_FENCE:
								daAddIt=daSh->IsVertInShape((daMesh->pv[daMesh->pl[i].nbvert[j]]),m_Renderer);
								break;
						}

						// Set It
						if (Crossing)
						{
							if (daAddIt)
							{
								daAddIt2=true;
								j=daMesh->pl[i].nb2vert;
							}
						}
						else
						{
							daAddIt2&=daAddIt;
						}
					}

					if (daAddIt2)
					{
						for (ik=0;ik<daMesh->pl[i].nb2vert;ik++) 
							PUTVERTEX((&daMesh->pv[daMesh->pl[i].nbvert[ik]]),daMesh,ik);

						daMesh->pl[i].Selected=AddIt;
					}
				}
			}
		}
	}
	RemoveBufUnselected();
	if (m_UVSelUpdate)
	{
		SelectedToUVBuffer(0);
	}
	return HasBeenSel;
}


bool CKSceneSelection::SelectUV(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
{
    int i;
	bool daAddIt,HasBeenSel=false;

	m_Precision=KOption2->Precision();

	CKPlan dap;
	dap.PlanOfView(m_Renderer,Active);

	Vertex Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    MYPOINT spt=Get2D(Clickhui);

    Vertex Clickhui2=m_Renderer->GetIsoCoord(dx,dy,Active);
    MYPOINT spt2=Get2D(Clickhui2);

    double Length=Pythagore((spt2.x-spt.x),(spt2.y-spt.y));

	//CKPlan dap;
	//dap.PlanOfView(m_Renderer,Active);

	//MYPOINT spt3=Get2D(Vertex(0,0,0));



	Vertex ClickhuiDot;

	for (i=0;i<m_CountUV;i++)
	{
		
		
		ClickhuiDot.x=(UVEdit[i].u*64.0f);
		ClickhuiDot.y=(-UVEdit[i].v*64.0f);
		ClickhuiDot.z=0;

		MYPOINT sdot=Get2D(ClickhuiDot);
		

		

		switch(TypeSel)
		{
			case SELECT_SINGLE:
				daAddIt=(Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<m_Precision);
				break;
			case SELECT_QUAD:
				daAddIt=( ( (((sdot.x>=spt.x)&&(sdot.x<=spt2.x))||((sdot.x<=spt.x)&&(sdot.x>=spt2.x)))&&
					(((sdot.y>=spt.y)&&(sdot.y<=spt2.y))||((sdot.y<=spt.y)&&(sdot.y>=spt2.y))) ) );
				break;
			case SELECT_CIRCLE:
				daAddIt=(Pythagore((sdot.x-spt2.x),(sdot.y-spt2.y))<=Length);
				break;
				/*
			case SELECT_FENCE:
				daAddIt=daSh->IsVertInShape((daMesh->pv[i]),m_Renderer);
				break;
				*/
		}

		if (daAddIt)
		{
			UVEdit[i].Selected=AddIt;
			HasBeenSel=true;

		}
	}

	if (HasBeenSel)
	{
		UpdateMinMaxUVBuf();
	}

	return HasBeenSel;
}

bool CKSceneSelection::SingleObjEdge(int X,int Y,bool AddIt)
{
	CKMesh *daMesh;
	MYPOINT sdeb,sfin,spt;
	
	m_Precision=KOption2->Precision();

    Vertex Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	for (daMesh=FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		for (int i=0;i<daMesh->nb2poly;i++)
		{
			for (int j=0;j<(daMesh->pl[i].nb2vert-1);j++)
			{
				sdeb=Get2D(daMesh->pv[daMesh->pl[i].nbvert[j]]);
				sfin=Get2D(daMesh->pv[daMesh->pl[i].nbvert[j+1]]);

				if (SegDistance(sdeb,sfin,spt)<m_Precision)
				{
					if ((!daMesh->pv[daMesh->pl[i].nbvert[j]].Selected)&&(AddIt)) AddBufVert(&daMesh->pv[daMesh->pl[i].nbvert[j]],daMesh,daMesh->pl[i].nbvert[j]);
					if ((!daMesh->pv[daMesh->pl[i].nbvert[j+1]].Selected)&&(AddIt)) AddBufVert(&daMesh->pv[daMesh->pl[i].nbvert[j+1]],daMesh,daMesh->pl[i].nbvert[j+1]);

					daMesh->pv[daMesh->pl[i].nbvert[j+1]].Selected=AddIt;
					daMesh->pv[daMesh->pl[i].nbvert[j]].Selected=AddIt;

					RemoveBufUnselected();
					return true;
				}
			}
		}
	}
	return false;
}

// -- CKSkeleton ----------------------------------------------------------------

bool CKSceneSelection::RecSingleSkel(CKBone *daBone,bool AddIt)
{
    CKBone *daBone2;

    if ((!daBone->Selected)&&(AddIt))
	{
		AddBufVert(&daBone->Pos,daTmpSkel);
		//NextBufVert->Skel=daTmpSkel;
	}
    daBone->Pos.Selected=AddIt;

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
        RecSingleSkel(daBone2,AddIt);
        daBone2=daBone2->Next;
    }
    return true;
}

bool CKSceneSelection::SingleSkel(int X,int Y,bool AddIt)
{
    CKSkeleton *daSkel;
    bool value=false;

    daSkel=GetSkeleton(X,Y);
    if (daSkel!=NULL)
    {
		daTmpSkel=daSkel;

        if ((!daSkel->Selected)&&(AddIt))
		{
			AddBufVert(&daSkel->RootPos,daSkel);
			//NextBufVert->Skel=daSkel;
		}
        daSkel->RootPos.Selected=AddIt;

        RecSingleSkel(daSkel->bone,AddIt);
        value=true;
        RemoveBufUnselected();
    }
	return value;
}

// -- circle

void CKSceneSelection::RecIsAllSkelInCircle(CKBone *daBone,int dx,int dy,int X,int Y,double Length,bool *AllIn,bool *OneIn)
{
    Vertex Clickhui;
    MYPOINT sdot,spt;
    bool value=false;
    CKBone *daBone2;

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

    // omni
    sdot=Get2D(daBone->Pos);
    if (Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<Length)
    {
        (*AllIn)&=true;
        (*OneIn)|=true;
    }
    else
    {
        (*AllIn)=false;
    }

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
        RecIsAllSkelInCircle(daBone2,dx,dy,X,Y,Length,AllIn,OneIn);
        daBone2=daBone2->Next;
    }
}

void CKSceneSelection::IsAllSkelInCircle(CKSkeleton *daSkel,int dx,int dy,int X,int Y,double Length,bool *AllIn,bool *OneIn)
{
    Vertex Clickhui;
    MYPOINT sdot,spt;
    bool value=false;
    CKBone *daBone2;

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

    // omni
    sdot=Get2D(daSkel->RootPos);
    if (Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<Length)
    {
        (*AllIn)&=true;
        (*OneIn)|=true;
    }
    else
    {
        (*AllIn)=false;
    }

    daBone2=daSkel->bone;
    while(daBone2!=NULL)
    {
        RecIsAllSkelInCircle(daBone2,dx,dy,X,Y,Length,AllIn,OneIn);
        daBone2=daBone2->Next;
    }
}

bool CKSceneSelection::CircleSkel(int dx,int dy,int X,int Y,bool AddIt,bool Crossing)
{
    CKSkeleton *daSkel;
    bool value=false;
    bool AllIn,OneIn;
    Vertex Clickhui;
    MYPOINT spt;
    double Length;

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);
    Length=Pythagore((X-dx),(Y-dy));

    OneIn=false;
    AllIn=false;

    daSkel=FirstSkel;
    if (daSkel!=NULL)
    {
		daTmpSkel=daSkel;

        IsAllSkelInCircle(daSkel,dx,dy,X,Y,Length,&AllIn,&OneIn);

        if (Crossing)
        {
            if (OneIn)
            {
                if ((!daSkel->Selected)&&(AddIt))
				{
					AddBufVert(&daSkel->RootPos,daSkel);
					//NextBufVert->Skel=daSkel;
				}
                daSkel->RootPos.Selected=AddIt;
                RecSingleSkel(daSkel->bone,AddIt);
            }
        }
        else
        {
            if (AllIn)
            {
                if ((!daSkel->Selected)&&(AddIt))
				{
					AddBufVert(&daSkel->RootPos,daSkel);
					//NextBufVert->Skel=daSkel;
				}
                daSkel->RootPos.Selected=AddIt;
                RecSingleSkel(daSkel->bone,AddIt);
            }
            
        }
        value=true;
        
    }
    RemoveBufUnselected();
	return value;
}


// -- quad

void CKSceneSelection::RecIsAllSkelInQuad(CKBone *daBone,int dx,int dy,int X,int Y,bool *AllIn,bool *OneIn)
{
    Vertex Clickhui;
    MYPOINT sdot,spt,spt2;
    bool value=false;
    CKBone *daBone2;

    Clickhui=m_Renderer->GetIsoCoord(dx,dy,Active);
    spt=Get2D(Clickhui);

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt2=Get2D(Clickhui);

    // omni
    sdot=Get2D(daBone->Pos);
    if ( (((sdot.x>=spt.x)&&(sdot.x<=spt2.x))||((sdot.x<=spt.x)&&(sdot.x>=spt2.x)))&&
        (((sdot.y>=spt.y)&&(sdot.y<=spt2.y))||((sdot.y<=spt.y)&&(sdot.y>=spt2.y))) )
    {
        (*AllIn)&=true;
        (*OneIn)|=true;
    }
    else
    {
        (*AllIn)=false;
    }

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
        RecIsAllSkelInQuad(daBone2,dx,dy,X,Y,AllIn,OneIn);
        daBone2=daBone2->Next;
    }
}

void CKSceneSelection::IsAllSkelInQuad(CKSkeleton *daSkel,int dx,int dy,int X,int Y,bool *AllIn,bool *OneIn)
{
    Vertex Clickhui;
    MYPOINT sdot,spt,spt2;
    bool value=false;
    CKBone *daBone2;

    Clickhui=m_Renderer->GetIsoCoord(dx,dy,Active);
    spt=Get2D(Clickhui);

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt2=Get2D(Clickhui);

    // omni
    sdot=Get2D(daSkel->RootPos);
    if ( (((sdot.x>=spt.x)&&(sdot.x<=spt2.x))||((sdot.x<=spt.x)&&(sdot.x>=spt2.x)))&&
        (((sdot.y>=spt.y)&&(sdot.y<=spt2.y))||((sdot.y<=spt.y)&&(sdot.y>=spt2.y))) )
    {
        (*AllIn)&=true;
        (*OneIn)|=true;
    }
    else
    {
        (*AllIn)=false;
    }

    daBone2=daSkel->bone;
    while(daBone2!=NULL)
    {
        RecIsAllSkelInQuad(daBone2,dx,dy,X,Y,AllIn,OneIn);
        daBone2=daBone2->Next;
    }
}

bool CKSceneSelection::QuadSkel(int dx,int dy,int X,int Y,bool AddIt,bool Crossing)
{
    CKSkeleton *daSkel;
    bool value=false;
    bool AllIn,OneIn;
    Vertex Clickhui;

    OneIn=false;
    AllIn=false;

    daSkel=FirstSkel;
    if (daSkel!=NULL)
    {
		daTmpSkel=daSkel;

        IsAllSkelInQuad(daSkel,dx,dy,X,Y,&AllIn,&OneIn);

        if (Crossing)
        {
            if (OneIn)
            {
                if ((!daSkel->Selected)&&(AddIt))
				{
					AddBufVert(&daSkel->RootPos,daSkel);
					//NextBufVert->Skel=daSkel;
				}
                daSkel->RootPos.Selected=AddIt;
                RecSingleSkel(daSkel->bone,AddIt);
            }
        }
        else
        {
            if (AllIn)
            {
                if ((!daSkel->Selected)&&(AddIt))
				{
					AddBufVert(&daSkel->RootPos,daSkel);
					//NextBufVert->Skel=daSkel;
				}
                daSkel->RootPos.Selected=AddIt;
                RecSingleSkel(daSkel->bone,AddIt);
            }
            
        }
        value=true;
        
    }
    RemoveBufUnselected();
	return value;
}	


// -- fence

void CKSceneSelection::IsAllSkelInFence(CKBone *daBone,int dx,int dy,int X,int Y,CKShape *daSh,bool *AllIn,bool *OneIn)
{
    Vertex Clickhui;
    bool value=false;
    CKBone *daBone2;

    if ( daSh->IsVertInShape(daBone->Pos,m_Renderer))
    {
        (*AllIn)&=true;
        (*OneIn)|=true;
    }
    else
    {
        (*AllIn)=false;
    }

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
        IsAllSkelInFence(daBone2,dx,dy,X,Y,daSh,AllIn,OneIn);
        daBone2=daBone2->Next;
    }
}

void CKSceneSelection::IsAllSkelInFence(CKSkeleton *daSkel,int dx,int dy,int X,int Y,CKShape *daSh,bool *AllIn,bool *OneIn)
{
    Vertex Clickhui;
    bool value=false;
    CKBone *daBone2;

    if ( daSh->IsVertInShape(daSkel->RootPos,m_Renderer))
    {
        (*AllIn)&=true;
        (*OneIn)|=true;
    }
    else
    {
        (*AllIn)=false;
    }

    daBone2=daSkel->bone;
    while(daBone2!=NULL)
    {
        IsAllSkelInFence(daBone2,dx,dy,X,Y,daSh,AllIn,OneIn);
        daBone2=daBone2->Next;
    }
}

bool CKSceneSelection::FenceSkel(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing)
{
    CKSkeleton *daSkel;
    bool value=false;
    bool AllIn,OneIn;
    Vertex Clickhui;

    OneIn=false;
    AllIn=false;

    daSkel=FirstSkel;
    if (daSkel!=NULL)
    {
		daTmpSkel=daSkel;
        IsAllSkelInFence(daSkel,dx,dy,X,Y,daSh,&AllIn,&OneIn);

        if (Crossing)
        {
            if (OneIn)
            {
                if ((!daSkel->Selected)&&(AddIt))
				{
					AddBufVert(&daSkel->RootPos,daSkel);
					//NextBufVert->Skel=daSkel;
				}
                daSkel->RootPos.Selected=AddIt;
                RecSingleSkel(daSkel->bone,AddIt);
            }
        }
        else
        {
            if (AllIn)
            {
                if ((!daSkel->Selected)&&(AddIt))
				{
					AddBufVert(&daSkel->RootPos,daSkel);
					//NextBufVert->Skel=daSkel;
				}
                daSkel->RootPos.Selected=AddIt;
                RecSingleSkel(daSkel->bone,AddIt);
            }
            
        }
        value=true;
        
    }
    RemoveBufUnselected();
	return value;
}

// -- Bone ---------------------------------------------------------------------

bool CKSceneSelection::RecSelectBone(CKBone *daBone,CKSkeleton *daSkel,MYPOINT &spt,MYPOINT &spt2,double Length,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
{
    Vertex Clickhui,Clickhui2;
    CKBone *daBone2;
    bool HasBeenSel=false;
	bool daAddIt;

	MYPOINT sdeb=Get2D(daBone->Pos);

	switch(TypeSel)
	{
		case SELECT_SINGLE:
			daAddIt=(Pythagore((sdeb.x-spt2.x),(sdeb.y-spt2.y))<m_Precision);
			break;
		case SELECT_CIRCLE:
			daAddIt=(Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<Length);
			break;
		case SELECT_QUAD:
			daAddIt=( (((sdeb.x>=spt.x)&&(sdeb.x<=spt2.x))||((sdeb.x<=spt.x)&&(sdeb.x>=spt2.x)))&&
				(((sdeb.y>=spt.y)&&(sdeb.y<=spt2.y))||((sdeb.y<=spt.y)&&(sdeb.y>=spt2.y))) );
			break;
		case SELECT_FENCE:
			daAddIt=daSh->IsVertInShape(daBone->Pos,m_Renderer);
			break;
	}
	
	if (daAddIt) 
	{
//		PUTVERTEX((&daBone->Pos),daSkel,daBone);
	}

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
        HasBeenSel|=RecSelectBone(daBone2,daSkel,spt,spt2,Length,daSh,AddIt,Crossing,TypeSel,WholeSelect);
        daBone2=daBone2->Next;
    }

	return HasBeenSel;
}


bool CKSceneSelection::SelectBone(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
{
    CKBone *daBone2;
    CKSkeleton *daSkel;
	MYPOINT sdeb;
	bool daAddIt;
	bool HasBeenSel=false;;

	m_Precision=KOption2->Precision();

    Vertex Clickhui=m_Renderer->GetIsoCoord(dx,dy,Active);
    MYPOINT spt=Get2D(Clickhui);

    Vertex Clickhui2=m_Renderer->GetIsoCoord(X,Y,Active);
    MYPOINT spt2=Get2D(Clickhui2);

	double Length=Pythagore((X-dx),(Y-dy));


    daSkel=FirstSkel;
	while(daSkel!=NULL)
	{
		daTmpSkel=daSkel;

		sdeb=Get2D(daSkel->RootPos);

		switch(TypeSel)
		{
			case SELECT_SINGLE:
				daAddIt=(Pythagore((sdeb.x-spt2.x),(sdeb.y-spt2.y))<m_Precision);
				break;
			case SELECT_CIRCLE:
				daAddIt=(Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<Length);
				break;
			case SELECT_QUAD:
				daAddIt=( (((sdeb.x>=spt.x)&&(sdeb.x<=spt2.x))||((sdeb.x<=spt.x)&&(sdeb.x>=spt2.x)))&&
					(((sdeb.y>=spt.y)&&(sdeb.y<=spt2.y))||((sdeb.y<=spt.y)&&(sdeb.y>=spt2.y))) );
				break;
			case SELECT_FENCE:
				daAddIt=daSh->IsVertInShape(daSkel->RootPos,m_Renderer);
				break;
		}
		
		if (daAddIt) 
		{
//			PUTVERTEX((&daSkel->RootPos),daSkel,NULL);
		}

        daBone2=daSkel->bone->FirstBone;
		while(daBone2!=NULL)
		{
            HasBeenSel|=RecSelectBone(daBone2,daSkel,spt,spt2,Length,daSh,AddIt,Crossing,TypeSel,WholeSelect);
			daBone2=daBone2->Next;
		}

		daSkel=daSkel->Next;
	}
    RemoveBufUnselected();
    return HasBeenSel;
}

// -- Shape CKSceneSelection ---------------------------------------------------------------

bool CKSceneSelection::SelectShape(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
{
	MYPOINT sdeb,sfin;
    bool HasBeenSel=false;
	bool daAddIt,daAddIt1;
	CKSegment *daSeg;

	m_Precision=KOption2->Precision();

	if ((TypeSel==SELECT_SINGLE)&&(WholeSelect==SELECT_WHOLE))
	{
		CKShape *Shp=GetShape(X,Y);
		if (Shp!=NULL)
		{
			daSeg=Shp->FirstSegment;
			while(daSeg!=NULL)
			{  
				PUTVERTEX((&daSeg->Dot),Shp,daSeg);
				daSeg->Selected=AddIt;
				daSeg=daSeg->Next;
				if (daSeg==Shp->FirstSegment) break;
			}
			Shp->Selected=AddIt;
			RemoveBufUnselected();
			return true;
		}
		RemoveBufUnselected();
		return false;
	}
	if ((TypeSel==SELECT_SINGLE)&&(WholeSelect==SELECT_FACE))
	{
		CKShape *daShape;
		GetShapeSeg(&daShape,&daSeg,NULL,X,Y);
		if (daSeg!=NULL)
		{
			if (daSeg->Next!=NULL)
			{
				if ((!daSeg->Dot.Selected)&&(AddIt)) AddBufVert(&daSeg->Dot);
				if ((!daSeg->Next->Dot.Selected)&&(AddIt)) AddBufVert(&daSeg->Next->Dot);

				daSeg->SegSelected=AddIt;
				daSeg->Dot.Selected=AddIt;
				daSeg->Next->Dot.Selected=AddIt;
			}
			RemoveBufUnselected();
			return true;
		}
		RemoveBufUnselected();
		return false;
	}
    

    Vertex Clickhui=m_Renderer->GetIsoCoord(dx,dy,Active);
    MYPOINT spt=Get2D(Clickhui);

    Vertex Clickhui2=m_Renderer->GetIsoCoord(X,Y,Active);
    MYPOINT spt2=Get2D(Clickhui2);

	double Length=Pythagore((X-dx),(Y-dy));

	for (CKShape *daShp=FirstShape;daShp!=NULL;daShp=daShp->Next)
    {
		daAddIt=!Crossing;

		daSeg=daShp->FirstSegment;
		while (daSeg->Next!=NULL)
		{
			sdeb=Get2D(daSeg->Dot);
			sfin=Get2D(daSeg->Next->Dot);

			if (WholeSelect==SELECT_FACE)
			{
				//Segment

				daAddIt=false;

				switch(TypeSel)
				{
					case SELECT_CIRCLE:
						if (Crossing)
							daAddIt=( (Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<Length) || (Pythagore((sfin.x-spt.x),(sfin.y-spt.y))<Length) );
						else
							daAddIt=( (Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<Length) && (Pythagore((sfin.x-spt.x),(sfin.y-spt.y))<Length) );
						break;
					case SELECT_QUAD:
						if (Crossing)
                        daAddIt= ( ( (((sdeb.x>=spt.x)&&(sdeb.x<=spt2.x))||((sdeb.x<=spt.x)&&(sdeb.x>=spt2.x)))&&
                            (((sdeb.y>=spt.y)&&(sdeb.y<=spt2.y))||((sdeb.y<=spt.y)&&(sdeb.y>=spt2.y))) ) ||
                            ( (((sfin.x>=spt.x)&&(sfin.x<=spt2.x))||((sfin.x<=spt.x)&&(sfin.x>=spt2.x)))&&
                            (((sfin.y>=spt.y)&&(sfin.y<=spt2.y))||((sfin.y<=spt.y)&&(sfin.y>=spt2.y))) ) );
						else
                        daAddIt= ( ( (((sdeb.x>=spt.x)&&(sdeb.x<=spt2.x))||((sdeb.x<=spt.x)&&(sdeb.x>=spt2.x)))&&
                            (((sdeb.y>=spt.y)&&(sdeb.y<=spt2.y))||((sdeb.y<=spt.y)&&(sdeb.y>=spt2.y))) ) &&
                            ( (((sfin.x>=spt.x)&&(sfin.x<=spt2.x))||((sfin.x<=spt.x)&&(sfin.x>=spt2.x)))&&
                            (((sfin.y>=spt.y)&&(sfin.y<=spt2.y))||((sfin.y<=spt.y)&&(sfin.y>=spt2.y))) ) );
						break;
					case SELECT_FENCE:
						if (Crossing)
							daAddIt= (  daSh->IsVertInShape(daSeg->Dot,m_Renderer) || daSh->IsVertInShape(daSeg->Next->Dot,m_Renderer) );
						else
							daAddIt= (  daSh->IsVertInShape(daSeg->Dot,m_Renderer) && daSh->IsVertInShape(daSeg->Next->Dot,m_Renderer) );
						break;
				}

                if (daAddIt)
                {
                    if ((!daSeg->Dot.Selected)&&(AddIt)) AddBufVert(&daSeg->Dot);
                    if ((!daSeg->Next->Dot.Selected)&&(AddIt)) AddBufVert(&daSeg->Next->Dot);

                    daSeg->SegSelected=AddIt;
                    daSeg->Dot.Selected=AddIt;
                    daSeg->Next->Dot.Selected=AddIt;
                }

			}
			else
			{
				// Whole/Vertex
				daAddIt1=false;

				switch(TypeSel)
				{
					case SELECT_SINGLE:
						daAddIt1=(Pythagore((sdeb.x-spt2.x),(sdeb.y-spt2.y))<m_Precision);
						break;
					case SELECT_CIRCLE:
						daAddIt1=(Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<Length);
						break;
					case SELECT_QUAD:
						daAddIt1=( (((sdeb.x>=spt.x)&&(sdeb.x<=spt2.x))||((sdeb.x<=spt.x)&&(sdeb.x>=spt2.x)))&&
							(((sdeb.y>=spt.y)&&(sdeb.y<=spt2.y))||((sdeb.y<=spt.y)&&(sdeb.y>=spt2.y))) );
						break;
					case SELECT_FENCE:
						daAddIt1=daSh->IsVertInShape(daSeg->Dot,m_Renderer);
						break;
				}

				if (WholeSelect==SELECT_WHOLE)
				{
					if (daAddIt1&&Crossing)
					{
						daAddIt=true;
						break;
					}
					else
					if ((!daAddIt1)&&(!Crossing))
					{
						daAddIt&=daAddIt1;
					}
				}
				else
				{
					// select vertex
					if (daAddIt1) PUTVERTEX((&daSeg->Dot),daShp,daSeg);
				}
			}

			daSeg=daSeg->Next;

            if (daSeg==daShp->FirstSegment) break;
		}
		// select whole if needed
		if (WholeSelect==SELECT_WHOLE)
		{
			if (daAddIt)
			{
				daSeg=daShp->FirstSegment;
				while (daSeg!=NULL)
				{
					PUTVERTEX((&daSeg->Dot),daShp,daSeg);
					daSeg=daSeg->Next;
					if (daSeg==daShp->FirstSegment) break;
				}
			}
		}
	}

    RemoveBufUnselected();
	return HasBeenSel;
}


// -- Single Ptr ---------------------------------------------------------------

CKCamera *CKSceneSelection::GetCamera(int X,int Y)
{
    Vertex Clickhui,Clickhui2,Camhui,Camhui2;
    CKCamera *daCam;
    //
    MYPOINT sdeb,sfin,spt;

	m_Precision=KOption2->Precision();

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);

    spt=Get2D(Clickhui);

    daCam=FirstCam;
    while(daCam!=NULL)
    {
        sdeb=Get2D(daCam->Source);
        sfin=Get2D(daCam->Dest);

        if (SegDistance(sdeb,sfin,spt)<m_Precision)
        {
            return daCam;
        }

        daCam=daCam->Next;
    }

    return NULL;
}

CKCamera *CKSceneSelection::GetCamera(int X,int Y,bool IsTarget)
{
    Vertex Clickhui,Clickhui2,Camhui,Camhui2;
    CKCamera *daCam;
    //Math Maths;
    MYPOINT sdeb,sfin,spt;
    bool HasBeenSel=false;


    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

    daCam=FirstCam;
    while(daCam!=NULL)
    {
        if (!IsTarget)
        {
            sdeb=Get2D(daCam->Source);

            if (Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<10)
            {
                return daCam;
            }
        }
        else
        {

            sfin=Get2D(daCam->Dest);

            if (Pythagore((sfin.x-spt.x),(sfin.y-spt.y))<10)
            {
                return daCam;
            }
        }
        daCam=daCam->Next;
    }
    return NULL;
}

CKMesh *CKSceneSelection::GetMeshByTriangle(int X,int Y,bool SelectIt,int *FaceNb)
{
    Vertex Clickhui,Clickhui2,Camhui,Camhui2;
    CKMesh *daMesh;
    //MYPOINT sdot1,sdot2,sdot3,spt,v1tmp,v2tmp;
    int i,j;
	double orig[3],dir[3],vert0[3],vert1[3],vert2[3];

	CKPlan dap;
	dap.PlanOfView(m_Renderer,Active);

	if (ViewType[Active]==VIEWTYPE_PERSPECTIVE)
	{
		Clickhui=m_Renderer->GetIsoCoord(X,Y,Active,Perspective[Active].Source+(Perspective[Active].Dest-Perspective[Active].Source)/100.0f);
		Clickhui2=m_Renderer->GetIsoCoord(X,Y,Active,Perspective[Active].Dest);
	}
	else
	{
		if (ViewType[Active]==VIEWTYPE_CAMERA)
		{
			Clickhui=m_Renderer->GetIsoCoord(X,Y,Active,cam[Active]->Source+(cam[Active]->Dest-cam[Active]->Source)/100.0f);
			Clickhui2=m_Renderer->GetIsoCoord(X,Y,Active,cam[Active]->Dest);
		}
		else
		{
			Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
			Clickhui2=Clickhui+dap.pZ;//m_Renderer->GetIsoCoord(X,Y,Active,dap.pZ);
		}
	}
	
	orig[0]=Clickhui.x;
	orig[1]=Clickhui.y;
	orig[2]=Clickhui.z;

	dir[0]=Clickhui2.x-Clickhui.x;
	dir[1]=Clickhui2.y-Clickhui.y;
	dir[2]=Clickhui2.z-Clickhui.z;

	double t,u,v;
	double daDist=999999999,daDist2;
	CKMesh *gObj=NULL;

    daMesh=FirstMesh;
    while(daMesh!=NULL)
    {
        if ((!daMesh->Selected)||(!SelectIt))
        {
            if (daMesh->pl!=NULL)
            {
                for (i=0;i<daMesh->nb2poly;i++)
                {
					Vertex PolyZ;

					for (j=0;j<daMesh->pl[i].nb2vert-2;j++)
					{
						vert0[0]=daMesh->pv[daMesh->pl[i].nbvert[0]].x;
						vert0[1]=daMesh->pv[daMesh->pl[i].nbvert[0]].y;
						vert0[2]=daMesh->pv[daMesh->pl[i].nbvert[0]].z;

						vert1[0]=daMesh->pv[daMesh->pl[i].nbvert[j+1]].x;
						vert1[1]=daMesh->pv[daMesh->pl[i].nbvert[j+1]].y;
						vert1[2]=daMesh->pv[daMesh->pl[i].nbvert[j+1]].z;

						vert2[0]=daMesh->pv[daMesh->pl[i].nbvert[j+2]].x;
						vert2[1]=daMesh->pv[daMesh->pl[i].nbvert[j+2]].y;
						vert2[2]=daMesh->pv[daMesh->pl[i].nbvert[j+2]].z;

						if (intersect_triangle(orig,dir,vert0,vert1,vert2,&t,&u,&v))
						{
							daDist2=t;
							if (((daDist2<daDist)&&(daDist2>0)) || (ViewType[Active]==VIEWTYPE_ORTHO))
							{
								if (FaceNb!=NULL) *FaceNb=i;

								daDist=t;//daDist2;
								gObj=daMesh;
								j=daMesh->pl[i].nb2vert;
							}
						}
					}
                }
            }
        }
        daMesh=daMesh->Next;
    }
    return gObj;
}

CKMesh *CKSceneSelection::IsOverSelectedMesh(int X,int Y)
{
    Vertex Clickhui,Clickhui2,Camhui,Camhui2;
    CKMesh *daMesh;
    //
//    MYPOINT sdot1,sdot2,sdot3,spt,v1tmp,v2tmp;
    int i,j;
//    float vr1,vr2,vr3;
	double orig[3],dir[3],vert0[3],vert1[3],vert2[3];

	CKPlan dap;
	dap.PlanOfView(m_Renderer,Active);

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
	Clickhui2=m_Renderer->GetIsoCoord(X,Y,Active,dap.pZ);

	orig[0]=Clickhui.x;
	orig[1]=Clickhui.y;
	orig[2]=Clickhui.z;

	dir[0]=Clickhui.x-Clickhui2.x;
	dir[1]=Clickhui.y-Clickhui2.y;
	dir[2]=Clickhui.z-Clickhui2.z;

	double t,u,v;

    daMesh=FirstMesh;
    while(daMesh!=NULL)
	{
        for (i=0;i<daMesh->nb2poly;i++)
        {
			for (j=0;j<daMesh->pl[i].nb2vert-2;j++)
			{

				vert0[0]=daMesh->pv[daMesh->pl[i].nbvert[0]].x;
				vert0[1]=daMesh->pv[daMesh->pl[i].nbvert[0]].y;
				vert0[2]=daMesh->pv[daMesh->pl[i].nbvert[0]].z;

				vert1[0]=daMesh->pv[daMesh->pl[i].nbvert[j+1]].x;
				vert1[1]=daMesh->pv[daMesh->pl[i].nbvert[j+1]].y;
				vert1[2]=daMesh->pv[daMesh->pl[i].nbvert[j+1]].z;

				vert2[0]=daMesh->pv[daMesh->pl[i].nbvert[j+2]].x;
				vert2[1]=daMesh->pv[daMesh->pl[i].nbvert[j+2]].y;
				vert2[2]=daMesh->pv[daMesh->pl[i].nbvert[j+2]].z;

				if (intersect_triangle(orig,dir,vert0,vert1,vert2,&t,&u,&v))
				{
					if (daMesh->Selected)
						return daMesh;
				}
			}
        }

        daMesh=daMesh->Next;
    }

    return NULL;
}

CKShape *CKSceneSelection::GetShape(int X,int Y)
{
	Vertex Clickhui;
	MYPOINT sdeb,sfin,spt;
    CKShape *daShape;
	CKSegment *daSeg;

	m_Precision=KOption2->Precision();

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	daShape=FirstShape;
	while (daShape!=NULL)	
	{
		daSeg=daShape->FirstSegment;
		while (daSeg!=NULL)
		{

			sdeb=Get2D(daSeg->Dot);
			sfin=Get2D(daSeg->Next->Dot);

			if ( (SegDistance(sdeb,sfin,spt)<m_Precision)|| ( (Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<m_Precision)|| (Pythagore((sfin.x-spt.x),(sfin.y-spt.y))<m_Precision)) )
			{
				return daShape;
			}


			daSeg=daSeg->Next;

            if ((daSeg->Next==NULL)||(daSeg==daShape->FirstSegment)) break;
			
		}
        daShape=daShape->Next;
    }


	return NULL;
}

CKBone *CKSceneSelection::RecurseGetBone(int X,int Y,Vertex Node,CKBone *daBone,MYPOINT daclick)
{
    Vertex Clickhui,Clickhui2;
	int daX,daY;
    MYPOINT sdeb,sfin,spt;
    CKBone *daBone2,*TmpBone;

	daX=X;
	daY=Y;
	spt.x=daclick.x;
	spt.y=daclick.y;

    sdeb=Get2D(Node);
    sfin=Get2D((*daBone->AbsPos));

    if (SegDistance(sdeb,sfin,spt)<m_Precision) return daBone;

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
        TmpBone=this->RecurseGetBone(daX,daY,(*daBone->AbsPos),daBone2,spt);
        if (TmpBone!=NULL) return TmpBone;
        daBone2=daBone2->Next;
    }

    return NULL;
}

CKBone *CKSceneSelection::GetBone(int X,int Y)
{
    Vertex Clickhui,Clickhui2;
    MYPOINT sdeb,sfin,spt;
    CKBone *daBone2,*TmpBone;
    CKSkeleton *daSkel;

	m_Precision=KOption2->Precision();

    daSkel=FirstSkel;
    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	while(daSkel!=NULL)
	{
		sdeb=Get2D(daSkel->RootPos);
		sfin=Get2D((*daSkel->bone->AbsPos));

    	if (SegDistance(sdeb,sfin,spt)<m_Precision) return daSkel->bone;
		daBone2=daSkel->bone->FirstBone;
		while(daBone2!=NULL)
		{
			TmpBone=RecurseGetBone(X,Y,(*daSkel->bone->AbsPos),daBone2,spt);
			if (TmpBone!=NULL) 
			{
				daTmpSkel=daSkel;
				return TmpBone;
			}
			daBone2=daBone2->Next;
		}

		daSkel=daSkel->Next;
	}
    return NULL;
}


CKSkeleton *CKSceneSelection::GetSkeleton(int X,int Y)
{
    Vertex Clickhui,Clickhui2;
    //
    MYPOINT sdeb,sfin,spt;

    CKBone *daBone2,*TmpBone;
    CKSkeleton *daSkel;
	double a;

	m_Precision=KOption2->Precision();

	//m_Renderer->DrawIt();

    daSkel=FirstSkel;
    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	while(daSkel!=NULL)
	{
		sdeb=Get2D(daSkel->RootPos);
		sfin=Get2D((*daSkel->bone->AbsPos));

		a=SegDistance(sdeb,sfin,spt);
		//a=Pythagore((sfin.x-spt.x),(sfin.y-spt.y));
		if (a<m_Precision)
		{
			return daSkel;
		}

		daBone2=daSkel->bone->FirstBone;
		while(daBone2!=NULL)
		{
			TmpBone=RecurseGetBone(X,Y,(*daSkel->bone->AbsPos),daBone2,spt);

			if (TmpBone!=NULL)
			{
				return daSkel;
			}
			daBone2=daBone2->Next;
		}

		daSkel=daSkel->Next;
	}
    return NULL;
}

CKEntity *CKSceneSelection::GetEntity(int X,int Y)
{
	for (CKEntity *daEnt=FirstEntity;daEnt!=NULL;daEnt=daEnt->Next)
	{
		//daEnt->ProcessMessage(KM_SETENTITY,(int)daEnt,0);
		if (daEnt->GetSingle(X,Y,m_Renderer))
			return daEnt;

	}
	return NULL;
}

CKPatch *CKSceneSelection::GetPatch(int X,int Y)
{
	
	return NULL;
}


Vertex *CKSceneSelection::GetShapeVert(int X,int Y)
{
    CKShape *daShape;
    CKSegment *daSeg;
    MYPOINT sdot,spt;
    Vertex Clickhui;

	m_Precision=KOption2->Precision();

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

    daShape=FirstShape;

    while(daShape!=NULL)
    {
        daSeg=daShape->FirstSegment;

        while(daSeg!=NULL)
        {
            sdot=Get2D(daSeg->Dot);

            if (Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<m_Precision)
            {
                return &daSeg->Dot;
            }

            daSeg=daSeg->Next;

            if ((daSeg==daShape->FirstSegment)||(daSeg==NULL)) break;
        }
        daShape=daShape->Next;
    }
	return NULL;
}

Vertex *CKSceneSelection::GetObjVert(int X,int Y,int &VertInd)
{
    Vertex Clickhui;
    MYPOINT sdot,spt;
    int i;

	m_Precision=KOption2->Precision();

    Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    spt=Get2D(Clickhui);

	for (CKMesh *daMesh=FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
    {
        for (i=0;i<daMesh->nb2vert;i++)
        {
            sdot=Get2D(daMesh->pv[i]);

            if (Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<m_Precision)
            {
				VertInd=i;
                return &daMesh->pv[i];
            }
        }
    }

    return NULL;
}

// -- Patch Vert --------------------------------------------------------------



CKPatch *CKSceneSelection::GetPatchByTriangle(int X,int Y,bool SelectIt)
{
	Vertex Clickhui,Clickhui2,Camhui,Camhui2;
    CKPatch *daPatch;
    int i,j;
	double orig[3],dir[3],vert0[3],vert1[3],vert2[3];

	CKPlan dap;
	dap.PlanOfView(m_Renderer,Active);

	if (ViewType[Active]==8)
	{
		Clickhui=m_Renderer->GetIsoCoord(X,Y,Active,Perspective[Active].Source+(Perspective[Active].Dest-Perspective[Active].Source)/100.0f);
		Clickhui2=m_Renderer->GetIsoCoord(X,Y,Active,Perspective[Active].Dest);
	}
	else
	{
		if (ViewType[Active]==9)
		{
			Clickhui=m_Renderer->GetIsoCoord(X,Y,Active,cam[Active]->Source+(cam[Active]->Dest-cam[Active]->Source)/100.0f);
			Clickhui2=m_Renderer->GetIsoCoord(X,Y,Active,cam[Active]->Dest);
		}
		else
		{
			Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
			Clickhui2=Clickhui+dap.pZ;//m_Renderer->GetIsoCoord(X,Y,Active,dap.pZ);
		}
	}
	
	orig[0]=Clickhui.x;
	orig[1]=Clickhui.y;
	orig[2]=Clickhui.z;

	dir[0]=Clickhui2.x-Clickhui.x;
	dir[1]=Clickhui2.y-Clickhui.y;
	dir[2]=Clickhui2.z-Clickhui.z;

	double t,u,v;
	double daDist=999999999,daDist2;
	CKPatch *gPatch=NULL;

	for (daPatch=FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
    {
        if ((!daPatch->Selected)||(!SelectIt))
        {
			for (int k=0;k<daPatch->nb2patch;k++)
			{
				int decal=k*((daPatch->Tesselate + 1)*(daPatch->Tesselate + 1));
				for (j=0;j<daPatch->Tesselate;j++)
				{
					for (i=2;i<((daPatch->Tesselate + 1)*2);i++)
					{
				
						vert0[0]=daPatch->pts[daPatch->strips[j][i-2]+decal].x;
						vert0[1]=daPatch->pts[daPatch->strips[j][i-2]+decal].y;
						vert0[2]=daPatch->pts[daPatch->strips[j][i-2]+decal].z;

						vert1[0]=daPatch->pts[daPatch->strips[j][i-1]+decal].x;
						vert1[1]=daPatch->pts[daPatch->strips[j][i-1]+decal].y;
						vert1[2]=daPatch->pts[daPatch->strips[j][i-1]+decal].z;

						vert2[0]=daPatch->pts[daPatch->strips[j][i]+decal].x;
						vert2[1]=daPatch->pts[daPatch->strips[j][i]+decal].y;
						vert2[2]=daPatch->pts[daPatch->strips[j][i]+decal].z;

						if (intersect_triangle(orig,dir,vert0,vert1,vert2,&t,&u,&v))
						{
							daDist2=t;
							if (((daDist2<daDist)&&(daDist2>0)) || (ViewType[Active]<8))
							{

								daDist=t;
								gPatch=daPatch;
								goto endit;
							}
						}
					}
				}
endit:;
			}
		}
	}
	return gPatch;
}

bool CKSceneSelection::SelectPatch(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
{
    int i,ii;
	bool daAddIt,daAddIt2,HasBeenSel=false;
	MYPOINT sdot;

	m_Precision=KOption2->Precision();

    Vertex Clickhui=m_Renderer->GetIsoCoord(X,Y,Active);
    MYPOINT spt=Get2D(Clickhui);

    Vertex Clickhui2=m_Renderer->GetIsoCoord(dx,dy,Active);
    MYPOINT spt2=Get2D(Clickhui2);

    double Length=Pythagore((spt2.x-spt.x),(spt2.y-spt.y));

	if ((TypeSel==SELECT_SINGLE)&&(WholeSelect==SELECT_WHOLE))
	{
		CKPatch *daPatch=GetPatchByTriangle(X,Y,false);
		if (daPatch!=NULL)
		{
			//AddIt=!daMesh->Selected;
			for (ii=0;ii<daPatch->nb2vert;ii++)
				PUTVERTEX((&daPatch->pv[ii]),daPatch,ii);

			daPatch->Selected=AddIt;
		}
		
	}
	else
	{
		for (CKPatch *daPatch=FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
		{
			daAddIt2=!Crossing;

			for (i=0;i<daPatch->nb2vert;i++)
			{
				sdot=Get2D((daPatch->pv[i]));
				
				// test it
				switch(TypeSel)
				{
					case SELECT_SINGLE:
						daAddIt=(Pythagore((sdot.x-spt.x),(sdot.y-spt.y))<m_Precision);
						break;
					case SELECT_QUAD:
						daAddIt=( ( (((sdot.x>=spt.x)&&(sdot.x<=spt2.x))||((sdot.x<=spt.x)&&(sdot.x>=spt2.x)))&&
							(((sdot.y>=spt.y)&&(sdot.y<=spt2.y))||((sdot.y<=spt.y)&&(sdot.y>=spt2.y))) ) );
						break;
					case SELECT_CIRCLE:
						daAddIt=(Pythagore((sdot.x-spt2.x),(sdot.y-spt2.y))<=Length);
						break;
					case SELECT_FENCE:
						daAddIt=daSh->IsVertInShape((daPatch->pv[i]),m_Renderer);
						break;
				}
				// Set it
				if (WholeSelect==SELECT_WHOLE)
				{
					if (Crossing)
					{
						if (daAddIt)
						{
							daAddIt2=true;
							i=daPatch->nb2vert;
						}
					}
					else
					{
						daAddIt2&=daAddIt;
					}
				}

				if (WholeSelect==SELECT_VERTEX)
					if (daAddIt)
					{
						PUTVERTEX((&daPatch->pv[i]),daPatch,i);
						if (TypeSel==SELECT_SINGLE) return HasBeenSel;
					}
			}
			if (WholeSelect==SELECT_WHOLE)
			{
				if (daAddIt2)
				{
					for (ii=0;ii<daPatch->nb2vert;ii++)
						PUTVERTEX((&daPatch->pv[ii]),daPatch,ii); 

					daPatch->Selected=AddIt;
//					daPatch->GeomIsDirty();
				}
			}
		}
	}
	RemoveBufUnselected();
	return HasBeenSel;
}

bool CKSceneSelection::SelectEntity(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
{
	//bool HasBeenSel;
	CKEntity *daEnt;

	CKSelectionInfos daSel;
	daSel.Crossing=Crossing;
	daSel.daSh=daSh;
	daSel.dx=dx;
	daSel.dy=dy;
	daSel.X=X;
	daSel.Y=Y;
	daSel.AddIt=AddIt;
	daSel.TypeSel=TypeSel;
	daSel.WholeSelect=WholeSelect;

	
    daSel.spt2=Get2D(m_Renderer->GetIsoCoord(X,Y,Active));
    daSel.spt=Get2D(m_Renderer->GetIsoCoord(dx,dy,Active));
	daSel.Length=Pythagore((daSel.spt2.x-daSel.spt.x),(daSel.spt2.y-daSel.spt.y));

	for (daEnt=FirstEntity;daEnt!=NULL;daEnt=daEnt->Next)
	{
//		daEnt->m_ProcessIt(KM_SETENTITY,(int)daEnt,0);
		daEnt->Select(daSel);
	}

	return false;
}

// -- Unselect -----------------------------------------------------------------

void CKSceneSelection::SingleMesh(CKMesh *daMesh,bool AddIt)
{
    int i;
	bool HasBeenSel;

	for (i=0;i<daMesh->nb2poly;i++)
	{
		daMesh->pl[i].Selected=AddIt;
	}
	for (i=0;i<daMesh->nb2vert;i++)
	{
		PUTVERTEX((&daMesh->pv[i]),daMesh,i);
	}
	daMesh->Selected=AddIt;
	RemoveBufUnselected();
}

void CKSceneSelection::SinglePatch(CKPatch *daPatch,bool AddIt)
{
	int i;
	bool HasBeenSel;

	for (i=0;i<daPatch->nb2vert;i++)
	{
		PUTVERTEX((&daPatch->pv[i]),daPatch,i);
	}
	daPatch->Selected=AddIt;
	RemoveBufUnselected();
}

void CKSceneSelection::SingleEntity(CKEntity *daEnt,bool AddIt)
{
//	daEnt->ProcessMessage(KM_SETENTITY,(int)daEnt,0);
	daEnt->SelectSingle(AddIt);
	daEnt->Selected=AddIt;
	RemoveBufUnselected();
}

void CKSceneSelection::SingleShape(CKShape *daShp,bool AddIt)
{
	bool HasBeenSel;

    CKSegment *daSeg;

	daShp->Selected=AddIt;
	daSeg=daShp->FirstSegment;
	while(daSeg!=NULL)
	{
		PUTVERTEX((&daSeg->Dot),daShp,daSeg);
		daSeg->Selected=AddIt;
		daSeg->Dot.Selected=AddIt;
		daSeg->SegSelected=AddIt;

		daSeg=daSeg->Next;

		if (daSeg==daShp->FirstSegment) break;
	}

	RemoveBufUnselected();
}

void CKSceneSelection::RecSingleSkeleton(CKSkeleton *daSkel,CKBone *daBone,bool AddIt)
{
    CKBone *daBone2;
	bool HasBeenSel;


	PUTVERTEX((&daBone->Pos),daSkel,daBone);
	daBone->Pos.Selected=AddIt;

    for (daBone2=daBone->FirstBone;daBone2!=NULL;daBone2=daBone2->Next)
        RecSingleSkeleton(daSkel,daBone2,AddIt);
}

void CKSceneSelection::SingleSkeleton(CKSkeleton *daSkel,bool AddIt)
{
	bool HasBeenSel;

	RecSingleSkeleton(daSkel,daSkel->bone,AddIt);
	PUTVERTEX((&daSkel->RootPos),daSkel,0);
		
	daSkel->Selected=AddIt;

	RemoveBufUnselected();
}
/*
void CKSceneSelection::SingleLight(CLight *daLight,bool AddIt)
{
	bool HasBeenSel;
	if (daLight->Type==0)
	{
		PUTVERTEX((&daLight->Source),daLight,0);
	}
	else
	{
		PUTVERTEX((&daLight->Source),daLight,0);
		PUTVERTEX((&daLight->Target),daLight,1);
	}
	daLight->Selected=AddIt;
	RemoveBufUnselected();
}
*/
void CKSceneSelection::SingleCamera(CKCamera *daCam,bool AddIt)
{
	bool HasBeenSel;

	PUTVERTEX((&daCam->Source),daCam,0);
	PUTVERTEX((&daCam->Dest),daCam,1);
	daCam->Selected=AddIt;
	RemoveBufUnselected();
}




void CKSceneSelection::UnSelectShape(bool daSelVal)
{
    CKShape *daShape;
    CKSegment *daSeg;

    for (daShape=FirstShape;daShape!=NULL;daShape=daShape->Next)
    {
        daShape->Selected=daSelVal;
        daSeg=daShape->FirstSegment;
        while(daSeg!=NULL)
        {
            daSeg->Selected=daSelVal;
            daSeg->Dot.Selected=daSelVal;
            daSeg->SegSelected=daSelVal;

            daSeg=daSeg->Next;

			if (daSeg==daShape->FirstSegment) break;
        }
		daShape->Tag=0;
    }
}

void CKSceneSelection::RecUnSelectSkeleton(CKBone *daBone,bool daSelVal)
{
    CKBone *daBone2;
    daBone->Selected=daSelVal;
	daBone->Pos.Selected=daSelVal;

    for (daBone2=daBone->FirstBone;daBone2!=NULL;daBone2=daBone2->Next)
    {
        RecUnSelectSkeleton(daBone2,daSelVal);
		daBone2->Tag=0;
    }
}

void CKSceneSelection::UnSelectSkeleton(bool daSelVal)
{
    CKSkeleton *daSkel;

    for (daSkel=FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
    {
        RecUnSelectSkeleton(daSkel->bone,daSelVal);

        daSkel->Selected=daSelVal;
		daSkel->RootPos.Selected=daSelVal;
        daSkel->Tag=0;
    }
}

void CKSceneSelection::UnSelectEntity(bool daSelVal)
{
    CKEntity *daEnts;

    for (daEnts=FirstEntity;daEnts!=NULL;daEnts=daEnts->Next)
    {
        daEnts->Selected=daSelVal;
		daEnts->Tag=0;
//		daEnts->ProcessMessage(KM_SETENTITY,(int)daEnts,0);
		daEnts->Unselect();
		
    }
}

void CKSceneSelection::UnSelectPatch(bool daSelVal)
{
	int i;

    for (CKPatch *daPatch=FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
	{
		for (i=0;i<daPatch->nb2vert;i++)
			daPatch->pv[i].Selected=daSelVal;
		daPatch->Tag=0;
    }
}


void CKSceneSelection::UnSelectCamera(bool daSelVal)
{
    CKCamera *daCam;

    for (daCam=FirstCam;daCam!=NULL;daCam=daCam->Next)
    {
        daCam->Selected=daSelVal;
		daCam->Tag=0;
    }
}


void CKSceneSelection::UnSelectUV(bool daSelVal)
{
    for (int i=0;i<m_CountUV;i++)
	{
        UVEdit[i].Selected=daSelVal;
    }
}

void CKSceneSelection::UnSelectMesh(bool daSelVal)
{
    CKMesh *daMesh;
    int i;

    for (daMesh=FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
    {
        for (i=0;i<daMesh->nb2poly;i++)
        {
            daMesh->pl[i].Selected=daSelVal;
        }

        for (i=0;i<daMesh->nb2vert;i++)
        {
            daMesh->pv[i].Selected=daSelVal;
        }

        daMesh->Selected=daSelVal;
        daMesh->Tag=0;
    }
}

void CKSceneSelection::UnSelectAll(bool daSelVal)
{
    UnSelectPatch(daSelVal);
	UnSelectEntity(daSelVal);
    UnSelectSkeleton(daSelVal);
    UnSelectShape(daSelVal);
    UnSelectMesh(daSelVal);
    UnSelectCamera(daSelVal);
}

//---------------------------------------------------------------------------

/*
Vertex  CKSceneSelection::GetIsoCoord(MYPOINT pt,int m_RendererInd)
{
	int realy;
    Vertex value;
    GLdouble ax,ay,az;
	double tmp1,tmp2,tmp3;

    int X=pt.x;
    int Y=pt.y;
    
	if (FullScreen)
	{
		realy=viewport[m_RendererInd][3]-(GLint)Y;
	}
	else 
	{
		switch(daViewMode)
		{
			
			case VIEW_MODE1x2a:
				if (ViewEnd[m_RendererInd].y==Height)
					realy=viewport[m_RendererInd][3]-(GLint)Y;
				else
					realy=viewport[m_RendererInd][3]-(GLint)Y+(Height/2);
				break;
			case VIEW_MODE1x3a:
				if (ViewEnd[m_RendererInd].y==Height)
					realy=viewport[m_RendererInd][3]-(GLint)Y;
				else
					realy=viewport[m_RendererInd][3]-(GLint)Y+(2*(Height/3));
				break;

			default:

				realy=viewport[m_RendererInd][3]-(GLint)Y+(Height/2);
				break;
		}


	}
    gluProject(0,0,0,mvmatrix[m_RendererInd], projmatrix[m_RendererInd], viewport[m_RendererInd], &ax, &ay, &az);
    gluUnProject((GLdouble)X,realy,(GLdouble)az,mvmatrix[m_RendererInd],projmatrix[m_RendererInd],viewport[m_RendererInd],&tmp1,&tmp2,&tmp3);
	
	value.x=tmp1;
	value.y=tmp2;
	value.z=tmp3;
//    temp=value;
    return value;

}
*/

void CKSceneSelection::SelectAll(void)
{
	CKMesh *daObj;
	CKCamera *daCam;
	CKShape *daShp;
	CKEntity *daEntity;
	CKPatch *daPatch;
	CKSkeleton *daSkel;

    for(daObj=FirstMesh;daObj!=NULL;daObj=daObj->Next)
		SingleMesh(daObj,true);

    for(daCam=FirstCam;daCam!=NULL;daCam=daCam->Next)
		SingleCamera(daCam,true);

    for(daEntity=FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
		SingleEntity(daEntity,true);

    for(daPatch=FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
		SinglePatch(daPatch,true);

    for(daShp=FirstShape;daShp!=NULL;daShp=daShp->Next)
		SingleShape(daShp,true);

    for(daSkel=FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
		SingleSkeleton(daSkel,true);

	UpdateSmthSel();
}

void CKSceneSelection::UpdateSmthSel(void)
{
	HookMinSel=GetMinBuf();
	HookMaxSel=GetMaxBuf();

	SomeThingSel=((FirstBufVert==NULL)?false:true);
	//if (HookMinSel!=HookMaxSel) SomeThingSel=true;

	UpdateMinMaxUVBuf();
}

void CKSceneSelection::SelectedToUVBuffer(int Layer)
{
}

void CKSceneSelection::UpdateMinMaxUVBuf(void)
{
}