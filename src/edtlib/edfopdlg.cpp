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

// edfopdlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "editcmd.h"
#include "edfopdlg.h"
#include "filesup.h"
#include "ccrystaltextbuffer.h"
#include <dlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditFileOpenDlg

IMPLEMENT_DYNAMIC (CEditFileOpenDlg, CFileDialog)

CEditFileOpenDlg::CEditFileOpenDlg (BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
  DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) : CFileDialog (bOpenFileDialog, lpszDefExt,
  lpszFileName, dwFlags, lpszFilter, pParentWnd)
  {
    //{{AFX_DATA_INIT(CEditFileOpenDlg)
    //}}AFX_DATA_INIT
    m_ofn.Flags |= OFN_EXPLORER|OFN_ENABLETEMPLATE;
    m_ofn.lpTemplateName = MAKEINTRESOURCE (CEditFileOpenDlg::IDD);
    m_bPreview = TRUE;
    m_nEncoding = CCrystalTextBuffer::m_nDefaultEncoding;
    m_bRecode = m_nEncoding != -1;
    m_nFormat = 0;
  }

void CEditFileOpenDlg::
DoDataExchange (CDataExchange * pDX)
  {
    CFileDialog::DoDataExchange (pDX);
    //{{AFX_DATA_MAP(CFileDialog)
    //}}AFX_DATA_MAP
  }

BEGIN_MESSAGE_MAP (CEditFileOpenDlg, CFileDialog)
//{{AFX_MSG_MAP(CEditFileOpenDlg)
  ON_CBN_SELCHANGE (IDC_ENCODING, OnChangeEncoding)
  ON_CBN_SELCHANGE (IDC_FORMAT, OnChangeFormat)
  ON_BN_CLICKED (IDC_PREVIEW, OnPreview)
  ON_BN_CLICKED (IDC_RECODE, OnRecode)
  ON_WM_QUERYNEWPALETTE ()
  ON_WM_PALETTECHANGED ()
  ON_WM_SETFOCUS ()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

BOOL CEditFileOpenDlg::LoadDib (LPCTSTR pszName)
  {
    CString sExt = GetExt (pszName);
    sExt.MakeLower ();
    if (sExt == _T ("bmp") || sExt == _T ("dib"))
      if (m_ctlDib.LoadDib (pszName))
        {
          m_ctlText.ShowWindow (SW_HIDE);
          m_ctlDib.ShowWindow (SW_SHOW);
          CString sDesc;
          sDesc.Format (_T ("Width:\t%d\nHeight:\t%d\nColors:\t%d"),
            m_ctlDib.m_DIB.Width (), m_ctlDib.m_DIB.Height (), m_ctlDib.m_DIB.NumColors ());
          m_ctlDesc.SetWindowText (sDesc);
          return TRUE;
        }
      else
        {
          m_ctlDib.ShowWindow (SW_HIDE);
          m_ctlText.ShowWindow (SW_SHOW);
          m_ctlText.SetWindowText (_T (""));
          m_ctlDesc.SetWindowText (_T (""));
          return FALSE;
        }
    else
      {
        m_ctlDib.ShowWindow (SW_HIDE);
        m_ctlText.ShowWindow (SW_SHOW);
        m_ctlDesc.SetWindowText (_T (""));
        TRY
          CStdioFile oFile (pszName, CFile::modeRead|CFile::shareDenyNone|CFile::typeText);
          CString sEntry;
          sExt.Empty ();
          CRect rc;
          m_ctlText.GetWindowRect (rc);
          int i, l = rc.Height () / 12;
          for (i = 0; i < l; i++)
            {
              if (!oFile.ReadString (sEntry))
                break;
              if (!sExt.IsEmpty ())
                sExt += _T ('\n');
              sExt += sEntry;
            }
          m_ctlText.SetWindowText (sExt);
        CATCH_ALL (e)
          m_ctlText.SetWindowText (_T (""));
          return FALSE;
        END_CATCH_ALL
      }
    return TRUE;
  }

void CEditFileOpenDlg::RemoveDib ()
  {
    m_ctlDib.RemoveDib ();
    m_ctlDib.ShowWindow (SW_HIDE);
    m_ctlText.ShowWindow (SW_SHOW);
    m_ctlText.SetWindowText (_T (""));
    m_ctlDesc.SetWindowText (_T (""));
  }

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CEditFileOpenDlg::Dump (CDumpContext &dc) const
  {
    CFileDialog::Dump (dc);
    if (m_bPreview)
      dc << _T ("preview is enabled\n");
    else
      dc << _T ("preview is disabled\n");
  }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

extern EDITPADC_CLASS LPCTSTR pszCodeNames[];
extern EDITPADC_CLASS void FillComboBox (CComboBox &Control, LPCTSTR *pszItems);

EDITPADC_CLASS LPCTSTR pszFormats[] =
  {
    _T ("Plain text"),
    _T ("Try to use native format (RTF...)"),
    _T ("Binary"),
    NULL
  };

BOOL CEditFileOpenDlg::OnInitDialog () 
  {
    CFileDialog::OnInitDialog ();
   
    m_ctlPreview.SubclassDlgItem (IDC_PREVIEW, this);
    m_ctlDib.SubclassDlgItem (IDC_IMAGE, this);
    m_ctlText.SubclassDlgItem (IDC_TEXT, this);
    m_ctlDesc.SubclassDlgItem (IDC_DESC, this);
    m_ctlEncodings.SubclassDlgItem (IDC_ENCODING, this);
    FillComboBox (m_ctlEncodings, pszCodeNames);
    m_ctlEncodings.SetCurSel (m_nEncoding);
    m_ctlFormat.SubclassDlgItem (IDC_FORMAT, this);
    FillComboBox (m_ctlFormat, pszFormats);
    m_ctlFormat.SetCurSel (0);
    GetDlgItem (IDC_PREVIEW)->SendMessage (BM_SETCHECK, m_bPreview ? 1 : 0);
    GetDlgItem (IDC_RECODE)->SendMessage (BM_SETCHECK, m_bRecode ? 1 : 0);
    m_ctlEncodings.EnableWindow (m_bRecode);
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
  }

void CEditFileOpenDlg::OnFileNameChange () 
  {
    CFileDialog::OnFileNameChange ();
    if (m_bPreview)
      LoadDib (GetPathName ()); // the control will handle errors
  }

void CEditFileOpenDlg::OnFolderChange () 
  {
    CFileDialog::OnFolderChange ();
    RemoveDib ();
  }

void CEditFileOpenDlg::OnPreview () 
  {
    m_bPreview = !m_bPreview;
    if (m_bPreview)
      LoadDib (GetPathName ()); // the control will handle errors
    else
      RemoveDib (); // no preview
  }

void CEditFileOpenDlg::OnRecode () 
  {
    m_bRecode = !m_bRecode;
    m_nEncoding = m_bRecode ? m_ctlEncodings.GetCurSel () : -1;
    m_ctlEncodings.EnableWindow (m_bRecode);
  }

void CEditFileOpenDlg::OnChangeEncoding ()
{
  UpdateData();
  m_nEncoding = m_ctlEncodings.GetCurSel ();
}

void CEditFileOpenDlg::OnChangeFormat ()
{
  UpdateData();
  m_nFormat = m_ctlFormat.GetCurSel ();
}

BOOL CEditFileOpenDlg::OnQueryNewPalette () 
  {
    m_ctlDib.SendMessage (WM_QUERYNEWPALETTE);  // redo the palette if necessary
    return CFileDialog::OnQueryNewPalette ();
  }

void CEditFileOpenDlg::OnPaletteChanged (CWnd *pFocusWnd) 
  {
    CFileDialog::OnPaletteChanged (pFocusWnd);
    m_ctlDib.SendMessage (WM_PALETTECHANGED, (WPARAM) pFocusWnd->GetSafeHwnd ()); // redo the palette if necessary
  }

void CEditFileOpenDlg::OnSetFocus (CWnd *pOldWnd) 
  {
    CFileDialog::OnSetFocus (pOldWnd);
    m_ctlDib.SendMessage (WM_QUERYNEWPALETTE);  // redo the palette if necessary
  }

void CEditFileOpenDlg::OnSize(UINT nType, int cx, int cy) 
{
	CFileDialog::OnSize(nType, cx, cy);
  CWnd *pWnd = GetParent ()->GetDlgItem (lst2);
  if (pWnd)
    {
      CRect rc, rc2;
      pWnd->GetWindowRect (rc);
      m_ctlDib.GetWindowRect (rc2);
      ScreenToClient (rc2);
      m_ctlDib.MoveWindow (rc2.left, rc2.top, rc2.Width (), rc.Height ());
      if (m_bPreview)
        LoadDib (GetPathName ());
      m_ctlText.GetWindowRect (rc2);
      ScreenToClient (rc2);
      m_ctlText.MoveWindow (rc2.left, rc2.top, rc2.Width (), rc.Height ());
      m_ctlPreview.GetWindowRect (rc);
      ScreenToClient (rc);
      m_ctlPreview.MoveWindow (rc2.left, rc.top, rc.Width (), rc.Height ());
      m_ctlDesc.GetWindowRect (rc);
      ScreenToClient (rc);
      m_ctlDesc.MoveWindow (rc2.left, rc.top, rc.Width (), rc.Height ());
    }
}

/*
 * stc3, stc2     The two label controls ("File name" and "Files of type")
 * edt1, cmb1     The edit control and the drop-down box.
 * IDOK, IDCANCEL The OK and Cancel button.
 * lst1           The window that is used to browse the namespace.
 * lst2           The window that is used to browse the file(s).
 */

/////////////////////////////////////////////////////////////////////////////
