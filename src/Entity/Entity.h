// Entity.h : main header file for the ENTITY DLL
//

#if !defined(AFX_ENTITY_H__B85B8888_146C_4CF0_8004_54050BA21418__INCLUDED_)
#define AFX_ENTITY_H__B85B8888_146C_4CF0_8004_54050BA21418__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEntityApp
// See Entity.cpp for the implementation of this class
//

class CEntityApp : public CWinApp
{
public:
	CEntityApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntityApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEntityApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTITY_H__B85B8888_146C_4CF0_8004_54050BA21418__INCLUDED_)
