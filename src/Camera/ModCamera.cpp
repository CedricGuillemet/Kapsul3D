#include "stdafx.h"
#include "Kapsul3D.h"
#include "resource.h"
#include "ModDiag.h"
#include "Kapsul3D.h"

#include "ModCamera.h"

CRollupCtrl *m_wndRollupCtrl=NULL;

HWND CKPluginCamera::Open(HWND Parent)
{
	SWITCH_RESOURCE;

    m_wndRollupCtrl=new CRollupCtrl;
    m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,4,164,362), CWnd::FromHandle(Parent), 2);	

	ModDiag=new CModDiag;
	ModDiag->Create((unsigned int)IDD_MODDIAG,CWnd::FromHandle(Parent));

	CreateSeg=0;

	return ModDiag->m_hWnd;
}

void CKPluginCamera::Close()
{
	ModDiag->DestroyWindow();
}

int CKPluginCamera::ScenePluginType()
{
	return PLUGIN_PRIMITIVE;
}

void CKPluginCamera::ReSize(int sx,int sy)
{
	if (m_wndRollupCtrl!=NULL)
		m_wndRollupCtrl->MoveWindow(0,0,164,sy,TRUE);
}

void CKPluginCamera::LoseFocus()
{
	ModDiag->UnSetPlugin();
}

CString CKPluginCamera::GetName()
{
	return "Camera";
}

CString CKPluginCamera::GetInfos()
{
	return "Camera";
}

bool CKPluginCamera::CreatingStatus()
{
	return CreateSeg;
}

void CKPluginCamera::SetScene(CKScene *pScene)
{
	m_Scene=pScene;
}

PrimBmp* CKPluginCamera::GetAllPrimitives()
{
	SWITCH_RESOURCE;

	daBmps.NbBmps=1;
	for (int i=0;i<daBmps.NbBmps;i++)
		daBmps.Bmp[i].Detach();

	daBmps.Bmp[0].LoadBitmap(MAKEINTRESOURCE(IDB_CAMERAIN));
	daBmps.PrimNb[0]=1;

	return &daBmps;
}

void CKPluginCamera::SetPrimitive(int PrimitiveNb)
{
}

void CKPluginCamera::DeleteStuff()
{
}

void CKPluginCamera::LMouseDown(int X,int Y,Vertex &Pos)
{
	if ((HasMoveCr)&&(CreateSeg))
    {
        CreateSeg=false;
    }
    else
    {
        if (!CreateSeg)
        {
            CurrentCam=m_Scene->AddCam();
			ModDiag->m_ParamDiag->CurrentCam=CurrentCam;

			CurrentUndo=m_Scene->AddUndo("camera.dll",1);
			CurrentUndo->UndoType=UNDO_CREATE;


			CurrentCam->ResoX=ModDiag->m_ParamDiag->m_SpinX.GetPos();// SendDlgItemMessage(CameraDiagHWND,IDC_SPIN1,UDM_GETPOS ,0,0);
			CurrentCam->ResoY=ModDiag->m_ParamDiag->m_SpinY.GetPos();//SendDlgItemMessage(CameraDiagHWND,IDC_SPIN2,UDM_GETPOS ,0,0);
			CurrentCam->Fov=ModDiag->m_ParamDiag->m_SpinFov.GetPos();//SendDlgItemMessage(CameraDiagHWND,IDC_SPIN3,UDM_GETPOS ,0,0);

            m_Scene->NextCam->SetSource(Pos);
            m_Scene->NextCam->SetDest(Pos);

            HasMoveCr=false;
            CreateSeg=true;
        }
    }
}

void CKPluginCamera::LMouseUp(int X,int Y,Vertex &Pos)
{
    if (HasMoveCr)
    {
        CreateSeg=false;
        HasMoveCr=false;
		CurrentUndo->SetAfterEntry(0,PLUGIN_CAMERA,m_Scene->NextCam);
    }
}

void CKPluginCamera::RMouseUp(int X,int Y,Vertex &Pos)
{
    if (CurrentCam!=NULL)
    {
        m_Scene->DelCamera(CurrentCam);
		CreateSeg=0;
    }
}

void CKPluginCamera::MouseMove(int X,int Y,Vertex &Pos)
{
	if (CreateSeg)
    {
        m_Scene->NextCam->SetDest(Pos);
		RStatus("Click to set camera Destination.");
		DrawViews();
    }
    else
    {
		RStatus("Click to set camera source.");
    }
    HasMoveCr=true;
}


