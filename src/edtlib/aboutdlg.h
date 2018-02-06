///////////////////////////////////////////////////////////////////////////
//  File:    aboutdlg.h
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl
//  E-mail:     prantl@ff.cuni.cz
//
//  About dialog
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

// editpad.h : main header file for the EDITPAD application
//

#ifndef __ABOUTDLG__
#define __ABOUTDLG__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "hlink.h"

class EDITPADC_CLASS CAboutDlg : public CDialog
  {
public :
    CAboutDlg ();

    // Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    CHyperlink m_ctlMe, m_ctlAndrei, m_ctlSven, m_ctlStas, m_ctlMarko, m_ctlAdolf,
      m_ctlFranky, m_ctlCristi, m_ctlSelom, m_ctlMFCCodeguru, m_ctlHans, m_ctlMichael,
      m_ctlRoberto, m_ctlJosh, m_ctlJan, m_ctlPaul, m_ctlWitold;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected :
    virtual void DoDataExchange (CDataExchange * pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected :
    //{{AFX_MSG(CAboutDlg)
    // No message handlers
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
  };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __ABOUTDLG__
