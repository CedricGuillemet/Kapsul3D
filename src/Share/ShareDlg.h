// ShareDlg.h : header file
//

#if !defined(AFX_SHAREDLG_H__8376E9F6_C750_4F1E_80D3_4F6D9BEF28FC__INCLUDED_)
#define AFX_SHAREDLG_H__8376E9F6_C750_4F1E_80D3_4F6D9BEF28FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShareDlg dialog

class CShareDlg : public CDialog
{
// Construction
public:
	CShareDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShareDlg)
	enum { IDD = IDD_SHARE_DIALOG };
	CStatic	m_St2;
	CStatic	m_St1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShareDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHAREDLG_H__8376E9F6_C750_4F1E_80D3_4F6D9BEF28FC__INCLUDED_)
