#include "stdafx.h"
#include "resource.h"
#include "richevw2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CRichEditView2, CRichEditView)

BEGIN_MESSAGE_MAP(CRichEditView2, CRichEditView)
  //{{AFX_MSG_MAP(CRichEditView2)
  //}}AFX_MSG_MAP
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditView2 construction/destruction

CRichEditView2::CRichEditView2()
{
}

CRichEditView2::~CRichEditView2()
{
}

CString CRichEditView2::GetRTF()
{
  // Return the RTF string of the text in the control.
  
  // Stream out here.
  EDITSTREAM es;
  es.dwError = 0;
  es.pfnCallback = CBStreamOut;   // Set the callback

  CString sRTF = "";

  es.dwCookie = (DWORD) &sRTF;  // so sRTF receives the string
  
  GetRichEditCtrl().StreamOut(SF_RTF, es);      // Call CRichEditCtrl::StreamOut to get the string.
  ///

  return sRTF;
}

void CRichEditView2::SetRTF(CString sRTF)
{
  // Put the RTF string sRTF into the rich edit control.

  // Read the text in
  EDITSTREAM es;
  es.dwError = 0;
  es.pfnCallback = CBStreamIn;
  es.dwCookie = (DWORD) &sRTF;
  GetRichEditCtrl().StreamIn(SF_RTF, es); // Do it.
}

/*
  Callback function to stream an RTF string into the rich edit control.
*/
DWORD CALLBACK CRichEditView2::CBStreamIn(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
  // We insert the rich text here.

/*  
  This function taken from CodeGuru.com
  http://www.codeguru.com/richedit/rtf_string_streamin.shtml
  Zafir Anjum
*/

  CString *pstr = (CString *) dwCookie;

  if (pstr->GetLength() < cb)
  {
    *pcb = pstr->GetLength();
    memcpy(pbBuff, (LPCTSTR) *pstr, *pcb);
    pstr->Empty();
  }
  else
  {
    *pcb = cb;
    memcpy(pbBuff, (LPCTSTR) *pstr, *pcb);
    *pstr = pstr->Right(pstr->GetLength() - cb);
  }
  ///

  return 0;
}

/*
  Callback function to stream the RTF string out of the rich edit control.
*/
DWORD CALLBACK CRichEditView2::CBStreamOut(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
  // Address of our string var is in psEntry
  CString *psEntry = (CString*) dwCookie;
  

  CString tmpEntry = "";
  tmpEntry = (CString) pbBuff;

  // And write it!!!
  *psEntry += tmpEntry.Left(cb);

  return 0;
}

bool CRichEditView2::SelectionIsBold()
{
  CHARFORMAT cf = GetCharFormat();  
  
  if (cf.dwEffects & CFM_BOLD)
    return true;
  else
    return false;
}

bool CRichEditView2::SelectionIsItalic()
{
  CHARFORMAT cf = GetCharFormat();  
  
  if (cf.dwEffects & CFM_ITALIC)
    return true;
  else
    return false;
}

bool CRichEditView2::SelectionIsUnderlined()
{
  CHARFORMAT cf = GetCharFormat();  
  
  if (cf.dwEffects & CFM_UNDERLINE)
    return true;
  else
    return false;
}

CHARFORMAT CRichEditView2::GetCharFormat(DWORD dwMask)
{
  CHARFORMAT cf;
  cf.cbSize = sizeof(CHARFORMAT);

  cf.dwMask = dwMask;

  GetRichEditCtrl().GetSelectionCharFormat(cf);

  return cf;
}

void CRichEditView2::SetCharStyle(int MASK, int STYLE, int nStart, int nEnd)
{
  CHARFORMAT cf;
  cf.cbSize = sizeof(CHARFORMAT);
  //cf.dwMask = MASK;
  CRichEditCtrl &ctl = GetRichEditCtrl();
  
  ctl.GetSelectionCharFormat(cf);
  
  if (cf.dwMask & MASK) // selection is all the same
  {
    cf.dwEffects ^= STYLE; 
  }
  else
  {
    cf.dwEffects |= STYLE;
  }
  
  cf.dwMask = MASK;

  ctl.SetSelectionCharFormat(cf);

}

void CRichEditView2::SetSelectionBold()
{
  long start=0, end=0;
  GetRichEditCtrl().GetSel(start, end);   // Get the current selection

  SetCharStyle(CFM_BOLD, CFE_BOLD, start, end); // Make it bold
}

void CRichEditView2::SetSelectionItalic()
{
  long start=0, end=0;
  GetRichEditCtrl().GetSel(start, end);

  SetCharStyle(CFM_ITALIC, CFE_ITALIC, start, end);
}

void CRichEditView2::SetSelectionUnderlined()
{
  long start=0, end=0;
  GetRichEditCtrl().GetSel(start, end);

  SetCharStyle(CFM_UNDERLINE, CFE_UNDERLINE, start, end);
}

void CRichEditView2::SetParagraphCenter()
{
  PARAFORMAT paraFormat;    
  paraFormat.cbSize = sizeof(PARAFORMAT);
  paraFormat.dwMask = PFM_ALIGNMENT;    
  paraFormat.wAlignment = PFA_CENTER;
  
  SetParaFormat(paraFormat);  // Set the paragraph.
}

void CRichEditView2::SetParagraphLeft()
{
  PARAFORMAT paraFormat;
  paraFormat.cbSize = sizeof(PARAFORMAT);
  paraFormat.dwMask = PFM_ALIGNMENT;    
  paraFormat.wAlignment = PFA_LEFT;
  
  SetParaFormat(paraFormat);
}

void CRichEditView2::SetParagraphRight()
{
  PARAFORMAT paraFormat;
  paraFormat.cbSize = sizeof(PARAFORMAT);
  paraFormat.dwMask = PFM_ALIGNMENT;    
  paraFormat.wAlignment = PFA_RIGHT;
  
  SetParaFormat(paraFormat);
}

bool CRichEditView2::ParagraphIsCentered()
{
  PARAFORMAT pf = GetParagraphFormat();

  if (pf.wAlignment == PFA_CENTER)
    return true;
  else
    return false;
}

bool CRichEditView2::ParagraphIsLeft()
{
  PARAFORMAT pf = GetParagraphFormat();

  if (pf.wAlignment == PFA_LEFT)
    return true;
  else
    return false;
}

bool CRichEditView2::ParagraphIsRight()
{
  PARAFORMAT pf = GetParagraphFormat();

  if (pf.wAlignment == PFA_RIGHT)
    return true;
  else
    return false;
}

PARAFORMAT CRichEditView2::GetParagraphFormat()
{
  PARAFORMAT pf;
  pf.cbSize = sizeof(PARAFORMAT);

  pf.dwMask = PFM_ALIGNMENT | PFM_NUMBERING;      

  GetRichEditCtrl().GetParaFormat(pf);

  return pf;
}

void CRichEditView2::SetParagraphBulleted()
{
  PARAFORMAT paraformat = GetParagraphFormat();

  if ( (paraformat.dwMask & PFM_NUMBERING) && (paraformat.wNumbering == PFN_BULLET) )
  {
    paraformat.wNumbering = 0;
    paraformat.dxOffset = 0;
    paraformat.dxStartIndent = 0;
    paraformat.dwMask = PFM_NUMBERING | PFM_STARTINDENT | PFM_OFFSET;
  }
  else
  {
    paraformat.wNumbering = PFN_BULLET;
    paraformat.dwMask = PFM_NUMBERING;
    if (paraformat.dxOffset == 0)
    {
      paraformat.dxOffset = 4;
      paraformat.dwMask = PFM_NUMBERING | PFM_STARTINDENT | PFM_OFFSET;
    }
  }
  
  SetParaFormat(paraformat);

}

bool CRichEditView2::ParagraphIsBulleted()
{
  PARAFORMAT pf = GetParagraphFormat();

  if (pf.wNumbering == PFN_BULLET)
    return true;
  else
    return false;
}

void CRichEditView2::SelectColor()
{
  CColorDialog dlg;

  CHARFORMAT cf = GetCharFormat();

  if (cf.dwEffects & CFE_AUTOCOLOR) cf.dwEffects -= CFE_AUTOCOLOR;

  // Get a color from the common color dialog.
  if( dlg.DoModal() == IDOK )
  { 
    cf.crTextColor = dlg.GetColor();
  }

  cf.dwMask = CFM_COLOR;

  GetRichEditCtrl().SetSelectionCharFormat(cf);
}

void CRichEditView2::SetFontName(CString sFontName)
{
  CHARFORMAT cf = GetCharFormat();

  // Set the font name.
#ifdef _UNICODE
  WideCharToMultiByte (CP_ACP,  // CodePage
                       0,  // dwFlags
                       (LPCTSTR) sFontName,    // lpWideCharStr
                       -1,     // cchWideChar
                       cf.szFaceName,     // lpMultiByteStr
                       //sizeof(cf.szFaceName), // cchMultiByte, wrong. sizeof on a pointer, psk, psk
                       LF_FACESIZE,
                       NULL,    // lpDefaultChar,
                       NULL);  // lpUsedDefaultChar
#else // _UNICODE
  _tcscpy (cf.szFaceName, (LPCTSTR) sFontName);
#endif // _UNICODE

  cf.dwMask = CFM_FACE;

  GetRichEditCtrl().SetSelectionCharFormat(cf);
}

void CRichEditView2::SetFontSize(int nPointSize)
{
  CHARFORMAT cf = GetCharFormat();

  nPointSize *= 20; // convert from to twips
  cf.yHeight = nPointSize;
  
  cf.dwMask = CFM_SIZE;

  GetRichEditCtrl().SetSelectionCharFormat(cf);
}

void CRichEditView2::GetSystemFonts(CStringArray &saFontList)
{
  CDC *pDC = GetDC ();

  EnumFonts (pDC->GetSafeHdc(),NULL,(FONTENUMPROC) CBEnumFonts,(LPARAM)&saFontList);//Enumerate

}

BOOL CALLBACK CRichEditView2::CBEnumFonts(LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData)
{
  // This function was written with the help of CCustComboBox, by Girish Bharadwaj.
  // Available from Codeguru.

  if (dwType == TRUETYPE_FONTTYPE) 
  {
    ((CStringArray *) lpData)->Add( lplf->lfFaceName );
  }

  return true;
}

CString CRichEditView2::GetSelectionFontName()
{
  CHARFORMAT cf = GetCharFormat();

  CString sName = cf.szFaceName;

  return sName;
}

long CRichEditView2::GetSelectionFontSize()
{
  CHARFORMAT cf = GetCharFormat();

  long nSize = cf.yHeight/20;

  return nSize;
}

/////////////////////////////////////////////////////////////////////////////
// CRichEditView2 printing

BOOL CRichEditView2::OnPreparePrinting(CPrintInfo* pInfo)
{
  // default preparation
  return DoPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CRichEditView2 diagnostics

#ifdef _DEBUG
void CRichEditView2::AssertValid() const
{
  CRichEditView::AssertValid();
}

void CRichEditView2::Dump(CDumpContext& dc) const
{
  CRichEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRichEditView2 message handlers

/////////////////////////////////////////////////////////////////////////////
