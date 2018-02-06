///////////////////////////////////////////////////////////////////////////
//  File:    editoroptionspage.h
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl
//  E-mail:     prantl@ff.cuni.cz
//
//  Editor options property page for options sheet
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITOROPTIONSPAGE_H__F6C77180_0B88_11D3_A2B7_006008C080F4__INCLUDED_)
#define AFX_EDITOROPTIONSPAGE_H__F6C77180_0B88_11D3_A2B7_006008C080F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// editoroptionspage.h : header file
//

#include "ccrystaleditview.h"
#include "psheet2.h"
#include "editpg1.h"
#include "editpg2.h"
#include "editpg3.h"

/////////////////////////////////////////////////////////////////////////////
// CEditorOptionsPage dialog

class EDITPADC_CLASS CEditorOptionsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditorOptionsPage)

// Construction
public:
	CEditorOptionsPage(CCrystalEditView *pParent = NULL);
	~CEditorOptionsPage();

// Dialog Data
	//{{AFX_DATA(CEditorOptionsPage)
	enum { IDD = IDD_EDITOR_PAGE };
    BOOL m_bNone;
    BOOL m_bAsp;
    BOOL m_bBasic;
    BOOL m_bBatch;
    BOOL m_bC;
    BOOL m_bAutoDcl;
    BOOL m_bFortran;
    BOOL m_bHtml;
    BOOL m_bInstallShield;
    BOOL m_bJava;
    BOOL m_bAutoLisp;
    BOOL m_bPascal;
    BOOL m_bPerl;
    BOOL m_bPhp;
    BOOL m_bPython;
    BOOL m_bRsrc;
    BOOL m_bRexx;
    BOOL m_bSgml;
    BOOL m_bSh;
    BOOL m_bSiod;
    BOOL m_bSql;
    BOOL m_bTcl;
    BOOL m_bTex;
	//}}AFX_DATA

  CCrystalEditView *m_pParent;
  CCrystalEditView::TextDefinition *m_curdef;
  int m_processed;
  bool m_parent;
  CPropertySheet2 m_Sheet;
  CEditorPage1 m_Page1;
  CEditorPage2 m_Page2;
  CEditorPage3 m_Page3;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditorOptionsPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog ();
	//}}AFX_VIRTUAL

  void UpdateStatus ();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEditorOptionsPage)
    virtual void OnOK ();
    afx_msg void OnSelectAll ();
    afx_msg void OnUnselectAll ();
    afx_msg void OnSrcTypeChanged ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITOROPTIONSPAGE_H__F6C77180_0B88_11D3_A2B7_006008C080F4__INCLUDED_)
