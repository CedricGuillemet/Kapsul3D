///////////////////////////////////////////////////////////////////////////
//  File:    fontcomb.cpp
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl, portions by Stcherbatchenko Andrei
//  E-mail:     prantl@ff.cuni.cz
//
//  Combo-box to offer list of available fonts
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "fontcomb.h"
#include "fontpgrc.h"

#if defined (ARX_WITH_MFC) && defined (_DEBUG)
// #define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined (ARX_WITH_MFC) && defined (_DEBUG)

#define ICON_DELTA 2
#define TEXT_DELTA 2
#define ICON_WIDTH 12
#define ICON_COUNT 2

#pragma warning ( disable : 4711 )
/////////////////////////////////////////////////////////////////////////////
// CLayerListAwt

IMPLEMENT_DYNAMIC (CFontComboBox, CComboBox)

CFontComboBox::CFontComboBox ()
{
  m_imagelistType.Create (IDB_FONTTYPE, ICON_WIDTH, ICON_COUNT, RGB (0, 255, 0));
  // m_imagelistType.SetBkColor (GetSysColor (COLOR_WINDOW));
}

CFontComboBox::~CFontComboBox ()
{
}

void CFontComboBox::
DrawItem (LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  CDC *pDC = CDC::FromHandle (lpDrawItemStruct->hDC);
  CRect rc = lpDrawItemStruct->rcItem;
  rc.left += ICON_DELTA;
  int iImage = GetItemData (lpDrawItemStruct->itemID);
  if (iImage)
    {
      m_imagelistType.Draw (pDC, iImage, rc.TopLeft (), ILD_TRANSPARENT);
    }
  rc.left += ICON_WIDTH;
  if (lpDrawItemStruct->itemState & ODS_SELECTED)
    {
      pDC->SetTextColor (::GetSysColor (COLOR_HIGHLIGHTTEXT));
      pDC->SetBkColor (::GetSysColor (COLOR_HIGHLIGHT));
    }
  else
    {
      pDC->SetTextColor (::GetSysColor (COLOR_WINDOWTEXT));
      pDC->SetBkColor (::GetSysColor (COLOR_WINDOW));
    }
  CString sText;
  GetLBText (lpDrawItemStruct->itemID, sText);
  CSize sz = pDC->GetTextExtent (sText);
  rc.right = rc.left + sz.cx + (TEXT_DELTA << 1);
  pDC->ExtTextOut (rc.left + TEXT_DELTA, rc.top, ETO_OPAQUE, rc, sText, NULL);
  if (lpDrawItemStruct->itemState & ODS_FOCUS && GetFocus () == this)
    {
      pDC->DrawFocusRect (rc);
    }
}

BEGIN_MESSAGE_MAP (CFontComboBox, CComboBox)
//{{AFX_MSG_MAP(CFontComboBox)
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
// CLayerListAwt message handlers

/////////////////////////////////////////////////////////////////////////////
#pragma warning ( default : 4711 )
