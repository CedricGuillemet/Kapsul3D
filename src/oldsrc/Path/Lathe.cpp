// Lathe.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Lathe.h"
#include "Mapping.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLathe dialog

CKMesh *CurLatheMesh=NULL;
CKShape *CurLatheShp=NULL;
extern "C" int TypeEd;
extern CMapping m_Mapping;
extern CKScene *GScene;

CLathe::CLathe(CWnd* pParent /*=NULL*/)
	: CDialog(CLathe::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLathe)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLathe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLathe)
	DDX_Control(pDX, IDC_LATHESCALE, m_LatheScale);
	DDX_Control(pDX, IDC_LATHEVAL, m_LatheVal);
	DDX_Control(pDX, IDC_SHAPENAME, m_ShapeName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLathe, CDialog)
	//{{AFX_MSG_MAP(CLathe)
	ON_BN_CLICKED(IDC_SHAPE, OnShape)
	ON_BN_CLICKED(IDC_LATHEIT, OnLatheit)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLathe message handlers

void CLathe::OnShape() 
{
	/*
	//dk->AddObject();
	CurLatheObj=new Object(NULL,NULL);
	CurLatheObj->Lathing(dk->FirstShape,16);
	CurLatheObj
	*/
	TypeEd=10;
}

void CLathe::OnLatheit() 
{
	if (CurLatheMesh!=NULL)
	{
		GScene->AddMesh(CurLatheMesh);
		CurLatheMesh=NULL;
		m_ShapeName.SetWindowText("");
	}	
}

void CLathe::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CString nb;
	nb.Format("%d",m_LatheVal.GetPos());
	m_LatheScale.SetWindowText(nb);

	if (CurLatheMesh!=NULL)
	{
		double Valu,Valv;
		Valu=m_Mapping.m_SlidU.GetPos();
		Valv=m_Mapping.m_SlidV.GetPos();

		Valu/=10;
		Valv/=10;

		CurLatheMesh->Lathing(CurLatheShp,m_LatheVal.GetPos(),Valu,Valv);
		DrawViews();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CLathe::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_LatheVal.SetRange(3,60);
	m_LatheVal.SetPos(8);
	m_LatheScale.SetWindowText("8");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
