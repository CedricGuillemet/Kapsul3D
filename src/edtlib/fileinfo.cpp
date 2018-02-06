///////////////////////////////////////////////////////////////////////////
//  File:    fileinfo.cpp
//  Version: 1.3.0.6
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl
//  E-mail:     prantl@ff.cuni.cz
//
//  Some handy stuff to deal with files and their names
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//  14-Sep-99
//  + FIX: GetFileSize stuff causing crash on file size comparings (Hans Eckardt)
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fileinfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////

CFileInfo::CFileInfo (LPCTSTR pszPathName)
  {
    TCHAR szPath[_MAX_PATH], szDrive[_MAX_DRIVE];
    _tsplitpath (pszPathName, szDrive, szPath, NULL, NULL);
    m_sPathName = pszPathName;
    m_sPath = szDrive;
    m_sPath += szPath;
    HANDLE hFile = CreateFile (pszPathName, GENERIC_READ, FILE_SHARE_READ /*|FILE_SHARE_WRITE|FILE_SHARE_DELETE*/,
      NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
      {
        VERIFY (GetFileTime (hFile, NULL, NULL, &m_ftModified));
		// ->HE
        m_dwSize= GetFileSize (hFile, NULL);
		ASSERT(m_dwSize != (DWORD)-1);
		// <-HE
        CloseHandle (hFile);
      }
  }

//////////////////////////////////////////////////////////////////////
