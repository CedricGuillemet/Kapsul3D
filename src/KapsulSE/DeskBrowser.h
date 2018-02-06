#if !defined(AFX_DESKBROWSER_H__A34018F9_9F20_409D_B50E_A9831BCD0C9B__INCLUDED_)
#define AFX_DESKBROWSER_H__A34018F9_9F20_409D_B50E_A9831BCD0C9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeskBrowser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeskBrowser dialog

class CDeskBrowser : public CDialog
{
// Construction
public:
	CDeskBrowser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeskBrowser)
	enum { IDD = IDD_TVTEST_DIALOG };
	CTreeCtrl	m_TreeHierar;
	CTabCtrl	m_Tabs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeskBrowser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeskBrowser)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESKBROWSER_H__A34018F9_9F20_409D_B50E_A9831BCD0C9B__INCLUDED_)
