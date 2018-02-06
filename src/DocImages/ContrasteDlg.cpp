// ContrasteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CImageDemo.h"

//#include "..\image\Image.h"
#include "CImageDemoDoc.h"
#include "ContrasteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContrasteDlg dialog


CContrasteDlg::CContrasteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContrasteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContrasteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CContrasteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContrasteDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContrasteDlg, CDialog)
	//{{AFX_MSG_MAP(CContrasteDlg)
	ON_WM_DRAWITEM()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContrasteDlg message handlers

void CContrasteDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if(nIDCtl==IDC_IMAGE
		&& lpDrawItemStruct->itemAction==ODA_DRAWENTIRE
		&& m_Image.IsValid())
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CRect rcDraw;
		(dc.GetWindow())->GetClientRect(&rcDraw);
		m_Image.Draw(dc.m_hDC, rcDraw, DIB_DRAW_SETPALETTE
			| DIB_DRAW_STRETCH_REDUCEX | DIB_DRAW_STRETCH_REDUCEY
			| DIB_DRAW_CENTER_HORZ | DIB_DRAW_CENTER_VERT
			| DIB_DRAW_KEEP_RATIO);
		dc.Detach();
		return;
	}
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

BOOL CContrasteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CSliderCtrl*)GetDlgItem(IDC_LUMIERE))->SetRange(-100, +100, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_CONTRASTE))->SetRange(-100, +100, TRUE);

	((CSliderCtrl*)GetDlgItem(IDC_LUMIERE))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_CONTRASTE))->SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CContrasteDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Image = m_pParent->m_Image;

	int nBright = ((CSliderCtrl*)GetDlgItem(IDC_LUMIERE))->GetPos();
	m_Image.AdjustBrightness(nBright);
	int nContrast = ((CSliderCtrl*)GetDlgItem(IDC_CONTRASTE))->GetPos();
	m_Image.AdjustContrast(nContrast);

	CString szDummy;
	szDummy.Format("( %d )", nBright);
	SetDlgItemText(IDC_INDIC_LUMIERE, szDummy);
	szDummy.Format("( %d )", nContrast);
	SetDlgItemText(IDC_INDIC_CONTRASTE, szDummy);

	GetDlgItem(IDC_IMAGE)->InvalidateRect(NULL);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
