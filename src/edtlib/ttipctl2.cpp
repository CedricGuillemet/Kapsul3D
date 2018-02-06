///////////////////////////////////////////////////////////////////////////
//  File:    ttipctl2.cpp
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl, portions by MFC Codeguru "gurus"
//  E-mail:     prantl@ff.cuni.cz, http://www.codeguru.com
//
//  Tooltip control extension
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ttipctl2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipCtrl2

CToolTipCtrl2::CToolTipCtrl2 ()
{
}

CToolTipCtrl2:: ~ CToolTipCtrl2 ()
{
}


BEGIN_MESSAGE_MAP (CToolTipCtrl2, CToolTipCtrl)
//{{AFX_MSG_MAP(CToolTipCtrl2)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
// CToolTipCtrl2 message handlers

COLORREF CToolTipCtrl2::SetBkColor (COLORREF crColor)
{
  COLORREF oldColor;

  oldColor = SendMessage (TTM_GETTIPBKCOLOR, 0, 0);
  SendMessage (TTM_SETTIPBKCOLOR, (WPARAM) (COLORREF) crColor, 0);

  return oldColor;
}

COLORREF CToolTipCtrl2::
SetTextColor (COLORREF crColor)
{
  COLORREF oldColor;

  oldColor = SendMessage (TTM_GETTIPTEXTCOLOR, 0, 0);
  SendMessage (TTM_SETTIPTEXTCOLOR, (WPARAM) (COLORREF) crColor, 0);

  return oldColor;
}

COLORREF CToolTipCtrl2::
GetBkColor ()
{
  return SendMessage (TTM_GETTIPBKCOLOR, 0, 0);
}

COLORREF CToolTipCtrl2::
GetTextColor ()
{
  return SendMessage (TTM_GETTIPTEXTCOLOR, 0, 0);
}

int CToolTipCtrl2::
SetDelayTime (DWORD dwType, int nTime)
{
  // dwType can be one of the following:
  // TTDT_AUTOPOP - The length of time the tooltip window
  // remains visible if the pointer is stationary within a tool's
  // bounding rectangle.
  //
  // TTDT_INITIAL - The length of time the pointer must
  // remain stationary within a tool's bounding rectangle before
  // the tooltip window appears.
  //
  // TTDT_RESHOW  The length of time it takes for
  // subsequent tooltip windows to appear as the pointer moves
  // from one tool to another.
  int nDuration;

  switch (dwType)
    {
    case TTDT_AUTOPOP:
    case TTDT_INITIAL:
    case TTDT_RESHOW:
      nDuration = SendMessage (TTM_GETDELAYTIME, (DWORD) dwType, 0);
      SendMessage (TTM_SETDELAYTIME, (WPARAM) (DWORD) dwType, (LPARAM) (INT) MAKELONG (nTime, 0));
      return nDuration;
    }
  return -1;
}

int CToolTipCtrl2::
GetDelayTime (DWORD dwType)
{
  // dwType can be one of the following:
  // TTDT_AUTOPOP - Retrieve the length of time the tooltip window
  // remains visible if the pointer is stationary within a tool's
  // bounding rectangle.
  //
  // TTDT_INITIAL - Retrieve the length of time the pointer must
  // remain stationary within a tool's bounding rectangle before
  // the tooltip window appears.
  //
  // TTDT_RESHOW  Retrieve the length of time it takes for
  // subsequent tooltip windows to appear as the pointer moves
  // from one tool to another.
  switch (dwType)
    {
    case TTDT_AUTOPOP :
    case TTDT_INITIAL:
    case TTDT_RESHOW:
      return SendMessage (TTM_GETDELAYTIME, (DWORD) dwType, 0);
    }
  return -1;
}

void CToolTipCtrl2::
GetMargin (LPRECT lpRect)
{
  // lpRect.top  Distance between top border and top of tooltip
  //   text, in pixels.
  // lpRect.left  Distance between left border and left end of
  //   tooltip text, in pixels.
  // lpRect.bottom  Distance between bottom border and bottom of
  //   tooltip text, in pixels.
  // lpRect.right  Distance between right border and right end of
  //   tooltip text, in pixels
  SendMessage (TTM_GETMARGIN, 0, (LPARAM) (LPRECT) lpRect);
}

int CToolTipCtrl2::
GetMaxTipWidth ()
{
  // The maximum tooltip width value does not indicate a tooltip
  // window's actual width. Rather, if a tooltip string exceeds
  // the maximum width, the control breaks the text into multiple
  // lines, using spaces to determine line breaks. If the text
  // cannot be segmented into multiple lines, it will be dis-
  // played on a single line. The length of this line may exceed
  // the maximum tooltip width.
  // Defaults to -1 when tooltip control is first created.
  return SendMessage (TTM_GETMAXTIPWIDTH, 0, 0);
}

RECT CToolTipCtrl2::
SetMargin (LPRECT lpRect)
{
  // lpRect.top  Distance between top border and top of tooltip
  //   text, in pixels.
  // lpRect.left  Distance between left border and left end of
  //   tooltip text, in pixels.
  // lpRect.bottom  Distance between bottom border and bottom of
  //   tooltip text, in pixels.
  // lpRect.right  Distance between right border and right end of
  //   tooltip text, in pixels.
  RECT TempRect;
  GetMargin (&TempRect);
  SendMessage (TTM_SETMARGIN, 0, (LPARAM) (LPRECT) lpRect);

  return TempRect;
}

int CToolTipCtrl2::
SetMaxTipWidth (int nWidth)
{
  // The maximum tooltip width value does not indicate a tooltip
  // window's actual width. Rather, if a tooltip string exceeds
  // the maximum width, the control breaks the text into multiple
  // lines, using spaces to determine line breaks. If the text
  // cannot be segmented into multiple lines, it will be dis-
  // played on a single line. The length of this line may exceed
  // the maximum tooltip width.
  return SendMessage (TTM_SETMAXTIPWIDTH, 0, (LPARAM) (INT) nWidth);
}

void CToolTipCtrl2::
TrackActivate (BOOL bActivate, LPTOOLINFO lpti)
{
  SendMessage (TTM_TRACKACTIVATE, (WPARAM) (BOOL) bActivate,
               (LPARAM) (LPTOOLINFO) lpti);
}

void CToolTipCtrl2::
TrackPosition (LPPOINT lppt)
{
  // The tooltip control chooses where to display the tooltip
  // window based on the coordinates you provide with this
  // message. This causes the tooltip window to appear beside the
  // tool to which it corresponds. To have tooltip windows
  // displayed at specific coordinates, include the TTF_ABSOLUTE
  // flag in the uFlags member of the TOOLINFO structure when
  // adding the tool.
  SendMessage (TTM_TRACKPOSITION, 0, (LPARAM) (DWORD) MAKELONG (lppt->x, lppt->y));
}

void CToolTipCtrl2::
TrackPosition (int xPos, int yPos)
{
  // The tooltip control chooses where to display the tooltip
  // window based on the coordinates you provide with this
  // message. This causes the tooltip window to appear beside the
  // tool to which it corresponds. To have tooltip windows
  // displayed at specific coordinates, include the TTF_ABSOLUTE
  // flag in the uFlags member of the TOOLINFO structure when
  // adding the tool.
  SendMessage (TTM_TRACKPOSITION, 0, (LPARAM) (DWORD) MAKELONG (xPos, yPos));
}
