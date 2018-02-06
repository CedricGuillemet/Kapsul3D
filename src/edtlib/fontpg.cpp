///////////////////////////////////////////////////////////////////////////
//  File:    fontpg.cpp
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl, portions by Stcherbatchenko Andrei
//  E-mail:     prantl@ff.cuni.cz
//
//  Property page to set font style
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "fontpg.h"
#include "ccrystaltextbuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontPage property page

IMPLEMENT_DYNCREATE(CFontPage, CPropertyPage)

CFontPage::CFontPage(CCrystalTextView *pParent /*= NULL*/, LPLOGFONT pLogFont /*= NULL*/) : CPropertyPage(CFontPage::IDD), m_pParent (pParent), m_pLogFont (pLogFont)
{
    //{{AFX_DATA_INIT(CFontPage)
    //}}AFX_DATA_INIT
    CWindowDC dc(GetDesktopWindow() );
    m_cyPixelsPerInch = GetDeviceCaps(dc, LOGPIXELSY);
    if (!m_pLogFont)
      {
        m_pLogFont = &CCrystalTextView::m_LogFont;
        /*m_pLogFont = &m_LogFont;
        CFont *pFont = dc.GetCurrentFont ();
        pFont->GetLogFont (m_pLogFont);*/
      }
    m_fontSample.CreateFontIndirect (m_pLogFont);
    m_sFont = m_pLogFont->lfFaceName;
    m_sSize.Format (_T ("%d"), -MulDiv (m_pLogFont->lfHeight, 72, m_cyPixelsPerInch));
    static BYTE CharSetCodes[] = { 177, 178, 161, 162, 186, 238, 204, 0 };
    static LPCTSTR CharSetNames[] = { _T("Western"), _T("Hebrew"), _T("Arabic"), _T("Greek"),
      _T("Turkish"), _T("Baltic"), _T("Central European"), _T("Cyrillic") };
    LPBYTE p = (LPBYTE) _tcschr ((LPCTSTR) CharSetCodes, m_pLogFont->lfCharSet);
    if (p && *p)
      m_sScript = CharSetNames[(p - CharSetCodes) + 1];
    else
      m_sScript = _T("Western");
    m_nEncoding = CCrystalTextBuffer::m_nDefaultEncoding;
    m_bRecode = m_nEncoding >= 0;
}

CFontPage::~CFontPage()
{
}

void CFontPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFontPage)
    DDX_Control(pDX, IDC_SAMPLE, m_staticSample);
    DDX_Control(pDX, IDC_FONT, m_comboFont);
    DDX_Control(pDX, IDC_FONTSIZE, m_comboSize);
    DDX_Control(pDX, IDC_SCRIPT, m_comboScript);
  	DDX_Control(pDX, IDC_ENCODING, m_comboEncoding);
    DDX_CBString(pDX, IDC_FONT, m_sFont);
    DDX_CBString(pDX, IDC_FONTSIZE, m_sSize);
    DDV_MaxChars(pDX, m_sSize, LF_FACESIZE);
    DDX_CBString(pDX, IDC_SCRIPT, m_sScript);
    DDX_Check(pDX, IDC_RECODE, m_bRecode);
  	DDX_CBIndex(pDX, IDC_ENCODING, m_nEncoding);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontPage, CPropertyPage)
    //{{AFX_MSG_MAP(CFontPage)
    ON_CBN_SELCHANGE(IDC_FONT, OnSelChange)
    ON_CBN_SELCHANGE(IDC_FONTSIZE, OnSelChange)
    ON_CBN_SELCHANGE(IDC_SCRIPT, OnSelChange)
    ON_CBN_KILLFOCUS(IDC_FONT, OnSelChange)
    ON_CBN_KILLFOCUS(IDC_FONTSIZE, OnSelChange)
    ON_CBN_KILLFOCUS(IDC_SCRIPT, OnSelChange)
    ON_BN_CLICKED(IDC_RECODE, OnRecode)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontPage message handlers

extern EDITPADC_CLASS LPCTSTR pszCodeNames[];
extern EDITPADC_CLASS void FillComboBox (CComboBox &Control, LPCTSTR *pszItems);

BOOL CFontPage::OnInitDialog() 
{
    CPropertyPage::OnInitDialog();
    /*m_imagesFont.Create (IDB_FONTTYPE, 11, 2, RGB (0, 255, 0));
    m_imagesFont.SetBkColor (GetSysColor (COLOR_WINDOW));
    m_comboFont.SetImageList (&m_imagesFont);*/
    m_comboFont.SetItemHeight (-1, 15);
    m_comboFont.SetItemHeight (0, 14);
    m_comboSize.SetItemHeight (-1, 15);
    m_comboSize.SetItemHeight (0, 14);
    CRect rc, rc2;
    m_comboSize.GetWindowRect (rc);
    m_comboFont.GetWindowRect (rc2);
    m_comboFont.SetWindowPos (NULL, -1, -1, rc2.Width (), rc.Height (), SWP_NOZORDER|SWP_NOMOVE);
    CWindowDC dc(this);
    LOGFONT logfont;
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfFaceName[0] = '\0';
    logfont.lfPitchAndFamily = 0;
    EnumFontFamiliesEx (dc.m_hDC, &logfont, (FONTENUMPROC)FontEnumProc, (LPARAM) this, 0);
    int /*i, */j = m_comboFont.FindStringExact (0, m_sFont);
    if (j >= 0)
      m_comboFont.SetCurSel (j);
    
    // Fill Size combobox with "common" sizes
    /*static LPCTSTR FontSizes[] = { _T("8"), _T("9"), _T("10"), _T("11"), _T("12"), _T("14"),
                _T("16"), _T("18"), _T("20"), _T("22"), _T("24"), _T("26"), 
                _T("28"), _T("36"), _T("48"), _T("72") };
    for (i = 0, j = -1; i < (sizeof(FontSizes)/sizeof(FontSizes[0])); i++)
      {
        m_comboSize.AddString(FontSizes[i]);
        if (!_tcscmp (FontSizes[i], m_sSize))
          j = i;
      }
    if (j >= 0)
      m_comboSize.SetCurSel (j);*/
    j = m_comboSize.FindStringExact (0, m_sSize);
    if (j >= 0)
      m_comboSize.SetCurSel (j);

    // Fill Script combobox with "common" scripts
    /*static LPCTSTR CharSetNames[] = { _T("Western"), _T("Hebrew"), _T("Arabic"), _T("Greek"),
      _T("Turkish"), _T("Baltic"), _T("Central European"), _T("Cyrillic") };
    for (i = 0, j = -1; i < (sizeof(CharSetNames)/sizeof(CharSetNames[0])); i++)
      {
        m_comboScript.AddString(CharSetNames[i]);
        if (!_tcscmp (CharSetNames[i], m_sScript))
          j = i;
      }
    if (j >= 0)
      m_comboScript.SetCurSel (j);*/
    j = m_comboScript.FindStringExact (0, m_sScript);
    if (j >= 0)
      m_comboScript.SetCurSel (j);

    FillComboBox (m_comboEncoding, pszCodeNames);
    m_comboEncoding.SetCurSel (m_nEncoding);
    m_comboEncoding.EnableWindow (m_bRecode);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

int CALLBACK CFontPage::FontEnumProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, 
        int FontType, CFontPage* pFontPage )
{
    if( pFontPage->m_comboFont.FindStringExact( 0, lpelfe->elfLogFont.lfFaceName ) == CB_ERR &&
      lpelfe->elfLogFont.lfPitchAndFamily & FIXED_PITCH)
      {
        // Add to list
        /*COMBOBOXEXITEM item;
        item.mask = CBEIF_IMAGE|CBEIF_TEXT|CBEIF_SELECTEDIMAGE;
        item.iItem = pFontPage->m_comboFont.GetCount ();
        item.pszText = (LPTSTR)(LPCTSTR)lpelfe->elfFullName;
        item.iImage = item.iSelectedImage = 1;
        pFontPage->m_comboFont.InsertItem (&item);*/
        int item = pFontPage->m_comboFont.AddString( lpelfe->elfLogFont.lfFaceName );
        pFontPage->m_comboFont.SetItemData (item, lpelfe->elfLogFont.lfOutPrecision != OUT_STRING_PRECIS);
      }

    return 1;
}

void CFontPage::OnRecode() 
{
  UpdateData ();
  m_comboEncoding.EnableWindow (m_bRecode);
}

void CFontPage::OnSelChange() 
{
  // The selection hasn't changed yet, so change it
  if( IsChild( GetFocus() ) && 
          GetFocus()->GetParent()->IsKindOf( RUNTIME_CLASS( CComboBox ) ) )
  {
      CComboBox *cb = (CComboBox *)GetFocus()->GetParent();
      CString sText;
      if( cb->GetCurSel() != CB_ERR )
      {
          cb->GetLBText( cb->GetCurSel(), sText );
          cb->SetWindowText( sText );
      }
  }

  UpdateData(TRUE);
  
  m_fontSample.GetLogFont( &m_LogFont );
  memcpy( m_LogFont.lfFaceName, m_sFont, LF_FACESIZE );

  m_LogFont.lfHeight = -MulDiv(_ttoi (m_sSize), m_cyPixelsPerInch, 72);
  static BYTE CharSetCodes[] = { 0, 177, 178, 161, 162, 186, 238, 204 };
  m_LogFont.lfCharSet = CharSetCodes[m_comboScript.GetCurSel ()];

  m_fontSample.DeleteObject();
  m_fontSample.CreateFontIndirect( &m_LogFont );
  m_staticSample.SetFont(&m_fontSample);  
  SetModified ();
}

void CFontPage::OnOK() 
{
	CPropertyPage::OnOK();
  m_fontSample.GetLogFont (m_pLogFont);
  if (m_pParent)
    {
      m_pParent->SetFont (*m_pLogFont);
    }
  SetModified (FALSE);
  CCrystalTextBuffer::m_nDefaultEncoding = m_bRecode ? m_nEncoding : -1;
}
