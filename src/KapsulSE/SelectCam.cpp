// SelectCam.cpp : implementation file
//

#include "stdafx.h"
//#include "t7.h"

//#include "memmgr/mmgr.h"

#include "SelectCam.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectCam dialog


CSelectCam::CSelectCam(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectCam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectCam)
	//}}AFX_DATA_INIT
	SelCam=NULL;
}


void CSelectCam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectCam)
	DDX_Control(pDX, IDC_LISTCAMERA, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectCam, CDialog)
	//{{AFX_MSG_MAP(CSelectCam)
	ON_BN_CLICKED(ID_OK, OnOk)
	ON_BN_CLICKED(ID_CANCEL, OnCancel)
	ON_LBN_DBLCLK(IDC_LISTCAMERA, OnDblclkListcamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectCam message handlers

BOOL CSelectCam::OnInitDialog() 
{
	CKCamera *pCam;
	int Index=0;


	CDialog::OnInitDialog();

	
	pCam=m_Scene->FirstCam;
	while (pCam!=NULL)
	{
		m_List.AddString(pCam->Name);
		pCam=pCam->Next;
	}	
	m_List.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectCam::OnOk() 
{
	CKCamera *pCam;
	int Index=0;

	pCam=m_Scene->FirstCam;
	while (pCam!=NULL)
	{
		if (Index==m_List.GetCurSel())
		{
			SelCam=pCam;
			CDialog::OnOK();
		}

		Index++;

		pCam=pCam->Next;
	}	

}

void CSelectCam::OnCancel() 
{
	CDialog::OnCancel();
}

void CSelectCam::OnDblclkListcamera() 
{
	OnOk();
}
