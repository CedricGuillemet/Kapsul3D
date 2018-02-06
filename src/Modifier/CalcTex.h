#if !defined(AFX_CALCTEX_H__7B0EB569_F73F_4234_97E9_700F719C43FE__INCLUDED_)
#define AFX_CALCTEX_H__7B0EB569_F73F_4234_97E9_700F719C43FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalcTex.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalcTex dialog
//#include "UVMapper.h"
#include "ModModifier.h"

class CCalcTex : public CDialog
{
// Construction
public:
	CCalcTex(CWnd* pParent = NULL);   // standard constructor
	CKPluginModifier *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CCalcTex)
	enum { IDD = IDD_CALCTEX };
	CButton	m_MapSphere;
	CButton	m_MapPlanar;
	CButton	m_MapCyl;
	CButton	m_MapCube;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalcTex)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalcTex)
	afx_msg void OnMapcube();
	afx_msg void OnMapcyl();
	afx_msg void OnMapplanar();
	afx_msg void OnMapspherical();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCTEX_H__7B0EB569_F73F_4234_97E9_700F719C43FE__INCLUDED_)
