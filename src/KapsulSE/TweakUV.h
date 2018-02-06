#if !defined(AFX_TWEAKUV_H__D5625C39_32E2_4179_87D1_8E5F8463F812__INCLUDED_)
#define AFX_TWEAKUV_H__D5625C39_32E2_4179_87D1_8E5F8463F812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TweakUV.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTweakUV dialog

class CTweakUV : public CDialog
{
// Construction
public:
	CTweakUV(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTweakUV)
	enum { IDD = IDD_TWEAKUV };
	CNumSpinCtrl	m_ShiftY;
	CNumSpinCtrl	m_ShiftX;
	CNumSpinCtrl	m_ScaleY;
	CNumSpinCtrl	m_ScaleX;
	CNumSpinCtrl	m_Rotate;
	CNumEdit	m_EditShiftY;
	CNumEdit	m_EditShiftX;
	CNumEdit	m_EditScaleY;
	CNumEdit	m_EditScaleX;
	CNumEdit	m_EditRotate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTweakUV)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK() {};
	virtual void OnCancel() {};
	// Generated message map functions
	//{{AFX_MSG(CTweakUV)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TWEAKUV_H__D5625C39_32E2_4179_87D1_8E5F8463F812__INCLUDED_)
