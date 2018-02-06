///////////////////////////////////////////////////////////////////////////
//  File:    foldrdlg.cpp
//  Version: 1.8.0.12
//  Updated: 8-Nov-1998
//
//  Copyright:  Ferdinand Prantl
//  E-mail:     prantl@ff.cuni.cz
//
//  Folder selection dialog
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "foldrdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

typedef struct folderdlgdata_t
  {
    BROWSEINFO bi;

    LPCTSTR pszInitialFolderName;
    TCHAR szFinalFolderName[MAX_PATH];

    TCHAR szDisplayName[MAX_PATH];
    TCHAR szPath[MAX_PATH];
  } folderdlgdata;

/*
 *  FUNCTION: shortname (LPTSTR, LPCTSTR)
 *
 *  PURPOSE:
 *
 *  COMMENTS:
 *
 */

LPTSTR shortname (LPTSTR pszDst, LPCTSTR pszSrc)
{
  if (_tcslen (pszSrc) <= 35)
    _tcscpy (pszDst, pszSrc);
  else
    {
      _tcsncpy (pszDst, pszSrc, 35);
      pszDst[35] = _T ('\0');
      _tcscat (pszDst, _T ("..."));
    }
  return pszDst;
}

/*
 *  FUNCTION: browsedircallback (HWND, UINT, LPARAM, LPARAM)
 *
 *  PURPOSE:
 *
 *  COMMENTS:
 *
 */

static int CALLBACK browsedircallback (HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
  folderdlgdata *pData;
  TCHAR szShortName[MAX_PATH];
  
  pData = (folderdlgdata*) lpData;

  switch (uMsg)
    {
    case BFFM_INITIALIZED:
      SendMessage (hWnd, BFFM_SETSELECTION, TRUE, (LPARAM) pData->pszInitialFolderName);
      SendMessage (hWnd, BFFM_SETSTATUSTEXT, 0, (LPARAM) shortname (szShortName, pData->pszInitialFolderName));
      break;
    case BFFM_SELCHANGED:
      SHGetPathFromIDList ((ITEMIDLIST*) lParam, pData->szPath);
      _tcscpy (pData->szFinalFolderName, pData->szPath);
      SendMessage (hWnd, BFFM_SETSTATUSTEXT, 0, (LPARAM) shortname (szShortName, pData->szFinalFolderName));
      break;
    }

  return 0;
}

/*
 *  FUNCTION: folderdlg (LPTSTR, LPCTSTR, LPCTSTR, DWORD, HWND)
 *
 *  PURPOSE:
 *
 *  COMMENTS:
 *
 */

int folderdlg (LPTSTR pszFinalFolderName, LPCTSTR pszInitialFolderName, LPCTSTR pszTitle, DWORD dwFlags, HWND hParentWnd)
  {
    folderdlgdata data;
    int nReturn;
    ITEMIDLIST *piid;
    LPMALLOC lpMalloc;

    memset (&data, _T ('\0'), sizeof (data));
    data.pszInitialFolderName = pszInitialFolderName ? pszInitialFolderName : _T ("");
    data.bi.hwndOwner = hParentWnd;
    data.bi.pidlRoot = NULL;
    data.bi.pszDisplayName = data.szDisplayName;
    data.bi.lpszTitle = pszTitle ? pszTitle : _T ("Select a directory:");
    data.bi.ulFlags = dwFlags | BIF_STATUSTEXT;
    data.bi.lpfn = browsedircallback;
    data.bi.lParam = (LPARAM) &data;

    _tcscpy (data.szFinalFolderName, data.pszInitialFolderName);
    piid = NULL;
    piid = SHBrowseForFolder (&data.bi);
    if (piid && SHGetPathFromIDList (piid, data.szPath))
      {
        _tcscpy (data.szFinalFolderName, data.szPath);
        nReturn = IDOK;
      }
    else
      {
        nReturn = IDCANCEL;
      }
    if (piid)
      {
        if (SHGetMalloc (&lpMalloc) == NOERROR)
          {
            lpMalloc->Free (piid);
            lpMalloc->Release ();
          }
      }
    _tcscpy (pszFinalFolderName, data.szFinalFolderName);
  
    return nReturn;
  }

/////////////////////////////////////////////////////////////////////////////
