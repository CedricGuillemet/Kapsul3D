// Path.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Path.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPath dialog


CPath::CPath(CWnd* pParent /*=NULL*/)
	: CDialog(CPath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPath)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPath)
	DDX_Control(pDX, IDC_CAPPING, m_Capping);
	DDX_Control(pDX, IDC_SPLINEDSHAPE, m_SplinedShape);
	DDX_Control(pDX, IDC_SPLINEDPATH, m_SplinedPath);
	DDX_Control(pDX, IDC_STEPSSHAPE, m_EditShape);
	DDX_Control(pDX, IDC_STEPSPATH, m_EditPath);
	DDX_Control(pDX, IDC_SPINSHAPE, m_SpinShape);
	DDX_Control(pDX, IDC_SPINPATH, m_SpinPath);
	DDX_Control(pDX, IDC_PATHNAME, m_PathName);
	DDX_Control(pDX, IDC_SHAPENAME, m_ShapeName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPath, CDialog)
	//{{AFX_MSG_MAP(CPath)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_PATH, OnPath)
	ON_BN_CLICKED(IDC_ROTATE, OnRotate)
	ON_BN_CLICKED(IDC_SHAPE, OnShape)
	ON_BN_CLICKED(IDC_SPLINEDPATH, OnSplinedpath)
	ON_BN_CLICKED(IDC_SPLINEDSHAPE, OnSplinedshape)
	ON_BN_CLICKED(IDC_SCALE, OnScale)
	ON_BN_CLICKED(IDC_ROTATEY, OnRotatey)
	ON_BN_CLICKED(IDC_ROTATEZ, OnRotatez)
	ON_BN_CLICKED(IDC_SCALEY, OnScaley)
	ON_BN_CLICKED(IDC_CAPPING, OnCapping)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPath message handlers

BOOL CPath::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SpinShape.SetBuddy(&m_EditShape);
	m_SpinShape.SetRange(1.0f, 100.0f);
	m_SpinShape.SetPos(1.0f);
	m_SpinShape.SetDelta(1.0f);	

	m_SpinPath.SetBuddy(&m_EditPath);
	m_SpinPath.SetRange(1.0f, 100.0f);
	m_SpinPath.SetPos(1.0f);
	m_SpinPath.SetDelta(1.0f);	

	m_Capping.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPath::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	SetPluginActive();
	if ((m_Plugin->SPath!=NULL)&&(m_Plugin->SShape!=NULL))
	{
		m_Plugin->GenerateObject();
		DrawViews();
	}
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
/*
void CPath::OnMoveshape() 
{
	m_Plugin->LastAction=ACTION_PATHMOVE;
	
}
*/
void CPath::OnPath() 
{
	SetPluginActive();
	m_Plugin->LastAction=ACTION_SELECTPATH;
}

void CPath::OnRotate() 
{
	SetPluginActive();
	m_Plugin->LastAction=ACTION_PATHROTATEX;
}

void CPath::OnShape() 
{
	SetPluginActive();
	m_Plugin->LastAction=ACTION_SELECTSHAPE;
}

void CPath::OnSplinedpath() 
{
	SetPluginActive();
	if ((m_Plugin->SPath!=NULL)&&(m_Plugin->SShape!=NULL))
	{
		m_Plugin->GenerateObject();
		DrawViews();
	}	
}

void CPath::OnSplinedshape() 
{
	if ((m_Plugin->SPath!=NULL)&&(m_Plugin->SShape!=NULL))
	{
		m_Plugin->GenerateObject();
		DrawViews();
	}	
	SetPluginActive();
}

void CPath::OnScale() 
{
	m_Plugin->LastAction=ACTION_PATHSCALEX;
	SetPluginActive();
}

void CPath::OnRotatey() 
{
	m_Plugin->LastAction=ACTION_PATHROTATEY;
	SetPluginActive();
}

void CPath::OnRotatez() 
{
	m_Plugin->LastAction=ACTION_PATHROTATEZ;
	SetPluginActive();
}

void CPath::OnScaley() 
{
	m_Plugin->LastAction=ACTION_PATHSCALEY;
	SetPluginActive();
}

void CPath::OnOK( )
{

}

void CPath::OnCancel( )
{

}

void CPath::OnCapping() 
{
	if ((m_Plugin->SPath!=NULL)&&(m_Plugin->SShape!=NULL))
	{
		m_Plugin->GenerateObject();
		DrawViews();
	}	
	SetPluginActive();	
	
}
