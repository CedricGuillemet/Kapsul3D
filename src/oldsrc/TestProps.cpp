// TestProps.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TestProps.h"
#include "EntityType.h"
//#include "enti.h"
#include "FPSPropertyList.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestProps dialog


CTestProps::CTestProps(CWnd* pParent /*=NULL*/)
	: CDialog(CTestProps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestProps)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestProps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestProps)
	DDX_Control(pDX, IDC_ENTLISTE, m_EntList);
	DDX_Control(pDX, IDC_PROPS, m_PropCont);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestProps, CDialog)
	//{{AFX_MSG_MAP(CTestProps)
	ON_CBN_SELCHANGE(IDC_ENTLISTE, OnSelchangeEntliste)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestProps message handlers

BOOL CTestProps::OnInitDialog() 
{
	CDialog::OnInitDialog();
	


    for (CEntityType *daEnt=GetFirstEntType();daEnt!=NULL;daEnt=daEnt->Next)
        m_EntList.AddString(daEnt->Name);

    m_EntList.SetCurSel(0);
    CurEnt=GetFirstEntType();
    OnSelchangeEntliste();






/*
	m_nPropList.AddItem("Name", FPSPROPERTYITEMTYPE_TEXT);

	ItemInfo.strName = "Type";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_COMBOBOX;
	ItemInfo.bAllowComboEdit = TRUE;
	ItemInfo.ComboBoxList.AddTail("Type 1");
	ItemInfo.ComboBoxList.AddTail("Type 2");
	ItemInfo.ComboBoxList.AddTail("Type 3");
	ItemInfo.ComboBoxList.AddTail("Custom");
	m_nPropList.AddItem(&ItemInfo);

	ItemInfo.strName = "Visible";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_BOOL;
	ItemInfo.bBoolValue = TRUE;
	m_nPropList.AddItem(&ItemInfo);

	ItemInfo.strName = "Fore Color";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_COLOR;
	ItemInfo.ColorValue = RGB(0, 0, 0);
	m_nPropList.AddItem(&ItemInfo);
	
	ItemInfo.strName = "Back Color";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_COLOR;
	ItemInfo.ColorValue = RGB(255, 255, 255);
	m_nPropList.AddItem(&ItemInfo);

	ItemInfo.strName = "Font";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_FONT;
	m_nPropList.AddItem(&ItemInfo);

	ItemInfo.strName = "File Name";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_FILE;
	ItemInfo.bFileOpenDialog = TRUE;
	ItemInfo.strFileFilter = "Access Files (*.MDB)|*.mdb|All Files (*.*)|*.*|";
	m_nPropList.AddItem(&ItemInfo);
*/

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestProps::OnSelchangeEntliste() 
{
    CString dalib;
    PROPERTYITEMSETUP ItemInfo;
    char temp[512];
    int tmpav;
    int i;


    m_EntList.GetLBText(m_EntList.GetCurSel(),dalib);
    CurEnt=GetByName(dalib.GetBuffer(1));	

    m_nPropList.RemoveAllItems();

    m_nPropList.DestroyWindow();

    CRect ClientRect;
	m_PropCont.GetClientRect(ClientRect);
	m_nPropList.Create(WS_CHILD | WS_VISIBLE ,ClientRect,&m_PropCont,1001);
	m_nPropList.ShowWindow(TRUE);

    for (CEntityProp *daProp=CurEnt->FirstProp;daProp!=NULL;daProp=daProp->Next)
    {
        switch (daProp->Type)
        {
        case 1:
            m_nPropList.AddItem(daProp->Name, FPSPROPERTYITEMTYPE_TEXT);
            break;
        case 2:
	        ItemInfo.strName= daProp->Name;
	        ItemInfo.dwType = FPSPROPERTYITEMTYPE_COMBOBOX;
	        ItemInfo.bAllowComboEdit = FALSE;

            tmpav=0;

            for (i=0;i<daProp->SizeVals;i++)
            {
                if (daProp->Vals[i]=='|')
                {
        	        ItemInfo.ComboBoxList.AddTail(temp);
                    tmpav=0;
                }
                else
                {
                    temp[tmpav]=daProp->Vals[i];
                    temp[++tmpav]=0;
                }
            }

	        m_nPropList.AddItem(&ItemInfo);
            break;
        case 3:
	        ItemInfo.strName = daProp->Name;
	        ItemInfo.dwType = FPSPROPERTYITEMTYPE_BOOL;
	        ItemInfo.bBoolValue = TRUE;
	        m_nPropList.AddItem(&ItemInfo);
            break;
        case 4:
	        ItemInfo.strName = daProp->Name;
	        ItemInfo.dwType = FPSPROPERTYITEMTYPE_FILE;
	        ItemInfo.bFileOpenDialog = TRUE;
	        ItemInfo.strFileFilter = daProp->Vals;
	        m_nPropList.AddItem(&ItemInfo);
            break;
        case 5:
	        ItemInfo.strName = daProp->Name;
	        ItemInfo.dwType = FPSPROPERTYITEMTYPE_COLOR;
	        ItemInfo.ColorValue = RGB(0, 0, 0);
	        m_nPropList.AddItem(&ItemInfo);
            break;
        }
/*
            switch (CurProp->Type)
            {
            case 1:
                m_TypeEdit.SetCheck(1);
                m_Vals.EnableWindow(FALSE);
                m_Vals.SetWindowText("");
                break;
            case 2:
                m_TypeCombo.SetCheck(1);
                m_Vals.EnableWindow(TRUE);
                break;
            case 3:
                m_TypeTrueFalse.SetCheck(1);
                m_Vals.EnableWindow(FALSE);
                m_Vals.SetWindowText("");
                break;
            case 4:
                m_TypeFile.SetCheck(1);
                m_Vals.EnableWindow(TRUE);
                break;
            case 5:
                m_TypeColorPicker.SetCheck(1);
                m_Vals.EnableWindow(FALSE);
                m_Vals.SetWindowText("");
                break;
            }
            */
    }
}

void CTestProps::OnDestroy() 
{
	CDialog::OnDestroy();
	
    CString tmp;
    m_nPropList.GetItemValue("prop3", tmp);

	
}
