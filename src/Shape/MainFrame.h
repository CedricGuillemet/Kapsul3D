#if !defined(AFX_MAINFRAME_H__A02D3CDA_6D89_445A_AFEC_89AF2B8A560E__INCLUDED_)
#define AFX_MAINFRAME_H__A02D3CDA_6D89_445A_AFEC_89AF2B8A560E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainFrame dialog

class CMainFrame : public CDialog
{
// Construction
public:
	CMainFrame(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainFrame)
	enum { IDD = IDD_MODDIAG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CMainFrame)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__A02D3CDA_6D89_445A_AFEC_89AF2B8A560E__INCLUDED_)
