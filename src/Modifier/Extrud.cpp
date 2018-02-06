// Extrud.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Extrud.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtrud dialog


CExtrud::CExtrud(CWnd* pParent /*=NULL*/)
	: CDialog(CExtrud::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtrud)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExtrud::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtrud)
	DDX_Control(pDX, IDC_STEPS, m_EditSteps);
	DDX_Control(pDX, IDC_SPINSTEPS, m_SpinSteps);
	DDX_Control(pDX, IDC_SPINSCALE, m_SpinScale);
	DDX_Control(pDX, IDC_SPINLENGTH, m_SpinLength);
	DDX_Control(pDX, IDC_SCALE, m_EditScale);
	DDX_Control(pDX, IDC_LENGTH, m_EditLenght);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExtrud, CDialog)
	//{{AFX_MSG_MAP(CExtrud)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtrud message handlers

BOOL CExtrud::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SpinSteps.SetBuddy(&m_EditSteps);
	m_SpinSteps.SetRange(1.0f, 10000.0f);
	m_SpinSteps.SetPos(1.0f);
	m_SpinSteps.SetDelta(1.0f);	

	m_SpinScale.SetBuddy(&m_EditScale);
	m_SpinScale.SetRange(0.0f, 10000.0f);
	m_SpinScale.SetPos(1.0f);
	m_SpinScale.SetDelta(0.1f);	

	m_SpinLength.SetBuddy(&m_EditLenght);
	m_SpinLength.SetRange(0.0f, 100000.0f);
	m_SpinLength.SetPos(0);
	m_SpinLength.SetDelta(0.1f);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExtrud::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_Plugin->LastAction!=ACTION_EXTRUD)
	{
		m_Plugin->LastAction=ACTION_EXTRUD;

		m_Plugin->ApplyModifs();
		/*
		for (CKMesh *aiM=m_Plugin->m_Scene->FirstMesh;aiM!=NULL;aiM=aiM->Next)
		{
			m_Plugin->m_shp=aiM->BuildShapesFromSelectedFaces();
		}*/
		m_Plugin->PutSelectedToBuf();
		m_Plugin->DeleteStuff();
		
	}

	m_Plugin->ExtrudIt();
	DrawViews();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CExtrud::OnOK( )
{

}

void CExtrud::OnCancel( )
{

}