#if !defined(AFX_BUILDSKEL_H__0A1BA93A_A5EC_431E_A48B_355E841B3C07__INCLUDED_)
#define AFX_BUILDSKEL_H__0A1BA93A_A5EC_431E_A48B_355E841B3C07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuildSkel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuildSkel dialog

class CBuildSkel : public CDialog
{
// Construction
public:
	CBuildSkel(CWnd* pParent = NULL);   // standard constructor
	CKPluginSkeleton *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CBuildSkel)
	enum { IDD = IDD_BUILD };
	CButton	m_MoveDot;
	CButton	m_DelBone;
	CButton	m_AddRoot;
	CButton	m_AddBone;
	//}}AFX_DATA

    void UnSetPlugin(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildSkel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CBuildSkel)
	afx_msg void OnAddbone();
	afx_msg void OnAddroot();
	afx_msg void OnDelbone();
	afx_msg void OnMovedot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILDSKEL_H__0A1BA93A_A5EC_431E_A48B_355E841B3C07__INCLUDED_)
