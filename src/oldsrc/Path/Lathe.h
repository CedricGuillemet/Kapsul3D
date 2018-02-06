#if !defined(AFX_LATHE_H__2851D79E_3839_4CCE_AF28_F068462A343F__INCLUDED_)
#define AFX_LATHE_H__2851D79E_3839_4CCE_AF28_F068462A343F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lathe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLathe dialog

class CLathe : public CDialog
{
// Construction
public:
	CLathe(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLathe)
	enum { IDD = IDD_LATHE };
	CStatic	m_LatheScale;
	CSliderCtrl	m_LatheVal;
	CStatic	m_ShapeName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLathe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( ) {};
	virtual void OnCancel( ) {};

	// Generated message map functions
	//{{AFX_MSG(CLathe)
	afx_msg void OnShape();
	afx_msg void OnLatheit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LATHE_H__2851D79E_3839_4CCE_AF28_F068462A343F__INCLUDED_)
