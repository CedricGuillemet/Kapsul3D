// editpg3.cpp : implementation file
//

#include "stdafx.h"
#include "editcmd.h"
#include "editpg3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorPage3 property page

IMPLEMENT_DYNCREATE(CEditorPage3, CPropertyPage)

CEditorPage3::CEditorPage3(CCrystalEditView *pParent /*= NULL*/) : CPropertyPage(CEditorPage3::IDD), m_pParent (pParent), m_curdef (NULL), m_processed (0)
{
	//{{AFX_DATA_INIT(CEditorPage3)
  m_sExtensions = _T ("");
  m_nEncoding = 0;
	//}}AFX_DATA_INIT
}

CEditorPage3::~CEditorPage3()
{
}

void CEditorPage3::UpdateStatus ()
{
  if (m_curdef)
    {
      m_nEncoding = m_curdef->encoding + 1;
      m_sExtensions = m_curdef->exts;
    }
  GetDlgItem (IDC_ENCODING)->EnableWindow (m_curdef != NULL);
  GetDlgItem (IDC_EXTENSIONS)->EnableWindow (m_curdef != NULL);
  UpdateData (FALSE);
  if (m_processed > 1)
    {
      ((CEdit*) GetDlgItem (IDC_EXTENSIONS))->SetWindowText (_T (""));
      m_ctlEncodings.SetCurSel (-1);
    }
  UpdateData (TRUE);
}

void CEditorPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorPage3)
  DDX_Control (pDX, IDC_ENCODING, m_ctlEncodings);
  DDX_Text (pDX, IDC_EXTENSIONS, m_sExtensions);
  DDX_CBIndex (pDX, IDC_ENCODING, m_nEncoding);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditorPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CEditorPage3)
ON_EN_CHANGE (IDC_EXTENSIONS, OnModified)
ON_EN_CHANGE (IDC_ENCODING, OnModified)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorPage3 message handlers

extern EDITPADC_CLASS LPCTSTR pszCodeNames[];
extern EDITPADC_CLASS void FillComboBox (CComboBox &Control, LPCTSTR *pszItems);

BOOL CEditorPage3::
OnInitDialog ()
{
  if (m_pParent)
    {
      m_sExtensions = m_curdef ? m_curdef->exts : _T ("");
      m_nEncoding = m_curdef ? m_curdef->encoding + 1 : 0;
    }
  else
    {
      CCrystalEditView::TextDefinition *def = CCrystalEditView::m_SourceDefs;
      m_sExtensions = def->exts;
      m_nEncoding = def->encoding + 1;
    }

  CPropertyPage::OnInitDialog ();
  FillComboBox (m_ctlEncodings, pszCodeNames);
  m_ctlEncodings.InsertString(0, _T ("No recoding"));
  m_ctlEncodings.SetCurSel (m_nEncoding);
  UpdateStatus ();

  return TRUE;
}

void CEditorPage3::
OnModified ()
{
  ((CPropertyPage*) (GetParent ()->GetParent ()))->SetModified ();
}
