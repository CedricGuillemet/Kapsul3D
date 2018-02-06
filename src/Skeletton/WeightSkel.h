#if !defined(AFX_WEIGHTSKEL_H__A0C4B35F_71F3_40C4_946C_D001E9E6DEBC__INCLUDED_)
#define AFX_WEIGHTSKEL_H__A0C4B35F_71F3_40C4_946C_D001E9E6DEBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WeightSkel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWeightSkel dialog

class CWeightSkel : public CDialog
{
// Construction
public:
	CWeightSkel(CWnd* pParent = NULL);   // standard constructor
	CKPluginSkeleton *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CWeightSkel)
	enum { IDD = IDD_WEIGHTS };
	CComboBox	m_ListSkels;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeightSkel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWeightSkel)
	afx_msg void OnAssignobj();
	afx_msg void OnSeltobone();
	afx_msg void OnGetsel();
	afx_msg void OnUnassigned();
	afx_msg void OnAutoWeights();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEIGHTSKEL_H__A0C4B35F_71F3_40C4_946C_D001E9E6DEBC__INCLUDED_)
