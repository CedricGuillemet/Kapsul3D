#if !defined(AFX_CONTRASTEDLG_H__34F90A82_0AAE_11D3_AC65_0000E85A8A24__INCLUDED_)
#define AFX_CONTRASTEDLG_H__34F90A82_0AAE_11D3_AC65_0000E85A8A24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContrasteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContrasteDlg dialog

class CContrasteDlg : public CDialog
{
// Construction
public:
	CCImageDemoDoc* m_pParent;
	CImage m_Image;
	CContrasteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CContrasteDlg)
	enum { IDD = IDD_CONTRASTE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContrasteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CContrasteDlg)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTRASTEDLG_H__34F90A82_0AAE_11D3_AC65_0000E85A8A24__INCLUDED_)
