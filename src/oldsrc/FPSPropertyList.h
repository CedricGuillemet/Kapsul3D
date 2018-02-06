// ****************************************************************
// 
// CFPSPropertyList
// Created by Matt Gullett
// (c) 1998
//
// This class is a CWnd derived custom control which implements a
// VB/Access-LIKE property list window.  The public I/F for this
// class is similar to the CListCtrl and other MFC control wrappers.
// 
// DEPENDENCIES : CFPSPropertyListItem class
//
// NOTE: The OnVScroll function is not 100% implemented.  The
// thumb-position messages are not being handled.
//
// ****************************************************************

#if !defined(AFX_FPSPROPERTYLIST_H__A0985602_8C52_11D1_94BC_00207811FA68__INCLUDED_)
#define AFX_FPSPROPERTYLIST_H__A0985602_8C52_11D1_94BC_00207811FA68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FPSPropertyList.h : header file
//

#define SCROLLBAR_ID		1000

#include "afxtempl.h"
#include "FPSPropertyListItem.h"

class __declspec( dllexport ) CFPSPropertyList : public CWnd
{
private:
	int			m_iVisibleItemCount;
	DWORD		m_dwTopItem;
	CScrollBar	m_nScrollBar;
	DWORD		m_dwItemCounter;
	COLORREF	m_nBackColor;
	COLORREF	m_nTextColor;

	void RedrawWindow();
	CFPSPropertyListItem* GetItemByName (LPCSTR lpszName);
	CFPSPropertyListItem* GetItemByID (DWORD dwID);
	void MakeAllItemsInvisible();
	void NotifyItems();
	void DrawSolidBackground (CDC* pDC);
	void RedrawWindow (CDC* pDC);
	CTypedPtrList<CObList, CFPSPropertyListItem*> m_nItemList;
// Construction
public:
	CFPSPropertyList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFPSPropertyList)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL SetItemValueList(LPCSTR lpszName, CStringList & ValueList);
	virtual BOOL SetItemValueList (DWORD dwID, CStringList& ValueList);
	virtual void SetBackColor (COLORREF NewColor);
	virtual void SetTextColor (COLORREF NewColor);
	virtual COLORREF GetTextColor () {return m_nTextColor;}
	virtual COLORREF GetBackColor () {return m_nBackColor;}
	virtual BOOL SetItemValue (LPCSTR lpszName, COLORREF Value);
	virtual BOOL SetItemValue (DWORD dwID, COLORREF Value);
	virtual BOOL SetItemValue (LPCSTR lpszName, LOGFONT Value);
	virtual BOOL SetItemValue (DWORD dwID, LOGFONT Value);
	virtual BOOL SetItemValue (LPCSTR lpszName, int iValue);
	virtual BOOL SetItemValue (DWORD dwID, int iValue);
	virtual BOOL SetItemValue(LPCSTR lpszName, long lValue);
	virtual BOOL SetItemValue (DWORD dwID, long lValue);
	virtual BOOL SetItemValue (LPCSTR lpszName, LPCSTR lpszValue);
	virtual BOOL SetItemValue (DWORD dwID, LPCSTR lpszValue);
	virtual BOOL GetItemRect(LPCSTR lpszName, CRect & rect);
	virtual BOOL GetItemRect (DWORD dwItem, CRect& rect);
	virtual BOOL IsItemVisible(LPCSTR lpszName);
	virtual BOOL IsItemVisible (DWORD dwItem);
	virtual DWORD AddItem (LPCSTR lpszName, DWORD dwType, DWORD dwData = NULL);
	virtual BOOL GetItemValue(LPCSTR lpszName, int & iValue);
	virtual BOOL GetItemValue(DWORD dwID, int & iValue);
	virtual BOOL GetItemValue(LPCSTR lpszName, long & lValue);
	virtual BOOL GetItemValue (DWORD dwID, long& lValue);
	virtual BOOL GetItemValue(LPCSTR lpszName, LOGFONT & Value);
	virtual BOOL GetItemValue (DWORD dwID, LOGFONT& Value);
	virtual BOOL GetItemValue(LPCSTR lpszName, COLORREF & Value);
	virtual BOOL GetItemValue (DWORD dwID, COLORREF& Value);
	virtual BOOL GetItemValue(LPCSTR lpszName, CString & strValue);
	virtual BOOL GetItemValue (DWORD dwID, CString& strValue);
	virtual BOOL RemoveItem (DWORD dwItemID);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void AboutToChange();
	virtual POSITION GetFirstItemPosition () {return m_nItemList.GetHeadPosition();}
	virtual CFPSPropertyListItem* GetNextItem(POSITION& CurrentPos) {return m_nItemList.GetNext(CurrentPos);}
	virtual BOOL GetItemInfo (DWORD dwID, PROPERTYITEMSETUP& Setup);
	virtual DWORD AddItem (PROPERTYITEMSETUP* pSetupInfo);
	virtual BOOL SetItemData (DWORD dwID, DWORD Data);
	virtual BOOL SetupItem (DWORD dwID, PROPERTYITEMSETUP* pSetupInfo);
	virtual DWORD GetItemData (DWORD dwID);
	virtual BOOL GetItem (DWORD dwID, CFPSPropertyListItem* pItem);
	virtual int GetItemCount () {return m_nItemList.GetCount();}
	virtual void RemoveAllItems();
	virtual DWORD AddItem (CFPSPropertyListItem* pItem);
	virtual ~CFPSPropertyList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFPSPropertyList)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FPSPROPERTYLIST_H__A0985602_8C52_11D1_94BC_00207811FA68__INCLUDED_)
