//---------------------------------------------------------------------------
#ifndef CKPluginManagerH
#define CKPluginManagerH
#include <vector>
using std::vector;

#include "Kapsul3D.h"

class KAPSUL_DESC CKPluginManager
{
    public:

	vector<CKFilePlugin*> FilePlugins;
	vector<CKScenePlugin*> OperationPlugins;
	vector<CKScenePlugin*> PrimitivePlugins;
	vector<CKRenderer*> RendererPlugins;

    bool RegisterPlugs(char *PlugDir);
	bool RegisterFilePlugs(char *PlugDir);
        
    CKPluginManager(bool InitPlugins);
    ~CKPluginManager();

	CKOption *m_Option;
/*
    CKScenePlugin *CamProp;
    CKScenePlugin *SkelProp;
    
	CKScenePlugin *PatchProp;
    CKScenePlugin *MeshProp;
    CKScenePlugin *ShapeProp;
*/
	CKScenePlugin *EntProp;

	vector<CKFilePlugin*> ReadGen;
	vector<CKFilePlugin*> WriteGen;

    CKScenePlugin * GetScenePluginByName(CString Name);
	CKFilePlugin * GetFilePluginByName(CString Name);

	inline CKPlugin * GetSupportedResManager(CString Path,CString &Dest,CString &ZipRep);

	// Intefaces
	//CKRenderer *(*CreateTempRenderInterface)(CKScene *Scene);
	CKRenderer *(*CreateRenderInterface)(CKScene *Scene);

	CKFilePlugin *(*CreateFileInterface)();
	CKScenePlugin *(*CreateSceneInterface)();
	CKEntity *(*CreateEntityInterface)(CString sEntity);

	PrimBmp* (*FillEntityPrimInterface)();
	void InitRendererInterface(CString PluginName);
	void InitEntityInterface(CString PluginName);

	HINSTANCE hInstRenderer;
	HINSTANCE hInstEntity;

	PrimBmp* EntityBitmaps();
	bool IsRendererValid(char *RendererName);
};


//---------------------------------------------------------------------------
#endif
