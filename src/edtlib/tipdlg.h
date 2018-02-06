#ifndef __TIPDLG_H__INCLUDED__
#define __TIPDLG_H__INCLUDED__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// tipdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipDlg dialog

class EDITPADC_CLASS CTipDlg : public CDialog
{
// Construction
  public :
    CTipDlg (CWnd * pParent = NULL);    // standard constructor

// Dialog Data
  //{{AFX_DATA(CTipDlg)
  enum { IDD = IDD_TIP };
  BOOL m_bStartup;
  CString m_strTip;
  //}}AFX_DATA
  FILE *m_pStream;
  int m_id;

// Operations
  public :
  void RedrawCaption (void);

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTipDlg)
  protected :
  virtual void DoDataExchange (CDataExchange * pDX);    // DDX/DDV support

  virtual BOOL OnInitDialog ();
  //}}AFX_VIRTUAL

// Implementation
  public :
  virtual ~CTipDlg ();
  virtual int DoModal ();

  protected :
  // Generated message map functions
  //{{AFX_MSG(CTipDlg)
    afx_msg void OnNextTip ();
  afx_msg HBRUSH OnCtlColor (CDC * pDC, CWnd * pWnd, UINT nCtlColor);
  virtual void OnOK ();
  afx_msg void OnPaint ();
  afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

  void DoPaint (CDC * pdc, BOOL updatetext);

  void GetNextTipString (CString & strNext);
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __TIPDLG_H__INCLUDED__
