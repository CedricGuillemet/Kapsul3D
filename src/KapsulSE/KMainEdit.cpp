// KMainEdit.cpp: implementation of the CKMainEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kapsulse.h"
#include "KMainEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CKScene ClipBoard;
extern CKScenePlugin *GCurPlug;
extern int daButton;

extern CTVTestDlg	*m_DesksBrowser;
extern int m_TextureLayer;
extern CKLocalization loc;

extern CMainFrame* mainf;
extern int FunctionID;

extern bool bCentered;
extern bool bCrossing;
extern bool bSnap;

extern int iEditMode;

extern CKOption *KOption;
extern CKPluginManager *GKPlugins;
extern int FunctionSwitch;

bool bCopy;


///////////////////////////////////////////////////////////////////////////////
// Static Handles Cursor/functions

static const UINT CursorRes[3][10]={{IDC_POINTER_UPRIGHT,IDC_POINTER_UPLEFT,IDC_POINTER_UPRIGHT,
IDC_POINTER_UPLEFT,IDC_POINTER_SCALEUPDOWN,IDC_POINTER_SCALEUPDOWN,IDC_POINTER_LEFTRIGHT,IDC_POINTER_LEFTRIGHT,
IDC_POINTER_ROTATE,IDC_POINTER_MOVE},
{IDC_TAPERVERT,IDC_TAPERHORZ,IDC_TAPERVERT,IDC_TAPERHORZ,IDC_SQUIZHORZ,IDC_SQUIZHORZ,IDC_SQUIZVERT,IDC_SQUIZVERT,IDC_POINTER_ROTATE,IDC_POINTER_MOVE} ,
{IDC_POINTER_UPRIGHT,IDC_POINTER_UPLEFT,IDC_POINTER_UPRIGHT,IDC_POINTER_UPLEFT,
IDC_BENDHORZ,IDC_BENDHORZ,IDC_BENDVERT,IDC_BENDVERT,IDC_POINTER_ROTATE,IDC_POINTER_MOVE}};

static const UINT HandlesFn[3][10]={{EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_ROTATEBUF,EDIT_MOVEBUF},
{EDIT_TAPERBUF,EDIT_TAPERBUF,EDIT_TAPERBUF,EDIT_TAPERBUF,EDIT_SQUIZBUF,EDIT_SQUIZBUF,EDIT_SQUIZBUF,EDIT_SQUIZBUF,EDIT_ROTATEBUF,EDIT_MOVEBUF},
{EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_SCALEBUF,EDIT_BENDBUF,EDIT_BENDBUF,EDIT_BENDBUF,EDIT_BENDBUF,EDIT_ROTATEBUF,EDIT_MOVEBUF}};


///////////////////////////////////////////////////////////////////////////////
// Constructor/Destructor

IMPLEMENT_DYNCREATE(CKMainEdit,CKViewEdit)

CKMainEdit::CKMainEdit()
{

}

CKMainEdit::~CKMainEdit()
{

}

///////////////////////////////////////////////////////////////////////////////
// KMOUSEDOWN

void CKMainEdit::KMouseDown(int Button,int iX, int iY)
{
    bool daOk=true;
    bool HasSwapped=false;
    bool IdentEnable=true;

	X=iX;
	Y=iY;

    m_Button=Button;

	bCopy=((Button&MK_SHIFT)!=0);

    if (SetFocus()!=this) 
        return;

	UpdateHierarchie(m_Scene);
    CDeskDoc *tmpdoc = (CDeskDoc *) GetDocument();
	tmpdoc->SetModifiedFlag(true);

	SetCapture();

	if (m_Scene->SomeThingSel)
	{
		Vertex HandMin,HandMax;

		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
		{
			HandMax.x=(m_Scene->UVMaxSel.u*64);
			HandMax.y=-(m_Scene->UVMaxSel.v*64);
			HandMax.z=0;

			HandMin.x=(m_Scene->UVMinSel.u*64);
			HandMin.y=-(m_Scene->UVMinSel.v*64);
			HandMin.z=0;

			m_Scene->HandUV.CalcHandles(m_Scene,m_Scene->Active,HandMin,HandMax);
			HandleNb=m_Scene->HandUV.GetHandle(m_Scene,X,Y);			
		}
		else
		{
			HandMax=m_Scene->HookMaxSel;
			HandMin=m_Scene->HookMinSel;

			m_Scene->Hand3D.CalcHandles(m_Scene,m_Scene->Active,HandMin,HandMax);
			HandleNb=m_Scene->Hand3D.GetHandle(m_Scene,X,Y);
		}

		if (HandleNb!=0)
		{
			SvgFunctionID=FunctionID;
		
			FunctionID=HandlesFn[FunctionSwitch][HandleNb-1];
		}

	}

	if ((FunctionID==EDIT_PLUGINCREATION)||(FunctionID==EDIT_PLUGINPRIMITIVE ))
    {
        if (GCurPlug->CreatingStatus())
        {
            daOk=false;
        }
    }

    if (IsMoving)
    {
        daOk=false;
    }

    if (daOk)
    {
        if (!m_Scene->SetActive(X,Y))
        {
			DrawViews();
            HasSwapped=true;

			Vertex hui=m_Renderer->GetIsoCoord(X,Y,m_Scene->Active);
			//if (bSnap) hui.Snap(SnapVal);
			DoSnapping(hui);
        }
    }


    if(!HasSwapped)
    {
		if (Button&MK_RBUTTON)
        {
			OnRButtonDown(Button,CPoint(X,Y));
		}
		else
        if (Button&MK_LBUTTON)
        {
			OnLButtonDown(Button,CPoint(X,Y));
        }
		if (Button&MK_MBUTTON)
		{
			OnMButtonDown(Button,CPoint(X,Y));
		}
    }

    if ((FunctionID==EDIT_PLUGINCREATION)|| (FunctionID==EDIT_PLUGINPRIMITIVE))
    {
        if (GCurPlug->CreatingStatus())
        {
            IdentEnable=false;
        }
    }

    if (IsMoving)
    {
        IdentEnable=false;
    }
}

void CKMainEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_Scene->tmppos[m_Scene->Active]=m_Scene->ViewPos[m_Scene->Active];

	m_Scene->tmpViewSize[m_Scene->Active]=m_Scene->ViewSize[m_Scene->Active];
	m_Scene->TmpViewNg[m_Scene->Active]=m_Scene->ViewNg[m_Scene->Active];
	huitemp=m_Renderer->GetIsoCoord(point.x,point.y,m_Scene->Active);

	DoSnapping(huitemp);

	dx=point.x;
	dy=point.y;

	switch(FunctionID)
	{
		case EDIT_CLICKAPPLYMESH:
			ClickApplyTexMesh();
			break;

		case EDIT_CLICKAPPLYPOLY:
			ClickApplyTexPoly();
			break;

		case EDIT_MOVEVIEW:
			BeginMoveView();
			break;
		
		case EDIT_SELECTQUAD:
			IsMoving=true;
			break;

		case EDIT_ROTATEVIEW:
			BeginRotateView();
			break;

		case EDIT_SELECTCIRCLE:
			IsMoving=true;
			break;

		case EDIT_SELECTFENCE:
			ClickSelectFence();
			break;

		case EDIT_PLUGINPRIMITIVE:
		case EDIT_PLUGINCREATION:
			GCurPlug->LMouseDown(point.x,point.y,huitemp);
			IsMoving=GCurPlug->CreatingStatus();
			IsMoving=true;
			break;

		case EDIT_ZOOM:
			IsMoving=true;
			m_Scene->ActiveViewToUndo();
			break;

		case EDIT_REGIONFIT:
			IsMoving=true;
			m_Scene->ActiveViewToUndo();
			break;

		case EDIT_MOVEBUF:
			BeginMoveBuffer();
			break;

		case EDIT_ROTATEBUF:
			BeginRotateBuffer();
			break;

		case EDIT_SCALEBUF:
			BeginScaleBuffer();
			break;

		case EDIT_BENDBUF:
			BeginBendBuffer();
			break;

		case EDIT_TAPERBUF:
			BeginTaperBuffer();
			break;

		case EDIT_SQUIZBUF:
			BeginSquizBuffer();
			break;

		case EDIT_PUTAXIS:
			m_Scene->SetAxis(huitemp);
			DrawViews();
			break;
	}
}

void CKMainEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_Scene->tmppos[m_Scene->Active]=m_Scene->ViewPos[m_Scene->Active];

    m_Scene->tmpViewSize[m_Scene->Active]=m_Scene->ViewSize[m_Scene->Active];
    m_Scene->TmpViewNg[m_Scene->Active]=m_Scene->ViewNg[m_Scene->Active];
    huitemp=m_Renderer->GetIsoCoord(point.x,point.y,m_Scene->Active);

	DoSnapping(hui);

    dx=point.x;
    dy=point.y;

    switch(FunctionID)
    {
		case EDIT_CLICKAPPLYMESH:
			ClickRetrieveTexMesh();
			break;

		case EDIT_CLICKAPPLYPOLY:
			ClickRetrieveTexPoly();
			break;

		default:
			if (GCurPlug!=NULL)
			{
				if (GCurPlug->CreatingStatus())
				{
					GCurPlug->RMouseUp(point.x,point.y,huitemp);
					IsMoving=GCurPlug->CreatingStatus();
					IsMoving=true;
					DrawViews();
				}
				else
				{
					ShowContextMenu(point.x,point.y);
				}
			}
			else
			{
				ShowContextMenu(point.x,point.y);
			}
			break;
	}
}

void CKMainEdit::OnMButtonDown(UINT nFlags, CPoint point)
{
	SvgFunctionID=FunctionID;
	if (nFlags&MK_CONTROL)
	{
		if (nFlags&MK_SHIFT)
		{
			//iso rotate/move source
			FunctionID=EDIT_PAN3D2;

			m_Scene->ActiveViewToUndo();
		}
		else
		{
			//iso rotate/move source
			FunctionID=EDIT_ROTATEVIEW;

			m_Scene->ActiveViewToUndo();
		}
	}
	else
	if (nFlags&MK_SHIFT)
	{
		//iso rotate/move source
		FunctionID=EDIT_PAN3D;

		m_Scene->ActiveViewToUndo();
	}
	else
	{
		m_Scene->ActiveViewToUndo();

		// move target
		FunctionID=EDIT_MOVEVIEW;

		dx=point.x;
		dy=point.y;
		

		huitemp=m_Renderer->GetIsoCoord(point.x,point.y,m_Scene->Active);
		
		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
		{
			if (m_Scene->cam[m_Scene->Active]!=NULL)
			{
				m_Scene->cam[m_Scene->Active]->SetMousePos();
				m_Scene->cam[m_Scene->Active]->BeginMove();
			}
		}
		else
		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
		{
			m_Scene->Perspective[m_Scene->Active].SetMousePos();
			m_Scene->Perspective[m_Scene->Active].BeginMove();

			SetCapture();
		}
	}
	IsMoving=true;

	ClientToScreen(&point);
	ox=point.x;
    oy=point.y;
	dx=ox;
	dy=oy;

	CView::OnMButtonDown(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////
// KMOUSEMOVE

void CKMainEdit::KMouseMove(int Button, int iX, int iY)
{
	X=iX;
	Y=iY;
	m_Button=Button;

    //daButton=Button;

	// status bar
    hui=m_Renderer->GetIsoCoord(X,Y,m_Scene->Active);
	DoSnapping(hui);

	CalcHandles(m_Scene->Active);

	/*
	sprintf(temp,"X: %7.3f Y: %7.3f Z: %7.3f",hui.x,hui.y,hui.z);
	mainf->m_wndStatusBar.SetPaneText( 1, (const char*)temp);		
	*/
	SetXYZ(hui.x,hui.y,hui.z);

	int HandleNb=0;

	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
	{
		//m_Scene->HandUV.CalcHandles(m_Scene,m_Scene->Active);
		HandleNb=m_Scene->HandUV.GetHandle(m_Scene,X,Y);
	}
	else
	{
		if (m_Scene->SomeThingSel)
		{
			HandleNb=m_Scene->Hand3D.GetHandle(m_Scene,X,Y);
		}
	}
	int tmpnb=0;
	if (GCurPlug!=NULL)
	{
		tmpnb=GCurPlug->GetCursor(X,Y);
	}

	if (HandleNb==0)
	{
		if (tmpnb==0)
			SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_STANDARD)));
		else
			SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(CursorRes[0][tmpnb-1])));
	}
	else
		SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(CursorRes[FunctionSwitch][HandleNb-1])));


	//m_Hierar.
	m_DesksBrowser->m_Browser.m_Scene=m_Scene;


    if ((IsMoving)||(FunctionID==EDIT_PLUGINCREATION)||(FunctionID==EDIT_PLUGINPRIMITIVE))
    {
        switch(FunctionID)
        {
            case EDIT_MOVEVIEW:
				MoveView();
                break;

			case EDIT_PAN3D:
				Pan3D();
				break;

			case EDIT_PAN3D2:
				Pan3D2();
				break;

            case EDIT_SELECTQUAD:
				SelectQuad();
                break;

            case EDIT_SELECTCIRCLE:
                SelectCircle();
                break;

            case EDIT_SELECTFENCE:
                m_Scene->Sel->SetSegment(&hui);
                DrawViews();
                break;

            case EDIT_ROTATEVIEW:
                RotateView();
                break;

            case EDIT_ZOOM:
                Zoom();
                break;

            case EDIT_REGIONFIT:
				RegionFit();
                break;

			case EDIT_PLUGINPRIMITIVE:
            case EDIT_PLUGINCREATION:
                GCurPlug->MouseMove(X,Y,hui);
                if (GCurPlug->CreatingStatus()) 
				{
                    DrawViews();
				}
                break;

            case EDIT_MOVEBUF:
				MoveBuffer();
                break;

            case EDIT_ROTATEBUF:
				RotateBuffer();
                break;

			case EDIT_SCALEBUF:
				ScaleBuffer();
				break;

			case EDIT_BENDBUF:
				BendBuffer();
				break;

			case EDIT_TAPERBUF:
				TaperBuffer();
				break;

			case EDIT_SQUIZBUF:
				SquizBuffer();
				break;

            default:
                break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Mouse UP

void CKMainEdit::KMouseUp(int Button, int iX, int iY)
{
    Vertex hui,hui2,hui3,hui4,hui5;
    bool IdentEnable=true;
    daButton=Button;
    CDeskDoc *tmpdoc;

	X=iX;
	Y=iY;
	m_Button=Button;

	if (Button&MK_MBUTTON)
	{
		OnMButtonUp(Button,CPoint(X,Y));
		return;
	}

	ReleaseCapture();

    hui=m_Renderer->GetIsoCoord(X,Y,m_Scene->Active);

	DoSnapping(hui);

    if (IsMoving)
    {
        switch(FunctionID)
        {
			case EDIT_ZOOM:
			case EDIT_ROTATEVIEW:
				m_Scene->ActiveViewToCurrentRedo();
				IsMoving=false;
				break;

            case EDIT_MOVEVIEW:
				EndMoveView();
				break;

            case EDIT_SELECTFENCE:
                break;

            case EDIT_REGIONFIT:
                EndRegionFit();
                break;

			case EDIT_PLUGINPRIMITIVE:
            case EDIT_PLUGINCREATION:
                GCurPlug->LMouseUp(X,Y,huitemp);
                IsMoving=GCurPlug->CreatingStatus();
                IsMoving=false;
                tmpdoc = (CDeskDoc *) GetDocument();
                tmpdoc->SetModifiedFlag(TRUE);
                break;

			case EDIT_SELECTCIRCLE:
            case EDIT_SELECTQUAD:
				EndSelectCircleQuad();
                break;

			case EDIT_BENDBUF:
			case EDIT_TAPERBUF:
			case EDIT_SQUIZBUF:
			case EDIT_SCALEBUF:
			case EDIT_ROTATEBUF:
            case EDIT_MOVEBUF:
				EndStandardOps();
                break;

            default:
                IsMoving=false;
				break;
        }
    }

    if ((FunctionID==EDIT_PLUGINCREATION)||(FunctionID==EDIT_PLUGINPRIMITIVE))
    {
        if (GCurPlug->CreatingStatus())
            IdentEnable=false;
    }

    if (IsMoving)
        IdentEnable=false;
}

void CKMainEdit::OnLButtonUp(UINT nFlags, CPoint point)
{

}

void CKMainEdit::OnRButtonUp(UINT nFlags, CPoint point)
{

}

void CKMainEdit::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	{
		if (m_Scene->cam[m_Scene->Active]!=NULL)
			m_Scene->cam[m_Scene->Active]->EndDraw();
	}
	else
	{
		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
			m_Scene->Perspective[m_Scene->Active].EndDraw();

		ReleaseCapture();
	}
	IsMoving=false;

	m_Scene->ActiveViewToCurrentRedo();

	FunctionID=SvgFunctionID;
	CView::OnMButtonUp(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////
// Show Context Menu

void  CKMainEdit::ShowContextMenu(int iX,int iY)
{
    CKCamera *daCam;
    CKEntity *daEntity;
    CKPatch *daPatch;
    CKSkeleton *daSkel;
    CKShape *daShape;
    CKMesh *daObject;
    
	BCMenu ctx,*ctx2;
	POINT mypt;
	
	strcpy(TmpName,"");

    tmpPlugin=NULL;
    PropEnt=NULL;
    
    daCam=m_Scene->GetCamera(X,Y);
    if (daCam!=NULL)
    {
        strcpy(TmpName,daCam->Name);
        tmpPlugin=GKPlugins->EntProp;
        PropEnt=daCam;
		PropType=PLUGIN_CAMERA;
    }
    else
    {
        daShape=m_Scene->GetShape(X,Y);
        if (daShape!=NULL)
        {
            strcpy(TmpName,daShape->Name);
            tmpPlugin=GKPlugins->EntProp;
            PropEnt=daShape;
			PropType=PLUGIN_SHAPE;
        }
        else
        {
            daEntity=m_Scene->GetEntity(X,Y);
            if (daEntity!=NULL)
            {
                //strcpy(TmpName,daEntity->Name);
                tmpPlugin=GKPlugins->EntProp;
                PropEnt=daEntity;
				PropType=PLUGIN_ENTITY;
            }
            else
            {
				daPatch=m_Scene->GetPatch(X,Y);
				if (daPatch!=NULL)
				{
					strcpy(TmpName,daPatch->Name);
					tmpPlugin=GKPlugins->EntProp;
					PropEnt=daPatch;
					PropType=PLUGIN_PATCH;
				}
				else
				{
					daObject=m_Scene->GetMeshByTriangle(X,Y,false);
					if (daObject!=NULL)
					{
						strcpy(TmpName,daObject->Name);
						tmpPlugin=GKPlugins->EntProp;
						PropEnt=daObject;
						PropType=PLUGIN_MESH;
					}
					else
					{
						daSkel=m_Scene->GetSkeleton(X,Y);
						if (daSkel!=NULL)
						{
							strcpy(TmpName,daSkel->Name);
							tmpPlugin=GKPlugins->EntProp;
							PropEnt=daSkel;
							PropType=PLUGIN_SKELETON;
						}
					}
				}
            }
        }
    }
			
	ctx.LoadMenu(IDR_CONTEXT);
    ctx2=(BCMenu*)ctx.GetSubMenu(0);
	mypt.x=X;
	mypt.y=Y;
	ClientToScreen(&mypt);

    if (PropEnt==NULL)
    {
		ctx2->EnableMenuItem(ID_PROPERTIES,MF_DISABLED);

		MENUITEMINFO         mii;       
		ZeroMemory(&mii, sizeof(mii));       
		mii.cbSize = sizeof(mii);       
		mii.fMask = MIIM_TYPE | MIIM_STATE;       
		mii.fType = MFT_STRING;       
		mii.fState = MFS_ENABLED;       
		mii.dwTypeData = TmpName;
		
    }

	// Localization

	ctx2->ModifyODMenu(loc.GetString(112),ID_EDIT_CUT);
	ctx2->ModifyODMenu(loc.GetString(113),ID_EDIT_COPY);
	ctx2->ModifyODMenu(loc.GetString(114),ID_EDIT_PASTE);
	ctx2->ModifyODMenu(loc.GetString(164),ID_VIEW_RENDER_MAPPEDOUTLINED);
	ctx2->ModifyODMenu(loc.GetString(165),ID_VIEW_RENDERMODE_MAPPED);
	ctx2->ModifyODMenu(loc.GetString(166),ID__RENDER_FLATSHADED);
	ctx2->ModifyODMenu(loc.GetString(167),ID_VIEW_RENDERMODE_WIRE);
	ctx2->ModifyODMenu(loc.GetString(299),ID_PROPERTIES);
	ctx2->ModifyODMenu(loc.GetString(121),ID_EDIT_MOVEROTATESCALE);
	ctx2->ModifyODMenu(loc.GetString(122),ID_EDIT_MOVEROTATETAPERSQUIZ);
	ctx2->ModifyODMenu(loc.GetString(123),ID_EDIT_BEND);


	if (FunctionSwitch==0) ctx2->CheckMenuItem(ID_EDIT_MOVEROTATESCALE,MF_CHECKED);
	if (FunctionSwitch==1) ctx2->CheckMenuItem(ID_EDIT_MOVEROTATETAPERSQUIZ,MF_CHECKED);
	if (FunctionSwitch==2) ctx2->CheckMenuItem(ID_EDIT_BEND,MF_CHECKED);

    ctx2->TrackPopupMenu(0,mypt.x,mypt.y,this);
	DestroyMenu(*ctx2);

}


void CKMainEdit::CalcHandles(int Indice)
{
	Vertex HandMin,HandMax;

	if (m_Scene->ViewType[Indice]==VIEWTYPE_UV)
	{
		HandMax.x=(m_Scene->UVMaxSel.u*64);
		HandMax.y=-(m_Scene->UVMaxSel.v*64);
		HandMax.z=0;

		HandMin.x=(m_Scene->UVMinSel.u*64);
		HandMin.y=-(m_Scene->UVMinSel.v*64);
		HandMin.z=0;

		m_Scene->HandUV.CalcHandles(m_Scene,Indice,HandMin,HandMax);
	}
	else
	{
		HandMax=m_Scene->HookMaxSel;
		HandMin=m_Scene->HookMinSel;

		m_Scene->Hand3D.CalcHandles(m_Scene,Indice,HandMin,HandMax);
	}
}


BOOL CKMainEdit::KMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	if (!m_Scene->GetVIWheel())
	{
		m_Scene->ActiveViewToUndo();
		m_Scene->SetVIWheel(true);
	}

	if ((m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_PERSPECTIVE)&&(m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_CAMERA))
	{
		if (zDelta>0)
		{
			m_Scene->ViewSize[m_Scene->Active].x=m_Scene->ViewSize[m_Scene->Active].x*1.08f;
			m_Scene->ViewSize[m_Scene->Active].y=m_Scene->ViewSize[m_Scene->Active].y*1.08f;

			if (m_Scene->ViewSize[m_Scene->Active].x>MAX_ZOOM ) m_Scene->ViewSize[m_Scene->Active].x=MAX_ZOOM;
			if (m_Scene->ViewSize[m_Scene->Active].y>MAX_ZOOM ) m_Scene->ViewSize[m_Scene->Active].y=MAX_ZOOM;

			CalcHandles(m_Scene->Active);

			DrawViews();
		}
		else
		{
			m_Scene->ViewSize[m_Scene->Active].x=m_Scene->ViewSize[m_Scene->Active].x*0.92f;
			m_Scene->ViewSize[m_Scene->Active].y=m_Scene->ViewSize[m_Scene->Active].y*0.92f;
			CalcHandles(m_Scene->Active);

			DrawViews();	
		}
	}
	else
	{
	    if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	    {
		    if (m_Scene->cam[m_Scene->Active]!=NULL)
		    {
				if (zDelta>0)
					m_Scene->cam[m_Scene->Active]->Run(30);
				else
					m_Scene->cam[m_Scene->Active]->Run(-30);
                m_Scene->cam[m_Scene->Active]->SetCamera();
                DrawViews();
		    }
	    }
        else
		{
            if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
            {
				if (zDelta>0)
					m_Scene->Perspective[m_Scene->Active].Run(30);
				else
					m_Scene->Perspective[m_Scene->Active].Run(-30);
                m_Scene->Perspective[m_Scene->Active].SetCamera();
                DrawViews();
			}
		}
	}

	if (m_Scene->GetVIWheel())
	{
		m_Scene->ActiveViewToCurrentRedo();
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


///////////////////////////////////////////////////////////////////////////////
// Move View

void CKMainEdit::BeginMoveView()
{
	ox=X;
	oy=Y;
	IsMoving=true;
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	{

		if (m_Scene->cam[m_Scene->Active]!=NULL)
		{
			m_Scene->cam[m_Scene->Active]->SetMousePos();
			m_Scene->cam[m_Scene->Active]->BeginMove();
		}
	}
	else
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
	{

		m_Scene->Perspective[m_Scene->Active].SetMousePos();
		m_Scene->Perspective[m_Scene->Active].BeginMove();
		SetCapture();
	}
}

void CKMainEdit::MoveView()
{
	hui=hui-huitemp;
    if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
    {
        if (m_Scene->cam[m_Scene->Active]!=NULL)
        {
			mx = -X;
			my = -Y;
			m_Scene->cam[m_Scene->Active]->SetMouse(mx, my,640,400);
            DrawViews();
        }
    }
    else
    {
		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
		{
			POINT tmpop;
			tmpop.x=X;
			tmpop.y=Y;
			ClientToScreen(&tmpop);

			if ( ((oy-tmpop.y)!=0)||((ox-tmpop.x)!=0) )
			{

				m_Scene->Perspective[m_Scene->Active].angle_a=oy-tmpop.y;
				m_Scene->Perspective[m_Scene->Active].angle_b=ox-tmpop.x;

				m_Scene->Perspective[m_Scene->Active].SetCamera();
				DrawViews();

				SetCursorPos(ox,oy);
			}
		}
		else
		{
	        m_Scene->ViewPos[m_Scene->Active]-=hui;
	        DrawViews();
		}
    }
}

void CKMainEdit::EndMoveView()
{
	{
		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
		{
			if (m_Scene->cam[m_Scene->Active]!=NULL)
				m_Scene->cam[m_Scene->Active]->EndDraw();
		}
		else
		{
			if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
				m_Scene->Perspective[m_Scene->Active].EndDraw();
		}

		IsMoving=false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Pan3D

void CKMainEdit::Pan3D()
{
	hui=hui-huitemp;
	CKCamera *cam=NULL;

	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	{
		if (m_Scene->cam[m_Scene->Active]!=NULL)
		{
			cam=m_Scene->cam[m_Scene->Active];
		}
	}
	else
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
	{
		cam=&m_Scene->Perspective[m_Scene->Active];
	}

	if (cam!=NULL)
	{

		POINT tmpop;
		tmpop.x=X;
		tmpop.y=Y;
		ClientToScreen(&tmpop);

		if ( ((oy-tmpop.y)!=0)||((ox-tmpop.x)!=0) )
		{

			double angy=oy-tmpop.y;
			double angx=ox-tmpop.x;
			cam->angle_a=0;
			cam->angle_b=0;
			float fact=(angx/100.0f);//(float)RunAv.x/cam->Length)*KOption->MotionValue();
			cam->Strafe(fact);
			fact=(angy/100.0f)*cam->Length;
			cam->Source.z+=fact;
			cam->Dest.z+=fact;
			cam->SetCamera();
			DrawViews();
			SetCursorPos(ox,oy);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Pan3D 2

void CKMainEdit::Pan3D2()
{
	hui=hui-huitemp;

	CKCamera *cam=NULL;

	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	{
		if (m_Scene->cam[m_Scene->Active]!=NULL)
		{
			cam=m_Scene->cam[m_Scene->Active];
		}
	}
	else
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
	{
		cam=&m_Scene->Perspective[m_Scene->Active];
	}

	if (cam!=NULL)
	{

		POINT tmpop;
		tmpop.x=X;
		tmpop.y=Y;
		ClientToScreen(&tmpop);

		if ( ((oy-tmpop.y)!=0)||((ox-tmpop.x)!=0) )
		{

			double angy=oy-tmpop.y;
			double angx=ox-tmpop.x;
			cam->angle_a=0;
			cam->angle_b=0;
			float fact=(angx/100.0f);//(float)RunAv.x/cam->Length)*KOption->MotionValue();
			cam->Strafe(fact);
			fact=(angy/100.0f)*cam->Length;
			cam->Run(fact);
			cam->SetCamera();
			DrawViews();
			SetCursorPos(ox,oy);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Select Quad

void CKMainEdit::SelectQuad()
{
	hui2=m_Renderer->GetIsoCoord(dx,Y,m_Scene->Active);
	DoSnapping(hui2);

    hui3=m_Renderer->GetIsoCoord(X,dy,m_Scene->Active);
	DoSnapping(hui3);

    if (m_Scene->Sel!=NULL) delete m_Scene->Sel;
    m_Scene->Sel=new (CKShape)(NULL,NULL);
    m_Scene->Sel->IsQuad(huitemp,hui2,hui,hui3);
    //m_Renderer->RenderOne(m_Scene->Active);
    DrawViews();
}

///////////////////////////////////////////////////////////////////////////////
// Select Circle

void CKMainEdit::SelectCircle()
{
	double Length;
	int i;

	Length=Pythagore((X-dx),(Y-dy));
    for (i=0;i<100;i++)
	{
        CircleHui[i]=m_Renderer->GetIsoCoord((int)(dx+cos((i*PI)/50)*Length),(int)(dy+sin((i*PI)/50)*Length),m_Scene->Active);
		//if (bSnap) CircleHui[i].Snap(SnapVal);

	}

    delete m_Scene->Sel;
    m_Scene->Sel=new (CKShape)(NULL,NULL);
    m_Scene->Sel->IsCircle(100,CircleHui);

    //m_Renderer->RenderOne(m_Scene->Active);
    DrawViews();
}


///////////////////////////////////////////////////////////////////////////////
// End Select Circle/Quad

void CKMainEdit::EndSelectCircleQuad()
{
	bool tmpbt;
	UINT TypeSelqc;

    if ((!(m_Button&MK_CONTROL))&&(!(m_Button&MK_SHIFT)))
    {
		if (m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_UV)
		{
			m_Scene->UnSelectAll(false);

			m_Scene->DeleteBufVert();
		}
		else
		{
			m_Scene->UnSelectUV(false);
		}
    }

	tmpbt=(!(m_Button&MK_CONTROL));

	if ( (abs(X-dx)<KOption->Precision())&&(abs(Y-dy)<KOption->Precision()) )
	{
		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
		{
			m_Scene->SelectUV(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
		}
		else
		{
			switch (iEditMode)
			{
			case 1:
				m_Scene->SelectMesh(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
				m_Scene->SelectEntity(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
				m_Scene->SelectPatch(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
				m_Scene->SelectCam(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
				m_Scene->SelectShape(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
				break;
			case 2:
				m_Scene->SelectCam(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
				m_Scene->SelectEntity(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
				m_Scene->SelectPatch(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
				m_Scene->SelectMesh(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_FACE);
				m_Scene->SelectShape(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_FACE);
				break;
			case 3:
				m_Scene->SelectMesh(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
				m_Scene->SelectEntity(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
				m_Scene->SelectPatch(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
				m_Scene->SelectCam(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
				m_Scene->SelectShape(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
    			m_Scene->SingleSkel(X,Y,tmpbt);
				break;
			}
		}
	}
	else
	{
		TypeSelqc=((FunctionID==EDIT_SELECTQUAD)?SELECT_QUAD:SELECT_CIRCLE);

		if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
		{
			m_Scene->SelectUV(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
		}
		else
		{

			switch (iEditMode)
			{
			case 1:
				m_Scene->SelectMesh(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
				m_Scene->SelectCam(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
				m_Scene->SelectEntity(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
				m_Scene->SelectPatch(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
				m_Scene->SelectShape(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
				break;
			case 2:
				m_Scene->SelectMesh(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_FACE);
				m_Scene->SelectEntity(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
				m_Scene->SelectPatch(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
				m_Scene->SelectCam(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
				m_Scene->SelectShape(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_FACE);

				break;
			case 3:
				m_Scene->SelectMesh(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
				m_Scene->SelectCam(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
				m_Scene->SelectEntity(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
				m_Scene->SelectPatch(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
				m_Scene->SelectShape(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
				if (TypeSelqc==SELECT_QUAD)
				{
    				//m_Scene->QuadShape(dx,dy,X,Y,tmpbt,bCrossing);
    				m_Scene->QuadSkel(dx,dy,X,Y,tmpbt,bCrossing);
				}
				else
				{
    				//m_Scene->CircleShape(dx,dy,X,Y,tmpbt,bCrossing);
    				m_Scene->CircleSkel(dx,dy,X,Y,tmpbt,bCrossing);
				}
				break;
			}
		}
	}
	
	m_Scene->UpdateSmthSel();

    delete m_Scene->Sel;
    m_Scene->Sel=new (CKShape)(NULL,NULL);

	//DrawViews();
    DrawViews();
    IsMoving=false;

}

///////////////////////////////////////////////////////////////////////////////
// Click Select Fence

void CKMainEdit::ClickSelectFence()
{
	bool tmpbt;

	if (m_Scene->Collapse(m_Scene->Sel,(Vertex*)(&huitemp))!=NULL)
	{
		m_Scene->Sel->Close();
		
		if ((!(m_Button&MK_CONTROL))&&(!(m_Button&MK_SHIFT)))
		{
			m_Scene->UnSelectCamera(false);
			m_Scene->UnSelectMesh(false);
			m_Scene->UnSelectShape(false);
			m_Scene->UnSelectPatch(false);
			m_Scene->UnSelectEntity(false);
			m_Scene->UnSelectSkeleton(false);
			m_Scene->DeleteBufVert();
		}

		tmpbt=(!(m_Button&MK_CONTROL));

		switch (iEditMode)
		{
		case 1:
			m_Scene->SelectMesh(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
			m_Scene->SelectEntity(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
			m_Scene->SelectPatch(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
			m_Scene->SelectCam(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
			m_Scene->SelectShape(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
			m_Scene->SelectBone(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
			break;
		case 2:
			m_Scene->SelectMesh(0,0,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_FACE);
			m_Scene->SelectCam(0,0,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			m_Scene->SelectEntity(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			m_Scene->SelectPatch(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
			m_Scene->SelectShape(0,0,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			m_Scene->SelectBone(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
			break;
		case 3:
			m_Scene->SelectMesh(0,0,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			m_Scene->SelectCam(0,0,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			m_Scene->SelectEntity(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			m_Scene->SelectPatch(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			m_Scene->SelectShape(0,0,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			m_Scene->SelectBone(dx,dy,X,Y,m_Scene->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
			break;
		}

		if (m_Scene->Sel!=NULL) delete m_Scene->Sel;
		m_Scene->Sel=new (CKShape)(NULL,NULL);
		IsMoving=false;

		m_Scene->UpdateSmthSel();
		DrawViews();

	}
	else
	{
		if (m_Scene->Sel==NULL) m_Scene->Sel=new (CKShape)(NULL,NULL);

		if (m_Scene->Sel->Count==0)
			m_Scene->Sel->AddSegment(&huitemp);

		m_Scene->Sel->AddSegment(&huitemp);
		//m_Renderer->RenderOne(m_Scene->Active);
		DrawViews();
		IsMoving=true;
	}

}
///////////////////////////////////////////////////////////////////////////////
// Rotate Views

void CKMainEdit::BeginRotateView()
{
	ox=X;
	oy=Y;
	IsMoving=true;
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
	{
		/*

		if (m_Scene->cam[m_Scene->Active]!=NULL)
		{
			m_Scene->cam[m_Scene->Active]->SetMousePos();
			m_Scene->cam[m_Scene->Active]->BeginMove();
		}
		*/
		SetCapture();
	}
	else
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
	{
		/*

		m_Scene->Perspective[m_Scene->Active].SetMousePos();
		m_Scene->Perspective[m_Scene->Active].BeginMove();
		*/
		SetCapture();
	}
	m_Scene->ActiveViewToUndo();
}

void CKMainEdit::RotateView()
{
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)
    {
        if (m_Scene->cam[m_Scene->Active]!=NULL)
        {
			POINT tmpop;
			tmpop.x=X;
			tmpop.y=Y;
			ClientToScreen(&tmpop);

			if ( ((oy-tmpop.y)!=0)||((ox-tmpop.x)!=0) )
			{
				Vertex swp;
				swp=m_Scene->cam[m_Scene->Active]->Source;
				m_Scene->cam[m_Scene->Active]->Source=m_Scene->cam[m_Scene->Active]->Dest;
				m_Scene->cam[m_Scene->Active]->Dest=swp;

				m_Scene->cam[m_Scene->Active]->angle_a=oy-tmpop.y;
				m_Scene->cam[m_Scene->Active]->angle_b=ox-tmpop.x;

				m_Scene->cam[m_Scene->Active]->SetCamera();
				swp=m_Scene->cam[m_Scene->Active]->Source;
				m_Scene->cam[m_Scene->Active]->Source=m_Scene->cam[m_Scene->Active]->Dest;
				m_Scene->cam[m_Scene->Active]->Dest=swp;


				DrawViews();

				SetCursorPos(ox,oy);
			}
        }
    }
    else
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)
	{
		POINT tmpop;
		tmpop.x=X;
		tmpop.y=Y;
		ClientToScreen(&tmpop);

		if ( ((oy-tmpop.y)!=0)||((ox-tmpop.x)!=0) )
		{
			Vertex swp;
			swp=m_Scene->Perspective[m_Scene->Active].Source;
			m_Scene->Perspective[m_Scene->Active].Source=m_Scene->Perspective[m_Scene->Active].Dest;
			m_Scene->Perspective[m_Scene->Active].Dest=swp;

			m_Scene->Perspective[m_Scene->Active].angle_a=oy-tmpop.y;
			m_Scene->Perspective[m_Scene->Active].angle_b=ox-tmpop.x;

			m_Scene->Perspective[m_Scene->Active].SetCamera();
			swp=m_Scene->Perspective[m_Scene->Active].Source;
			m_Scene->Perspective[m_Scene->Active].Source=m_Scene->Perspective[m_Scene->Active].Dest;
			m_Scene->Perspective[m_Scene->Active].Dest=swp;


			DrawViews();

			SetCursorPos(ox,oy);
		}
	}
	else
    {
        daNgx=180;
        daNgx/=265;
        daNgx*=(X-dx);
        daNgy=180;
        daNgy/=250;
        daNgy*=(Y-dy);
        m_Scene->ViewNg[m_Scene->Active].z=m_Scene->TmpViewNg[m_Scene->Active].z+daNgx;
        m_Scene->ViewNg[m_Scene->Active].x=m_Scene->TmpViewNg[m_Scene->Active].x+daNgy;
        //m_Renderer->RenderOne(m_Scene->Active);
        DrawViews();
    }
}

///////////////////////////////////////////////////////////////////////////////
// Zoom

void CKMainEdit::Zoom()
{
	int tst;

	tst=(Y-dy);
    if (tst==0)
    {
        tst=1;
    }
    else
    {
        if (tst>0)
        {
            tst=pow(1.05,tst);
        }
        else
        {
            tst=1/(-tst);
        }
    }

    m_Scene->ViewSize[m_Scene->Active].x=m_Scene->tmpViewSize[m_Scene->Active].x*tst;
    m_Scene->ViewSize[m_Scene->Active].y=m_Scene->tmpViewSize[m_Scene->Active].y*tst;

	if (m_Scene->ViewSize[m_Scene->Active].x>MAX_ZOOM ) m_Scene->ViewSize[m_Scene->Active].x=MAX_ZOOM;
	if (m_Scene->ViewSize[m_Scene->Active].y>MAX_ZOOM ) m_Scene->ViewSize[m_Scene->Active].y=MAX_ZOOM;

    DrawViews();

}

///////////////////////////////////////////////////////////////////////////////
// Move Buffer

void CKMainEdit::BeginMoveBuffer()
{
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
	{
		IsMoving=true;
		dap->PlanOfView(m_Renderer,m_Scene->Active);
		/*
		sprintf(temp,"X: 0.00 Y: 0.00 ");
		mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
		*/
		m_Scene->HandUV.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
		m_Scene->GetNbSelectedMeshs();
		m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
	}
	else
	{
		// copy Meshes
		CopyMoving();

		IsMoving=true;
		dap->PlanOfView(m_Renderer,m_Scene->Active);
		/*
		sprintf(temp,"X: 0.00 Y: 0.00 Z: 0.00");
		mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
		*/
		m_Scene->Hand3D.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
		m_Scene->GetNbSelectedMeshs();
		m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
	}
}

void CKMainEdit::MoveBuffer()
{
	Vertex datr,datr2;
	m_Renderer->Project((Vertex*)&huitemp,(Vertex*)&datr,m_Scene->Active);
	m_Renderer->Project((Vertex*)&hui,(Vertex*)&datr2,m_Scene->Active);
	MYPOINT hugh;

	hugh.x=(hui-huitemp).x/64.0f;
	hugh.y=-(hui-huitemp).y/64.0f;

	MYPOINT rtr;

	rtr.x=datr2.x-datr.x;
	rtr.y=datr2.y-datr.y;

	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
	{
		/*
		sprintf(temp,"X: %7.2f Y: %7.2f ",(hui-huitemp).x,(hui-huitemp).y);
		mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
*/
		m_Scene->TranslateUVBuf(dap,hugh);
		m_Scene->UpdateTaged(PLUGIN_ALL);

		// don't know where to put it

		m_Scene->HandUV.TranslateHandles(rtr,m_Scene->Active);
		
	}
	else
	{
		/*
		sprintf(temp,"X: %7.2f Y: %7.2f Z: %7.2f",(hui-huitemp).x,(hui-huitemp).y,(hui-huitemp).z);
		mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
		*/

		m_Scene->TranslateBuf(dap,hui-huitemp);
		m_Scene->UpdateTaged(PLUGIN_ALL);
		
		UpdateTaggedByPlugin();
		/*
		// don't know where to put it

*/
		m_Scene->Hand3D.TranslateHandles(rtr,m_Scene->Active);

		for (int i=0;i<48;i++)
			m_Scene->Hand3D.DrawHanks[i]=m_Scene->Hand3D.Hanks[i]+(hui-huitemp);
	}

	DrawViews();
}

void CKMainEdit::UpdateTaggedByPlugin(void)
{
	if (GCurPlug!=NULL)
	{

		// entity
		for(CKEntity *daEntity=m_Scene->FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
			if (daEntity->Tag==1) 
				GCurPlug->UpdateStuff(daEntity,PLUGIN_ENTITY);

		// mesh
		for(CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
			if (daMesh->Tag==1) 
				GCurPlug->UpdateStuff(daMesh,PLUGIN_MESH);

		// shape
		for(CKShape *daShape=m_Scene->FirstShape;daShape!=NULL;daShape=daShape->Next)
			if (daShape->Tag==1) 
				GCurPlug->UpdateStuff(daShape,PLUGIN_SHAPE);

		// camera
		for(CKCamera *daCamera=m_Scene->FirstCam;daCamera!=NULL;daCamera=daCamera->Next)
			if (daCamera->Tag==1) 
				GCurPlug->UpdateStuff(daCamera,PLUGIN_CAMERA);

		// patch
		for(CKPatch *daPatch=m_Scene->FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
			if (daPatch->Tag==1) 
				GCurPlug->UpdateStuff(daPatch,PLUGIN_PATCH);

		// skeleton
		for(CKSkeleton *daSkel=m_Scene->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
			if (daSkel->Tag==1) 
				GCurPlug->UpdateStuff(daSkel,PLUGIN_SKELETON);
	}
}
///////////////////////////////////////////////////////////////////////////////
// Rotate Buffer

void CKMainEdit::BeginRotateBuffer()
{
	MYPOINT center;
	m_Renderer->Project((Vertex*)&m_Scene->Axis,(Vertex*)&Getng,m_Scene->Active);
	m_Renderer->Project((Vertex*)&huitemp,(Vertex*)&Getng2,m_Scene->Active);


	m_Scene->Hand3D.Get2DCenter(m_Scene->Active,center);
	Getng.x=center.x;
	Getng.y=center.y;

	ngl=ng(Getng.x,Getng.y,Getng2.x,Getng2.y);
	dap->PlanOfView(m_Renderer,m_Scene->Active);
	//SetCapture(hWndEdit);

	/*
	sprintf(temp,"Angle 0 degs");
	mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
	*/
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
	{
		m_Scene->HandUV.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
	}
	else
	{
		m_Scene->Hand3D.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
	}

	IsMoving=true;
	m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
}

void CKMainEdit::RotateBuffer()
{
	double tempng;
    m_Renderer->Project((Vertex*)&hui,(Vertex*)&Getng2,m_Scene->Active);

	tempng=-int(((ng(Getng.x,Getng.y,Getng2.x,Getng2.y)-ngl)*180)/PI);
    dap->MatrixRotateNormale(-((tempng*PI)/180));

	/*
	sprintf(temp,"Angle %d degs",(int)tempng);
	mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
	*/

	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
	{
		MYPOINT ctr;

		ctr.x=(m_Scene->UVMinSel.u+(m_Scene->UVMaxSel.u-m_Scene->UVMinSel.u)/2.0f);
		ctr.y=(m_Scene->UVMinSel.v+(m_Scene->UVMaxSel.v-m_Scene->UVMinSel.v)/2.0f);
		m_Scene->RotateUVBuf(dap,ctr,-((tempng*PI)/180));
		m_Scene->UpdateTaged(PLUGIN_ALL);

		//UpdateTaggedByPlugin();

		// don't know where to put it

		m_Scene->HandUV.RotateHandles((float)(tempng*2),m_Scene->Active);
	}
	else
	{
		Vertex ctr=(m_Scene->HookMinSel+(m_Scene->HookMaxSel-m_Scene->HookMinSel)/2.0f);
		m_Scene->RotateBuf(dap,ctr);
		m_Scene->UpdateTaged(PLUGIN_ALL);
		
		UpdateTaggedByPlugin();

		m_Scene->Hand3D.RotateHandles((float)tempng*2,m_Scene->Active);

		for (int i=0;i<48;i++)
			m_Scene->Hand3D.DrawHanks[i]=(dap->Rotate(m_Scene->Hand3D.Hanks[i]-ctr)+ctr);
	}

    DrawViews();
}

///////////////////////////////////////////////////////////////////////////////
// Scale Buffer

void CKMainEdit::BeginScaleBuffer()
{
	if (HandleNb==0) return;

	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
		m_Scene->HandUV.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
	else
	{
		m_Scene->Hand3D.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
	}

	dap->PlanOfView(m_Renderer,m_Scene->Active);
	IsMoving=true;

	/*
	sprintf(temp,"X: 100%% Y: 100%% Z: 100%%");
	mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
*/
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


	m_ScaleSvgSize.x=fabs(m_Scene->Hand3D.ta2DHandles[0].x-m_Scene->Hand3D.ta2DHandles[2].x);
	m_ScaleSvgSize.y=fabs(m_Scene->Hand3D.ta2DHandles[0].y-m_Scene->Hand3D.ta2DHandles[2].y);
	m_Scene->Axis=m_Renderer->GetIsoCoord(m_Scene->Hand3D.ta2DHandles[NewHand-1].x,m_Scene->Height-m_Scene->Hand3D.ta2DHandles[NewHand-1].y,m_Scene->Active);

	if (fabs(m_Scene->HookMinSel.x-m_Scene->Axis.x)<fabs(m_Scene->HookMaxSel.x-m_Scene->Axis.x))
		m_Scene->Axis.x=m_Scene->HookMinSel.x;
	else
		m_Scene->Axis.x=m_Scene->HookMaxSel.x;

	if (fabs(m_Scene->HookMinSel.y-m_Scene->Axis.y)<fabs(m_Scene->HookMaxSel.y-m_Scene->Axis.y))
		m_Scene->Axis.y=m_Scene->HookMinSel.y;
	else
		m_Scene->Axis.y=m_Scene->HookMaxSel.y;

	if (fabs(m_Scene->HookMinSel.z-m_Scene->Axis.z)<fabs(m_Scene->HookMaxSel.z-m_Scene->Axis.z))
		m_Scene->Axis.z=m_Scene->HookMinSel.z;
	else
		m_Scene->Axis.z=m_Scene->HookMaxSel.z;

	
	
	m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
}

void CKMainEdit::ScaleBuffer()
{
	if ((fabs(dap->pX.x)>0.0001)&&(fabs(dap->pY.y)>0.0001))
	{
		tlng.x=fabs(m_Scene->HookMaxSel.x-m_Scene->HookMinSel.x);
		tlng.y=fabs(m_Scene->HookMaxSel.y-m_Scene->HookMinSel.y);
	}
	else
	if ((fabs(dap->pX.y)>0.0001)&&(fabs(dap->pY.z)>0.0001))
	{
		tlng.x=fabs(m_Scene->HookMaxSel.y-m_Scene->HookMinSel.y);
		tlng.y=fabs(m_Scene->HookMaxSel.z-m_Scene->HookMinSel.z);
	}
	if ((fabs(dap->pX.x)>0.0001)&&(fabs(dap->pY.z)>0.0001))
	{
		tlng.x=fabs(m_Scene->HookMaxSel.x-m_Scene->HookMinSel.x);
		tlng.y=fabs(m_Scene->HookMaxSel.z-m_Scene->HookMinSel.z);
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


	if (m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_UV)
	if (bSnap)
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

	if (m_Button&MK_CONTROL) 
	{
		ScaleVal.y=ScaleVal.x;
		if (m_Button&MK_SHIFT)
		{
			ScaleVal.z=ScaleVal.x;
		}
	}

	//sprintf(temp,"X: %5.2f%% Y: %5.2f%% Z: %d%%",(ScaleVal.x*100.0f),(ScaleVal.y*100.0f),(int)(ScaleVal.z*100));
	/*
	sprintf(temp,"X: %5.2f  Y: %5.2f",(tlng.x*ScaleVal.x),(tlng.y*ScaleVal.y));
	mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
	*/

	dap->ScaleMatrix();

	
	if (m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_UV)
	{

		m_Scene->ScaleBuf(dap,m_Scene->Axis,ScaleVal);
		m_Scene->UpdateTaged(PLUGIN_ALL);
		
		MYPOINT scvr;
		scvr.x=ScaleVal.x;
		scvr.y=ScaleVal.y;

		UpdateTaggedByPlugin();

		m_Scene->Hand3D.ScaleHandles(NewHand-1,scvr,m_Scene->Active);

		for (int i=0;i<48;i++)
			m_Scene->Hand3D.DrawHanks[i]=(dap->Scale(m_Scene->Hand3D.Hanks[i]-m_Scene->Axis,ScaleVal)+m_Scene->Axis);
		
	}
	else
	{
		MYPOINT hugh;
/*
		hugh.x=(hui-huitemp).x/64.0f;
		hugh.y=-(hui-huitemp).y/64.0f;
		*/
		hugh.x=ScaleVal.x;
		hugh.y=ScaleVal.y;

		MYPOINT ctr;

		if (m_ScaleMask.x==1)
			ctr.x=m_Scene->UVMaxSel.u;
		if (m_ScaleMask.x==-1)
			ctr.x=m_Scene->UVMinSel.u;

		if (m_ScaleMask.y==1)
			ctr.y=m_Scene->UVMaxSel.v;
		if (m_ScaleMask.y==-1)
			ctr.y=m_Scene->UVMinSel.v;

		m_Scene->ScaleUVBuf(dap,ctr,hugh);
		m_Scene->UpdateTaged(PLUGIN_ALL);
		{
			MYPOINT scvr;
			scvr.x=ScaleVal.x;
			scvr.y=ScaleVal.y;

			m_Scene->HandUV.ScaleHandles(NewHand-1,scvr,m_Scene->Active);
		}
	}
	DrawViews();
}

///////////////////////////////////////////////////////////////////////////////
// Bend Buffer

void CKMainEdit::BeginBendBuffer()
{
	m_Scene->Hand3D.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
	switch(HandleNb)
	{
	case 8:
		NewHand=2;
		NewHand2=1;
		m_Sens=0;
		m_ScaleMask.y=1;
		break;
	case 7:
		NewHand=3;
		NewHand2=4;
		m_Sens=2;
		m_ScaleMask.y=-1;
		break;
	case 6:
		m_Sens=1;
		NewHand=1;
		NewHand2=4;
		m_ScaleMask.x=1;
		break;
	case 5:
		m_Sens=3;
		NewHand=2;
		NewHand2=3;
		m_ScaleMask.x=-1;
		break;
	}
	IsMoving=true;
	m_Scene->Axis=m_Renderer->GetIsoCoord(m_Scene->Hand3D.ta2DHandles[NewHand-1].x,m_Scene->Height-m_Scene->Hand3D.ta2DHandles[NewHand-1].y,m_Scene->Active);
	m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
}

void CKMainEdit::BendBuffer()
{
	int tmphand;
	double dang;
	double dang2;

	if (m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_UV)
	{

		if ((m_Sens&1)==0)
		{
			dang=(m_ScaleMask.y*(Y-dy))/20.0f;
			
			
			
			if (dang<0)
			{
				tmphand=NewHand;
				if (m_Sens==2) tmphand=NewHand2;
			}
			else
			{
				tmphand=NewHand2;
				if (m_Sens==2) tmphand=NewHand;
				dang=dang+PI;
			}
			if (dang>=(2*PI)) dang=((2*PI)-0.01f);
			if (dang<=(-PI)) dang=((-PI)+0.01f);

			m_Scene->Axis=m_Renderer->GetIsoCoord(m_Scene->Hand3D.ta2DHandles[tmphand-1].x,m_Scene->Height-m_Scene->Hand3D.ta2DHandles[tmphand-1].y,m_Scene->Active);
			
			dang2=-dang;

			if (dang2>0) dang2+=PI;


			m_Scene->BendBuf(dang,1,m_Scene->Hand3D.ta2DHandles[4],m_Scene->Hand3D.ta2DHandles[2],m_Scene->Hand3D.ta2DHandles[tmphand-1]);
			m_Scene->UpdateTaged(PLUGIN_ALL);

			UpdateTaggedByPlugin();

			m_Scene->Hand3D.BendBuf(tmphand-1,dang2,1);

			/*
			sprintf(temp,"Angle %5.2f degs",dang);
			mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);	
			*/
		}
		else
		{
			dang=(m_ScaleMask.x*(X-dx))/20.0f;
						
			if (dang<0)
			{
				tmphand=NewHand;
				if (m_Sens==3) tmphand=NewHand2;
			}
			else
			{
				tmphand=NewHand2;
				if (m_Sens==3) tmphand=NewHand;
				dang=dang+PI;
			}
			if (dang>=(2*PI)) dang=((2*PI)-0.01f);
			if (dang<=(-PI)) dang=((-PI)+0.01f);

			m_Scene->Axis=m_Renderer->GetIsoCoord(m_Scene->Hand3D.ta2DHandles[tmphand-1].x,m_Scene->Height-m_Scene->Hand3D.ta2DHandles[tmphand-1].y,m_Scene->Active);
			
			dang2=-dang;

			if (dang2>0) dang2+=PI;


			m_Scene->BendBuf(dang,0,m_Scene->Hand3D.ta2DHandles[4],m_Scene->Hand3D.ta2DHandles[2],m_Scene->Hand3D.ta2DHandles[tmphand-1]);
			m_Scene->UpdateTaged(PLUGIN_ALL);

			
			m_Scene->Hand3D.BendBuf(tmphand-1,dang2,0);

			/*
			sprintf(temp,"Angle %5.2f degs",dang);
			mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
			*/
		}
			
		CKPlan *Dap;

		Dap=new CKPlan();
		Dap->PlanOfView(m_Scene->m_Renderer,m_Scene->Active);
		Dap->ScaleMatrix(false);
		MYPOINT tmp;
		double ngr,ngb;
		
		ngb=dang;
		ngb-=PI;
		ngb=fmod(ngb,PI);

		for (int i=0;i<48;i++)
		{
			tmp=m_Scene->Get2D(m_Scene->Hand3D.Hanks[i]);

			if (!(m_Sens&1))
				ngr=((tmp.x-m_Scene->Hand3D.ta2DHandles[tmphand-1].x)/(m_Scene->Hand3D.ta2DHandles[2].x-m_Scene->Hand3D.ta2DHandles[tmphand-1].x))*ngb;
			else
				ngr=((tmp.y-m_Scene->Hand3D.ta2DHandles[tmphand-1].y)/(m_Scene->Hand3D.ta2DHandles[2].y-m_Scene->Hand3D.ta2DHandles[tmphand-1].y))*ngb;

			Dap->MatrixRotateNormale(ngr);

			m_Scene->Hand3D.DrawHanks[i]=(Dap->Rotate((m_Scene->Hand3D.Hanks[i]-m_Scene->Axis))+m_Scene->Axis);
		}

		delete Dap;
	}
	DrawViews();
}

///////////////////////////////////////////////////////////////////////////////
// Taper Buffer

void CKMainEdit::BeginTaperBuffer()
{
	m_Scene->Hand3D.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
	switch(HandleNb)
	{
	case 4:
		NewHand=6;
		m_Sens=1;
		m_ScaleMask.x=1;
		break;
	case 2:
		NewHand=5;
		m_Sens=1;
		m_ScaleMask.x=-1;
		break;
	case 1:
		m_Sens=0;
		NewHand=8;
		m_ScaleMask.y=1;
		break;
	case 3:
		m_Sens=0;
		NewHand=7;
		m_ScaleMask.y=-1;
		break;
	}
	IsMoving=true;
	m_Scene->Axis=m_Renderer->GetIsoCoord(m_Scene->Hand3D.ta2DHandles[NewHand-1].x,m_Scene->Height-m_Scene->Hand3D.ta2DHandles[NewHand-1].y,m_Scene->Active);
	m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
}

void CKMainEdit::TaperBuffer()
{
	float Factor;

	if (m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_UV)
	{
		MYPOINT ctr;

		ctr.x=(m_Scene->UVMinSel.u+(m_Scene->UVMaxSel.u-m_Scene->UVMinSel.u)/2.0f);
		ctr.y=(m_Scene->UVMinSel.v+(m_Scene->UVMaxSel.v-m_Scene->UVMinSel.v)/2.0f);

		if (m_Sens==0)
		{
			Factor=m_ScaleMask.y*(dy-Y)/2;
			m_Scene->TaperBuf(Factor,m_Sens,m_Scene->Hand3D.ta2DHandles[4],m_Scene->Hand3D.ta2DHandles[2],m_Scene->Hand3D.ta2DHandles[NewHand-1]);
			m_Scene->Hand3D.TaperBuf(NewHand-1,m_ScaleMask.y*(Y-dy)/2,m_Sens);

			/*
			sprintf(temp,"Factor %5.2f ",m_ScaleMask.y*(dy-Y)/2);
			mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
			*/

			m_Scene->UpdateTaged(PLUGIN_ALL);

			UpdateTaggedByPlugin();
		}
		else
		{
			Factor=m_ScaleMask.x*(dx-X);
			m_Scene->TaperBuf(Factor,m_Sens,m_Scene->Hand3D.ta2DHandles[4],m_Scene->Hand3D.ta2DHandles[2],m_Scene->Hand3D.ta2DHandles[NewHand-1]);
			m_Scene->Hand3D.TaperBuf(NewHand-1,m_ScaleMask.x*(dx-X),m_Sens);

			/*
			sprintf(temp,"Factor %5.2f ",m_ScaleMask.x*(dx-X));
			mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
			*/

			m_Scene->UpdateTaged(PLUGIN_ALL);

			UpdateTaggedByPlugin();

			
		}
	}
	//MYPOINT *ptrcnt=&m_Scene->Hand3D.ta2DHandles[NewHand-1];
	Vertex tmpr;
	MYPOINT tmp;
	//MYPOINT dif;

	CKPlan *Dap;

	Dap=new CKPlan();
	Dap->PlanOfView(m_Scene->m_Renderer,m_Scene->Active);
    Dap->ScaleMatrix(false);


	for (int i=0;i<48;i++)
	{
        tmp=m_Scene->Get2D(m_Scene->Hand3D.Hanks[i]);


        tmpr.x=0;
        tmpr.y=0;
        tmpr.z=0;

        // right deform
		if (m_Sens==1)
			tmpr.x=((tmp.y-m_Scene->Hand3D.ta2DHandles[NewHand-1].y)/(m_Scene->Hand3D.ta2DHandles[2].y-m_Scene->Hand3D.ta2DHandles[4].y))*Factor;
		else
			tmpr.y=((tmp.x-m_Scene->Hand3D.ta2DHandles[NewHand-1].x)/(m_Scene->Hand3D.ta2DHandles[2].x-m_Scene->Hand3D.ta2DHandles[4].x))*Factor;

		Vertex ptx=Dap->pX*tmpr.x;
		Vertex pty=Dap->pY*tmpr.y;

		m_Scene->Hand3D.DrawHanks[i]=m_Scene->Hand3D.Hanks[i]+ptx+pty;
	}

	delete Dap;

	DrawViews();
}

///////////////////////////////////////////////////////////////////////////////
// Taper Buffer

void CKMainEdit::BeginSquizBuffer()
{
	m_Scene->Hand3D.CalculateHandles=false;	// don't recalculate handles on draw. Let the operation (move,scale,...) do the work
	switch(HandleNb)
	{
	case 8:
		NewHand=7;
		m_Sens=0;
		m_ScaleMask.x=1;
		break;
	case 7:
		NewHand=8;
		m_Sens=0;
		m_ScaleMask.x=-1;
		break;
	case 6:
		m_Sens=1;
		NewHand=5;
		m_ScaleMask.y=1;
		break;
	case 5:
		m_Sens=1;
		NewHand=6;
		m_ScaleMask.y=1;
		break;
	}
	IsMoving=true;
	m_Scene->Axis=m_Renderer->GetIsoCoord(m_Scene->Hand3D.ta2DHandles[NewHand-1].x,m_Scene->Height-m_Scene->Hand3D.ta2DHandles[NewHand-1].y,m_Scene->Active);
	m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToBeforeUndo("KAPSUL.DLL",UNDO_MODIFY);
}

void CKMainEdit::SquizBuffer()
{
	float Factor;

	CKPlan *Dap;

	Dap=new CKPlan();
	Dap->PlanOfView(m_Scene->m_Renderer,m_Scene->Active);
    Dap->ScaleMatrix(false);



	if (m_Scene->ViewType[m_Scene->Active]!=VIEWTYPE_UV)
	{
		if (m_Sens==0)
		{
			Factor=(dy-Y)/50.0f;
			m_Scene->SquizBuf(Factor,1,m_Scene->Hand3D.ta2DHandles[4],m_Scene->Hand3D.ta2DHandles[2],m_Scene->Hand3D.ta2DHandles[NewHand-1]);
			m_Scene->Hand3D.SquizBuf(NewHand-1,(dy-Y)/50.0f,1);
			m_Scene->UpdateTaged(PLUGIN_ALL);

			UpdateTaggedByPlugin();
		
			/*
			sprintf(temp,"Factor %5.2f ",((dy-Y)/50.0f)+1);
			mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
			*/

		}
		else
		{
			Factor=(dx-X)/50.0f;
			m_Scene->SquizBuf((dx-X)/50.0f,0,m_Scene->Hand3D.ta2DHandles[4],m_Scene->Hand3D.ta2DHandles[2],m_Scene->Hand3D.ta2DHandles[NewHand-1]);
			m_Scene->Hand3D.SquizBuf(NewHand-1,(dx-X)/50.0f,0);
			m_Scene->UpdateTaged(PLUGIN_ALL);

			UpdateTaggedByPlugin();

			/*
			sprintf(temp,"Factor %5.2f ",((dx-X)/50.0f)+1);
			mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
			*/
			
		}
	}

	MYPOINT *ptrcnt=&m_Scene->Hand3D.ta2DHandles[NewHand-1];
	Vertex tmpr;
	MYPOINT tmp;
	MYPOINT dif;

	dif.x=m_Scene->Hand3D.ta2DHandles[2].x-m_Scene->Hand3D.ta2DHandles[4].x;
	dif.y=m_Scene->Hand3D.ta2DHandles[2].y-m_Scene->Hand3D.ta2DHandles[4].y;

	for (int i=0;i<48;i++)
	{
		
        tmpr.x=1;
        tmpr.y=1;
        tmpr.z=1;

		tmp=m_Scene->Get2D(m_Scene->Hand3D.Hanks[i]);

		if (m_Sens!=0)
		{
			tmpr.x=(((tmp.y-ptrcnt->y)/dif.y)*Factor)+1.0f;
		}
		else
		{
			tmpr.y=(((tmp.x-ptrcnt->x)/dif.x)*Factor)+1.0f;
		}

		m_Scene->Hand3D.DrawHanks[i]=(Dap->Scale((m_Scene->Hand3D.Hanks[i]-m_Scene->Axis),tmpr)+m_Scene->Axis);
	}
	delete Dap;

	DrawViews();
}

///////////////////////////////////////////////////////////////////////////////
// End Standard Ops

void CKMainEdit::EndStandardOps()
{
	m_Scene->UpdateUVBuf();
	m_Scene->UpdateBuf();
	m_Scene->Hand3D.CalculateHandles=true;
	m_Scene->HandUV.CalculateHandles=true;
	
	/*
	sprintf(temp,"");
	mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
	*/
	
	ReleaseCapture();
	IsMoving=false;
	
	CDeskDoc *tmpdoc = (CDeskDoc *) GetDocument();
	tmpdoc = (CDeskDoc *) GetDocument();
	tmpdoc->SetModifiedFlag(TRUE);
	FunctionID=0;
	// update min Max
	m_Scene->UpdateSmthSel();
	m_Scene->UpdateMinMaxUVBuf();
	
	FunctionID=SvgFunctionID;
	//m_Scene->GetNbSelectedMeshs();
	m_Scene->SetSelectedToAfterUndoNoADD();
	DrawViews();
}

///////////////////////////////////////////////////////////////////////////////
// Region Fit

void CKMainEdit::RegionFit()
{
	hui2=m_Renderer->GetIsoCoord(dx,Y,m_Scene->Active);
	DoSnapping(hui2);
	hui3=m_Renderer->GetIsoCoord(X,dy,m_Scene->Active);
	DoSnapping(hui3);

	delete m_Scene->Sel;
	m_Scene->Sel=new (CKShape)(NULL,NULL);
	m_Scene->Sel->IsQuad(huitemp,hui2,hui,hui3);
	DrawViews();
}

void CKMainEdit::EndRegionFit()
{
	hui2=m_Renderer->GetIsoCoord(X,dy,m_Scene->Active);
	DoSnapping(hui2);
	//m_Scene->ViewPos[m_Scene->Active]=(hui+((huitemp-hui)/2));
	m_Scene->ViewPos[m_Scene->Active]=huitemp;
	m_Scene->ViewPos[m_Scene->Active]-=hui;
	m_Scene->ViewPos[m_Scene->Active]/=2;
	m_Scene->ViewPos[m_Scene->Active]+=hui;

	// en x
	hui3.x=Pythagore3D(huitemp,hui2);
	// en y
	hui3.y=Pythagore3D(hui2,hui);

	if ((hui3.x/m_Scene->ViewEnd[m_Scene->Active].x)>(hui3.y/m_Scene->ViewEnd[m_Scene->Active].y))
	{
		hui3.x/=2;
		hui3.x*=1.1f;
		m_Scene->ViewSize[m_Scene->Active]=hui3;
	}
	else
	{
		hui3.x=m_Scene->ViewEnd[m_Scene->Active].x;
		hui3.x/=m_Scene->ViewEnd[m_Scene->Active].y;
		hui3.x*=hui3.y;
		hui3.x/=2;
		hui3.x*=1.1f;
		m_Scene->ViewSize[m_Scene->Active]=hui3;
	}

	delete m_Scene->Sel;
	m_Scene->Sel=new (CKShape)(NULL,NULL);
	IsMoving=false;
	m_Scene->ActiveViewToCurrentRedo();
	DrawViews();
}

///////////////////////////////////////////////////////////////////////////////
// Click Tex Mesh

void CKMainEdit::ClickApplyTexMesh()
{
	if (!m_DesksBrowser->m_Browser.m_Texture.IsEmpty())
	{
		int FaceNb;
		CKMesh *MeshSel=m_Scene->GetMeshByTriangle(X,Y,false,&FaceNb);
		if (MeshSel!=NULL)
		{
			// apply object
			CKTexture *datex=m_Scene->AddTex(m_DesksBrowser->m_Browser.m_Texture);
			datex->Type=TEXTURE_FILE;
			datex->Load();
			MeshSel->ApplyTexture(datex,(m_TextureLayer-1));
		}
		else
		{
			// test path
			CKPatch *PatchSel=m_Scene->GetPatchByTriangle(X,Y,false);
			if (PatchSel!=NULL)
			{
				CKTexture *datex=m_Scene->AddTex(m_DesksBrowser->m_Browser.m_Texture);
				datex->Type=TEXTURE_FILE;
				datex->Load();
				PatchSel->ApplyTexture(datex,(m_TextureLayer-1));
			}
		}
	}
}

void CKMainEdit::ClickRetrieveTexMesh()
{
	int FaceNb;
	CKMesh *MeshSel=m_Scene->GetMeshByTriangle(X,Y,false,&FaceNb);
	if (MeshSel!=NULL)
	{
		CString TexName;
		switch (m_TextureLayer)
		{
			case 1:
				if (MeshSel->Tex1==NULL)
					TexName="NoTexture";
				else
					TexName=MeshSel->Tex1->FileName;
				break;
			case 2:
				if (MeshSel->Tex2==NULL)
					TexName="NoTexture";
				else
					TexName=MeshSel->Tex2->FileName;
				break;
			case 3:
				if (MeshSel->Tex3==NULL)
					TexName="NoTexture";
				else
					TexName=MeshSel->Tex3->FileName;
				break;
			case 4:
				if (MeshSel->Tex4==NULL)
					TexName="NoTexture";
				else
					TexName=MeshSel->Tex4->FileName;
				break;
		}

		if (TexName=="NoTexture")
		{
			MessageBox("No texture on this layer.","Texture info",MB_OK|MB_ICONINFORMATION);
		}
		else
		if (TexName=="DefaultTexture")
		{
			MessageBox("Cannot retrieve default texture.","Texture info",MB_OK|MB_ICONINFORMATION);
		}
		else
		{
			switch (m_TextureLayer)
			{
			case 1:
				m_DesksBrowser->m_Browser.SelectTexture(MeshSel->Tex1->FileName);
				break;
			case 2:
				m_DesksBrowser->m_Browser.SelectTexture(MeshSel->Tex2->FileName);
				break;
			case 3:
				m_DesksBrowser->m_Browser.SelectTexture(MeshSel->Tex3->FileName);
				break;
			case 4:
				m_DesksBrowser->m_Browser.SelectTexture(MeshSel->Tex4->FileName);
				break;
			}
		}
	}
	else
	{
		// test patch
		CKPatch *PatchSel=m_Scene->GetPatchByTriangle(X,Y,false);
		if (PatchSel!=NULL)
		{
			CString TexName;
			switch (m_TextureLayer)
			{
				case 1:
					if (PatchSel->Tex1==NULL)
						TexName="NoTexture";
					else
						TexName=PatchSel->Tex1->FileName;
					break;
				case 2:
					if (PatchSel->Tex2==NULL)
						TexName="NoTexture";
					else
						TexName=PatchSel->Tex2->FileName;
					break;
				case 3:
					if (PatchSel->Tex3==NULL)
						TexName="NoTexture";
					else
						TexName=PatchSel->Tex3->FileName;
					break;
				case 4:
					if (PatchSel->Tex4==NULL)
						TexName="NoTexture";
					else
						TexName=PatchSel->Tex4->FileName;
					break;
			}
			if (TexName=="NoTexture")
			{
				MessageBox("No texture on this layer.","Texture info",MB_OK|MB_ICONINFORMATION);
			}
			else
			if (TexName=="DefaultTexture")
			{
				MessageBox("Cannot retrieve default texture.","Texture info",MB_OK|MB_ICONINFORMATION);
			}
			else
			{
				switch (m_TextureLayer)
				{
				case 1:
					m_DesksBrowser->m_Browser.SelectTexture(PatchSel->Tex1->FileName);
					break;
				case 2:
					m_DesksBrowser->m_Browser.SelectTexture(PatchSel->Tex2->FileName);
					break;
				case 3:
					m_DesksBrowser->m_Browser.SelectTexture(PatchSel->Tex3->FileName);
					break;
				case 4:
					m_DesksBrowser->m_Browser.SelectTexture(PatchSel->Tex4->FileName);
					break;
				}
			}
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////
// Click Retrieve Tex Poly

void CKMainEdit::ClickApplyTexPoly()
{
	if (!m_DesksBrowser->m_Browser.m_Texture.IsEmpty())
	{
		int FaceNb;
		CKMesh *MeshSel=m_Scene->GetMeshByTriangle(X,Y,false,&FaceNb);
		if (MeshSel!=NULL)
		{
			// apply texture
			CKTexture *datex=m_Scene->AddTex(m_DesksBrowser->m_Browser.m_Texture);
			datex->Type=TEXTURE_FILE;
			datex->Load();
			MeshSel->pl[FaceNb].Maps[(m_TextureLayer-1)]=datex;
		}
	}
}

void CKMainEdit::ClickRetrieveTexPoly()
{
	int FaceNb;
	CKMesh *MeshSel=m_Scene->GetMeshByTriangle(X,Y,false,&FaceNb);
	if (MeshSel!=NULL)
	{
		/*
		// apply texture
		CKTexture *datex=m_Scene->AddTex(m_DesksBrowser->m_Browser.m_Texture);
		datex->Type=TEXTURE_FILE;
		datex->Load();
		MeshSel->pl[FaceNb].Maps[(m_TextureLayer-1)]=datex;
		*/

		if (MeshSel->pl[FaceNb].Maps[(m_TextureLayer-1)]->FileName=="DefaultTexture")
		{
			MessageBox("Cannot retrieve default texture.","Texture info",MB_OK|MB_ICONINFORMATION);
		}
		else
		{
			m_DesksBrowser->m_Browser.SelectTexture(MeshSel->pl[FaceNb].Maps[(m_TextureLayer-1)]->FileName);
		}
	}
}

void CKMainEdit::DoSnapping(Vertex &toSnap)
{
	if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV)
	{
		// Snap to 1
		toSnap.x=(int)toSnap.x;
		toSnap.y=(int)toSnap.y;
		toSnap.z=(int)toSnap.z;
	}
	else
	if ((bSnap)&&(FunctionID!=EDIT_MOVEVIEW)) 
	{
		// snap to normal snap value
		toSnap.Snap(SnapVal);
	}
}

void CKMainEdit::CopyMoving()
{
	if (bCopy)
	{
		for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			if (daMesh->Selected)
			{
				m_Scene->AddMesh()->IsCopyOf(daMesh);
			}
		}
	}
}