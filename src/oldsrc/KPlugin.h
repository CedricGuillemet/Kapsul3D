//---------------------------------------------------------------------------
#ifndef CKPluginH
#define CKPluginH

//#include "stdafx.h"

//#include "Kapsul3D.h"
//#include "Vertex.h"
//#include <windows.h>
//#include "Vertex.h"

#include "Kapsul3D.h"
//#include <windows.h>
class KAPSUL_DESC CKPlugin
{
    private:

        HINSTANCE   hInst;
		int (*ProcessIt)(int ,int = 0,int = 0);
    public:

        ~CKPlugin();
         CKPlugin(char *FileName);
        

        CBitmap* m_Dib;
		CBitmap* m_Dib2;

        int     Type,SecType;
        bool    IsProperty;

        HWND    Param();
        void    Info(char *daInfos);
        void    Close();
        void    SetContext(void *dadk,void *params);

        void    MouseDown(int X,int Y,Vertex daPos);
        void    MouseMove(int X,int Y,Vertex daPos);
        void    MouseUp(int X,int Y,Vertex daPos);
        void    MouseAbort(int X,int Y,Vertex daPos);

        bool    IsCreating(void);
		int		Process(UINT Msg,UINT wParam=0,UINT lParam=0);

		void    *Hwnd;
		/*
        void    *Desk;
        
        void    *Mem;
        void    *Component;
        void    *dest;

        HWND	MainWin;
*/

        CString RFileDesc,RFilter;
        CString WFileDesc,WFilter;
        CString    Infos;
        CString	Name;
		CString PlugName;

        void GetParams(void);
        int Read(void *dadk,char *FileName);
        int Write(void *dadk,char *FileName);
        void SetObject(void *daObj);
		bool ReadSupport,WriteSupport;
		int Draw(int daState,int WichOne);

		vector<CString> ResExtensions;
		void ReadResExtensions(void);

};

//---------------------------------------------------------------------------
#endif
