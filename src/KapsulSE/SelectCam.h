#if !defined(AFX_SELECTCAM_H__62951F52_533D_46F8_BC24_212962DCD558__INCLUDED_)
#define AFX_SELECTCAM_H__62951F52_533D_46F8_BC24_212962DCD558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectCam.h : header file
//
#include "resource.h"
//#include "NiceStatic.h"
/////////////////////////////////////////////////////////////////////////////
// CSelectCam dialog

class CSelectCam : public CDialog
{
// Construction
public:
	CSelectCam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectCam)
	enum { IDD = IDD_SELECTCAM };
	CListBox	m_List;
	//}}AFX_DATA


	CKScene *m_Scene;
	CKCamera *SelCam;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectCam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectCam)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	afx_msg void OnCancel();
	afx_msg void OnDblclkListcamera();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTCAM_H__62951F52_533D_46F8_BC24_212962DCD558__INCLUDED_)
