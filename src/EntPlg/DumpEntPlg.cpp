// DumpInfos.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "DumpEntPlg.h"
//#include "CKEntityManager.h"
#include "Kapsul3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKEntity *CurrentEntity;

inline DWORD Rgb2Bgr(DWORD &val)
{
	return (((val&0xff)<<16)+(val&0xff00)+((val&0xff0000)>>16));
}


/////////////////////////////////////////////////////////////////////////////
// CEntPlg dialog

vector<CKEntityType*> *m_EntsType;
//vector<CEntityType*> *GetEntsType(void);
CKEntityType *m_ObjectProps;
CKEntityType *m_SkeletonProps;
CKEntityType *m_PatchProps;
CKEntityType *m_ShapeProps;
CKEntityType *m_CameraProps;

CEntPlg::CEntPlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntPlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntPlg)

	//}}AFX_DATA_INIT

	m_EntsType=GetEntsType();
	m_ObjectProps=GetObjectProps();
	m_SkeletonProps=GetSkeletonProps();
	m_ShapeProps=GetShapeProps();
	m_PatchProps=GetPatchProps();
	m_CameraProps=GetCameraProps();
}


void CEntPlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntPlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEntPlg, CDialog)
	//{{AFX_MSG_MAP(CEntPlg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_MESSAGE((WM_USER+815),OnWmUpdateEntity)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntPlg message handlers

void CEntPlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

LRESULT CEntPlg::OnWmUpdateEntity(WPARAM wParam, LPARAM lParam) 
{
	OnNotifyProp();
	return 0;
}

BOOL CEntPlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Oi.Create(CRect(0,25,165,600),this,8858,WS_CHILD|WS_VISIBLE);

	




	ResetAllValues();

	//m_Oi.Create(CRect(10,10,100,200),this,25147,WS_CHILD|WS_VISIBLE);

	//	CObjectInspector::CProperty *pProp;

	// Prepare control's appearance
	m_szBorderStyle		   = "bsLowered";
	m_bHotTrack			   = false;
	m_b3dFocus			   = false;
	m_szValueHeader		   = _T("Value");
	m_szPropertyHeader	   = _T("Property");
	m_clBackColor		   = ::GetSysColor(COLOR_BTNFACE);
	m_clVTColor			   = RGB(200,200,200);
	m_clPTColor			   = (COLORREF)0;
	m_clGridLineColor	   = RGB(80,80,80);
	m_nMinPropertyColWidth = 50;
	m_nMinValueColWidth    = 50;
	m_clFocusLineColor     = RGB(200,200,200);
	m_nStyle			   = 1;


	

	UpdatePropList((*m_EntsType)[0]);
	//m_EntsTypes.SetCurSel(0);
	//m_EntsTypes.SetDroppedWidth(300);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEntPlg::OnOK( )
{

}

void CEntPlg::OnCancel( )
{

}

void CEntPlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (IsWindow(m_Oi.m_hWnd))
	{
		m_Oi.SetWindowPos(this,0,0,cx,cy,SWP_NOZORDER);
	}
}


void CEntPlg::UpdatePropList(CKEntityType *daTyp)
{
	CObjectInspector::CProperty *pProp;

	//m_Oi.SetRedraw(FALSE);

	m_Oi.CleanUp();
	//ResetAllValues();

	m_Oi.m_PropertyList.clear();
	int szAv=0,clAv=0,iAv=0,fAv=0,cbAv=0,iOther=0,blAv=0;

	// Predefined properties
	if (daTyp->Name=="Mesh")
	{
		m_Oi.AddProperty (pProp = new CObjectInspector::CProperty(GetLocal()->GetString(311,"Defaults")));
		pProp->Expand ();
		// name
		m_szProp[szAv]=CurrentMesh->Name;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(301,"Name"), &m_szProp[szAv++]));
		// mesh color
		m_clProp[clAv]=RGB(CurrentMesh->Color.bRed,CurrentMesh->Color.bGreen,CurrentMesh->Color.bBlue);
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(302,"Color"), &m_clProp[clAv++]));
		// nb faces
		m_iProp[iAv]=CurrentMesh->nb2poly;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(303,"Polygons"), &m_iProp[iAv++]));
		// nb Vertex
		m_iProp[iAv]=CurrentMesh->nb2vert;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(304,"Vertex"), &m_iProp[iAv++]));
		// Auto UV
		m_blProp[blAv]=CurrentMesh->GetAutoTexRecalc();
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(305,"Auto UV"), &m_blProp[blAv++]));
		// Prefab Name
		m_szProp[szAv]=CurrentMesh->PrefabName;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(306,"Prefab name"), &m_szProp[szAv++]));

	}
	else
	if (daTyp->Name=="Shape")
	{
		m_Oi.AddProperty (pProp = new CObjectInspector::CProperty(GetLocal()->GetString(311,"Defaults")));
		pProp->Expand ();
		// name
		m_szProp[szAv]=CurrentShape->Name;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(301,"Name"), &m_szProp[szAv++]));
		// color
		m_clProp[clAv]=RGB(CurrentShape->Color.bRed,CurrentShape->Color.bGreen,CurrentShape->Color.bBlue);
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(302,"Color"), &m_clProp[clAv++]));
		// Draw Spline
		m_blProp[blAv]=CurrentShape->DrawSpline;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(307,"Draw spline"), &m_blProp[blAv++]));


	}
	else
	if (daTyp->Name=="Skeleton")
	{
		m_Oi.AddProperty (pProp = new CObjectInspector::CProperty(GetLocal()->GetString(311,"Defaults")));
		pProp->Expand ();
		// name
		m_szProp[szAv]=CurrentSkeletton->Name;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(301,"Name"), &m_szProp[szAv++]));
		// color
		m_clProp[clAv]=RGB(CurrentSkeletton->Color.bRed,CurrentSkeletton->Color.bGreen,CurrentSkeletton->Color.bBlue);
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(302,"Color"), &m_clProp[clAv++]));

	}
	else
	if (daTyp->Name=="Patch")
	{
		m_Oi.AddProperty (pProp = new CObjectInspector::CProperty(GetLocal()->GetString(311,"Defaults")));
		pProp->Expand ();
		// name
		m_szProp[szAv]=CurrentPatch->Name;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(301,"Name"), &m_szProp[szAv++]));
		// color
		m_clProp[clAv]=RGB(CurrentPatch->Color.bRed,CurrentPatch->Color.bGreen,CurrentPatch->Color.bBlue);
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(302,"Color"), &m_clProp[clAv++]));

	}
	else
	if (daTyp->Name=="Camera")
	{
		m_Oi.AddProperty (pProp = new CObjectInspector::CProperty(GetLocal()->GetString(311,"Defaults")));
		pProp->Expand ();
		// name
		m_szProp[szAv]=CurrentCamera->Name;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(301,"Name"), &m_szProp[szAv++]));
		// color
		m_clProp[clAv]=RGB(CurrentCamera->Color.bRed,CurrentCamera->Color.bGreen,CurrentCamera->Color.bBlue);
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(302,"Color"), &m_clProp[clAv++]));
		// Fov
		m_iProp[iAv]=CurrentCamera->Fov;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(308,"FOV"), &m_iProp[iAv++]));
		// Reso X
		m_iProp[iAv]=CurrentCamera->ResoX;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(309,"Reso X"), &m_iProp[iAv++]));
		// Reso Y
		m_iProp[iAv]=CurrentCamera->ResoY;
		pProp->AddProperty (new CObjectInspector::CProperty(GetLocal()->GetString(310,"Reso Y"), &m_iProp[iAv++]));


	}
	// User defined properties

	for (vector<CKEntityGroup*>::iterator i = daTyp->m_Groups.begin(); i != daTyp->m_Groups.end(); i++)
	{
		m_Oi.AddProperty (pProp = new CObjectInspector::CProperty((*i)->Name));
		pProp->Expand ();

		for (vector<CKEntityParam*>::iterator j = (*i)->m_Params.begin(); j != (*i)->m_Params.end(); j++)
		{
			switch((*j)->Type)
			{
			case 0:
				m_szProp[szAv]=(*j)->Default;
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_szProp[szAv++]));
				break;
			case 1:
				sscanf((*j)->Default,"%d",&m_iProp[iAv]);
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_iProp[iAv++]));
				break;
			case 2:
				sscanf((*j)->Default,"%x",&m_clProp[clAv]);
				m_clProp[clAv]=Rgb2Bgr(m_clProp[clAv]);
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_clProp[clAv++]));
				break;
			case 3:
				sscanf((*j)->Default,"%f",&m_fProp[fAv]);
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_fProp[fAv++]));
				break;
			case 4:
				m_cbProp[cbAv]=(*j)->Default;
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_cbProp[cbAv], (*j)->m_ListProp , -1, CBS_DROPDOWNLIST));
				cbAv++;
				break;
			case 5:	//MASKED	
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, (*j)->m_ListProp->GetAt((*j)->m_ListProp->FindIndex(0)).GetBuffer(1)));
				iOther++;
				break;
			case 6:	//SLIDER
				sscanf((*j)->Default,"%d",&m_iProp[iAv]);
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_iProp[iAv++],atoi((*j)->m_ListProp->GetAt((*j)->m_ListProp->FindIndex(0)).GetBuffer(1)),atoi((*j)->m_ListProp->GetAt((*j)->m_ListProp->FindIndex(1)).GetBuffer(1)),false));//INT_MIN,INT_MAX,false));
				iOther++;
				break;
			case 7:	//MEMO
				m_szProp[szAv]=(*j)->Default;
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_szProp[szAv++])); 
				break;
			case 8:	//FBROWSER
				m_szProp[szAv]=(*j)->Default;
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_szProp[szAv],m_szProp[szAv++]));
				break;
			case 9: // boolean
				m_blProp[blAv]=(*j)->Default;
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_blProp[blAv++]));
				break;
			}
		}
	}
	//m_Oi.SetRedraw(TRUE);
}


void CEntPlg::ResetAllValues(void)
{
	for (int i=0;i<20;i++)
	{
		m_szProp[i]="";
		m_fProp[i]=0;
		m_iProp[i]=0;
		m_clProp[i]=0;
		m_cbProp[i]="";
	}
}

void CEntPlg::BuildXmlProps(CKHashTable &EntProp)
{
	CString value;
	COLORREF tmpcolor;


	vector<CObjectInspector::CProperty*>::iterator i = m_Oi.m_PropertyList.begin();
	vector<CObjectInspector::CProperty*>::iterator j;
	switch(CurrentEditType)
	{
		case PLUGIN_MESH:
			{
				j = (*i)->m_Childs.begin();

				CurrentMesh->Name=(*j++)->GetValueAsText();
				
				sscanf((*j++)->GetValueAsText(),"%x",&tmpcolor);
				j+=2; // faces/vertex
				CurrentMesh->Color.bRed=GetRValue(tmpcolor);
				CurrentMesh->Color.bGreen=GetGValue(tmpcolor);
				CurrentMesh->Color.bBlue=GetBValue(tmpcolor);

				CurrentMesh->SetAutoTexRecalc(((*j++)->GetValueAsText()=="1"));
				CurrentMesh->PrefabName=(*j++)->GetValueAsText();


				i++;
			}
			break;
		case PLUGIN_SHAPE:
			{
				j = (*i)->m_Childs.begin();

				CurrentShape->Name=(*j++)->GetValueAsText();
				
				sscanf((*j++)->GetValueAsText(),"%x",&tmpcolor);
				CurrentShape->Color.bRed=GetRValue(tmpcolor);
				CurrentShape->Color.bGreen=GetGValue(tmpcolor);
				CurrentShape->Color.bBlue=GetBValue(tmpcolor);

				// Draw Spline
				CurrentShape->DrawSpline=((*j++)->GetValueAsText()=="1");
				i++;
			}
			break;
		case PLUGIN_CAMERA:
			{
				j = (*i)->m_Childs.begin();

				CurrentCamera->Name=(*j++)->GetValueAsText();
				
				sscanf((*j++)->GetValueAsText(),"%x",&tmpcolor);
				CurrentCamera->Color.bRed=GetRValue(tmpcolor);
				CurrentCamera->Color.bGreen=GetGValue(tmpcolor);
				CurrentCamera->Color.bBlue=GetBValue(tmpcolor);
				i++;
			}
			break;
		case PLUGIN_PATCH:
			{
				j = (*i)->m_Childs.begin();

				CurrentPatch->Name=(*j++)->GetValueAsText();
				
				sscanf((*j++)->GetValueAsText(),"%x",&tmpcolor);
				CurrentPatch->Color.bRed=GetRValue(tmpcolor);
				CurrentPatch->Color.bGreen=GetGValue(tmpcolor);
				CurrentPatch->Color.bBlue=GetBValue(tmpcolor);
				i++;
			}
			break;
		case PLUGIN_SKELETON:
			{
				j = (*i)->m_Childs.begin();

				CurrentSkeletton->Name=(*j++)->GetValueAsText();
				
				sscanf((*j++)->GetValueAsText(),"%x",&tmpcolor);
				CurrentSkeletton->Color.bRed=GetRValue(tmpcolor);
				CurrentSkeletton->Color.bGreen=GetGValue(tmpcolor);
				CurrentSkeletton->Color.bBlue=GetBValue(tmpcolor);
				i++;
			}
			break;
	}

	for (; i != m_Oi.m_PropertyList.end(); i++)
	{
		for (j = (*i)->m_Childs.begin(); j != (*i)->m_Childs.end(); j++)
		{
			CString Verif1=(*j)->GetName();
			CString Verif2=(*j)->GetValueAsText();
			EntProp.SetEntry(Verif1,Verif2);
		}
	}
}



void CEntPlg::OnNotifyProp(NMHDR* pNMHDR, LRESULT* pResult)
{
	switch(CurrentEditType)
	{
	case PLUGIN_ENTITY:
		if (CurrentEntity!=NULL)
		{
			BuildXmlProps(CurrentEntity->m_Table);
			CurrentEntity->SetProperties();//ProcessMessage(KM_SETXML,(int)&CurrentEntity->m_Table,0);
		}
		break;
	case PLUGIN_MESH:
		if (CurrentMesh!=NULL)
		{
			BuildXmlProps(CurrentMesh->m_Table);
			DrawViews();
		}
		break;
	case PLUGIN_SHAPE:
		if (CurrentShape!=NULL)
		{
			BuildXmlProps(CurrentShape->m_Table);
			DrawViews();
		}
		break;
	case PLUGIN_CAMERA:
		if (CurrentCamera!=NULL)
		{
			BuildXmlProps(CurrentCamera->m_Table);
			DrawViews();
		}
		break;
	case PLUGIN_PATCH:
		if (CurrentPatch!=NULL)
		{
			BuildXmlProps(CurrentPatch->m_Table);
			DrawViews();
		}
		break;
	case PLUGIN_SKELETON:
		if (CurrentSkeletton!=NULL)
		{
			BuildXmlProps(CurrentSkeletton->m_Table);
			DrawViews();
		}
		break;
	}
}

void CEntPlg::OnNotifyProp(void)
{
	/*
	if (CurrentEntity!=NULL)
	{
		BuildXmlProps(CurrentEntity->m_Table);
		CurrentEntity->ProcessMessage(KM_SETXML,(int)&CurrentEntity->m_Table,0);
	}
	*/
	OnNotifyProp(NULL,NULL);
}
/*
void CEntPlg::OnSelchangeCb1() 
{
	//ResetAllValues();
	//UpdatePropList(m_EntsType[m_EntsTypes.GetCurSel()]);	
}
*/
void CEntPlg::UpdatePropsFromEntity(void)
{
	CKHashTable *CurTable;

	vector<CObjectInspector::CProperty*>::iterator i = m_Oi.m_PropertyList.begin();

	switch (CurrentEditType)
	{
	case PLUGIN_ENTITY:
//		CurrentEntity->ProcessMessage(KM_SETENTITY,(int)CurrentEntity,0);
		CurrentEntity->GetProperties();//ProcessMessage(KM_GETXML,(int)&CurrentEntity->m_Table,0);
		CurTable=&CurrentEntity->m_Table;
		break;
	case PLUGIN_MESH:
		CurTable=&CurrentMesh->m_Table;
		i++;
		break;
	case PLUGIN_SHAPE:
		CurTable=&CurrentShape->m_Table;
		i++;
		break;
	case PLUGIN_SKELETON:
		CurTable=&CurrentSkeletton->m_Table;
		i++;
		break;
	case PLUGIN_CAMERA:
		CurTable=&CurrentCamera->m_Table;
		i++;
		break;
	case PLUGIN_PATCH:
		CurTable=&CurrentPatch->m_Table;
		i++;
		break;
	}


	for (; i != m_Oi.m_PropertyList.end(); i++)
	{
		for (vector<CObjectInspector::CProperty*>::iterator j = (*i)->m_Childs.begin(); j != (*i)->m_Childs.end(); j++)
		{
			if (CurTable->EntryExists((*j)->GetName()))
			{
				switch((*j)->GetType())
				{
					
				case CObjectInspector::ptGroup:
					break;
				case CObjectInspector::ptShort:
				case CObjectInspector::ptInteger:
					
					*(*j)->m_pnValue=CurTable->GetInt((*j)->GetName());
					break;
				case CObjectInspector::ptFloat:
				case CObjectInspector::ptDouble:
					*(*j)->m_pfValue=CurTable->GetFloat((*j)->GetName());
					break;
				case CObjectInspector::ptBool:
					break;
				case CObjectInspector::ptDate:
					break;
				case CObjectInspector::ptColor:
					//*(*j)->m_pclValue=Rgb2Bgr(*(*j)->m_pclValue);
					*(*j)->m_pclValue=CurTable->GetDWord((*j)->GetName());
					break;
				case CObjectInspector::ptStringList:
					//sscanf(value,"%s",(*j)->m_pszValue);
					*(*j)->m_pszValue=CurTable->GetString((*j)->GetName());
					break;
				case CObjectInspector::ptMaskedEdit:
					*(*j)->m_pszValue=CurTable->GetString((*j)->GetName());
					break;
				case CObjectInspector::ptSliderCtrl:
					//sscanf(value,"%d",(*j)->m_pnValue);
					*(*j)->m_pnValue=CurTable->GetInt((*j)->GetName());
					break;
				case CObjectInspector::ptMemoEdit:
					//*(*j)->m_pszValue=value;
					*(*j)->m_pszValue=CurTable->GetString((*j)->GetName());
					break;
				case CObjectInspector::ptFileBroswer:
					//*(*j)->m_pszValue=value;
					*(*j)->m_pszValue=CurTable->GetString((*j)->GetName());
					break;
				}
				if (IsWindow(*(*j)->m_pInplaceControl))
					(*j)->SetValueInternal();
			}
		}
	}
	m_Oi.Invalidate(FALSE);
	
	
}

void CEntPlg::UpdateEntityList()
{
 // Build a list of entities
}


CKEntityType* CEntPlg::FindEntityTypeByName(CString EntName,int &ListNb)
{
	int j=0;
	for (vector<CKEntityType*>::iterator i = m_EntsType->begin(); i != m_EntsType->end(); i++)
	{
		ListNb=j;
		if ((*i)->Name==EntName) return (*i);
		j++;
	}
	return NULL;
}
CKEntityType* CEntPlg::FindEntityTypeByIndex(int Index)
{
	return (*m_EntsType)[Index];
	/*
	for (vector<CEntityType*>::iterator i = m_EntsType->begin(); i != m_EntsType->end(); i++)
	{
		j++;
	}
	*/
}

void CEntPlg::SetPropPrimitive(void *daPrim,unsigned int PlugType)
{
	CurrentEditType=PlugType;

	switch(PlugType)
	{
	case PLUGIN_MESH:
		CurrentMesh=((CKMesh*)daPrim);
		UpdatePropList(m_ObjectProps);
		break;
	case PLUGIN_SHAPE:
		CurrentShape=((CKShape*)daPrim);
		UpdatePropList(m_ShapeProps);
		break;
	case PLUGIN_PATCH:
		CurrentPatch=((CKPatch*)daPrim);
		UpdatePropList(m_PatchProps);
		break;
	case PLUGIN_SKELETON:
		CurrentSkeletton=((CKSkeleton*)daPrim);
		UpdatePropList(m_SkeletonProps);
		break;
	case PLUGIN_CAMERA:
		CurrentCamera=((CKCamera*)daPrim);
		UpdatePropList(m_CameraProps);
		break;
	case PLUGIN_ENTITY:
		CurrentEntity=(CKEntity*)daPrim;
		break;
	default:
		break;
	}

}
