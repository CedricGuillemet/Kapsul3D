#include "stdafx.h"

#include "resource.h"
#include "ModDiag.h"
#include "UVMapper.h"
// call in C only, Mfc in plugins are hard to implement.


CRollupCtrl *m_wndRollupCtrl;

CKUVMapper::CKUVMapper()
{
}
CKUVMapper::~CKUVMapper()
{
}

HWND CKUVMapper::Open(HWND Parent)
{
	SWITCH_RESOURCE;

	ApplyMapMesh=NULL;
	ApplyMapMesh2=NULL;
	daMesh=NULL;
	m_Scene=NULL;
	TypeMap=0;


	bool IsMoving=false;



    m_wndRollupCtrl=new CRollupCtrl();
    m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,4,164,362), CWnd::FromHandle(Parent), 2);	

    m_Diag=new CPathModDiag;
    m_Diag->Create((unsigned int)IDD_MODDIAG,CWnd::FromHandle(Parent));
    
    
    

	
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
	return m_Diag->m_hWnd;
}
void CKUVMapper::Close()
{
	m_wndRollupCtrl->DestroyWindow();
    m_Diag->DestroyWindow();
}
int CKUVMapper::ScenePluginType()
{
	return PLUGIN_OPERATION;
}
void CKUVMapper::ReSize(int sx,int sy)
{
	m_wndRollupCtrl->MoveWindow(0,0,164,sy,TRUE);
}
void CKUVMapper::LoseFocus()
{
}


CString CKUVMapper::GetName()
{
	return "UV Mapper";
}
CString CKUVMapper::GetInfos()
{
	return "UV Mapper";
}

bool CKUVMapper::CreatingStatus()
{
	return IsMoving;
}
void CKUVMapper::SetScene(CKScene *pScene)
{
	m_Scene=pScene;
	DrawViews();
	m_Scene->SelectedToUVBuffer(0);
}

DWORD CKUVMapper::OwnerDraw(CKRenderer *pRenderer,int ViewNb)
{
{
	/*
	m_Scene->ViewType[2]=4;
	m_Scene->EnableUVSelectionUpdate(true);
	*/
	//UVHand.CalculateHandles=true;
	/*
	switch(TypeMap)
	{
	case 1:
		pRenderer->DrawMesh(&CubeMap,0,WichOne);
		UVHand.DrawHandles(m_Scene,WichOne,CubeMap.Min,CubeMap.Max);
		break;
	case 2:
		pRenderer->DrawMesh(&CylMap,0,WichOne);
		UVHand.DrawHandles(m_Scene,WichOne,CylMap.Min,CylMap.Max);
		break;
	case 3:
		pRenderer->DrawMesh(&PlanarMap,0,WichOne);
		UVHand.DrawHandles(m_Scene,WichOne,PlanarMap.Min,PlanarMap.Max);
		break;
	case 4:
		pRenderer->DrawMesh(&SphereMap,0,WichOne);
		UVHand.DrawHandles(m_Scene,WichOne,SphereMap.Min,SphereMap.Max);
		break;
	}
	*/

/*
	if (WichOne==2)
	{
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);
		m_Scene->FirstMesh->Tex1->Bind();

		glPushMatrix();

		dap.PlanOfView(GDrawScene,WichOne);

		Vertex daa,dab;

		dap.pX.Normalize();
		dap.pY.Normalize();
		dap.pZ.Normalize();


		daa=dap.pX+dap.pY;

		glScalef(64,64,64);
		
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(0,0,0);
		glTexCoord2f(0,1);
		glVertex3f(dap.pY.x,dap.pY.y,dap.pY.z);
		glTexCoord2f(1,1);
		glVertex3f(daa.x,daa.y,daa.z);
		glTexCoord2f(1,0);
		glVertex3f(dap.pX.x,dap.pX.y,dap.pX.z);
		glEnd();

		glEnable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);

		// draw the mapping triangles

		daMesh=m_Scene->FirstMesh;

		int i,j;
		Vertex tmpd;

		glDisable(GL_DEPTH_TEST);
		glPointSize(4);
		glColor4f(1,1,1,1);

		for (i=0;i<daMesh->nb2poly;i++)
		{

			glBegin(GL_LINE_LOOP);
			
			for (j=0;j<daMesh->pl[i].nb2vert;j++)
			{
				tmpd=dap.pX*daMesh->puv[0][daMesh->pl[i].Tex[0][j]].u;
				tmpd+=(dap.pY*daMesh->puv[0][daMesh->pl[i].Tex[0][j]].v);

				glVertex3f(tmpd.x,tmpd.y,tmpd.z);
			}


			glEnd();
				
		}
		glPointSize(1);

		glEnable(GL_DEPTH_TEST);

		glPopMatrix();


		return PLUGIN_NONE;
	}
	*/
	return PLUGIN_ALL;
}

}

int CKUVMapper::GetCursor(int X,int Y)
{
	return UVHand.GetHandle(m_Scene,X,Y);
}

CBitmap *CKUVMapper::GetBitmap()
{
	SWITCH_RESOURCE;

	m_Dib.Detach();
	m_Dib.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP));
	return &m_Dib;
}
CBitmap *CKUVMapper::GetHotBitmap()
{
	SWITCH_RESOURCE;

	m_Dib2.Detach();
	m_Dib2.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP1));
	return &m_Dib2;
}

void CKUVMapper::LMouseDown(int X,int Y,Vertex &Pos)
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
				
			//UVHand.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
			//m_Scene->GetNbSelectedMeshs();
			//m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
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
		//SetCapture(hWndEdit);

		//sprintf(temp,"Angle 0 degs");
		//mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
		
			UVHand.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
		//}
		IsMoving=true;
		//m_Scene->GetNbSelectedMeshs();
		//m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
		}
		break;
	case EDIT_SCALEBUF:
		{
			
				//UVHand.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work

			dap.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);
			IsMoving=true;

			//sprintf(temp,"X: 100%% Y: 100%% Z: 100%%");
			//mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		

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
			/*
			m_ScaleOrigin.x=m_Scene->m_Renderer->ta2DHandles[NewHand-1].x;
			m_ScaleOrigin.y=m_Scene->Height-m_Scene->m_Renderer->ta2DHandles[NewHand-1].y;
			*/
			//m_Scene->GetNbSelectedMeshs();
			//m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
		}
		break;
	}
}
void CKUVMapper::LMouseUp(int X,int Y,Vertex &Pos)
{
	if ( (TypeEd==EDIT_SCALEBUF)||
		(TypeEd==EDIT_ROTATEBUF)||
		(TypeEd==EDIT_MOVEBUF) )
	{

		//m_Scene->UpdateUVBuf();
		//m_Scene->UpdateBuf();
		UVHand.CalculateHandles=true;

		//sprintf(temp,"");
		//mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		

		//ReleaseCapture();
		IsMoving=false;
/*
		tmpdoc = (CDeskDoc *) GetDocument();
		tmpdoc->SetModifiedFlag(TRUE);
		*/
		TypeEd=0;
		// update min Max
		m_Scene->UpdateSmthSel();
		m_Scene->UpdateMinMaxUVBuf();

//		FunctionID=SvgFunctionID;
		//m_Scene->GetNbSelectedMeshs();
		m_Scene->SetSelectedToAfterUndoNoADD();
	}

}
void CKUVMapper::MouseMove(int X,int Y,Vertex &Pos)
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

					/*
						sprintf(temp,"X: %7.2f Y: %7.2f Z: %7.2f",(hui-huitemp).x,(hui-huitemp).y,(hui-huitemp).z);
						mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
						*/

					/*
						m_Scene->TranslateBuf(dap,hui-huitemp);
						m_Scene->UpdateTaged(PLUGIN_ALL);
						*/
					for (i=0;i<ApplyMapMesh->nb2vert;i++)
					{
						ApplyMapMesh->pv[i]=ApplyMapMesh2->pv[i]+(hui-huitemp);

					}

					ApplyMapMesh->Min=ApplyMapMesh2->Min+(hui-huitemp);
					ApplyMapMesh->Max=ApplyMapMesh2->Max+(hui-huitemp);

					//OldTrans=(hui-huitemp);

						// don't know where to put it
						
						//UVHand.TranslateHandles(rtr,m_Scene->Active);

					DrawViews();
				}
//                IsMoving=true;
                break;
            case EDIT_ROTATEBUF:
				double tempng;
                m_Scene->m_Renderer->Project((Vertex*)&hui,(Vertex*)&Getng2,m_Scene->Active);

				tempng=-int(((ng(Getng.x,Getng.y,Getng2.x,Getng2.y)-ngl)*180)/PI);
                dap.MatrixRotateNormale(-((tempng*PI)/180));

				/*
				sprintf(temp,"Angle %d degs",(int)tempng);
				mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
				*/

			
				/*
				m_Scene->RotateBuf(dap,(ApplyMapMesh2->Min+(ApplyMapMesh2->Max-ApplyMapMesh2->Min)/2.0f));
				m_Scene->UpdateTaged(PLUGIN_ALL);
				*/
				Center=ApplyMapMesh2->Min+((ApplyMapMesh2->Max-ApplyMapMesh2->Min)/2);

				for (i=0;i<ApplyMapMesh->nb2vert;i++)
				{
					//ApplyMapMesh->pv[i]=ApplyMapMesh2->pv[i]+(hui-huitemp);

					ApplyMapMesh->pv[i]=(dap.Rotate(ApplyMapMesh2->pv[i]-Center)+Center);

				}
				/*
				ApplyMapMesh->Min=(dap.Rotate(ApplyMapMesh2->Min-Center)+Center);
				ApplyMapMesh->Max=(dap.Rotate(ApplyMapMesh2->Max-Center)+Center);
				*/
				
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


				//if (m_Scene->ViewType[m_Scene->Active]!=4)
				/*
				if (GetSnap())
				{
					MYPOINT nlng;
					nlng.x=(tlng.x*ScaleVal.x);
					float temp=floor(nlng.x/SnapVal.x)*SnapVal.x;
					float v1=fmod(tlng.x,SnapVal.x);
					if (v1<(SnapVal.x/2))
						nlng.x=temp;
					else
						nlng.x=temp+SnapVal.x;

					nlng.y=(tlng.y*ScaleVal.y);
					temp=floor(nlng.y/SnapVal.y)*SnapVal.y;
					v1=fmod(tlng.y,SnapVal.y);
					if (v1<(SnapVal.y/2))
						nlng.y=temp;
					else
						nlng.y=temp+SnapVal.y;

					ScaleVal.x=nlng.x/tlng.x;
					ScaleVal.y=nlng.y/tlng.y;
					
				}
				*/

				/*
				if (Button&MK_CONTROL) 
				{
					ScaleVal.y=ScaleVal.x;
					if (Button&MK_SHIFT)
					{
						ScaleVal.z=ScaleVal.x;
					}
				}
				*/

				//sprintf(temp,"X: %5.2f%% Y: %5.2f%% Z: %d%%",(ScaleVal.x*100.0f),(ScaleVal.y*100.0f),(int)(ScaleVal.z*100));
				/*
				sprintf(temp,"X: %5.2f  Y: %5.2f",(tlng.x*ScaleVal.x),(tlng.y*ScaleVal.y));
				mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
				*/

				dap.ScaleMatrix();


				//Center=ApplyMapMesh2->Min+((ApplyMapMesh2->Max-ApplyMapMesh2->Min)/2);

				for (i=0;i<ApplyMapMesh->nb2vert;i++)
				{
					//ApplyMapMesh->pv[i]=ApplyMapMesh2->pv[i]+(hui-huitemp);

					ApplyMapMesh->pv[i]=(dap.Scale(ApplyMapMesh2->pv[i]-m_Scene->Axis,ScaleVal)+m_Scene->Axis);
					

				}
				ApplyMapMesh->Min=(dap.Scale(ApplyMapMesh2->Min-m_Scene->Axis,ScaleVal)+m_Scene->Axis);
				ApplyMapMesh->Max=(dap.Scale(ApplyMapMesh2->Max-m_Scene->Axis,ScaleVal)+m_Scene->Axis);
				/*
				ApplyMapMesh->Min=(dap.Rotate(ApplyMapMesh2->Min-Center)+Center);
				ApplyMapMesh->Max=(dap.Rotate(ApplyMapMesh2->Max-Center)+Center);
				*/
				

				/*
				m_Scene->ScaleBuf(dap,m_Scene->Axis,ScaleVal);
				m_Scene->UpdateTaged(PLUGIN_ALL);
				*/
				{
					MYPOINT scvr;
					scvr.x=ScaleVal.x;
					scvr.y=ScaleVal.y;


				UVHand.ScaleHandles(NewHand-1,scvr,m_Scene->Active);
				}
				
				DrawViews();

				break;
		}
	}

}


