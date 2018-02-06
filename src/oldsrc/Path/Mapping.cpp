// Mapping.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Mapping.h"
#include "Lathe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapping dialog

extern CKMesh *CurLatheMesh;
extern "C" CKMesh *Mesh;
extern CKShape *CurLatheShp;
extern CLathe m_Lathe;
extern "C" {

void GenerateObject(void);
}

CMapping::CMapping(CWnd* pParent /*=NULL*/)
	: CDialog(CMapping::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapping)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMapping::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapping)
	DDX_Control(pDX, IDC_SLIDV, m_SlidV);
	DDX_Control(pDX, IDC_SLIDU, m_SlidU);
	DDX_Control(pDX, IDC_TEXTV, m_TextV);
	DDX_Control(pDX, IDC_TEXTU, m_TextU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapping, CDialog)
	//{{AFX_MSG_MAP(CMapping)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapping message handlers

BOOL CMapping::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SlidU.SetRange(1,100);
	m_SlidV.SetRange(1,100);

	m_SlidU.SetPos(10);
	m_SlidV.SetPos(10);

	SetTextU(1);
	SetTextV(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMapping::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	double Valu,Valv;
    Valu=m_SlidU.GetPos();
    Valv=m_SlidV.GetPos();

	Valu/=10;
	Valv/=10;

	SetTextU(Valu);
	SetTextV(Valv);
	if (CurLatheMesh!=NULL)
	{
		CurLatheMesh->Lathing(CurLatheShp,m_Lathe.m_LatheVal.GetPos(),Valu,Valv);
	}

	if (Mesh!=NULL)
	{
		GenerateObject();
	}
	DrawViews();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMapping::OnOK( )
{

}

void CMapping::OnCancel( )
{

}

void CMapping::SetTextU(float Value)
{
	char temp[64];
	sprintf(temp,"%5.2f",Value);
	m_TextU.SetWindowText(temp);
}

void CMapping::SetTextV(float Value)
{
	char temp[64];
	sprintf(temp,"%5.2f",Value);
	m_TextV.SetWindowText(temp);
}
