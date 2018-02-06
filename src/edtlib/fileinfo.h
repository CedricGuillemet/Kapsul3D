///////////////////////////////////////////////////////////////////////////
//  File:    fileinfo.h
//  Version: 1.1.0.4
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

#ifndef __FILEINFO_H__
#define __FILEINFO_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

class EDITPADC_CLASS CFileInfo
  {
  public:
    CFileInfo (LPCTSTR pszPathName);
    ~CFileInfo () {}
    LPCTSTR GetPathName () const { return m_sPathName; }
    LPCTSTR GetPath () const { return m_sPath; }
    const FILETIME &GetModified () const { return m_ftModified; }
    DWORD GetSize () const { return m_dwSize; }
    void SetModified (const FILETIME &ftModified) { m_ftModified = ftModified; }
    void SetSize (DWORD dwSize) { m_dwSize = dwSize; }
  protected:
    CString m_sPathName, m_sPath;
    FILETIME m_ftModified;
    DWORD m_dwSize;
  };

//////////////////////////////////////////////////////////////////////

#endif // __FILEINFO_H__
