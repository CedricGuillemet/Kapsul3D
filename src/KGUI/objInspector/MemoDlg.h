#if !defined(AFX_MEMODLG_H__CD27717E_5D37_4120_A1AA_FF415B872366__INCLUDED_)
#define AFX_MEMODLG_H__CD27717E_5D37_4120_A1AA_FF415B872366__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemoDlg dialog

class CMemoDlg : public CDialog
{
// Construction
public:
	CMemoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMemoDlg)
	enum { IDD = IDD_MEMOEDIT };
	CString	m_MemoEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	CRect m_Rect;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMemoDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMODLG_H__CD27717E_5D37_4120_A1AA_FF415B872366__INCLUDED_)
