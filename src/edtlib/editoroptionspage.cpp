///////////////////////////////////////////////////////////////////////////
//  File:    editoroptionspage.cpp
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

#include "stdafx.h"
#include "editcmd.h"
#include "editoroptionspage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorOptionsPage property page

IMPLEMENT_DYNCREATE(CEditorOptionsPage, CPropertyPage)

CEditorOptionsPage::CEditorOptionsPage(CCrystalEditView *pParent /*= NULL*/) : CPropertyPage(CEditorOptionsPage::IDD), m_pParent (pParent), m_curdef (NULL), m_processed (0), m_Page1 (pParent), m_Page2 (pParent), m_Page3 (pParent), m_parent (true)
{
	//{{AFX_DATA_INIT(CEditorOptionsPage)
    m_bNone = FALSE;
    m_bAsp = FALSE;
    m_bBasic = FALSE;
    m_bBatch = FALSE;
    m_bC = FALSE;
    m_bAutoDcl = FALSE;
    m_bFortran = FALSE;
    m_bHtml = FALSE;
    m_bInstallShield = FALSE;
    m_bJava = FALSE;
    m_bAutoLisp = FALSE;
    m_bPascal = FALSE;
    m_bPerl = FALSE;
    m_bPhp = FALSE;
    m_bPython = FALSE;
    m_bRsrc = FALSE;
    m_bRexx = FALSE;
    m_bSgml = FALSE;
    m_bSh = FALSE;
    m_bSiod = FALSE;
    m_bSql = FALSE;
    m_bTcl = FALSE;
    m_bTex = FALSE;
	//}}AFX_DATA_INIT
  if (m_pParent)
    m_Page3.m_curdef = m_Page2.m_curdef = m_Page1.m_curdef = m_curdef = m_pParent->m_CurSourceDef;
  if (m_curdef)
    m_Page3.m_processed = m_Page2.m_processed = m_Page1.m_processed = m_processed = 1;
}

CEditorOptionsPage::~CEditorOptionsPage()
{
}

void CEditorOptionsPage::UpdateStatus ()
{
  CCrystalEditView::TextDefinition *def = CCrystalEditView::m_SourceDefs;
  m_processed = 0;
  m_parent = false;
  for (int i = IDC_NONE; i <= IDC_TEX; i++, def++)
    {
      if (((CButton*) GetDlgItem (i))->GetCheck () == 1)
        {
          m_processed++;
          ASSERT (def);
          m_curdef = def;
          if (m_pParent && m_pParent->m_CurSourceDef == def)
            m_parent = true;
        }
    }
  if (m_processed != 1)
    m_curdef = NULL;
  m_Page3.m_curdef = m_Page2.m_curdef = m_Page1.m_curdef = m_curdef;
  m_Page3.m_processed = m_Page2.m_processed = m_Page1.m_processed = m_processed;
  m_Page1.UpdateStatus ();
  m_Page2.UpdateStatus ();
  m_Page3.UpdateStatus ();
  UpdateData (FALSE);
}

void CEditorOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorOptionsPage)
  DDX_Check (pDX, IDC_NONE, m_bNone);
  DDX_Check (pDX, IDC_ASP, m_bAsp);
  DDX_Check (pDX, IDC_BASIC, m_bBasic);
  DDX_Check (pDX, IDC_BATCH, m_bBatch);
  DDX_Check (pDX, IDC_C, m_bC);
  DDX_Check (pDX, IDC_AUTODCL, m_bAutoDcl);
  DDX_Check (pDX, IDC_FORTRAN, m_bFortran);
  DDX_Check (pDX, IDC_HTML, m_bHtml);
  DDX_Check (pDX, IDC_INSTALLSHIELD, m_bInstallShield);
  DDX_Check (pDX, IDC_JAVA, m_bJava);
  DDX_Check (pDX, IDC_AUTOLISP, m_bAutoLisp);
  DDX_Check (pDX, IDC_PASCAL, m_bPascal);
  DDX_Check (pDX, IDC_PERL, m_bPerl);
  DDX_Check (pDX, IDC_PHP, m_bPhp);
  DDX_Check (pDX, IDC_PYTHON, m_bPython);
  DDX_Check (pDX, IDC_RSRC, m_bRsrc);
  DDX_Check (pDX, IDC_REXX, m_bRexx);
  DDX_Check (pDX, IDC_SGML, m_bSgml);
  DDX_Check (pDX, IDC_SH, m_bSh);
  DDX_Check (pDX, IDC_SIOD, m_bSiod);
  DDX_Check (pDX, IDC_SQL, m_bSql);
  DDX_Check (pDX, IDC_TCL, m_bTcl);
  DDX_Check (pDX, IDC_TEX, m_bTex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditorOptionsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CEditorOptionsPage)
ON_BN_CLICKED (IDC_SELECT_ALL, OnSelectAll)
ON_BN_CLICKED (IDC_UNSELECT_ALL, OnUnselectAll)
ON_BN_CLICKED (IDC_NONE, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_ASP, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_BASIC, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_BATCH, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_C, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_AUTODCL, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_FORTRAN, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_HTML, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_INSTALLSHIELD, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_JAVA, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_AUTOLISP, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_PASCAL, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_PERL, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_PHP, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_PYTHON, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_RSRC, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_REXX, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_SGML, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_SH, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_SIOD, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_SQL, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_TCL, OnSrcTypeChanged)
ON_BN_CLICKED (IDC_TEX, OnSrcTypeChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorOptionsPage message handlers

BOOL CEditorOptionsPage::
OnInitDialog ()
{
  m_Sheet.AddPage (&m_Page1);
  m_Sheet.AddPage (&m_Page2);
  m_Sheet.AddPage (&m_Page3);
  m_Sheet.Create (this, WS_CHILD | WS_VISIBLE, 0);
  m_Sheet.ModifyStyleEx (0, WS_EX_CONTROLPARENT);
  m_Sheet.ModifyStyle (0, WS_TABSTOP);
  CRect rcSheet;
  GetDlgItem (IDC_EDITPAGE1)->GetWindowRect (&rcSheet);
  ScreenToClient (&rcSheet);
  m_Sheet.SetWindowPos (NULL, rcSheet.left - 7, rcSheet.top - 7, 0,0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
  m_Sheet.SetActivePage (&m_Page3);
  m_Sheet.SetActivePage (&m_Page2);
  m_Sheet.SetActivePage (&m_Page1);
  if (m_pParent)
    {
      switch (m_pParent->m_CurSourceDef->type)
      {
      case CCrystalTextView::SRC_PLAIN:
        m_bNone = TRUE;
        break;
      case CCrystalTextView::SRC_ASP:
        m_bAsp = TRUE;
        break;
      case CCrystalTextView::SRC_BASIC:
        m_bBasic = TRUE;
        break;
      case CCrystalTextView::SRC_BATCH:
        m_bBatch = TRUE;
        break;
      case CCrystalTextView::SRC_C:
        m_bC = TRUE;
        break;
      case CCrystalTextView::SRC_DCL:
        m_bAutoDcl = TRUE;
        break;
      case CCrystalTextView::SRC_FORTRAN:
        m_bFortran = TRUE;
        break;
      case CCrystalTextView::SRC_HTML:
        m_bHtml = TRUE;
        break;
      case CCrystalTextView::SRC_INSTALLSHIELD:
        m_bInstallShield = TRUE;
        break;
      case CCrystalTextView::SRC_JAVA:
        m_bJava = TRUE;
        break;
      case CCrystalTextView::SRC_LISP:
        m_bAutoLisp = TRUE;
        break;
      case CCrystalTextView::SRC_PASCAL:
        m_bPascal = TRUE;
        break;
      case CCrystalTextView::SRC_PERL:
        m_bPerl = TRUE;
        break;
      case CCrystalTextView::SRC_PHP:
        m_bPhp = TRUE;
        break;
      case CCrystalTextView::SRC_PYTHON:
        m_bPython = TRUE;
        break;
      case CCrystalTextView::SRC_REXX:
        m_bRexx = TRUE;
        break;
      case CCrystalTextView::SRC_RSRC:
        m_bRsrc = TRUE;
        break;
      case CCrystalTextView::SRC_SGML:
        m_bSgml = TRUE;
        break;
      case CCrystalTextView::SRC_SH:
        m_bSh = TRUE;
        break;
      case CCrystalTextView::SRC_SIOD:
        m_bSiod = TRUE;
        break;
      case CCrystalTextView::SRC_SQL:
        m_bSql = TRUE;
        break;
      case CCrystalTextView::SRC_TCL:
        m_bTcl = TRUE;
        break;
      case CCrystalTextView::SRC_TEX:
        m_bTex = TRUE;
        break;
      }
    }
  else
    {
      CCrystalEditView::TextDefinition *def = CCrystalEditView::m_SourceDefs;
      m_bNone = TRUE;
    }

  CPropertyPage::OnInitDialog ();
  UpdateStatus ();

  return TRUE;
}

void CEditorOptionsPage::
OnSelectAll ()
{
  UpdateData (TRUE);
  m_bNone = TRUE;
  m_bAsp = TRUE;
  m_bBasic = TRUE;
  m_bBatch = TRUE;
  m_bC = TRUE;
  m_bAutoDcl = TRUE;
  m_bFortran = TRUE;
  m_bHtml = TRUE;
  m_bInstallShield = TRUE;
  m_bJava = TRUE;
  m_bAutoLisp = TRUE;
  m_bPascal = TRUE;
  m_bPerl = TRUE;
  m_bPhp = TRUE;
  m_bPython = TRUE;
  m_bRsrc = TRUE;
  m_bRexx = TRUE;
  m_bSgml = TRUE;
  m_bSh = TRUE;
  m_bSiod = TRUE;
  m_bSql = TRUE;
  m_bTcl = TRUE;
  m_bTex = TRUE;
  UpdateData (FALSE);
  UpdateStatus ();
}

void CEditorOptionsPage::
OnUnselectAll ()
{
  UpdateData (TRUE);
  m_bNone = FALSE;
  m_bAsp = FALSE;
  m_bBasic = FALSE;
  m_bBatch = FALSE;
  m_bC = FALSE;
  m_bAutoDcl = FALSE;
  m_bFortran = FALSE;
  m_bHtml = FALSE;
  m_bInstallShield = FALSE;
  m_bJava = FALSE;
  m_bAutoLisp = FALSE;
  m_bPascal = FALSE;
  m_bPerl = FALSE;
  m_bPhp = FALSE;
  m_bPython = FALSE;
  m_bRsrc = FALSE;
  m_bRexx = FALSE;
  m_bSgml = FALSE;
  m_bSh = FALSE;
  m_bSiod = FALSE;
  m_bSql = FALSE;
  m_bTcl = FALSE;
  m_bTex = FALSE;
  UpdateData (FALSE);
  UpdateStatus ();
}

void CEditorOptionsPage::
OnSrcTypeChanged ()
{
  UpdateData (TRUE);
  UpdateStatus ();
}

void CEditorOptionsPage::
OnOK ()
{
  CPropertyPage::OnOK ();
  CPropertyPage *pPage = m_Sheet.GetActivePage ();
  if (pPage == &m_Page1)
    {
      m_Page1.UpdateData ();
      m_Sheet.SetActivePage (&m_Page2);
      m_Page2.UpdateData ();
      m_Sheet.SetActivePage (&m_Page3);
      m_Page3.UpdateData ();
      m_Sheet.SetActivePage (&m_Page1);
    }
  else if (pPage == &m_Page2)
    {
      m_Page2.UpdateData ();
      m_Sheet.SetActivePage (&m_Page1);
      m_Page1.UpdateData ();
      m_Sheet.SetActivePage (&m_Page3);
      m_Page3.UpdateData ();
      m_Sheet.SetActivePage (&m_Page2);
    }
  else
    {
      m_Page3.UpdateData ();
      m_Sheet.SetActivePage (&m_Page1);
      m_Page1.UpdateData ();
      m_Sheet.SetActivePage (&m_Page2);
      m_Page2.UpdateData ();
      m_Sheet.SetActivePage (&m_Page3);
    }
  DWORD dwMask = 0xffffffff, dwFlags = 0;
  if (m_Page1.m_nInsertTabs != -1)
    {
      dwMask ^= SRCOPT_INSERTTABS;
      dwFlags |= !m_Page1.m_nInsertTabs ? SRCOPT_INSERTTABS : 0;
    }
  if (m_Page1.m_bShowTabs != 2)
    {
      dwMask ^= SRCOPT_SHOWTABS;
      dwFlags |= m_Page1.m_bShowTabs ? SRCOPT_SHOWTABS : 0;
    }
  if (m_Page1.m_bAutoIndent != 2)
    {
      dwMask ^= SRCOPT_AUTOINDENT;
      dwFlags |= m_Page1.m_bAutoIndent ? SRCOPT_AUTOINDENT : 0;
    }
  if (m_Page1.m_nBraces != -1)
    {
      dwMask ^= SRCOPT_BRACEANSI|SRCOPT_BRACEGNU;
      dwFlags |= m_Page1.m_nBraces == 1 ? SRCOPT_BRACEANSI : (m_Page1.m_nBraces == 2 ? SRCOPT_BRACEGNU : 0);
    }
  if (m_Page2.m_bBackspaceAtBOL != 2)
    {
      dwMask ^= SRCOPT_BSATBOL;
      dwFlags |= m_Page2.m_bBackspaceAtBOL ? SRCOPT_BSATBOL : 0;
    }
  if (m_Page2.m_bSelMargin != 2)
    {
      dwMask ^= SRCOPT_SELMARGIN;
      dwFlags |= m_Page2.m_bSelMargin ? SRCOPT_SELMARGIN : 0;
    }
  if (m_Page2.m_bWordWrap != 2)
    {
      dwMask ^= SRCOPT_WORDWRAP;
      dwFlags |= m_Page2.m_bWordWrap ? SRCOPT_WORDWRAP : 0;
    }
  if (m_Page2.m_bFnBrace != 2)
    {
      dwMask ^= SRCOPT_FNBRACE;
      dwFlags |= m_Page2.m_bFnBrace ? SRCOPT_FNBRACE : 0;
    }
  if (m_Page2.m_nEoln != -1)
    {
      dwMask ^= SRCOPT_EOLNDOS|SRCOPT_EOLNUNIX|SRCOPT_EOLNMAC;
      dwFlags |= m_Page2.m_nEoln == 1 ? SRCOPT_EOLNDOS : (m_Page2.m_nEoln == 2 ? SRCOPT_EOLNUNIX : (m_Page2.m_nEoln == 3 ? SRCOPT_EOLNMAC : 0));
    }
  if (m_pParent && m_parent)
    {
      m_pParent->SetInsertTabs (!m_Page1.m_nInsertTabs);
      if (m_curdef)
        m_pParent->SetTabSize (m_Page1.m_nTabSize);
      m_pParent->SetViewTabs (m_Page1.m_bShowTabs);
      m_pParent->SetAutoIndent (m_Page1.m_bAutoIndent);
      m_pParent->SetDisableBSAtSOL (!m_Page2.m_bBackspaceAtBOL);
      m_pParent->SetSelectionMargin (m_Page2.m_bSelMargin);
      m_pParent->SetWordWrapping (m_Page2.m_bWordWrap);
      m_pParent->SetCRLFMode (m_Page2.m_nEoln - 1);
      m_pParent->SetFlags (dwFlags);
    }
  if (m_curdef)
    {
      m_curdef->tabsize = m_Page1.m_nTabSize;
      _tcscpy (m_curdef->exts, m_Page3.m_sExtensions);
      m_curdef->encoding = m_Page3.m_nEncoding - 1;
    }
  CCrystalEditView::TextDefinition *def = CCrystalEditView::m_SourceDefs;
  for (int i = IDC_NONE; i <= IDC_TEX; i++, def++)
    {
      ASSERT (def);
      if (((CButton*) GetDlgItem (i))->GetCheck ())
        {
          def->flags &= dwMask;
          def->flags |= dwFlags;
        }
    }
  SetModified (FALSE);
}

BOOL CEditorOptionsPage::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam > 32)
    {
      if (m_Sheet.CheckKey (pMsg->wParam))
        {
          return TRUE;
        }
    }

  return CPropertyPage::PreTranslateMessage(pMsg);
}
