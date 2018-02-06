// FPSPropertyListItem.cpp: implementation of the CFPSPropertyListItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FPSPropertyListItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
CFPSPropertyListItem::CFPSPropertyListItem()
{
	m_nTextColor = RGB(0, 0, 0);
	m_nBackColor = GetSysColor(COLOR_BTNFACE);//RGB(192,192,192);
	m_pTempFont = NULL;
	m_bAutoDelete = TRUE;
	m_bIsVisible = FALSE;
	m_strTextValue = "";
	m_bIsButtonCreated = FALSE;
	m_bIsCreated = FALSE;
	m_pItemEditWindow = NULL;

	m_nDrawFont.lfHeight = 80;
	m_nDrawFont.lfWidth = 0;
	m_nDrawFont.lfEscapement = 0;
	m_nDrawFont.lfOrientation = 0;
	m_nDrawFont.lfWeight = 400;
	m_nDrawFont.lfItalic = FALSE;
	m_nDrawFont.lfUnderline = FALSE;
	m_nDrawFont.lfStrikeOut = FALSE;
	m_nDrawFont.lfCharSet = ANSI_CHARSET;
	m_nDrawFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_nDrawFont.lfClipPrecision = OUT_DEFAULT_PRECIS;
	m_nDrawFont.lfQuality = PROOF_QUALITY;
	m_nDrawFont.lfPitchAndFamily = DEFAULT_PITCH;
	strcpy(m_nDrawFont.lfFaceName, "Arial");
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
CFPSPropertyListItem::~CFPSPropertyListItem()
{
	HandleWindows();
	if (m_pTempFont)
		delete m_pTempFont;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::SetItemRect(CRect & rect)
{
	m_nItemRect.CopyRect(rect);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyListItem::DrawItem(CDC * pDC)
{
	CFont*	pNewFont = new CFont;
	CFont*	pOldFont;

	// First, lets get the text name
	CString Text = m_strName;
	//Text += "....................................................................";

	// Second, lets seup our font and load it into the DC
	pNewFont->CreatePointFontIndirect(&m_nDrawFont, pDC);
	pOldFont = pDC->SelectObject(pNewFont);

	// Third, lets set the colors
	pDC->SetTextColor(m_nTextColor);
	pDC->SetBkColor(m_nBackColor);

	// Fourth, lets draw the name text
	CRect TextRect;
	TextRect.SetRect(m_nItemRect.TopLeft().x + 2,
					m_nItemRect.TopLeft().y + 1,
					(int)((m_nItemRect.TopLeft().x + m_nItemRect.BottomRight().x) * .35),
					m_nItemRect.BottomRight().y);
	pDC->ExtTextOut(TextRect.TopLeft().x, TextRect.TopLeft().y+1, ETO_CLIPPED, TextRect, Text, NULL);


	// Fifth, lets draw the edit rectangle
    CRect EditRect;

    if (!DoesItemHaveButton())
    {

	
	EditRect.SetRect((int)((m_nItemRect.TopLeft().x + m_nItemRect.BottomRight().x) * .35),
					m_nItemRect.TopLeft().y + 1,
					m_nItemRect.BottomRight().x ,
					m_nItemRect.BottomRight().y);
	m_nEditRect = EditRect;
	pDC->FillSolidRect(EditRect, RGB(255, 255, 255));
	DrawItemText(pDC);
    }
	// Sixth, lets draw/redraw the button
    else
	{
	    EditRect.SetRect((int)((m_nItemRect.TopLeft().x + m_nItemRect.BottomRight().x) * .35),
					    m_nItemRect.TopLeft().y + 1,
					    m_nItemRect.BottomRight().x - 20,
					    m_nItemRect.BottomRight().y);
	    m_nEditRect = EditRect;
	    pDC->FillSolidRect(EditRect, RGB(255, 255, 255));
	    DrawItemText(pDC);

		CFont* pButtonFont = new CFont;
		CFont* pOldButtonFont;
		pButtonFont->CreatePointFont(70, "Arial");
		pOldButtonFont = pDC->SelectObject(pButtonFont);
		CRect ButtonRect;
		ButtonRect.SetRect(m_nItemRect.BottomRight().x - 16,
						m_nItemRect.TopLeft().y + 1,
						m_nItemRect.BottomRight().x ,
						m_nItemRect.BottomRight().y);
		pDC->Draw3dRect(ButtonRect, RGB(255, 255, 255), RGB(0, 0, 0));

		m_nButtonRect = ButtonRect;
		pDC->SetTextColor(m_nTextColor);
		pDC->SetBkColor(m_nBackColor);
		pDC->TextOut(m_nItemRect.BottomRight().x - 14,
						m_nItemRect.TopLeft().y + 2,
						CString("..."));

		pDC->SelectObject(pOldButtonFont);
		delete pButtonFont;
	}


	pDC->SelectObject(pOldFont);
	delete pNewFont;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyListItem::DoesItemHaveButton()
{
	switch (m_dwItemType)
	{
	case FPSPROPERTYITEMTYPE_FONT:
		{
			return TRUE;
			break;
		}
	case FPSPROPERTYITEMTYPE_COLOR:
		{
			return TRUE;
			break;
		}
	case FPSPROPERTYITEMTYPE_FILE:
		{
			return TRUE;
			break;
		}
	default:
		{
			return FALSE;
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DrawItemText(CDC * pDC)
{
	switch (m_dwItemType)
	{
	case FPSPROPERTYITEMTYPE_TEXT:
		{
			DrawText(pDC, m_strTextValue);
			break;
		}
	case FPSPROPERTYITEMTYPE_INTEGER:
		{
			char buffer[20];
			_itoa(m_iIntegerValue, buffer, 10);
			DrawText(pDC, buffer);
			break;
		}
	case FPSPROPERTYITEMTYPE_LONG:
		{
			char buffer[20];
			_itoa(m_lLongValue, buffer, 10);
			DrawText (pDC, buffer);
			break;
		}
	case FPSPROPERTYITEMTYPE_FONT:
		{
			DrawText(pDC, m_nFontValue.lfFaceName);
			break;
		}
	case FPSPROPERTYITEMTYPE_COLOR:
		{
			DrawColor(pDC);
			break;
		}
	case FPSPROPERTYITEMTYPE_FILE:
		{
			DrawText(pDC, m_strTextValue);
			break;
		}
	case FPSPROPERTYITEMTYPE_COMBOBOX:
		{
			DrawText(pDC, m_strTextValue);
			break;
		}
	case FPSPROPERTYITEMTYPE_BOOL:
		{
			if (m_bBoolValue)
			{
				DrawText(pDC, "Yes");
			}
			else
			{
				DrawText(pDC, "No");
			}
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
BOOL CFPSPropertyListItem::OnClick(CPoint pt)
{
	HandleWindows();

	if (!m_bIsVisible)
		return FALSE;

	if (m_nEditRect.PtInRect(pt))
	{
		switch (m_dwItemType)
		{
		case FPSPROPERTYITEMTYPE_BOOL:
			{
				m_bBoolValue = !m_bBoolValue;
				RedrawItem();
				break;
			}
		case FPSPROPERTYITEMTYPE_TEXT:
			{
				DisplayEditBox(m_strTextValue);
				break;
			}
		case FPSPROPERTYITEMTYPE_LONG:
			{
				char buffer[20];
				_ltoa(m_lLongValue, buffer, 10);
				DisplayEditBox(buffer);
				break;
			}
		case FPSPROPERTYITEMTYPE_INTEGER:
			{
				char buffer[20];
				_itoa(m_iIntegerValue, buffer, 10);
				DisplayEditBox(buffer);
				break;
			}
		case FPSPROPERTYITEMTYPE_FILE:
			{
				DisplayEditBox(m_strTextValue);
				break;
			}
		case FPSPROPERTYITEMTYPE_COMBOBOX:
			{
				DisplayComboBox(m_strTextValue);
				break;
			}
		default:
			{
				break;
			}
		}
		return TRUE;
	}
	else if ((m_nButtonRect.PtInRect(pt)) && (DoesItemHaveButton()))
	{
		DrawSunkenButton();
		switch (m_dwItemType)
		{
		case FPSPROPERTYITEMTYPE_FONT:
			{
				DisplayFontDialog();
				break;
			}
		case FPSPROPERTYITEMTYPE_COLOR:
			{
				DisplayColorDialog();
				break;
			}
		case FPSPROPERTYITEMTYPE_FILE:
			{
				DisplayFileDialog();
				break;
			}
		}
		RedrawItem();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::Setup(PROPERTYITEMSETUP * pSetupInfo)
{
	m_strName = pSetupInfo->strName;
	m_dwItemType = pSetupInfo->dwType;
	m_dwItemData = pSetupInfo->dwData;
	m_bBoolValue = pSetupInfo->bBoolValue;
	m_nColorValue = pSetupInfo->ColorValue;
	m_iIntegerValue = pSetupInfo->iIntegerValue;
	m_lLongValue = pSetupInfo->lLongValue;
	m_strFileFilter = pSetupInfo->strFileFilter;
	m_bFileOpenDialog = pSetupInfo->bFileOpenDialog;
	m_strTextValue = pSetupInfo->strTextValue;
	m_nComboItemList.AddTail(&(pSetupInfo->ComboBoxList));
	m_bAllowTextEdit = pSetupInfo->bAllowComboEdit;
	m_nFontValue = pSetupInfo->FontValue;
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DisplayFontDialog()
{
	CFontDialog dlg (&m_nFontValue);

	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&m_nFontValue);
		m_pParent->PostMessage(FPS_PROPLIST_ITEM_CHANGED, m_dwID, 0);
	}

}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DisplayColorDialog()
{
	CColorDialog dlg (m_nColorValue);

	if (dlg.DoModal() == IDOK)
	{
		m_nColorValue = dlg.GetColor();
		m_pParent->PostMessage(FPS_PROPLIST_ITEM_CHANGED, m_dwID, 0);
	}

}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DisplayFileDialog()
{
	CFileDialog dlg (m_bFileOpenDialog, 
					NULL, 
					m_strTextValue,
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					m_strFileFilter);

	if (dlg.DoModal() == IDOK)
	{
		m_strTextValue = dlg.GetPathName();
		m_pParent->PostMessage(FPS_PROPLIST_ITEM_CHANGED, m_dwID, 0);
	}
					

}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::RedrawItem()
{
	CClientDC dc (m_pParent);

	DrawItem(&dc);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DrawText(CDC * pDC, CString Text)
{
	pDC->ExtTextOut(m_nEditRect.TopLeft().x,
					m_nEditRect.TopLeft().y,
					ETO_CLIPPED,
					m_nEditRect, Text,
					NULL);

}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DrawColor(CDC * pDC)
{
	pDC->FillSolidRect(m_nEditRect,
						m_nColorValue);

}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::HandleWindows()
{
	if (m_pItemEditWindow)
	{
		if (IsWindow(m_pItemEditWindow->m_hWnd))
		{
			switch (m_dwItemType)
			{
			case FPSPROPERTYITEMTYPE_TEXT:
				{
					m_pItemEditWindow->GetWindowText(m_strTextValue);
					break;
				}
			case FPSPROPERTYITEMTYPE_LONG:
				{
					CString Value;
					m_pItemEditWindow->GetWindowText(Value);
					m_lLongValue = atol(Value);
					break;
				}
			case FPSPROPERTYITEMTYPE_INTEGER:
				{
					CString Value;
					m_pItemEditWindow->GetWindowText(Value);
					m_iIntegerValue = atoi(Value);
					break;
				}
			case FPSPROPERTYITEMTYPE_COMBOBOX:
				{
					m_pItemEditWindow->GetWindowText(m_strTextValue);
					break;
				}
			case FPSPROPERTYITEMTYPE_FILE:
				{
					m_pItemEditWindow->GetWindowText(m_strTextValue);
					break;
				}
			}
		}
		delete m_pItemEditWindow;
		m_pItemEditWindow = NULL;

		if (m_pTempFont)
		{
			delete m_pTempFont;
			m_pTempFont = NULL;
		}
		m_pParent->PostMessage(FPS_PROPLIST_ITEM_CHANGED, m_dwID, 0);
	}
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DisplayEditBox(CString Value)
{
	CClientDC dc(m_pParent);
	if (m_pTempFont)
		delete m_pTempFont;
	m_pTempFont = new CFont;
	m_pTempFont->CreatePointFontIndirect(&m_nDrawFont, &dc);

	HandleWindows();

	m_pItemEditWindow = new CEdit;

	((CEdit*)m_pItemEditWindow)->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
								m_nEditRect,
								m_pParent,
								1001);

	m_pItemEditWindow->SetFont(m_pTempFont);
	m_pItemEditWindow->SetWindowText(Value);
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DisplayComboBox(CString Value)
{
	CClientDC dc(m_pParent);
	if (m_pTempFont)
		delete m_pTempFont;
	m_pTempFont = new CFont;
	m_pTempFont->CreatePointFontIndirect(&m_nDrawFont, &dc);

	HandleWindows();

	m_pItemEditWindow = new CComboBox;
	CRect ComboRect;
	ComboRect.SetRect(m_nEditRect.TopLeft().x,
						m_nEditRect.TopLeft().y,
						m_nEditRect.BottomRight().x,
						m_nEditRect.BottomRight().y + 150);

    /*
	if (m_bAllowTextEdit)
	{
		((CComboBox*)m_pItemEditWindow)->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
												ComboRect,
												m_pParent,
												1001);
	}
	else
    */
	{
		((CComboBox*)m_pItemEditWindow)->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
												ComboRect,
												m_pParent,
												1001);
	}
	m_pItemEditWindow->SetFont(m_pTempFont);
	m_pItemEditWindow->SetWindowText(Value);

	POSITION CurrentPos;
	CString  CurrentString;
	int      CurSel;
	CurrentPos = m_nComboItemList.GetHeadPosition();
	while (CurrentPos != NULL)
	{
		CurrentString = m_nComboItemList.GetNext(CurrentPos);
		if (CurrentString == Value)
		{
			CurSel = ((CComboBox*)m_pItemEditWindow)->AddString(CurrentString);
		}
		else
		{
			((CComboBox*)m_pItemEditWindow)->AddString(CurrentString);
		}
	}

	if (!m_bAllowTextEdit)
	{
		((CComboBox*)m_pItemEditWindow)->SetCurSel(CurSel);
	}
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::DrawSunkenButton()
{
	CClientDC dc(m_pParent);

	dc.Draw3dRect(m_nButtonRect, RGB(0, 0, 0), RGB(255, 255, 255));
}

/////////////////////////////////////////////////////////////////////
//					APPLICATION FUCNTION
/////////////////////////////////////////////////////////////////////
void CFPSPropertyListItem::GetSetup(PROPERTYITEMSETUP * pSetupInfo)
{
	pSetupInfo->strName = m_strName;
	pSetupInfo->dwType = m_dwItemType;
	pSetupInfo->dwData = m_dwItemData;
	pSetupInfo->bBoolValue = m_bBoolValue;
	pSetupInfo->ColorValue = m_nColorValue;
	pSetupInfo->iIntegerValue = m_iIntegerValue;
	pSetupInfo->lLongValue = m_lLongValue;
	pSetupInfo->strTextValue = m_strTextValue;
	pSetupInfo->bAllowComboEdit = m_bAllowTextEdit;
	pSetupInfo->FontValue = m_nFontValue;
	pSetupInfo->strFileFilter = m_strFileFilter;
	pSetupInfo->bFileOpenDialog = m_bFileOpenDialog;
}

