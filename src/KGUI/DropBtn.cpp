// DropButton.cpp : implementation file
//

#include "stdafx.h"
#include "DropBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropList
CDropList::CDropList()
{
	m_nPrevSelection			= 0;
	m_nGroupCount				= 0;
	m_pHeaderFont				= NULL;
	m_pTextFont					= NULL;
	m_pBkBrush					= NULL;
	m_pBkHighlightBrush			= NULL;
	m_pBkPen					= NULL;
}

CDropList::~CDropList()
{
	if(m_pHeaderFont) delete m_pHeaderFont;
	if(m_pBkBrush) delete m_pBkBrush;
	if(m_pBkHighlightBrush) delete m_pBkHighlightBrush;
	if(m_pBkPen) delete m_pBkPen;

	// Clear out the Items
	ClearItems();
}

void CDropList::ClearItems()
{
	POSITION Pos = m_ItemList.GetHeadPosition();
	while(Pos)
	{
		m_pCurListItem = (LISTITEM*)m_ItemList.GetNext(Pos);
		delete m_pCurListItem;
	}
	m_ItemList.RemoveAll();
	m_nGroupCount = 0;
	m_nPrevSelection = 0;
}

BEGIN_MESSAGE_MAP(CDropList, CListBox)
	//{{AFX_MSG_MAP(CDropList)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropList message handlers
int CDropList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Brushes and Pens
	m_pBkBrush	= new CBrush(RGB(255,255,255));
	m_pBkPen	= new CPen(PS_SOLID, 1, RGB(255,255,255));

	m_pBkHighlightBrush = new CBrush(RGB(247,247,239));
	SetItemHeight(-1,16);
	return 0;
}
void CDropList::OnSize(UINT nType, int cx, int cy) 
{
	CListBox::OnSize(nType, cx, cy);
	GetClientRect(m_WindowRect);		
}
void CDropList::OnKillFocus(CWnd* pNewWnd) 
{
	CListBox::OnKillFocus(pNewWnd);
	GetParent()->ShowWindow(SW_HIDE);
}
void CDropList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// Make sure its a valid item
	if(lpDrawItemStruct->itemID == LB_ERR )
		return;
     
  	// Obtain the text for this item
	m_csText.Empty();
	GetText(lpDrawItemStruct->itemID, m_csText);
	
	// Set the current List item
	m_pCurListItem = (LISTITEM*)m_ItemList.GetAt(m_ItemList.FindIndex(lpDrawItemStruct->itemID));

	// Get the drawing DC
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	
	// Obtain the Item Rect
	CRect ItemRect(lpDrawItemStruct->rcItem);
	ItemRect.InflateRect(1,1);
	
    // Draw This item
	DrawItem(pDC, ItemRect, lpDrawItemStruct->itemState & ODS_SELECTED);
}
void CDropList::DrawItem(CDC* pDC, CRect ItemRect, BOOL bSelected)
{
	////////////////////////////////////////////////
	// Draw the Background Rectangle
	pDC->SelectObject(m_pBkPen);
	pDC->SelectObject(m_pBkBrush);
	pDC->SetTextColor(m_pCurListItem->crTextColor);
	if(bSelected && !m_pCurListItem->btHeader)
	{
		pDC->SelectObject(m_pBkHighlightBrush);
		pDC->SetTextColor(m_pCurListItem->crTextHighlightColor);
	}
	pDC->Rectangle(ItemRect);

	////////////////////////////////////////////////
	// Draw the Text - Is this a header?
	pDC->SetBkMode(TRANSPARENT);
	ItemRect.left = 4;
	ItemRect.right -= 5;
	if(m_pCurListItem->btHeader)
	{
		pDC->SelectObject(m_pHeaderFont);
		pDC->DrawText(m_csText, m_csText.GetLength(), ItemRect, DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_CALCRECT);
		pDC->DrawText(m_csText, m_csText.GetLength(), ItemRect, DT_SINGLELINE|DT_VCENTER|DT_LEFT);

		// Create a pen based on the text color
		CPen LinePen(PS_SOLID, 1, m_pCurListItem->crTextColor);
		pDC->SelectObject(LinePen);

		// Draw a line
		pDC->MoveTo(ItemRect.right + 2, ItemRect.top + (ItemRect.Height() / 2));
		pDC->LineTo(m_WindowRect.right - 2, ItemRect.top + (ItemRect.Height() / 2));
	}
	else
	{
		pDC->SelectObject(m_pTextFont);
		pDC->DrawText(m_csText, m_csText.GetLength(), ItemRect, DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_END_ELLIPSIS);
	}
}
void CDropList::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
}
HBRUSH CDropList::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	return (HBRUSH)(m_pBkBrush->GetSafeHandle() );
}
void CDropList::SetPreviousSelection(int nPrevSelection)
{
	m_nPrevSelection = nPrevSelection;
}

/////////////////////////////////////////////////////////////////////////////
// Overrides
int CDropList::AddString(LPCTSTR lpszItem)
{
	// Create a new Item
	m_pCurListItem = new LISTITEM;
	m_pCurListItem->crTextColor = RGB(0,0,0);
	m_pCurListItem->crTextHighlightColor = RGB(0,0,0);
	m_pCurListItem->btHeader = 0;

	// Should we create a Group Item?
	if(!m_ItemList.GetCount())
	{
		m_nGroupCount++;
	}
	else if(m_ItemList.GetCount() == 1) 
		SetCurSel(m_nPrevSelection);

	// Add this item to the list box (always at the top)
	return AddToList(1, lpszItem);
}
int CDropList::AddString(LPCTSTR lpszItem, int GroupPos, COLORREF crTextColor, COLORREF crTextHighlightColor)
{
	// Is this a valid group
	if(GroupPos > m_nGroupCount + 1)
		return -1;
	
	// Create a new Item
	m_pCurListItem = new LISTITEM;
	m_pCurListItem->crTextColor = crTextColor;
	m_pCurListItem->crTextHighlightColor = crTextHighlightColor;
	m_pCurListItem->btHeader = 0;

	// Is this a new group header
	if(GroupPos == m_nGroupCount + 1)
	{
		m_nGroupCount++;
		m_pCurListItem->btHeader = 1;
	}
	
	// Add this item to the list box (always at the top)
	return AddToList(GroupPos, lpszItem);
1;
}

int CDropList::AddToList(int nGroup, CString csText)
{
	/////////////////////////////////////////////////////
	// If this item is a header then add it to the end
	if(m_pCurListItem->btHeader)
	{
		m_ItemList.AddTail(m_pCurListItem);
		return CListBox::AddString(csText);
	}
	
	/////////////////////////////////////////////////////
	// Loop through the list items until you find the correct group
	int nListBoxItem = 0, nCurGroup = 1;	
	LISTITEM* pItem;
	POSITION Pos = m_ItemList.GetHeadPosition();
	POSITION OldPos = Pos;
	while(Pos)
	{
		// Get the item and check for a header
		pItem = (LISTITEM*)m_ItemList.GetNext(Pos);
		if(pItem->btHeader)
			nCurGroup++;

		// Is this the group?
		nListBoxItem++;
		if(nCurGroup == nGroup)
			break;
	}

	/////////////////////////////////////////////////////
	// If this was the first group - then force a heading
	if(nGroup == 1)
	{
		Pos = OldPos;
		nListBoxItem = 0;
	}
	else
		OldPos = Pos;

	/////////////////////////////////////////////////////
	// Continue looping from this position look for the correct spot
	CString csCurText;
	while(Pos)
	{
		// Get the Next Item
		OldPos = Pos;
		pItem = (LISTITEM*)m_ItemList.GetNext(Pos);

		// Get the Text For this item
		GetText(nListBoxItem, csCurText);

		// Have we hit a header?
		if(csText.CompareNoCase(csCurText) < 0)
		{
			m_ItemList.InsertBefore(OldPos, m_pCurListItem);
			return InsertString(nListBoxItem, csText);
		}
		nListBoxItem++;
	}

	/////////////////////////////////////////////////////
	// If we get here then we never found it so add it to the end
	m_ItemList.AddTail(m_pCurListItem);
	return CListBox::AddString(csText);
}
int CDropList::DeleteString(UINT nIndex)
{
	// Is this a valid item?
	if(nIndex >= (UINT)GetCount())
		return -1;
	
	// Find this item in our list
	POSITION Pos = m_ItemList.FindIndex(nIndex);
	POSITION LastPos = Pos;
	m_pCurListItem = (LISTITEM*)m_ItemList.GetNext(Pos);

	// Is this a header?
	if(m_pCurListItem->btHeader)
	{
		// have to remove all items until the end or next header
		m_nGroupCount--; // Reduce the Group Count
		while(Pos)
		{
			// Remove this item
			delete m_pCurListItem;
			m_ItemList.RemoveAt(LastPos);
			CListBox::DeleteString(nIndex);

			// Get the Next Element
			LastPos = Pos;
			m_pCurListItem = (LISTITEM*)m_ItemList.GetNext(Pos);
			if(m_pCurListItem->btHeader)
				break;
		}
	}

	// Deletes a Single item and Last item in the list in a group delete
	if(!m_pCurListItem->btHeader || LastPos && !Pos)
	{
		// Remove only this item
		delete m_pCurListItem;
		m_ItemList.RemoveAt(LastPos);
		return CListBox::DeleteString(nIndex);
	}
		
	return 1;
}
void CDropList::ResetContent()
{
	// Clear the list
	ClearItems();

	CListBox::ResetContent();
}


/////////////////////////////////////////////////////////////////////////////
// User UI
void CDropList::SetBkColor(COLORREF crColor)
{
	if(m_pBkBrush) delete m_pBkBrush;
	if(m_pBkPen)	delete m_pBkPen;
	m_pBkPen	= new CPen(PS_SOLID, 1, crColor);
	m_pBkBrush	= new CBrush(crColor);	
	RedrawWindow();
}
void CDropList::SetHighlightBkColor(COLORREF crColor)
{
	if(m_pBkHighlightBrush) delete m_pBkHighlightBrush;
	m_pBkHighlightBrush = new CBrush(crColor);
	RedrawWindow();
}
void CDropList::SetFont(CFont* pFont, BOOL bRedraw)
{
	// Can only set the font once (sorry - no resize on the fly)
	if(m_pTextFont)
		return;
	m_pTextFont = pFont;
	CWnd::SetFont(pFont);

	// Figure out the text size
	LOGFONT lpLogFont;
	m_pTextFont->GetLogFont(&lpLogFont);

	// Create the heading font with the bold attribute
	lpLogFont.lfWeight = FW_BOLD;
	m_pHeaderFont = new CFont();
	m_pHeaderFont->CreateFontIndirect(&lpLogFont);

	// Set the Row height
	SetItemHeight(-1,lpLogFont.lfHeight);
}
	

/////////////////////////////////////////////////////////////////////////////
// CListWnd
/////////////////////////////////////////////////////////////////////////////
CListWnd::CListWnd()
{
	m_pDropList = NULL;
}

CListWnd::~CListWnd()
{
	if(m_pDropList) delete m_pDropList;
}

BEGIN_MESSAGE_MAP(CListWnd, CWnd)
	//{{AFX_MSG_MAP(CListWnd)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(ID_CUSTOMLIST, OnSelectionChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListWnd message handlers
BOOL CListWnd::Create(CWnd* pParentWnd, UINT uID)
{
	CString csWndClassName = AfxRegisterWndClass( CS_SAVEBITS , NULL, NULL, NULL );

	// Create the Window
	if(!CreateEx(WS_EX_TOPMOST, csWndClassName, NULL, WS_BORDER|WS_POPUP, 0, 0, 200, 200, pParentWnd->GetSafeHwnd(), NULL, NULL))
		return FALSE;

	// Create the Custom List box
	m_pDropList = new CDropList();
	if(!m_pDropList->Create(WS_CHILD|WS_VSCROLL|WS_VISIBLE|LBS_NOTIFY|LBS_HASSTRINGS|LBS_OWNERDRAWFIXED|LBS_NOINTEGRALHEIGHT, CRect(0,0,0,0), this, ID_CUSTOMLIST))
		return FALSE;
	m_pParent = pParentWnd;
	return TRUE;
}
void CListWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// Move the List Window
	if(!m_pDropList)
		return;

	CRect WindowRect;
	GetClientRect(WindowRect);

	m_pDropList->MoveWindow(WindowRect);
}

void CListWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
	if(!bShow)	
		GetParent()->RedrawWindow();	
}
void CListWnd::OnSelectionChange()
{
	// Did they pick a Header?
	LISTITEM* pItem = m_pDropList->GetCurListItem();
	if(pItem->btHeader)
		return;
	
	// Close the Window
	ShowWindow(SW_HIDE);		

	// Is the mouse still over this window
	CRect WindowRect;
	GetWindowRect(WindowRect);

	POINT pPoint;
	GetCursorPos(&pPoint);
	if(!WindowRect.PtInRect(pPoint))
	{
		// Set back to the Selection before this one
		m_pDropList->SetCurSel(m_pDropList->GetPreviousSelection());
		return;
	}
	
	// Inform parent of a new selection
	m_pParent->SendMessage(CM_SELECTION_CHANGED, m_pDropList->GetCurSel(), 0);
}

/////////////////////////////////////////////////////////////////////////////
// CDropButton
/////////////////////////////////////////////////////////////////////////////
CDropButton::CDropButton()
{
	// Inititalize
	m_bOver			= false;
	m_bDeleteFont 	= false;
	m_bChangeTitle 	= true;
	m_pBkBrush 		= NULL;
	m_pBkOverBrush	= NULL;
	m_pBorderPen	= NULL;
	m_pTriBrush 	= NULL;
	m_pTriPen		= NULL;
	m_pDropWnd		= NULL;
	m_nListHeight	= 100;
//	m_MouseHook		= NULL;
}

CDropButton::~CDropButton()
{
	// Clean Up
	delete	m_pBkBrush;
	delete	m_pBkOverBrush;
	delete	m_pBorderPen;
	delete	m_pTriBrush;
	delete	m_pTriPen;
	
	delete	m_pDropWnd;
	if(m_bDeleteFont) delete m_pTextFont;
}

BEGIN_MESSAGE_MAP(CDropButton, CButton)
	//{{AFX_MSG_MAP(CDropButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(CM_SELECTION_CHANGED, OnSelectionChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropButton message handlers
BOOL CDropButton::Create(CString csCaption, CRect Rect, CWnd* pParent, UINT uID, COLORREF crBkColor, COLORREF crBkOverColor, COLORREF crTxtColor, COLORREF crTxtOverColor, CFont* pTextFont, COLORREF crBkListColor)
{
	// Create the Correct Brush for the background Fill
    if(crBkColor == -1)
	{
		m_pBkBrush = new CBrush(RGB(221,217,205));
		m_pBkOverBrush = new CBrush(RGB(233,229,217));		
	}
    else
	{
		m_pBkBrush = new CBrush(crBkColor);
		m_pBkOverBrush = new CBrush(crBkOverColor);		
	}

	// Create the Down highlight pen
	m_pBorderPen = new CPen(PS_SOLID, 1, RGB(0,0,0));

    // Save the Button Font
    m_pTextFont = pTextFont;
    if(!m_pTextFont)
    {
        m_bDeleteFont = true;
        m_pTextFont = new CFont();
 		m_pTextFont->CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, 
								CLIP_LH_ANGLES, DRAFT_QUALITY, VARIABLE_PITCH | FF_SWISS, "Arial");    
    }

	// Save the text color
   	m_crTxtColor = crTxtColor;
    if(m_crTxtColor == -1)
    	m_crTxtColor = RGB(0,0,0);
    
	// Save the text over color
	m_crTxtOverColor = crTxtOverColor;
    if(m_crTxtOverColor == -1)
    	m_crTxtOverColor = RGB(0,0,0);

	// Triangle Brush
	m_pTriBrush = new CBrush(m_crTxtColor); 
	m_pTriPen = new CPen(PS_SOLID, 1, m_crTxtColor); 

    // Create the CButton
	if(!CButton::Create(csCaption, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW, Rect, pParent, uID))
		return FALSE;
	
	// Get the Client Rect
	GetClientRect(m_WindowRect);
	m_nListWidth = m_WindowRect.Width();

	// Create the List box
	m_pDropWnd = new CListWnd();
	if(!m_pDropWnd->Create(this, uID + 1))
		return FALSE;

	// Set the Font to the list box
	m_pDropWnd->m_pDropList->SetFont(m_pTextFont);
	m_pDropWnd->m_pDropList->SetBkColor(crBkListColor);
	m_pParent = pParent;
	m_uID = uID;
	return TRUE;
}

void CDropButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CDC*	pDC			= CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT	uState		= lpDrawItemStruct->itemState;
	CRect 	ButtonRect  = lpDrawItemStruct->rcItem;
    
	///////////////////////////////////////////////////
	// Fill the Background
	CBrush* pOldBrush;
	CPen*	pOldPen		= (CPen*)pDC->SelectObject(m_pBorderPen);
	if(m_bOver)
		pOldBrush = (CBrush*)pDC->SelectObject(m_pBkOverBrush);
	else
		pOldBrush = (CBrush*)pDC->SelectObject(m_pBkBrush);
	pDC->Rectangle(ButtonRect);
		
	///////////////////////////////////////////////////
	// Calculate the Total Width of Arrow and Text
	CFont* pOldFont = (CFont*)pDC->SelectObject(m_pTextFont);
	CSize cTri  = pDC->GetTextExtent( "M", 1 );
	CString csText;
	GetWindowText(csText);
	CSize cText =  pDC->GetTextExtent(csText, csText.GetLength());

	///////////////////////////////////////////////////
	// Calculate the Y Position (Hope they didn't create a font or a button that is too large to fit! - perhaps fix later if they did)
	int nYStart = (ButtonRect.Height() - cText.cy) / 2;
	
	///////////////////////////////////////////////////
	// Set the Bk Mode and Transparenacy
	int	nOldBkMode		= pDC->SetBkMode(TRANSPARENT);
	COLORREF crOldColor = pDC->SetTextColor(m_crTxtColor);

	///////////////////////////////////////////////////
	// Draw the Arrow
	CPoint ptTri(ButtonRect.right - (cTri.cx + 5), nYStart + (cTri.cy / 3));
	DrawTriangle(pDC, ptTri, cTri.cx);

	///////////////////////////////////////////////////
	// If its too long then shorten it and add ellipse's
	pDC->DrawText(csText, csText.GetLength(), CRect(5, 0, m_WindowRect.right - (cTri.cx + 10), m_WindowRect.bottom), DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS|DT_SINGLELINE);

	// Return what we used
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
	pDC->SetBkMode(nOldBkMode);
	pDC->SetTextColor(crOldColor);
	pDC->SelectObject(pOldFont);
}

void CDropButton::DrawTriangle(CDC* pDC, CPoint ptTopLeft, int nWidth)
{
	POINT 	ptArray[3];
	
	ptArray[0] 	 = ptTopLeft;
	ptArray[1].x = ptTopLeft.x + nWidth - 1;
	ptArray[1].y = ptTopLeft.y;
	ptArray[2].x = ptTopLeft.x + nWidth / 2;
	ptArray[2].y = ptTopLeft.y + nWidth / 2;

	// Select the Brush and Draw the triangle
	pDC->SelectObject(m_pTriBrush);
	pDC->SelectObject(m_pTriPen);
	pDC->Polygon(ptArray, 3);
}

void CDropButton::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{

}

void CDropButton::OnSize(UINT nType, int cx, int cy) 
{
	CButton::OnSize(nType, cx, cy);
	GetClientRect(m_WindowRect);	
}

void CDropButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// If this window already captured
	if(!m_bOver && !m_pDropWnd->IsWindowVisible())
		SetCapture();
	
	// Convert this window to screen coordinates
	CRect NewRect(m_WindowRect);
	ClientToScreen(NewRect);

	// Convert Point to coordinate
	ClientToScreen(&point);

	// Is the mouse in this window
	if(NewRect.PtInRect(point))
	{
		if(!m_bOver && !m_pDropWnd->IsWindowVisible())
		{
			m_bOver = true;	
			RedrawWindow();
		}
	}
	else
	{
		// Is this in the Drop down?
		if(m_pDropWnd->IsWindowVisible())
		{
			m_pDropWnd->GetWindowRect(NewRect);
			if(!NewRect.PtInRect(point))
				m_pDropWnd->ShowWindow(SW_HIDE);
		}
		else
		{
			// Release the capture and repaint
			m_bOver = false;
			RedrawWindow();
			ReleaseCapture();
		}
	}

	CButton::OnMouseMove(nFlags, point);
}

void CDropButton::DisplayList()
{
	// Convert to this button coordinates to desktop coordinates
	CRect ButtonRect(m_WindowRect);
	MapWindowPoints(GetDesktopWindow(), ButtonRect);
		
	int nTemp = m_pDropWnd->m_pDropList->GetItemHeight(0);
	int nCount = m_pDropWnd->m_pDropList->GetCount();
	
	// Should we recalculate the Acutal height
	int nHeight = m_nListHeight;
	if(m_pDropWnd->m_pDropList->GetCount())
		if(m_pDropWnd->m_pDropList->GetCount() * m_pDropWnd->m_pDropList->GetItemHeight(0) < m_nListHeight)
			nHeight = m_pDropWnd->m_pDropList->GetCount() * m_pDropWnd->m_pDropList->GetItemHeight(0);		
	
	// Move the outer List Window
	CRect NewRect(ButtonRect.left, ButtonRect.bottom - 1, ButtonRect.left + m_nListWidth, ButtonRect.bottom + nHeight );
	m_ListRect = NewRect;
	m_pDropWnd->MoveWindow(m_ListRect, FALSE);

	// What is the size of the list box now? (its integral height - so it may not fill correctly)
	m_pDropWnd->m_pDropList->GetWindowRect(ButtonRect);
	if(ButtonRect.bottom != m_ListRect.bottom)
	{
		ButtonRect.bottom = m_ListRect.bottom; // Two for the border
		ButtonRect.InflateRect(1,1);
		m_pDropWnd->MoveWindow(ButtonRect);
	}

	// Show the Window
	m_pDropWnd->ShowWindow(SW_SHOWNORMAL);
}

void CDropButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Show or hide the list
	m_bOver = false;
	if(m_pDropWnd->IsWindowVisible())
	{
		// Is this outside the Current Rectangle
		MapWindowPoints(GetDesktopWindow(), &point, 2);
		if(!m_ListRect.PtInRect(point))
			m_pDropWnd->ShowWindow(SW_HIDE);
	}
	else	
		DisplayList();

	CButton::OnLButtonDown(nFlags, point);
}
void CDropButton::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	
	if(m_pDropWnd->IsWindowVisible())
		m_pDropWnd->m_pDropList->SetFocus();
		
}
LONG CDropButton::OnSelectionChanged(UINT wParam, LONG lParam)
{
	if(m_bChangeTitle)
	{
		// Set the New Title
		CString csText;
		m_pDropWnd->m_pDropList->GetText(wParam, csText);
		SetWindowText(csText);

		// repaint
		RedrawWindow();		
	}

	// Send a message to the parent that the selection changed
	GetParent()->PostMessage(CM_SELECTION_CHANGED, m_uID, wParam);
	m_pDropWnd->m_pDropList->SetPreviousSelection(wParam);
	return 1;
}



/*
WONT Work unless put inside a DLL - NOT GOING THAT DIRECTION!! 
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT* m = (MOUSEHOOKSTRUCT *) lParam;

	// do stuff and access mouse info here with m->pt.x, m->pt.y,
	if(nCode == HC_ACTION)
	{
		// Was this a mouse click?
		if(wParam == WM_LBUTTONDOWN)
		{
			int nTest = 0;
			::UnhookWindowsHookEx(m_MouseHook);
		}

	}

	return 0;
}
*/
//	HHOOK m_MouseHook;

// Set a hook to this window
//	m_MouseHook = ::SetWindowsHookEx(WH_MOUSE, MouseProc, AfxGetApp()->m_hInstance, GetCurrentThreadId());
