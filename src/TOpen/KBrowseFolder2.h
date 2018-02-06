#if !defined(AFX_KBROWSEFOLDER_H__51DD9DA3_43D7_4E68_BCD1_A9550FCAB4CC__INCLUDED_)
#define AFX_KBROWSEFOLDER_H__51DD9DA3_43D7_4E68_BCD1_A9550FCAB4CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KBrowseFolder.h : header file
//
//#define KAPSUL_DESC __declspec(dllimport)
#include "Kapsul3D.h"

#include "resource.h"
#include "FileTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CKBrowseFolder2 dialog

//#define CKBrowseFolder2 CKBrowseFolder22
class CKBrowseFolder2 : public CDialog
{
// Construction
public:
	CKBrowseFolder2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKBrowseFolder2)
	enum { IDD = IDD_TPACKSHAD_FOLDER };
	CButton	m_Ok;
	CButton	m_Cancel;
	//}}AFX_DATA

	CString m_Folder;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKBrowseFolder2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CTreeFileCtrl m_TreeCtl;
	// Generated message map functions
	//{{AFX_MSG(CKBrowseFolder2)
	afx_msg void OnBtok();
	afx_msg void OnBtcancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KBROWSEFOLDER_H__51DD9DA3_43D7_4E68_BCD1_A9550FCAB4CC__INCLUDED_)
