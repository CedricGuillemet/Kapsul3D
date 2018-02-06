#if !defined(AFX_NBFRAMES_H__9B4CA5A2_8155_4BC0_8D8A_5B1FAAC4C56D__INCLUDED_)
#define AFX_NBFRAMES_H__9B4CA5A2_8155_4BC0_8D8A_5B1FAAC4C56D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NbFrames.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNbFrames dialog
#include "Kapsul3D.h"
class CNbFrames : public CDialog
{
// Construction
public:
	CNbFrames(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNbFrames)
	enum { IDD = IDD_ANIMNBFRAMES };
	CSpinButtonCtrl	m_Spin;
	CEdit	m_NbFrames;
	//}}AFX_DATA
    int nbFrames;
    bool Rescal;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNbFrames)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNbFrames)
	virtual BOOL OnInitDialog();
	afx_msg void OnRescale();
	afx_msg void OnRadio2();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NBFRAMES_H__9B4CA5A2_8155_4BC0_8D8A_5B1FAAC4C56D__INCLUDED_)
