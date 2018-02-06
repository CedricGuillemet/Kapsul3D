#include "stdafx.h"

extern HINSTANCE g_Inst;
extern CParameters m_Parameters;
extern CRollupCtrl *m_wndRollupCtrl;

CKPluginShape::CKPluginShape()
{
}

CKPluginShape::~CKPluginShape()
{
}


HWND CKPluginShape::Open(HWND Parent)
{
	SWITCH_RESOURCE;

	nbSegNGon=3;
    nbSegArc=3;
    nbSegStar=6;

    CreateSeg=false;
	CreateSeg2=false;
    TypeEdit=0;

	m_Parameters.m_Plugin=this;
    m_wndRollupCtrl=new CRollupCtrl();
    m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,4,164,362), CWnd::FromHandle(Parent), 2);	


    Diag=new CMainFrame;
    Diag->Create((unsigned int)IDD_MODDIAG,CWnd::FromHandle(Parent));
    
    
    return Diag->m_hWnd;
}

void CKPluginShape::Close()
{
	m_wndRollupCtrl->DestroyWindow();
    Diag->DestroyWindow();
//        DestroyWindow(ShapeDiag);
	SetPointer(0);
}

int CKPluginShape::ScenePluginType()
{
	return PLUGIN_PRIMITIVE;
}

void CKPluginShape::ReSize(int sx,int sy)
{
	m_wndRollupCtrl->MoveWindow(0,0,sx,sy,TRUE);
}

void CKPluginShape::LoseFocus()
{
}

CString CKPluginShape::GetName()
{
	return "Shape";
}

CString CKPluginShape::GetInfos()
{
	return "Shape";
}

bool CKPluginShape::CreatingStatus()
{
	return (CreateSeg||CreateSeg2);
}

void CKPluginShape::SetScene(CKScene *pScene)
{
	m_Scene=pScene;
}

PrimBmp* CKPluginShape::GetAllPrimitives()
{
	SWITCH_RESOURCE;

	daBmps.NbBmps=5;
	for (int i=0;i<daBmps.NbBmps;i++)
	{
		daBmps.Bmp[i].Detach();
	}
	daBmps.Bmp[0].LoadBitmap(MAKEINTRESOURCE(IDB_LINEIN));
	daBmps.PrimNb[0]=1;
	daBmps.Bmp[1].LoadBitmap(MAKEINTRESOURCE(IDB_NGONIN));
	daBmps.PrimNb[1]=2;
	daBmps.Bmp[2].LoadBitmap(MAKEINTRESOURCE(IDB_QUADIN));
	daBmps.PrimNb[2]=3;
	daBmps.Bmp[3].LoadBitmap(MAKEINTRESOURCE(IDB_ARCIN));
	daBmps.PrimNb[3]=4;
	daBmps.Bmp[4].LoadBitmap(MAKEINTRESOURCE(IDB_STARIN));
	daBmps.PrimNb[4]=5;
	
	return &daBmps;
}
void CKPluginShape::SetPrimitive(int PrimitiveNb)
{
	TypeEdit=PrimitiveNb;
	if (CreateSeg||CreateSeg2)
	{
		Vertex Null;
		RMouseUp(0,0,Vertex(0,0,0));
		DrawViews();
	}
	switch (TypeEdit)
	{
	case 2:
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_Parameters.SetParam(3,200,1,nbSegNGon);
		m_wndRollupCtrl->ExpandPage(0,TRUE);
		break;
	case 4:
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_Parameters.SetParam(3,200,1,nbSegArc);
		m_wndRollupCtrl->ExpandPage(0,TRUE);
		break;
	case 5:
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_Parameters.SetParam(6,200,2,nbSegNGon);
		m_wndRollupCtrl->ExpandPage(0,TRUE);
		break;
	default:
		m_wndRollupCtrl->EnablePage(0,FALSE);
		m_wndRollupCtrl->ExpandPage(0,FALSE);
		break;
	}
	Diag->Invalidate(true);
}

void CKPluginShape::DeleteStuff(void *pData,int DataType)
{
	if (((CKShape*)pData)==CurShapeEd)
	{
		CurShapeEd=NULL;
		CreateSeg=NULL;
	}
}


void CKPluginShape::RMouseDown(int X,int Y,Vertex &Pos)
{

}

void CKPluginShape::LMouseDown(int X,int Y,Vertex &Pos)
{
	CKUndoRedo *CurrentUndo;
	Crp.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);

    switch(TypeEdit)
    {
        // line

        case 1:
            Remem=Pos;
            dx=X;
            dy=Y;

			if (CreateSeg)
			{
				daOk=false;

				if ((TypeEd==1)||(TypeEd==2)||(TypeEd==5))
				{
					m_Scene->GetEndShapeVert((CKShape **)&CurShape,(CKSegment **)&CurSeg,CurSegEd,X,Y);
					if (CurSeg!=NULL)
					{
						if (CurShape==CurShapeEd)
						{
							//CurShapeEd->Close();
							CurShapeEd->NextSegment=CurShapeEd->FirstSegment;
							CreateSeg=false;
/*
							CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
							CurrentUndo->UndoType=UNDO_MODIFY;
							CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,CurShapeEd);
							*/
						}
						else
						{
							CKSegment *daSeg;
							daSeg=CurShape->NextSegment;

							if (TypeEd==1)
							{
								while (daSeg!=NULL)
								{
									CurShapeEd->AddSegment(daSeg->Dot);
									daSeg=daSeg->Prev;
								}

							}
							else
							{
								while (daSeg!=NULL)
								{
									CurShapeEd->InsertAtFirst(daSeg->Dot);
									daSeg=daSeg->Prev;
								}

							}
/*
							CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
							CurrentUndo->UndoType=UNDO_MODIFY;
							CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,CurShapeEd);
*/
							CurShape->DelAll();
							m_Scene->DelShape(CurShape);
						}

						daOk=true;
					}

					m_Scene->GetStartShapeVert((CKShape **)&CurShape,(CKSegment **)&CurSeg,CurSegEd,X,Y);
					if (CurSeg!=NULL)
					{
						if (CurShape==CurShapeEd)
						{
							//CurShapeEd->Close();
							CurSegEd->Prev->Next=CurShapeEd->FirstSegment;
							//CurShapeEd->DelSeg(CurSegEd->Prev->Next
							CKSegment *Delito=CurShapeEd->NextSegment;
							CurShapeEd->NextSegment=CurShapeEd->NextSegment->Prev;

							CreateSeg=false;
							delete Delito;
/*
							CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
							CurrentUndo->UndoType=UNDO_MODIFY;
							CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,CurShapeEd);
							*/
						}
						else
						{
							CKSegment *daSeg;
							daSeg=CurShape->FirstSegment;

							if (TypeEd==1)
							{
								while (daSeg!=NULL)
								{
									CurShapeEd->AddSegment(daSeg->Dot);
									daSeg=daSeg->Next;
								}

							}
							else
							{
								while (daSeg!=NULL)
								{
									CurShapeEd->InsertAtFirst(daSeg->Dot);
									daSeg=daSeg->Next;
								}

							}
							/*

							CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
							CurrentUndo->UndoType=UNDO_MODIFY;
							CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,CurShapeEd);
							*/

							CurShape->DelAll();
							m_Scene->DelShape(CurShape);
							
						}
						daOk=true;
					}
				}

				if (!daOk)
				{
					/*
					CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
					CurrentUndo->UndoType=UNDO_MODIFY;
					CurrentUndo->SetPrevEntry(0,PLUGIN_SHAPE,CurShapeEd);
					*/

					switch(TypeEd)
					{
					case 1:
						CurShapeEd->AddSegment(Pos);
						CurSegEd=CurShapeEd->NextSegment;
						break;
					case 2:
						CurShapeEd->InsertAtFirst(Pos);
						CurSegEd=CurShapeEd->FirstSegment;
						break;
					case 3:
						CurSegEd=CurShapeEd->InsertSegment(CurSegEd,Pos);
						TypeEd=4;
						break;
					case 4:
						CurSegEd=CurShapeEd->InsertSegment(CurSegEd,Pos);
						break;
					case 5:
						m_Scene->NextShape->AddSegment(Pos);
						CurSegEd=m_Scene->NextShape->NextSegment;
						break;
					}

					//CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,CurShapeEd);
				}
			}
			else
			{
				daOk=false;
				m_Scene->GetEndShapeVert((CKShape **)&CurShape,(CKSegment **)&CurSeg,(CKSegment *)NULL,X,Y);
				if (CurSeg!=NULL)
				{
					CurShape->AddSegment(Pos);
					CurShapeEd=CurShape;
					CurSegEd=CurShape->NextSegment;

					TypeEd=1;
					daOk=true;
				}

				m_Scene->GetStartShapeVert((CKShape **)&CurShape,(CKSegment **)&CurSeg,(CKSegment *)NULL,X,Y);
				if ((CurSeg!=NULL)&&(!daOk))
				{
					CurShape->InsertAtFirst(Pos);
					CurSegEd=CurShape->FirstSegment;
					CurShapeEd=CurShape;

					TypeEd=2;
					daOk=true;
				}


				
				m_Scene->GetShapeVert((CKShape **)&CurShape,(CKSegment **)&CurSeg,(CKSegment *)NULL,X,Y);
				if ((CurSeg!=NULL)&&(!daOk))
				{
					CurSegEd=CurSeg;
					CurShapeEd=CurShape;
					svg=CurSegEd->Dot;
					
					TypeEd=3;
					daOk=true;
				}
				
				m_Scene->GetShapeSeg((CKShape **)&CurShape,(CKSegment **)&CurSeg,(CKSegment *)NULL,X,Y);
				if ((CurSeg!=NULL)&&(!daOk))
				{
					CurShapeEd=CurShape;
					CurSegEd=CurShapeEd->InsertSegment(CurSeg,Pos);

					
					TypeEd=4;
					daOk=true;
				}

				CreateSeg=true;
				if (!daOk)
				{
					m_Scene->AddShape();
					m_Scene->NextShape->AddSegment(Pos);
					m_Scene->NextShape->AddSegment(Pos);
					CurSegEd=m_Scene->NextShape->NextSegment;
					CurShapeEd=m_Scene->NextShape;
					CreateSeg=1;

					TypeEd=5;
/*
					CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
					CurrentUndo->UndoType=UNDO_CREATE;
					CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,CurShapeEd);
					*/
				}
				else
				{
/*
					CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
					CurrentUndo->UndoType=UNDO_MODIFY;
					CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,CurShapeEd);
					*/
				}
			}
            break;

        // ngon

        case 2:
            

            if (CreateSeg)
            {
                CreateSeg=0;

				CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
				CurrentUndo->UndoType=UNDO_CREATE;
				CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,m_Scene->NextShape);

            }
            else
            {
				Remem=Pos;
                m_Scene->AddShape();
                CreateNGon(Remem,0,0,5);
				CurShapeEd=m_Scene->NextShape;
				dx=X;
				dy=Y;
                CreateSeg=1;
            }

            break;

        // quad

        case 3:
            Remem=Pos;

            if (CreateSeg)
            {
                CreateSeg=0;
				CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
				CurrentUndo->UndoType=UNDO_CREATE;
				CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,m_Scene->NextShape);
            }
            else
            {
                m_Scene->AddShape();
				CurShapeEd=m_Scene->NextShape;
                CreateQuad(Remem,0,0);
				dx=X;
				dy=Y;
                CreateSeg=1;
            }
            break;

        // arc

        case 4:

            if ((!CreateSeg)&&(!CreateSeg2))
            {
                m_Scene->AddShape();
				CurShapeEd=m_Scene->NextShape;
                CreateSeg=true;
                Remem=Pos;
                dx=X;
                dy=Y;

            }
            else
            {
                if ((CreateSeg)&&(!CreateSeg2))
                {
                    CreateSeg=false;
                    CreateSeg2=true;
                dx=X;
                dy=Y;                    
                }
                else
                {
                    if ((!CreateSeg)&&(CreateSeg2))
                    {
                        CreateSeg=false;
                        CreateSeg2=false;

						CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
						CurrentUndo->UndoType=UNDO_CREATE;
						CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,m_Scene->NextShape);

                    }
                }
            }

            break;

        // star

        case 5:
            if ((!CreateSeg)&&(!CreateSeg2))
            {
                m_Scene->AddShape();
				CurShapeEd=m_Scene->NextShape;
                CreateSeg=true;
                Remem=Pos;
                dx=X;
                dy=Y;


            }
            else
            {
                if ((CreateSeg)&&(!CreateSeg2))
                {
                    CreateSeg=false;
                    CreateSeg2=true;
					dx=X;
					dy=Y;
                }
                else
                {
                    if ((!CreateSeg)&&(CreateSeg2))
                    {
                        CreateSeg=false;
                        CreateSeg2=false;

						CurrentUndo=m_Scene->AddUndo("Shape.dll",1);
						CurrentUndo->UndoType=UNDO_CREATE;
						CurrentUndo->SetAfterEntry(0,PLUGIN_SHAPE,m_Scene->NextShape);
                    }
                }
            }

            break;

        // to surface

        case 6:
            break;

        // connect

        case 7:
            break;


    }

}
void CKPluginShape::LMouseUp(int X,int Y,Vertex &Pos)
{

}

void CKPluginShape::RMouseUp(int X,int Y,Vertex &Pos)
{
	CreateSeg=false;
    CreateSeg2=false;

    if (TypeEdit==1)
    {
		if (TypeEd==3)
		{
			CurSegEd->Dot=svg;
		}
		else
		{
		
			if (CurSegEd->Prev!=NULL)
				CurSegEd->Prev->Next=CurSegEd->Next;

			if (CurSegEd->Next!=NULL)
				CurSegEd->Next->Prev=CurSegEd->Prev;

			if (CurShapeEd->FirstSegment==CurSegEd)
				CurShapeEd->FirstSegment=CurSegEd->Next;

			if (CurShapeEd->NextSegment==CurSegEd)
				CurShapeEd->NextSegment=CurSegEd->Prev;

			if (CurShapeEd->FirstSegment->Next==NULL)
				m_Scene->DelShape(CurShapeEd);
		}

    }
    else
    {
		m_Scene->DelShape(CurShapeEd);
		CurShapeEd=NULL;
    }
}


void CKPluginShape::MouseMove(int X,int Y,Vertex &Pos)
{
	if (CreateSeg||CreateSeg2)
	{
		X=X;
		Y=Y;
	}

    switch(TypeEdit)
    {
        // Line

        case 1:
            if (CreateSeg)
            {
                //m_Scene->NextShape->SetSegment(&Pos);
				CurSegEd->Dot=Pos;
				daOk=false;

				if ((TypeEd==1)||(TypeEd==2)||(TypeEd==5))
				{
					m_Scene->GetEndShapeVert((CKShape **)&CurShape2,(CKSegment **)&CurSeg2,CurSegEd,X,Y);
					if (CurSeg2!=NULL)
					{
						if (CurShape2==CurShapeEd)
						{
							LStatus("Click to close shape");
							SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_CLOSE)));
							
						}
						else
						{
							LStatus("Click to collapse with this shape");
							SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_COLAPPSE)));
						}
						daOk=true;
					}

					m_Scene->GetStartShapeVert((CKShape **)&CurShape2,(CKSegment **)&CurSeg2,CurSegEd,X,Y);
					if (CurSeg2!=NULL)
					{
                        
						if (CurShape2==CurShapeEd)
						{
							LStatus("Click to close shape");
							SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_CLOSE)));
						}
						else
						{
							LStatus("Click to collapse with this shape");
							SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_COLAPPSE)));
						}
                        
						daOk=true;
					}

					if (!daOk)
					{
						LStatus("Click to add segment");
						SetPointer(0);

					}
					DrawViews();
				}
            }
			else
			{
				daOk=false;
				m_Scene->GetEndShapeVert((CKShape **)&CurShape2,(CKSegment **)&CurSeg2,(CKSegment *)NULL,X,Y);
				if (CurSeg2!=NULL)
				{
					LStatus("Click to append segment");
					SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_APPEND)));
					daOk=true;
				}

				m_Scene->GetStartShapeVert((CKShape **)&CurShape2,(CKSegment **)&CurSeg2,(CKSegment *)NULL,X,Y);
				if ((CurSeg2!=NULL)&&(!daOk))
				{
					LStatus("Click to append segment");
					SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_APPEND)));
					daOk=true;
				}
				
				m_Scene->GetShapeVert((CKShape **)&CurShape2,(CKSegment **)&CurSeg2,(CKSegment *)NULL,X,Y);
				if ((CurSeg2!=NULL)&&(!daOk))
				{
					LStatus("Click to modify dot");
					SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_MOVEDOT)));
					daOk=true;
				}
				
				m_Scene->GetShapeSeg((CKShape **)&CurShape2,(CKSegment **)&CurSeg2,(CKSegment *)NULL,X,Y);
				if ((CurSeg2!=NULL)&&(!daOk))
				{
					LStatus("Click to insert segment");
					SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_INSERT)));
					daOk=true;
				}

				if (!daOk)
				{
					LStatus("Click to build new shape");
					SetPointer(0);
				}

				
			}
            break;

        // NGon

        case 2:
            if (CreateSeg)
            {
				lng1=sqrt((dx-X)*(dx-X)+(dy-Y)*(dy-Y));
				ang1=-ng(dx,dy,X,Y);
                CreateNGon(Remem,lng1,ang1,nbSegNGon);
				DrawViews();
            }

            break;

        // Quad

        case 3:
            if (CreateSeg)
            {
                CreateQuad(Remem,X-dx,Y-dy);
				DrawViews();
            }
            break;

        // Arc

        case 4:

            if ((CreateSeg)&&(!CreateSeg2))
            {
                Radius=sqrt((dx-X)*(dx-X)+(dy-Y)*(dy-Y));
                nga=-ng(dx,dy,X,Y);

                m_Scene->NextShape->DelAll();
                m_Scene->NextShape->AddSegment(Remem);//Crp.GetAbs(dx,dy,0)+Remem);
                m_Scene->NextShape->AddSegment(Pos);//Crp.GetAbs(X,Y,0)+Remem);
				DrawViews();

            }
            else
            {
                if ((!CreateSeg)&&(CreateSeg2))
                {
					ngb=-ng(dx,dy,X,Y);
                    CreateArc(Remem,Radius,nga,ngb,nbSegArc);
	                RStatus("Arc Rad1: %5.2f ng1: %5.2f ng2: %5.2f",Radius,(nga*180)/PI,-(ng(dx,dy,X,Y)*180.0f)/PI);
					DrawViews();
                }
            }

            break;

        // Star

        case 5:
            if ((CreateSeg)&&(!CreateSeg2))
            {
                Radius=sqrt((dx-X)*(dx-X)+(dy-Y)*(dy-Y));
                nga=-ng(dx,dy,X,Y);

                CreateStar(Remem,Radius,Radius,nga,nbSegStar);
				DrawViews();

            }
            else
            {
                if ((!CreateSeg)&&(CreateSeg2))
                {
					lng2=sqrt((dx-X)*(dx-X)+(dy-Y)*(dy-Y));
                    CreateStar(Remem,Radius,lng2,nga,nbSegStar);
					DrawViews();
                }
            }

            break;
        case 6:
            break;
        case 7:
            break;
    }
}

void CKPluginShape::CreateQuad(Vertex Center,double X,double Y)
{

    m_Scene->NextShape->DelAll();
    m_Scene->NextShape->AddSegment(Crp.GetAbs(0,0,0)+Center);
	if (GetSnap()) m_Scene->NextShape->NextSegment->Dot.Snap(m_Scene->SnapVal);
    m_Scene->NextShape->AddSegment(Crp.GetAbs(X,0,0)+Center);
	if (GetSnap()) m_Scene->NextShape->NextSegment->Dot.Snap(m_Scene->SnapVal);
    m_Scene->NextShape->AddSegment(Crp.GetAbs(X,Y,0)+Center);
	if (GetSnap()) m_Scene->NextShape->NextSegment->Dot.Snap(m_Scene->SnapVal);
    m_Scene->NextShape->AddSegment(Crp.GetAbs(0,Y,0)+Center);
	if (GetSnap()) m_Scene->NextShape->NextSegment->Dot.Snap(m_Scene->SnapVal);
    m_Scene->NextShape->Close();
}

void CKPluginShape::CreateNGon(Vertex Center,double radius,double ngb,int nb2Seg)
{
    int i;

    m_Scene->NextShape->DelAll();
    for (i=0;i<nb2Seg;i++)
    {
        m_Scene->NextShape->AddSegment(Crp.GetAbs((cos( (ngb-(2.0f*PI/((double)nb2Seg))*((double)i)) )*radius),
            (sin( (ngb-(2.0f*PI/((double)nb2Seg))*((double)i)) )*radius),0)+Center);

    }
    m_Scene->NextShape->Close();

}

void CKPluginShape::CreateStar(Vertex Center,double radius1,double radius2,double ngb,int nb2Seg)
{
    double radius;
    int i;

    m_Scene->NextShape->DelAll();

    for (i=0;i<nb2Seg;i++)
    {
        if (i&1) radius=radius1;
        else radius=radius2;

        m_Scene->NextShape->AddSegment(Crp.GetAbs((cos( (ngb-(2.0f*PI/((double)nb2Seg))*((double)i)) )*radius),
            (sin( (ngb-(2.0f*PI/((double)nb2Seg))*((double)i)) )*radius),0)+Center);
    }
    m_Scene->NextShape->Close();


}

void CKPluginShape::CreateArc(Vertex Center,double radius,double ngb,double ng2,int nb2Seg)
{
    int i;

    m_Scene->NextShape->DelAll();

    for (i=0;i<nb2Seg;i++)
    {
        m_Scene->NextShape->AddSegment(Crp.GetAbs((cos((ngb+( (ng2/((double)(nb2Seg-1))) *(double)i)))*radius),
            (sin((ngb+((ng2/((double)(nb2Seg-1)))*(double)i)))*radius),0)+Center);
    }
    //m_Scene->NextShape->Close();

}

void CKPluginShape::UpdateShape(void)
{
	if (CurShapeEd!=NULL)
	{
		switch (TypeEdit)
		{
			case 5:
				CreateStar(Remem,Radius,lng2,nga,nbSegStar);
				break;
			case 4:
				CreateArc(Remem,Radius,nga,ngb,nbSegArc);
				break;
			case 2:
				CreateNGon(Remem,lng1,ang1,nbSegNGon);
				break;
		}
		DrawViews();
	}
}
