#if !defined(AFX_MAINFRAME_H__55CE27C4_0551_44C1_BD51_3D9D6A9B4E06__INCLUDED_)
#define AFX_MAINFRAME_H__55CE27C4_0551_44C1_BD51_3D9D6A9B4E06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mainframe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainframe dialog

class CMainframe : public CDialog
{
// Construction
public:
	CMainframe(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainframe)
	enum { IDD = IDD_MAINFRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

    
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainframe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainframe)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__55CE27C4_0551_44C1_BD51_3D9D6A9B4E06__INCLUDED_)
