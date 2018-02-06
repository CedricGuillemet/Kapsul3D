#include "stdafx.h"


#include "resource.h"
#include <commctrl.h>
#include <math.h>
#include "PrimDiag.h"
#include "ModPrim3D.h"
#include "PrimDiag.h"

//#include "f:/projets/kapsul/prim3D/Tree.h"
#include "Tree/tree/Tree.h"

CRollupCtrl *m_wndRollupCtrl;
CMapping m_Mapping;
CParameters m_Parameters;
CTreeParam m_TreeParam;

CKPluginPrim3D::CKPluginPrim3D()
{
}

CKPluginPrim3D::~CKPluginPrim3D()
{
}

HWND CKPluginPrim3D::Open(HWND Parent)
{
	SWITCH_RESOURCE;

	CurrentMesh=NULL;
	LeafMesh=NULL;
	CurrentPatch=NULL;
	GNeedTexRecalc=false;

	m_Parameters.m_Plugin=this;
	m_Mapping.m_Plugin=this;
	m_TreeParam.m_Plugin=this;

	nbSegHemis=8;
	nbSegSphere=8;
	nbSeg1Grid=4;
	nbSeg2Grid=4;
	nbSeg1Torus=6;
	nbSeg2Torus=8;
	nbSeg1Cylinder=1;
	nbSeg2Cylinder=8;
	nbSeg1Cone=1;
	nbSeg2Cone=8;
	nbSeg1Tube=1;
	nbSeg2Tube=8;
	nbSeg1Patch=1;
	nbSeg2Patch=1;
	nbSegStairs=3;
	nbSeg13DGrid=3;
	nbSeg23DGrid=3;
	nbSeg33DGrid=3;
	HasMoveCr=false;

    Valu=1.0f;
    Valv=1.0f;

	CreateSeg=0;



    m_wndRollupCtrl=new CRollupCtrl();
    m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,4,164,362), CWnd::FromHandle(Parent), 2);	


    BrowserDiag=new CPrimDiag;
    BrowserDiag->Create((unsigned int)IDD_MODDIAG,CWnd::FromHandle(Parent));
    
    
    return BrowserDiag->m_hWnd;

	GNeedTexRecalc=((CKOption*)GetGOption())->GenerateUV();
	m_Parameters.SetAutoUV(GNeedTexRecalc);
    // init other variables

/*
    treeTex=new CTexture(NULL,NULL);
    treeTex->Type=TEXTURE_FILE;
    strcpy(treeTex->FileName,"bouleau.jpg");
    treeTex->Load();

    FeuilTex=new CTexture(NULL,NULL);
    FeuilTex->Type=TEXTURE_FILE;
    FeuilTex->ComputeAlpha=true;
    strcpy(FeuilTex->FileName,"bouleau2.bmp");
    //strcpy(FeuilTex->FileName,"F:/projets/Kapsul/Skybox/SnowLand/l2back.bmp");
    //strcpy(FeuilTex->FileName,"leaf_back.png");

    
    FeuilTex->Load();
*/


}
void CKPluginPrim3D::Close()
{
	m_wndRollupCtrl->DestroyWindow();
    BrowserDiag->DestroyWindow();
}


void CKPluginPrim3D::ObjToUndo(void)
{
	CurrentUndo=m_Scene->AddUndo("Prim3D.dll",1);
	CurrentUndo->UndoType=UNDO_CREATE;
	CurrentUndo->SetAfterEntry(0,PLUGIN_MESH,CurrentMesh);
}

void CKPluginPrim3D::PatchToUndo(void)
{
	CurrentUndo=m_Scene->AddUndo("Prim3D.dll",1);
	CurrentUndo->UndoType=UNDO_CREATE;
	CurrentUndo->SetAfterEntry(0,PLUGIN_PATCH,CurrentPatch);
}

void CKPluginPrim3D::LastToSel(void)
{
	m_Scene->UnSelectAll(false);
	m_Scene->SingleMesh(CurrentMesh,true);
	m_Scene->HookMinSel=m_Scene->GetMinBuf();
	m_Scene->HookMaxSel=m_Scene->GetMaxBuf();
	m_Scene->SomeThingSel=(m_Scene->FirstBufVert!=NULL);
}

int CKPluginPrim3D::ScenePluginType()
{
	return PLUGIN_PRIMITIVE;
}
void CKPluginPrim3D::ReSize(int sx,int sy)
{
	m_wndRollupCtrl->MoveWindow(0,0,sx,sy,TRUE);
}
void CKPluginPrim3D::LoseFocus()
{
	CurrentMesh=NULL;
	CurrentPatch=NULL;
}

CString CKPluginPrim3D::GetName()
{
	return "3D primitives";
}

CString CKPluginPrim3D::GetInfos()
{
	return "3D primitives";
}

bool CKPluginPrim3D::CreatingStatus()
{
	return (CreateSeg!=0);
}

void CKPluginPrim3D::SetScene(CKScene *pScene)
{
	m_Scene=pScene;
}

PrimBmp* CKPluginPrim3D::GetAllPrimitives()
{
	SWITCH_RESOURCE;

	daBmps.NbBmps=14;
	for (int i=0;i<daBmps.NbBmps;i++)
		daBmps.Bmp[i].Detach();

	daBmps.Bmp[0].LoadBitmap(MAKEINTRESOURCE(IDB_GRIDIN));
	daBmps.PrimNb[0]=3;
	daBmps.Bmp[1].LoadBitmap(MAKEINTRESOURCE(IDB_SPHEREIN));
	daBmps.PrimNb[1]=4;
	daBmps.Bmp[2].LoadBitmap(MAKEINTRESOURCE(IDB_CYLINDERIN));
	daBmps.PrimNb[2]=5;
	daBmps.Bmp[3].LoadBitmap(MAKEINTRESOURCE(IDB_CONEIN));
	daBmps.PrimNb[3]=6;
	daBmps.Bmp[4].LoadBitmap(MAKEINTRESOURCE(IDB_CUBEIN));
	daBmps.PrimNb[4]=7;
	daBmps.Bmp[5].LoadBitmap(MAKEINTRESOURCE(IDB_TORUSIN));
	daBmps.PrimNb[5]=8;
	daBmps.Bmp[6].LoadBitmap(MAKEINTRESOURCE(IDB_TUBEIN));
	daBmps.PrimNb[6]=9;
	daBmps.Bmp[7].LoadBitmap(MAKEINTRESOURCE(IDB_HEMISIN));
	daBmps.PrimNb[7]=10;
	daBmps.Bmp[8].LoadBitmap(MAKEINTRESOURCE(IDB_TREEIN));
	daBmps.PrimNb[8]=11;
	daBmps.Bmp[9].LoadBitmap(MAKEINTRESOURCE(IDB_PATCHIN));
	daBmps.PrimNb[9]=12;
	daBmps.Bmp[10].LoadBitmap(MAKEINTRESOURCE(IDB_COMPLEXSTAIRSIN));
	daBmps.PrimNb[10]=13;
	daBmps.Bmp[11].LoadBitmap(MAKEINTRESOURCE(IDB_SIMPLESTAIRSIN));
	daBmps.PrimNb[11]=14;
	daBmps.Bmp[12].LoadBitmap(MAKEINTRESOURCE(IDB_GRID3DIN));
	daBmps.PrimNb[12]=15;
	daBmps.Bmp[13].LoadBitmap(MAKEINTRESOURCE(IDB_BONE));
	daBmps.PrimNb[13]=16;

	return &daBmps;
}
void CKPluginPrim3D::SetPrimitive(int PrimitiveNb)
{
	TypeEdit=PrimitiveNb;

	CurrentPatch=NULL;
	CurrentMesh=NULL;
	LeafMesh=NULL;
	switch(TypeEdit)
	{
	case 3:	// grid
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		m_Parameters.SetParams(true,true,1,200,1,200,1,1,nbSeg1Grid,nbSeg2Grid);
		break;
	case 4:	// sphere
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		m_Parameters.SetParams(true,false,3,200,0,0,1,0,nbSegSphere,0);
		break;
	case 5:  // cylinder
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);
		
		m_Parameters.SetParams(true,true,1,200,3,200,1,1,nbSeg1Cylinder,nbSeg2Cylinder);
		break;
	case 6:	//cone
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		m_Parameters.SetParams(true,true,1,200,3,200,1,1,nbSeg1Cone,nbSeg2Cone);
		break;
	case 7:	// cube
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		RememBox=m_Scene->SnapVal;
		m_Parameters.SetParams(false,false,0,0,0,0,0,0,0,0);
		break;
	case 8: // torus
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);
		
		m_Parameters.SetParams(true,true,1,200,3,200,1,1,nbSeg1Torus,nbSeg2Torus);
		break;
	case 9: // tube
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		m_Parameters.SetParams(true,true,1,200,3,200,1,1,nbSeg1Tube,nbSeg2Tube);
		break;
	case 10: //hemis
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		m_Parameters.SetParams(true,false,3,200,0,0,1,0,nbSegHemis,0);
		break;
	case 11: // tree
		m_wndRollupCtrl->EnablePage(0,FALSE);
		m_wndRollupCtrl->EnablePage(1,TRUE);

		m_wndRollupCtrl->ExpandPage(0,FALSE);
		m_wndRollupCtrl->ExpandPage(1,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);
		break;
	case 12: // patch
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		m_Parameters.SetParams(true,true,1,20,1,20,1,1,nbSeg1Patch,nbSeg2Patch);
		break;
	case 13: // complex stairs
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		RememBox=m_Scene->SnapVal*nbSegStairs;
		
		m_Parameters.SetParams(true,false,0,30,0,0,1,0,nbSegStairs,0);
		break;
	case 14:	// simple stairs
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		RememBox=m_Scene->SnapVal*nbSegStairs;
		
		m_Parameters.SetParams(true,false,0,30,0,0,1,0,nbSegStairs,0);
		break;
	case 15: // Grid 3D
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);
		RememBox=m_Scene->SnapVal;
		m_Parameters.SetParams(true,true,1,200,1,200,1,1,nbSeg13DGrid,nbSeg23DGrid,true,1,100,1,nbSeg33DGrid);

		break;
	case 16: // bone
		m_wndRollupCtrl->EnablePage(0,TRUE);
		m_wndRollupCtrl->EnablePage(1,FALSE);

		m_wndRollupCtrl->ExpandPage(0,TRUE);
		m_wndRollupCtrl->ExpandPage(2,TRUE);

		m_Parameters.SetParams(false,false,0,0,0,0,0,0,0,0);
		break;

	}

	BrowserDiag->Invalidate(true);
}
void CKPluginPrim3D::DeleteStuff(void *pData,int DataType)
{
	if (pData!=NULL)
	{
		if ((CKMesh*)pData==CurrentMesh)
		{
			CurrentMesh=NULL;
			LeafMesh=NULL;
		}

		if ((CKPatch*)pData==CurrentPatch)
		{
			CurrentPatch=NULL;
		}

		
	}
	else
	{
		if (CurrentMesh!=NULL)
		{
			if (CurrentMesh->Selected)
			{
				CurrentMesh=NULL;
				LeafMesh=NULL;
			}
		}

		if (CurrentPatch!=NULL)
		{
			if (CurrentPatch->Selected)
			{
				CurrentPatch=NULL;
			}
		}

	}
}

void CKPluginPrim3D::LMouseDown(int X,int Y,Vertex &Pos)
{
	Crp.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);

    switch(TypeEdit)
    {
        case 1:
            break;

        // -- Grid -------------------------------------------------------------

        case 3:
            if (CreateSeg)
            {
				//CurrentMesh->UpdateMesh();
                CreateSeg=0;
				LastToSel();
				ObjToUndo();
            }
            else
            {
                CurrentMesh=m_Scene->AddMesh();
				

                Remem=Pos;
                dx=X;
                dy=Y;

				m_Gen.AutoUV=GNeedTexRecalc;
				double sx=0,sy=0;

                m_Gen.CreateGrid(CurrentMesh,Remem,sx,sy,nbSeg1Grid,nbSeg2Grid);
				//CurrentMesh->SetAutoTexRecalc(GNeedTexRecalc);

                CreateSeg=1;
				HasMoveCr=false;
            }
            break;

        // -- Sphere -----------------------------------------------------------

        case 4:
            if (CreateSeg)
            {
				//CurrentMesh->UpdateMesh();
                CreateSeg=0;
				LastToSel();

				ObjToUndo();
            }
            else
            {
                CurrentMesh=m_Scene->AddMesh();
				

                Remem=Pos;
				m_Gen.AutoUV=GNeedTexRecalc;
                m_Gen.CreateSphere(CurrentMesh,Remem,0,nbSegSphere,OriginNg);
				//CurrentMesh->SetAutoTexRecalc(GNeedTexRecalc);

                CreateSeg=1;
				HasMoveCr=false;
            }
            break;
        // -- Cylinder ---------------------------------------------------------
        case 5:
            switch(CreateSeg)
            {
                case 0:
                    dx=X;
                    dy=Y;

					CurrentMesh=m_Scene->AddMesh();
					
					m_Gen.AutoUV=GNeedTexRecalc;
					Radius1=0;
					Radius2=0;
                    m_Gen.CreateCyl(CurrentMesh,Pos,Radius1,Radius2,nbSeg1Cylinder,nbSeg2Cylinder,OriginNg);
					//CurrentMesh->SetAutoTexRecalc(GNeedTexRecalc);
                    Remem=Pos;


                    /*
                    StartVert=Pos;
                    CreateCube(StartVert,(Pos-Pos));
                    */
					HasMoveCr=false;
                    CreateSeg=1;
                    break;
                case 1:
                    CreateSeg=2;
                    break;
                case 2:
					//CurrentMesh->UpdateMesh();
                    CreateSeg=0;
				LastToSel();

					ObjToUndo();
                    break;

            }
            break;
        // -- Cone -------------------------------------------------------------
        case 6:
            switch(CreateSeg)
            {
                case 0:
                    dx=X;
                    dy=Y;

					CurrentMesh=m_Scene->AddMesh();
					

					m_Gen.AutoUV=GNeedTexRecalc;
					Radius1=0;
					Radius2=0;
                    m_Gen.CreateCyl(CurrentMesh,Pos,Radius1,Radius2,nbSeg1Cone,nbSeg2Cone,OriginNg);
					//CurrentMesh->SetAutoTexRecalc(GNeedTexRecalc);
                    Remem=Pos;
					HasMoveCr=false;


                    /*
                    StartVert=Pos;
                    CreateCube(StartVert,(Pos-Pos));
                    */
                    CreateSeg=1;
                    break;
                case 1:
                    CreateSeg=2;
                    break;
                case 2:
                    CreateSeg=3;
                    break;
                case 3:
					//CurrentMesh->UpdateMesh();
                    CreateSeg=0;
				LastToSel();

					ObjToUndo();

                    break;

            }
            break;

        // -- Cube & stairs-------------------------------------------------------------

		case 13:
		case 14:
        case 7:
		    if ((HasMoveCr)&&(CreateSeg))
			{
				//CurrentMesh->UpdateMesh();
				CreateSeg=0;
				LastToSel();

				ObjToUndo();
			}
			else
			{
				if(CreateSeg==0)
				{
					dx=X;
					dy=Y;
					CurrentMesh=m_Scene->AddMesh();
					
					m_Gen.AutoUV=GNeedTexRecalc;

					switch(TypeEdit)
					{
					case 7:

						m_Gen.CreateCube(CurrentMesh,Pos,0,0,0);
						break;
					case 13:
						m_Gen.CreateStairs(CurrentMesh,Pos,0,0,0,nbSegStairs);//svgX,svgY,0);
					case 14:
		                m_Gen.CreateStairsSimple(CurrentMesh,Pos,0,0,0,nbSegStairs);
						break;
					}


					//CurrentMesh->SetAutoTexRecalc(GNeedTexRecalc);
					Remem=Pos;

					CreateSeg=1;
					HasMoveCr=false;
				}
			}
            break;

        // -- Torus ------------------------------------------------------------
        case 8:
            switch(CreateSeg)
            {
                case 0:
                    dx=X;
                    dy=Y;
					CurrentMesh=m_Scene->AddMesh();
					
					m_Gen.AutoUV=GNeedTexRecalc;
                    m_Gen.CreateTorus(CurrentMesh,Pos,0,0,nbSeg1Torus,nbSeg2Torus,OriginNg);
					//CurrentMesh->SetAutoTexRecalc(GNeedTexRecalc);
                    Remem=Pos;
                    CreateSeg=1;
					HasMoveCr=false;
                    break;
                case 1:
                    CreateSeg=2;
                    break;
                case 2:
					//CurrentMesh->UpdateMesh();
                    CreateSeg=0;
				LastToSel();

					ObjToUndo();
                    break;
            }
            break;
        // -- Tube -------------------------------------------------------------
        case 9:
            switch(CreateSeg)
            {
                case 0:
                    dx=X;
                    dy=Y;

					CurrentMesh=m_Scene->AddMesh();
					


                    //CreateCyl(Pos,0,0,10,10);
                    Remem=Pos;

					m_Gen.AutoUV=GNeedTexRecalc;
					Radius1=0;
                    m_Gen.CreateTube(CurrentMesh,Pos,0,0,Radius1,nbSeg1Tube,nbSeg2Tube,OriginNg);
					//CurrentMesh->SetAutoTexRecalc(GNeedTexRecalc);
                    Remem=Pos;


                    /*
                    StartVert=Pos;
                    CreateCube(StartVert,(Pos-Pos));
                    */
					HasMoveCr=false;
                    CreateSeg=1;
                    break;
                case 1:
                    CreateSeg=2;
                    break;
                case 2:
                    CreateSeg=3;
                    break;
                case 3:
					//CurrentMesh->UpdateMesh();

                    CreateSeg=0;
				LastToSel();

					ObjToUndo();

                    break;

            }
            break;
        // -- HemiSphere -------------------------------------------------------

        case 10:
            if (CreateSeg)
            {
				//CurrentMesh->UpdateMesh();
                CreateSeg=0;
				LastToSel();

				ObjToUndo();
            }
            else
            {
                CurrentMesh=m_Scene->AddMesh();
				


                Remem=Pos;
				m_Gen.AutoUV=GNeedTexRecalc;
                m_Gen.CreateHemis(CurrentMesh,Remem,0,nbSegHemis,OriginNg);
				//CurrentMesh->SetAutoTexRecalc(GNeedTexRecalc);
				HasMoveCr=false;
                CreateSeg=1;

				
            }
            break;

        // -- Tree ------------------------------------------------------------
        case 11:    
            m_Scene->AddMesh();
            CurrentMesh=m_Scene->NextMesh;
			//CurrentMesh->NeedTexRecalc=GNeedTexRecalc;

            m_Scene->AddMesh();
            LeafMesh=m_Scene->NextMesh;
            Remem=Pos;
            mytree.build(CurrentMesh,LeafMesh,&Pos);
			CurrentMesh->UpdateMesh();
			LeafMesh->UpdateMesh();

			CurrentUndo=m_Scene->AddUndo("Prim3D.dll",2);
			CurrentUndo->UndoType=UNDO_CREATE;
			CurrentUndo->SetAfterEntry(0,PLUGIN_MESH,CurrentMesh);
			CurrentUndo->SetAfterEntry(1,PLUGIN_MESH,LeafMesh);
            break;
        // -- Patch ------------------------------------------------------------

        case 12:
            if (CreateSeg)
            {
				//CurrentPatch->up
                CreateSeg=0;


				//ObjToUndo();
            }
            else
            {
				
				Crp.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);
				rmX=Crp.pX;
				rmY=Crp.pY;

                m_Scene->AddPatch();

                CurrentPatch=m_Scene->NextPatch;


                Remem=Pos;
                dx=X;
                dy=Y;

                //m_Gen.CreateGrid(CurrentMesh,Remem,0,0,4,4);

				CurrentPatch->IsPlanar(nbSeg1Patch,nbSeg2Patch,Remem,Vertex(0,0,0),rmX,rmY,1,1);
				CurrentPatch->Build(10);
				CurrentPatch->ComputeTexCoords(0,1,1,nbSeg1Patch,nbSeg2Patch);
				HasMoveCr=false;
                CreateSeg=1;
            }
            break;
		// Grid 3D
		case 15:
			if ((HasMoveCr)&&(CreateSeg))
			{
				//CurrentMesh->UpdateMesh();
				CreateSeg=0;
				LastToSel();

				ObjToUndo();
			}
			else
			{
				if(CreateSeg==0)
				{
					dx=X;
					dy=Y;
					CurrentMesh=m_Scene->AddMesh();
					
					m_Gen.AutoUV=GNeedTexRecalc;

					double sx=0,sy=0,sz=0;
					m_Gen.Create3DGrid(CurrentMesh,Pos,sx,sy,sz,nbSeg13DGrid,nbSeg23DGrid,nbSeg33DGrid);
					Remem=Pos;

					CreateSeg=1;
					HasMoveCr=false;
				}
			}
			break;
			// -- Bone ----------------------------------------------------------
		case 16:
			if (CreateSeg==0)
			{
				CKBone *myBone=0;
				myBone=m_Scene->GetBone(X,Y);
				if (myBone!=NULL)
				{
					CurrentBone=myBone;
                
					CurSkel=m_Scene->GetSkeleton(X,Y);
					if (CurSkel!=NULL)
					{
						CurrentSkel=CurSkel;
						CreateSeg=1;
						CurrentBone=CurrentSkel->AddBone(CurrentBone);
						CurrentBone->Pos=Pos;
						CurSkel->BuildBase();
					}
				}
				else
				{
					//new skeletton
					CurrentSkel=m_Scene->AddSkel();
					CurrentSkel->RootPos=Pos;
					CurrentBone=CurrentSkel->AddBone(NULL);
					CurrentSkel->BuildBase();
					CurrentBone->Pos=Pos;
					CurrentBone=CurrentSkel->AddBone(CurrentBone);
					CurSkel=CurrentSkel;
					CreateSeg=1;
				}
			}
			else
			{
				CurSkel->BuildBase();
				CurrentBone=CurrentSkel->AddBone(CurrentBone);
				CurrentBone->Pos=Pos;
				CurSkel->BuildBase();
			}
			break;
    }
	DrawViews();
}
void CKPluginPrim3D::RMouseDown(int X,int Y,Vertex &Pos)
{
}

void CKPluginPrim3D::LMouseUp(int X,int Y,Vertex &Pos)
{
	if (TypeEdit!=16)
	{
		if (CreateSeg)
		{
			if (HasMoveCr)
			{
				//CreateSeg=0;
				if (CreateSeg==1)
				{
					LMouseDown(X,Y,Pos);
					HasMoveCr=false;
				}
			}
		}
	}
	DrawViews();
}

void CKPluginPrim3D::RMouseUp(int X,int Y,Vertex &Pos)
{
	if (CreateSeg)
    {
		if (TypeEdit==16)
		{
			CreateSeg=0;
			CurSkel->DelBone(CurrentBone);
		}
		else
		{
			if (TypeEdit==12) 
				m_Scene->DelPatch(CurrentPatch);
			else 
				m_Scene->DelMesh(CurrentMesh);
		}

        DrawViews();
        CreateSeg=0;
        CurrentMesh=NULL;
		CurrentPatch=NULL;
		DrawViews();
    }
}
void CKPluginPrim3D::MouseMove(int X,int Y,Vertex &Pos)
{
	MYPOINT spt1,spt2;

	Crp.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);

	if (CreateSeg)
	{
		m_Gen.VecX=Crp.pX;
		m_Gen.VecY=Crp.pY;
		m_Gen.VecZ=Crp.pZ;

		m_Gen.VecX.Normalize();
		m_Gen.VecY.Normalize();
		m_Gen.VecZ.Normalize();

	}


    switch(TypeEdit)
    {
        case 1:
            break;

        // -- Grid -------------------------------------------------------------
        case 3:
            if (CreateSeg)
            {
				Vertex daStart;
				double lngx,lngy;
				Crp.PlanOfView(m_Scene->m_Renderer,m_Scene->Active);

				m_Gen.VecX=Crp.pX;
				m_Gen.VecY=Crp.pY;
				m_Gen.VecZ=Crp.pZ;

				lngx=(X-dx);
				lngy=(Y-dy);

				daStart=Remem;

				m_Gen.AutoUV=GNeedTexRecalc;
                m_Gen.CreateGrid(CurrentMesh,daStart,lngx,lngy,nbSeg1Grid,nbSeg2Grid);
                oX=X;
                oY=Y;
				
                CurrentMesh=m_Scene->NextMesh;
                LStatus("Grid X: %5.2f Y:%5.2f ",(float)lngx,(float)lngy);

            }
            break;
        // -- Sphere -----------------------------------------------------------
        case 4:
            if (CreateSeg)
            {
                spt1=m_Scene->Get2D(Remem);
                spt2=m_Scene->Get2D(Pos);
                OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                Radius1=::Pythagore3D(Remem,Pos);

				m_Gen.AutoUV=GNeedTexRecalc;
                m_Gen.CreateSphere(CurrentMesh,Remem,Radius1,nbSegSphere,OriginNg);

				//CurrentMesh->UpdateMesh();

                CurrentMesh=m_Scene->NextMesh;

                LStatus("Sphere Radius: %5.2f Angle: %5.2f",Radius1,(OriginNg/PI)*180.0f);

            }
            break;
        // -- Cylinder ---------------------------------------------------------
        case 5:
            switch(CreateSeg)
            {
                case 1:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    //Radius1=Pythagore(dx-X,dy-Y);
					Radius1=::Pythagore3D(Remem,Pos);
					m_Gen.AutoUV=GNeedTexRecalc;
					Radius2=0;
                    m_Gen.CreateCyl(CurrentMesh,Remem,Radius1,Radius2,nbSeg1Cylinder,nbSeg2Cylinder,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;
                    break;

                case 2:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius2=dy-Y;//Pythagore(dx-X,dy-Y);
					m_Gen.AutoUV=GNeedTexRecalc;
                    m_Gen.CreateCyl(CurrentMesh,Remem,Radius1,Radius2,nbSeg1Cylinder,nbSeg2Cylinder,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;
					
                    break;
            }
            if (CreateSeg)
            {
                LStatus("Cylinder Radius 1: %5.2f Height: %5.2f Angle: %5.2f",Radius1,Radius2,(OriginNg/PI)*180.0f);
            }

            break;

        // -- Cone -------------------------------------------------------------
        case 6:
            switch(CreateSeg)
            {
                case 1:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius1=::Pythagore3D(Remem,Pos);
					
					m_Gen.AutoUV=GNeedTexRecalc;
					Radius2=0;
                    m_Gen.CreateCone(CurrentMesh,Remem,Radius1,Radius1,Radius2,nbSeg1Cone,nbSeg2Cone,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;
                    break;

                case 2:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius2=::Pythagore3D(Remem,Pos);
					m_Gen.AutoUV=GNeedTexRecalc;
					Radius3=0;
                    m_Gen.CreateCone(CurrentMesh,Remem,Radius2,Radius1,Radius3,nbSeg1Cone,nbSeg2Cone,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;
                    break;
                case 3:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius3=dy-Y;//Pythagore(dx-X,dy-Y);
					m_Gen.AutoUV=GNeedTexRecalc;
                    m_Gen.CreateCone(CurrentMesh,Remem,Radius2,Radius1,Radius3,nbSeg1Cone,nbSeg2Cone,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;

                    break;
            }
            if (CreateSeg)
            {
                LStatus("Cone Radius 1: %5.2f Radius 1: %5.2f Height : %5.2f Angle: %5.2f",Radius1,Radius2,Radius3,(OriginNg/PI)*180.0f);
            }

            break;

        // -- Cube -------------------------------------------------------------
		case 13:
		case 14:
        case 7:
			if (CreateSeg)
			{
				Vertex tempsz=Pos-Remem;

				if (tempsz.x==0) tempsz.x=RememBox.x;
				if (tempsz.y==0) tempsz.y=RememBox.y;
				if (tempsz.z==0) tempsz.z=RememBox.z;

				Vertex daStart,daLength;

				if (tempsz.x<0)
				{
					daStart.x=Pos.x;
					tempsz.x=-tempsz.x;
				}
				else
					daStart.x=Remem.x;

				if (tempsz.y<0)
				{
					daStart.y=Pos.y;
					tempsz.y=-tempsz.y;
				}
				else
					daStart.y=Remem.y;

				if (tempsz.z<0)
				{
					daStart.z=Pos.z;
					tempsz.z=-tempsz.z;
				}
				else
					daStart.z=Remem.z;


				m_Gen.VecX=Vertex(1,0,0);
				m_Gen.VecY=Vertex(0,1,0);
				m_Gen.VecZ=Vertex(0,0,1);

				m_Gen.AutoUV=GNeedTexRecalc;

				switch (TypeEdit)
				{
				case 7:
	                m_Gen.CreateCube(CurrentMesh,daStart,tempsz.x,tempsz.y,tempsz.z);//svgX,svgY,0);
					//CurrentMesh->UpdateMesh();
					LStatus("Cube X: %5.2f Y: %5.2f Z: %5.2f ",tempsz.x,tempsz.y,tempsz.z);
					break;
				case 13:
	                m_Gen.CreateStairs(CurrentMesh,daStart,tempsz.x,tempsz.y,tempsz.z,nbSegStairs);//svgX,svgY,0);
					//CurrentMesh->UpdateMesh();
					LStatus("Complex Stairs X: %5.2f Y: %5.2f Z: %5.2f",tempsz.x,tempsz.y,tempsz.z);
					break;
				case 14:
	                m_Gen.CreateStairsSimple(CurrentMesh,daStart,tempsz.x,tempsz.y,tempsz.z,nbSegStairs);//svgX,svgY,0);
					//CurrentMesh->UpdateMesh();
					LStatus("Simple Stairs X: %5.2f Y: %5.2f Z: %5.2f ",tempsz.x,tempsz.y,tempsz.z);
					break;
				}
				Radius1=tempsz.x;
				Radius2=tempsz.y;
				Radius3=tempsz.z;

				RememBox2=tempsz;
				RememBox3=daStart;
                CurrentMesh=m_Scene->NextMesh;


			}
            break;
        // -- Torus ------------------------------------------------------------
        case 8:
            switch(CreateSeg)
            {
                case 1:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius1=::Pythagore3D(Remem,Pos);
					m_Gen.AutoUV=GNeedTexRecalc;
                    m_Gen.CreateTorus(CurrentMesh,Remem,Radius1,0,nbSeg1Torus,nbSeg2Torus,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;
                    break;

                case 2:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius2=::Pythagore3D(Remem,Pos);
					m_Gen.AutoUV=GNeedTexRecalc;
                    m_Gen.CreateTorus(CurrentMesh,Remem,Radius1,Radius2,nbSeg1Torus,nbSeg2Torus,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;
                    break;
            }

            if (CreateSeg)
            {
                LStatus("Torus Radius 1: %5.2f Radius 2: %5.2f Angle: %5.2f",Radius1,Radius2,(OriginNg/PI)*180.0f);
            }

            break;
        // -- Tube -------------------------------------------------------------
        case 9:
            switch(CreateSeg)
            {
                case 1:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius1=::Pythagore3D(Remem,Pos);
					m_Gen.AutoUV=GNeedTexRecalc;
					Radius2=0;
                    m_Gen.CreateTube(CurrentMesh,Remem,Radius1,Radius1,Radius2,nbSeg1Tube,nbSeg2Tube,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;
                    break;

                case 2:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius2=::Pythagore3D(Remem,Pos);
					m_Gen.AutoUV=GNeedTexRecalc;
					Radius3=0;
                    m_Gen.CreateTube(CurrentMesh,Remem,Radius1,Radius2,Radius3,nbSeg1Tube,nbSeg2Tube,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;
                    break;
                case 3:
                    spt1=m_Scene->Get2D(Remem);
                    spt2=m_Scene->Get2D(Pos);
                    OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                    Radius3=dy-Y;////Pythagore(dx-X,dy-Y);
					m_Gen.AutoUV=GNeedTexRecalc;
                    m_Gen.CreateTube(CurrentMesh,Remem,Radius1,Radius2,Radius3,nbSeg1Tube,nbSeg2Tube,OriginNg);
					//CurrentMesh->UpdateMesh();
                    CurrentMesh=m_Scene->NextMesh;

                    break;
            }
            if (CreateSeg)
            {
                LStatus("Tube Radius 1: %5.2f Radius 2: %5.2f Height %5.2f Angle: %5.2f",Radius1,Radius2,Radius3,(OriginNg/PI)*180.0f);
            }

            break;
        // -- HemiSphere -------------------------------------------------------
        case 10:
            if (CreateSeg)
            {
                spt1=m_Scene->Get2D(Remem);
                spt2=m_Scene->Get2D(Pos);
                OriginNg=ng(spt1.x,spt1.y,spt2.x,spt2.y);

                Radius1=::Pythagore3D(Remem,Pos);
				m_Gen.AutoUV=GNeedTexRecalc;
                m_Gen.CreateHemis(CurrentMesh,Remem,Radius1,nbSegHemis,OriginNg);
				//CurrentMesh->UpdateMesh();
                CurrentMesh=m_Scene->NextMesh;

                LStatus("Hemisphere radius : %5.2f Angle: %5.2f",Radius1,(OriginNg/PI)*180.0f);
            }

            break;
        // -- Patch -------------------------------------------------------------
        case 12:
            if (CreateSeg)
            {
				double sx=(X-dx),sy=(Y-dy);
				
				if (GetSnap())
				{
					Vertex vlngx=rmX*sx;
					vlngx.Snap(m_Scene->SnapVal);

					Vertex vlngy=rmY*sy;
					vlngy.Snap(m_Scene->SnapVal);

					// uniform
					if (fabs(rmX.x)>=0.0001f)
						sx=(vlngx.x/rmX.x);
					else
						if (fabs(rmX.y)>=0.0001f)
							sx=(vlngx.y/rmX.y);
						else
							sx=(vlngx.z/rmX.z);

					if (fabs(rmY.x)>=0.0001f)
						sy=(vlngy.x/rmY.x);
					else
						if (fabs(rmY.y)>=0.0001f)
							sy=(vlngy.y/rmY.y);
						else
							sy=(vlngy.z/rmY.z);
				}
				//Vertex daStart=Center;
	
				Vertex Center=Remem;

				if (sx<0)
				{
					sx=-sx;
					Center-=(rmX*sx);
				}

				if (sy>0)
				{
					sy=-sy;
					Center-=(rmY*sy);
				}


				CurrentPatch->IsPlanar(nbSeg1Patch,nbSeg2Patch,Center,Vertex(sx,sy,0),rmX,rmY,1,1);
				CurrentPatch->Build(10);
				CurrentPatch->ComputeTexCoords(0,1,1,nbSeg1Patch,nbSeg2Patch);

				
                oX=X;
                oY=Y;
				
                CurrentMesh=m_Scene->NextMesh;
                LStatus("Patch X: %5.2f Y:%5.2f ",(float)(X-dx),(float)(Y-dy));

            }
            break;
		// GRID 3D
		case 15:
			if (CreateSeg)
			{
				Vertex tempsz=Pos-Remem;

				if (tempsz.x==0) tempsz.x=RememBox.x;
				if (tempsz.y==0) tempsz.y=RememBox.y;
				if (tempsz.z==0) tempsz.z=RememBox.z;

				Vertex daStart,daLength;

				if (tempsz.x<0)
				{
					daStart.x=Pos.x;
					tempsz.x=-tempsz.x;
				}
				else
					daStart.x=Remem.x;

				if (tempsz.y<0)
				{
					daStart.y=Pos.y;
					tempsz.y=-tempsz.y;
				}
				else
					daStart.y=Remem.y;

				if (tempsz.z<0)
				{
					daStart.z=Pos.z;
					tempsz.z=-tempsz.z;
				}
				else
					daStart.z=Remem.z;


				m_Gen.VecX=Vertex(1,0,0);
				m_Gen.VecY=Vertex(0,1,0);
				m_Gen.VecZ=Vertex(0,0,1);

				m_Gen.AutoUV=GNeedTexRecalc;

				double sx=tempsz.x;
				double sy=tempsz.y;
				double sz=tempsz.z;
				//sy=8;
				m_Gen.Create3DGrid(CurrentMesh,daStart,sx,sy,sz,nbSeg13DGrid,nbSeg23DGrid,nbSeg33DGrid);
				LStatus("Grid X: %5.2f Y: %5.2f Z: %5.2f ",sx,sy,sz);

				Radius1=tempsz.x;
				Radius2=tempsz.y;
				Radius3=tempsz.z;

				RememBox2=tempsz;
				RememBox3=daStart;
                CurrentMesh=m_Scene->NextMesh;


			}
            break;
		case 16:
			if (CreateSeg==1)
			{
				CurrentBone->Pos=Pos;
				CurSkel->BuildBase();
				LStatus("Click to set extremity.");

			}
			else
			{
				LStatus("Pick bone or root.");
				//sprintf(temp,"Got -> %x",m_Scene->GetBone(X,Y));
				//SendMessage(TWin,WM_SETSTATUS,2,(long)temp);

			}
			break;


    }
	if (CreateSeg)
	{
		DrawViews();
	}

	HasMoveCr=true;
}

void CKPluginPrim3D::UpdateCurrentPrimitive()
{
	bool mSelected=false;
	// unselect vertex
	if ((TypeEdit<12)||(TypeEdit>12))
	{
		if (CurrentMesh==NULL) return;
		if (CurrentMesh->Selected)
		{
			mSelected=true;
			m_Scene->UnSelectAll(false);
			m_Scene->DeleteBufVert();
		}
	}
	else
	{
		if (CurrentPatch==NULL) return;

		if (CurrentPatch->Selected)
		{
			mSelected=true;
			m_Scene->UnSelectAll(false);
			m_Scene->DeleteBufVert();
		}
	}


	// update mesh

    if ((CurrentMesh!=NULL)||(CurrentPatch!=NULL))
    {
        switch(TypeEdit)
        {
            //case IDC_CUBE:
        case 7:
            m_Gen.CreateCube(CurrentMesh,RememBox3,RememBox2.x,RememBox2.y,RememBox2.z);
            break;
            //case IDC_HEMIS:
        case 10:
            m_Gen.CreateHemis(CurrentMesh,Remem,Radius1,nbSegHemis,OriginNg);
            break;
            //case IDC_SPHERE:
        case 4:
            m_Gen.CreateSphere(CurrentMesh,Remem,Radius1,nbSegSphere,OriginNg);
            break;
            //case IDC_GRID:
        case 3:
			{
				double sx=oX-dx;
				double sy=oY-dy;
				
				m_Gen.CreateGrid(CurrentMesh,Remem,sx,sy,nbSeg1Grid,nbSeg2Grid);
			}
            break;
            //case IDC_TORUS:
        case 8:
            m_Gen.CreateTorus(CurrentMesh,Remem,Radius1,Radius2,nbSeg1Torus,nbSeg2Torus,OriginNg);
            break;
            //case IDC_CYLINDER:
        case 5:
            m_Gen.CreateCyl(CurrentMesh,Remem,Radius1,Radius2,nbSeg1Cylinder,nbSeg2Cylinder,OriginNg);
            break;
            //case IDC_CONE:
        case 6:
            m_Gen.CreateCone(CurrentMesh,Remem,Radius2,Radius1,Radius3,nbSeg1Cone,nbSeg2Cone,OriginNg);
            break;
            //case IDC_TUBE:
        case 9:
            m_Gen.CreateTube(CurrentMesh,Remem,Radius1,Radius2,Radius3,nbSeg1Tube,nbSeg2Tube,OriginNg);
            break;
        case 11:
            //CurrentMesh->de
            break;
        case 12:
			CurrentPatch->IsPlanar(nbSeg1Patch,nbSeg2Patch,Remem,Vertex(oX-dx,oY-dy,0),rmX,rmY,1,1);
			CurrentPatch->Build(10);
			CurrentPatch->ComputeTexCoords(0,1,1,nbSeg1Patch,nbSeg2Patch);
            break;
		case 13: // complex stairs
			m_Gen.CreateStairs(CurrentMesh,RememBox3,Radius1,Radius2,Radius3,nbSegStairs);
			break;
		case 14: //simple stairs
			m_Gen.CreateStairsSimple(CurrentMesh,RememBox3,Radius1,Radius2,Radius3,nbSegStairs);
			break;
		case 15: // 3D grid
			{
				double sx=RememBox2.x,sy=RememBox2.y,sz=RememBox2.z;
				m_Gen.Create3DGrid(CurrentMesh,Remem,sx,sy,sz,nbSeg13DGrid,nbSeg23DGrid,nbSeg33DGrid);
			}
			break;

        }

		if (TypeEdit==12)
		{
			CurrentPatch->Update();
			if (mSelected)
			{

				m_Scene->SinglePatch(CurrentPatch,true);
			}
		}
		else
		if (TypeEdit==16)
		{

		}
		else
		{
			CurrentMesh->UpdateMesh();
			if (mSelected)
			{
				m_Scene->SingleMesh(CurrentMesh,true);
			}

		}
		if (TypeEdit!=12)
			ObjToUndo();
		else
			PatchToUndo();

		m_Scene->UpdateSmthSel();

		DrawViews();
	}
}