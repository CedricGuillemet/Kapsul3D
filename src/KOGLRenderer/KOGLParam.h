#if !defined(AFX_KOGLPARAM_H__3CF2A924_D0C7_4B70_8743_CF8F788DDB40__INCLUDED_)
#define AFX_KOGLPARAM_H__3CF2A924_D0C7_4B70_8743_CF8F788DDB40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KOGLParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKOGLParam dialog

class CKOGLParam : public CDialog
{
// Construction
public:
	CKOGLParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKOGLParam)
	enum { IDD = IDD_KOGLPARAM };
	CListBox	m_ExtList;
	CStatic	m_Renderer;
	CStatic	m_GLVersion;
	CStatic	m_GluVersion;
	CStatic	m_Vendor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKOGLParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKOGLParam)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KOGLPARAM_H__3CF2A924_D0C7_4B70_8743_CF8F788DDB40__INCLUDED_)
