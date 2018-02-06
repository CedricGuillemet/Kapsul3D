#if !defined(AFX_KSTATUSBAR_H__34240D53_0335_449A_BACF_D86E408F6884__INCLUDED_)
#define AFX_KSTATUSBAR_H__34240D53_0335_449A_BACF_D86E408F6884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKStatusBar dialog

class CKStatusBar : public CDialog
{
// Construction
public:
	CKStatusBar(CWnd* pParent = NULL);   // standard constructor
	void UpdateChecks();
	void UpdateCBOption();
	void SetCB(CKScene *pScene);
// Dialog Data
	//{{AFX_DATA(CKStatusBar)
	enum { IDD = IDD_STATUSBAR };
	CButtonST2	m_Z;
	CButtonST2	m_Y;
	CButtonST2	m_X;
	CComboBox	m_GridList;
	CComboBox	m_AngleList;
	CNumSpinCtrl	m_SpinZ;
	CNumSpinCtrl	m_SpinY;
	CNumSpinCtrl	m_SpinX;
	CStatic	m_Scroll;
	CStatic	m_Read;
	CStatic	m_Over;
	CStatic	m_Num;
	CStatic	m_LineXY;
	CStatic	m_Infos;
	CButtonST2	m_Grid;
	CNumEdit	m_EditZ;
	CNumEdit	m_EditY;
	CNumEdit	m_EditX;
	CButtonST2	m_Crossing;
	CEdit	m_Console;
	CButtonST2	m_Centroid;
	CStatic	m_Caps;
	CButtonST2	m_Angle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKStatusBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CKScene *m_Scene;
	afx_msg void OnOk();
	afx_msg void OnCancel();

	// Generated message map functions
	//{{AFX_MSG(CKStatusBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCrossing();
	afx_msg void OnCentroid();
	afx_msg void OnAngle();
	afx_msg void OnGrid();
	afx_msg void OnSelchangeGridlist();
	afx_msg void OnSelchangeAnglelist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSTATUSBAR_H__34240D53_0335_449A_BACF_D86E408F6884__INCLUDED_)
