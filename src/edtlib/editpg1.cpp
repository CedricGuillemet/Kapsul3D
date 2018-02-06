// editpg1.cpp : implementation file
//

#include "stdafx.h"
#include "editcmd.h"
#include "editpg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorPage1 property page

IMPLEMENT_DYNCREATE(CEditorPage1, CPropertyPage)

CEditorPage1::CEditorPage1(CCrystalEditView *pParent /*= NULL*/) : CPropertyPage(CEditorPage1::IDD), m_pParent (pParent), m_curdef (NULL), m_processed (0)
{
	//{{AFX_DATA_INIT(CEditorPage1)
    m_nInsertTabs = 0;
    m_nTabSize = 4;
    m_bShowTabs = FALSE;
    m_nBraces = 0;
    m_bAutoIndent = TRUE;
	//}}AFX_DATA_INIT
}

CEditorPage1::~CEditorPage1()
{
}

void CEditorPage1::UpdateStatus ()
{
  if (m_curdef)
    {
      m_nInsertTabs = (m_curdef->flags & SRCOPT_INSERTTABS) == FALSE;
      m_nTabSize = m_curdef->tabsize;
      m_bShowTabs = (m_curdef->flags & SRCOPT_SHOWTABS) != FALSE;
      m_bAutoIndent = (m_curdef->flags & SRCOPT_AUTOINDENT) != FALSE;
      if (m_curdef->flags & SRCOPT_BRACEANSI)
        {
          m_nBraces = 1;
        }
      else if (m_curdef->flags & SRCOPT_BRACEGNU)
        {
          m_nBraces = 2;
        }
      else /*no braces indent */
        {
          m_nBraces = 0;
        }
    }
  GetDlgItem (IDC_INSERT_TABS)->EnableWindow (m_processed);
  GetDlgItem (IDC_INSERT_SPACES)->EnableWindow (m_processed);
  GetDlgItem (IDC_TAB_SIZE)->EnableWindow (m_curdef != NULL);
  GetDlgItem (IDC_SHOW_TABS)->EnableWindow (m_processed);
  GetDlgItem (IDC_AUTOINDENT)->EnableWindow (m_processed);
  GetDlgItem (IDC_BRACES_NO)->EnableWindow (m_processed);
  GetDlgItem (IDC_BRACES_ANSI)->EnableWindow (m_processed);
  GetDlgItem (IDC_BRACES_GNU)->EnableWindow (m_processed);
  UpdateData (FALSE);
  if (m_processed > 1)
    {
      ((CButton*) GetDlgItem (IDC_INSERT_TABS))->SetCheck (0);
      ((CButton*) GetDlgItem (IDC_INSERT_SPACES))->SetCheck (0);
      ((CEdit*) GetDlgItem (IDC_TAB_SIZE))->SetWindowText (_T ("0"));
      ((CButton*) GetDlgItem (IDC_SHOW_TABS))->SetCheck (2);
      ((CButton*) GetDlgItem (IDC_AUTOINDENT))->SetCheck (2);
      ((CButton*) GetDlgItem (IDC_BRACES_NO))->SetCheck (0);
      ((CButton*) GetDlgItem (IDC_BRACES_ANSI))->SetCheck (0);
      ((CButton*) GetDlgItem (IDC_BRACES_GNU))->SetCheck (0);
    }
  UpdateData (TRUE);
}

void CEditorPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorPage1)
  DDX_Radio (pDX, IDC_INSERT_TABS, m_nInsertTabs);
  DDX_Radio (pDX, IDC_BRACES_NO, m_nBraces);
  DDX_Text (pDX, IDC_TAB_SIZE, m_nTabSize);
  DDX_Check (pDX, IDC_SHOW_TABS, m_bShowTabs);
  DDX_Check (pDX, IDC_AUTOINDENT, m_bAutoIndent);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditorPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CEditorPage1)
ON_BN_CLICKED (IDC_INSERT_TABS, OnModified)
ON_BN_CLICKED (IDC_INSERT_SPACES, OnModified)
ON_BN_CLICKED (IDC_BRACES_NO, OnModified)
ON_BN_CLICKED (IDC_BRACES_ANSI, OnModified)
ON_BN_CLICKED (IDC_BRACES_GNU, OnModified)
ON_BN_CLICKED (IDC_AUTOINDENT, OnModified)
ON_BN_CLICKED (IDC_SHOW_TABS, OnModified)
ON_EN_CHANGE (IDC_TAB_SIZE, OnModified)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorPage1 message handlers

BOOL CEditorPage1::
OnInitDialog ()
{
  if (m_pParent)
    {
      m_nInsertTabs = m_pParent->GetInsertTabs () ? 0 : 1;
      m_nTabSize = m_pParent->GetTabSize ();
      m_bShowTabs = m_pParent->GetViewTabs ();
      m_bAutoIndent = m_pParent->GetAutoIndent ();
      if (m_pParent->GetFlags () & SRCOPT_BRACEANSI)
        {
          m_nBraces = 1;
        }
      else if (m_pParent->GetFlags () & SRCOPT_BRACEGNU)
        {
          m_nBraces = 2;
        }
      else
        {
          m_nBraces = 0;
        }
    }
  else
    {
      CCrystalEditView::TextDefinition *def = CCrystalEditView::m_SourceDefs;
      m_nInsertTabs  = def->flags & SRCOPT_INSERTTABS ? 0 : 1;
      m_bShowTabs = def->flags & SRCOPT_SHOWTABS;
      m_bAutoIndent = def->flags & SRCOPT_AUTOINDENT;
      m_nBraces = def->flags & SRCOPT_BRACEANSI ? 1 : (def->flags & SRCOPT_BRACEGNU ? 2 : 0);
      m_nTabSize = def->tabsize;
    }

  CPropertyPage::OnInitDialog ();
  UpdateStatus ();

  return TRUE;
}

void CEditorPage1::
OnModified ()
{
  ((CPropertyPage*) (GetParent ()->GetParent ()))->SetModified ();
}
