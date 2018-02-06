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

#ifndef __HLINK_H__INCLUDED__
#define __HLINK_H__INCLUDED__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// hlinkctl.h : header file
//

#include "ttipctl2.h"

/////////////////////////////////////////////////////////////////////////////
// CHyperlink

class EDITPADC_CLASS CHyperlink : public CStatic
  {
public :
    //Constructors / Destructors
    CHyperlink ();
    virtual ~CHyperlink ();

    //Set or get the hyperlink to use
    void SetHyperLink (const CString & sActualLink);
    CString GetActualHyperLink () const
    {
      return m_sActualLink;
    };

    //Set or get the hyperlink description (really just the static's window text)
    void SetHyperLinkDescription (const CString & sDescription);
    CString GetHyperLinkDescription () const;

    //Set or get the hyperlink color
    void SetLinkColor (const COLORREF & color);
    COLORREF GetLinkColor ()
    {
      return m_Color;
    };

    //Set or get the hyperlink color for visited links
    void SetVisitedLinkColor (const COLORREF & color);
    COLORREF GetVisitedLinkColor ()
    {
      return m_VisitedColor;
    };

    //Set or get the hyperlink color for highlighted links
    void SetHighlightLinkColor (const COLORREF & color);
    COLORREF GetHighlightLinkColor ()
    {
      return m_HighlightColor;
    };
    void SetUseHighlightColor (BOOL bUseHighlight)
    {
      m_bUseHighlight = bUseHighlight;
    };

    //Gets whether the hyperlink has been visited
    BOOL GetVisited ()
    {
      return m_State == ST_VISITED;
    };

    //Set or get whether the control should display a context menu
    void SetAllowContextMenu (BOOL bAllowContextMenu)
    {
      m_bAllowContextMenu = bAllowContextMenu;
    };
    BOOL GetAllowContextMenu () const
    {
      return m_bAllowContextMenu;
    };


    //Gets whether the window is automatically adjusted to
    //the size of the description text displayed
    BOOL GetShrinkToFit ()
    {
      return m_bShrinkToFit;
    }

    //Saves the hyperlink to an actual shortcut on file
#ifndef HLINK_NOOLE
    BOOL Save (const CString & sFilename) const;
#endif

#ifndef HLINK_NOOLE
    //Saves the hyperlink to the favorites folder
    BOOL AddToFavorites () const;
#endif

#ifndef HLINK_NOOLE
    //Saves the hyperlink to the desktop folder
    BOOL AddToDesktop () const;
#endif

    //Displays the properties dialog for this URL
    void ShowProperties () const;

    //Connects to the URL
    BOOL Open (int how = OPEN) const;

protected :
    enum State
    {
      ST_NOT_VISITED,
      ST_VISITED,
      ST_VISIT_FAILED,
      ST_HIGHLIGHTED
    };
    enum Mode
    {
      OPEN,
      EDIT,
      PRINT
    };

    //{{AFX_VIRTUAL(CHyperlink)
public :
    virtual BOOL PreTranslateMessage (MSG * pMsg);
protected :
    virtual void PreSubclassWindow ();
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CHyperlink)
    afx_msg BOOL OnSetCursor (CWnd * pWnd, UINT nHitTest, UINT message);
    afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
    afx_msg void OnMouseMove (UINT nFlags, CPoint point);
    afx_msg void OnCopyShortcut ();
    afx_msg void OnProperties ();
    afx_msg void OnOpen ();
    afx_msg void OnEdit ();
    afx_msg void OnPrint ();
    afx_msg void OnContextMenu (CWnd *, CPoint point);
    afx_msg HBRUSH CtlColor (CDC * pDC, UINT nCtlColor);
    //}}AFX_MSG
#ifndef HLINK_NOOLE
    afx_msg void OnAddToFavorites ();
    afx_msg void OnAddToDesktop ();
#endif

    void SetActualHyperLink (const CString & sActualLink);
    void CheckActualHyperLink ();
    void HighLight (BOOL state);
#ifndef HLINK_NOOLE
    BOOL AddToSpecialFolder (int nFolder) const;
    BOOL OpenUsingCom (int how = OPEN) const;
#endif
    BOOL OpenUsingShellExecute (int how = OPEN) const;
    BOOL OpenUsingRegisteredClass (int how = OPEN) const;

    CString m_sLinkDescription;
    CString m_sActualLink;
    CString m_sToolTip;
    HCURSOR m_hLinkCursor;
    HCURSOR m_hArrowCursor;
    HCURSOR m_hBadCursor;
    COLORREF m_Color;
    COLORREF m_VisitedColor;
    COLORREF m_FailedColor;
    COLORREF m_HighlightColor;
    BOOL m_bShrinkToFit;
    BOOL m_bUseHighlight;
    State m_State;
    State m_OldState;
    BOOL m_bShowingContext;
    CFont m_font;
    BOOL m_bAllowContextMenu;
    CToolTipCtrl2 m_ToolTip;      // The tooltip

    DECLARE_MESSAGE_MAP ()
  };

#ifdef FP_SRC_HYPERLINK

class CHyperlinkPage : public CPropertyPage
  {
public :
    CHyperlinkPage ();
    ~CHyperlinkPage ();
    void SetBuddy (const CHyperlink * pBuddy)
    {
      m_pBuddy = pBuddy;
    };

    //{{AFX_DATA(CHyperlinkPage)
    enum
    {
      IDD = IDD_HLINK_PROPERTIES
    };
    //}}AFX_DATA

protected :
    //{{AFX_VIRTUAL(CHyperlinkPage)
protected :
    virtual void DoDataExchange (CDataExchange * pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    DECLARE_DYNCREATE (CHyperlinkPage)

    //{{AFX_MSG(CHyperlinkPage)
    virtual BOOL OnInitDialog ();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
    const CHyperlink *m_pBuddy;
  };


class CHyperlinkSheet : public CPropertySheet
  {
public :
    CHyperlinkSheet (UINT nIDCaption, CWnd * pParentWnd = NULL, UINT iSelectPage = 0);
    CHyperlinkSheet (LPCTSTR pszCaption, CWnd * pParentWnd = NULL, UINT iSelectPage = 0);
    virtual ~CHyperlinkSheet ();
    void SetBuddy (const CHyperlink * pBuddy)
    {
      m_page1.SetBuddy (pBuddy);
    };


protected :
    //{{AFX_VIRTUAL(CHyperlinkSheet)
    //}}AFX_VIRTUAL

    DECLARE_DYNAMIC (CHyperlinkSheet)

    //{{AFX_MSG(CHyperlinkSheet)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

    CHyperlinkPage m_page1;
  };

#endif /* FP_SRC_HYPERLINK */

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.


#endif // __HLINK_H__INCLUDED__
