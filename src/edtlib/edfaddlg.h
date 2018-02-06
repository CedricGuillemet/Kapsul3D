#ifndef __EDFADDLG_H__INCLUDED__
#define __EDFADDLG_H__INCLUDED__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// edfaddlg.h : header file
//

#include "dib.h"
#include "dibstat.h"

/////////////////////////////////////////////////////////////////////////////
// CEditFileAddDlg dialog

class EDITPADC_CLASS CEditFileAddDlg : public CFileDialog
  {
      DECLARE_DYNAMIC (CEditFileAddDlg)
    
    public:
      CEditFileAddDlg (BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL,
      DWORD dwFlags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd *pParentWnd = NULL);
    
    // Attributes
    //{{AFX_DATA(CEditFileAddDlg)
    enum { IDD = IDD_EDFILEADD };
    //}}AFX_DATA
    public:
      BOOL m_bPreview;
      CDIBStatic m_ctlDib;
      CStatic m_ctlText, m_ctlDesc;
      CButton m_ctlPreview;
    
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CEditFileAddDlg)
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
      //{{AFX_MSG(CEditFileAddDlg)
      virtual BOOL OnInitDialog ();
      afx_msg void OnPreview ();
      afx_msg void OnRecode ();
      afx_msg BOOL OnQueryNewPalette ();
      afx_msg void OnPaletteChanged (CWnd *pFocusWnd);
      afx_msg void OnSetFocus (CWnd *pOldWnd);
      afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
      virtual void OnFileNameChange ();
      virtual void OnFolderChange ();
    
      DECLARE_MESSAGE_MAP ()
  };

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __EDFADDLG_H__INCLUDED__
