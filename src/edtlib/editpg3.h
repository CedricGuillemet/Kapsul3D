#ifndef __EDITPG3_INCLUDED__
#define __EDITPG3_INCLUDED__

#if _MSC_VER > 2000
#pragma once
#endif // _MSC_VER > 2000
// editpg3.h : header file
//

#include "ccrystaleditview.h"

/////////////////////////////////////////////////////////////////////////////
// CEditorPage3 dialog

class CEditorPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditorPage3)

// Construction
public:
	CEditorPage3(CCrystalEditView *pParent = NULL);
	~CEditorPage3();

// Dialog Data
	//{{AFX_DATA(CEditorPage3)
	enum { IDD = IDD_EDITOR_PAGE3 };
    CComboBox m_ctlEncodings;
    CString m_sExtensions;
    int m_nEncoding;
	//}}AFX_DATA

  CCrystalEditView *m_pParent;
  CCrystalEditView::TextDefinition *m_curdef;
  int m_processed;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditorPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog ();
	//}}AFX_VIRTUAL

public:
  void UpdateStatus ();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEditorPage3)
    afx_msg void OnModified ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __EDITPG3_INCLUDED__
