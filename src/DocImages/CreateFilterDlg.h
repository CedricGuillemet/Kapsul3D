#if !defined(AFX_CREATEFILTERDLG_H__C9B3D161_FE9A_11D3_B0C3_DEF0186EE51B__INCLUDED_)
#define AFX_CREATEFILTERDLG_H__C9B3D161_FE9A_11D3_B0C3_DEF0186EE51B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateFilterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateFilterDlg dialog

class CCreateFilterDlg : public CDialog
{
// Construction
public:
	CCImageDemoDoc* m_pParent;
	CImage m_Image;
	CCreateFilterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateFilterDlg)
	enum { IDD = IDD_FILTRES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateFilterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateFilterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnChangeNrows();
	afx_msg void OnAppliquer();
	afx_msg void OnCopierFiltre();
	afx_msg void OnDblclkFiltresCimage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEFILTERDLG_H__C9B3D161_FE9A_11D3_B0C3_DEF0186EE51B__INCLUDED_)

