//---------------------------------------------------------------------------
#ifndef LibContainerH
#define LibContainerH
/*
#include <io.h>
#include "GenericLib.h"
*/
#include "Kapsul3D.h"

class __declspec( dllexport ) LibContainer
{
    public:
        GenericLib **ObjectsLib;
        int nb2ObjectsLib;
        char  **ObjLibName;

        GenericLib **TexturesLib;
        int nb2TexturesLib;
        char  **TexLibName;

        GenericLib **FilesLib;
        int nb2FilesLib;
        char  **FlsLibName;

        GenericLib **ToolsLib;
        int nb2ToolsLib;
        char  **TlsLibName;

        //int AddFilesIn(char Dir[260],char **Liste,int max);
        bool RegisterLibs(char *PlugDir);
        
    LibContainer();
    ~LibContainer();
    //void AffName(String Name);
//    TStatusBar *StatusBar;

    GenericLib *CamProp;
    GenericLib *SkelProp;
    GenericLib *LightProp;
    GenericLib *ObjectProp;
    GenericLib *ShapeProp;

    //GenericLib *EmiProp;

	GenericLib **ReadGen;
	GenericLib **WriteGen;


    GenericLib * GetLibByName(char Name[256]);
};

//__declspec(dllexport) extern LibContainer *KapsulLibs;



//---------------------------------------------------------------------------
#endif
