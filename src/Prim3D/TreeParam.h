#if !defined(AFX_TREEPARAM_H__C855F5B2_F861_4C1D_BE7E_213A2C630861__INCLUDED_)
#define AFX_TREEPARAM_H__C855F5B2_F861_4C1D_BE7E_213A2C630861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeParam.h : header file
//
class CKPluginPrim3D;
/////////////////////////////////////////////////////////////////////////////
// CTreeParam dialog

class CTreeParam : public CDialog
{
    DECLARE_DYNCREATE(CTreeParam)

// Construction
public:
	CTreeParam(CWnd* pParent = NULL);   // standard constructor
	CKPluginPrim3D *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CTreeParam)
	enum { IDD = IDD_MODDIAG2 };
	CSliderCtrl	m_Twist;
	CSliderCtrl	m_Threshold;
	CSliderCtrl	m_LeafSize;
	CSliderCtrl	m_BranchSize;
	CSliderCtrl	m_BranchNoise;
	CSliderCtrl	m_BranchBias;
	CSliderCtrl	m_Branch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CTreeParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEPARAM_H__C855F5B2_F861_4C1D_BE7E_213A2C630861__INCLUDED_)
