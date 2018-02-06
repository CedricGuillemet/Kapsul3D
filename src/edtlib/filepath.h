#ifndef __FILEPATH_H__
#define __FILEPATH_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

class EDITPADC_CLASS CFilePath
  {
  public:
    CFilePath (LPCTSTR pszPath) : m_sPath (pszPath), m_nCount (1) {}
    ~CFilePath () {}
    LPCTSTR GetPath () const { return m_sPath; }
    int GetCount () const { return m_nCount; }
    void Inc () { m_nCount++; }
    void Dec () { m_nCount--; }
  protected:
    CString m_sPath;
    int m_nCount;
  };

//////////////////////////////////////////////////////////////////////

#endif // __FILEPATH_H__
