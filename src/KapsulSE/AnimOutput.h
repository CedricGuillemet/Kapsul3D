#if !defined(AFX_ANIMOUTPUT_H__8C6BF1E2_AB68_4E60_94F5_5186C98E146B__INCLUDED_)
#define AFX_ANIMOUTPUT_H__8C6BF1E2_AB68_4E60_94F5_5186C98E146B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimOutput.h : header file
//
#include "OutputDump.h"
#include "Animate.h"

/////////////////////////////////////////////////////////////////////////////
// CAnimOutput dialog

class CAnimOutput : public CDialog
{
// Construction
public:
	CAnimOutput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimOutput)
	enum { IDD = IDD_ANIMOUTPUT };
	CTabCtrl	m_Tabs;
	//}}AFX_DATA

	COutputDump	m_Dump;
	CAnimate m_Animate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOk() {};
	virtual void OnCancel() {};


	// Generated message map functions
	//{{AFX_MSG(CAnimOutput)
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMOUTPUT_H__8C6BF1E2_AB68_4E60_94F5_5186C98E146B__INCLUDED_)
