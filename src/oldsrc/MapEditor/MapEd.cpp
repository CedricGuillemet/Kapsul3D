// Browser.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
//#include "Browser.h"

#include <headers.h>
#include "resource.h"
#include <commctrl.h>
//#include "ModdBrowser.h"
#include <vector>
#include "ThumbnailDlg.h"
#include "MapEdutils.h"
#include "EditorFunc.h"
#include "KDLLInst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// call in C only, Mfc in plugins are hard to implement.
extern HINSTANCE g_Inst;

#ifdef __cplusplus
    extern "C" {
#endif

/* 
    Plugins structure and private datas
*/

HWND Parent;
CThumbnailDlg *BrowserDiagHWND;
HINSTANCE myHinst;
bool IsCreating;
Desk *dk;
OGLView *View;
Object *CurrentObj=NULL;
Plan Crp;
bool SomethingSel=false;
bool LShiftDown=false;
bool CtrlDown=false;
Vertex Snap(8,8,8);
int TypeEdit=0;
int ngl;
Plan dap;
int dx,dy;
Vertex Remem,Remem2;
Vertex Length(8,8,8);
Vertex Min,Max;
MYPOINT PrjMin,PrjMax;

Vertex MulScal;
Vertex Center;
Vertex Startl,Endl;
double lx,ly;
Vertex daNorm;
Vertex CubeSize(8,8,8);
MYPOINT pts;
bool JustAddIt=0;
bool IsMoving=false;

int vtyp;
CWnd *tempo;
HINSTANCE tmphInst;
Object *daObj;
int CreateSeg=0;
CBitmap m_Dib;
COption *KOption;
CUndoRedo *CurrentUndo;

static char PluginName[]={"Map editor"};
static char PluginInfos[]={"Map editor"};


unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
void LMouseDown(int X,int Y,Vertex *Pos);
void LMouseUp(int X,int Y,Vertex *Pos);
void MouseMove(int X,int Y,Vertex *Pos);
void RMouseDown(int X,int Y,Vertex *Pos);
void RMouseUp(int X,int Y,Vertex *Pos);
void KMKeyDown(unsigned nChar);
void KMKeyUp(unsigned nChar);



unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
    //AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE tempinst=AfxGetInstanceHandle();
	AfxSetResourceHandle(g_Inst);
	if (Msg==123)
		value=0;

    switch (Msg)
    {
    case KM_OPEN:
        KOption=(COption*)GetGOption();
        Parent=(HWND)wParam;
        tempo=CWnd::FromHandle((HWND)wParam);
        BrowserDiagHWND=new CThumbnailDlg;
        BrowserDiagHWND->Create((unsigned int)IDD_MODDIAG,tempo);
        value=(unsigned int)BrowserDiagHWND->m_hWnd;
	
        break;
    case KM_CLOSE:
		//delete BrowserDiagHWND;
		BrowserDiagHWND->DestroyWindow();
		delete BrowserDiagHWND;

        //BrowserDiagHWND.DestroyWindow();
        //::DestroyWindow(BrowserDiagHWND.m_hWnd);
        //BrowserDiagHWND.m_hm_hImageList
        //::EndDialog(BrowserDiagHWND->m_hWnd,0);

        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
    case KM_GETTYPE:
        value=PLUGIN_CREATION;
        break;
    case KM_GETSECONDARYTYPE:
        value=PLUGIN_OBJECT;
        break;
    case KM_ISPROPERTY:
        value=0;
        break;
    case KM_ISCREATING:
        value=CreateSeg;
        break;
    case KM_SETDESK:
        if ((dk!=(Desk*)wParam)&&((Desk*)wParam!=NULL))
        {
			//SomethingSel=(GetNbSelectedObjects()!=0);
            dk=(Desk*)wParam;
        }
        break;
    case KM_GETBITMAP:
        m_Dib.LoadBitmap(IDB_BITMAP);
        value=(unsigned int)&m_Dib;
        break;
    case KM_DRAW:
		if ((TypeEdit==11)&&(CreateSeg==1) )
		{
			glColor4f(1,0,1,1);
			glLineStipple(4,0xAAAA);
			glEnable(GL_LINE_STIPPLE);

			glBegin(GL_LINES);
			glVertex3f(Remem.vx,Remem.vy,Remem.vz);
			glVertex3f(Remem2.vx,Remem2.vy,Remem2.vz);
			glEnd();

			glDisable(GL_LINE_STIPPLE);
		}
	
        value=PLUGIN_ALL;
        break;
    case KM_SETVIEW:
        if (View!=(OGLView*)wParam)
        {
            View=(OGLView*)wParam;
        }
        break;

    case KM_LMOUSEDOWN:
        LMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_RMOUSEDOWN:
        RMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_LMOUSEUP:
        LMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_RMOUSEUP:
        RMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_MOUSEMOVE:
        MouseMove(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_MOVEWINDOW:
        BrowserDiagHWND->MoveWindow(0,0,162,(int)lParam,TRUE);
        value=(int)lParam;
        break;
    case KM_KEYDOWN:
        KMKeyDown(wParam);
        break;
    case KM_KEYUP:
        KMKeyUp(wParam);
        break;
    case KM_UNSETPLUGIN:
        BrowserDiagHWND->UnActiveIt();
        break;
    }
	AfxSetResourceHandle(tempinst);
    return value;
}



void LMouseDown(int X,int Y,Vertex *Pos)
{
    Crp.PlanOfView(View,dk->Active);

    if (CreateSeg==0)
    {
		if (LShiftDown)
		{
			ClickSelectObject(X,Y,Pos);
		}
		else
		{
			if (TypeEdit==10)
			{
				BeginRotate(X,Y,Pos);
			}
			if (TypeEdit==11)
			{
				BeginCutter(X,Y,Pos);
			}
			if (TypeEdit==12)
			{
				BeginMoveVertex(X,Y,Pos);
			}
			if (TypeEdit==13)
			{
				BeginMoveEdge(X,Y,Pos);
			}
			if (TypeEdit==20)
			{
				BeginTranslatecoords(X,Y,Pos);
			}
			if (TypeEdit==21)
			{
				BeginScalecoords(X,Y,Pos);
			}
			if (TypeEdit==22)
			{
				BeginRotatecoords(X,Y,Pos);
			}

			if (TypeEdit==0)
			{
				SomethingSel=GetNbSelectedObjects();
				if (SomethingSel)
				{
					if (!BeginMoveBuffer(X,Y,Pos))
						BeginScale(X,Y,Pos);
				}
				else
				{
					BeginCreateBox(X,Y,Pos);
				}

			}
		}
	}
	else
	{
		if (TypeEdit==11)
		{
			ValidateCutter(X,Y,Pos);
		}
	}
}


void LMouseUp(int X,int Y,Vertex *Pos)
{
	if (TypeEdit!=11)
	{
		dk->UpdateBuf();

		if ((TypeEdit==12)||(TypeEdit==13)) dk->DeleteBufVert();

		CreateSeg=0;
		if (JustAddIt)
		{
			dk->cSel->SingleObject(CurrentObj,true);
			CurrentObj->Selected=true;
			SomethingSel=true;
			JustAddIt=false;
		}

		if (IsMoving)
		{
			IsMoving=false;
			
		}
	}
}

void MouseMove(int X,int Y,Vertex *Pos)
{
    Vertex temp;
	if ((TypeEdit==11)&&(CreateSeg==1))
	{
		Remem2=*Pos;
	}
	else
	if ((TypeEdit==12)&&(CreateSeg==1))
	{
		MoveVertex(X,Y,Pos);
	}
	else
	if ((TypeEdit==13)&&(CreateSeg==1))
	{
		MoveEdge(X,Y,Pos);
	}
	else
	if ((TypeEdit==20)&&(CreateSeg==1))
	{
		Translatecoords(X,Y,Pos);
	}
	else
	if ((TypeEdit==21)&&(CreateSeg==1))
	{
		Scalecoords(X,Y,Pos);
	}
	else
	if ((TypeEdit==22)&&(CreateSeg==1))
	{
		Rotatecoords(X,Y,Pos);
	}
	else

    if (!SomethingSel)
	//if (GetNbSelectedObjects()==0)
    {
        if (CreateSeg)
        {
			if (TypeEdit==0)
			{
				CreateBox(X,Y,Pos);
			}
            //DrawViews();
        }
    }
    else
    {
		if (TypeEdit==10)
		{
			// rotate
			if (CreateSeg)
			{
				RotateBuffer(X,Y,Pos);
			}
		}
		else
		{
			if (IsMoving)
			{
				MoveBuffer(X,Y,Pos);

			}
			else
			if (CreateSeg)
			{
				// scale it
				ScaleBuffer(X,Y,Pos);
			}
		}
    }
}

void KMKeyDown(unsigned nChar)
{
	Object *daObj,*daObj2;
	Vertex Vtr;

    switch(nChar)
    {
    case VK_SHIFT:
        LShiftDown=true;
        break;
    case VK_CONTROL:
        CtrlDown=true;
        break;
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
		CurrentUndo->UndoType=UNDO_MODIFY;
		SetSelectedToBeforeUndo();

		if (CtrlDown)
		{
			int nbSide=nChar-'0';
			SetSelectedNGon(nbSide);
			DrawViews();
		}
		SetSelectedToAfterUndo();
		break;

	// Delete all selected objects
	case VK_DELETE:
		// undo

		
		CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
		CurrentUndo->UndoType=UNDO_DELETE;
		SetSelectedToBeforeUndo();

		for (daObj=dk->FirstObject;daObj!=NULL;)
		{
			daObj2=daObj->Next;
			if (daObj->Selected)
			{
				dk->DelObject(daObj);
			}
			daObj=daObj2;
		}
		SomethingSel=false;
		DrawViews();
		break;
	// Copy Objects
	case VK_SPACE:
		CurrentUndo=dk->AddUndo("MapEditor.dll",GetNbSelectedObjects());
		CurrentUndo->UndoType=UNDO_CREATE;

		switch(GetView())
		{
		case 1:
			Vtr=Vertex(Snap.vx,Snap.vy,0);
			break;
		case 2:
			Vtr=Vertex(Snap.vx,0,-Snap.vz);
			break;
		case 3:
			Vtr=Vertex(0,-Snap.vy,-Snap.vz);
			break;
		case 4:
			Vtr=Vertex(-Snap.vx,-Snap.vy,0);
			break;
		case 5:
			Vtr=Vertex(-Snap.vx,0,Snap.vz);
			break;
		case 6:
			Vtr=Vertex(0,Snap.vy,Snap.vz);
			break;
		default:
			Vtr=Vertex(Snap.vx,Snap.vy,0);
			break;



		}
//		dk->InitAllObjectsTag(0);
		for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
		{
			if (daObj->Selected)
			{
				dk->AddObject();
				dk->NextObject->IsCopyOf(daObj);
				dk->NextObject->Translate(Vtr);
				dk->NextObject->Selected=false;
				dk->NextObject->Tag=1;
			}
		}
		
		dk->cSel->UnSelectObject(false);
		for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
		{
			if (daObj->Tag==1)
			{
				dk->cSel->SingleObject(daObj,true);
				daObj->Selected=true;
			}
		}
		SomethingSel=true;
		SetSelectedToAfterUndo();
		DrawViews();
		break;

    case VK_ESCAPE:
        SomethingSel=false;
		TypeEdit=0;
		CreateSeg=0;
		DrawViews();
        break;
    default:

        break;
    }

}

void KMKeyUp(unsigned nChar)
{
    switch(nChar)
    {
    case VK_SHIFT:
        LShiftDown=false;
        break;
    case VK_CONTROL:
        CtrlDown=false;
        break;
    default:
        break;
    }

}

void RMouseDown(int X,int Y,Vertex *Pos)
{

}

void RMouseUp(int X,int Y,Vertex *Pos)
{
	if (TypeEdit==11)
		CreateSeg=0;
	DrawViews();
}



#ifdef __cplusplus
    }
#endif
