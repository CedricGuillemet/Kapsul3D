#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include "DumpInfos.h"
#include "ModInfos.h"
#include "InfosScene.h"
#include "InfosSel.h"

// call in C only, Mfc in plugins are hard to implement.

CRollupCtrl *m_wndRollupCtrl;
CInfosScene *m_InfoScene;
CInfosSel *m_InfoSel;

HWND CKPluginInfos::Open(HWND Parent)
{
	SWITCH_RESOURCE;
	
	m_wndRollupCtrl=new CRollupCtrl;
	m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,4,164,362), CWnd::FromHandle(Parent), 2);	
	
	ModDiag=new CDumpInfos;
	ModDiag->Create((unsigned int)IDD_MODDIAG,CWnd::FromHandle(Parent));
	
	
	//CreateSeg=0;
	
	return ModDiag->m_hWnd;
}

void CKPluginInfos::Close()
{
	ModDiag->DestroyWindow();
}

int CKPluginInfos::ScenePluginType()
{
	return PLUGIN_OPERATION;
}

void CKPluginInfos::ReSize(int sx,int sy)
{
	m_wndRollupCtrl->MoveWindow(0,0,164,sy,TRUE);
}

CString CKPluginInfos::GetName()
{
	return "Infos";
}

CString CKPluginInfos::GetInfos()
{
	return "Infos";
}

bool CKPluginInfos::CreatingStatus()
{
	return false;
}

void CKPluginInfos::SetScene(CKScene *pScene)
{
	m_InfoScene->m_Scene=pScene;
	m_Scene=pScene;
	m_InfoScene->AffValues();
}

void CKPluginInfos::DeleteStuff()
{
	m_InfoScene->AffValues();
}


void CKPluginInfos::UpdateSelection()
{

}
	

CBitmap *CKPluginInfos::GetBitmap()
{
	SWITCH_RESOURCE;

	m_Dib.Detach();
	m_Dib.LoadBitmap(IDB_BITMAP_HOT);
    return &m_Dib;
}




