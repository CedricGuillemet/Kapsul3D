// MemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "MemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_WIDTH  258 
#define MIN_HEIGHT 154

/////////////////////////////////////////////////////////////////////////////
// CMemoDlg dialog


CMemoDlg::CMemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemoDlg)
	m_MemoEdit = _T("");
	//}}AFX_DATA_INIT

	m_Rect.SetRectEmpty();
}


void CMemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemoDlg)
	DDX_Text(pDX, IDC_EDTMEMO, m_MemoEdit);
	DDV_MaxChars(pDX, m_MemoEdit, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMemoDlg, CDialog)
	//{{AFX_MSG_MAP(CMemoDlg)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoDlg message handlers

void CMemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	/*if(cx <= MIN_WIDTH)
		cx = MIN_WIDTH;

	if(cy <= MIN_HEIGHT)
		cy = MIN_HEIGHT;

	GetWindowRect(m_Rect);*/

	CDialog::OnSize(nType, cx, cy);
	
	/*int w_diff = cx - m_Rect.Width();
	int h_diff = cy - m_Rect.Height();

	CWnd * pEdit = GetDlgItem(IDC_EDIT1);
	CWnd * pFrame = GetDlgItem(IDC_STATIC);

	CRect rEdit,rFrame;
	pEdit->GetWindowRect(rEdit);
	pFrame->GetWindowRect(rFrame);

	rEdit.right += w_diff;
	rEdit.bottom += h_diff;

	rFrame.right += w_diff;
	rFrame.bottom += h_diff;

	pEdit->MoveWindow(rEdit);
	pFrame->MoveWindow(rFrame);*/
}

void CMemoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)
	{
		CWnd * pEdit = GetDlgItem(IDC_EDTMEMO);
		pEdit->SetFocus();
	}
}