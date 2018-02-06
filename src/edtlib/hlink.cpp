///////////////////////////////////////////////////////////////////////////
//  File:    hlink.cpp
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl, portions by MFC Codeguru "gurus"
//  E-mail:     prantl@ff.cuni.cz, http://www.codeguru.com
//
//  Hyperlink control
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifndef HLINK_NOOLE
#define INITGUID
#endif
#include "resource.h"
#include "editcmd.h"
#ifndef HLINK_NOOLE
#include <initguid.h>
#endif
#include <winnetwk.h>
#include <winnls.h>
#include <shlobj.h>
#ifndef HLINK_NOOLE
#include <intshcut.h>
#endif
#define FP_SRC_HYPERLINK
#include "hlink.h"

/////////////////////////////////  Macros & Statics ///////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////// Implementation //////////////////////////////

#define TOOLTIP_ID 1

BEGIN_MESSAGE_MAP (CHyperlink, CStatic)
ON_WM_CONTEXTMENU ()
//{{AFX_MSG_MAP(CHyperlink)
ON_WM_SETCURSOR ()
ON_WM_LBUTTONDOWN ()
ON_WM_MOUSEMOVE ()
ON_COMMAND (ID_POPUP_OPEN, OnOpen)
ON_COMMAND (ID_POPUP_EDIT, OnEdit)
ON_COMMAND (ID_POPUP_PRINT, OnPrint)
ON_COMMAND (ID_POPUP_COPYSHORTCUT, OnCopyShortcut)
ON_COMMAND (ID_POPUP_PROPERTIES, OnProperties)
ON_WM_CTLCOLOR_REFLECT ()
//}}AFX_MSG_MAP
#ifndef HLINK_NOOLE
ON_COMMAND (ID_POPUP_ADDTOFAVORITES, OnAddToFavorites)
ON_COMMAND (ID_POPUP_ADDTODESKTOP, OnAddToDesktop)
#endif
END_MESSAGE_MAP ()


CHyperlink::CHyperlink ()
{
  m_Color = RGB (0, 0, 255);
  m_VisitedColor = RGB (128, 0, 128);
  m_FailedColor = RGB (128, 128, 128);
  m_HighlightColor = RGB (255, 0, 0);

  m_bShrinkToFit = TRUE;
  m_bUseHighlight = TRUE;
  m_State = ST_NOT_VISITED;
  m_OldState = ST_NOT_VISITED;
  m_bShowingContext = FALSE;
  m_bAllowContextMenu = TRUE;

  //Load up the cursors
  m_hLinkCursor = AfxGetApp ()->LoadCursor (IDC_HLINK);
  m_hBadCursor = AfxGetApp ()->LoadCursor (IDC_HLINK_BAD);
  m_hArrowCursor = AfxGetApp ()->LoadStandardCursor (IDC_ARROW);
}


CHyperlink:: ~ CHyperlink ()
{
}


void CHyperlink::
SetHyperLink (const CString & sActualLink)
{
  SetActualHyperLink (sActualLink);
}


void CHyperlink::
SetHyperLinkDescription (const CString & sDescription)
{
  SetWindowText (sDescription);
}


CString CHyperlink::
GetHyperLinkDescription ()
const
{
  CString sDescription;
  GetWindowText (sDescription);
  return sDescription;
}


void CHyperlink::SetActualHyperLink (const CString & sActualLink)
{
  m_sActualLink = sActualLink;
  CheckActualHyperLink ();
  m_ToolTip.UpdateTipText (m_sToolTip, this, TOOLTIP_ID);
}

void CHyperlink::
CheckActualHyperLink ()
{
  int pos = m_sActualLink.Find (_T ('\n'));
  if (pos != -1)
    {
      SetHyperLinkDescription (m_sActualLink.Left (pos));
      int pos1 = m_sActualLink.Mid (pos + 1).Find (_T ('\n'));
      if (pos1 != -1)
        {
          m_sToolTip = m_sActualLink.Mid (pos + pos1 + 2);
          m_sActualLink = m_sActualLink.Mid (pos + 1, pos1);
        }
      else
        {
          m_sActualLink = m_sActualLink.Mid (pos + 1);
          m_sToolTip = m_sActualLink;
        }
    }
}

BOOL CHyperlink::
OnSetCursor (CWnd * /*pWnd */ , UINT /*nHitTest */ , UINT /*message */ )
{
  if (m_bShowingContext)
    ::SetCursor (m_hArrowCursor);
  else if (m_State == ST_VISIT_FAILED)
    ::SetCursor (m_hBadCursor);
  else
    ::SetCursor (m_hLinkCursor);
  return TRUE;
}

void CHyperlink::
OnLButtonDown (UINT /*nFlags */ , CPoint /*point */ )
{
  PostMessage (WM_COMMAND, ID_POPUP_OPEN);
}


void CHyperlink::
OnOpen ()
{
  if (Open ())
    m_State = ST_VISITED;
  else
    m_State = ST_VISIT_FAILED;
}


void CHyperlink::
OnEdit ()
{
  if (Open (EDIT))
    m_State = ST_VISITED;
  else
    m_State = ST_VISIT_FAILED;
}


void CHyperlink::
OnPrint ()
{
  if (Open (PRINT))
    m_State = ST_VISITED;
  else
    m_State = ST_VISIT_FAILED;
}


void CHyperlink::
SetLinkColor (const COLORREF & color)
{
  m_Color = color;
  UpdateWindow ();
}


void CHyperlink::
SetVisitedLinkColor (const COLORREF & color)
{
  m_VisitedColor = color;
  UpdateWindow ();
}


void CHyperlink::
SetHighlightLinkColor (const COLORREF & color)
{
  m_HighlightColor = color;
  UpdateWindow ();
}


void CHyperlink::
OnMouseMove (UINT nFlags, CPoint point)
{
  if (!m_bUseHighlight)
    return;

  CRect rc;
  GetClientRect (rc);
  if (rc.PtInRect (point))
    {
      if (m_State != ST_HIGHLIGHTED)
        {
          SetCapture ();
          HighLight (TRUE);
        }
    }
  else
    {
      if (m_State == ST_HIGHLIGHTED)
        {
          HighLight (FALSE);
          ReleaseCapture ();
        }
    }

  CStatic::OnMouseMove (nFlags, point);
}


void CHyperlink::
HighLight (BOOL state)
{
  if (state)
    {
      if (m_State != ST_HIGHLIGHTED)
        {
          m_OldState = m_State;
          m_State = ST_HIGHLIGHTED;
          Invalidate ();
        }
    }
  else
    {
      if (m_State == ST_HIGHLIGHTED)
        {
          m_State = m_OldState;
          Invalidate ();
        }
    }
}


void CHyperlink::
OnContextMenu (CWnd *, CPoint point)
{
  if (!m_bAllowContextMenu)
    return;

  HighLight (FALSE);
  ReleaseCapture ();

  if (point.x == -1 && point.y == -1)
    {
      //keystroke invocation
      CRect rect;
      GetClientRect (rect);
      ClientToScreen (rect);

      point = rect.TopLeft ();
      point.Offset (5, 5);
    }

  CMenu menu;
  VERIFY (menu.LoadMenu (IDM_POPUP_HLINK));

  CMenu *pPopup = menu.GetSubMenu (0);
  ASSERT (pPopup != NULL);
  MENUITEMINFO mi;
  mi.fMask = MIIM_STATE;
  mi.fState = MFS_ENABLED | MFS_DEFAULT;
  //VERIFY(SetMenuItemInfo(pPopup->GetSafeHmenu(), ID_POPUP_OPEN, FALSE, &mi));
  SetMenuItemInfo (pPopup->GetSafeHmenu (), ID_POPUP_OPEN, FALSE, &mi);
  CWnd *pWndPopupOwner = this;

  m_bShowingContext = TRUE;
  pPopup->TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
  m_bShowingContext = FALSE;
}


void CHyperlink::
OnCopyShortcut ()
{
  if (OpenClipboard ())
    {
      int nBytes = sizeof (TCHAR) * (m_sActualLink.GetLength () + 1);
      HANDLE hMem = GlobalAlloc (GMEM_MOVEABLE | GMEM_DDESHARE, nBytes);
      TCHAR *pData = (TCHAR *) GlobalLock (hMem);
      _tcscpy (pData, (LPCTSTR) m_sActualLink);
      GlobalUnlock (hMem);
      SetClipboardData (CF_TEXT, hMem);
      CloseClipboard ();
    }
}


void CHyperlink::
OnProperties ()
{
  ShowProperties ();
}


void CHyperlink::
ShowProperties ()
const
{
  CHyperlinkSheet propSheet (IDS_HLINK_PROPERTIES, this->GetParent ());
  propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
  propSheet.SetBuddy (this);
  propSheet.DoModal ();
}


BOOL CHyperlink::Open (int how /*= OPEN*/ )
const
{
  CWaitCursor cursor;

#ifndef HLINK_NOOLE
  //First try to open using IUniformResourceLocator
  BOOL bSuccess = OpenUsingCom (how);

  //As a last resort try ShellExecuting the URL, may
  //even work on Navigator!
  if (!bSuccess)
    bSuccess = OpenUsingShellExecute (how);
#else
  BOOL bSuccess = OpenUsingShellExecute (how);
#endif

  if (!bSuccess)
    bSuccess = OpenUsingRegisteredClass (how);
  return bSuccess;
}

#ifndef HLINK_NOOLE
BOOL CHyperlink::OpenUsingCom (int how /*= OPEN*/ )
const
{
  //Get the URL Com interface
  IUniformResourceLocator *pURL;
  HRESULT hres = CoCreateInstance (CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER, IID_IUniformResourceLocator, (void **) &pURL);
  if (!SUCCEEDED (hres))
    {
      TRACE (_T ("Failed to get the IUniformResourceLocator interface\n"));
      return FALSE;
    }

  hres = pURL->SetURL (m_sActualLink, IURL_SETURL_FL_GUESS_PROTOCOL);
  if (!SUCCEEDED (hres))
    {
      TRACE (_T ("Failed in call to SetURL\n"));
      pURL->Release ();
      return FALSE;
    }

  //Open the URL by calling InvokeCommand
  URLINVOKECOMMANDINFO ivci;
  ivci.dwcbSize = sizeof (URLINVOKECOMMANDINFO);
  ivci.dwFlags = IURL_INVOKECOMMAND_FL_ALLOW_UI;
  ivci.hwndParent = GetParent ()->GetSafeHwnd ();
  switch (how)
    {
    case OPEN:
      ivci.pcszVerb = _T ("open");
      break;
    case EDIT:
      ivci.pcszVerb = _T ("edit");
      break;
    case PRINT:
      ivci.pcszVerb = _T ("print");
      break;
    default:
      ASSERT (FALSE);
    }
  hres = pURL->InvokeCommand (&ivci);
  if (!SUCCEEDED (hres))
    {
      TRACE (_T ("Failed to invoke URL using InvokeCommand\n"));
      pURL->Release ();
      return FALSE;
    }

  // Release the pointer to IUniformResourceLocator.
  pURL->Release ();

  return TRUE;
}
#endif

BOOL CHyperlink::
OpenUsingShellExecute (int how /*= OPEN*/ )
const
{
  LPCTSTR mode;
  switch (how)
    {
    case OPEN:
      mode = _T ("open");
      break;
    case EDIT:
      mode = _T ("edit");
      break;
    case PRINT:
      mode = _T ("print");
      break;
    default:
      ASSERT (FALSE);
      mode = _T ("open");
    }
  HINSTANCE hRun = ShellExecute (GetParent ()->GetSafeHwnd (), mode, m_sActualLink, NULL, NULL, SW_SHOW);
  if ((int) hRun <= HINSTANCE_ERROR)
    {
      TRACE (_T ("Failed to invoke URL using ShellExecute\n"));
      return FALSE;
    }
  return TRUE;
}

LONG
GetRegKey (HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
  HKEY hkey;
  LONG retval = RegOpenKeyEx (key, subkey, 0, KEY_QUERY_VALUE, &hkey);

  if (retval == ERROR_SUCCESS)
    {
      long datasize = MAX_PATH;
      TCHAR data[MAX_PATH];
      RegQueryValue (hkey, NULL, data, &datasize);
      _tcscpy (retdata, data);
      RegCloseKey (hkey);
    }

  return retval;
}

BOOL CHyperlink::
OpenUsingRegisteredClass (int how /*= OPEN*/ )
const
{
  TCHAR key[MAX_PATH + MAX_PATH];
  HINSTANCE result;

  if (GetRegKey (HKEY_CLASSES_ROOT, _T (".htm"), key) == ERROR_SUCCESS)
    {
      LPCTSTR mode;
      switch (how)
        {
        case OPEN:
          mode = _T ("\\shell\\open\\command");
          break;
        case EDIT:
          mode = _T ("\\shell\\edit\\command");
          break;
        case PRINT:
          mode = _T ("\\shell\\print\\command");
          break;
        default:
          mode = _T ("\\shell\\open\\command");
          ASSERT (FALSE);
        }
      _tcscat (key, mode);
      if (GetRegKey (HKEY_CLASSES_ROOT, key, key) == ERROR_SUCCESS)
        {
          LPTSTR pos;
          pos = _tcsstr (key, _T ("\"%1\""));
          if (pos == NULL)
            {              // No quotes found

              pos = _tcsstr (key, _T ("%1"));   // Check for %1, without quotes

              if (pos == NULL)     // No parameter at all...

                pos = key + _tcslen (key) - 1;
              else
                *pos = _T ('\0');  // Remove the parameter

            }
          else
            *pos = _T ('\0');  // Remove the parameter

          _tcscat (pos, _T (" "));
          _tcscat (pos, m_sActualLink);
          USES_CONVERSION;
          result = (HINSTANCE) WinExec (T2A (key), SW_SHOW);
          if ((int) result <= HINSTANCE_ERROR)
            {
              CString str;
              switch ((int) result)
                {
                case 0:
                  str = _T ("The operating system is out\nof memory or resources.");
                  break;
                case SE_ERR_PNF:
                  str = _T ("The specified path was not found.");
                  break;
                case SE_ERR_FNF:
                  str = _T ("The specified file was not found.");
                  break;
                case ERROR_BAD_FORMAT:
                  str = _T ("The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image).");
                  break;
                case SE_ERR_ACCESSDENIED:
                  str = _T ("The operating system denied\naccess to the specified file.");
                  break;
                case SE_ERR_ASSOCINCOMPLETE:
                  str = _T ("The filename association is\nincomplete or invalid.");
                  break;
                case SE_ERR_DDEBUSY:
                  str = _T ("The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed.");
                  break;
                case SE_ERR_DDEFAIL:
                  str = _T ("The DDE transaction failed.");
                  break;
                case SE_ERR_DDETIMEOUT:
                  str = _T ("The DDE transaction could not\nbe completed because the request timed out.");
                  break;
                case SE_ERR_DLLNOTFOUND:
                  str = _T ("The specified dynamic-link library was not found.");
                  break;
                case SE_ERR_NOASSOC:
                  str = _T ("There is no application associated\nwith the given filename extension.");
                  break;
                case SE_ERR_OOM:
                  str = _T ("There was not enough memory to complete the operation.");
                  break;
                case SE_ERR_SHARE:
                  str = _T ("A sharing violation occurred.");
                  break;
                default:
                  str.Format (_T ("Unknown Error (%d) occurred."), (int) result);
                }
              str = _T ("Unable to open hyperlink:\n\n") + str;
              AfxMessageBox (str, MB_ICONEXCLAMATION | MB_OK);
            }
          else
            return TRUE;
        }
    }
  return FALSE;
}

#ifndef HLINK_NOOLE
BOOL CHyperlink::
AddToSpecialFolder (int nFolder)
const
{
  //Give the user some feedback
  CWaitCursor cursor;

  // Get the shell's allocator.
  IMalloc *pMalloc;
  if (!SUCCEEDED (SHGetMalloc (&pMalloc)))
    {
      TRACE (_T ("Failed to get the shell's IMalloc interface\n"));
      return FALSE;
    }

  //Get the location of the special Folder required
  LPITEMIDLIST pidlFolder;
  HRESULT hres = SHGetSpecialFolderLocation (NULL, nFolder, &pidlFolder);
  if (!SUCCEEDED (hres))
    {
      TRACE (_T ("Failed in call to SHGetSpecialFolderLocation\n"));
      pMalloc->Release ();
      return FALSE;
    }

  //convert the PIDL to a file system name and
  //add an extension of URL to create an Internet
  //Shortcut file
  TCHAR sFolder[_MAX_PATH];
  if (!SHGetPathFromIDList (pidlFolder, sFolder))
    {
      TRACE (_T ("Failed in call to SHGetPathFromIDList"));
      pMalloc->Release ();
      return FALSE;
    }
  TCHAR sShortcutFile[_MAX_PATH];

  CString sLinkDescription;
  GetWindowText (sLinkDescription);
  _tmakepath (sShortcutFile, NULL, sFolder, sLinkDescription, _T ("URL"));

  //Free the pidl
  pMalloc->Free (pidlFolder);

  //Do the actual saving
  BOOL bSuccess = Save (sShortcutFile);

  // Release the pointer to IMalloc
  pMalloc->Release ();

  return bSuccess;
}
#endif


#ifndef HLINK_NOOLE
void CHyperlink::
OnAddToFavorites ()
{
  AddToSpecialFolder (CSIDL_FAVORITES);
}
#endif


#ifndef HLINK_NOOLE
void CHyperlink::
OnAddToDesktop ()
{
  AddToSpecialFolder (CSIDL_DESKTOP);
}
#endif


#ifndef HLINK_NOOLE
BOOL CHyperlink::
Save (const CString & sFilename)
const
{
  //Get the URL Com interface
  IUniformResourceLocator *pURL;
  HRESULT hres = CoCreateInstance (CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER, IID_IUniformResourceLocator, (void **) &pURL);
  if (!SUCCEEDED (hres))
    {
      TRACE (_T ("Failed to get the IUniformResourceLocator interface\n"));
      return FALSE;
    }

  hres = pURL->SetURL (m_sActualLink, IURL_SETURL_FL_GUESS_PROTOCOL);
  if (!SUCCEEDED (hres))
    {
      TRACE (_T ("Failed in call to SetURL\n"));
      pURL->Release ();
      return FALSE;
    }

  // Get the IPersistFile interface for
  // saving the shortcut in persistent storage.
  IPersistFile *ppf;
  hres = pURL->QueryInterface (IID_IPersistFile, (void **) &ppf);
  if (!SUCCEEDED (hres))
    {
      TRACE (_T ("Failed to get the IPersistFile interface\n"));
      pURL->Release ();
      return FALSE;
    }

  // Save the shortcut via the IPersistFile::Save member function.
#ifndef _UNICODE
  WORD wsz[_MAX_PATH];
  MultiByteToWideChar (CP_ACP, 0, sFilename, -1, wsz, _MAX_PATH);
  hres = ppf->Save (wsz, TRUE);
#else
  hres = ppf->Save (sFilename, TRUE);
#endif
  if (!SUCCEEDED (hres))
    {
      TRACE (_T ("IPersistFile::Save failed!\n"));
      ppf->Release ();
      pURL->Release ();
      return FALSE;
    }

  // Release the pointer to IPersistFile.
  ppf->Release ();

  // Release the pointer to IUniformResourceLocator.
  pURL->Release ();

  return TRUE;
}
#endif


#ifdef _DEBUG
HBRUSH CHyperlink::
CtlColor (CDC * pDC, UINT nCtlColor)
#else
HBRUSH CHyperlink::
CtlColor (CDC * pDC, UINT /*nCtlColor */ )
#endif
{
  ASSERT (nCtlColor == CTLCOLOR_STATIC);

  DWORD dwStyle = GetStyle ();
  if (!(dwStyle & SS_NOTIFY))
    {
      // Turn on notify flag to get mouse messages and STN_CLICKED.
      // Otherwise, I'll never get any mouse clicks!
      ::SetWindowLong (m_hWnd, GWL_STYLE, dwStyle | SS_NOTIFY);
    }


  HBRUSH hbr = NULL;
  if ((dwStyle & 0xFF) <= SS_RIGHT)
    {
      // Modify the font to be underline
      if (!((HFONT) m_font))
        {
          LOGFONT lf;
          GetFont ()->GetObject (sizeof (lf), &lf);

          lf.lfUnderline = TRUE;
          m_font.CreateFontIndirect (&lf);
        }
      pDC->SelectObject (&m_font);


      //set the text colors
      switch (m_State)
        {
        case ST_HIGHLIGHTED:
          pDC->SetTextColor (m_HighlightColor);
          break;
        case ST_VISITED:
          pDC->SetTextColor (m_VisitedColor);
          break;
        case ST_VISIT_FAILED:
          pDC->SetTextColor (m_FailedColor);
          break;
        case ST_NOT_VISITED:
          pDC->SetTextColor (m_Color);
          break;
        default:
          ASSERT (FALSE);
        }
      pDC->SetBkMode (TRANSPARENT);

      // return hollow brush to preserve parent background color
      hbr = (HBRUSH)::GetStockObject (HOLLOW_BRUSH);
    }

  return hbr;
}

BOOL CHyperlink::
PreTranslateMessage (MSG * pMsg)
{
  m_ToolTip.RelayEvent (pMsg);
  return CStatic::PreTranslateMessage (pMsg);
}

void CHyperlink::
PreSubclassWindow ()
{
  //  if(m_sActualLink.IsEmpty() && m_sActualLink.LoadString(GetDlgCtrlID())) {
  if (m_sActualLink.IsEmpty ())
    GetWindowText (m_sActualLink);
  CheckActualHyperLink ();
  CRect rect;
  GetClientRect (rect);
  m_ToolTip.Create (this);
  m_ToolTip.AddTool (this, m_sToolTip, rect, TOOLTIP_ID);
  CStatic::PreSubclassWindow ();
}

IMPLEMENT_DYNCREATE (CHyperlinkPage, CPropertyPage)

CHyperlinkPage::CHyperlinkPage ():CPropertyPage (CHyperlinkPage::IDD)
{
  //{{AFX_DATA_INIT(CHyperlinkPage)
  //}}AFX_DATA_INIT
  m_pBuddy = NULL;
}


CHyperlinkPage:: ~ CHyperlinkPage ()
{
}

void CHyperlinkPage::
DoDataExchange (CDataExchange * pDX)
{
  CPropertyPage::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CHyperlinkPage)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP (CHyperlinkPage, CPropertyPage)
//{{AFX_MSG_MAP(CHyperlinkPage)
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

IMPLEMENT_DYNAMIC (CHyperlinkSheet, CPropertySheet)

CHyperlinkSheet::CHyperlinkSheet (UINT nIDCaption, CWnd * pParentWnd, UINT iSelectPage)
    :CPropertySheet (nIDCaption, pParentWnd, iSelectPage)
{
  AddPage (&m_page1);
}


CHyperlinkSheet::CHyperlinkSheet (LPCTSTR pszCaption, CWnd * pParentWnd, UINT iSelectPage)
    :CPropertySheet (pszCaption, pParentWnd, iSelectPage)
{
  AddPage (&m_page1);
}


CHyperlinkSheet:: ~ CHyperlinkSheet ()
{
}


BEGIN_MESSAGE_MAP (CHyperlinkSheet, CPropertySheet)
//{{AFX_MSG_MAP(CHyperlinkSheet)
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()


BOOL CHyperlinkPage::OnInitDialog ()
{
  CPropertyPage::OnInitDialog ();

  ASSERT (m_pBuddy);
  GetDlgItem (IDC_NAME)->SetWindowText (m_pBuddy->GetHyperLinkDescription ());
  GetDlgItem (IDC_URL)->SetWindowText (m_pBuddy->GetActualHyperLink ());

  return TRUE;
}
