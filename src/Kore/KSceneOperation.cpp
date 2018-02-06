// KSceneOperation.cpp: implementation of the CKSceneOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KSceneOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKSceneOperation::CKSceneOperation()
{

}

CKSceneOperation::~CKSceneOperation()
{

}

bool CKSceneOperation::BendBuf(double ngb,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center)
{
    VertBuf *daBufVert;
    double ngr;
    MYPOINT tmp;
	CKPlan *Dap;

	Dap=new CKPlan();
	Dap->PlanOfView(m_Renderer,Active);

	ngb-=PI;
	ngb=fmod(ngb,PI);

	double dif;

/*
    MYPOINT tmpCenter=View->Hand3D.ta2DHandles[Corner];//Get2D(Axis);
    MYPOINT tmpMax=View->Hand3D.ta2DHandles[2];//Get2D(HookMaxSel);
	MYPOINT tmpMin=View->Hand3D.ta2DHandles[4];//Get2D(HookMinSel);
*/
    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        tmp=Get2D(daBufVert->AncVal);

		if (Sens==1)
		{
			if ((Max.x-Center.x)!=0) dif=(Max.x-Center.x);
			else dif=(Min.x-Center.x);

			ngr=((tmp.x-Center.x)/dif)*ngb;
		}
		else
		{
			if ((Max.y-Center.y)!=0) dif=(Max.y-Center.y);
			else dif=(Min.y-Center.y);

			ngr=((tmp.y-Center.y)/dif)*ngb;
		}

        Dap->MatrixRotateNormale(ngr);

        daBufVert->IsNow( (Dap->Rotate(daBufVert->AncVal-Axis)+Axis) );
        daBufVert=daBufVert->Next;
    }
	/*
	for (int i=0;i<48;i++)
	{
        tmp=Get2D(Dap->CurDrawScene->Hand3D.Hanks[i]);

		if (Sens==1)
			ngr=((tmp.x-tmpCenter.x)/(tmpMax.x-tmpCenter.x))*ngb;
		else
			ngr=((tmp.y-tmpCenter.y)/(tmpMax.y-tmpCenter.y))*ngb;

        Dap->MatrixRotateNormale(ngr);

		Dap->CurDrawScene->Hand3D.DrawHanks[i]=(Dap->Rotate((Dap->CurDrawScene->Hand3D.Hanks[i]-Axis))+Axis);
	}
*/
    delete Dap;
    return true;
}

bool CKSceneOperation::SquizBuf(double Facteur,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center)
{
    MYPOINT tmp;
    Vertex destval;
    Vertex tmpr;
    VertBuf *daBufVert;
	CKPlan *Dap;


	Dap=new CKPlan();
	Dap->PlanOfView(m_Renderer,Active);
    Dap->ScaleMatrix(false);

	MYPOINT dif;
	dif.x=Max.x-Min.x;
	dif.y=Max.y-Min.y;


    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
		tmpr.x=1;
		tmpr.y=1;
		tmpr.z=1;


		tmp=Get2D(daBufVert->AncVal);

		if (Sens==0)
		{
			tmpr.x=(((tmp.y-Center.y)/dif.y)*Facteur)+1.0f;
		}
		else
		{
			tmpr.y=(((tmp.x-Center.x)/dif.x)*Facteur)+1.0f;
		}

        daBufVert->IsNow( Dap->Scale((daBufVert->AncVal-Axis),tmpr)+Axis );
        daBufVert=daBufVert->Next;
    }

    delete Dap;

    return true;
}

bool CKSceneOperation::TaperBuf(double Facteur,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center)
{
    MYPOINT tmp;
    Vertex destval;
    Vertex tmpr;
    VertBuf *daBufVert;
	CKPlan *Dap;


	Dap=new CKPlan();
	Dap->PlanOfView(m_Renderer,Active);

    daBufVert=FirstBufVert;

    while(daBufVert!=NULL)
    {
        tmp=Get2D(daBufVert->AncVal);


        tmpr.x=0;
        tmpr.y=0;
        tmpr.z=0;

        // right deform
		if (Sens==1)
			tmpr.x=((tmp.y-Center.y)/(Max.y-Min.y))*Facteur;
		else
			tmpr.y=((tmp.x-Center.x)/(Max.x-Min.x))*Facteur;

		Vertex ptx=Dap->pX*tmpr.x;
		Vertex pty=Dap->pY*tmpr.y;


        daBufVert->IsNow( daBufVert->AncVal+ptx+pty );
        daBufVert=daBufVert->Next;
    }
/*
	

*/
    delete Dap;

    return true;
}


void CKSceneOperation::SelectedToUVBuffer(int Layer)
{
	int CountUV=0;
	int i,j;
	CKMesh *daMesh;

	// Count;
	for (daMesh=FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		if (daMesh->Selected)
			CountUV+=daMesh->nbTexCoords[Layer];
		else
		{
			for (i=0;i<daMesh->nb2poly;i++)
			{
				if (daMesh->pl[i].Selected)
					CountUV+=daMesh->pl[i].nb2vert;
			}
		}
	}

	if (UVEdit!=NULL) free(UVEdit);

	UVEdit=(UVCoordsEdit*)malloc(CountUV*sizeof(UVCoordsEdit));

	m_CountUV=CountUV;

	CountUV=0;
	
	// allocate
	for (daMesh=FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		if (daMesh->Selected)
		{
			for (i=0;i<daMesh->nbTexCoords[Layer];i++)
			{
				UVEdit[CountUV].daMesh=daMesh;
				UVEdit[CountUV].PuvInd=i;
				UVEdit[CountUV].Selected=false;
				UVEdit[CountUV].u=daMesh->puv[Layer][i].u;
				UVEdit[CountUV].v=daMesh->puv[Layer][i].v;
				CountUV++;
			}
		}
		else
		{
			for (i=0;i<daMesh->nb2poly;i++)
			{
				if (daMesh->pl[i].Selected)
				{
					for (j=0;j<daMesh->pl[i].nb2vert;j++)
					{
						UVEdit[CountUV].daMesh=daMesh;
						UVEdit[CountUV].PuvInd=daMesh->pl[i].Tex[Layer][j];
						UVEdit[CountUV].Selected=false;
						UVEdit[CountUV].u=daMesh->puv[Layer][UVEdit[CountUV].PuvInd].u;
						UVEdit[CountUV].v=daMesh->puv[Layer][UVEdit[CountUV].PuvInd].v;
						CountUV++;
					}
				}
			}
		}
	}


}

void CKSceneOperation::EnableUVSelectionUpdate(bool Enable)
{
	m_UVSelUpdate=Enable;
}

void CKSceneOperation::TranslateUVBuf(CKPlan *dap,MYPOINT Trans)
{
	int i;

	for (i=0;i<m_CountUV;i++)
	{
		if (UVEdit[i].Selected)
		{
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u=UVEdit[i].u+Trans.x;
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v=UVEdit[i].v+Trans.y;
		}
	}
/*
	for (i=0;i<48;i++)
		dap->CurDrawScene->HandUV.DrawHanks[i]=dap->CurDrawScene->HandUV.Hanks[i]+Vertex(Trans.x,Trans.y,0);
*/		
}

void CKSceneOperation::UpdateUVBuf(void)
{
	int i;

	for (i=0;i<m_CountUV;i++)
	{
		if (UVEdit[i].Selected)
		{
			UVEdit[i].u=UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u;
			UVEdit[i].v=UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v;
		}
	}
}

void CKSceneOperation::RotateUVBuf(CKPlan *dap,MYPOINT Center,float angle)
{
    int i;

	for (i=0;i<m_CountUV;i++)
	{
		if (UVEdit[i].Selected)
		{
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u=RotX((UVEdit[i].u-Center.x),(UVEdit[i].v-Center.y),angle);
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u+=Center.x;
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v=RotY((UVEdit[i].u-Center.x),(UVEdit[i].v-Center.y),angle);//+Center.y;
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v+=Center.y;
		}
	}
/*
	Vertex ct;
	ct.x=Center.x;
	ct.y=Center.y;
	ct.z=0;

	for (i=0;i<48;i++)
		dap->CurDrawScene->HandUV.DrawHanks[i]=(dap->Rotate(dap->CurDrawScene->HandUV.Hanks[i]-ct)+ct);
*/
}

void CKSceneOperation::ScaleUVBuf(CKPlan *dap,MYPOINT Center,MYPOINT ScaleVal)
{
	int i;

	for (i=0;i<m_CountUV;i++)
	{
		if (UVEdit[i].Selected)
		{
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u=((UVEdit[i].u-Center.x)*ScaleVal.x)+Center.x;
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v=((UVEdit[i].v-Center.y)*ScaleVal.y)+Center.y;
		}
	}

	/*
	Vertex ct,scv;
	ct.x=Center.x;
	ct.y=Center.y;
	ct.z=0;

	scv.x=ScaleVal.x;
	scv.y=ScaleVal.y;
	scv.z=0;

	for (i=0;i<48;i++)
		dap->CurDrawScene->HandUV.DrawHanks[i]=(dap->Scale(dap->CurDrawScene->HandUV.Hanks[i]-ct,scv)+ct);
*/
}

void CKSceneOperation::UpdateMinMaxUVBuf(void)
{
	int i;

	UVMinSel.u=999999;
	UVMinSel.v=999999;
	UVMaxSel.u=-999999;
	UVMaxSel.v=-999999;

	for (i=0;i<m_CountUV;i++)
	{
		if (UVEdit[i].Selected)
		{
			if (UVEdit[i].u<UVMinSel.u) UVMinSel.u=UVEdit[i].u;
			if (UVEdit[i].v<UVMinSel.v) UVMinSel.v=UVEdit[i].v;

			if (UVEdit[i].u>UVMaxSel.u) UVMaxSel.u=UVEdit[i].u;
			if (UVEdit[i].v>UVMaxSel.v) UVMaxSel.v=UVEdit[i].v;
		}
	}
}



bool CKSceneOperation::BendUVBuf(double ngb,int Sens,MYPOINT center)
{
    double ngr;
    MYPOINT tmp;
	int i;

	ngb-=PI;
	ngb=fmod(ngb,PI);

	double dif;

    MYPOINT tmpMax;
	tmpMax.x=UVMaxSel.u;
	tmpMax.y=UVMaxSel.v;

	MYPOINT tmpMin;
	tmpMin.x=UVMinSel.u;
	tmpMin.y=UVMinSel.v;

	for (i=0;i<m_CountUV;i++)
	{
		if (UVEdit[i].Selected)
		{

			if (Sens==1)
			{
				if ((tmpMax.x-center.x)!=0) dif=(tmpMax.x-center.x);
				else dif=(tmpMin.x-center.x);

				ngr=((tmp.x-center.x)/dif)*ngb;
			}
			else
			{
				if ((tmpMax.y-center.y)!=0) dif=(tmpMax.y-center.y);
				else dif=(tmpMin.y-center.y);

				ngr=((tmp.y-center.y)/dif)*ngb;
			}

			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u=RotX((UVEdit[i].u-center.x),(UVEdit[i].v-center.y),ngr);
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u+=center.x;
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v=RotY((UVEdit[i].u-center.x),(UVEdit[i].v-center.y),ngr);//+Center.y;
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v+=center.y;
        }
    }
	/*
	for (int i=0;i<48;i++)
	{
        tmp=cSel->Get2D(Dap->CurDrawScene->Hand3D.Hanks[i]);

		if (Sens==1)
			ngr=((tmp.x-tmpCenter.x)/(tmpMax.x-tmpCenter.x))*ngb;
		else
			ngr=((tmp.y-tmpCenter.y)/(tmpMax.y-tmpCenter.y))*ngb;

        Dap->MatrixRotateNormale(ngr);

		Dap->CurDrawScene->Hand3D.DrawHanks[i]=(Dap->Rotate((Dap->CurDrawScene->Hand3D.Hanks[i]-Axis))+Axis);
	}

    delete Dap;
	*/
    return true;
}

bool CKSceneOperation::SquizUVBuf(double Facteur,int Sens,MYPOINT center)
{
    //VertexBuf *vb;
    MYPOINT tmp;
    Vertex destval;
    MYPOINT tmpr;
	int i;


    MYPOINT tmpMax;
	tmpMax.x=UVMaxSel.u;
	tmpMax.y=UVMaxSel.v;

	MYPOINT tmpMin;
	tmpMin.x=UVMinSel.u;
	tmpMin.y=UVMinSel.v;



	MYPOINT dif;
	dif.x=tmpMax.x-tmpMin.x;
	dif.y=tmpMax.y-tmpMin.y;


	for (i=0;i<m_CountUV;i++)
	{
		if (UVEdit[i].Selected)
		{
			tmpr.x=1;
			tmpr.y=1;
			
			if (Sens==0)
			{
				tmpr.x=(((tmp.y-center.y)/dif.y)*Facteur)+1.0f;
			}
			else
			{
				tmpr.y=(((tmp.x-center.x)/dif.x)*Facteur)+1.0f;
			}

			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u=((UVEdit[i].u-center.x)*tmpr.x)+center.x;
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v=((UVEdit[i].v-center.y)*tmpr.y)+center.y;
		}
    }
/*
	for (int i=0;i<48;i++)
	{
        tmpr.x=1;
        tmpr.y=1;
        tmpr.z=1;

		tmp=cSel->Get2D(Dap->CurDrawScene->Hand3D.Hanks[i]);

		if (Sens==0)
		{
			tmpr.x=(((tmp.y-tmpCenter.y)/dif.y)*Facteur)+1.0f;
		}
		else
		{
			tmpr.y=(((tmp.x-tmpCenter.x)/dif.x)*Facteur)+1.0f;
		}

		Dap->CurDrawScene->Hand3D.DrawHanks[i]=(Dap->Scale((Dap->CurDrawScene->Hand3D.Hanks[i]-Axis),tmpr)+Axis);
	}
*/

    return true;
}

bool CKSceneOperation::TaperUVBuf(double Facteur,int Sens,MYPOINT center)
{
    MYPOINT tmp;
    Vertex destval;
    MYPOINT tmpr;


    MYPOINT tmpMax;
	tmpMax.x=UVMaxSel.u;
	tmpMax.y=UVMaxSel.v;

	MYPOINT tmpMin;
	tmpMin.x=UVMinSel.u;
	tmpMin.y=UVMinSel.v;

	int i;

	for (i=0;i<m_CountUV;i++)
	{
		if (UVEdit[i].Selected)
		{

			tmpr.x=0;
			tmpr.y=0;

			// right deform
			if (Sens==1)
				tmpr.x=((tmp.y-center.y)/(tmpMax.y-tmpMin.y))*Facteur;
			else
				tmpr.y=((tmp.x-center.x)/(tmpMax.x-tmpMin.x))*Facteur;

			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].u=UVEdit[i].u+tmpr.x;
			UVEdit[i].daMesh->puv[0][UVEdit[i].PuvInd].v=UVEdit[i].v+tmpr.y;
		}
    }
/*
	for (int i=0;i<48;i++)
	{
        tmp=cSel->Get2D(Dap->CurDrawScene->Hand3D.Hanks[i]);


        tmpr.x=0;
        tmpr.y=0;
        tmpr.z=0;

        // right deform
		if (Sens==1)
			tmpr.x=((tmp.y-tmpCenter.y)/(tmpMax.y-tmpMin.y))*Facteur;
		else
			tmpr.y=((tmp.x-tmpCenter.x)/(tmpMax.x-tmpMin.x))*Facteur;

		Vertex ptx=Dap->pX*tmpr.x;
		Vertex pty=Dap->pY*tmpr.y;

		Dap->CurDrawScene->Hand3D.DrawHanks[i]=Dap->CurDrawScene->Hand3D.Hanks[i]+ptx+pty;
	}


    delete Dap;
*/
    return true;
}



void CKSceneOperation::DeleteAll(void)
{
    CKShape *daShp,*daShp2;
    CKMesh *daObj,*daObj2;
    CKPatch *daPatch,*daPatch2;
	CKEntity *daEntity,*daEntity2;
    CKSkeleton *daSkel,*daSkel2;
    CKCamera *daCam,*daCam2;

    daShp=FirstShape;
    while(daShp!=NULL)
    {
        daShp2=daShp->Next;
        DelShape(daShp);
        daShp=daShp2;
    }

    daObj=FirstMesh;
    while(daObj!=NULL)
    {
        daObj2=daObj->Next;
        DelMesh(daObj);
        daObj=daObj2;
    }

    daPatch=FirstPatch;
    while(daPatch!=NULL)
    {
        daPatch2=daPatch->Next;
        DelPatch(daPatch);
        daPatch=daPatch2;
    }

    daEntity=FirstEntity;
    while(daEntity!=NULL)
    {
        daEntity2=daEntity->Next;
        DelEntity(daEntity);
        daEntity=daEntity2;
    }

    daSkel=FirstSkel;
    while(daSkel!=NULL)
    {
        daSkel2=daSkel->Next;
        DelSkeleton(daSkel);
        daSkel=daSkel2;
    }

    daCam=FirstCam;
    while(daCam!=NULL)
    {
        daCam2=daCam->Next;
        DelCamera(daCam);
        daCam=daCam2;
    }

	UpdateHierarchie((CKScene*)this);

    DeleteBufVert();
}

void CKSceneOperation::DeleteSelected(void)
{
    CKShape *daShp,*daShp2;
    CKMesh *daObj,*daObj2;
    CKPatch *daPatch,*daPatch2;
	CKEntity *daEntity,*daEntity2;
    CKSkeleton *daSkel,*daSkel2;
    CKCamera *daCam,*daCam2;
    bool HasDelSeg=false;

    
    daShp=FirstShape;
    while(daShp!=NULL)
    {
        daShp2=daShp->Next;
        if (daShp->Selected) 
        {
            DelShape(daShp);
            HasDelSeg=true;
        }


        daShp=daShp2;
    }

    if (!HasDelSeg)
    {
        if (!DelShapeSeg())
        {
            DelShapeVert();
        }

    }


    daObj=FirstMesh;
    while(daObj!=NULL)
    {
        daObj2=daObj->Next;
        if (daObj->Selected) 
            DelMesh(daObj);
        else
        {
            if (!daObj->DelSelectedFaces())
            {
                daObj->DelSelectedVertex();
            }
        }
        daObj=daObj2;
    }

    daEntity=FirstEntity;
    while(daEntity!=NULL)
    {
        daEntity2=daEntity->Next;
        if (daEntity->Selected) DelEntity(daEntity);
        daEntity=daEntity2;
    }

    daPatch=FirstPatch;
    while(daPatch!=NULL)
    {
        daPatch2=daPatch->Next;
        if (daPatch->Selected) DelPatch(daPatch);
        daPatch=daPatch2;
    }

    daSkel=FirstSkel;
    while(daSkel!=NULL)
    {
        daSkel2=daSkel->Next;
        if (daSkel->Selected) 
            DelSkeleton(daSkel);
        else
            daSkel->DelSelectedBones(daSkel->bone);

        daSkel=daSkel2;
    }

    daCam=FirstCam;
    while(daCam!=NULL)
    {
        daCam2=daCam->Next;
        if ((daCam->Source.Selected)||(daCam->Dest.Selected))
		{
			if ((daCam!=cam[0])&&(daCam!=cam[1])&&(daCam!=cam[2])&&(daCam!=cam[3]))
				DelCamera(daCam);
		}
        daCam=daCam2;
    }
    

	UpdateHierarchie((CKScene*)this);

    //DeleteBufVert();
	VertBuf *daBufVert,*daBufVert2;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert2=daBufVert->Next;
        delete daBufVert;
        daBufVert=NULL;
        daBufVert=daBufVert2;
    }
    FirstBufVert=NULL;
    NextBufVert=NULL;

	// erase undo vector
	UndoRedoEntriesCount.erase(UndoRedoEntriesCount.begin(),UndoRedoEntriesCount.end());

	UpdateSmthSel();
}
