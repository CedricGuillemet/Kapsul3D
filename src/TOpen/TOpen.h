// TOpen.h : main header file for the TOPEN application
//

#if !defined(AFX_TOPEN_H__1445E609_15C5_4D23_932E_E325DF1BA9AA__INCLUDED_)
#define AFX_TOPEN_H__1445E609_15C5_4D23_932E_E325DF1BA9AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTOpenApp:
// See TOpen.cpp for the implementation of this class
//

class CTOpenApp : public CWinApp
{
public:
	CTOpenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTOpenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTOpenApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPEN_H__1445E609_15C5_4D23_932E_E325DF1BA9AA__INCLUDED_)
