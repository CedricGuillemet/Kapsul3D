// ObkjectInspector.cpp : implementation file
//
// MFC Object-Inspector Control v1.0
//
// Written by Gunnar Bolle <webmaster@beatmonsters.com>
// Copyright (c) 2001. All Rights Reserved.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
//
// Additional source codes by :
// 
// CMemDC		- Keith Rule
// CColorButton - James White
// CColourPopup - Chris Maunder
//				  Alexander Bischofberger
// 
// History:
// --------
//
//          1.0			30 Jun 2001
//                      First release version. 
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemDC.h"
#include "GfxTools.h"
#include "ColorButton.h"
#include "../resource.h"
#include "ObjectInspector.h"
//#include "../DumpEntPlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectInspector


// For sorting a vector with pointers to objects
template <class T> struct iter_less : public std::binary_function<T,T,bool>
{
  bool operator()(const T x, const T y) const { return *x < *y; }
};

template <class T> struct iter_greater : public std::binary_function<T,T,bool>
{
  bool operator()(const T x, const T y) const { return !(*x < *y); }
};

CObjectInspector::CProperty::~CProperty() 
{ 
	DestroyInplaceControl(); 
	
	delete m_pControlFont; 
	
	// Destroy childs as well
	for (vector<CProperty*>::iterator i = m_Childs.begin(); i != m_Childs.end(); i++)
		delete (*i);

	m_Childs.clear ();
};



bool CObjectInspector::CProperty::GetValueFromControl(short *psValue)
{
	if (psValue && m_ptType == ptShort && m_bEditing)
	{
		CString cValue;
		m_pInplaceControl->GetWindowText(cValue);
		int nValue = atoi(cValue);
		*psValue = (short) nValue;
		return true;
	}
	
	return false;
}

bool CObjectInspector::CProperty::GetValueFromControl(int *pnValue)
{
	if (pnValue && m_ptType == ptInteger && m_bEditing)
	{
		CString cValue;
		m_pInplaceControl->GetWindowText(cValue);
		int nValue = atoi(cValue);
		*pnValue = nValue;
		return true;
	}else
	if (pnValue && m_ptType == ptSliderCtrl && m_bEditing)
	{
		*pnValue = ((CSliderCtrl*)m_pInplaceControl)->GetPos();
		return true;
	}
	
	return false;
}

bool CObjectInspector::CProperty::GetValueFromControl(bool *pbValue)
{
	if (pbValue && m_ptType == ptBool && m_bEditing)
	{
		*pbValue = ((CButton*)m_pInplaceControl)->GetCheck () ? true : false;
		return true;
	}
	
	return false;
}

bool CObjectInspector::CProperty::GetValueFromControl(float *pfValue)
{
	if (pfValue && m_ptType == ptFloat && m_bEditing)
	{
		CString cValue;
		m_pInplaceControl->GetWindowText(cValue);
		*pfValue = (float) atof(cValue);
		return true;
	}
	
	return false;
}

bool CObjectInspector::CProperty::GetValueFromControl(double *pdblValue)
{
	if (pdblValue && m_ptType == ptDouble && m_bEditing)
	{
		CString cValue;
		m_pInplaceControl->GetWindowText(cValue);
		*pdblValue = (double) atof(cValue);
		return true;
	}
	
	return false;
}

bool CObjectInspector::CProperty::GetValueFromControl(COleDateTime *pdtValue)
{
	if (pdtValue && m_ptType == ptDate && m_bEditing)
	{
		COleDateTime dtValue;
		((CDateTimeCtrl*)m_pInplaceControl)->GetTime(*pdtValue);
		return true;
	}

	return false;
}

bool CObjectInspector::CProperty::GetValueFromControl(CString *pszValue)
{
	if (pszValue && (m_ptType == ptMemoEdit || m_ptType == ptStringList || m_ptType == ptFileBroswer || m_ptType == ptMaskedEdit) && m_bEditing)
	{
		CString cValue;
		m_pInplaceControl->GetWindowText(*pszValue);
		return true;
	}
	
	return false;
}

bool CObjectInspector::CProperty::GetValueFromControl(COLORREF *pclValue)
{
	if (pclValue && m_ptType == ptColor && m_bEditing)
	{
		*pclValue = ((CColorButton*)m_pInplaceControl)->GetColor ();
		return true;
	}
	
	return false;
}

CWnd* CObjectInspector::CProperty::GetInplaceControl() 
{ 
	return m_pInplaceControl; 
};

CRect CObjectInspector::CProperty::GetPropertyRect()
{
	return m_rtPropertyRect;
}

CRect CObjectInspector::CProperty::GetValueRect()
{
	return m_rtValueRect;
}

void CObjectInspector::CProperty::SetRectangles(CRect rtProperty, CRect rtValue)
{
	m_rtPropertyRect = rtProperty;
	m_rtValueRect    = rtValue;

	if (m_bEditing && m_pInplaceControl && ::IsWindow (m_pInplaceControl->m_hWnd))
		m_pInplaceControl->MoveWindow (&m_rtValueRect);
	
}

CWnd *CObjectInspector::CProperty::CreateControlFromType()
{
	CWnd *pWndCtrl = NULL;

	switch (m_ptType)
	{
	case ptFloat :
	case ptDouble :
		{ 
			 CEdit *pCtrl = new CEdit;
			 if (!pCtrl->Create(ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD, m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				 AfxThrowMemoryException();
			 else
				pWndCtrl = pCtrl;
			 break;
		}
	case ptShort :
	case ptInteger : 
		{ 
			 CEdit *pCtrl = new CEdit;
			 if (!pCtrl->Create(ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD | ES_NUMBER, m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				 AfxThrowMemoryException();
			 else
				pWndCtrl = pCtrl;
			 break;
		}
	case ptBool : 
		{ 
			 CButton *pCtrl = new CButton;
			 if (!pCtrl->Create("", WS_VISIBLE | WS_CHILD | BS_FLAT | (m_bRadio ? BS_RADIOBUTTON : BS_AUTOCHECKBOX ), m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				 AfxThrowMemoryException();
			 else
				pWndCtrl = pCtrl;
			 break;
		}
	case ptDate : 
		{
			 CDateTimeCtrl *pCtrl = new CDateTimeCtrl;
			 if (!pCtrl->Create(WS_VISIBLE | WS_CHILD | (m_bUseTime ? DTS_TIMEFORMAT : DTS_SHORTDATEFORMAT), m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				 AfxThrowMemoryException();
			 else
				pWndCtrl = pCtrl;
			 break;
		}
	case ptColor :
		{
			CColorButton *pCtrl = new CColorButton;
			if (!pCtrl->Create("", WS_VISIBLE | WS_CHILD, m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				AfxThrowMemoryException();
			else
				pWndCtrl = pCtrl;
			break;
		}
	case ptStringList:
		{
			if (m_pStringList == NULL)
			{
				CEdit *pCtrl = new CEdit;
				if (!pCtrl->Create(WS_VISIBLE | WS_CHILD, m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
					AfxThrowMemoryException();
				else
					pWndCtrl = pCtrl;
			}
			else
			{
				CComboBox *pCtrl = new CComboBox;
				if (!pCtrl->Create (WS_VISIBLE | WS_CHILD | WS_VSCROLL | m_dwComboBoxStyle, RectCopyInflate(m_rtValueRect,0,0,0,100), m_pParentWnd, IDC_INPLACECONTROL))
					AfxThrowMemoryException();
				else
				for (POSITION pos = (*m_pStringList).GetHeadPosition (); pos != NULL; )
				{
					CString cItem = (*m_pStringList).GetNext (pos);
					pCtrl->AddString (cItem);
				}

				pWndCtrl = pCtrl;
			}
			break;
		}
	case ptFileBroswer:
		{
			CFileEditCtrl *pCtrl = new CFileEditCtrl();
			//pCtrl->m_szFolder=*m_pszValue;
			if (!pCtrl->Create(FEC_FILE,0,*m_pszValue,WS_VISIBLE | WS_CHILD, m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				AfxThrowMemoryException();
			else
				pWndCtrl = pCtrl;
			break;
		}
	case ptMaskedEdit:
		{
			COXMaskedEdit * pCtrl = new COXMaskedEdit();
			if (!pCtrl->Create(WS_VISIBLE | WS_CHILD, m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				AfxThrowMemoryException();
			else
				pWndCtrl = pCtrl;
				pCtrl->SetMask(*m_pszValue);
			break;
		}
	case ptMemoEdit:
		{
			CMemoEditCtrl * pCtrl = new CMemoEditCtrl();
			if (!pCtrl->Create(WS_VISIBLE | WS_CHILD, m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				AfxThrowMemoryException();
			else
				pWndCtrl = pCtrl;
			break;
		}
	case ptSliderCtrl:
		{
			 CSliderCtrl *pCtrl = new CSliderCtrl();
			 if (!pCtrl->Create(WS_VISIBLE | WS_CHILD, m_rtValueRect, m_pParentWnd, IDC_INPLACECONTROL))
				 AfxThrowMemoryException();
			 else
				pWndCtrl = pCtrl;
				pCtrl->SetRange((int)m_dblMin,(int)m_dblMax);
				pCtrl->SetPos(*m_pnValue);
			 break;
		}
	}
	
	if (pWndCtrl)
		pWndCtrl->SetFont (m_pControlFont);

	return pWndCtrl;
}

void CObjectInspector::CProperty::Create(CString cName, EPropertyType ptType)
{
	m_bVisible        = true;
	m_bExpanded       = false;
	m_bFocused		  = false;
	m_bEditing		  = false;
	m_bRadio          = false;
	m_pParentWnd	  = NULL;
	m_pParent         = NULL;
	m_pInplaceControl = NULL;
	m_pItemData       = NULL;
	m_ptType		  = ptType;
	m_cName			  = cName;
	m_nImage          = -1;
	m_cFloatFormat    = _T("%-5.1f");
	m_pControlFont    = new CQuickFont("MS Sans Serif", 10, FW_NORMAL, false);
	
}


void CObjectInspector::CProperty::AddProperty(CProperty *pProperty)
{
	pProperty->m_pParentWnd = m_pParentWnd;
	pProperty->m_pParent    = this;
	pProperty->m_nIndex     = m_Childs.size();
	
	m_Childs.insert(m_Childs.end(), pProperty);
}
	
void CObjectInspector::CProperty::SendNotification(int nMsg)
{
	NM_OIVIEW OIMsg;
	if (OIVN_ITEMCHANGED==nMsg)
	{
//		((CEntPlg*)(m_pParentWnd->GetParent()))->OnNotifyProp();
		m_pParentWnd->GetParent()->SendMessage(WM_USER+815,0,0);
		return;
	}

	ASSERT(m_pParentWnd);

	UINT wParam = m_pParentWnd->GetDlgCtrlID();

	OIMsg.hdr.code	   = nMsg;
	OIMsg.hdr.hwndFrom = m_pParentWnd->m_hWnd;
	OIMsg.hdr.idFrom   = m_pParentWnd->GetDlgCtrlID();
	OIMsg.pProperty	   = this;

	::SendMessage(m_pParentWnd->GetParent()->m_hWnd , WM_NOTIFY,  wParam, (LPARAM) &OIMsg );
}


CString CObjectInspector::CProperty::GetValueAsText() 
{ 
	switch (m_ptType)
	{
	case ptShort :
		{
			CString cValue;
			cValue.Format("%d", *m_psValue);
			return cValue;
		}
	
	case ptInteger : 
		{
			CString cValue;
			cValue.Format("%d", *m_pnValue);
			return cValue;
		}
	
	case ptFloat : 
		{
			CString cValue;
			cValue.Format(m_cFloatFormat, *m_pfValue);
			return cValue;
		}

	case ptDouble :
		{
			CString cValue;
			cValue.Format(m_cFloatFormat, *m_pdblValue);
			return cValue;
		}
	
	case ptBool:
		if (*m_pbValue)
			return _T("1");
		else
			return _T("0");
	case ptColor:
		{
			CString cValue;
			cValue.Format("%x", *m_pclValue);
			return cValue;
		}
		
	case ptDate :
		{
			CString cValue;
			cValue.Format("%s", (*m_pdtValue).Format(m_bUseTime ? VAR_TIMEVALUEONLY : VAR_DATEVALUEONLY));
			return cValue;
		}
	case ptStringList:
		{
			return *m_pszValue;
		}
	case ptFileBroswer:
		{
			return *m_pszValue;
		}
	case ptMaskedEdit:
		{
			return *m_pszValue;
		}
	case ptMemoEdit:
		{
			return *m_pszValue;
		}
	case ptSliderCtrl:
		{
			CString cValue;
			cValue.Format("%d", *m_pnValue);
			return cValue;			
		}
	}

	return _T("");
}
	
void CObjectInspector::CProperty::RangeError(int nMin, int nMax )
{
	CString cMin, cMax;
	cMin.Format("%d", nMin);
	cMax.Format("%d", nMax);
	CString prompt;
	AfxFormatString2(prompt, AFX_IDP_PARSE_INT_RANGE, cMin, cMax);
	AfxMessageBox(prompt, MB_ICONEXCLAMATION, AFX_IDP_PARSE_INT_RANGE);
}

void CObjectInspector::CProperty::RangeError(float fMin, float fMax )
{
	CString cMin, cMax;
	cMin.Format("%.*g", FLT_DIG, fMin);
	cMax.Format("%.*g", FLT_DIG, fMax);
	CString prompt;
	AfxFormatString2(prompt, AFX_IDP_PARSE_REAL_RANGE, cMin, cMax);
	AfxMessageBox(prompt, MB_ICONEXCLAMATION, AFX_IDP_PARSE_REAL_RANGE);
}

void CObjectInspector::CProperty::RangeError(double dblMin, double dblMax )
{
	CString cMin, cMax;
	cMin.Format("%.*g", DBL_DIG, dblMin);
	cMax.Format("%.*g", DBL_DIG, dblMax);
	CString prompt;
	AfxFormatString2(prompt, AFX_IDP_PARSE_REAL_RANGE, cMin, cMax);
	AfxMessageBox(prompt, MB_ICONEXCLAMATION, AFX_IDP_PARSE_REAL_RANGE);
}

bool CObjectInspector::CProperty::GetValueInternal()
{
	switch (m_ptType)
	{
		case ptShort:
		{
			CString cValue;
			m_pInplaceControl->GetWindowText(cValue);
			int nValue = atoi(cValue);

			if ((double) nValue < m_dblMin || (double) nValue > m_dblMax)
			{
				RangeError((int)m_dblMin,(int)m_dblMax);
				return false;
			}

			if (nValue != *m_psValue)
			{
				*m_psValue = (short) nValue;
				SendNotification();
			}
			break;
		}

		case ptInteger:
		{
			CString cValue;
			m_pInplaceControl->GetWindowText(cValue);
			int nValue = atoi(cValue);
			if ((double) nValue < m_dblMin || (double) nValue > m_dblMax)
			{
				RangeError((int)m_dblMin,(int)m_dblMax);
				return false;
			}

			if (nValue != *m_pnValue)
			{
				*m_pnValue = nValue;
				SendNotification();
			}
			break;
		}

		case ptFloat:
		{
			CString cValue;
			m_pInplaceControl->GetWindowText(cValue);
			float fValue = (float) atof(cValue);
			if ((double) fValue < m_dblMin )
			{
				if ((double) fValue > m_dblMax)
			{
				RangeError((float)m_dblMin,(float)m_dblMax);
				return false;
			}
			}

			if (fValue != *m_pfValue)
			{
				*m_pfValue = fValue;
				SendNotification();
			}
			break;
		}

		case ptDouble:
		{
			CString cValue;
			m_pInplaceControl->GetWindowText(cValue);
			double fValue = atof(cValue);
			if ((double) fValue < m_dblMin || (double) fValue > m_dblMax)
			{
				RangeError((double)m_dblMin,(double)m_dblMax);
				return false;
			}

			if (fValue != *m_pdblValue)
			{
				*m_pdblValue = fValue;
				SendNotification();
			}
			break;
		}


		case ptBool:
		{
			
			bool bValue =  ((CButton*)m_pInplaceControl)->GetCheck () ? true : false;

			if (m_bRadio && m_nIndex != *m_pnValue)
			{
				*m_pnValue = m_nIndex;
				SendNotification();
			}
			else
			if (bValue != *m_pbValue)
			{
				*m_pbValue = bValue;
				SendNotification();
			}
			break;
		}

		case ptDate:
		{
			COleDateTime dtValue;
			((CDateTimeCtrl*)m_pInplaceControl)->GetTime(dtValue);

			if (dtValue != *m_pdtValue)
			{
				*m_pdtValue = dtValue;
				SendNotification();
			}

			break;
		}
		case ptColor:
		{
			COLORREF color;
			color = ((CColorButton*)m_pInplaceControl)->GetColor ();
			if (color != *m_pclValue)
			{
				*m_pclValue = color;
				SendNotification();
			}
			break;
		}
		case ptStringList:
		{
			CString cValue;
			m_pInplaceControl->GetWindowText(cValue);
			if (cValue != *m_pszValue)
			{
				*m_pszValue = cValue;
				SendNotification();
			}
		}
		case ptFileBroswer:
		{
			CString szTemp;
			((CFileEditCtrl*)m_pInplaceControl)->GetWindowText(szTemp);
			if (szTemp != *m_pszValue)
			{
				*m_pszValue = szTemp;
				SendNotification();
			}
			break;		
		}
		case ptMaskedEdit:
		{
			CString szTemp;
			((COXMaskedEdit*)m_pInplaceControl)->GetWindowText(szTemp);
			if (szTemp != *m_pszValue)
			{
				*m_pszValue = szTemp;
				SendNotification();
			}
			break;		
		}
		case ptMemoEdit:
		{
			CString szTemp;
			((CMemoEditCtrl*)m_pInplaceControl)->GetWindowText(szTemp);
			if (szTemp != *m_pszValue)
			{
				*m_pszValue = szTemp;
				SendNotification();
			}
			break;		
		}
		case ptSliderCtrl:
		{
			int nValue = ((CSliderCtrl*)m_pInplaceControl)->GetPos();
			if ((double) nValue < m_dblMin || (double) nValue > m_dblMax)
			{
				RangeError((int)m_dblMin,(int)m_dblMax);
				return false;
			}

			if (nValue != *m_pnValue)
			{
				*m_pnValue = nValue;
				SendNotification();
			}
			break;		
		}
	}

	return true;
}

void  CObjectInspector::CProperty::SetValueInternal()
{
	CString cValue;

	switch (m_ptType)
	{
	case ptShort :
			cValue.Format("%d",*m_psValue );
			m_pInplaceControl->SetWindowText (cValue);
			break;
		case ptInteger:
			cValue.Format("%d",*m_pnValue );
			m_pInplaceControl->SetWindowText (cValue);
			break;
		case ptFloat:
			cValue.Format(m_cFloatFormat, *m_pfValue );
			m_pInplaceControl->SetWindowText (cValue);
			break;
		case ptDouble:
			cValue.Format(m_cFloatFormat, *m_pdblValue );
			m_pInplaceControl->SetWindowText (cValue);
			break;
		case ptBool:
			((CButton*)m_pInplaceControl)->SetCheck (*m_pbValue);
			break;
		case ptDate:
			((CDateTimeCtrl*)m_pInplaceControl)->SetTime(*m_pdtValue);
			break;
		case ptColor:
			((CColorButton*)m_pInplaceControl)->SetColor(*m_pclValue);
			break;
		case ptStringList:
			if (!m_pStringList)
				m_pInplaceControl->SetWindowText (*m_pszValue);
			else
				((CComboBox*)m_pInplaceControl)->SelectString (-1,*m_pszValue);
			break;
		case ptFileBroswer:
			((CFileEditCtrl*)m_pInplaceControl)->SetWindowText(*m_pszValue);
			break;
		case ptMaskedEdit:
			((CFileEditCtrl*)m_pInplaceControl)->SetWindowText(*m_pszValue);
			break;
		case ptMemoEdit:
			((CMemoEditCtrl*)m_pInplaceControl)->SetWindowText(*m_pszValue);
			break;
		case ptSliderCtrl:
			((CSliderCtrl*)m_pInplaceControl)->SetPos(*m_pnValue);
			break;
	}

	
}

void CObjectInspector::CProperty::BeginEdit ()
{
	m_bEditing = true;
	
	CreateInplaceControl();

	SetValueInternal();

	if (m_pInplaceControl)
		m_pInplaceControl->SetFocus ();
}

bool CObjectInspector::CProperty::EndEdit ()
{
	if (!GetValueInternal())
		return false;

	m_bEditing = false;

	DestroyInplaceControl();

	return true;
}

void CObjectInspector::CProperty::CreateInplaceControl()
{
	m_pInplaceControl = CreateControlFromType();
}

void CObjectInspector::CProperty::DestroyInplaceControl()
{
	if (m_pInplaceControl)
	{
		delete m_pInplaceControl;
		m_pInplaceControl = NULL;
	}
}

CObjectInspector::CObjectInspector()
{

	m_cPropertyHeaderTitle = _T("Property");
	m_cPropertyValueTitle  = _T("Value");
	m_nXSplitterPos        = -1;
	m_nHeaderHeight        = 0;
	m_nFirstVisibleItem    = 0;
	m_nScrollPos           = 0;
	m_nMinPropertyColWidth = 50;
	m_nMinValueColWidth    = 50;
	m_bSplitterMoving      = false;
	m_bScrollbarVisible	   = false;
	m_b3dFocus             = false;
	m_bHotTrack			   = false;
	m_bSorted              = false;
	m_bW2KStyle            = true;
	m_bsStyle			   = bsLowered;
	m_clBackColor          = ::GetSysColor (COLOR_BTNFACE);
	m_clPropertyRowColor   = (COLORREF) 0;
	m_clGridLineColor      = RGB(120,120,120);
	m_clValueRowColor      = RGB(0,0,255);
	m_clFocusLineColor     = RGB(100,100,255);
	m_pEditingProperty     = NULL;
	m_pImageList           = NULL;
	m_pLastEnteredProperty = NULL;
	m_sdSortDirection      = sdUp;

	WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    // Register window class
    if (!(::GetClassInfo(hInst, CLASS_OBJECTINSPECTOR, &wndcls)))
    {
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = CLASS_OBJECTINSPECTOR;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return ;
        }
    }
}

CObjectInspector::~CObjectInspector()
{
	CleanUp();
	
}


BEGIN_MESSAGE_MAP(CObjectInspector, CWnd)
	//{{AFX_MSG_MAP(CObjectInspector)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDBLCLK()
	ON_EN_CHANGE(IDC_INPLACECONTROL, OnChangeInplaceControl)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_INPLACECONTROL, OnChangeDateTimeCtrl)
	ON_CBN_SELCHANGE(IDC_INPLACECONTROL, OnSelchangeComboBox)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_INPLACECONTROL, OnRadioSelect)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CObjectInspector 

BOOL CObjectInspector::Create(const RECT& rect, CWnd* parent, UINT nID, DWORD dwStyle,CString szProp,CString szValue)
{
	BOOL bRet = CWnd::CreateEx(WS_EX_TOOLWINDOW, CLASS_OBJECTINSPECTOR, NULL, dwStyle, rect, parent, nID, 0);

	//SetHeaderTitles(GetLocal()->GetString(299,"Properties"),GetLocal()->GetString(300,"Values"));
	SetHeaderTitles(szProp,szValue);
	return bRet;
}

void CObjectInspector::DrawBorder(CDC *pDC, CRect& rect)
{
	CBrush brush((COLORREF)0);

	switch (m_bsStyle)
	{
		case bsNone    : break;
		case bsSingle  : pDC->FrameRect(&rect, &brush); rect.DeflateRect (1,1,1,1); break;
		case bsLowered : pDC->DrawEdge( &rect, EDGE_SUNKEN, BF_RECT); rect.DeflateRect (2,2,2,2); break;
		case bsRaised  : pDC->DrawEdge( &rect, EDGE_RAISED, BF_RECT); rect.DeflateRect (2,2,2,2); break;
	}
}

void CObjectInspector::DrawSplitter(CDC *pDC)
{
	if (m_nXSplitterPos == -1)
		m_nXSplitterPos = m_rtClientRect.CenterPoint().x;

	m_rtSplitterRect = CRect(m_nXSplitterPos, m_rtClientRect.top, m_nXSplitterPos + 1, m_rtClientRect.bottom );

	{
		CPenSelector grayPen(PS_SOLID,1, RGB(80,80,80), pDC);
	
		pDC->MoveTo(m_rtSplitterRect.left, m_rtSplitterRect.top);
		pDC->LineTo(m_rtSplitterRect.left, m_rtSplitterRect.bottom);
	}

	{
		CPenSelector whitePen(PS_SOLID,1, RGB(255,255,255), pDC);
	
		pDC->MoveTo(m_rtSplitterRect.right, m_rtSplitterRect.top);
		pDC->LineTo(m_rtSplitterRect.right, m_rtSplitterRect.bottom);
	}
}

void CObjectInspector::DrawHeader(CDC *pDC)
{
	m_nHeaderHeight = pDC->GetTextExtent("pP").cy + 6;

	m_rtPropertyHeaderRect = CRect (m_rtClientRect.left , m_rtClientRect.top, m_rtSplitterRect.left + 1 , m_rtClientRect.top + m_nHeaderHeight );
	m_rtValueHeaderRect    = CRect (m_rtSplitterRect.left + 2 , m_rtClientRect.top, m_rtClientRect.right, m_rtClientRect.top + m_nHeaderHeight);
	
	pDC->FillSolidRect (m_rtClientRect.left, m_rtClientRect.top, m_rtClientRect.Width (), m_nHeaderHeight, ::GetSysColor(COLOR_BTNFACE));
	
	if (m_bSorted)
	{
		CBrush brush (::GetSysColor(COLOR_BTNFACE));
		CRect  copyRect (m_rtPropertyHeaderRect);
		copyRect.OffsetRect (CPoint(-4,0));
		copyRect.left = copyRect.right - GetSystemMetrics(SM_CXHSCROLL);
		pDC->DrawFrameControl (copyRect, DFC_SCROLL, (m_sdSortDirection == sdUp ? DFCS_SCROLLUP : DFCS_SCROLLDOWN) | DFCS_MONO );
		pDC->FrameRect (copyRect, &brush);
		copyRect.DeflateRect (1,1,1,1);
		pDC->FrameRect (copyRect, &brush);
		
	}

	CFontSelector headerFont(&CQuickFont("MS Sans Serif", 10, FW_BOLD), pDC);
	
	pDC->Draw3dRect (&m_rtPropertyHeaderRect, RGB(255,255,255), RGB(50,50,50));
	pDC->Draw3dRect (&m_rtValueHeaderRect, RGB(255,255,255), RGB(50,50,50));
	
	m_rtPropertyHeaderRect.DeflateRect (3,0,1,0);
	m_rtValueHeaderRect.DeflateRect (3,0,1,0);

	pDC->DrawText( m_cPropertyHeaderTitle, m_rtPropertyHeaderRect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS );
	pDC->DrawText( m_cPropertyValueTitle, m_rtValueHeaderRect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS );
}
 
void CObjectInspector::DrawItem(CDC*pDC, CProperty *pProperty, int& nY, int& nCellHeight)
{

	CFontSelector cellFont(&CQuickFont("MS Sans Serif", 10, FW_NORMAL, pProperty->m_bFocused && m_bHotTrack), pDC);

	CRect rtPropertyRect(m_rtClientRect.left + 1, nY + 1, m_rtSplitterRect.left - 1, nY + nCellHeight - 1);
	CRect rtValueRect(m_rtSplitterRect.right + 1, nY + 1, m_rtClientRect.right, nY + nCellHeight - 1);

	pProperty->SetRectangles (rtPropertyRect, rtValueRect);

	if (!pProperty->m_bVisible)
	{
		if (pProperty->m_bEditing )
		{
			pProperty->EndEdit ();
			m_pEditingProperty = NULL;
		}

		return;
	}

	m_nExpandedItemsCount++;
	
	if (pProperty->GetInplaceControl () && !pProperty->GetInplaceControl ()->IsWindowVisible ())
		pProperty->GetInplaceControl ()->ShowWindow (SW_SHOW);

	if (pProperty->m_bEditing)
	{
		if (m_b3dFocus)
			pDC->DrawEdge (RectCopyInflate(pProperty->GetPropertyRect(),0,1,0,1), EDGE_SUNKEN, BF_RECT);
		else
			pDC->FillSolidRect (RectCopyInflate(pProperty->GetPropertyRect(),0,-1,0,0), m_clFocusLineColor);
		
	}
	
	int nBaseIndent = 12;

	if (m_pImageList && m_pImageList->GetImageCount () > 0)
	{
		IMAGEINFO imageInfo;
		m_pImageList->GetImageInfo (0, &imageInfo);
		int nImageHeight = CRect(imageInfo.rcImage).Height();
		if (pProperty->m_nImage != -1 && pProperty->m_Childs.size() == 0)
		{
			CPoint ptImage = CPoint(pProperty->GetPropertyRect().left, pProperty->GetPropertyRect().CenterPoint ().y - (nImageHeight / 2));
			m_pImageList->Draw (pDC, pProperty->m_nImage, ptImage,ILD_TRANSPARENT);
		}
		nBaseIndent = CRect(imageInfo.rcImage).Width() + 4;
	}

	if (pProperty->GetType () == ptGroup)
	{
		CFontSelector cellFontBold(&CQuickFont("MS Sans Serif", 10, FW_BOLD, pProperty->m_bFocused && m_bHotTrack), pDC);
	
		if (m_bW2KStyle)
		{
			pDC->FillSolidRect(RectCopyInflate(pProperty->m_rtPropertyRect,0,0,1,1),::GetSysColor(COLOR_INACTIVECAPTION));
			pDC->FillSolidRect(RectCopyInflate(pProperty->m_rtValueRect,0,0,1,1),::GetSysColor(COLOR_INACTIVECAPTION));
			pDC->SetTextColor(RGB(255,255,255));		

		}		
		else
			pDC->SetTextColor (m_clPropertyRowColor);

		pDC->DrawText(pProperty->m_cName, RectCopyDeflate(rtPropertyRect,nBaseIndent + (m_nIndent * 10),0,0,0),DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
	else
	{
		pDC->SetTextColor ((!m_b3dFocus && pProperty->m_bEditing) ? RGB(255,255,255) : m_clPropertyRowColor);
		pDC->DrawText(pProperty->m_cName, RectCopyDeflate(rtPropertyRect,nBaseIndent + (m_nIndent * 10),0,0,0),DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
	pDC->SetTextColor (m_clValueRowColor);

	if (pProperty->GetType() == ptColor)
	{
		CPenSelector(PS_SOLID,1,(COLORREF)0, pDC);
		pDC->Rectangle (RectCopyDeflate(pProperty->GetValueRect (),2,2,2,1));
		pDC->FillSolidRect (RectCopyDeflate(pProperty->GetValueRect (),3,3,3,2), *pProperty->m_pclValue);
	}
	else
	if (pProperty->GetType() == ptBool)
	{
		CRect copyRect (rtValueRect);
		copyRect.left += 2;
		copyRect.right = copyRect.left + GetSystemMetrics(SM_CXMENUCHECK);
		if (pProperty->m_bRadio)
			pDC->DrawFrameControl (copyRect, DFC_BUTTON, DFCS_FLAT | DFCS_BUTTONRADIO | (*pProperty->m_pbValue ? DFCS_CHECKED : 0));
		else
			pDC->DrawFrameControl (copyRect, DFC_BUTTON, DFCS_FLAT | DFCS_BUTTONCHECK | (*pProperty->m_pbValue ? DFCS_CHECKED : 0));

	}
	else
		pDC->DrawText( pProperty->GetValueAsText(), RectCopyDeflate(rtValueRect,2,0,0,0),DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

	if (pProperty->GetType () == ptGroup)
	{
		CPenSelector(PS_SOLID, 1, (COLORREF)0, pDC);

		pProperty->m_rtGroupRect = CRect(( m_nIndent * 10 ) + pProperty->GetPropertyRect ().left + 1 ,
										 pProperty->GetPropertyRect ().CenterPoint ().y - 4,
										 ( m_nIndent * 10 ) + pProperty->GetPropertyRect ().left + 10,
										 pProperty->GetPropertyRect ().CenterPoint ().y + 5);

		
		pDC->Rectangle (pProperty->m_rtGroupRect);

		pDC->MoveTo (pProperty->m_rtGroupRect.left + 1, pProperty->m_rtGroupRect.CenterPoint ().y);
		pDC->LineTo (pProperty->m_rtGroupRect.right - 1, pProperty->m_rtGroupRect.CenterPoint ().y);
	
		if (!pProperty->m_bExpanded)
		{
			pDC->MoveTo (pProperty->m_rtGroupRect.CenterPoint().x, pProperty->m_rtGroupRect.top + 1);
			pDC->LineTo (pProperty->m_rtGroupRect.CenterPoint().x, pProperty->m_rtGroupRect.bottom - 1);
		}

	}

	nY += nCellHeight;

	m_nOverallItemHeight += nCellHeight;

	CPenSelector grayPen(PS_SOLID, 1, m_clGridLineColor, pDC);

	pDC->MoveTo(m_rtClientRect.left, nY);
	pDC->LineTo(m_rtSplitterRect.left - 1, nY);
	pDC->MoveTo(m_rtSplitterRect.right + 1, nY);
	pDC->LineTo(m_rtClientRect.right , nY);
}

void CObjectInspector::DrawChildItems(CDC*pDC,int& nItem, CProperty *pProperty, int& nY, int& nCellHeight)
{
	if (!m_bW2KStyle)
		m_nIndent ++;

	for (vector<CProperty*>::iterator i = pProperty->m_Childs.begin(); i != pProperty->m_Childs.end(); i++)
	{
		if ((*i)->m_pParent && (!(*i)->m_pParent->m_bExpanded || !(*i)->m_pParent->m_bVisible))
			(*i)->m_bVisible = false;
		else
			(*i)->m_bVisible = true;

		DrawItem(pDC, *i, nY, nCellHeight); 
		nItem++;
		if ((*i)->m_Childs.size() != 0 )
			DrawChildItems(pDC, nItem, *i, nY, nCellHeight);
	}

	if (!m_bW2KStyle)
		m_nIndent--;
}

void CObjectInspector::DrawItems(CDC *pDC)
{
	int nCellHeight = pDC->GetTextExtent("pP").cy + 6; 

	m_nCellHeight = nCellHeight;

	int nY = m_rtPropertyHeaderRect.bottom - m_nScrollPos;

	m_nOverallItemHeight  = 0;
	m_nExpandedItemsCount = 0;

	int nItem = 0;
	
	for (vector<CProperty*>::iterator i = m_PropertyList.begin(); i != m_PropertyList.end(); i++, nItem++)
	{
		m_nIndent = 0;
		DrawItem(pDC, *i, nY, nCellHeight);
		if ((*i)->m_Childs.size() != 0)
			DrawChildItems(pDC, nItem, *i, nY, nCellHeight);

	}
	
	if (m_nOverallItemHeight > (m_rtClientRect.Height() - m_nHeaderHeight )&& !m_bScrollbarVisible )
	{
		m_bScrollbarVisible = true;
		Invalidate(TRUE);
		return;
	}

	if (m_nOverallItemHeight < (m_rtClientRect.Height() - m_nHeaderHeight ) && m_bScrollbarVisible)
	{
		m_bScrollbarVisible = false;
		Invalidate(TRUE);
		return;
	}
}


void CObjectInspector::CleanUp()
{
	for (vector<CProperty*>::iterator i = m_PropertyList.begin(); i != m_PropertyList.end(); i++)
		delete (*i);
	
	m_PropertyList.clear ();
}

void CObjectInspector::CalculateScrollRange(CProperty *pProperty)
{
	static int nItemsVisible = 0;

	if (pProperty == NULL)
	{
		nItemsVisible = 0;
		for (vector<CProperty*>::iterator i = m_PropertyList.begin(); i != m_PropertyList.end(); i++)
		{
			if (!((*i)->m_pParent && !(*i)->m_pParent->m_bExpanded))
				nItemsVisible++;
			if ((*i)->m_Childs.size () != 0)
				CalculateScrollRange(*i);
		}
	}
	else
	{
		if (!(pProperty->m_pParent && !pProperty->m_pParent->m_bExpanded))
				nItemsVisible++;
		if (pProperty->m_Childs.size != 0)
			for (vector<CProperty*>::iterator i = pProperty->m_Childs.begin(); i != pProperty->m_Childs.end(); i++)
					CalculateScrollRange(*i);
	}

	m_nScrollRange = nItemsVisible * m_nCellHeight - m_rtClientRect.Height ();
}

void CObjectInspector::DrawScrollBar()
{
	if (m_bScrollbarVisible)
	{

		if (!::IsWindow(m_ScrollBar.m_hWnd))
			m_ScrollBar.Create (SBS_VERT | SBS_TOPALIGN | WS_CHILD, CRect(0,0,0,0), this, IDC_SCROLLBAR);
	

		m_rtClientRect.DeflateRect (0,0, ::GetSystemMetrics (SM_CXVSCROLL),0);

		if (!m_ScrollBar.IsWindowVisible ())
			m_ScrollBar.ShowWindow (SW_SHOW);

		CRect sbRect;
		m_ScrollBar.GetWindowRect (&sbRect);
		CRect sbNewRect (m_rtClientRect.right, m_rtClientRect.top, m_rtClientRect.right + ::GetSystemMetrics (SM_CXVSCROLL), m_rtClientRect.top + m_rtClientRect.Height ());

		if (sbRect != sbNewRect)
			m_ScrollBar.MoveWindow(sbNewRect, TRUE);
	
				
		m_ScrollBar.SetScrollRange (0, m_nScrollRange);
		
	}
	else
		if (::IsWindow(m_ScrollBar.m_hWnd))
			m_ScrollBar.ShowWindow (SW_HIDE);

}

void CObjectInspector::OnPaint() 
{
	CPaintDC dc(this); 

	CMemDC memDC(&dc);
	
	GetClientRect(&m_rtClientRect);

	CBitmap		bmp;
	CDC			saveDC;
	CDC*		pControlDC;

	int			nBmpWidth  = 0;  
	int			nBmpHeight = 0;
	CGdiObject* pOldObject = NULL;
	
	// Check if there's a currently active inplace edit control
	if (m_pEditingProperty && m_pEditingProperty->GetInplaceControl () &&
		m_pEditingProperty->GetInplaceControl ()->IsWindowVisible ())
	{
		// Get a bitmap of the inplace control to prevent flickering
		nBmpWidth  = m_pEditingProperty->GetValueRect ().Width ();
		nBmpHeight = m_pEditingProperty->GetValueRect ().Height();
		pControlDC = m_pEditingProperty->GetInplaceControl ()->GetDC();
		saveDC.CreateCompatibleDC (pControlDC);
		bmp.CreateCompatibleBitmap (pControlDC, nBmpWidth, nBmpHeight);
		pOldObject = saveDC.SelectObject (&bmp);
		saveDC.BitBlt (0,0, nBmpWidth, nBmpHeight, pControlDC, 0, 0, SRCCOPY);
		m_pEditingProperty->GetInplaceControl ()->ReleaseDC(pControlDC);
	}
	
	
	memDC.FillSolidRect (&m_rtClientRect, m_clBackColor);

	memDC.SetBkColor(::GetSysColor (COLOR_BTNFACE));

	memDC.SetBkMode (TRANSPARENT);

	DrawBorder(&memDC, m_rtClientRect);

	CalculateScrollRange();

	DrawScrollBar();

	DrawSplitter(&memDC);

	DrawHeader(&memDC);

	CRgn rgn;
	rgn.CreateRectRgn (m_rtClientRect.left, m_rtPropertyHeaderRect.bottom, m_rtClientRect.right, m_rtClientRect.bottom-1);
	memDC.SelectClipRgn(&rgn);

	DrawItems(&memDC);

	if (m_pEditingProperty && m_pEditingProperty->GetInplaceControl () &&
		m_pEditingProperty->GetInplaceControl ()->IsWindowVisible ())
	{
		memDC.BitBlt (m_pEditingProperty->GetValueRect ().left , m_pEditingProperty->GetValueRect ().top, nBmpWidth, nBmpHeight, &saveDC, 0, 0, SRCCOPY);

		if (pOldObject)
			saveDC.SelectObject (pOldObject);

		m_pEditingProperty->GetInplaceControl ()->Invalidate (TRUE);
	}
}

void CObjectInspector::SetBorderStyle(EBorderStyle bsStyle)
{
	if (m_bsStyle != bsStyle)
	{
		m_bsStyle = bsStyle;
		Invalidate(TRUE);
	}
}

CObjectInspector::CProperty *CObjectInspector::GetPropertyFromPoint(CPoint point, CObjectInspector::CProperty *pRoot)
{
	CProperty *pProperty = NULL;

	if (pRoot == NULL)
	{
		for (vector<CProperty*>::iterator i = m_PropertyList.begin(); i != m_PropertyList.end(); i++)
		{
			if (!(*i)->m_bVisible)
				continue;

			if ((*i)->GetPropertyRect().PtInRect (point) || (*i)->GetValueRect().PtInRect (point))
				return &(**i);

			if ((*i)->m_Childs.size() != 0)
			{
				pProperty = GetPropertyFromPoint(point, (*i));
				if (pProperty)
					return pProperty;
			}
		}
	}
	else
	{
		for (vector<CProperty*>::iterator i = pRoot->m_Childs.begin(); i != pRoot->m_Childs.end(); i++)
		{
			if (!(*i)->m_bVisible)
				continue;
		
			if ((*i)->GetPropertyRect().PtInRect (point) || (*i)->GetValueRect().PtInRect (point))
				return  &(**i);

			if ((*i)->m_Childs.size() != 0)
			{
				pProperty = GetPropertyFromPoint(point, (*i));
				if (pProperty)
					return pProperty;
			}
		}
	}

	return pProperty;
}

void CObjectInspector::AddProperty(CObjectInspector::CProperty* pProperty)
{
	pProperty->m_pParentWnd = this;
	
	m_PropertyList.insert(m_PropertyList.end(), pProperty);
	
	Invalidate(FALSE);
}

void CObjectInspector::OnMouseMove(UINT nFlags, CPoint point) 
{
	static CProperty *pLastFocusedProperty = NULL;

	CRect rtSplitterGripRect = m_rtSplitterRect;

	rtSplitterGripRect.InflateRect (2,0,2,0);

	if (rtSplitterGripRect.PtInRect (point))
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
	else
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	
	if (m_bSplitterMoving && point.x < m_rtClientRect.right && point.x > 0 && point.x > m_nMinPropertyColWidth && (m_rtClientRect.Width() - point.x) > m_nMinValueColWidth )
	{
		m_nXSplitterPos = point.x;
		InvalidateRect(m_rtClientRect,FALSE);
	}

	if (m_bHotTrack)
	{
		CProperty *pProperty = GetPropertyFromPoint(point, NULL);

		if (pProperty)
		{
			if (pProperty->m_bFocused)
				return;
			
			pProperty->m_bFocused = true;
			
			if (pLastFocusedProperty)
				pLastFocusedProperty->m_bFocused = false;
			
			pLastFocusedProperty = pProperty;

			InvalidateRect(m_rtClientRect,FALSE);
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CObjectInspector::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bSplitterMoving = false;
	
	ReleaseCapture();
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CObjectInspector::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	CRect rtSplitterGripRect = m_rtSplitterRect;

	rtSplitterGripRect.InflateRect (2,0,2,0);

	if (m_rtPropertyHeaderRect.PtInRect (point))
	{
		m_bSorted = true;
		
		m_sdSortDirection = (ESortDirection) (((int) m_sdSortDirection + 1 ) & 1);
		
		if (m_sdSortDirection == sdDown)
			std::sort (m_PropertyList.begin(), m_PropertyList.end(), iter_less <CProperty*>());
		else
			std::sort (m_PropertyList.begin(), m_PropertyList.end(), iter_greater <CProperty*>());

		InvalidateRect(m_rtClientRect);
	}
	else
	if (rtSplitterGripRect.PtInRect (point))
	{
		SetCapture();
		m_bSplitterMoving = true;
	}
	else
	{
		CProperty *pProperty = GetPropertyFromPoint (point, NULL);
		
		if (pProperty)
		{
			if (pProperty->GetType () != ptGroup )
			{
				if (pProperty->m_bEditing)
					return;
				
				if (m_pLastEnteredProperty && m_pLastEnteredProperty->m_bEditing)
					if (!m_pLastEnteredProperty->EndEdit())
						return;

				if (pProperty->m_ptType == ptBool && pProperty->m_bRadio)
				{
					for (vector<CProperty*>::iterator i = pProperty->m_pParent->m_Childs.begin(); i!= pProperty->m_pParent->m_Childs.end(); i++)
						if ((*i)->m_bRadio)
							*(*i)->m_pbValue = false;
			
					*pProperty->m_pbValue = true;
				}
					
				pProperty->BeginEdit();

				if (pProperty->m_ptType == ptBool && !pProperty->m_bRadio)
					((CButton*)pProperty->GetInplaceControl ())->SetCheck (!((CButton*)pProperty->GetInplaceControl ())->GetCheck());
				
				m_pEditingProperty = pProperty;
								
				m_pLastEnteredProperty = pProperty;
				
				InvalidateRect(m_rtClientRect,FALSE);
			}
			else
			{
				if (pProperty->m_rtGroupRect.PtInRect(point))
				{						
					pProperty->m_bExpanded = !pProperty->m_bExpanded;
					InvalidateRect(m_rtClientRect, FALSE);
					CalculateScrollRange();
					
				}
			}
		}
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CObjectInspector::OnRadioSelect()
{
	if (m_pEditingProperty && m_pEditingProperty->m_bRadio)
	{		
		CProperty *pParent = m_pEditingProperty->m_pParent;
		if (pParent)
			for (vector<CProperty*>::iterator i = pParent->m_Childs.begin(); i!= pParent->m_Childs.end(); i++)
				if ((*i)->m_bRadio)
					*(*i)->m_pbValue = false;

		if (m_pEditingProperty->GetInplaceControl())
			((CButton*)m_pEditingProperty->GetInplaceControl())->SetCheck (true);
	}
}

void CObjectInspector::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (!m_bScrollbarVisible)
		return;

	if (nSBCode == SB_LINEDOWN && m_nScrollPos < m_nScrollRange) 
		m_nScrollPos ++;

	if (nSBCode == SB_LINEUP && m_nScrollPos > 0) 
		m_nScrollPos --;

	if (nSBCode == SB_BOTTOM)
		m_nScrollPos = m_nScrollRange;

	if (nSBCode == SB_TOP)
		m_nScrollPos = 0;

	if (nSBCode == SB_PAGEDOWN)
	{
		if ((m_nScrollPos + m_nCellHeight) <= m_nScrollRange)
			m_nScrollPos += m_nCellHeight;
		else
			m_nScrollPos = m_nScrollRange;
	}
	
	if (nSBCode == SB_PAGEUP)
	{
		if ((m_nScrollPos - m_nCellHeight) >= 0)
			m_nScrollPos -= m_nCellHeight;
		else
			m_nScrollPos = 0;
	}

	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
		m_nScrollPos = nPos;

	if (m_pEditingProperty)
	{
		m_pEditingProperty->EndEdit ();
		m_pEditingProperty = NULL;
	}


	m_ScrollBar.SetScrollPos (m_nScrollPos);			

	InvalidateRect(m_rtClientRect,FALSE);
}

void CObjectInspector::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CProperty *pProperty = GetPropertyFromPoint (point, NULL);
		
	if (pProperty && pProperty->GetType () == ptGroup)
	{
		pProperty->m_bExpanded = !pProperty->m_bExpanded;
		InvalidateRect(m_rtClientRect, FALSE);
	}
	
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CObjectInspector::SetHeaderTitles(CString cPropertyHeaderTitle, CString cPropertyValueTitle)
{
	m_cPropertyHeaderTitle = cPropertyHeaderTitle;
	m_cPropertyValueTitle  = cPropertyValueTitle;
}

void CObjectInspector::SetStyle(bool bW2K)
{
	m_bW2KStyle = bW2K;
	Invalidate();
}

void CObjectInspector::SetHotTrack(bool bEnabled) 
{ 
	m_bHotTrack = bEnabled; 
	Invalidate(); 
};

void CObjectInspector::Set3dFocus(bool bValue)
{
	m_b3dFocus = bValue;
	Invalidate();
}

void CObjectInspector::SetBackColor(COLORREF clBackColor)
{
	m_clBackColor = clBackColor;
	Invalidate();
}

void CObjectInspector::SetMinPropertyColWidth(int nWidth)
{
	m_nMinPropertyColWidth = nWidth;
	Invalidate();
}

void CObjectInspector::SetMinValueColWidth(int nWidth)
{
	m_nMinValueColWidth = nWidth;
	Invalidate();
}

void CObjectInspector::SetPropertyColTextColor(COLORREF clPropertyRowColor)
{
	m_clPropertyRowColor = clPropertyRowColor;
	Invalidate();
}

void CObjectInspector::SetValueColTextColor(COLORREF clValueRowColor)
{
	m_clValueRowColor = clValueRowColor;
	Invalidate();
}

void CObjectInspector::SetGridLineColor(COLORREF clGridLineColor)
{
	m_clGridLineColor = clGridLineColor;
	Invalidate();
}

void CObjectInspector::SetFocusLineColor(COLORREF clFocusLineColor)
{
	m_clFocusLineColor = clFocusLineColor;
	Invalidate();
}

void CObjectInspector::GeHeaderTitles(CString& cPropertyHeaderTitle, CString& cPropertyValueTitle)
{
	cPropertyHeaderTitle = m_cPropertyHeaderTitle;
	cPropertyValueTitle = m_cPropertyValueTitle;
}

CObjectInspector::EBorderStyle CObjectInspector::GetBorderStyle()
{
	return m_bsStyle;
}

bool CObjectInspector::GetHotTrack()
{
	return m_bHotTrack;
}

bool CObjectInspector::Get3dFocus()
{
	return m_b3dFocus;
}

COLORREF CObjectInspector::GetBackColor()
{
	return m_clBackColor;
}

COLORREF CObjectInspector::GetPropertyColTextColor()
{
	return m_clPropertyRowColor; 
}

COLORREF CObjectInspector::GetValueColTextColor()
{
	return m_clValueRowColor; 
}

COLORREF CObjectInspector::GetGridLineColor()
{
	return m_clGridLineColor;
}

COLORREF CObjectInspector::GetFocusLineColor()
{
	return m_clFocusLineColor;
}

int CObjectInspector::GetMinPropertyColWidth()
{
	return m_nMinPropertyColWidth;
}

int CObjectInspector::GetMinValueColWidth()
{
	return m_nMinValueColWidth;
}
 
void CObjectInspector::OnChangeInplaceControl()
{
	if (m_pEditingProperty)
		m_pEditingProperty->SendNotification (OIVN_ITEMCHANGING);
}

void CObjectInspector::OnChangeDateTimeCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_pEditingProperty)
		m_pEditingProperty->SendNotification (OIVN_ITEMCHANGING);
}

void CObjectInspector::OnSelchangeComboBox()
{
	if (m_pEditingProperty)
		m_pEditingProperty->SendNotification (OIVN_ITEMCHANGING);
}

CObjectInspector::CProperty *CObjectInspector::GetNextProperty(CProperty *pProperty)
{
	if (pProperty->m_pParent)
	{
		vector <CProperty*>::iterator pos = find(pProperty->m_pParent->m_Childs.begin(),
											     pProperty->m_pParent->m_Childs.end(),
											     pProperty);

		if (*pos != pProperty->m_pParent->m_Childs.back())
			return *(++pos);
		else
			return GetNextProperty(pProperty->m_pParent);
	}
	else
	{
		vector <CProperty*>::iterator pos = find(m_PropertyList.begin(),
											     m_PropertyList.end(),
											     pProperty);

		if (*pos != m_PropertyList.back())
			return *(++pos);
		else
			return NULL;
		
	}
}

CObjectInspector::CProperty *CObjectInspector::GetPrevProperty(CProperty *pProperty)
{
	if (pProperty->m_pParent)
	{
		vector <CProperty*>::iterator pos = find(pProperty->m_pParent->m_Childs.begin(),
											     pProperty->m_pParent->m_Childs.end(),
											     pProperty);

		if (*pos != pProperty->m_pParent->m_Childs.front())
			return *(--pos);
		else
			return GetPrevProperty(pProperty->m_pParent);
	}
	else
	{
		vector <CProperty*>::iterator pos = find(m_PropertyList.begin(),
											     m_PropertyList.end(),
											     pProperty);

		if (*pos != m_PropertyList.front())
			return *(--pos);
		else
			return NULL;
	}
}


BOOL CObjectInspector::PreTranslateMessage(MSG* pMsg) 
{
	if  (m_pEditingProperty != NULL && pMsg->message == WM_KEYDOWN && IsCtrlDown()) 
	{
		int nVirtKey = (int) pMsg->wParam;

		CProperty *pProperty;

		if (nVirtKey == VK_DOWN)
		{
			pProperty = GetNextProperty(m_pEditingProperty);
			
			if (pProperty)
			{
				m_pEditingProperty->EndEdit ();
				m_pLastEnteredProperty = m_pEditingProperty = pProperty;
				InvalidateRect(m_rtClientRect, FALSE);
				m_pEditingProperty->BeginEdit ();
				return TRUE;
			}
			else
				m_pEditingProperty = NULL;
			
		}

		if (nVirtKey == VK_UP)
		{
			pProperty = GetPrevProperty(m_pEditingProperty);

			if (pProperty)
			{
				m_pEditingProperty->EndEdit ();
				m_pLastEnteredProperty = m_pEditingProperty = pProperty;
				InvalidateRect(m_rtClientRect, FALSE);
				m_pEditingProperty->BeginEdit ();
				return TRUE;
			}
			else
				m_pEditingProperty = NULL;
	
		}
	}

	if (m_pEditingProperty != NULL && pMsg->wParam == VK_RETURN && pMsg->message == WM_KEYUP) 
	{
		int nVirtKey = (int) pMsg->wParam;

		CProperty *pProperty;

		if (nVirtKey == VK_RETURN)
		{
			pProperty = GetNextProperty(m_pEditingProperty);
			
			if (pProperty)
			{
				m_pEditingProperty->EndEdit ();
				m_pLastEnteredProperty = m_pEditingProperty = pProperty;
				InvalidateRect(m_rtClientRect, FALSE);
				m_pEditingProperty->BeginEdit ();
				return TRUE;
			}
			else
				m_pEditingProperty = NULL;
			
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

// Handles mouse wheel notifications
#if (_MFC_VER >= 0x0421)
BOOL CObjectInspector::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
   int nRowsScrolled = zDelta / 120;

   if (nRowsScrolled > 0)
        for (int i = 0; i < nRowsScrolled; i++)
            PostMessage(WM_VSCROLL, SB_PAGEUP, 0);
    else
        for (int i = 0; i > nRowsScrolled; i--)
            PostMessage(WM_VSCROLL, SB_PAGEDOWN, 0);

    return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
#endif // (_MFC_VER >= 0x0421)

HBRUSH CObjectInspector::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (m_pEditingProperty && m_pEditingProperty->GetType () == ptBool)
	{
		m_CtrlBrush.Detach ();
		m_CtrlBrush.CreateSolidBrush (m_clBackColor);
		return m_CtrlBrush;
	}
	else
		return CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
}



int CObjectInspector::GetParamType(char *ParamTypeName)
{
	if (strcmp(ParamTypeName,"string")==0)		return 0;
	if (strcmp(ParamTypeName,"integer")==0)		return 1;
	if (strcmp(ParamTypeName,"color")==0)		return 2;
	if (strcmp(ParamTypeName,"float")==0)		return 3;
	if (strcmp(ParamTypeName,"combo")==0)		return 4;
	if (strcmp(ParamTypeName,"masked")==0)		return 5;
	if (strcmp(ParamTypeName,"slider")==0)		return 6;
	if (strcmp(ParamTypeName,"memo")==0)		return 7;
	if (strcmp(ParamTypeName,"fbrowser")==0)	return 8;
	if (strcmp(ParamTypeName,"bool")==0)	return 9;
	return -1;
}