// ****************************************************************
// 
// CFPSPropertyListItem
// Created by Matt Gullett
// (c) 1998
//
// This class is a support class for the CFPSPropertyList custom
// control.  This class implements the property item objects which
// get drawn on demand.  Several property types are supported.
// these are :
//           TEXT
//           INTEGER
//           LONG
//           FONT
//           COLOR
//           FILE
//           COMBO BOX
//           BOOLEAN
// 
// DEPENDENCIES : CFPSPropertyList class
//
// NOTE :
// This class is not usually accesed directy as wrapper functions
// are implemented in the CFPSPropertyList class for creating
// and setting up these items.  The PROPERTYITEMSETUP structure
// is provided to permit setting up the configuration of these
// objects.  In order to keep windows resource usage low, no
// GDI objects are maintained for object duraction, instead they
// are created on demand
//
// ****************************************************************

#if !defined(AFX_FPSPROPERTYLISTITEM_H__A0985603_8C52_11D1_94BC_00207811FA68__INCLUDED_)
#define AFX_FPSPROPERTYLISTITEM_H__A0985603_8C52_11D1_94BC_00207811FA68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "afxtempl.h"

#define FPS_PROPLIST_ITEM_CHANGED		WM_USER + 1


#define FPSPROPERTYITEMTYPE_TEXT			1			// CEdit
#define FPSPROPERTYITEMTYPE_INTEGER			2			// CEdit
#define FPSPROPERTYITEMTYPE_LONG			3			// CEdit
#define FPSPROPERTYITEMTYPE_FONT			4			// Button
#define FPSPROPERTYITEMTYPE_COLOR			5			// Button
#define FPSPROPERTYITEMTYPE_FILE			6			// Button
#define FPSPROPERTYITEMTYPE_COMBOBOX		7			// CComboBox
#define FPSPROPERTYITEMTYPE_BOOL			10			// Click

typedef struct PROPERTYITEMSETUPTAG
{
	CString		strName;
	DWORD		dwType;
	DWORD		dwData;
	CString		strTextValue;
	long		lLongValue;
	int			iIntegerValue;
	CStringList	ComboBoxList;
	BOOL		bAllowComboEdit;
	CString		strFileFilter;
	BOOL		bFileOpenDialog;
	BOOL		bBoolValue;
	LOGFONT		FontValue;
	COLORREF	ColorValue;
} PROPERTYITEMSETUP;

class __declspec( dllexport ) CFPSPropertyListItem : public CObject  
{
	friend class CFPSPropertyList;
protected:
	COLORREF	m_nTextColor;
	COLORREF	m_nBackColor;
	CFont*		m_pTempFont;
	BOOL		m_bAutoDelete;
	BOOL		m_bIsVisible;
	LOGFONT		m_nDrawFont;
	CRect		m_nItemRect;
	CRect		m_nEditRect;
	CRect		m_nButtonRect;
	CWnd*		m_pParent;
	CWnd*		m_pItemEditWindow;

	BOOL		m_bIsCreated;
	CString		m_strName;
	DWORD		m_dwID;
	DWORD		m_dwItemData;
	CString		m_strItemText;
	DWORD		m_dwItemType;

	BOOL		m_bIsButtonCreated;


	// each item type needs an object of some kind (except for MORE types)

	// FPSPROPERTYITEMTYPE_TEXT
	CString		m_strTextValue;

	// FPSPROPERTYITEMTYPE_INTEGER
	int			m_iIntegerValue;

	// FPSPROPERTYITEMTYPE_LONG
	long		m_lLongValue;

	// FPSPROPERTYITEMTYPE_FONT
	LOGFONT		m_nFontValue;

	// FPSPROPERTYITEMTYPE_COLOR
	COLORREF	m_nColorValue;

	// FPSPROPERTYITEMTYPE_FILE
	CString		m_strFileFilter;
	BOOL		m_bFileOpenDialog;

	// FPSPROPERTYITEMTYPE_COMBOBOX
	BOOL		m_bAllowTextEdit;
	CStringList m_nComboItemList;

	// FPSPROPERTYITEMTYPE_BOOL
	BOOL		m_bBoolValue;

public:
	virtual void SetTextColor (COLORREF NewColor) {m_nTextColor = NewColor;}
	virtual void SetBackColor (COLORREF NewColor) {m_nBackColor = NewColor;}
	virtual COLORREF GetTextColor () {return m_nTextColor;}
	virtual COLORREF GetBackColor () {return m_nBackColor;}
	virtual LOGFONT GetDrawFont() {return m_nDrawFont;}
	virtual void SetDrawFont(LOGFONT NewFont) {m_nDrawFont = NewFont;}
	virtual void GetSetup (PROPERTYITEMSETUP* pSetupInfo);
	virtual void SetItemData (DWORD Data) {m_dwItemData = Data;}
	virtual DWORD GetItemData () {return m_dwItemData;}
	virtual BOOL IsVisible () {return m_bIsVisible;}
	virtual void Setup (PROPERTYITEMSETUP* pSetupInfo);
	CFPSPropertyListItem();
	~CFPSPropertyListItem();

	virtual BOOL OnClick (CPoint pt);
	virtual BOOL GetBoolValue () {return m_bBoolValue;}
	virtual LOGFONT GetFontValue () {return m_nFontValue;}
	virtual long GetLongValue () {return m_lLongValue;}
	virtual int GetIntegerValue () {return m_iIntegerValue;}
	virtual CString& GetTextValue () {return m_strTextValue;}
	virtual COLORREF GetColorValue () {return m_nColorValue;}
	virtual BOOL DrawItem (CDC* pDC);
	virtual void SetItemRect (CRect& rect);
private:
	void DrawSunkenButton();
	void DisplayComboBox (CString Value);
	void DisplayEditBox (CString Value);
	void HandleWindows();
	void DrawColor (CDC* pDC);
	void DrawText (CDC* pDC, CString Text);
	void RedrawItem();
	void DisplayFileDialog();
	void DisplayColorDialog();
	void DisplayFontDialog();
	void DrawItemText (CDC* pDC);
	BOOL DoesItemHaveButton();
};

#endif // !defined(AFX_FPSPROPERTYLISTITEM_H__A0985603_8C52_11D1_94BC_00207811FA68__INCLUDED_)
