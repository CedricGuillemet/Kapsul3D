//---------------------------------------------------------------------------
#ifndef GenericLibH
#define GenericLibH

//#include "stdafx.h"

//#include "Kapsul3D.h"
//#include "Vertex.h"
//#include <windows.h>
//#include "Vertex.h"

#include "Kapsul3D.h"
//#include <windows.h>
class __declspec( dllexport ) GenericLib
{
    private:

        HINSTANCE   hInst;
        HWND (*ParamAddy)(void *,void *,void *,void *); // hwnd;component,mem,param
		//void *ParamAddy;
        void (*ExecAddy)(void *,char *); //param
		//void *ExecAddy;//)(void *,String); //param
        void (*ExecTexAddy)(void *);
        void (*CloseAddy)();
        void (*InfosAddy)(void *);
        void (*NameAddy)(void *);
        void (*PaletteAddy)(void *);
        void (*SetObjectAddy)(void *);

        void (*SetAddy)(void *,void*,void *);        
        void (*TypeAddy)(int *);
        void (*SecondaryTypeAddy)(int *);
        void (*MouseDownAddy)(int,int,Vertex);
        void (*MouseMoveAddy)(int,int,Vertex);
        void (*MouseUpAddy)(int,int,Vertex);
        void (*MouseAbortAddy)(int,int,Vertex);        
        
        int  (*IsCreatingAddy)();
        int  (*IsPropertyAddy)();

        void (*GetParamsAddy)(char *,char *);
        int  (*ReadSupportAddy)();
        int  (*WriteSupportAddy)();
		int  (*DrawAddy)();
        int  (*ReadAddy)(void *,char [260]);
        int  (*WriteAddy)(void *,char [260]);
        CBitmap* (*BitmapAddy)();

    public:

        int (*Process)(int ,int = 0,int = 0);        

        //HBITMAP GottenBits;
        CBitmap* m_Dib;
        //Graphics::TBitmap *gotten;

        int     Type,SecType;
        bool    IsProperty;

        bool    Link(char FileName[256],int WaitedType);
        HWND    Param();
        void    Info(char *daInfos);
        void    Run();
        void    Close();
        void    SetContext(void *dadk,void *params,void *daView);

        void    MouseDown(int X,int Y,Vertex daPos);
        void    MouseMove(int X,int Y,Vertex daPos);
        void    MouseUp(int X,int Y,Vertex daPos);
        void    MouseAbort(int X,int Y,Vertex daPos);

        bool    IsCreating(void);
        int     SizeX,SizeY;
        char    *Infos;
        char    *ParamVal;
        void    *Desk;
        void    *Hwnd;
        void    *Mem;
        void    *Component;
        char	*LinkedName;
        void    *dest;

        char	*Name;
        char	*tmpName; 
        HWND	MainWin;

        ~GenericLib();
         GenericLib();
        void GetPalette(PALETTEENTRY * PalDest);

        char *RFileDesc,*RFilter;
        char *WFileDesc,*WFilter;

        void GetParams(void);
        int Read(void *dadk,char FileName[256]);
        int Write(void *dadk,char FileName[256]);
        void SetObject(void *daObj);
		bool ReadSupport,WriteSupport;
		int Draw(int daState,int WichOne);
};

//---------------------------------------------------------------------------
#endif
