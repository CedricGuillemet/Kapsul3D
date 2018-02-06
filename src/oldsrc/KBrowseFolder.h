#if !defined(AFX_KBROWSEFOLDER_H__51DD9DA3_43D7_4E68_BCD1_A9550FCAB4CC__INCLUDED_)
#define AFX_KBROWSEFOLDER_H__51DD9DA3_43D7_4E68_BCD1_A9550FCAB4CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KBrowseFolder.h : header file
//
#include "resource.h"
#include "FileTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CKBrowseFolder dialog

class KAPSUL_DESC CKBrowseFolder : public CDialog
{
// Construction
public:
	CKBrowseFolder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKBrowseFolder)
	enum { IDD = IDD_TPACKSHAD_FOLDER };
	CButton	m_Ok;
	CButton	m_Cancel;
	//}}AFX_DATA

	CString m_Folder;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKBrowseFolder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CTreeFileCtrl m_TreeCtl;
	// Generated message map functions
	//{{AFX_MSG(CKBrowseFolder)
	afx_msg void OnBtok();
	afx_msg void OnBtcancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KBROWSEFOLDER_H__51DD9DA3_43D7_4E68_BCD1_A9550FCAB4CC__INCLUDED_)
