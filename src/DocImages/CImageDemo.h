// CImageDemo.h : main header file for the CIMAGEDEMO application
//

#if !defined(AFX_CIMAGEDEMO_H__CD874C06_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_)
#define AFX_CIMAGEDEMO_H__CD874C06_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoApp:
// See CImageDemo.cpp for the implementation of this class
//

class CCImageDemoApp : public CWinApp
{
public:
	BOOL m_bUseDithering;
	CCImageDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCImageDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCImageDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CIMAGEDEMO_H__CD874C06_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_)
