
#if !defined(AFX_CKPluginInfos_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_CKPluginInfos_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <kapsul3D.h>
#include "DumpInfos.h"

class CKPluginInfos : public CKScenePlugin  
{
public:
	HWND Open(HWND Parent);
	void Close();
	int ScenePluginType();
	void ReSize(int sx,int sy);

	CString GetName();
	CString GetInfos();

	bool CreatingStatus();
	void SetScene(CKScene *pScene);

	CBitmap *GetBitmap();
	void DeleteStuff();

	void UpdateSelection();
	

private:
	
	CKScene *m_Scene;
	void RecCalcBone(CKBone *daBone);
	void Calc(void);
	CDumpInfos *ModDiag;
	CBitmap m_Dib,m_Dib2;
};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
