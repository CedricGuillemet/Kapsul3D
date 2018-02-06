#if !defined(AFX_OUTPUTDUMP_H__89E2A973_7864_4B7F_9A46_F05744567E68__INCLUDED_)
#define AFX_OUTPUTDUMP_H__89E2A973_7864_4B7F_9A46_F05744567E68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputDump.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutputDump dialog

class COutputDump : public CDialog
{
// Construction
public:
	COutputDump(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COutputDump)
	enum { IDD = IDD_OUTPUT };
	CEdit	m_Output;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputDump)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutputDump)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTDUMP_H__89E2A973_7864_4B7F_9A46_F05744567E68__INCLUDED_)
