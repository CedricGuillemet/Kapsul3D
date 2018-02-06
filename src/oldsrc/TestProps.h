#if !defined(AFX_TESTPROPS_H__81888889_8B00_4FDD_BEAA_A72B098F4ED3__INCLUDED_)
#define AFX_TESTPROPS_H__81888889_8B00_4FDD_BEAA_A72B098F4ED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestProps.h : header file
//
#include "FPSPropertyList.h"
#include "EntityType.h"
/////////////////////////////////////////////////////////////////////////////
// CTestProps dialog

class CTestProps : public CDialog
{
// Construction
public:
	CTestProps(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestProps)
	enum { IDD = IDD_ENTITYTEST };
	CComboBox	m_EntList;
	CStatic	m_PropCont;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestProps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFPSPropertyList m_nPropList;
    CEntityType *CurEnt;
	// Generated message map functions
	//{{AFX_MSG(CTestProps)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEntliste();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPROPS_H__81888889_8B00_4FDD_BEAA_A72B098F4ED3__INCLUDED_)
