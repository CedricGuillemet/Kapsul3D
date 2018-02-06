#ifndef __EDITPG1_INCLUDED__
#define __EDITPG1_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// editpg1.h : header file
//

#include "ccrystaleditview.h"

/////////////////////////////////////////////////////////////////////////////
// CEditorPage1 dialog

class CEditorPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditorPage1)

// Construction
public:
	CEditorPage1(CCrystalEditView *pParent = NULL);
	~CEditorPage1();

// Dialog Data
	//{{AFX_DATA(CEditorPage1)
	enum { IDD = IDD_EDITOR_PAGE1 };
    int m_nInsertTabs;
    int m_nBraces;
    int m_nTabSize;
    BOOL m_bShowTabs;
    BOOL m_bAutoIndent;
	//}}AFX_DATA

  CCrystalEditView *m_pParent;
  CCrystalEditView::TextDefinition *m_curdef;
  int m_processed;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditorPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog ();
	//}}AFX_VIRTUAL

public:
  void UpdateStatus ();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEditorPage1)
    afx_msg void OnModified ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __EDITPG1_INCLUDED__
