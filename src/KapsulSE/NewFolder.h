#if !defined(AFX_NEWFOLDER_H__E35F6FE2_0997_4E25_8E95_E5362805FCA7__INCLUDED_)
#define AFX_NEWFOLDER_H__E35F6FE2_0997_4E25_8E95_E5362805FCA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewFolder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewFolder dialog

class CNewFolder : public CDialog
{
// Construction
public:
	CNewFolder(CWnd* pParent = NULL);   // standard constructor
	CString FolderName,FolderExt;
// Dialog Data
	//{{AFX_DATA(CNewFolder)
	enum { IDD = IDD_NEWFOLDER };
	CStatic	m_FolderLib2;
	CStatic	m_FolderLib1;
	CEdit	m_FolderName;
	CEdit	m_FolderExt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewFolder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewFolder)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWFOLDER_H__E35F6FE2_0997_4E25_8E95_E5362805FCA7__INCLUDED_)
