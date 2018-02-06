// KUpNet.h : main header file for the KUPNET application
//

#if !defined(AFX_KUPNET_H__C4D23931_2B6F_47B0_A966_231069203FBD__INCLUDED_)
#define AFX_KUPNET_H__C4D23931_2B6F_47B0_A966_231069203FBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKUpNetApp:
// See KUpNet.cpp for the implementation of this class
//

class CKUpNetApp : public CWinApp
{
public:
	CKUpNetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKUpNetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKUpNetApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KUPNET_H__C4D23931_2B6F_47B0_A966_231069203FBD__INCLUDED_)
