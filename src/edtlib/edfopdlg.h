/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jorge Lodos
// All rights reserved
//
// Distribute and use freely, except:
// 1. Don't alter or remove this notice.
// 2. Mark the changes you made
//
// Send bug reports, bug fixes, enhancements, requests, etc. to:
//    lodos@cigb.edu.cu
/////////////////////////////////////////////////////////////////////////////

#ifndef __EDFOPDLG_H__INCLUDED__
#define __EDFOPDLG_H__INCLUDED__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// edfopdlg.h : header file
//

#include "dib.h"
#include "dibstat.h"

/////////////////////////////////////////////////////////////////////////////
// CEditFileOpenDlg dialog

class EDITPADC_CLASS CEditFileOpenDlg : public CFileDialog
  {
      DECLARE_DYNAMIC (CEditFileOpenDlg)
    
    public:
      CEditFileOpenDlg (BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL,
      DWORD dwFlags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd *pParentWnd = NULL);
    
    // Attributes
    //{{AFX_DATA(CEditFileOpenDlg)
    enum { IDD = IDD_EDFILEOPEN };
    //}}AFX_DATA
    public:
      BOOL m_bPreview, m_bRecode;
      CDIBStatic m_ctlDib;
      CStatic m_ctlText, m_ctlDesc;
      CComboBox m_ctlEncodings, m_ctlFormat;
      CButton m_ctlPreview;
      int m_nEncoding, m_nFormat;
    
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CEditFileOpenDlg)
    protected :
      virtual void DoDataExchange (CDataExchange * pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
   public:
      BOOL LoadDib (LPCTSTR pszName);
      void RemoveDib ();

#ifdef _DEBUG
      virtual void Dump (CDumpContext &dc) const;
#endif // _DEBUG
    protected:
      //{{AFX_MSG(CEditFileOpenDlg)
      virtual BOOL OnInitDialog ();
      afx_msg void OnPreview ();
      afx_msg void OnRecode ();
      afx_msg BOOL OnQueryNewPalette ();
      afx_msg void OnPaletteChanged (CWnd *pFocusWnd);
      afx_msg void OnSetFocus (CWnd *pOldWnd);
      afx_msg void OnSize(UINT nType, int cx, int cy);
      afx_msg void OnChangeEncoding ();
      afx_msg void OnChangeFormat ();
	//}}AFX_MSG
      virtual void OnFileNameChange ();
      virtual void OnFolderChange ();
    
      DECLARE_MESSAGE_MAP ()
  };

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __EDFOPDLG_H__INCLUDED__
