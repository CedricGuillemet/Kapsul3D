#ifndef __EDITPG2_INCLUDED__
#define __EDITPG2_INCLUDED__

#if _MSC_VER > 2000
#pragma once
#endif // _MSC_VER > 2000
// editpg2.h : header file
//

#include "ccrystaleditview.h"

/////////////////////////////////////////////////////////////////////////////
// CEditorPage2 dialog

class CEditorPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditorPage2)

// Construction
public:
	CEditorPage2(CCrystalEditView *pParent = NULL);
	~CEditorPage2();

// Dialog Data
	//{{AFX_DATA(CEditorPage2)
	enum { IDD = IDD_EDITOR_PAGE2 };
    int m_nEoln;
    BOOL m_bFnBrace;
    BOOL m_bBackspaceAtBOL;
    BOOL m_bSelMargin;
    BOOL m_bWordWrap;
	//}}AFX_DATA

  CCrystalEditView *m_pParent;
  CCrystalEditView::TextDefinition *m_curdef;
  int m_processed;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditorPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog ();
	//}}AFX_VIRTUAL

public:
  void UpdateStatus ();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEditorPage2)
    afx_msg void OnModified ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __EDITPG2_INCLUDED__
