// editpg2.cpp : implementation file
//

#include "stdafx.h"
#include "editcmd.h"
#include "editpg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorPage2 property page

IMPLEMENT_DYNCREATE(CEditorPage2, CPropertyPage)

CEditorPage2::CEditorPage2(CCrystalEditView *pParent /*= NULL*/) : CPropertyPage(CEditorPage2::IDD), m_pParent (pParent), m_curdef (NULL), m_processed (0)
{
	//{{AFX_DATA_INIT(CEditorPage2)
    m_nEoln = 0;
    m_bFnBrace = FALSE;
    m_bBackspaceAtBOL = TRUE;
    m_bSelMargin = TRUE;
    m_bWordWrap = FALSE;
	//}}AFX_DATA_INIT
}

CEditorPage2::~CEditorPage2()
{
}

void CEditorPage2::UpdateStatus ()
{
  if (m_curdef)
    {
      m_bBackspaceAtBOL = (m_curdef->flags & SRCOPT_BSATBOL) != FALSE;
      m_bSelMargin = (m_curdef->flags & SRCOPT_SELMARGIN) != FALSE;
      m_bWordWrap = (m_curdef->flags & SRCOPT_WORDWRAP) != FALSE;
      m_bFnBrace = (m_curdef->flags & SRCOPT_FNBRACE) != FALSE;
      if (m_curdef->flags & SRCOPT_EOLNDOS)
        {
          m_nEoln = 1;
        }
      else if (m_curdef->flags & SRCOPT_EOLNUNIX)
        {
          m_nEoln = 2;
        }
      else if (m_curdef->flags & SRCOPT_EOLNMAC)
        {
          m_nEoln = 3;
        }
      else /* eoln auto */
        {
          m_nEoln = 0;
        }
    }
  GetDlgItem (IDC_WORDWRAP)->EnableWindow (m_processed);
  GetDlgItem (IDC_BACKSP_AT_BOL)->EnableWindow (m_processed);
  GetDlgItem (IDC_SEL_MARGIN)->EnableWindow (m_processed);
  GetDlgItem (IDC_EOLN_AUTO)->EnableWindow (m_processed);
  GetDlgItem (IDC_EOLN_DOS)->EnableWindow (m_processed);
  GetDlgItem (IDC_EOLN_UNIX)->EnableWindow (m_processed);
  GetDlgItem (IDC_EOLN_MAC)->EnableWindow (m_processed);
  GetDlgItem (IDC_FNBRACE)->EnableWindow (m_processed);
  UpdateData (FALSE);
  if (m_processed > 1)
    {
      ((CButton*) GetDlgItem (IDC_WORDWRAP))->SetCheck (2);
      ((CButton*) GetDlgItem (IDC_BACKSP_AT_BOL))->SetCheck (2);
      ((CButton*) GetDlgItem (IDC_SEL_MARGIN))->SetCheck (2);
      ((CButton*) GetDlgItem (IDC_EOLN_AUTO))->SetCheck (0);
      ((CButton*) GetDlgItem (IDC_EOLN_DOS))->SetCheck (0);
      ((CButton*) GetDlgItem (IDC_EOLN_UNIX))->SetCheck (0);
      ((CButton*) GetDlgItem (IDC_EOLN_MAC))->SetCheck (0);
      ((CButton*) GetDlgItem (IDC_FNBRACE))->SetCheck (2);
    }
  UpdateData (TRUE);
}

void CEditorPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorPage2)
  DDX_Radio (pDX, IDC_EOLN_AUTO, m_nEoln);
  DDX_Check (pDX, IDC_FNBRACE, m_bFnBrace);
  DDX_Check (pDX, IDC_BACKSP_AT_BOL, m_bBackspaceAtBOL);
  DDX_Check (pDX, IDC_SEL_MARGIN, m_bSelMargin);
  DDX_Check (pDX, IDC_WORDWRAP, m_bWordWrap);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditorPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CEditorPage2)
ON_BN_CLICKED (IDC_EOLN_AUTO, OnModified)
ON_BN_CLICKED (IDC_EOLN_DOS, OnModified)
ON_BN_CLICKED (IDC_EOLN_UNIX, OnModified)
ON_BN_CLICKED (IDC_EOLN_MAC, OnModified)
ON_BN_CLICKED (IDC_FNBRACE, OnModified)
ON_BN_CLICKED (IDC_SEL_MARGIN, OnModified)
ON_BN_CLICKED (IDC_WORDWRAP, OnModified)
ON_BN_CLICKED (IDC_BACKSP_AT_BOL, OnModified)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorPage2 message handlers

BOOL CEditorPage2::
OnInitDialog ()
{
  if (m_pParent)
    {
      m_bBackspaceAtBOL = !m_pParent->GetDisableBSAtSOL ();
      m_bSelMargin = m_pParent->GetSelectionMargin ();
      m_bWordWrap = m_pParent->GetWordWrapping ();
      m_nEoln = m_pParent->GetCRLFMode () + 1;
      m_bFnBrace = (m_pParent->GetFlags () & SRCOPT_FNBRACE) != 0;
    }
  else
    {
      CCrystalEditView::TextDefinition *def = CCrystalEditView::m_SourceDefs;
      m_bBackspaceAtBOL = def->flags & SRCOPT_BSATBOL;
      m_bSelMargin = def->flags & SRCOPT_SELMARGIN;
      m_bWordWrap = def->flags & SRCOPT_WORDWRAP;
      m_nEoln = def->flags & SRCOPT_EOLNDOS ? 1 : (def->flags & SRCOPT_EOLNUNIX ? 2 : (def->flags & SRCOPT_EOLNMAC ? 3 : 0));
      m_bFnBrace = def->flags & SRCOPT_FNBRACE;
    }

  CPropertyPage::OnInitDialog ();
  UpdateStatus ();

  return TRUE;
}

void CEditorPage2::
OnModified ()
{
  ((CPropertyPage*) (GetParent ()->GetParent ()))->SetModified ();
}
