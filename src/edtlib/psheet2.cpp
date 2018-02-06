#include "stdafx.h"
#include "psheet2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertySheet2

IMPLEMENT_DYNAMIC (CPropertySheet2, CPropertySheet)

CPropertySheet2::CPropertySheet2 ()
  {
  }

CPropertySheet2::~CPropertySheet2 ()
  {
  }

BOOL CPropertySheet2::CheckKey (TCHAR cAccel)
  {
    CTabCtrl *pTab = GetTabControl ();
    
    int n = pTab->GetItemCount ();
    
    TCHAR buf[80], shortcut[3];
    
    TC_ITEM tcItem;
    tcItem.mask = TCIF_TEXT;
    tcItem.pszText = buf;
    shortcut[0] = _T ('&');
    shortcut[2] = _T ('\0');
    for (int i = 0; i < n; i++)
      {
        tcItem.cchTextMax = 79;
        pTab->GetItem (i, &tcItem);
        shortcut[1] = cAccel;
        
        // convert string characters into uppercase characters
        short nCount = 0;
        while (buf[nCount] != _T ('\0'))
          {
            buf[nCount] = toupper (buf[nCount]);
            nCount++;
          }
  
        if (_tcsstr (buf, shortcut)) {
        
          SetActivePage (i);
          return TRUE;
        }
      }
    return FALSE;
  }  

BOOL CPropertySheet2::PreTranslateMessage (MSG* pMsg)
  {
    if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam > 32)
      {
        if (CheckKey (pMsg->wParam))
          return TRUE;
      
        return (GetParent ()->GetParent ()->PreTranslateMessage (pMsg));
      }
  
    return CPropertySheet::PreTranslateMessage (pMsg);
  }

BEGIN_MESSAGE_MAP (CPropertySheet2, CPropertySheet)
  //{{AFX_MSG_MAP (CPropertySheet2)
    // NOTE - the ClassWizard will add and remove mapping macros here.
  //}}AFX_MSG_MAP
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
// CPropertySheet2 message handlers
