// KUVEdit.cpp: implementation of the CKUVEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "KUVEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKUVEdit::CKUVEdit()
{

}

CKUVEdit::~CKUVEdit()
{

}
// mapping stuff
void CKUVEdit::Init()
{
	bool snapval=GetSnap(); // set snap to false
	SetSnap(false);
	CKGenericMesh mobj;
	mobj.VecX=Vertex(1,0,0);
	mobj.VecY=Vertex(0,1,0);
	mobj.VecZ=Vertex(0,0,1);
	double sx=128,sy=128;

	mobj.CreateCube(&CubeMap,Vertex(0,0,0),128,128,128);
	mobj.CreateCyl(&CylMap,Vertex(0,0,0),sx,sy,1,16,0);
	sx=10;
	sy=10;
	mobj.CreateGrid(&PlanarMap,Vertex(10,10,10),sx,sy,1,1);
	mobj.CreateSphere(&SphereMap,Vertex(0,0,0),128,8,0);
	SetSnap(snapval);

	CubeMap.UpdateMesh();
	CylMap.UpdateMesh();
	PlanarMap.UpdateMesh();
	SphereMap.UpdateMesh();
	CubeMap2.IsCopyOf(&CubeMap);
	CylMap2.IsCopyOf(&CylMap);
	PlanarMap2.IsCopyOf(&PlanarMap);
	SphereMap2.IsCopyOf(&SphereMap);
	CubeMap2.UpdateMesh();
	CylMap2.UpdateMesh();
	PlanarMap2.UpdateMesh();
	SphereMap2.UpdateMesh();
}

DWORD CKUVEdit::OwnerDraw(CKRenderer *pRenderer,int ViewNb)
{

	switch(TypeMap)
	{
	case 1:
		pRenderer->DrawMesh(&CubeMap,0,ViewNb);
		pRenderer->DrawHandles(&UVHand,ViewNb,CubeMap.Min,CubeMap.Max);
		break;
	case 2:
		pRenderer->DrawMesh(&CylMap,0,ViewNb);
		pRenderer->DrawHandles(&UVHand,ViewNb,CylMap.Min,CylMap.Max);
		break;
	case 3:
		pRenderer->DrawMesh(&PlanarMap,0,ViewNb);
		pRenderer->DrawHandles(&UVHand,ViewNb,PlanarMap.Min,PlanarMap.Max);
		break;
	case 4:
		pRenderer->DrawMesh(&SphereMap,0,ViewNb);
		pRenderer->DrawHandles(&UVHand,ViewNb,SphereMap.Min,SphereMap.Max);
		break;
	}
	return PLUGIN_ALL;
}

void CKUVEdit::LMouseDown(int X,int Y,Vertex &Pos)
{
	dx=X;
	dy=Y;

	int HandleNb=0;
	if (ApplyMapMesh!=NULL)
	{
		UVHand.CalcHandles(m_Scene,m_Scene->Active,ApplyMapMesh->Min,ApplyMapMesh->Max);
		HandleNb=UVHand.GetHandle(m_Scene,X,Y);
	}

	// Scale/Move/Rotate Switch
	switch (HandleNb)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		TypeEd=EDIT_SCALEBUF;
		break;
	case 9:
		TypeEd=EDIT_ROTATEBUF;
		break;
	case 10:
		TypeEd=EDIT_MOVEBUF;
		break;
	}

	switch (TypeEd)
	{
	case EDIT_MOVEBUF:
		
			IsMoving=true;
			dap.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);

			OldTrans=Vertex(0,0,0);
		
		break;
	case EDIT_ROTATEBUF:
		{
			MYPOINT center;
			huitemp=m_Scene->m_Renderer->GetIsoCoord(X,Y,m_Scene->Active);
		m_Scene->m_Renderer->Project((Vertex*)&m_Scene->Axis,(Vertex*)&Getng,m_Scene->Active);
		m_Scene->m_Renderer->Project((Vertex*)&huitemp,(Vertex*)&Getng2,m_Scene->Active);


		UVHand.Get2DCenter(m_Scene->Active,center);
		Getng.x=center.x;
		Getng.y=center.y;

		ngl=ng(Getng.x,Getng.y,Getng2.x,Getng2.y);
		dap.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);

		UVHand.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work

		IsMoving=true;

		}
		break;
	case EDIT_SCALEBUF:
		{

			dap.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);
			IsMoving=true;

			switch(HandleNb)
			{
			case 1:
				NewHand=3;
				m_ScaleMask=Vertex(1,-1,0);
				break;
			case 2:
				NewHand=4;
				m_ScaleMask=Vertex(1,1,0);
				break;
			case 3:
				NewHand=1;
				m_ScaleMask=Vertex(-1,1,0);
				break;
			case 4:
				NewHand=2;
				m_ScaleMask=Vertex(-1,-1,0);
				break;
			case 5:
				NewHand=6;
				m_ScaleMask=Vertex(0,-1,0);
				break;
			case 6:
				NewHand=5;
				m_ScaleMask=Vertex(0,1,0);
				break;
			case 7:
				NewHand=8;
				m_ScaleMask=Vertex(1,0,0);
				break;
			case 8:
				NewHand=7;
				m_ScaleMask=Vertex(-1,0,0);
				break;
			}


			m_ScaleSvgSize.x=fabs(UVHand.ta2DHandles[0].x-UVHand.ta2DHandles[2].x);
			m_ScaleSvgSize.y=fabs(UVHand.ta2DHandles[0].y-UVHand.ta2DHandles[2].y);
			m_Scene->Axis=ApplyMapMesh->Min+((ApplyMapMesh->Max-ApplyMapMesh->Min)/2.0f);
		}
		break;
	}
}
void CKUVEdit::LMouseUp(int X,int Y,Vertex &Pos)
{
	if ( (TypeEd==EDIT_SCALEBUF)||
		(TypeEd==EDIT_ROTATEBUF)||
		(TypeEd==EDIT_MOVEBUF) )
	{

		UVHand.CalculateHandles=true;

		IsMoving=false;

		TypeEd=0;
		// update min Max
		m_Scene->UpdateSmthSel();
		m_Scene->UpdateMinMaxUVBuf();

		m_Scene->SetSelectedToAfterUndoNoADD();
	}

}
void CKUVEdit::MouseMove(int X,int Y,Vertex &Pos)
{
	int i;
	Vertex Center;

	if (IsMoving)
	{
		MYPOINT tlng;
		Vertex ScaleVal;
		hui=m_Scene->m_Renderer->GetIsoCoord(X,Y,m_Scene->Active);

		switch(TypeEd)
		{
			case EDIT_MOVEBUF:
				{
					Vertex datr,datr2;
					m_Scene->m_Renderer->Project((Vertex*)&huitemp,(Vertex*)&datr,m_Scene->Active);
					m_Scene->m_Renderer->Project((Vertex*)&hui,(Vertex*)&datr2,m_Scene->Active);
					MYPOINT hugh;

					hugh.x=(hui-huitemp).x/64.0f;
					hugh.y=-(hui-huitemp).y/64.0f;

					MYPOINT rtr;

					rtr.x=datr2.x-datr.x;
					rtr.y=datr2.y-datr.y;

					for (i=0;i<ApplyMapMesh->nb2vert;i++)
					{
						ApplyMapMesh->pv[i]=ApplyMapMesh2->pv[i]+(hui-huitemp);

					}

					ApplyMapMesh->Min=ApplyMapMesh2->Min+(hui-huitemp);
					ApplyMapMesh->Max=ApplyMapMesh2->Max+(hui-huitemp);

					DrawViews();
				}

                break;
            case EDIT_ROTATEBUF:
				double tempng;
                m_Scene->m_Renderer->Project((Vertex*)&hui,(Vertex*)&Getng2,m_Scene->Active);

				tempng=-int(((ng(Getng.x,Getng.y,Getng2.x,Getng2.y)-ngl)*180)/PI);
                dap.MatrixRotateNormale(-((tempng*PI)/180));

				Center=ApplyMapMesh2->Min+((ApplyMapMesh2->Max-ApplyMapMesh2->Min)/2);

				for (i=0;i<ApplyMapMesh->nb2vert;i++)
				{
					ApplyMapMesh->pv[i]=(dap.Rotate(ApplyMapMesh2->pv[i]-Center)+Center);

				}
				
				UVHand.RotateHandles((float)tempng*2,m_Scene->Active);
			
                DrawViews();
				
                break;

			case EDIT_SCALEBUF:
				
				if ((fabs(dap.pX.x)>0.0001)&&(fabs(dap.pY.y)>0.0001))
				{
					tlng.x=fabs(ApplyMapMesh2->Max.x-ApplyMapMesh2->Min.x);
					tlng.y=fabs(ApplyMapMesh2->Max.y-ApplyMapMesh2->Min.y);
				}
				else
				if ((fabs(dap.pX.y)>0.0001)&&(fabs(dap.pY.z)>0.0001))
				{
					tlng.x=fabs(ApplyMapMesh2->Max.y-ApplyMapMesh2->Min.y);
					tlng.y=fabs(ApplyMapMesh2->Max.z-ApplyMapMesh2->Min.z);
				}
				if ((fabs(dap.pX.x)>0.0001)&&(fabs(dap.pY.z)>0.0001))
				{
					tlng.x=fabs(ApplyMapMesh2->Max.x-ApplyMapMesh2->Min.x);
					tlng.y=fabs(ApplyMapMesh2->Max.z-ApplyMapMesh2->Min.z);
				}

				if (m_ScaleMask.x!=0)
				{
					if (fabs(m_ScaleSvgSize.x)<0.0001) 
					{
						ScaleVal.x=1.0f;
					}
					else
					{
						ScaleVal.x=int((( (m_ScaleMask.x*((double)dx-(double)X)) +m_ScaleSvgSize.x)/(float)m_ScaleSvgSize.x)*100.0f);
						ScaleVal.x/=100;
					}
				}
				else
					ScaleVal.x=1.0f;

				if (m_ScaleMask.y!=0)
				{
					if (fabs(m_ScaleSvgSize.y)<0.0001) 
					{
						ScaleVal.y=1.0f;
					}
					else
					{
						ScaleVal.y=int((( (m_ScaleMask.y*((double)dy-(double)Y)) +m_ScaleSvgSize.y)/(float)m_ScaleSvgSize.y)*100.0f);
						ScaleVal.y/=100;
					}
				}
				else
					ScaleVal.y=1.0f;



				ScaleVal.z=1;

				dap.ScaleMatrix();


				//Center=ApplyMapMesh2->Min+((ApplyMapMesh2->Max-ApplyMapMesh2->Min)/2);

				for (i=0;i<ApplyMapMesh->nb2vert;i++)
				{
					//ApplyMapMesh->pv[i]=ApplyMapMesh2->pv[i]+(hui-huitemp);

					ApplyMapMesh->pv[i]=(dap.Scale(ApplyMapMesh2->pv[i]-m_Scene->Axis,ScaleVal)+m_Scene->Axis);
					

				}
				ApplyMapMesh->Min=(dap.Scale(ApplyMapMesh2->Min-m_Scene->Axis,ScaleVal)+m_Scene->Axis);
				ApplyMapMesh->Max=(dap.Scale(ApplyMapMesh2->Max-m_Scene->Axis,ScaleVal)+m_Scene->Axis);


				MYPOINT scvr;
				scvr.x=ScaleVal.x;
				scvr.y=ScaleVal.y;

				UVHand.ScaleHandles(NewHand-1,scvr,m_Scene->Active);
				
				DrawViews();

				break;
		}
	}
}

