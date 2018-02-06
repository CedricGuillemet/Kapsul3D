// CorrectionCouleursDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CImageDemo.h"

//#include "..\image\Image.h"
#include "CImageDemoDoc.h"
#include "CorrectionCouleursDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCorrectionCouleursDlg dialog


CCorrectionCouleursDlg::CCorrectionCouleursDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCorrectionCouleursDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCorrectionCouleursDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bGoOn = FALSE;
}


void CCorrectionCouleursDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCorrectionCouleursDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCorrectionCouleursDlg, CDialog)
	//{{AFX_MSG_MAP(CCorrectionCouleursDlg)
	ON_EN_CHANGE(IDC_ROUGE, OnCorrectCouleurs)
	ON_WM_DRAWITEM()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_GAMMA, OnDeltaposSpinGamma)
	ON_EN_CHANGE(IDC_VERT, OnCorrectCouleurs)
	ON_EN_CHANGE(IDC_BLEU, OnCorrectCouleurs)
	ON_EN_CHANGE(IDC_GAMMA, OnCorrectCouleurs)
	ON_EN_CHANGE(IDC_SATURATION, OnCorrectCouleurs)
	ON_EN_CHANGE(IDC_TEINTE, OnCorrectCouleurs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCorrectionCouleursDlg message handlers

void CCorrectionCouleursDlg::OnCorrectCouleurs() 
{
	if(m_bGoOn)
	{
		m_Image = m_pParent->m_Image;

		int nSat = GetDlgItemInt(IDC_SATURATION);
		int nHue = GetDlgItemInt(IDC_TEINTE);
		m_Image.AdjustSaturationAndHue(nSat, nHue);

		int nRouge = ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ROUGE))->GetPos();
		int nVert = ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_VERT))->GetPos();
		int nBleu = ((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_BLEU))->GetPos();
		m_Image.CorrectColors(nRouge, nVert, nBleu);

		CString szDummy;
		GetDlgItemText(IDC_GAMMA, szDummy);
		m_Image.AdjustGamma(atof(szDummy));

		GetDlgItem(IDC_IMAGE)->InvalidateRect(NULL);
	}
}

void CCorrectionCouleursDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
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

BOOL CCorrectionCouleursDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ROUGE))->SetRange(0, UD_MAXVAL);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_VERT))->SetRange(0, UD_MAXVAL);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_BLEU))->SetRange(0, UD_MAXVAL);
	
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ROUGE))->SetPos(1000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_VERT))->SetPos(1000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_BLEU))->SetPos(1000);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_GAMMA))->SetRange(0, 100);
	SetDlgItemText(IDC_GAMMA, "1.000");

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SATURATION))->SetRange(-100, 100);	
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SATURATION))->SetPos(0);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_TEINTE))->SetRange(-100, 100);	
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_TEINTE))->SetPos(0);

	m_bGoOn = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCorrectionCouleursDlg::OnDeltaposSpinGamma(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	CString szDummy;
	GetDlgItemText(IDC_GAMMA, szDummy);
	szDummy.Format("%1.3f", atof(szDummy)+(pNMUpDown->iDelta>0 ? 0.1 : (-0.1)));
	SetDlgItemText(IDC_GAMMA, szDummy);

	*pResult = 1;
}
