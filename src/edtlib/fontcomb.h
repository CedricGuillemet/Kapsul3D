///////////////////////////////////////////////////////////////////////////
//  File:    fontcomb.h
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl, portions by Stcherbatchenko Andrei
//  E-mail:     prantl@ff.cuni.cz
//
//  Combo-box to offer list of available fonts
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#ifndef __FONTCOMB_H__INCLUDED__
#define __FONTCOMB_H__INCLUDED__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFontComboBox control

#define EXTRACOLORS 4

#pragma warning ( disable : 4512 )
class EDITPADC_CLASS CFontComboBox : public CComboBox
  {
    // Construction
public :
    DECLARE_DYNAMIC (CFontComboBox)

    CFontComboBox ();

    // Attributes
public :
    CImageList m_imagelistType;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CFontComboBox)
public :
    virtual void DrawItem (LPDRAWITEMSTRUCT lpDrawItemStruct);
    //}}AFX_VIRTUAL

    // Implementation
public :
    virtual ~CFontComboBox ();

    // Generated message map functions
protected :
    //{{AFX_MSG(CFontComboBox)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
  };
#pragma warning ( default : 4512 )

//////////////////////////////////////////////////////////////////////////////////////

#endif // __FONTCOMB_H__INCLUDED__
