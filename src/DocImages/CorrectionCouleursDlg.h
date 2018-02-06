#if !defined(AFX_CORRECTIONCOULEURSDLG_H__33D66261_60A3_11D3_AC65_0000E85A8A24__INCLUDED_)
#define AFX_CORRECTIONCOULEURSDLG_H__33D66261_60A3_11D3_AC65_0000E85A8A24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CorrectionCouleursDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCorrectionCouleursDlg dialog

class CCorrectionCouleursDlg : public CDialog
{
// Construction
public:
	BOOL m_bGoOn;
	CCImageDemoDoc* m_pParent;
	CImage m_Image;
	CCorrectionCouleursDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCorrectionCouleursDlg)
	enum { IDD = IDD_CORRECT_COULEURS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCorrectionCouleursDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCorrectionCouleursDlg)
	afx_msg void OnCorrectCouleurs();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinGamma(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CORRECTIONCOULEURSDLG_H__33D66261_60A3_11D3_AC65_0000E85A8A24__INCLUDED_)
