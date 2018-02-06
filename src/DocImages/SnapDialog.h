#ifndef __SNAPDIALOG_H__
#define __SNAPDIALOG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSnapDialog : public CDialog
{
// Construction
public:
	CSnapDialog(UINT IDD, CWnd* pParent = NULL);   // standard constructor

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnapDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnWindowPosChanging( WINDOWPOS* lpwndpos );
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSnapDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
// Attributes
public:
	int m_nYOffset;
	int m_nXOffset;

	DECLARE_MESSAGE_MAP()
};

#endif //__SNAPDIALOG_H__