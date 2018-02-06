// MainEdit.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MainEdit.h"
#include "Parameters.h"
#include <headers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainEdit dialog

extern "C" int TypeEdit;
extern "C" CParameters m_Parameters;
extern "C" CRollupCtrl *m_wndRollupCtrl;
extern "C" bool CreateSeg,CreateSeg2;
extern "C" void RMouseUp(int X,int Y,Vertex *Pos);
extern "C" int nbSegStar,nbSegArc,nbSegNGon;

CMainEdit::CMainEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CMainEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainEdit)
	DDX_Control(pDX, IDC_STAR, m_Star);
	DDX_Control(pDX, IDC_QUAD, m_Quad);
	DDX_Control(pDX, IDC_NGON, m_NGon);
	DDX_Control(pDX, IDC_LINE, m_Line);
	DDX_Control(pDX, IDC_ARC, m_Arc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainEdit, CDialog)
	//{{AFX_MSG_MAP(CMainEdit)
	ON_BN_CLICKED(IDC_LINE, OnLine)
	ON_BN_CLICKED(IDC_ARC, OnArc)
	ON_BN_CLICKED(IDC_NGON, OnNgon)
	ON_BN_CLICKED(IDC_QUAD, OnQuad)
	ON_BN_CLICKED(IDC_STAR, OnStar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainEdit message handlers

void CMainEdit::OnLine() 
{
	m_Star.SetCheck(0);
    m_Quad.SetCheck(0);
    m_Line.SetCheck(1);
    m_NGon.SetCheck(0);
    m_Arc.SetCheck(0);
    TypeEdit=1;
    SetPluginActive();
    if (CreateSeg||CreateSeg2)
	{
		Vertex Null;
		RMouseUp(0,0,&Vertex(0,0,0));
		DrawViews();
	}
    m_wndRollupCtrl->EnablePage(1,FALSE);
}

void CMainEdit::OnArc() 
{
	m_Star.SetCheck(0);
    m_Quad.SetCheck(0);
    m_Line.SetCheck(0);
    m_NGon.SetCheck(0);
    m_Arc.SetCheck(1);
    TypeEdit=4;
    SetPluginActive();
    if (CreateSeg||CreateSeg2)
	{
		Vertex Null;
		RMouseUp(0,0,&Vertex(0,0,0));
		DrawViews();
	}
    m_wndRollupCtrl->EnablePage(1,TRUE);

	m_Parameters.m_Slid1.SetRange(3,200);
	m_Parameters.m_Slid1.SetPos(nbSegArc);
    m_Parameters.SetText(nbSegArc);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
}

void CMainEdit::OnNgon() 
{
	m_Star.SetCheck(0);
    m_Quad.SetCheck(0);
    m_Line.SetCheck(0);
    m_NGon.SetCheck(1);
    m_Arc.SetCheck(0);
    TypeEdit=2;
    SetPluginActive();
    if (CreateSeg||CreateSeg2)
	{
		Vertex Null;
		RMouseUp(0,0,&Vertex(0,0,0));
		DrawViews();
	}
    m_wndRollupCtrl->EnablePage(1,TRUE);

	/*
    m_Parameters.m_Spin.SetBuddy(&m_Parameters.m_Edit);
	m_Parameters.m_Spin.SetRange(3.0f, 200.0f);
	m_Parameters.m_Spin.SetPos(nbSegNGon);
	m_Parameters.m_Spin.SetDelta(1.0f);
    m_Parameters.m_Edit.SetValue(nbSegNGon);
	*/
	m_Parameters.m_Slid1.SetRange(3,200);
	m_Parameters.m_Slid1.SetPos(nbSegNGon);
    m_Parameters.SetText(nbSegNGon);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
}

void CMainEdit::OnQuad() 
{
	m_Star.SetCheck(0);
    m_Quad.SetCheck(1);
    m_Line.SetCheck(0);
    m_NGon.SetCheck(0);
    m_Arc.SetCheck(0);
    TypeEdit=3;
    SetPluginActive();
    if (CreateSeg||CreateSeg2)
	{
		Vertex Null;
		RMouseUp(0,0,&Vertex(0,0,0));
		DrawViews();
	}
    m_wndRollupCtrl->EnablePage(1,FALSE);
}

void CMainEdit::OnStar() 
{
	m_Star.SetCheck(1);
    m_Quad.SetCheck(0);
    m_Line.SetCheck(0);
    m_NGon.SetCheck(0);
    m_Arc.SetCheck(0);
    TypeEdit=5;
    SetPluginActive();
    if (CreateSeg||CreateSeg2)
	{
		Vertex Null;
		RMouseUp(0,0,&Vertex(0,0,0));
		DrawViews();
	}
    m_wndRollupCtrl->EnablePage(1,TRUE);

	/*
    m_Parameters.m_Spin.SetBuddy(&m_Parameters.m_Edit);
	m_Parameters.m_Spin.SetRange(6.0f, 200.0f);
	m_Parameters.m_Spin.SetPos(nbSegStar);
	m_Parameters.m_Spin.SetDelta(2.0f);
    m_Parameters.m_Edit.SetValue(nbSegStar);
	*/
	m_Parameters.m_Slid1.SetRange(6,200);
	m_Parameters.m_Slid1.SetPos(nbSegStar);
    m_Parameters.SetText(nbSegStar);
    m_wndRollupCtrl->ExpandPage(1,TRUE);

}

BOOL CMainEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnLine();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainEdit::UnSetPlugin(void)
{
	m_Star.SetCheck(0);
    m_Quad.SetCheck(0);
    m_Line.SetCheck(0);
    m_NGon.SetCheck(0);
    m_Arc.SetCheck(0);
    TypeEdit=0;
    if (CreateSeg||CreateSeg2)
	{
		Vertex Null;
		RMouseUp(0,0,&Vertex(0,0,0));
		DrawViews();
	}

}

void CMainEdit::OnOK( )
{

}

void CMainEdit::OnCancel( )
{

}