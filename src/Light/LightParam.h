#if !defined(AFX_LIGHTPARAM_H__FA6D3422_8694_490C_BC62_B516AE36C39E__INCLUDED_)
#define AFX_LIGHTPARAM_H__FA6D3422_8694_490C_BC62_B516AE36C39E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLightParam dialog

class CLightParam : public CDialog
{
// Construction
public:
	CLightParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLightParam)
	enum { IDD = IDD_PARAM };
	CSliderCtrl	m_SlidRadius;
	CStatic	m_TextRadius;
	CStatic	m_Color;
	//}}AFX_DATA

	void SetText(double RadVal);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CLightParam)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	virtual void OnOK( ); 
	virtual void OnCancel( ); 
	afx_msg void OnColor();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTPARAM_H__FA6D3422_8694_490C_BC62_B516AE36C39E__INCLUDED_)
