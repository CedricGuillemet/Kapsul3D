#if !defined(AFX_OBJECTINSPECTOR_H__DB3F042A_B838_4CB7_B9AA_82DB7E7C82C6__INCLUDED_)
#define AFX_OBJECTINSPECTOR_H__DB3F042A_B838_4CB7_B9AA_82DB7E7C82C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "float.h"

#include <vector>
#include <algorithm>
#include <functional>
#include "FileEditCtrl.h"
#include "OXMaskedEdit.h"
#include "MemoEditCtrl.h"


using namespace std;

#define CLASS_OBJECTINSPECTOR "ObjectInspectorCtrl"

#define IDC_SCROLLBAR		  999
#define IDC_INPLACECONTROL	  998
												// Notification codes :
#define OIVN_ITEMCHANGED      LVN_ITEMCHANGED	// Inplacecontrol lost focus 
												// and the associated property has been changed
#define OIVN_ITEMCHANGING     LVN_ITEMCHANGING  // Value has been changed

#define IsCtrlDown()		  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 ) 

/////////////////////////////////////////////////////////////////////////////
// CObjectInspector 


class KAPSUL_DESC CObjectInspector : public CWnd
{
	
public:

	enum EBorderStyle   { bsNone, bsSingle, bsLowered, bsRaised };
	enum EPropertyType  { ptGroup,  ptShort, ptInteger, ptFloat, ptDouble, ptBool, ptDate, ptColor, ptStringList, ptFileBroswer, ptMaskedEdit, ptMemoEdit, ptSliderCtrl};
	enum ESortDirection { sdUp, sdDown };

	class KAPSUL_DESC CProperty 
	{

	friend CObjectInspector;

public:
	vector <CProperty*> m_Childs;           // vector of child items

public :
	
		
		
		CRect		m_rtPropertyRect;		    // bounding rectangle of the property cell
		CRect		m_rtValueRect;				// bounding rectangle of the value cell
		CRect		m_rtGroupRect;				// bounding rectangle of the group's plus/minus sign
		
		CWnd*		m_pInplaceControl;			// Currently active Inplace-Control
		CFont*		m_pControlFont;				// Controlfont
		
		CProperty*	m_pParent;					// Parent property

		bool		m_bExpanded;				// true if item is expanded
		bool		m_bVisible;					// true if item is visible (i.e. the parent is expanded)
		bool		m_bUseTime;					// used for COleDateTime properties. If true only the time portion will be shown
		bool        m_bRadio;					// used for bool properties. If true property is part of a radio group
		bool        m_bRadioDummy;				

		DWORD		m_dwComboBoxStyle;			

		CString     m_cFloatFormat;				// used for formatting a float or double value. Set this for customizing float/double display

		//////////////////////////////

		CWnd* CreateControlFromType();			// Create control depending on the property type
public:
		bool  GetValueInternal();				// Get a property value from the inplace control
		void  SetValueInternal();				// Set a property value 

		void  SendNotification(int nMsg = OIVN_ITEMCHANGED); // Sends notification to the OI's parent window
	

	public :
	
		CString		  m_cName;					// property name

												// Property values : 
		short*        m_psValue;				// 
		int*		  m_pnValue;
		float*        m_pfValue;
		double*       m_pdblValue;
		bool*         m_pbValue;
		COleDateTime* m_pdtValue;
		COLORREF*     m_pclValue;
		CString*      m_pszValue;
		CStringList*  m_pStringList;

		LPARAM        m_pItemData;

		double		  m_dblMin;					// Limits (min,max) for all numeric properties
		double		  m_dblMax;					// ...
		int           m_nMaxStringLen;			// Max. string length for string properties
		int           m_nImage;					// Index of the image to be shown in front of the propty's name
		int			  m_nIndex;					// Index of the property in the parent's child vector 
					
		EPropertyType m_ptType;					// Property type

		CWnd*		  m_pParentWnd;				// parent window (CObjectInspector)
		bool		  m_bFocused;				// True if currently focused, i.e. hottracked
		bool	  	  m_bEditing;				// True if currently in edit mode
		
		void		  BeginEdit();				// Create the appropr. inplace control and put property in edit mode
		bool		  EndEdit();				// destroy the appropr. inplace control and put property in non-edit mode
		void		  CreateInplaceControl();	
		void		  DestroyInplaceControl();	
		void		  SetRectangles(CRect rtProperty, CRect rtValue); // Sets the bounding rectangles for both the property and the value cell
		void		  Create(CString cName, EPropertyType ptType);	   
		void          RangeError(int nMin, int nMax);				  // Range checking stuff for numeric properties	
		void          RangeError(float fMin, float fMax);			  // ... 
		void          RangeError(double dblMin, double dblMax);       // ....


		CWnd*		  GetInplaceControl();		// Returns pointer to the currently active inplace control
		CRect		  GetPropertyRect();		
		CRect		  GetValueRect();
		CString		  GetValueAsText();
		

	public :

		CProperty (CString cName)
		{
			m_cName=cName;
			Create (cName, ptGroup);
		}
				
		CProperty (CString cName, short *psValue, short sMin = SHRT_MIN, short sMax = SHRT_MAX)
		{
			m_dblMin = (double) sMin;
			m_dblMax = (double) sMax;
			m_psValue = psValue;
			Create(cName, ptShort);
		}
		 
		CProperty (CString cName, bool bRadio, int *pnValue)
		{
			m_bRadioDummy = false;
			m_pbValue = &m_bRadioDummy;
			m_pnValue = pnValue;
			Create(cName, ptBool);
			m_bRadio = true;
		}

		CProperty (CString cName, int *pnValue, int nMin = INT_MIN, int nMax = INT_MAX)
		{
			m_dblMin = (double) nMin;
			m_dblMax = (double) nMax;
			m_pnValue = pnValue;
			Create(cName, ptInteger);
		}

		CProperty (CString cName, float *pfValue, float fMin = FLT_MIN, float fMax = FLT_MAX)
		{
			m_dblMin = (double) fMin;
			m_dblMax = (double) fMax;
			m_pfValue = pfValue;
			Create(cName, ptFloat);
		}

		CProperty (CString cName, double *pdblValue, double dblMin = DBL_MIN, double dblMax = DBL_MAX)
		{
			m_dblMin = (double) dblMin;
			m_dblMax = (double) dblMax;
			m_pdblValue = pdblValue;
			Create(cName, ptDouble);
		}

		CProperty (CString cName, bool *pbValue)
		{
			m_pbValue = pbValue;
			Create(cName, ptBool);
		}

		CProperty (CString cName, COleDateTime *pdtValue, bool bTime = false) 
		{
			m_bUseTime = bTime;
			m_pdtValue = pdtValue;
			Create(cName, ptDate);
		}

		CProperty (CString cName, COLORREF *pclValue) 
		{
			m_pclValue = pclValue;
			Create(cName, ptColor);
		}

		CProperty(CString cName, CString *pszValue, CStringList *pStringList = NULL, int nMaxLen = -1, DWORD dwStyle = CBS_DROPDOWN)
		{
			m_nMaxStringLen   = nMaxLen;
			m_pszValue		  = pszValue;
			m_pStringList	  = pStringList;
			m_dwComboBoxStyle = dwStyle;
			Create(cName, ptStringList);
		}

		CProperty (UINT nID)
		{
			CString cText;
			cText.LoadString (nID);
			Create (cText, ptGroup);
		}

		CProperty (UINT nID, short *psValue, short sMin = SHRT_MIN, short sMax = SHRT_MAX)
		{
			CString cText;
			cText.LoadString (nID);
			m_dblMin = (double) sMin;
			m_dblMax = (double) sMax;
			m_psValue = psValue;
			Create(cText, ptShort);
		}

		CProperty (UINT nID, int *pnValue, int nMin = INT_MIN, int nMax = INT_MAX)
		{
			CString cText;
			cText.LoadString (nID);
			m_dblMin = (double) nMin;
			m_dblMax = (double) nMax;
			m_pnValue = pnValue;
			Create(cText, ptInteger);
		}

		CProperty (UINT nID, float *pfValue, float fMin = FLT_MIN, float fMax = FLT_MAX)
		{
			CString cText;
			cText.LoadString (nID);
			m_dblMin = (double) fMin;
			m_dblMax = (double) fMax;
			m_pfValue = pfValue;
			Create(cText, ptFloat);
		}

		CProperty (UINT nID, double *pdblValue, double dblMin = DBL_MIN, double dblMax = DBL_MAX)
		{
			CString cText;
			cText.LoadString (nID);
			m_dblMin = (double) dblMin;
			m_dblMax = (double) dblMax;
			m_pdblValue = pdblValue;
			Create(cText, ptDouble);
		}

		CProperty (UINT nID, bool *pbValue, bool bRadio = false)
		{
			CString cText;
			cText.LoadString (nID);
			m_bRadio = bRadio;
			m_pbValue = pbValue;
			Create(cText, ptBool);
		}

		CProperty (UINT nID, COleDateTime *pdtValue, bool bTime = false) 
		{
			CString cText;
			cText.LoadString (nID);
			m_bUseTime = bTime;
			m_pdtValue = pdtValue;
			Create(cText, ptDate);
		}

		CProperty (UINT nID, COLORREF *pclValue) 
		{
			CString cText;
			cText.LoadString (nID);
			m_pclValue = pclValue;
			Create(cText, ptColor);
		}

		CProperty(UINT nID, CString *pszValue, CStringList *pStringList = NULL, int nMaxLen = -1, DWORD dwStyle = CBS_DROPDOWN)
		{
			CString cText;
			cText.LoadString (nID);
			m_nMaxStringLen   = nMaxLen;
			m_pszValue		  = pszValue;
			m_pStringList	  = pStringList;
			m_dwComboBoxStyle = dwStyle;
			Create(cText, ptStringList);
		}

		CProperty(CString pszPropName,CString *pszInitialValue,CString pszFilter)
		{
			m_pszValue = pszInitialValue;
			Create(pszPropName,ptFileBroswer);
		}

		CProperty(CString pszPropName,CString pszMask)
		{
			m_pszValue = new CString(pszMask);
			Create(pszPropName,ptMaskedEdit);
		}

		CProperty(CString pszPropName,int iPlaceHolder)
		{
			m_pszValue = new CString(" ");
			Create(pszPropName,ptMemoEdit);
		}

		CProperty(CString pszPropName,int *Pos,int ValMin,int ValMax,bool bPlaceHolder = FALSE)
		{
			m_dblMin = (double)ValMin;
			m_dblMax = (double)ValMax;
			m_pnValue = Pos;
			Create(pszPropName,ptSliderCtrl);
		}

		bool operator < (const CProperty& other) const { return (other.m_cName > m_cName) ? true : false; };

		virtual		 ~CProperty();
	
		EPropertyType GetType()						  { return m_ptType; };
		void          SetImage(int nImage)			  { m_nImage = nImage; };
		void          SetFloatFormat(CString cFormat) { m_cFloatFormat = cFormat; }
		void          SetItemData(LPARAM pItemData)   { m_pItemData = pItemData; }
		LPARAM        GetItemData()                   { return m_pItemData; }
		CString       GetName()						  { return m_cName; };
		void          Expand()						  { m_bExpanded = true; }
		void          Collapse()					  { m_bExpanded = false; }

		void          AddProperty(CProperty *pProperty);

		bool          GetValueFromControl(short *psValue);
		bool          GetValueFromControl(int *pnValue);
		bool          GetValueFromControl(bool *pbValue);
		bool          GetValueFromControl(float *pfValue);
		bool          GetValueFromControl(double *pdblValue);
		bool          GetValueFromControl(COleDateTime *pdtValue);
		bool          GetValueFromControl(CString *pszValue);
		bool          GetValueFromControl(COLORREF *pclValue);
	};

public:

	vector <CProperty*> m_PropertyList;

	int        m_nXSplitterPos;
	int        m_nScrollPos;
	int        m_nScrollRange;
	int		   m_nOverallItemHeight;
	int        m_nFirstVisibleItem;
	int        m_nExpandedItemsCount;
	int        m_nHeaderHeight;
	int		   m_nIndent;
	int        m_nComboDroppedHeight;
	int        m_nCellHeight;
	int        m_nMinPropertyColWidth;
	int        m_nMinValueColWidth;
	bool       m_bSplitterMoving;
	bool       m_bScrollbarVisible;
	bool       m_b3dFocus;
	bool       m_bHotTrack;
	bool       m_bSorted;
	bool       m_bW2KStyle;
	CRect      m_rtClientRect;
	CRect      m_rtSplitterRect;
	CRect      m_rtPropertyHeaderRect;
	CRect	   m_rtValueHeaderRect;
	COLORREF   m_clBackColor;
	COLORREF   m_clPropertyRowColor;
	COLORREF   m_clValueRowColor;
	COLORREF   m_clGridLineColor;
	COLORREF   m_clFocusLineColor;
	CString    m_cPropertyHeaderTitle;
	CString    m_cPropertyValueTitle;
	CScrollBar m_ScrollBar;
	CProperty* m_pEditingProperty;
	CProperty* m_pLastEnteredProperty;

	CBrush          m_CtrlBrush;
	CImageList*		m_pImageList; 
	EBorderStyle	m_bsStyle;
	ESortDirection	m_sdSortDirection;

	void CleanUp();
	void CalculateScrollRange(CProperty *pProperty = NULL);
	void DrawScrollBar();
	void DrawBorder(CDC *pDC, CRect& rect);
	void DrawSplitter(CDC *pDC);
	void DrawHeader(CDC *pDC);
	void DrawItem(CDC*pDC, CProperty *pProperty, int& nY, int& nCellHeight);
	void DrawChildItems(CDC*pDC,int& nItem, CProperty *pProperty, int& nY, int& nCellHeight);
	void DrawItems(CDC *pDC);
	

	CProperty *GetNextProperty(CProperty *pProperty);
	CProperty *GetPrevProperty(CProperty *pProperty);
	CProperty *GetPropertyFromPoint(CPoint point, CObjectInspector::CProperty *pRoot);

public:

	CObjectInspector();

	typedef struct tagNM_OIVIEW {
		NMHDR	   hdr;
		CProperty* pProperty;
	} NM_OIVIEW;

	BOOL		 Create(const RECT& rect, CWnd* parent, UINT nID, DWORD dwStyle = WS_POPUP | WS_VISIBLE,CString szProp="Properties",CString szValue="Value");

	void		 AddProperty(CProperty* pProperty);
	void		 SetComboDropHeight(int nHeight) { m_nComboDroppedHeight = nHeight; };
	void		 SetImageList(CImageList *pList) { m_pImageList = pList; };
	void		 GeHeaderTitles(CString& cPropertyHeaderTitle, CString& cPropertyValueTitle);
	bool		 GetHotTrack();
	bool		 Get3dFocus();
	int			 GetMinPropertyColWidth();
	int			 GetMinValueColWidth();
	COLORREF	 GetBackColor();
	COLORREF	 GetPropertyColTextColor();
	COLORREF	 GetValueColTextColor();
	COLORREF	 GetGridLineColor();
	COLORREF	 GetFocusLineColor();
	EBorderStyle GetBorderStyle();
	
	void		 SetHeaderTitles(CString cPropertyHeaderTitle, CString cPropertyValueTitle);
	void		 SetBorderStyle(EBorderStyle bsStyle);
	void		 SetHotTrack(bool bEnabled);
	void		 Set3dFocus(bool bValue);
	void		 SetBackColor(COLORREF clBackColor);
	void		 SetPropertyColTextColor(COLORREF clPropertyRowColor);
	void	     SetValueColTextColor(COLORREF clValueRowColor);
	void		 SetGridLineColor(COLORREF clGridLineColor);
	void		 SetFocusLineColor(COLORREF clFocusLineColor);
	void		 SetMinPropertyColWidth(int nWidth);
	void		 SetMinValueColWidth(int nWidth);
	void	     SetStyle(bool bW2K);

	//{{AFX_VIRTUAL(CObjectInspector)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//}}AFX_VIRTUAL

public:
	virtual ~CObjectInspector();
	int GetParamType(char *ParamTypeName);
protected:
	//{{AFX_MSG(CObjectInspector)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnChangeInplaceControl();
	afx_msg void OnChangeDateTimeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboBox();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRadioSelect();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // AFX_OBJECTINSPECTOR_H__DB3F042A_B838_4CB7_B9AA_82DB7E7C82C6__INCLUDED_
