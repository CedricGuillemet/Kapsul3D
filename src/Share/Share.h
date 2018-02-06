// Share.h : main header file for the SHARE application
//

#if !defined(AFX_SHARE_H__AD0F56B2_AE94_4898_A685_1BFF66E38E28__INCLUDED_)
#define AFX_SHARE_H__AD0F56B2_AE94_4898_A685_1BFF66E38E28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShareApp:
// See Share.cpp for the implementation of this class
//

class CShareApp : public CWinApp
{
public:
	CShareApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShareApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHARE_H__AD0F56B2_AE94_4898_A685_1BFF66E38E28__INCLUDED_)
