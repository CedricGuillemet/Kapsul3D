///////////////////////////////////////////////////////////////////////////
//  File:    filevent.h
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

#ifndef __FILEVENT_H__
#define __FILEVENT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#pragma warning(disable:4786)
//////////////////////////////////////////////////////////////////////

class CFileInfo;
class CFilePath;

typedef CMap<CString, LPCTSTR, CFileInfo*, CFileInfo*> CFileInfoMap;
typedef CList<CFilePath*, CFilePath*> CFilePathList;

#define FE_NONE 0
#define FE_CHANGED_NAME 1
#define FE_CHANGED_SIZE 2
#define FE_CHANGED_TIME 4
#define FE_MODIFIED (FE_CHANGED_NAME|FE_CHANGED_SIZE|FE_CHANGED_TIME)
#define FE_DELETED 8

class EDITPADC_CLASS CFileEvent
  {
  public:
    CFileEvent () : m_bEvent (false) {}
    virtual ~CFileEvent ();
    void AddFile (LPCTSTR pszPathName);
    void RemoveFile (LPCTSTR pszPathName);
    void StartWatching ();
    void StopWatching ();
    bool IsWatching () const { return m_bEvent; }
  protected:
    virtual void OnFileEvent (WPARAM wEvent, LPCTSTR pszPathName) = 0;
    CEvent m_evWatching;
    CFileInfoMap m_mapFileInfo;
    CFilePathList m_lstFilePath;
    bool m_bEvent;
    static UINT FileEventProc (LPVOID lpParam);
  };

//////////////////////////////////////////////////////////////////////

#endif // __FILEVENT_H__
