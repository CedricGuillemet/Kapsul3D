// TerrainEd.h : main header file for the TERRAINED application
//

#if !defined(AFX_TERRAINED_H__ADD68CF2_3F34_4E81_891D_BC78DA4FAAA3__INCLUDED_)
#define AFX_TERRAINED_H__ADD68CF2_3F34_4E81_891D_BC78DA4FAAA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTerrainEdApp:
// See TerrainEd.cpp for the implementation of this class
//

class CTerrainEdApp : public CWinApp
{
public:
	CTerrainEdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTerrainEdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTerrainEdApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TERRAINED_H__ADD68CF2_3F34_4E81_891D_BC78DA4FAAA3__INCLUDED_)
