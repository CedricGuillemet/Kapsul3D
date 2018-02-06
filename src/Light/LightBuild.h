#if !defined(AFX_LIGHTBUILD_H__6AF92E49_03A0_4806_AD72_EB9533311E6B__INCLUDED_)
#define AFX_LIGHTBUILD_H__6AF92E49_03A0_4806_AD72_EB9533311E6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightBuild.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLightBuild dialog

class CLightBuild : public CDialog
{
// Construction
public:
	CLightBuild(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLightBuild)
	enum { IDD = IDD_BUILD };
	CButton	m_BuildIt;
	CButton	m_Omni;
	CButton	m_Spot;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightBuild)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLightBuild)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	afx_msg void OnOmni();
	afx_msg void OnSpot();
	virtual void OnOK( ); 
	virtual void OnCancel( ); 
	afx_msg void OnNeon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTBUILD_H__6AF92E49_03A0_4806_AD72_EB9533311E6B__INCLUDED_)
