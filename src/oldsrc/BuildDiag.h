#if !defined(AFX_BUILDDIAG_H__5478A245_BB05_4C39_9C69_A1D5084FD575__INCLUDED_)
#define AFX_BUILDDIAG_H__5478A245_BB05_4C39_9C69_A1D5084FD575__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuildDiag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuildDiag dialog

class CBuildDiag : public CDialog
{
// Construction
public:
	CBuildDiag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBuildDiag)
	enum { IDD = IDD_BUILD };
	CButton	m_BuildIt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CBuildDiag)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILDDIAG_H__5478A245_BB05_4C39_9C69_A1D5084FD575__INCLUDED_)
