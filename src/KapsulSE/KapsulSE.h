// Kapsul.h : main header file for the KAPSUL application
//

#if !defined(AFX_KAPSUL_H__46F73017_C31F_4C1D_803E_6D12EAB4582D__INCLUDED_)
#define AFX_KAPSUL_H__46F73017_C31F_4C1D_803E_6D12EAB4582D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "WinAppEx.h"
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CKapsulApp:
// See Kapsul.cpp for the implementation of this class
//

class CKapsulApp : public CWinAppEx
{
public:
	CKapsulApp();
	void OpenCmdLine(char *FileName);
	bool FullScreen;
    /*
	CMultiDocTemplate* pDocTemplate3D;
	CMultiDocTemplate* pDocTemplateScript;
    */
    CMultiDocTemplate* pDocTemplate,*pDocScript;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKapsulApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle( LONG lCount ); 
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CKapsulApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnWindowTogglefullscreen();
	afx_msg void OnHelpContents();
	afx_msg void OnHelpIndex();
	afx_msg void OnHelpSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KAPSUL_H__46F73017_C31F_4C1D_803E_6D12EAB4582D__INCLUDED_)
