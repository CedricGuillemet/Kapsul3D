///////////////////////////////////////////////////////////////////////////
//  File:    hlink.h
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl, portions by MFC Codeguru "gurus"
//  E-mail:     prantl@ff.cuni.cz, http://www.codeguru.com
//
//  Hyperlink control
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//  File:    ttipctl2.h
//  Version: 1.1.0.4
//  Updated: 19-Jul-1998
//
//  Copyright:  Ferdinand Prantl
//  E-mail:     prantl@ff.cuni.cz
//
//  Tooltip control extension
//
//  You are free to use or modify this code to the following restrictions:
//  - Acknowledge me somewhere in your about box, simple "Parts of code by.."
//  will be enough. If you can't (or don't want to), contact me personally.
//  - LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////

#ifndef __TTIPCTL2_H__
#define __TTIPCTL2_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////

class EDITPADC_CLASS CToolTipCtrl2 : public CToolTipCtrl
  {
    // Construction
public :
    CToolTipCtrl2 ();

    // Attributes
public :

    // Operations
public :
    void TrackPosition (int xPos, int yPos);
    void TrackPosition (LPPOINT lppt);
    void TrackActivate (BOOL bActivate, LPTOOLINFO lpti);
    int SetMaxTipWidth (int nWidth);
    RECT SetMargin (LPRECT lpRect);
    int GetMaxTipWidth ();
    void GetMargin (LPRECT lpRect);
    int GetDelayTime (DWORD dwType);
    int SetDelayTime (DWORD dwType, int nTime);
    COLORREF GetTextColor ();
    COLORREF GetBkColor ();
    COLORREF SetTextColor (COLORREF crColor);
    COLORREF SetBkColor (COLORREF crColor);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CToolTipCtrl2)
    //}}AFX_VIRTUAL

    // Implementation
public :
    virtual ~CToolTipCtrl2 ();

    // Generated message map functions
protected :
    //{{AFX_MSG(CToolTipCtrl2)
    // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP ()
  };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __TTIPCTL2_H__
