#if !defined(AFX_PATH_H__71FE0608_C1DB_471D_A648_2A34ABE51082__INCLUDED_)
#define AFX_PATH_H__71FE0608_C1DB_471D_A648_2A34ABE51082__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Path.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPath dialog

class CPath : public CDialog
{
// Construction
public:
	CPath(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPath)
	enum { IDD = IDD_PATH };
	CStatic	m_ShapeName;
	CStatic	m_PathName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( ) {};
	virtual void OnCancel( ) {};
	// Generated message map functions
	//{{AFX_MSG(CPath)
	afx_msg void OnGenerate();
	afx_msg void OnPath();
	afx_msg void OnShape();
	afx_msg void OnMoveshape();
	afx_msg void OnRotate();
	afx_msg void OnScale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATH_H__71FE0608_C1DB_471D_A648_2A34ABE51082__INCLUDED_)
