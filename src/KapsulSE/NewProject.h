#if !defined(AFX_NEWPROJECT_H__6227BF1D_B393_4E9B_AC25_695BA74FFB45__INCLUDED_)
#define AFX_NEWPROJECT_H__6227BF1D_B393_4E9B_AC25_695BA74FFB45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProject.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewProject dialog

class CNewProject : public CDialog
{
// Construction
public:
	CNewProject(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewProject)
	enum { IDD = IDD_NEWPROJECT };
	CEdit	m_PrjLoc;
	CEdit	m_PrjName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewProject)
	afx_msg void OnPrjbrowseloc();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECT_H__6227BF1D_B393_4E9B_AC25_695BA74FFB45__INCLUDED_)
