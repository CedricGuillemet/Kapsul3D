#if !defined(AFX_CAMKF_H__B8EC29D4_C815_417D_8C7C_A34E0C391220__INCLUDED_)
#define AFX_CAMKF_H__B8EC29D4_C815_417D_8C7C_A34E0C391220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CamKF.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCamKF dialog

class CCamKF : public CDialog
{
// Construction
public:
	CCamKF(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCamKF)
	enum { IDD = IDD_KEYFRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamKF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCamKF)
	afx_msg void OnDestroylink();
	afx_msg void OnLinktocamdst();
	afx_msg void OnLinktocamsrc();
	afx_msg void OnLinktoshape();
	afx_msg void OnMovept();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMKF_H__B8EC29D4_C815_417D_8C7C_A34E0C391220__INCLUDED_)
