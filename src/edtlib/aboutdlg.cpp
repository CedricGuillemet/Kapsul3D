///////////////////////////////////////////////////////////////////////////
//  File:    aboutdlg.cpp
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

// editpad.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "editcmd.h"

#include "aboutdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

CAboutDlg::CAboutDlg ():CDialog (CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::
DoDataExchange (CDataExchange * pDX)
{
  CDialog::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  DDX_Control (pDX, IDC_ME, m_ctlMe);
  DDX_Control (pDX, IDC_ANDREI, m_ctlAndrei);
  DDX_Control (pDX, IDC_SVEN, m_ctlSven);
  DDX_Control (pDX, IDC_STAS, m_ctlStas);
  DDX_Control (pDX, IDC_MARKO, m_ctlMarko);
  DDX_Control (pDX, IDC_ADOLF, m_ctlAdolf);
  DDX_Control (pDX, IDC_FRANKY, m_ctlFranky);
  DDX_Control (pDX, IDC_CRISTI, m_ctlCristi);
  DDX_Control (pDX, IDC_SELOM, m_ctlSelom);
  DDX_Control (pDX, IDC_MFCCODEGURU, m_ctlMFCCodeguru);
  DDX_Control (pDX, IDC_HANS, m_ctlHans);
  DDX_Control (pDX, IDC_MICHAEL, m_ctlMichael);
  DDX_Control (pDX, IDC_ROBERTO, m_ctlRoberto);
  DDX_Control (pDX, IDC_JOSH, m_ctlJosh);
  DDX_Control (pDX, IDC_JAN, m_ctlJan);
  DDX_Control (pDX, IDC_PAUL, m_ctlPaul);
  DDX_Control (pDX, IDC_WITOLD, m_ctlWitold);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP (CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
