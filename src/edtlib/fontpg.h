///////////////////////////////////////////////////////////////////////////
//  File:    fontpg.h
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl (I'm sorry, author unknown ...)
//  E-mail:     prantl@ff.cuni.cz
//
//  Code to font changing property page
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#ifndef __FONTPG_H__INCLUDED__
#define __FONTPG_H__INCLUDED__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFontPage dialog

#include "ccrystaltextview.h"
#include "fontpgrc.h"
#include "fontcomb.h"

class EDITPADC_CLASS CFontPage : public CPropertyPage
{
    DECLARE_DYNCREATE(CFontPage)

// Construction
public:
    CFontPage(CCrystalTextView *pParent = NULL, LPLOGFONT pLogFont = NULL);
    ~CFontPage();

// Dialog Data
    //{{AFX_DATA(CFontPage)
    enum { IDD = IDD_FONTPAGE };
    CStatic m_staticSample;
    CFontComboBox m_comboFont;
    CComboBox m_comboSize;
    CComboBox m_comboScript;
    CComboBox m_comboEncoding;
    int m_nEncoding;
    BOOL m_bRecode;
    CString m_sFont;
    CString m_sSize;
    CString m_sScript;
    //}}AFX_DATA

    CCrystalTextView *m_pParent;
    LOGFONT m_LogFont, *m_pLogFont;
    //CImageList m_imagesFont;

// Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(CFontPage)
	public:
	virtual void OnOK();
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CFontPage)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelChange();
    afx_msg void OnRecode();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    CFont m_fontSample;
    int m_cyPixelsPerInch;
    static int CALLBACK FontEnumProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, 
        int FontType, CFontPage* pFontPage );


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately 
// before the previous line.

#endif // __FONTPG_H__INCLUDED__
