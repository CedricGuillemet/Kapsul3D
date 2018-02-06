// TweakUV.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "TweakUV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTweakUV dialog

extern int iEditMode;

CTweakUV::CTweakUV(CWnd* pParent /*=NULL*/)
	: CDialog(CTweakUV::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTweakUV)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTweakUV::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTweakUV)
	DDX_Control(pDX, IDC_SHIFTY, m_ShiftY);
	DDX_Control(pDX, IDC_SHIFTX, m_ShiftX);
	DDX_Control(pDX, IDC_SCALEY, m_ScaleY);
	DDX_Control(pDX, IDC_SCALEX, m_ScaleX);
	DDX_Control(pDX, IDC_ROTATE, m_Rotate);
	DDX_Control(pDX, IDC_EDITSHIFTY, m_EditShiftY);
	DDX_Control(pDX, IDC_EDITSHIFTX, m_EditShiftX);
	DDX_Control(pDX, IDC_EDITSCALEY, m_EditScaleY);
	DDX_Control(pDX, IDC_EDITSCALEX, m_EditScaleX);
	DDX_Control(pDX, IDC_EDITROTATE, m_EditRotate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTweakUV, CDialog)
	//{{AFX_MSG_MAP(CTweakUV)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTweakUV message handlers

BOOL CTweakUV::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ShiftY.SetBuddy(&m_EditShiftY);
	m_ShiftY.SetRange(-10000.0f, 10000.0f);
	m_ShiftY.SetPos(0);
	m_ShiftY.SetDelta(0.1f);

	m_ShiftX.SetBuddy(&m_EditShiftX);
	m_ShiftX.SetRange(-10000.0f, 10000.0f);
	m_ShiftX.SetPos(0);
	m_ShiftX.SetDelta(0.1f);

	m_ScaleY.SetBuddy(&m_EditScaleY);
	m_ScaleY.SetRange(-100.0f, 100.0f);
	m_ScaleY.SetPos(0);
	m_ScaleY.SetDelta(0.1f);

	m_ScaleX.SetBuddy(&m_EditScaleX);
	m_ScaleX.SetRange(-100.0f, 100.0f);
	m_ScaleX.SetPos(0);
	m_ScaleX.SetDelta(0.1f);
	
	m_Rotate.SetBuddy(&m_EditRotate);
	m_Rotate.SetRange(0.0f, 359.0f);
	m_Rotate.SetPos(0);
	m_Rotate.SetDelta(1.0f);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTweakUV::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	bool UpdateIt;

	
	CTVTestDlg *par=(CTVTestDlg*)GetParent();
	CKScene *m_Scene=par->m_Scene;

	if (iEditMode==2)
	{
		// apply the polygons

		for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			UpdateIt=false;
			for (int i=0;i<daMesh->nb2poly;i++)
			{
				if (daMesh->pl[i].Selected)
				{
					daMesh->pl[i].TweakUV=true;
					daMesh->pl[i].TransU=m_ShiftX.GetPos();
					daMesh->pl[i].TransV=m_ShiftY.GetPos();
					daMesh->pl[i].ScaleU=m_ScaleX.GetPos();
					daMesh->pl[i].ScaleV=m_ScaleY.GetPos();
					daMesh->pl[i].Rotate=m_Rotate.GetPos();
					UpdateIt=true;
				}
			}
			if (UpdateIt) daMesh->UpdateMesh();
		}
		DrawViews();
	}
	else
	if (iEditMode==3)
	{
		// apply per object
		for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			if (daMesh->Selected)
			{
				//daMesh->ApplyTexture(datex);
				for (int i=0;i<daMesh->nb2poly;i++)
				{
					daMesh->pl[i].TweakUV=true;
					daMesh->pl[i].TransU=m_ShiftX.GetPos();
					daMesh->pl[i].TransV=m_ShiftY.GetPos();
					daMesh->pl[i].ScaleU=m_ScaleX.GetPos();
					daMesh->pl[i].ScaleV=m_ScaleY.GetPos();
					daMesh->pl[i].Rotate=m_Rotate.GetPos();
				}
				daMesh->UpdateMesh();
			}
		}
		DrawViews();
		/*
		// apply per patch
		for (CKPatch *daPatch=m_Scene->FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
		{
			if (daPatch->Selected)
				daPatch->ApplyTexture(datex);
		}
		*/
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
