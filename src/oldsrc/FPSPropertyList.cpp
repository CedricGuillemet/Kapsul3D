// FPSPropertyList.cpp : implementation file
//

#include "stdafx.h"
#include "FPSPropertyList.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
CFPSPropertyList::CFPSPropertyList()
{
	m_iVisibleItemCount = 0;
	m_dwTopItem = 1;
	m_dwItemCounter = 0;
	m_nBackColor = GetSysColor(COLOR_BTNFACE);//RGB(192,192,192);
	m_nTextColor = RGB(0, 0, 0);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
CFPSPropertyList::~CFPSPropertyList()
{
	RemoveAllItems();
}


BEGIN_MESSAGE_MAP(CFPSPropertyList, CWnd)
	//{{AFX_MSG_MAP(CFPSPropertyList)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	CRect ScrollRect;
	CRect ClientRect;

	GetClientRect(ClientRect);
	ScrollRect.SetRect(ClientRect.Width() - 20,
						5,
						ClientRect.Width() - 5,
						ClientRect.Height() - 5);

	m_nScrollBar.Create(WS_CHILD | WS_VISIBLE | SBS_VERT,
						ScrollRect,
						this,
						SCROLLBAR_ID);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	RedrawWindow(&dc);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(ClientRect);

	if (!IsWindow(m_nScrollBar.m_hWnd))
		return;

	NotifyItems();
	m_nScrollBar.SetWindowPos(NULL,
								ClientRect.Width() - 20,
								5,
								15,
								ClientRect.Height() - 10,
								SWP_SHOWWINDOW);


}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch (nSBCode)
	{
	case SB_BOTTOM:
		{
			m_dwTopItem = m_dwItemCounter - m_iVisibleItemCount + 1;
			break;
		}
	case SB_TOP:
		{
			m_dwTopItem = 1;
			break;
		}
	case SB_LINEDOWN:
		{
			m_dwTopItem++;
			if (m_dwTopItem > (m_dwItemCounter - m_iVisibleItemCount + 1))
				m_dwTopItem = m_dwItemCounter - m_iVisibleItemCount + 1;
			break;
		}
	case SB_LINEUP:
		{
			m_dwTopItem--;
			if (m_dwTopItem < 1)
				m_dwTopItem = 1;
			break;
		}
	case SB_PAGEDOWN:
		{
			m_dwTopItem = m_dwTopItem + m_iVisibleItemCount - 1;
			if (m_dwTopItem > (m_dwItemCounter - m_iVisibleItemCount + 1))
				m_dwTopItem = m_dwItemCounter - m_iVisibleItemCount + 1;
			break;
		}
	case SB_PAGEUP:
		{
			if (((int)m_dwTopItem - (m_iVisibleItemCount - 1)) < 1)
			{
				m_dwTopItem = 1;
			}
			else
			{
				m_dwTopItem = m_dwTopItem - (m_iVisibleItemCount - 1);
			}
			break;
		}
    case SB_THUMBTRACK:
        if ((nPos+m_iVisibleItemCount-1)>m_dwItemCounter)
            nPos=m_dwItemCounter-m_iVisibleItemCount;
        m_dwTopItem=nPos;
        //pScrollBar->SetScrollPos(m_dwTopItem);
        break;
	}

	//m_nScrollBar.ShowWindow(FALSE);
	//CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	RedrawWindow();
    pScrollBar->SetScrollPos(m_dwTopItem);
	//m_nScrollBar.ShowWindow(TRUE);
    m_nScrollBar.Invalidate(FALSE);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
DWORD CFPSPropertyList::AddItem(CFPSPropertyListItem * pItem)
{
	m_nItemList.AddTail(pItem);

	m_dwItemCounter++;
	pItem->m_dwID = m_dwItemCounter;
	pItem->m_bAutoDelete = FALSE;
	pItem->SetTextColor(m_nTextColor);
	pItem->SetBackColor(m_nBackColor);
	
	return m_dwItemCounter;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::RedrawWindow(CDC * pDC)
{
	CMemDC		DrawDC(pDC);
	CRect		ClientRect;
	POSITION	CurrentPos;
	CFPSPropertyListItem* pEntry;
	int			Y;

	if (!IsWindow(m_hWnd))
		return;

	m_iVisibleItemCount = 0;

	DrawSolidBackground(&DrawDC);
	MakeAllItemsInvisible();

	Y = 3;

	GetClientRect(ClientRect);

	CurrentPos = m_nItemList.GetHeadPosition();
	while (CurrentPos != NULL)
	{
		pEntry = m_nItemList.GetNext(CurrentPos);
		if (pEntry->m_dwID >= m_dwTopItem)
		{
			CRect ItemRect;
			ItemRect.SetRect(3, Y, ClientRect.Width() - 6, Y + 15);
			pEntry->m_pParent = this;
			pEntry->SetItemRect(ItemRect);
			if (Y + 18 < ClientRect.Height())
			{
				pEntry->DrawItem(&DrawDC);
				pEntry->m_bIsVisible = TRUE;
				m_iVisibleItemCount++;
			}
			else
			{
				pEntry->m_bIsVisible = FALSE;
			}
			Y = Y + 16;
		}
		else
		{
			pEntry->m_bIsVisible = FALSE;
		}
	}

	if (m_iVisibleItemCount == (int)m_dwItemCounter)
	{
		m_nScrollBar.ShowWindow(FALSE);
	}
	else
	{
		m_nScrollBar.SetScrollRange(1, m_dwItemCounter, TRUE);
		if (m_dwTopItem == 1)
		{
			m_nScrollBar.SetScrollPos(1);
		}
		else if (m_dwTopItem == (m_dwItemCounter - m_iVisibleItemCount + 1))
		{
			m_nScrollBar.SetScrollPos(m_dwItemCounter);
		}
		else
		{
			int pos = m_dwTopItem + (m_iVisibleItemCount / 2);
			m_nScrollBar.SetScrollPos(pos);
		}
		EnableScrollBar(SCROLLBAR_ID, TRUE);
		m_nScrollBar.EnableScrollBar();
		m_nScrollBar.ShowScrollBar();
	}
}


/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::RemoveAllItems()
{
	POSITION		CurrentPos;
	CFPSPropertyListItem* pEntry;

	CurrentPos = m_nItemList.GetHeadPosition();
	while (CurrentPos != NULL)
	{
		pEntry = m_nItemList.GetNext(CurrentPos);
		if (pEntry->m_bAutoDelete)
			delete pEntry;
	}
	m_nItemList.RemoveAll();
	m_dwItemCounter = 0;
	m_dwTopItem = 1;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::DrawSolidBackground(CDC * pDC)
{
	CRect	ClientRect;

	GetClientRect(ClientRect);

	pDC->FillSolidRect(ClientRect,/*RGB(192,192,192)*/GetSysColor(COLOR_BTNFACE));
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	POSITION	CurrentPos;
	CFPSPropertyListItem* pEntry;
	BOOL		Found = FALSE;

	CurrentPos = m_nItemList.GetHeadPosition();
	while ((CurrentPos != NULL))
	{
		pEntry = m_nItemList.GetNext(CurrentPos);
		if (pEntry->OnClick(point))
			Found = TRUE;
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::OnDestroy() 
{
	NotifyItems();

	CWnd::OnDestroy();
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::OnClose() 
{
	NotifyItems();
	
	CWnd::OnClose();
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::NotifyItems()
{
	POSITION		CurrentPos;
	CFPSPropertyListItem* pEntry;

	CurrentPos = m_nItemList.GetHeadPosition();
	while (CurrentPos != NULL)
	{
		pEntry = m_nItemList.GetNext(CurrentPos);
		CPoint pt(-1, -1);
		pEntry->OnClick(pt);
	}

}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::MakeAllItemsInvisible()
{
	POSITION				CurrentPos;
	CFPSPropertyListItem*	pEntry;

	CurrentPos = m_nItemList.GetHeadPosition();
	while (CurrentPos != NULL)
	{
		pEntry = m_nItemList.GetNext(CurrentPos);
		pEntry->m_bIsVisible = FALSE;
	}
}


/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItem(DWORD dwID, CFPSPropertyListItem * pItem)
{
	pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
CFPSPropertyListItem* CFPSPropertyList::GetItemByID(DWORD dwID)
{
	POSITION		CurrentPos;
	CFPSPropertyListItem* pEntry;
	BOOL			bFound = FALSE;

	CurrentPos = m_nItemList.GetHeadPosition();
	while ((CurrentPos != NULL) && (!bFound))
	{
		pEntry = m_nItemList.GetNext(CurrentPos);
		if (pEntry->m_dwID == dwID)
			bFound = TRUE;
	}

	if (!bFound)
	{
		return NULL;
	}
	else
	{
		return pEntry;
	}
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
DWORD CFPSPropertyList::GetItemData(DWORD dwID)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return NULL;

	return pItem->GetItemData();
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetupItem(DWORD dwID, PROPERTYITEMSETUP * pSetupInfo)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->Setup(pSetupInfo);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemData(DWORD dwID, DWORD Data)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->SetItemData(Data);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
DWORD CFPSPropertyList::AddItem(PROPERTYITEMSETUP * pSetupInfo)
{
	CFPSPropertyListItem* pItem = new CFPSPropertyListItem;

	pItem->Setup(pSetupInfo);

	m_dwItemCounter++;
	pItem->m_dwID = m_dwItemCounter;
	pItem->m_bAutoDelete = TRUE;

	m_nItemList.AddTail(pItem);
	
	return m_dwItemCounter;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemInfo(DWORD dwID, PROPERTYITEMSETUP & Setup)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->GetSetup(&Setup);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::AboutToChange()
{
	NotifyItems();
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::RedrawWindow()
{
	CClientDC dc (this);

	RedrawWindow(&dc);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::Create(DWORD dwStyle, const RECT & rect, CWnd * pParentWnd, UINT nID, CCreateContext * pContext)
{
	return Create(NULL, NULL, dwStyle, rect, pParentWnd, nID, pContext);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::RemoveItem(DWORD dwItemID)
{
	CFPSPropertyListItem* pEntry = GetItemByID(dwItemID);

	if (pEntry)
	{
		POSITION Pos = m_nItemList.Find(pEntry);
		if (Pos)
		{
			m_nItemList.RemoveAt(Pos);
			delete pEntry;
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
CFPSPropertyListItem* CFPSPropertyList::GetItemByName(LPCSTR lpszName)
{
	POSITION CurrentPos;
	CFPSPropertyListItem* pEntry;
	BOOL bFound = FALSE;

	CurrentPos = GetFirstItemPosition();
	while (CurrentPos != NULL && !bFound)
	{
		pEntry = GetNextItem(CurrentPos);
		if (pEntry->m_strName == lpszName)
			bFound = TRUE;
	}

	if (bFound)
		return pEntry;

	return NULL;

}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(DWORD dwID, CString & strValue)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	strValue = pItem->GetTextValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(LPCSTR lpszName, CString & strValue)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	strValue = pItem->GetTextValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(DWORD dwID, COLORREF & Value)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	Value = pItem->GetColorValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(LPCSTR lpszName, COLORREF & Value)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	Value = pItem->GetColorValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(DWORD dwID, LOGFONT & Value)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	Value = pItem->GetFontValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(LPCSTR lpszName, LOGFONT & Value)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	Value = pItem->GetFontValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(DWORD dwID, long & lValue)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	lValue = pItem->GetLongValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(LPCSTR lpszName, long & lValue)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	lValue = pItem->GetLongValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(DWORD dwID, int & iValue)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	iValue = pItem->GetIntegerValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemValue(LPCSTR lpszName, int & iValue)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	iValue = pItem->GetIntegerValue();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
DWORD CFPSPropertyList::AddItem(LPCSTR lpszName, DWORD dwType, DWORD dwData)
{
	PROPERTYITEMSETUP	ItemInfo;

	ItemInfo.strName = lpszName;
	ItemInfo.dwType = dwType;
	ItemInfo.dwData = dwData;
	ItemInfo.lLongValue = 0;
	ItemInfo.iIntegerValue = 0;
	ItemInfo.bAllowComboEdit = FALSE;
	ItemInfo.bFileOpenDialog = TRUE;
	ItemInfo.bBoolValue = FALSE;
	ItemInfo.ColorValue = RGB(0, 0, 0);
	ItemInfo.FontValue.lfHeight = 80;
	ItemInfo.FontValue.lfWidth = 0;
	ItemInfo.FontValue.lfEscapement = 0;
	ItemInfo.FontValue.lfOrientation = 0;
	ItemInfo.FontValue.lfWeight = 400;
	ItemInfo.FontValue.lfItalic = FALSE;
	ItemInfo.FontValue.lfUnderline = FALSE;
	ItemInfo.FontValue.lfStrikeOut = FALSE;
	ItemInfo.FontValue.lfCharSet = ANSI_CHARSET;
	ItemInfo.FontValue.lfOutPrecision = OUT_DEFAULT_PRECIS;
	ItemInfo.FontValue.lfClipPrecision = OUT_DEFAULT_PRECIS;
	ItemInfo.FontValue.lfQuality = PROOF_QUALITY;
	ItemInfo.FontValue.lfPitchAndFamily = DEFAULT_PITCH;
	strcpy(ItemInfo.FontValue.lfFaceName, "Arial");

	return AddItem(&ItemInfo);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::IsItemVisible(DWORD dwItem)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwItem);
	if (!pItem)
		return FALSE;

	return pItem->IsVisible();
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::IsItemVisible(LPCSTR lpszName)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	return pItem->IsVisible();
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemRect(DWORD dwItem, CRect & rect)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwItem);
	if (!pItem)
		return FALSE;

	rect = pItem->m_nItemRect;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::GetItemRect(LPCSTR lpszName, CRect & rect)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	rect = pItem->m_nItemRect;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(DWORD dwID, LPCSTR lpszValue)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->m_strTextValue = lpszValue;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(LPCSTR lpszName, LPCSTR lpszValue)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	pItem->m_strTextValue = lpszValue;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(DWORD dwID, long lValue)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->m_lLongValue = lValue;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(LPCSTR lpszName, long lValue)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	pItem->m_lLongValue = lValue;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(DWORD dwID, int iValue)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->m_iIntegerValue = iValue;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(LPCSTR lpszName, int iValue)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	pItem->m_iIntegerValue = iValue;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(DWORD dwID, LOGFONT Value)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->m_nFontValue = Value;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(LPCSTR lpszName, LOGFONT Value)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	pItem->m_nFontValue = Value;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(DWORD dwID, COLORREF Value)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->m_nColorValue = Value;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValue(LPCSTR lpszName, COLORREF Value)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	pItem->m_nColorValue = Value;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::SetTextColor(COLORREF NewColor)
{
	POSITION CurrentPos;
	CFPSPropertyListItem* pEntry;

	CurrentPos = GetFirstItemPosition();
	while (CurrentPos != NULL)
	{
		pEntry = GetNextItem(CurrentPos);
		pEntry->SetTextColor(NewColor);
	}

	m_nTextColor = NewColor;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyList::SetBackColor(COLORREF NewColor)
{
	POSITION CurrentPos;
	CFPSPropertyListItem* pEntry;

	CurrentPos = GetFirstItemPosition();
	while (CurrentPos != NULL)
	{
		pEntry = GetNextItem(CurrentPos);
		pEntry->SetBackColor(NewColor);
	}

	m_nBackColor = NewColor;
}


/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValueList(DWORD dwID, CStringList & ValueList)
{
	CFPSPropertyListItem* pItem = GetItemByID(dwID);
	if (!pItem)
		return FALSE;

	pItem->m_nComboItemList.AddTail(&ValueList);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyList::SetItemValueList(LPCSTR lpszName, CStringList & ValueList)
{
	CFPSPropertyListItem* pItem = GetItemByName(lpszName);
	if (!pItem)
		return FALSE;

	pItem->m_nComboItemList.AddTail(&ValueList);

	return TRUE;
}
