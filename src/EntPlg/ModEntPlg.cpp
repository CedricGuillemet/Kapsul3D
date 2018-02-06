#include "stdafx.h"
#include "Kapsul3D.h"

#include "resource.h"
#include "ModEntPlg.h"
#include "DumpEntPlg.h"
#include "resswitch.h"
// call in C only, Mfc in plugins are hard to implement.

extern vector<CKEntityType*> *m_EntsType;
CKEntity *CurrentEntity;

CKPluginEntPlg::CKPluginEntPlg()
{
}


CKPluginEntPlg::~CKPluginEntPlg()
{
}

HWND CKPluginEntPlg::Open(HWND Parent)
{
	SWITCH_RESOURCE;
	IsCreating=false;
	TypeEdit=-1;
	CurrentEntity=NULL;

    ModDiag=new CEntPlg;
    ModDiag->Create((unsigned int)IDD_MODDIAG,CWnd::FromHandle(Parent));
    
    return ModDiag->m_hWnd;
}

void CKPluginEntPlg::Close()
{
	ModDiag->DestroyWindow();
}

int CKPluginEntPlg::ScenePluginType()
{
	return PLUGIN_PRIMITIVE;
}

void CKPluginEntPlg::ReSize(int sx,int sy)
{
	ModDiag->MoveWindow(0,0,162,sy,TRUE);
}
void CKPluginEntPlg::LoseFocus()
{
	CurrentEntity=NULL;
}

CString CKPluginEntPlg::GetName()
{
	return "Entity Builder";
}

CString CKPluginEntPlg::GetInfos()
{
	return "Entity Builder";
}

bool CKPluginEntPlg::CreatingStatus()
{
	if (CurrentEntity!=NULL)
		return CurrentEntity->CreatingStatus();
	else
	{
		CurrentEntity=NULL;
		return false;
	}
}

void CKPluginEntPlg::SetScene(CKScene *pScene)
{
	m_Scene=pScene;
	if (ModDiag!=NULL)
	if (IsWindow(ModDiag->m_hWnd))
		ModDiag->Invalidate();
}

void CKPluginEntPlg::SetObject(void *pData,int DataType)
{
	if (DataType==PLUGIN_ENTITY)
	{
		CurrentEntity=(CKEntity*)pData;
		int ListNb;
		EntType=ModDiag->FindEntityTypeByName(CurrentEntity->EntType,ListNb);
		TypeEdit=ListNb;
		if (EntType!=NULL)
		{
			IsCreating=false;
			ModDiag->SetPropPrimitive(pData,DataType);
			ModDiag->UpdatePropList(EntType);
			ModDiag->UpdatePropsFromEntity();
		}
	}
	else
	{
		TypeEdit=-1;
		CurrentEntity=NULL;
		IsCreating=false;
		ModDiag->SetPropPrimitive(pData,DataType);
		ModDiag->UpdatePropsFromEntity();
	}
}


PrimBmp* CKPluginEntPlg::GetAllPrimitives()
{
	/*
	CKEntityManager cmnger;
	
	PROCESSIT procit=CKEntityManager::GetHandlerC("Entity");
	if (procit!=NULL)
	{
		procit(KM_GETBITMAPS,(UINT)&daBmps,0);
		return &daBmps;
	}
	*/
	return GetLib()->FillEntityPrimInterface();

}

void CKPluginEntPlg::SetPrimitive(int PrimitiveNb)
{
	TypeEdit=PrimitiveNb;
	ModDiag->SetPropPrimitive(NULL,(unsigned int)PLUGIN_ENTITY);
	ModDiag->UpdatePropList((*m_EntsType)[TypeEdit]);
}

void CKPluginEntPlg::DeleteStuff(void *pData,int DataType)
{
	// Selected stuffs are deleted (user pressed DEL)
	// take care if your are working on a selected item
	// this message is sent before effective cleaning
	if (CurrentEntity!=NULL)
	if (CurrentEntity->Selected)
	{
		CurrentEntity=NULL;
	}
}

void CKPluginEntPlg::UpdateStuff(void *pObject,int PlugType)
{
	if (CurrentEntity==(CKEntity*)pObject)
	{
		ModDiag->SetPropPrimitive((void*)CurrentEntity,(unsigned int)PLUGIN_ENTITY);
		ModDiag->UpdatePropsFromEntity();
	}
}



void CKPluginEntPlg::LMouseDown(int X,int Y,Vertex &Pos)
{
	/*
	if (CurrentEntity!=NULL)
	{
		CurrentEntity->LMouseDown(X,Y,Pos);
		CurrentEntity->GetMinMax();
	}
	*/
	if (TypeEdit!=-1)
	{
		if (CurrentEntity!=NULL)
		{
			if (CurrentEntity->CreatingStatus())
			{
				if (CurrentEntity!=NULL)
				{				
					CurrentEntity->LMouseDown(X,Y,Pos);
					CurrentEntity->Update();
				}
			}
			else
			{
				CurrentEntity=NULL;
			}
		}
		if (CurrentEntity==NULL)
		{
			CString CurrentType;
			CurrentType=(*m_EntsType)[TypeEdit]->Name;
			CurrentEntity=m_Scene->AddEntity(CurrentType);
//			CurrentEntity->SetEntity(CurrentEntity,0);
			//ModDiag->OnNotifyProp();
			if (CurrentEntity!=NULL)
			{				
				CurrentEntity->LMouseDown(X,Y,Pos);
				CurrentEntity->Update();
			}				
			ModDiag->UpdatePropsFromEntity();
			ModDiag->OnNotifyProp();
		}
	}
}
void CKPluginEntPlg::RMouseDown(int X,int Y,Vertex &Pos)
{
	if (CurrentEntity!=NULL)
		CurrentEntity->RMouseDown(X,Y,Pos);
}
void CKPluginEntPlg::LMouseUp(int X,int Y,Vertex &Pos)
{
	if (CurrentEntity!=NULL)
	{
		CurrentEntity->LMouseUp(X,Y,Pos);
		CurrentEntity->Update();
	}
}
void CKPluginEntPlg::RMouseUp(int X,int Y,Vertex &Pos)
{
	if (CurrentEntity!=NULL)
		CurrentEntity->RMouseUp(X,Y,Pos);
}
void CKPluginEntPlg::MouseMove(int X,int Y,Vertex &Pos)
{
	if (CurrentEntity!=NULL)
	{
		CurrentEntity->MouseMove(X,Y,Pos);
		if (CurrentEntity->CreatingStatus())
		{
			ModDiag->SetPropPrimitive((void*)CurrentEntity,(unsigned int)PLUGIN_ENTITY);
			ModDiag->UpdatePropsFromEntity();
			CurrentEntity->Update();
			DrawViews();
		}
	}
}


void CKPluginEntPlg::KeyDown(BYTE ckey)
{
	if (CurrentEntity!=NULL)
		CurrentEntity->KeyDown(ckey);
}

void CKPluginEntPlg::KeyUp(BYTE ckey)
{
	if (CurrentEntity!=NULL)
		CurrentEntity->KeyDown(ckey);
}
