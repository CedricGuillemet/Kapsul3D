//------------------------------------------------------------------------------
#include "stdafx.h"

CKPlugin::CKPlugin(char *FileName)
{
	Type=-1;

	PlugName=FileName;
    hInst=LoadLibrary(FileName);
    if (hInst==NULL) return ;

    ProcessIt=(int (*)(int,int,int))GetProcAddress(hInst,"Process");
    if (ProcessIt==NULL) return ;

    Type=Process(KM_GETTYPE);
    SecType=Process(KM_GETSECONDARYTYPE);

    Name=(char*)Process(KM_GETNAME);

    switch (Type)
    {
        case PLUGIN_CREATION:
            m_Dib=(CBitmap *)Process(KM_GETBITMAP);
			m_Dib2=(CBitmap *)Process(KM_GETBITMAPHOT);
			if (m_Dib2==NULL) m_Dib2=m_Dib;
            IsProperty=(Process(KM_ISPROPERTY)==1);
            break;
        case PLUGIN_PRIMITIVE:
            IsProperty=(Process(KM_ISPROPERTY)==1);
            break;
        case PLUGIN_FILE:
            GetParams();
            break;
        default:
            break;
    }
}

CKPlugin::~CKPlugin()
{
	if (hInst!=NULL)
	{
		FreeLibrary(hInst);
	}
}

HWND    CKPlugin::Param()
{
    return (HWND)Process(KM_OPEN,(int)Hwnd);
}

void    CKPlugin::Info(char *daInfos)
{
    daInfos=(char*)Process(KM_GETINFOS);
}

void CKPlugin::Close()
{
    Process(KM_CLOSE);
}

void CKPlugin::MouseDown(int X,int Y,Vertex daPos)
{
    Process(KM_LMOUSEDOWN,MAKELONG(X,Y),(int)&daPos);
}

void CKPlugin::MouseMove(int X,int Y,Vertex daPos)
{
    Process(KM_MOUSEMOVE,MAKELONG(X,Y),(int)&daPos);
}

void CKPlugin::MouseAbort(int X,int Y,Vertex daPos)
{
    Process(KM_RMOUSEUP,MAKELONG(X,Y),(int)&daPos);
}

void CKPlugin::MouseUp(int X,int Y,Vertex daPos)
{
    Process(KM_LMOUSEUP,MAKELONG(X,Y),(int)&daPos);
}

void CKPlugin::SetContext(void *dadk,void *params)
{
    Process(KM_SETSCENE,(int)dadk);
    //Process(KM_SETVIEW,(int)daView);
}

bool CKPlugin::IsCreating(void)
{
    return (Process(KM_ISCREATING)==1);
}

void CKPlugin::GetParams(void)
{
	CString tmp1,tmp2;
    tmp1=(char*)Process(KM_GETFILEDESC);
    tmp2=(char*)Process(KM_GETFILTER);

	ReadSupport=(Process(KM_GETREADSUPPORT)==1);
	WriteSupport=(Process(KM_GETWRITESUPPORT)==1);
    
    if (ReadSupport==1)
    {
        RFileDesc=tmp1;
        RFilter=tmp2;
    }
    else
    {
        RFileDesc="";
        RFilter="";
    }

    if (WriteSupport==1)
    {
        WFileDesc=tmp1;
        WFilter=tmp2;
    }
    else
    {
        WFileDesc="";
        WFilter="";
    }
}

int CKPlugin::Read(void *dadk,char *FileName)
{
	((CKScene*)dadk)->SetSceneForReading(true);
    bool retval=Process(KM_READFILE,(int)dadk,(int)FileName);
	((CKScene*)dadk)->SetSceneForReading(false);
	return retval;
}

int CKPlugin::Write(void *dadk,char *FileName)
{
    return Process(KM_WRITEFILE,(int)dadk,(int)FileName);
}

void CKPlugin::SetObject(void *daObj)
{
    Process(KM_SETOBJECT,(int)daObj);
}

int CKPlugin::Draw(int daState,int WichOne)
{
    return Process(KM_DRAW,daState,WichOne);
}

int CKPlugin::Process(UINT Msg,UINT wParam,UINT lParam)
{
	if (ProcessIt!=NULL)
		return ProcessIt(Msg,wParam,lParam);
	else
		return -1;
}

void CKPlugin::ReadResExtensions(void)
{
	char *Exts=(char*)Process(KM_GETEXTENSIONS,0,0);
	if (Exts!=NULL)
	{
		CString CurExt="";
		for (int i=0;i<strlen(Exts);i++)
		{
			if (Exts[i]!=';')
			{
				CurExt+=Exts[i];
			}
			else
			{
				ResExtensions.push_back(CurExt);
				CurExt="";
			}
		}
		ResExtensions.push_back(CurExt);
	}
}