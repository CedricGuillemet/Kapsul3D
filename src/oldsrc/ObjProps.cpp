// ObjProps.cpp : implementation file
//

#include "stdafx.h"
#include "KapsulSE.h"
#include "Kapsul3D.h"
#include "ObjProps.h"


// CObjProps dialog

IMPLEMENT_DYNAMIC(CObjProps, CDialog)
CObjProps::CObjProps(CWnd* pParent /*=NULL*/)
	: CDialog(CObjProps::IDD, pParent)
{
}

CObjProps::~CObjProps()
{
}

void CObjProps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITNAME, m_EditName);
}


BEGIN_MESSAGE_MAP(CObjProps, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_SETNAME, OnBnClickedSetname)
END_MESSAGE_MAP()


// CObjProps message handlers

int CObjProps::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CObjProps::OnBnClickedOk()
{
	OnBnClickedSetname();
	
	daObj->Property1=0;
	for (int i=0;i<32;i++)
	{
		if (SendDlgItemMessage(IDC_PROP1+i,BM_GETCHECK,0,0)==BST_CHECKED)
		{
			daObj->Property1|=(1<<i);
		}
	}

	DrawViews();
	OnOK();
}

void CObjProps::OnBnClickedSetname()
{
	m_EditName.GetWindowText(daObj->Name);
}

BOOL CObjProps::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_EditName.SetWindowText(daObj->Name);

	for (int i=0;i<32;i++)
	{
		if (daObj->Property1&(1<<i))
			SendDlgItemMessage(IDC_PROP1+i,BM_SETCHECK,BST_CHECKED,0);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
