#include "stdafx.h"



CRollupCtrl *m_wndRollupCtrl;

void BeginCutter(int X,int Y,Vertex *Pos);
void ValidateCutter(int X,int Y,Vertex *Pos);
bool SymBuf(Vertex Center,Vertex remem,Vertex Pos);




CKPluginModifier::CKPluginModifier()
{
}
CKPluginModifier::~CKPluginModifier()
{
}

HWND CKPluginModifier::Open(HWND Parent)
{
	SWITCH_RESOURCE;

    m_wndRollupCtrl=new CRollupCtrl();
    m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,34,164,362), CWnd::FromHandle(Parent), 2);	


    ModDiag=new CModDiag;
    ModDiag->Create((unsigned int)IDD_MODDIAG,CWnd::FromHandle(Parent));
    RECT rc;

	ModDiag->GetClientRect(&rc);
	m_TailleOrg=rc.bottom;

	LastAction=-1;

	m_Modify.m_Plugin=this;
	m_Explode.m_Plugin=this;
	m_Extrud.m_Plugin=this;
	m_Lathe.m_Plugin=this;
	m_Path.m_Plugin=this;
	m_Spherize.m_Plugin=this;
	m_UVParam.m_Plugin=this;
	m_Normals.m_Plugin=this;
	m_SubDiv.m_Plugin=this;
	m_Fractalize.m_Plugin=this;
	m_Divide.m_Plugin=this;
	m_CalcTex.m_Plugin=this;
	m_Mapper.m_Plugin=this;
	m_Lightmap.m_Plugin=this;

	CreateSeg=0;

	m_Mesh2DelStart=NULL;
	//m_Mesh2DelEnd=NULL;
	CurLatheMesh=NULL;

	m_Seed=(unsigned)time( NULL );

	SShape=NULL;
	SPath=NULL;
	LoftMesh=NULL;

	memset(AllModif,0,sizeof(ModifVert)*100);

	m_KUVEdit.Init();

    return ModDiag->m_hWnd;
}

int CKPluginModifier::GetCursor(int X,int Y)
{
	return m_KUVEdit.UVHand.GetHandle(m_Scene,X,Y);
}

void CKPluginModifier::Close()
{
	m_wndRollupCtrl->DestroyWindow();
    ModDiag->DestroyWindow();
	CurLatheShp=NULL;
	CurLatheMesh=NULL;
	ApplyModifs();
}

int CKPluginModifier::ScenePluginType()
{
	return PLUGIN_OPERATION;
}

void CKPluginModifier::ReSize(int sx,int sy)
{
	m_wndRollupCtrl->MoveWindow(0,m_TailleOrg,164,sy-m_TailleOrg,TRUE);
}
void CKPluginModifier::LoseFocus()
{
	ApplyModifs();
	ModDiag->UnSetPlugin();
}

CString CKPluginModifier::GetName()
{
	return "Modifier";
}
CString CKPluginModifier::GetInfos()
{
	return "Modifier";
}

bool CKPluginModifier::CreatingStatus()
{
	return (CreateSeg!=0);
}
void CKPluginModifier::SetScene(CKScene *pScene)
{
	m_Scene=pScene;
	m_KUVEdit.m_Scene=pScene;
}

void CKPluginModifier::UpdateSelection()
{

}


DWORD CKPluginModifier::OwnerDraw(CKRenderer *pRenderer,int ViewNb)
{
	if ((TypeEdit==11)&&(CreateSeg==1) )
	{
		/*
		glColor4f(1,0,1,1);
		glLineStipple(4,0xAAAA);
		glEnable(GL_LINE_STIPPLE);

		glBegin(GL_LINES);
		glVertex3f(Remem.x,Remem.y,Remem.z);
		glVertex3f(Remem2.x,Remem2.y,Remem2.z);
		glEnd();

		glDisable(GL_LINE_STIPPLE);
		*/
	}
	m_KUVEdit.OwnerDraw(m_Scene->m_Renderer,ViewNb);

	return PLUGIN_ALL;
}

CBitmap *CKPluginModifier::GetBitmap()
{
	SWITCH_RESOURCE;

	m_Dib.Detach();
	m_Dib.LoadBitmap(IDB_BITMAPHOT);
    return &m_Dib;
}

void CKPluginModifier::DeleteStuff(void *pData,int DataType)
{



}

void CKPluginModifier::UpdateStuff(void *pObject,int PlugType)
{



}

void CKPluginModifier::LMouseDown(int X,int Y,Vertex &Pos)
{
	CKShape *tmpShp;
	

	Crp.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);

	switch (LastAction)
	{
		case ACTION_MAPPINGEDIT:
			m_KUVEdit.LMouseDown(X,Y,Pos);
			break;
		case ACTION_CUTTER:
			if (CreateSeg==0)
			{
				BeginCutter(X,Y,&Pos);
			}
			else
			{
				ValidateCutter(X,Y,&Pos);
			}
			break;
		case ACTION_LATHE:
			tmpShp=m_Scene->GetShape(X,Y);
			if (tmpShp!=NULL)
			{
				if (CurLatheShp!=tmpShp)
				{
					CurLatheShp=tmpShp;
					if (CurLatheShp!=NULL)
					{
						m_Lathe.m_ShapeName.SetWindowText(CurLatheShp->Name);
						m_Lathe.m_CurrentUndo=m_Scene->AddUndo("Modifier",1);
						m_Lathe.m_CurrentUndo->UndoType=UNDO_CREATE;

						CurLatheMesh=m_Scene->AddMesh();

						CurLatheMesh->Lathing(CurLatheShp,m_Lathe.m_SpinEdit.GetPos(),m_UVParam.m_SpinU.GetPos(),m_UVParam.m_SpinV.GetPos());

						DrawViews();
					}
				}
			}
			break;
		case ACTION_SELECTSHAPE:
			tmpShp=m_Scene->GetShape(X,Y);
			if (tmpShp!=NULL)
			{
				if (tmpShp->IsClosed())
				{
					SShape=tmpShp;
					ModifAv=0;
					trX=0;
					trY=0;
					m_Path.m_ShapeName.SetWindowText(SShape->Name);

					//SetWindowText(GetDlgItem(PathDiagHWND,IDC_SHAPENAME),SShape->Name);
					if (SPath!=NULL)
					{
						GenerateObject();
						DrawViews();
					}
				}
				else
					MessageBox(NULL,"Shape to extrud must be closed.","Bad Shape.",MB_OK);
			}
			break;
		case ACTION_SELECTPATH:
			tmpShp=m_Scene->GetShape(X,Y);
			if (tmpShp!=NULL)
			{
				SPath=tmpShp;
				ModifAv=0;
				trX=0;
				trY=0;

				m_Path.m_PathName.SetWindowText(SPath->Name);

				//SetWindowText(GetDlgItem(PathDiagHWND,IDC_PATHNAME),SPath->Name);
				if (SShape!=NULL)
				{
					
					GenerateObject();
					DrawViews();
				}
			}
			break;

		// Move Dot
			/*
		case ACTION_PATHMOVE:
			if (!CreateSeg)
			{
				Vertex *daSeg;
				daSeg=m_Scene->GetShapeVert(X,Y);
				if (daSeg!=NULL)
				{
					CreateSeg=1;
					PrevVal=(*daSeg);
					MoveVert=daSeg;
					DaVal.x=daSeg->x-Pos.x;

					DaVal.y=daSeg->y-Pos.y;
					DaVal.z=daSeg->z-Pos.z;

					if ((SShape!=NULL)&&(SPath!=NULL))
						GenerateObject();

				}

			}
			else
			{
				CreateSeg=0;
			}
			break;
			*/
		case ACTION_PATHSCALEX:
		case ACTION_PATHSCALEY:
			//scale
			if (!CreateSeg)
			{
				Vertex *daSeg;
				daSeg=m_Scene->GetShapeVert(X,Y);
				if (daSeg!=NULL)
				{
					CreateSeg=1;
					tmpMod=FindModif(daSeg);
					if (tmpMod==-1)
						tmpMod=(ModifAv==99)?-1:ModifAv++;

					if (tmpMod!=-1)
					{
						AllModif[tmpMod].Dot=daSeg;
						dx=X;
						dy=Y;
						AllModif[tmpMod].HasScale=true;
					}
				}

			}
			else
			{
				CreateSeg=0;
			}

			break;

		case ACTION_PATHROTATEX:
		case ACTION_PATHROTATEY:
		case ACTION_PATHROTATEZ:
			//rotate
			if (!CreateSeg)
			{
				Vertex *daSeg;
				daSeg=m_Scene->GetShapeVert(X,Y);
				if (daSeg!=NULL)
				{
					CreateSeg=1;
					tmpMod=FindModif(daSeg);
					if (tmpMod==-1)
						tmpMod=(ModifAv==99)?-1:ModifAv++;

					if (tmpMod!=-1)
					{

						AllModif[tmpMod].Dot=daSeg;
						dx=X;
						dy=Y;
						AllModif[tmpMod].HasRotate=true;
					}
				}
			}
			else
			{
				CreateSeg=0;
			}
			break;

	}			

}
void CKPluginModifier::RMouseDown(int X,int Y,Vertex &Pos)
{
}
void CKPluginModifier::LMouseUp(int X,int Y,Vertex &Pos)
{

}
void CKPluginModifier::RMouseUp(int X,int Y,Vertex &Pos)
{
	if (TypeEdit==ACTION_MAPPINGEDIT)
		m_KUVEdit.LMouseDown(X,Y,Pos);
	else
	if (TypeEdit==ACTION_CUTTER)
		CreateSeg=0;
	DrawViews();
}
void CKPluginModifier::MouseMove(int X,int Y,Vertex &Pos)
{
	SWITCH_RESOURCE;

	CKShape *tmpShp;

    Vertex temp;

	if ((LastAction==ACTION_CUTTER)&&(CreateSeg==1))
	{
		Remem2=Pos;
	}
	else
	{
		switch(LastAction)
		{
			case ACTION_MAPPINGEDIT:
				m_KUVEdit.MouseMove(X,Y,Pos);
				break;
			case ACTION_LATHE:
				{
					tmpShp=m_Scene->GetShape(X,Y);
					if (tmpShp!=NULL)
					{
						LStatus("Pick this shape to lathe");
						SetPointer(LoadCursor(ExtensionDLL.hResource,MAKEINTRESOURCE(IDC_POINTER_FOUND)));
					}
					else
					{
						LStatus("Pick a shape to lathe");
						SetPointer(LoadCursor(ExtensionDLL.hResource,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));
					}
				}
				break;
			case ACTION_SELECTSHAPE:
				tmpShp=m_Scene->GetShape(X,Y);
				if (tmpShp!=NULL)
				{
					if (tmpShp->IsClosed())
					{
						LStatus("Pick this shape to extrude");
					}
					else
						LStatus("Pick a shape to extrude");
					//SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_FOUND)));
				}
				else
				{
					LStatus("Pick a shape to extrude");
					//SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));
				}
				break;
			case ACTION_SELECTPATH:
				tmpShp=m_Scene->GetShape(X,Y);
				if (tmpShp!=NULL)
				{
					LStatus("Pick this shape for path extruder");
					//SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_FOUND)));
				}
				else
				{
					LStatus("Pick a extruder shape");
					//SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));
				}
				break;

			// Move Dot
			case ACTION_PATHMOVE:
				if (CreateSeg)
				{
					*MoveVert=DaVal+(Pos);
					GenerateObject();
					DrawViews();
				}
				break;
			case ACTION_PATHSCALEX:
				// scale
				if (CreateSeg)
				{
					AllModif[tmpMod].ScaleX=((X-dx)/10.0f);
					AllModif[tmpMod].ScaleX=((AllModif[tmpMod].ScaleX<=-1)?-1:(AllModif[tmpMod].ScaleX));

					LStatus("Scale X: %5.2f Y: %5.2f",AllModif[tmpMod].ScaleX,AllModif[tmpMod].ScaleY);
					GenerateObject();
					DrawViews();
				}
				else
				{
					Vertex *daSeg;
					daSeg=m_Scene->GetShapeVert(X,Y);

					if (daSeg!=NULL)
						LStatus("Scale this Vertex");
					else
						LStatus("Select a path vertex to scale");
				}
				break;
			case ACTION_PATHSCALEY:
				// scale
				if (CreateSeg)
				{
					AllModif[tmpMod].ScaleY=((Y-dy)/10.0f);
					AllModif[tmpMod].ScaleY=((AllModif[tmpMod].ScaleY<=-1)?-1:(AllModif[tmpMod].ScaleY));

					LStatus("Scale X: %5.2f Y: %5.2f",AllModif[tmpMod].ScaleX,AllModif[tmpMod].ScaleY);
					GenerateObject();
					DrawViews();
				}
				else
				{
					Vertex *daSeg;
					daSeg=m_Scene->GetShapeVert(X,Y);

					if (daSeg!=NULL)
						LStatus("Scale this Vertex");
					else
						LStatus("Select a path vertex to scale");
				}
				break;
			case ACTION_PATHROTATEX:
				// rotate
				if (CreateSeg)
				{
					AllModif[tmpMod].RotatX=(X-dx);

					LStatus("Rotation X: %5.2f Y: %5.2f Z: %5.2f",AllModif[tmpMod].RotatX,AllModif[tmpMod].RotatY,AllModif[tmpMod].RotatZ);
					GenerateObject();
					DrawViews();
				}
				else
				{
					Vertex *daSeg;
					daSeg=m_Scene->GetShapeVert(X,Y);

					if (daSeg!=NULL)
						LStatus("Rotate this Vertex");
					else
						LStatus("Select a path vertex to rotate");
				}
				break;
			case ACTION_PATHROTATEY:
				// rotate
				if (CreateSeg)
				{
					AllModif[tmpMod].RotatY=(X-dx);

					LStatus("Rotation X: %5.2f Y: %5.2f Z: %5.2f",AllModif[tmpMod].RotatX,AllModif[tmpMod].RotatY,AllModif[tmpMod].RotatZ);
					GenerateObject();
					DrawViews();
				}
				else
				{
					Vertex *daSeg;
					daSeg=m_Scene->GetShapeVert(X,Y);

					if (daSeg!=NULL)
						LStatus("Rotate this Vertex");
					else
						LStatus("Select a path vertex to rotate");
				}
				break;
			case ACTION_PATHROTATEZ:
				// rotate
				if (CreateSeg)
				{
					AllModif[tmpMod].RotatZ=(X-dx);

					LStatus("Rotation X: %5.2f Y: %5.2f Z: %5.2f",AllModif[tmpMod].RotatX,AllModif[tmpMod].RotatY,AllModif[tmpMod].RotatZ);
					GenerateObject();
					DrawViews();
				}
				else
				{
					Vertex *daSeg;
					daSeg=m_Scene->GetShapeVert(X,Y);

					if (daSeg!=NULL)
						LStatus("Rotate this Vertex");
					else
						LStatus("Select a path vertex to rotate");
				}
				break;
		}
	}
}


void CKPluginModifier::RecurseUnif(UnifFace *dau,int nbu,int v1,int v2)
{
    int j;

    for (int i=0;i<nbu;i++)
    {
        if (dau[i].daTag==0)
        {
			bool bCollapse=false;

			int modit=dau[i].daf->nb2vert;

			for (j=0;j<dau[i].daf->nb2vert;j++)
			{
				if ( ((dau[i].daf->nbvert[j]==v1)&&(dau[i].daf->nbvert[((j+1)%modit)]==v2)) ||
					((dau[i].daf->nbvert[j]==v2)&&(dau[i].daf->nbvert[((j+1)%modit)]==v1)) )
					bCollapse=true;

			}

			if (bCollapse)
            {
                dau[i].daTag=1;
				bool SameWise=false;

				for (j=0;j<modit;j++)
				{
					if ((dau[i].daf->nbvert[j]==v1)&&(dau[i].daf->nbvert[((j+1)%modit)]==v2)) 
						SameWise=true;

				}

				if (SameWise)
				{
					dau[i].daf->FlipWise();
					/*
					for (j=0;j<modit;j++)
					{
                    dummy=dau[i].daf->nbvert[2];
                    dau[i].daf->nbvert[2]=dau[i].daf->nbvert[0];
                    dau[i].daf->nbvert[0]=dummy;
					}
					*/
                }

				for (j=0;j<dau[i].daf->nb2vert;j++)
				{
					RecurseUnif(dau,nbu,dau[i].daf->nbvert[j],dau[i].daf->nbvert[((j+1)%dau[i].daf->nb2vert)]);
				}
				/*
                RecurseUnif(dau,nbu,dau[i].daf->nbvert[0],dau[i].daf->nbvert[1]);
                RecurseUnif(dau,nbu,dau[i].daf->nbvert[1],dau[i].daf->nbvert[2]);
                RecurseUnif(dau,nbu,dau[i].daf->nbvert[2],dau[i].daf->nbvert[0]);
				*/
            }
        }
    }
}

void CKPluginModifier::UnifyNormalFaces(void)
{
    int i,j;
    UnifFace * pef;

    
    for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
    {
        if (daMesh->Selected)
        {
            pef=new UnifFace[daMesh->nb2poly];

            for (i=0;i<daMesh->nb2poly;i++)
            {
                pef[i].daTag=0;
                pef[i].daf=&daMesh->pl[i];
            }

            for (i=0;i<daMesh->nb2poly;i++)
            {
                if (pef[i].daTag==0)
                {
                    pef[i].daTag=1;
					for (j=0;j<pef[i].daf->nb2vert;j++)
					{
						RecurseUnif(pef,daMesh->nb2poly,pef[i].daf->nbvert[j],pef[i].daf->nbvert[((j+1)%pef[i].daf->nb2vert)]);
					}
                }
            }

            delete [] pef;
			daMesh->UpdateMesh();

        }
        else
        {
            /*
            for (i=0;i<daMesh->nb2faces;i++)
            {
                if ( (daMesh->pv[daMesh->pf[i]->nbvert[0]]->Selected)&&
                    (daMesh->pv[daMesh->pf[i]->nbvert[1]]->Selected)&&
                    (daMesh->pv[daMesh->pf[i]->nbvert[2]]->Selected) )
                {
                    dummy=daMesh->pf[i]->nbvert[0];
                    daMesh->pf[i]->nbvert[0]=daMesh->pf[i]->nbvert[2];
                    daMesh->pf[i]->nbvert[2]=dummy;
                }
            }
            */
			

        }
        
    }

    DrawViews();
}

void CKPluginModifier::FlipNormalFaces(void)
{
    int i;

    for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
    {
        if (daMesh->Selected)
        {
            for (i=0;i<daMesh->nb2poly;i++)
            {
				daMesh->pl[i].FlipWise();
            }
        }
        else
        {
            for (i=0;i<daMesh->nb2poly;i++)
            {
                if ( (daMesh->pv[daMesh->pl[i].nbvert[0]].Selected)&&
                    (daMesh->pv[daMesh->pl[i].nbvert[1]].Selected)&&
                    (daMesh->pv[daMesh->pl[i].nbvert[2]].Selected) )
                {
					daMesh->pl[i].FlipWise();
                }
            }
        }
		daMesh->UpdateMesh();
    }

    DrawViews();
}

// ----------------------------------------------------------------------------


void CKPluginModifier::SetSelectedToAfterUndo(void)
{
	int UndoAv=0;
	for (CKMesh *daMesh2=m_Scene->FirstMesh;daMesh2!=NULL;daMesh2=daMesh2->Next)
	{
		if (daMesh2->Selected)
		{
			CurrentUndo->SetAfterEntry(UndoAv,PLUGIN_MESH,daMesh2);
			UndoAv++;
		}
	}
}

void CKPluginModifier::SetSelectedToBeforeUndo(void)
{
	int UndoAv=0;
	for (CKMesh *daMesh2=m_Scene->FirstMesh;daMesh2!=NULL;daMesh2=daMesh2->Next)
	{
		if (daMesh2->Selected)
		{
			CurrentUndo->SetPrevEntry(UndoAv,PLUGIN_MESH,daMesh2);
			UndoAv++;
		}
	}
}

void CKPluginModifier::BeginCutter(int X,int Y,Vertex *Pos)
{
	// Cliper
	Remem=(*Pos);
	dx=X;
	dy=Y;

	CreateSeg=1;
	// undo
	CurrentUndo=m_Scene->AddUndo("MapEditor.dll",GetNbSelectedObjects());
	CurrentUndo->UndoType=UNDO_MODIFY;
	SetSelectedToBeforeUndo();
}

void CKPluginModifier::ValidateCutter(int X,int Y,Vertex *Pos)
{
	CKMesh *daMesh=BuildCutter(Remem,*Pos);
	daMesh->CalcAllPlanes();
	UpdateBspTree(daMesh);

//	m_Scene->InitAllObjectsTag(0);
	for (CKMesh *daMesh2=m_Scene->FirstMesh;daMesh2!=NULL;daMesh2=daMesh2->Next)
	{
		if (daMesh2->Selected)
		{
			UpdateBspTree(daMesh2);
			SubObject(daMesh2,daMesh);
			daMesh2->Tag=1;
		}
	}
	m_Scene->DeleteBufVert();
	m_Scene->UnSelectAll(false);
	//SomethingSel=false;

	for (daMesh2=m_Scene->FirstMesh;daMesh2!=NULL;daMesh2=daMesh2->Next)
	{
		if (daMesh2->Tag)
		{
			m_Scene->SingleMesh(daMesh2,true);
			daMesh2->Selected=true;
		}
	}

	//m_Scene->AddMesh(daMesh);
	CreateSeg=0;
	DrawViews();
	//undo
	SetSelectedToAfterUndo();
}

#define CSG_NONE				0
#define CSG_DIFFERENCE			1
#define CSG_INTERSECTION		2
#define CSG_UNION				3

int g_iCSGMode=CSG_INTERSECTION;

void CKPluginModifier::UnionObject(CKMesh *Obj1,CKMesh *Obj2)
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CKBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	ClipSolid1 = FALSE; ClipSolid2 = FALSE; 

	CSGTree = ((CKBSPTree*)Obj1->BSPTree);
	
	// Store target tree for easy access
	TGTTree = ((CKBSPTree*)Obj2->BSPTree);
	// Clip the tree against the CSG Tree
	CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
	// First Make a copy of the CSG brush and manipulate this, instead
	// of the actual CSG brush, remember that we may need to add polys to several
	// intersecting brushes.
	CPYTree = CSGTree->CopyTree();
	TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
	// Add all surviving polygons to the target tree
	for ( f = 0; f < CPYTree->PolyCount; f++ )
	{
		if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
	} // Next f
	// Free Up the Copy of the CSG Tree
	//delete CPYTree; CPYTree = NULL;

}

void CKPluginModifier::SubObject(CKMesh *Obj2,CKMesh *Obj1)
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CKBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	ClipSolid1 = TRUE; ClipSolid2 = FALSE; 

	CSGTree = ((CKBSPTree*)Obj1->BSPTree);

	// Store target tree for easy access
	TGTTree = ((CKBSPTree*)Obj2->BSPTree);
	// Clip the tree against the CSG Tree
	CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
	// First Make a copy of the CSG brush and manipulate this, instead
	// of the actual CSG brush, remember that we may need to add polys to several
	// intersecting brushes.
	CPYTree = CSGTree->CopyTree();
	TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
	// When in Difference Mode Invert The Copied Trees polygons
	CPYTree->InvertPolys();
	// Add all surviving polygons to the target tree
	for ( f = 0; f < CPYTree->PolyCount; f++ )
	{
		if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
	} // Next f
	// Free Up the Copy of the CSG Tree
	//delete CPYTree; CPYTree = NULL;
	//TGTTree->RenderBSPPolys(0);

	TGTTree->Commit(Obj2);
	Obj2->CalcTexCoord(128,128,Vertex(0,0,0),0,0);
	Obj2->UpdateMesh();
}


bool CKPluginModifier::AddMesh(CKMesh *Obj2,CKMesh *Obj1)
{
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CKBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	int Oldnbf1,Oldnbf2;

	Oldnbf1=Obj1->nb2poly;
	Oldnbf2=Obj2->nb2poly;

	((CKBSPTree*)Obj1->BSPTree)->ClipTree( ((CKBSPTree*)Obj1->BSPTree)->RootNode, NULL, 0, ((CKBSPTree*)Obj2->BSPTree), TRUE, TRUE);
	((CKBSPTree*)Obj2->BSPTree)->ClipTree( ((CKBSPTree*)Obj2->BSPTree)->RootNode, NULL, 0, ((CKBSPTree*)Obj1->BSPTree), TRUE, FALSE);



	if ( (Obj1->BSPTree->PolyCount!=Oldnbf1)&&(Obj2->BSPTree->PolyCount!=Oldnbf2) )
	{
		Obj1->BSPTree->Commit(Obj1);
		Obj2->BSPTree->Commit(Obj2);//AddTo(Obj1);
		Obj1->UpdateMesh();
		Obj2->UpdateMesh();
		return true;
	}
	else
   
	{
		Obj1->BSPTree->Commit(Obj1);
		Obj2->BSPTree->Commit(Obj2);
		Obj1->UpdateMesh();
		Obj2->UpdateMesh();
		return false;
	}
	//m_Scene->DelObject(daMesh);
}

void CKPluginModifier::UpdateBSPTrees( )
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CKBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;
/*
	// Compile Mini-BSP Trees.
	for ( b = 0; b < BrushCount; b++ ){
		// Clear previously created tree
		if ( Brushes[b].BSPTree ) {
			delete ((CKBSPTree*)Brushes[b].BSPTree);
			Brushes[b].BSPTree = NULL;
		} // End If
		if ( Brushes[b].BSPTree == NULL ) Brushes[b].BSPTree = new CKBSPTree;
		((CKBSPTree*)Brushes[b].BSPTree)->InitPolygons( &Brushes[b], 1, FALSE );
	} // Next Brush
*/
	CKMesh *daMesh;
	for (daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		if (daMesh->BSPTree)
		{
			delete daMesh->BSPTree;
			daMesh->BSPTree=NULL;
		}

		if (daMesh->BSPTree==NULL)
			daMesh->BSPTree=new CKBSPTree;

		daMesh->BSPTree->InitPolygons(daMesh,1,FALSE);
	}

	
	// Setup our solid clipping flags
	switch ( g_iCSGMode ) 
	{
		case CSG_DIFFERENCE:
			ClipSolid1 = TRUE; ClipSolid2 = FALSE; 
			break;
		case CSG_INTERSECTION:
			ClipSolid1 = FALSE; ClipSolid2 = FALSE; 
			break;
	} // End Switch

/*
	if ( g_iCSGMode != CSG_NONE ) {
		// Store CSG Brush for easy access
		CSGTree = ((CKBSPTree*)Brushes[g_iCSGBrush].BSPTree);
		// Perform op with CSG brush on each normal brush
		for ( b = 0; b < BrushCount; b++ ) {
			if ( b == g_iCSGBrush ) continue;
			if ( !BoundingBoxesIntersect(Brushes[g_iCSGBrush].Bounds, Brushes[b].Bounds) ) continue;
			// Store target tree for easy access
			TGTTree = ((CKBSPTree*)Brushes[b].BSPTree);
			// Clip the tree against the CSG Tree
			CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
			// First Make a copy of the CSG brush and manipulate this, instead
			// of the actual CSG brush, remember that we may need to add polys to several
			// intersecting brushes.
			CPYTree = CSGTree->CopyTree();
			TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
			// When in Difference Mode Invert The Copied Trees polygons
			if ( g_iCSGMode == CSG_DIFFERENCE ) CPYTree->InvertPolys();
			// Add all surviving polygons to the target tree
			for ( f = 0; f < CPYTree->PolyCount; f++ ){
				if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
			} // Next f
			// Free Up the Copy of the CSG Tree
			delete CPYTree; CPYTree = NULL;
			if ( g_iCSGMode == CSG_INTERSECTION) TGTTree->InitPolygons( &Brushes[b], 1, TRUE);
		} // Next Brush
	} // End if CSG Mode != CSG_NONE
*/
	if ( g_iCSGMode != CSG_NONE ) 
	{
		// Store CSG Brush for easy access
		CSGTree = ((CKBSPTree*)m_Scene->FirstMesh->BSPTree);
		// Perform op with CSG brush on each normal brush
		for ( daMesh=m_Scene->FirstMesh->Next; daMesh!=NULL; daMesh=daMesh->Next) 
		{
			//if ( b == g_iCSGBrush ) continue;
			//if ( !BoundingBoxesIntersect(Brushes[g_iCSGBrush].Bounds, Brushes[b].Bounds) ) continue;

			// Store target tree for easy access
			TGTTree = ((CKBSPTree*)daMesh->BSPTree);
			// Clip the tree against the CSG Tree
			CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
			// First Make a copy of the CSG brush and manipulate this, instead
			// of the actual CSG brush, remember that we may need to add polys to several
			// intersecting brushes.
			CPYTree = CSGTree->CopyTree();
			TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
			// When in Difference Mode Invert The Copied Trees polygons
			if ( g_iCSGMode == CSG_DIFFERENCE ) CPYTree->InvertPolys();
			// Add all surviving polygons to the target tree
			for ( f = 0; f < CPYTree->PolyCount; f++ ){
				if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
			} // Next f
			// Free Up the Copy of the CSG Tree
			delete CPYTree; CPYTree = NULL;
			TGTTree->RenderBSPPolys(0);
			//if ( g_iCSGMode == CSG_INTERSECTION) TGTTree->InitPolygons( daMesh, 1, TRUE);
			//TGTTree->RenderBSPPolys(0);
		} // Next Brush
	} // End if CSG Mode != CSG_NONE


	/*
	// Now perform a union on all the resulting Trees.
	// THIS is how we perform pre-compile Hidden Surface removal.
	for ( b = 0; b < BrushCount; b++ ) {
		if ( b == g_iCSGBrush && g_iCSGMode != CSG_NONE) continue;
		((CKBSPTree*)Brushes[b].BSPTree)->m_bMisc = FALSE;
		for ( int o = 0; o < BrushCount; o++ ) {
			if ( o == b || (o == g_iCSGBrush && g_iCSGMode != CSG_NONE)) continue;
			if (((CKBSPTree*)Brushes[o].BSPTree)->m_bMisc == TRUE) continue;
			if ( BoundingBoxesIntersect(Brushes[o].Bounds, Brushes[b].Bounds) == TRUE ) {
				((CKBSPTree*)Brushes[o].BSPTree)->ClipTree( ((CKBSPTree*)Brushes[o].BSPTree)->RootNode, NULL, 0, ((CKBSPTree*)Brushes[b].BSPTree), TRUE, TRUE);
				((CKBSPTree*)Brushes[b].BSPTree)->ClipTree( ((CKBSPTree*)Brushes[b].BSPTree)->RootNode, NULL, 0, ((CKBSPTree*)Brushes[o].BSPTree), TRUE, FALSE);
			} //End If Bound Boxes Intersect
			// Because we do a role reversal for each brush in the tree
			// the below line ensures that each tree is only clipped once.
			((CKBSPTree*)Brushes[b].BSPTree)->m_bMisc = TRUE;
		} // End For o
	} // End For b
*/

	CKMesh *g_iCSGBrush=m_Scene->FirstMesh;

	// Now perform a union on all the resulting Trees.
	// THIS is how we perform pre-compile Hidden Surface removal.
	for ( daMesh=m_Scene->FirstMesh; daMesh!=NULL; daMesh=daMesh->Next ) 
	{
		if ( daMesh == g_iCSGBrush && g_iCSGMode != CSG_NONE) continue;
		((CKBSPTree*)daMesh->BSPTree)->m_bMisc = FALSE;
		for ( CKMesh *daO=m_Scene->FirstMesh; daO!=NULL; daO=daO->Next ) 
		{
			if ( daO == daMesh || (daO == g_iCSGBrush && g_iCSGMode != CSG_NONE)) continue;
			if (((CKBSPTree*)daO->BSPTree)->m_bMisc == TRUE) continue;

			//if ( BoundingBoxesIntersect(Brushes[o].Bounds, Brushes[b].Bounds) == TRUE ) 
			{
				((CKBSPTree*)daO->BSPTree)->ClipTree( ((CKBSPTree*)daO->BSPTree)->RootNode, NULL, 0, ((CKBSPTree*)daMesh->BSPTree), TRUE, TRUE);
				((CKBSPTree*)daMesh->BSPTree)->ClipTree( ((CKBSPTree*)daMesh->BSPTree)->RootNode, NULL, 0, ((CKBSPTree*)daO->BSPTree), TRUE, FALSE);
			} //End If Bound Boxes Intersect
			// Because we do a role reversal for each brush in the tree
			// the below line ensures that each tree is only clipped once.
			((CKBSPTree*)daMesh->BSPTree)->m_bMisc = TRUE;
		} // End For o
	} // End For b

	/*
	// Compile final BSP if enabled
	if (g_bCompileFinal ) {	
		// Delete the CSG Brush as we must not include
		// this brush in the final BSP Compile process.
		if ( g_iCSGMode != CSG_NONE ) {
			delete (CKBSPTree*)Brushes[g_iCSGBrush].BSPTree;
			Brushes[g_iCSGBrush].BSPTree = NULL;
		} // End If
		if ( FinalBSP == NULL ) FinalBSP = new CKBSPTree;
		// Do the final compile
		FinalBSP->InitPolygons( Brushes, BrushCount, TRUE);
	} // End If
	*/
}

void CKPluginModifier::HollowObject(CKMesh *Obj)
{
	int i,j,k;


	Obj->CalcAllPlanes();


	if (Obj->BSPTree==NULL)
	{
		Obj->BSPTree=new CKBSPTree;
		Obj->BSPTree->InitPolygons(Obj,1,FALSE);
	}

    //i=0;
	for (i=0;i<Obj->nb2poly;i++)
	{
		m_Scene->AddMesh();
		m_Scene->NextMesh->AllocatePoly(0,Obj->pl[i].nb2vert*2);

		int nb2Poly=2+Obj->pl[i].nb2vert;//+(2*(Obj->pl[i].nb2vert-2));

		m_Scene->NextMesh->AllocatePoly(nb2Poly,0);

		int nSide=Obj->pl[i].nb2vert;
		m_Scene->NextMesh->AllocateUV(0,(nSide*2)+(nSide*4));

		

		// caping
		m_Scene->NextMesh->pl[0].Allocate(m_Scene->NextMesh,1,nSide);
		m_Scene->NextMesh->pl[1].Allocate(m_Scene->NextMesh,1,nSide);
		int TexAv=0;

		for (j=0;j<nSide;j++)
		{
			m_Scene->NextMesh->pl[0].nbvert[nSide-j-1]=(nSide-1-j)*2;
			m_Scene->NextMesh->pl[0].Tex[0][nSide-j-1]=TexAv++;

			m_Scene->NextMesh->pl[1].nbvert[nSide-j-1]=(j*2)+1;
			m_Scene->NextMesh->pl[1].Tex[0][nSide-j-1]=TexAv++;

		}

		// get center of polygon
		Vertex PolyCenter;

		for (j=0;j<nSide;j++)
		{
			PolyCenter+=Obj->pv[Obj->pl[i].nbvert[j]];
		}
		PolyCenter/=nSide;

		// extruding 

		for (j=0;j<nSide;j++)
		{
			m_Scene->NextMesh->pl[j+2].Allocate(m_Scene->NextMesh,1,4);

			m_Scene->NextMesh->pv[j*2]=(Obj->pv[Obj->pl[i].nbvert[j]]-PolyCenter);
			m_Scene->NextMesh->pv[j*2].x*=3;
			m_Scene->NextMesh->pv[j*2].y*=3;
			m_Scene->NextMesh->pv[j*2].z*=3;

			m_Scene->NextMesh->pv[j*2+1]=m_Scene->NextMesh->pv[j*2];

			m_Scene->NextMesh->pv[j*2]+=PolyCenter;
			

			//*m_Scene->NextMesh->pv[j*2+1]=(*Obj->pv[Obj->pl[i].nbvert[j]]-PolyCenter);
			//*m_Scene->NextMesh->pv[j*2+1]*=100.0f;
			m_Scene->NextMesh->pv[j*2+1]-=(Obj->pl[i].Normale*8.0f);
			m_Scene->NextMesh->pv[j*2+1]+=PolyCenter;

				
			m_Scene->NextMesh->pl[j+2].nbvert[3]=(j*2);
			m_Scene->NextMesh->pl[j+2].nbvert[2]=((j*2)+2)%(nSide*2);
			m_Scene->NextMesh->pl[j+2].nbvert[1]=((j*2)+3)%(nSide*2);
			m_Scene->NextMesh->pl[j+2].nbvert[0]=((j*2)+1)%(nSide*2);

			for (k=0;k<4;k++)
				m_Scene->NextMesh->pl[j+2].Tex[0][k]=TexAv++;//k+(nSide*2)+(j*nSide);
		}

		//CalcTexCoord(m_Scene->NextMesh,128,128,*m_Scene->NextMesh->pv[0],0,0);

        m_Scene->NextMesh->CalcAllPlanes();
        Obj->CalcAllPlanes();

		m_Scene->NextMesh->BSPTree=new CKBSPTree;
		m_Scene->NextMesh->BSPTree->InitPolygons(m_Scene->NextMesh,1,FALSE);

		UnionObject(Obj,m_Scene->NextMesh);
        //AddMesh(m_Scene->NextMesh,Obj);
		m_Scene->NextMesh->BSPTree->Commit(m_Scene->NextMesh);
        //Obj->BSPTree->Commit(Obj);
		if (Obj->pl[0].Maps[0]!=NULL)
			m_Scene->NextMesh->ApplyTexture(Obj->pl[0].Maps[0]);
		else
			m_Scene->NextMesh->ApplyTexture(Obj->Tex1);
	    //m_Scene->NextMesh->CalcTexCoord(128,128,Vertex(0,0,0),0,0);
		m_Scene->NextMesh->SetAutoTexRecalc(Obj->GetAutoTexRecalc());

		m_Scene->NextMesh->UpdateMesh();

	}
	m_Scene->DelMesh(Obj);
}

void CKPluginModifier::Symetry(Vertex value)
{

	Vertex daMin,daMax,daCenter;
	Vertex VX,VY,VZ;

	daCenter=m_Scene->GetCenterOfSel(&daMin,&daMax);

    VertBuf *daBufVert;
	Vertex temp,temp2;

    daBufVert=m_Scene->FirstBufVert;
    while(daBufVert!=NULL)
    {
		temp=daBufVert->AncVal;
		temp2=temp;
		
		if (value.x==1) temp2.x=temp.x+2*(daCenter.x-temp.x);
		if (value.y==1) temp2.y=temp.y+2*(daCenter.y-temp.y);
		if (value.z==1) temp2.z=temp.z+2*(daCenter.z-temp.z);

        daBufVert->IsNow(temp2);

        daBufVert=daBufVert->Next;
    }

	m_Scene->UpdateBuf();
}

void CKPluginModifier::Spherize(double ScVal)
{
	//ScVal=0;


	Vertex daMin,daMax,daCenter;
	Vertex VX,VY,VZ;
	double Length2,Length,gLength;

	daCenter=m_Scene->GetCenterOfSel(&daMin,&daMax);

	daMax-=daCenter;
	Length=daMax.Normalize();
	//Length=::Pythagore3D(daCenter,(daMax-daCenter));

    VertBuf *daBufVert;
	Vertex temp,temp2;

    daBufVert=m_Scene->FirstBufVert;
    while(daBufVert!=NULL)
    {
		temp=daBufVert->AncVal;
		
		temp-=daCenter;
		Length2=temp.Normalize();
		
		gLength=Length2+((Length-Length2)*ScVal);
		

		temp.x*=gLength;
		temp.y*=gLength;
		temp.z*=gLength;
		temp+=daCenter;

        daBufVert->IsNow(temp);

        daBufVert=daBufVert->Next;
    }

//	m_Scene->UpdateBuf();
}

void CKPluginModifier::RotateBuf(Vertex Vect,double ng)
{
	Vertex daMin,daMax,daCenter;
	Vertex value,value2;
    double nx2,ny2,nz2;
    double m1,m2,m3,m4,m5,m6,m7,m8,m9;


	daCenter=m_Scene->GetCenterOfSel(&daMin,&daMax);

	ng*=PI;
	ng/=180;

    nx2=(Vect.x*Vect.x);
    ny2=(Vect.y*Vect.y);
    nz2=(Vect.z*Vect.z);

    m1=(nx2+((1-nx2)*cos(ng)));
    m2=((Vect.x*Vect.y*(1-cos(ng)))-(Vect.z*sin(ng)));
    m3=((Vect.x*Vect.z*(1-cos(ng)))+(Vect.y*sin(ng)));
    m4=((Vect.x*Vect.y*(1-cos(ng)))+(Vect.z*sin(ng)));
    m5=(ny2+((1-ny2)*cos(ng)));
    m6=((Vect.y*Vect.z*(1-cos(ng)))-(Vect.x*sin(ng)));
    m7=((Vect.x*Vect.z*(1-cos(ng)))-(Vect.y*sin(ng)));
    m8=((Vect.y*Vect.z*(1-cos(ng)))+(Vect.x*sin(ng)));
    m9=(nz2+((1-nz2)*cos(ng)));

	VertBuf *daVert;

	daVert=m_Scene->FirstBufVert;
	while(daVert!=NULL)
	{
		value=(daVert->AncVal-daCenter);

		value2.x=value.x*m1+value.y*m2+value.z*m3;
		value2.y=value.x*m4+value.y*m5+value.z*m6;
		value2.z=value.x*m7+value.y*m8+value.z*m9;

		daVert->IsNow((value2+daCenter));

		daVert=daVert->Next;
	}

	m_Scene->UpdateBuf();
}

void CKPluginModifier::HollowSelectedObject()
{
	for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;)
	{
		CKMesh *daNext=daMesh->Next;

		UpdateBspTree(daMesh);

		if (daMesh->Selected)
			HollowObject(daMesh);

		daMesh=daNext;
	}

	m_Scene->UnSelectAll(false);
	m_Scene->DeleteBufVert();
}

void CKPluginModifier::UpdateBspTree(CKMesh *daMesh)
{
	daMesh->CalcAllPlanes();

	if (daMesh->BSPTree)
	{
		delete daMesh->BSPTree;
		daMesh->BSPTree=NULL;
	}

	if (daMesh->BSPTree==NULL)
		daMesh->BSPTree=new CKBSPTree;

	daMesh->BSPTree->InitPolygons(daMesh,1,FALSE);
}
void CKPluginModifier::SubSelectedObject(void)
{
	for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		CKMesh *daNext=daMesh->Next;

		if (daMesh->Selected)
		{
			for (CKMesh *daMesh2=m_Scene->FirstMesh;daMesh2!=NULL;daMesh2=daMesh2->Next)
			{
				if (daMesh!=daMesh2)
				{
					UpdateBspTree(daMesh);
					UpdateBspTree(daMesh2);

					SubObject(daMesh2,daMesh);
					//daMesh2->BSPTree->Commit(daMesh2);
				}
			}
		}
	}

	m_Scene->UnSelectAll(false);
	m_Scene->DeleteBufVert();
}

void CKPluginModifier::AddSelectedObject(void)
{
	for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;)
	{
		CKMesh *ObjTmp=daMesh->Next;
		CKMesh *daNext=daMesh->Next;

		if (daMesh->Selected)
		{
			CKMesh *daMesh2=daMesh->Next;
			for (;daMesh2!=NULL;daMesh2=daMesh2->Next)
			{
				if (daMesh2->Selected)
				{
					UpdateBspTree(daMesh);
					UpdateBspTree(daMesh2);

					if (AddMesh(daMesh,daMesh2))
					{
						// addition successfull
						//m_Scene->DelObject(daMesh);
						break;
					}
					else
					{
						// no addition at all

					}
				}
			}
		}
		daMesh=ObjTmp;
	}

	m_Scene->UnSelectAll(false);
	m_Scene->DeleteBufVert();
}

CKMesh *CKPluginModifier::BuildCutter(Vertex v1,Vertex v2)
{

    Vertex End;
    CKMesh *Obj;
    int i;

	Vertex Dif=v2-v1;
	Vertex Zd;

	dap.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);
	/*

	if (Dif.x==0) Zd.x=10;
	if (Dif.y==0) Zd.y=10;
	if (Dif.z==0) Zd.z=10;
*/
	Zd=dap.pZ;
	Vertex Start(0,0,0);
	Zd.x*=1000;
	Zd.y*=1000;
	Zd.z*=1000;



	Obj=new CKMesh();
	Obj->AllocatePoly(0,8);

	Dif.x*=100;
	Dif.y*=100;
	Dif.z*=100;

	Obj->pv[0]=v1-(Zd)-(Dif);
	Obj->pv[1]=v1+(Zd)-(Dif);
	Obj->pv[2]=v2+(Zd)+(Dif);
	Obj->pv[3]=v2-(Zd)+(Dif);

	Vertex Normale;
	Vertex *dpv=Obj->pv;

	Normale.Cross(dpv[1]-dpv[0], dpv[2]-dpv[0]);
	Normale.Normalize();

	Normale.x*=1000;
	Normale.y*=1000;
	Normale.z*=1000;

	Obj->pv[4]=v1-Zd-(Normale)-(Dif);
	Obj->pv[5]=v1+Zd-(Normale)-(Dif);
	Obj->pv[6]=v2+Zd-(Normale)+(Dif);
	Obj->pv[7]=v2-Zd-(Normale)+(Dif);


    Obj->AllocateUV(0,24);
    for (i=0;i<24;i++)
    {
        Obj->puv[0][i].u=0;
        Obj->puv[0][i].v=0;
    }
    Obj->AllocatePoly(6,0);
    for (i=0;i<6;i++)
    {
        Obj->pl[i].Allocate(m_Scene->NextMesh,1,4);
        Obj->pl[i].Tex[0][0]=0;
        Obj->pl[i].Tex[0][1]=0;
        Obj->pl[i].Tex[0][2]=0;
        Obj->pl[i].Tex[0][3]=0;
    }
    // bottom
    Obj->pl[0].nbvert[0]=3;
    Obj->pl[0].nbvert[1]=2;
    Obj->pl[0].nbvert[2]=1;
    Obj->pl[0].nbvert[3]=0;
    // top
    Obj->pl[1].nbvert[0]=4;
    Obj->pl[1].nbvert[1]=5;
    Obj->pl[1].nbvert[2]=6;
    Obj->pl[1].nbvert[3]=7;
    // front
    Obj->pl[2].nbvert[0]=7;
    Obj->pl[2].nbvert[1]=3;
    Obj->pl[2].nbvert[2]=0;
    Obj->pl[2].nbvert[3]=4;
    // back
    Obj->pl[3].nbvert[0]=1;
    Obj->pl[3].nbvert[1]=2;
    Obj->pl[3].nbvert[2]=6;
    Obj->pl[3].nbvert[3]=5;
    // left  
    Obj->pl[4].nbvert[0]=6;
    Obj->pl[4].nbvert[1]=2;
    Obj->pl[4].nbvert[2]=3;
    Obj->pl[4].nbvert[3]=7;
    // right
    Obj->pl[5].nbvert[0]=0;
    Obj->pl[5].nbvert[1]=1;
    Obj->pl[5].nbvert[2]=5;
    Obj->pl[5].nbvert[3]=4;

    //CalcTexCoord(Obj,128,128,Start,tmpuv);
    Obj->Selected=true;

	Obj->CalcAllPlanes();
	Obj->BSPTree=new CKBSPTree;
	Obj->BSPTree->InitPolygons(Obj,1,FALSE);

	return Obj;
}

int CKPluginModifier::GetNbSelectedObjects(void)
{
	int nbObjSel=0;

	for (CKMesh *daMesh2=m_Scene->FirstMesh;daMesh2!=NULL;daMesh2=daMesh2->Next)
		if (daMesh2->Selected) nbObjSel++;

	return nbObjSel;
}


void CKPluginModifier::ApplyModifs(void)
{
	if (m_BufMesh.size()!=0)
		m_BufMesh.erase(m_BufMesh.begin(),m_BufMesh.end());

	m_Mesh2DelStart=NULL;

	m_Scene->UpdateBuf();
}
void CKPluginModifier::PutSelectedToBuf(void)
{
	ApplyModifs();

	for (CKMesh *itMesh=m_Scene->FirstMesh;itMesh!=NULL;itMesh=itMesh->Next)
	{

		if (itMesh->Selected)
		{
			CKMesh *tmpMesh=new CKMesh;
			tmpMesh->IsCopyOf(itMesh);

			tmpMesh->Selected=itMesh->Selected;

			for (int i=0;i<itMesh->nb2poly;i++)
				tmpMesh->pl[i].Selected=itMesh->pl[i].Selected;

			m_BufMesh.push_back(tmpMesh);
			//m_Scene->DelMesh(itMesh);
		}
		else
		{
			for (int i=0;i<itMesh->nb2poly;i++)
			{
				if (itMesh->pl[i].Selected)
				{
					CKMesh *tmpMesh=new CKMesh;
					tmpMesh->IsCopyOf(itMesh);

					tmpMesh->Selected=itMesh->Selected;

					for (int i=0;i<itMesh->nb2poly;i++)
					tmpMesh->pl[i].Selected=itMesh->pl[i].Selected;

					m_BufMesh.push_back(tmpMesh);
					break;
					//m_Scene->DelMesh(itMesh);
				}
			}
		}
	}
}

void CKPluginModifier::DelSelectedMesh(void)
{
	CKMesh *itMesh2;

	for (CKMesh *itMesh=m_Scene->FirstMesh;itMesh!=NULL;)
	{
		itMesh2=itMesh->Next;

		if (itMesh->Selected)
		{
			m_Scene->DelMesh(itMesh);
		}
		else
		{
			for (int i=0;i<itMesh->nb2poly;i++)
			{
				if (itMesh->pl[i].Selected)
				{
					m_Scene->DelMesh(itMesh);
					break;
				}
			}
		}
		itMesh=itMesh2;
	}
	m_Scene->DeleteBufVert();
}

void CKPluginModifier::Explode(float Decal)
{
	
	if (m_Mesh2DelStart!=NULL)
	{
		for (CKMesh *j=m_Mesh2DelStart;j!=NULL;)
		{
			CKMesh *itm2=j->Next;
			m_Scene->DelMesh(j);
			j=itm2;
		}
		m_Scene->DeleteBufVert();
	}
	
	m_Mesh2DelStart=m_Scene->NextMesh;
	
	for (int i=0;i<m_BufMesh.size();i++)
	{
		m_BufMesh[i]->Explode(m_Scene,Decal);
		
	}

	if (m_Mesh2DelStart==NULL) m_Mesh2DelStart=m_Scene->FirstMesh;

	// Select newly meshes
	for (CKMesh *j=m_Mesh2DelStart;j!=NULL;j=j->Next)
		m_Scene->SingleMesh(j,true);

	m_Scene->UpdateSmthSel();

}


void CKPluginModifier::SubDivide(int Iter)
{
	if (m_Mesh2DelStart!=NULL)
	{
		for (CKMesh *j=m_Mesh2DelStart;j!=NULL;)
		{
			CKMesh *itm2=j->Next;
			m_Scene->DelMesh(j);
			j=itm2;
		}
	//	m_Scene->DeleteBufVert();
	}
	
	m_Mesh2DelStart=m_Scene->NextMesh;

	for (int i=0;i<m_BufMesh.size();i++)
	{
		CKMesh *tmpMesh=new CKMesh();
		tmpMesh->IsCopyOf(m_BufMesh[i]);

		m_Scene->AddMesh(tmpMesh);

		if (Iter>0)
			tmpMesh->SubDivide(Iter);

		tmpMesh->UpdateMesh();
	}

	if (m_Mesh2DelStart==NULL) m_Mesh2DelStart=m_Scene->FirstMesh;
/*
	// Select newly meshes
	for (CKMesh *j=m_Mesh2DelStart;j!=NULL;j=j->Next)
		m_Scene->SingleMesh(j,true);

	m_Scene->UpdateSmthSel();
	*/
}
void CKPluginModifier::ExtrudIt()
{
	if (m_Mesh2DelStart!=NULL)
	{
		for (CKMesh *j=m_Mesh2DelStart;j!=NULL;)
		{
			CKMesh *itm2=j->Next;
			m_Scene->DelMesh(j);
			j=itm2;
		}
	}

	m_Mesh2DelStart=m_Scene->NextMesh;

	for (int i=0;i<m_BufMesh.size();i++)
	{
		CKMesh *nMesh=m_Scene->AddMesh();
		nMesh->IsCopyOf(m_BufMesh[i]);

		for (int j=0;j<m_BufMesh[i]->nb2poly;j++)
		{
			nMesh->pl[j].Selected=m_BufMesh[i]->pl[j].Selected;
		}

		nMesh->Extrud(Vertex(0,0,0),m_Extrud.m_SpinLength.GetPos(),
			m_Extrud.m_SpinSteps.GetPos(),m_Extrud.m_SpinScale.GetPos(),false);

		nMesh->UpdateMesh();
	}

	if (m_Mesh2DelStart==NULL) m_Mesh2DelStart=m_Scene->FirstMesh;
}

void CKPluginModifier::Fractalize()
{
	srand(m_Seed);

    VertBuf *daBufVert;
	Vertex temp;

    daBufVert=m_Scene->FirstBufVert;
    while(daBufVert!=NULL)
    {
		temp=daBufVert->AncVal;
		float rnd=rand();
		
		temp.x=temp.x+(((rnd/32768.0f)-0.5f)*m_Fractalize.m_Spin.GetPos());
		rnd=rand();
		temp.y=temp.y+(((rnd/32768.0f)-0.5f)*m_Fractalize.m_Spin.GetPos());
		rnd=rand();
		temp.z=temp.z+(((rnd/32768.0f)-0.5f)*m_Fractalize.m_Spin.GetPos());


        daBufVert->IsNow(temp);

        daBufVert=daBufVert->Next;
    }
}

void CKPluginModifier::GenerateObject(void)
{
	Vertex vt1,vt2;
    Vertex tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8,tmp9;
    Vertex tmp10,tmp11,tmp12,tmp13,tmp14,tmpprev;
    Vertex rotv;
    int VertAv=0;
    int FaceAv=0;
    Vertex Ordinate;
	int i,j,k;
    int SCount,PCount,trav;
    double TotalLength,Length=0;
    int atmpMod;
	int nbSteps=5;
	float Valv,Valu;
	double modelview2[16],modelview[16],InverseModel[16],InverseModel2[16];
	double modelview3[16],InverseModel3[16];
	Vertex Src,Dst;
	CKSegment *daSeg,*daSeg2;



	if ((SShape==NULL)||(SPath==NULL)) return;
	Vertex ZeroBase=SShape->GetCenter();//>FirstSegment->Dot;


	
	
    SCount=SShape->GetCount();
    PCount=SPath->GetCount();

	// path Splined Steps
	double koiv=99.98f/((float)(PCount)*m_Path.m_SpinPath.GetPos());
	double koivv=0;

	// shape steps

	double koiu=100.0f/((float)SCount*m_Path.m_SpinShape.GetPos());
	double koivu=0;
	
    if (LoftMesh==NULL)
		LoftMesh=m_Scene->AddMesh();

	
	bSplinedPath=m_Path.m_SplinedPath.GetCheck();
	bSplinedShape=m_Path.m_SplinedShape.GetCheck();

    //new (CKMesh)(m_Scene,NULL,NULL);
    
    //trav=0;
	int nbPathSteps;
	if (bSplinedPath)
		nbPathSteps=((PCount+1)*(m_Path.m_SpinPath.GetPos()));
	else
	{
		if (SPath->IsClosed())
			nbPathSteps=((PCount)*(m_Path.m_SpinPath.GetPos()));
		else
			nbPathSteps=((PCount)*(m_Path.m_SpinPath.GetPos()))+1;
	}

	int nbShapeSteps=(SCount*(bSplinedShape?m_Path.m_SpinShape.GetPos():1));
	int nbnf=(((PCount)*(m_Path.m_SpinPath.GetPos())))*nbShapeSteps*2;
	
	int nbnv=nbPathSteps*nbShapeSteps;

	if (m_Path.m_Capping.GetCheck()&&(!SPath->IsClosed()))
	{
		trav=ToSurface(SShape,nbnv-nbShapeSteps);
		LoftMesh->AllocatePoly(LoftMesh->nb2poly+nbnf,LoftMesh->nb2vert+nbnv);
	}
	else 
	{
		trav=0;
		LoftMesh->AllocatePoly(nbnf,nbnv);
	}

    

	// pcount+1 pour opened path
	
	LoftMesh->AllocateUV(0,nbnv/*(((PCount+1)*nbSteps)+1)*SCount*/);

	Valv=m_UVParam.m_SpinU.GetPos();
	//ValvDiv=
	Valu=m_UVParam.m_SpinV.GetPos();//(PCount*nbSteps);

	//glPushMatrix();
	//glMatrixMode( GL_MODELVIEW );

    TotalLength=SPath->GetLength();

    j=0;
	// Start of creation
	int dbg1=0;
	int dbg2;

	

	bool OneTrack=false;
	daSeg=SPath->FirstSegment;
	double koivseg=0;
	float avstp=0;
	while(daSeg!=NULL)
	{
		double koivseg=koivv;
		avstp=0;

		int nbiSteps;
		if (bSplinedPath)
			nbiSteps=m_Path.m_SpinPath.GetPos();
		else
			nbiSteps=((daSeg->Next==NULL)?1:m_Path.m_SpinPath.GetPos());

		for (int koi=0;koi<nbiSteps;koi++)
		{
			
			// Path Vertex
			dbg1++;


			//glLoadIdentity();
			if (bSplinedPath)
			{
				Src=SPath->GetSpline(koivv);

				//DMPOutputString("%5.2f + %5.2f -> ",koivv,koiv);
				koivv+=koiv;
				Dst=SPath->GetSpline(koivv+0.01f);
				//DMPOutputString("%5.2f \r\n",koivv);
				
			}
			else
			{
				if (daSeg->Next==NULL)
				{
					Dst=daSeg->Dot+(daSeg->Dot-daSeg->Prev->Dot);
				}
				else
					Dst=daSeg->Next->Dot;
/*
				if (daSeg->Prev==NULL)
					Src=daSeg->Dot;
				else
					Src=daSeg->Prev->Dot;
					*/
				Src=daSeg->Dot;

				Src+=(((Dst-Src)/m_Path.m_SpinPath.GetPos())*avstp);

				// inclinaison 
				if ((avstp==0)&&(daSeg->Prev!=NULL))
				{
					Dst+=(daSeg->Dot-daSeg->Prev->Dot);
				}

				if ((avstp==0)&&(SPath->NextSegment->Next==SPath->FirstSegment)&&(daSeg==SPath->FirstSegment)) //daSeg->Prev!=NULL))
				{
					Dst+=(daSeg->Dot-SPath->NextSegment->Dot);
				}

				koivv+=koiv;
			}	
			
			//DMPOutputString("%5.2f %5.2f %5.2f -> %5.2f %5.2f %5.2f\r\n",Src.x,Src.y,Src.z,Dst.x,Dst.y,Dst.z);

			// Path Matrix

			Vertex upvect=Dst-Src;
			upvect.Normalize();

			//memset(modelview2,0,sizeof(double)*16);
			atmpMod=FindModif(&daSeg->Dot);

			//glLoadIdentity();

			memset(modelview2,0,sizeof(double)*16);
			modelview2[0]=1;
			modelview2[5]=1;
			modelview2[10]=1;
			modelview2[15]=1;

			memset(modelview3,0,sizeof(double)*16);
			modelview3[0]=1;
			modelview3[5]=1;
			modelview3[10]=1;
			modelview3[15]=1;


			double itnrx=0,itnry=0,itnrz=0;
			double cx,cy,cz;
			double sx,sy,sz;
			double anrx=0,anry=0,anrz=0;
			double nfx=0,anfx=0;
			double nfy=0,anfy=0;


			if (atmpMod!=-1)
			{
				if (AllModif[atmpMod].HasScale)
				{
					nfx=AllModif[atmpMod].ScaleX;
					nfy=AllModif[atmpMod].ScaleY;

					//if (bSplinedPath)
					{
						if (daSeg->Next!=NULL)
						{
							int atmpMod2=FindModif(&daSeg->Next->Dot);
							if (atmpMod2!=-1)
							{
								anfx=AllModif[atmpMod2].ScaleX;
								anfy=AllModif[atmpMod2].ScaleY;
							}
						}
					}
				}

				if (AllModif[atmpMod].HasRotate)
				{

					itnrx=AllModif[atmpMod].RotatX;
					itnry=AllModif[atmpMod].RotatY;
					itnrz=AllModif[atmpMod].RotatZ;					
				
					//if (bSplinedPath)
					{
						if (daSeg->Next!=NULL)
						{
							int atmpMod2=FindModif(&daSeg->Next->Dot);
							if (atmpMod2!=-1)
							{
								anrx=AllModif[atmpMod2].RotatX;
								anry=AllModif[atmpMod2].RotatY;
								anrz=AllModif[atmpMod2].RotatZ;

							}
						}
					}
				}
			}
			else
			{
				int atmpMod2=FindModif(&daSeg->Next->Dot);
				if (atmpMod2!=-1)
				{
					if (AllModif[atmpMod2].HasScale)
					{
						anfx=AllModif[atmpMod2].ScaleX;
						anfy=AllModif[atmpMod2].ScaleY;
					}

					if (AllModif[atmpMod2].HasRotate)
					{

						anrx=AllModif[atmpMod2].RotatX;
						anry=AllModif[atmpMod2].RotatY;
						anrz=AllModif[atmpMod2].RotatZ;					
					}
				}
			}


			double Fact=avstp/(m_Path.m_SpinPath.GetPos());
			itnrx=itnrx+((anrx-itnrx)*(Fact));
			itnry=itnry+((anry-itnry)*(Fact));
			itnrz=itnrz+((anrz-itnrz)*(Fact));

			
			nfx=nfx+((anfx-nfx)*(Fact));
			nfy=nfy+((anfy-nfy)*(Fact));

			modelview3[0]=1+nfx;
			modelview3[5]=1+nfy;



			cx = cos((itnrx*PI)/360.0f);
			sx = sin((itnrx*PI)/360.0f);
			cy = cos((itnry*PI)/360.0f);
			sy = sin((itnry*PI)/360.0f);
			cz = cos((itnrz*PI)/360.0f);
			sz = sin((itnrz*PI)/360.0f);


			modelview2[5]= cx*cz;   
			modelview2[9] = sx;
			modelview2[6] = -sx;  
			modelview2[10] = cx*cy;   

			modelview2[0]= cy*cz;   
			modelview2[8]= -sy;
			modelview2[2]= sy;  

			modelview2[4]= sz;
			modelview2[1]= -sz;  


			Vertex nx,ny,nz;

			nz=(Src-Dst);
			nz.Normalize();
			ny=Vertex(0,0,1);

			nx.x =  ny.y*nz.z - ny.z*nz.y;
			nx.y = -ny.x*nz.z + ny.z*nz.x;
			nx.z =  ny.x*nz.y - ny.y*nz.x;

			/* Recompute Y = Z cross X */
			ny.x =  nz.y*nx.z - nz.z*nx.y;
			ny.y = -nz.x*nx.z + nz.z*nx.x;
			ny.z =  nz.x*nx.y - nz.y*nx.x;

			nx.Normalize();
			ny.Normalize();

			#define Mm(row,col)  modelview[col*4+row]
			   Mm(0,0) = nx.x;  Mm(0,1) = nx.y;  Mm(0,2) = nx.z;  Mm(0,3) = 0.0;
			   Mm(1,0) = ny.x;  Mm(1,1) = ny.y;  Mm(1,2) = ny.z;  Mm(1,3) = 0.0;
			   Mm(2,0) = nz.x;  Mm(2,1) = nz.y;  Mm(2,2) = nz.z;  Mm(2,3) = 0.0;
			   Mm(3,0) = 0.0;   Mm(3,1) = 0.0;   Mm(3,2) = 0.0;   Mm(3,3) = 1.0;
			#undef Mm

        

			Length=SPath->GetLength(j);

			//glGetDoublev(GL_MODELVIEW_MATRIX,modelview2);

			//for (i=0;i<16;i++) modelview[i]*=modelview2[i];

			InvertMatrix(modelview,InverseModel);
			InvertMatrix(modelview2,InverseModel2);
			//InvertMatrix(modelview3,InverseModel3);
			memcpy(InverseModel3,modelview3,sizeof(double)*16);

			double avx,avy,avz;

			k=0;

			// Shape Creation

			koivu=0;

			dbg2=0;
			daSeg2=SShape->FirstSegment;
			while(daSeg2!=NULL)
			{

				// Splined Shape

				for (int koj=0;koj<(bSplinedShape?m_Path.m_SpinShape.GetPos():1);koj++)
				{

					dbg2++;

					Vertex ShapeDot;
					if (bSplinedShape)
					{
						ShapeDot=SShape->GetSpline(koivu);
					}
					else
					{
						ShapeDot=daSeg2->Dot;
					}
					koivu+=koiu;
					//ShapeDot-=ZeroBase;
					Vertex ShapeDot2;
					ShapeDot2=ShapeDot-ZeroBase;
					float avx2,avy2,avz2;

					avx=(ShapeDot2.x+trX)*InverseModel3[0]+(ShapeDot2.y+trY)*InverseModel3[4]+ShapeDot2.z*InverseModel3[8];
					avy=(ShapeDot2.x+trX)*InverseModel3[1]+(ShapeDot2.y+trY)*InverseModel3[5]+ShapeDot2.z*InverseModel3[9];
					avz=(ShapeDot2.x+trX)*InverseModel3[2]+(ShapeDot2.y+trY)*InverseModel3[6]+ShapeDot2.z*InverseModel3[10];

					avx2=avx*InverseModel2[0]+avy*InverseModel2[4]+avz*InverseModel2[8];
					avy2=avx*InverseModel2[1]+avy*InverseModel2[5]+avz*InverseModel2[9];
					avz2=avx*InverseModel2[2]+avy*InverseModel2[6]+avz*InverseModel2[10];


					LoftMesh->pv[VertAv].x=avx2*InverseModel[0]+avy2*InverseModel[4]+avz2*InverseModel[8];
					LoftMesh->pv[VertAv].y=avx2*InverseModel[1]+avy2*InverseModel[5]+avz2*InverseModel[9];
					LoftMesh->pv[VertAv].z=avx2*InverseModel[2]+avy2*InverseModel[6]+avz2*InverseModel[10];
					LoftMesh->pv[VertAv]+=Src;
					//LoftMesh->pv[VertAv]+=Src;//daSeg->Dot;


					LoftMesh->puv[0][VertAv].u=(Valu*koivv/100.0f);///TotalLength)*Length;
					LoftMesh->puv[0][VertAv].v=(Valv*koivu/100.0f);

					VertAv++;
				}
				k++;

				daSeg2=daSeg2->Next;
				if (daSeg2==SShape->FirstSegment) break;

			}

			avstp++;
//			if (avstp==m_Path.m_SpinPath.GetPos()) avstp=0;

		}

        j++;
		
		OneTrack=true;


		
		daSeg=daSeg->Next;
		if ((daSeg==SPath->FirstSegment)&&(OneTrack)) break;
		//if (daSeg->Next==NULL) break;
		//if (bSplinedPath&&daSeg->Next->Next==NULL) break;

	}

	//glPopMatrix();

	// Creation des faces

    FaceAv=0;

	//int shpav=
	int shsav=(bSplinedShape?m_Path.m_SpinShape.GetPos():1)*SCount;
    for (i=0;i<(m_Path.m_SpinPath.GetPos())*PCount-(SPath->IsClosed()?1:0);i++)
    {
        for (j=0;j<(bSplinedShape?m_Path.m_SpinShape.GetPos():1)*SCount;j++)
        {
			LoftMesh->pl[FaceAv+trav].Allocate(LoftMesh,1,3);
            LoftMesh->pl[FaceAv+trav].nbvert[0]=j+i*(shsav);
            LoftMesh->pl[FaceAv+trav].nbvert[1]=j+(shsav)+i*(shsav);
            LoftMesh->pl[FaceAv+trav].nbvert[2]=((j+1)%(shsav))+(shsav)+i*(shsav);

			
            LoftMesh->pl[FaceAv+trav].Tex[0][0]=j+i*(shsav);
            LoftMesh->pl[FaceAv+trav].Tex[0][1]=j+(shsav)+i*(shsav);
            LoftMesh->pl[FaceAv+trav].Tex[0][2]=((j+1)%(shsav))+(shsav)+i*(shsav);
			
            FaceAv++;

			LoftMesh->pl[FaceAv+trav].Allocate(LoftMesh,1,3);
            LoftMesh->pl[FaceAv+trav].nbvert[0]=j+i*(shsav);
            LoftMesh->pl[FaceAv+trav].nbvert[1]=((1+j)%(shsav))+(shsav)+i*(shsav);
            LoftMesh->pl[FaceAv+trav].nbvert[2]=((j+1)%(shsav))+i*(shsav);

            LoftMesh->pl[FaceAv+trav].Tex[0][0]=j+i*(shsav);
            LoftMesh->pl[FaceAv+trav].Tex[0][1]=((1+j)%(shsav))+(shsav)+i*(shsav);
            LoftMesh->pl[FaceAv+trav].Tex[0][2]=((j+1)%(shsav))+i*(shsav);
			
            FaceAv++;
			
        }
        //nb2scalesegv++;
    }
	
	if (SPath->IsClosed())
	{
		//MessageBox(NULL,"yup","yop",MB_OK);
		//i=0;
		for (j=0;j<(bSplinedShape?m_Path.m_SpinShape.GetPos():1)*SCount;j++)
        {
			LoftMesh->pl[FaceAv+trav].Allocate(LoftMesh,1,3);
            LoftMesh->pl[FaceAv+trav].nbvert[0]=j+i*(shsav);
            LoftMesh->pl[FaceAv+trav].nbvert[1]=j;
            LoftMesh->pl[FaceAv+trav].nbvert[2]=((j+1)%(shsav))+i*(shsav);

			
            LoftMesh->pl[FaceAv+trav].Tex[0][0]=j+i*(shsav);
            LoftMesh->pl[FaceAv+trav].Tex[0][1]=j;
            LoftMesh->pl[FaceAv+trav].Tex[0][2]=((j+1)%(shsav))+i*(shsav);
			
            FaceAv++;

			LoftMesh->pl[FaceAv+trav].Allocate(LoftMesh,1,3);
            LoftMesh->pl[FaceAv+trav].nbvert[0]=j;//j+i*(shsav);
            LoftMesh->pl[FaceAv+trav].nbvert[1]=((1+j)%(shsav));
            LoftMesh->pl[FaceAv+trav].nbvert[2]=((j+1)%(shsav))+i*(shsav);

            LoftMesh->pl[FaceAv+trav].Tex[0][0]=j;//j+i*(shsav);
            LoftMesh->pl[FaceAv+trav].Tex[0][1]=((1+j)%(shsav));
            LoftMesh->pl[FaceAv+trav].Tex[0][2]=((j+1)%(shsav))+i*(shsav);
			
            FaceAv++;
			
        }

	}
	

	LoftMesh->UpdateMesh();
}


int CKPluginModifier::FindModif(Vertex *vt)
{
    int i;

    for (i=0;i<ModifAv;i++)
    {
        if (AllModif[i].Dot==vt) return i;   
    }

    return -1;
}
int CKPluginModifier::Delaunay(int N, double* x, double* y, int& numTriangles, TriangleList*& triangle)
{
    int result;

    double** point = new double*[N+3];
    int i;
    for (i = 0; i < N+3; i++)
        point[i] = new double[2];
    for (i = 0; i < N; i++)
    {
        point[i][0] = x[i];
        point[i][1] = y[i];
    }

    const double EPSILON = 0.00001;
    const int TSIZE = 75;
    const double RANGE = 10.0;

    double xmin = point[0][0], xmax = xmin;
    double ymin = point[0][1], ymax = ymin;

    for (i = 1; i < N; i++)
    {
        double value = point[i][0];
        if ( xmax < value )
            xmax = value;
        if ( xmin > value )
            xmin = value;

        value = point[i][1];
        if ( ymax < value )
            ymax = value;
        if ( ymin > value )
            ymin = value;
    }

    double xrange = xmax-xmin, yrange = ymax-ymin;
    double maxrange = xrange;
    if ( maxrange < yrange )
        maxrange = yrange;

    // need to scale the data later to do a correct triangle count
    double maxrange2 = maxrange*maxrange;

    // tweak the points by very small random numbers
    double bgs = EPSILON*maxrange;
    srand(367);   
    for (i = 0; i < N; i++) 
    {
        point[i][0] += bgs*(0.5-rand()/double(RAND_MAX));
        point[i][1] += bgs*(0.5-rand()/double(RAND_MAX));
    }

    double wrk[2][3] =
    {
        { 5*RANGE, -RANGE, -RANGE },
        { -RANGE, 5*RANGE, -RANGE }
    };
    for (i = 0; i < 3; i++)
    {
        point[N+i][0] = xmin+xrange*wrk[0][i];
        point[N+i][1] = ymin+yrange*wrk[1][i];
    }

    int i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i11;
    int nts, ii[3];
    double xx;

    int tsz = 2*TSIZE;
    int** tmp = new int*[tsz+1];
    tmp[0] = new int[2*(tsz+1)];
    for (i0 = 1; i0 < tsz+1; i0++)
        tmp[i0] = tmp[0] + 2*i0;
    i1 = 2*(N + 2);

    int* id = new int[i1];
    for (i0 = 0; i0 < i1; i0++) 
        id[i0] = i0; 

    int** a3s = new int*[i1];
    a3s[0] = new int[3*i1];
    for (i0 = 1; i0 < i1; i0++)
        a3s[i0] = a3s[0] + 3*i0;
    a3s[0][0] = N;
    a3s[0][1] = N+1;
    a3s[0][2] = N+2;

    double** ccr = new double*[i1];  // circumscribed centers and radii
    ccr[0] = new double[3*i1];
    for (i0 = 1; i0 < i1; i0++)
        ccr[i0] = ccr[0] + 3*i0;
    ccr[0][0] = 0.0;
    ccr[0][1] = 0.0;
    ccr[0][2] = +999999999999;//+NAN;// FLT_MAX;

    nts = 1;  // number of triangles
    i4 = 1;

    // compute triangulation
    for (i0 = 0; i0 < N; i0++)
    {  
        i1 = i7 = -1;
        i9 = 0;
        for (i11 = 0; i11 < nts; i11++)
        {
            i1++;
            while ( a3s[i1][0] < 0 ) 
                i1++;
            xx = ccr[i1][2];
            for (i2 = 0; i2 < 2; i2++)
            {  
                double z = point[i0][i2]-ccr[i1][i2];
                xx -= z*z;
                if ( xx < 0 )
                    goto Corner3;
            }
            i9--;
            i4--;
            id[i4] = i1;
            for (i2 = 0; i2 < 3; i2++)
            {  
                ii[0] = 0;
                if (ii[0] == i2) 
                    ii[0]++;
                for (i3 = 1; i3 < 2; i3++)
                {  
                    ii[i3] = ii[i3-1] + 1;
                    if (ii[i3] == i2) 
                        ii[i3]++;
                }
                if ( i7 > 1 )
                {  
                    i8 = i7;
                    for (i3 = 0; i3 <= i8; i3++)
                    {  
                        for (i5 = 0; i5 < 2; i5++)
                            if ( a3s[i1][ii[i5]] != tmp[i3][i5] )
                                goto Corner1;
                        for (i6 = 0; i6 < 2; i6++) 
                            tmp[i3][i6] = tmp[i8][i6];
                        i7--;
                        goto Corner2;
Corner1:;
                    }
                }
                if ( ++i7 > tsz )
                {
                    // temporary storage exceeded, increase TSIZE
                    result = 0;
                    goto ExitDelaunay;
                }
                for (i3 = 0; i3 < 2; i3++) 
                    tmp[i7][i3] = a3s[i1][ii[i3]];
Corner2:;
            }
            a3s[i1][0] = -1;
Corner3:;
        }

        for (i1 = 0; i1 <= i7; i1++)
        {  
            for (i2 = 0; i2 < 2; i2++)
                for (wrk[i2][2] = 0, i3 = 0; i3 < 2; i3++)
                {
                    wrk[i2][i3] = point[tmp[i1][i2]][i3]-point[i0][i3];
                    wrk[i2][2] += 
                        0.5*wrk[i2][i3]*(point[tmp[i1][i2]][i3]+point[i0][i3]);
                }

            xx = wrk[0][0]*wrk[1][1]-wrk[1][0]*wrk[0][1];
            ccr[id[i4]][0] = (wrk[0][2]*wrk[1][1]-wrk[1][2]*wrk[0][1])/xx;
            ccr[id[i4]][1] = (wrk[0][0]*wrk[1][2]-wrk[1][0]*wrk[0][2])/xx;

            for (ccr[id[i4]][2] = 0, i2 = 0; i2 < 2; i2++) 
            {  
                double z = point[i0][i2]-ccr[id[i4]][i2];
                ccr[id[i4]][2] += z*z;
                a3s[id[i4]][i2] = tmp[i1][i2];
            }

            a3s[id[i4]][2] = i0;
            i4++;
            i9++;
        }
        nts += i9;
    }

    // count the number of triangles
    numTriangles = 0;
    i0 = -1;
    for (i11 = 0; i11 < nts; i11++)
    {  
        i0++;
        while ( a3s[i0][0] < 0 ) 
            i0++;
        if ( a3s[i0][0] < N )
        {  
            for (i1 = 0; i1 < 2; i1++) 
                for (i2 = 0; i2 < 2; i2++) 
                    wrk[i1][i2] = 
                        point[a3s[i0][i1]][i2]-point[a3s[i0][2]][i2];

            xx = wrk[0][0]*wrk[1][1]-wrk[0][1]*wrk[1][0];

            if ( fabs(xx) > EPSILON*maxrange2 )
                numTriangles++;
        }
    }

    // create the triangles
    triangle = new TriangleList[numTriangles];

    numTriangles = 0;
    i0 = -1;
    for (i11 = 0; i11 < nts; i11++)
    {
        i0++;
        while ( a3s[i0][0] < 0 )
            i0++;
        if ( a3s[i0][0] < N )
        {
            for (i1 = 0; i1 < 2; i1++)
                for (i2 = 0; i2 < 2; i2++)
                    wrk[i1][i2] =
                        point[a3s[i0][i1]][i2]-point[a3s[i0][2]][i2];

            xx = wrk[0][0]*wrk[1][1]-wrk[0][1]*wrk[1][0];

            if ( fabs(xx) > EPSILON*maxrange2 )
            {  
                int delta = xx < 0 ? 1 : 0;
                TriangleList& tri = triangle[numTriangles];
                tri[0] = a3s[i0][0];
                tri[1] = a3s[i0][1+delta];
                tri[2] = a3s[i0][2-delta];
                numTriangles++;
            }
        }
    }

    //delete [] triangle;

    result = 1;

ExitDelaunay:;
    delete[] tmp[0];
    delete[] tmp;
    delete[] id;
    delete[] a3s[0];
    delete[] a3s;
    delete[] ccr[0];
    delete[] ccr;
    for (i = 0; i < N+3; i++)
        delete[] point[i];
    delete[] point;

    return result;
}

double davertx[10000],daverty[10000];

int CKPluginModifier::ToSurface(CKShape *daShp,int TroncFaces)
{ 
    CKMesh *value;

    Vertex bout,mwt,mwt2,mwt3;
	int stopiteasy=0,stopitok=0;
    int nb2SIB1=0;
    TriangleList* datriangle;
	Vertex temp;
    CKSegment *daSeg;
    int vtav,numTriangles,trav;
    int i;

    vtav=0;

	if (m_Path.m_SplinedShape.GetCheck())
	{
		float avval=(100.0f/(m_Path.m_SpinShape.GetPos()*SShape->GetCount()));
		for (float ikoi=0;ikoi<100;ikoi+=avval)
		{
			Vertex splvt=daShp->GetSpline(ikoi);
			davertx[vtav]=splvt.x;
			daverty[vtav]=splvt.y;

			vtav++;
			nb2SIB1++;
		}
	}
	else
	{
		daSeg=daShp->FirstSegment;

		while(daSeg!=NULL)
		{
			davertx[vtav]=daSeg->Dot.x;
			daverty[vtav]=daSeg->Dot.y;

			vtav++;
			nb2SIB1++;

			daSeg=daSeg->Next;

			if (daSeg==daShp->FirstSegment) break;
		}
	}
	
	Delaunay(nb2SIB1,davertx,daverty,numTriangles,datriangle);

    if (numTriangles==0)
    {
        return NULL;
    }

    value=LoftMesh;
    value->AllocatePoly(numTriangles*2,0);


    // -- Medium weight --------------------------------------------------------

    trav=0;

    for (i=0;i<numTriangles;i++)
    {
        
        mwt.x=(davertx[datriangle[i][0]]+davertx[datriangle[i][1]]+davertx[datriangle[i][2]])/3;
        mwt.y=(daverty[datriangle[i][0]]+daverty[datriangle[i][1]]+daverty[datriangle[i][2]])/3;
        mwt.z=0;


		if (daShp->IsVertInShape(mwt,NULL))
        {
			value->pl[trav].Allocate(value,1,3);
          value->pl[trav].nbvert[0]=datriangle[i][0];
          value->pl[trav].nbvert[1]=datriangle[i][1];
          value->pl[trav].nbvert[2]=datriangle[i][2];
          value->pl[trav].Tex[0][0]=datriangle[i][0];
          value->pl[trav].Tex[0][1]=datriangle[i][1];
          value->pl[trav].Tex[0][2]=datriangle[i][2];

          trav++;
		  value->pl[trav].Allocate(value,1,3);
          value->pl[trav].nbvert[0]=datriangle[i][2]+TroncFaces;
          value->pl[trav].nbvert[1]=datriangle[i][1]+TroncFaces;
          value->pl[trav].nbvert[2]=datriangle[i][0]+TroncFaces;
          value->pl[trav].Tex[0][0]=datriangle[i][2]+TroncFaces;
          value->pl[trav].Tex[0][1]=datriangle[i][1]+TroncFaces;
          value->pl[trav].Tex[0][2]=datriangle[i][0]+TroncFaces;

          trav++;

          
        }

    }

    delete [] datriangle;
    value->nb2poly=trav;
    value->AllocatePoly(trav,0);

    return trav;
}
