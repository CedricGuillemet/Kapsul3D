///////////////////////////////////////////////////////////////////////////
//  File:    foldrdlg.h
//  Version: 1.8.0.12
//  Updated: 8-Nov-1998
//
//  Copyright:  Ferdinand Prantl
//  E-mail:     prantl@ff.cuni.cz
//
//  Folder selection dialog
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#ifndef __FOLDRDLG_H__
#define __FOLDRDLG_H__

/////////////////////////////////////////////////////////////////////////////

int EDITPADC_CLASS folderdlg (LPTSTR pszFinalFolderName, LPCTSTR pszInitialFolderName, LPCTSTR pszTitle, DWORD dwFlags, HWND hParentWnd);

/////////////////////////////////////////////////////////////////////////////

#endif // __FOLDRDLG_H__
