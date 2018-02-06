// SelTypeDoc.cpp : implementation file
//

#include "stdafx.h"
#include "KapsulSE.h"
#include "SelTypeDoc.h"


// CSelTypeDoc dialog

IMPLEMENT_DYNAMIC(CSelTypeDoc, CDialog)
CSelTypeDoc::CSelTypeDoc(CWnd* pParent /*=NULL*/)
	: CDialog(CSelTypeDoc::IDD, pParent)
{
}

CSelTypeDoc::~CSelTypeDoc()
{
}

void CSelTypeDoc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DESK, m_Desk);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
}


BEGIN_MESSAGE_MAP(CSelTypeDoc, CDialog)
	ON_BN_CLICKED(IDC_DESK, OnBnClickedDesk)
	ON_BN_CLICKED(IDC_SCRIPT, OnBnClickedScript)
END_MESSAGE_MAP()


// CSelTypeDoc message handlers

BOOL CSelTypeDoc::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Desk.SetCheck(1);
	TypeDoc=0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelTypeDoc::OnBnClickedDesk()
{
	TypeDoc=0;
	m_Script.SetCheck(0);
}

void CSelTypeDoc::OnBnClickedScript()
{
	TypeDoc=1;
	m_Desk.SetCheck(0);
}
