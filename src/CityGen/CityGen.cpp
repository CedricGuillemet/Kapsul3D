#include "stdafx.h"
#include <Kapsul3D.h>
#include <headers.h>
#include "resource.h"
#include <commctrl.h>
#include "CityDiag.h"
// call in C only, Mfc in plugins are hard to implement.
#include <vector>
using std::vector;

HINSTANCE g_Inst;

static AFX_EXTENSION_MODULE CityGenDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove t his if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("CityGen.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(CityGenDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(CityGenDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("CityGen.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(CityGenDLL);
	}
	return 1;   // ok
}

#ifdef __cplusplus
    extern "C" {
#endif

/* 
    Plugins structure and private datas
*/

HWND Parent;

HINSTANCE myHinst;
bool IsCreating;
Desk *dk;
OGLView *View;

/*
    My datas
*/

// put here your datas
Shape *SShape;
CPrivateData *pd=NULL;
Shape *genshp=NULL;
/*
    My datas
*/
Object *obase,*omedian[5],*oend;



vector<Assigns> ass;
/*
    constants
*/

static char PluginName[]={"City Generator"};
static char PluginInfos[]={"City Generator"};

/*
    My stuffs
*/

bool LowestIsStart(Shape *daShp)
{
    if (daShp->FirstSegment->Dot.vy<daShp->NextSegment->Dot.vy) return true;
        
    return false;
}

void AppendShp(Shape *baseShp,Vertex Trans1,Vertex Trans2,bool Lowest,double amin,int NumObj)
{
    Segment *daSeg;
    int vav=0,fav=0;
    int i,j;
    float nbc;
    Object *daObj;

    //dk->AddObject();

    nbc=baseShp->GetCount();

    if (NumObj==0) daObj=obase;
    if ((NumObj>=1)&&(NumObj<=9)) daObj=omedian[NumObj-1];
    if (NumObj==10) daObj=oend;

    daObj->AllocatePoly(8*nbc,nbc*16);
	daObj->AllocateUV(0,nbc*16);

    j=0;

    if (Lowest)
    {
        
        daSeg=baseShp->FirstSegment;
        while(daSeg!=NULL)
        {
            Vertex tmp1;
            tmp1=(daSeg->Dot-Trans1+Trans2);
            
            genshp->AddSegment(tmp1.vx-amin,tmp1.vz,tmp1.vy);

            for (i=0;i<8;i++)
            {
                double Len=(daSeg->Dot.vx-Trans1.vx+Trans2.vx-amin);
                daObj->pv[vav].vx=cos((2.0f*PI)/8*i)*Len;
                daObj->pv[vav].vy=sin((2.0f*PI)/8*i)*Len;
                daObj->pv[vav].vz=(daSeg->Dot.vy-Trans1.vy+Trans2.vy);

                daObj->puv[0][vav].u=((1.0f/(double)(8))*(double)i);
                daObj->puv[0][vav].v=((1.0f/(double)(nbc))*(double)j);


                vav++;
            }
                

            daSeg=daSeg->Next;
            j++;
        }
    }
    else
    {
        daSeg=baseShp->NextSegment;
        while(daSeg!=NULL)
        {

            Vertex tmp1;
            tmp1=(daSeg->Dot-Trans1+Trans2);
            
            genshp->AddSegment(tmp1.vx-amin,tmp1.vz,tmp1.vy);


            for (i=0;i<8;i++)
            {
                double Len=(daSeg->Dot.vx-Trans1.vx+Trans2.vx-amin);
                daObj->pv[vav].vx=cos((2.0f*PI)/8*i)*Len;
                daObj->pv[vav].vy=sin((2.0f*PI)/8*i)*Len;
                daObj->pv[vav].vz=(daSeg->Dot.vy-Trans1.vy+Trans2.vy);

                daObj->puv[0][vav].u=((1.0f/(double)(8))*(double)i);
                daObj->puv[0][vav].v=((1.0f/(double)(nbc))*(double)j);

                vav++;
            }

            daSeg=daSeg->Prev;
            j++;

        }
    }

    fav=0;
    int nb2sec2=baseShp->GetCount();
    int nb2sec1=8;
    
	for (j=0;j<nb2sec2;j++)
    {
    	for (i=0;i<nb2sec1;i++)
	    {
			daObj->pl[fav].Allocate(1,4);
	    	daObj->pl[fav].nbvert[0]=((i+1)%nb2sec1)+nb2sec1+j*nb2sec1;
    		daObj->pl[fav].nbvert[1]=i+nb2sec1+j*nb2sec1;
			daObj->pl[fav].nbvert[3]=((i+1)%nb2sec1)+j*nb2sec1;
            daObj->pl[fav].nbvert[2]=i+j*nb2sec1;
    		
	    	daObj->pl[fav].Tex[0][0]=daObj->pl[fav].nbvert[0];
    		daObj->pl[fav].Tex[0][1]=daObj->pl[fav].nbvert[1];
			daObj->pl[fav].Tex[0][2]=daObj->pl[fav].nbvert[2];
            daObj->pl[fav].Tex[0][3]=daObj->pl[fav].nbvert[3];
    		
    		fav++;
/*
    		daObj->pl[fav].nbvert[0]=((i+1)%nb2sec1)+j*nb2sec1;
    		daObj->pl[fav].nbvert[1]=((1+i)%nb2sec1)+nb2sec1+j*nb2sec1;
            daObj->pl[fav].nbvert[2]=i+j*nb2sec1;
  */  		
  		
            //fav++;

    	}
    }
/*

	    	Obj->pf[ind]->nbvert[0]=i+j*nb2sec;
    		Obj->pf[ind]->nbvert[1]=i+nb2sec+j*nb2sec;
    		Obj->pf[ind]->nbvert[2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
    		ind++;

    		Obj->pf[ind]->nbvert[0]=i+j*nb2sec;
    		Obj->pf[ind]->nbvert[1]=((1+i)%nb2sec)+nb2sec+j*nb2sec;
    		Obj->pf[ind]->nbvert[2]=((i+1)%nb2sec)+j*nb2sec;
*/
/*
    for (fav=0;fav<(8*baseShp->GetCount());fav++)
    {
        dk->NextObject->pf[fav]->nbvert[0]=;
        dk->NextObject->pf[fav]->nbvert[1]=;
        dk->NextObject->pf[fav]->nbvert[2]=;
        fav++;

        dk->NextObject->pf[fav]->nbvert[0]=;
        dk->NextObject->pf[fav]->nbvert[1]=;
        dk->NextObject->pf[fav]->nbvert[2]=;
        fav++;

    }
    */
}

void GenBuilding(void)
{
    Assigns *allbase[100],*allmed[100],*allend[100];
    Assigns *base,*med[5],*end;
    Shape *baseShp,*medShp[5],*endShp;
    int allbaseav=0,allmedav=0,allendav=0;
    int i,nbmed;

    genshp=new Shape(NULL,NULL);

    // tris

    for (i=0;i<ass.size();i++)
    {
        if (ass[i].UseBase) 
            allbase[allbaseav++]=&ass[i];
        if (ass[i].UseMedian) 
            allmed[allmedav++]=&ass[i];
        if (ass[i].UseEnd) 
            allend[allendav++]=&ass[i];
    }

    // gen

    base=allbase[rand()%allbaseav];
    baseShp=(Shape*)dk->GetByName(base->Name,PLUGIN_SHAPE);

    nbmed=(rand()%5);
    nbmed=5;
    for (i=0;i<nbmed;i++)
    {
        med[i]=allmed[rand()%allmedav];
        medShp[i]=(Shape*)dk->GetByName(med[i]->Name,PLUGIN_SHAPE);
    }

    end=allend[rand()%allendav];
    endShp=(Shape*)dk->GetByName(end->Name,PLUGIN_SHAPE);


    // shape build

    Vertex Trans;
    Vertex Trans2;
    bool Lowest;

    // map x

    double aminx;
    Lowest=LowestIsStart(baseShp);
    if (Lowest)
    {
        aminx=endShp->NextSegment->Dot.vx-endShp->FirstSegment->Dot.vx;
        
    }
    else
    {
        aminx=endShp->FirstSegment->Dot.vx-endShp->NextSegment->Dot.vx;
    }

    
    for (i=0;i<nbmed;i++)
    {

        Lowest=LowestIsStart(medShp[i]);

        if (Lowest)
        {
            aminx+=(medShp[i]->NextSegment->Dot.vx-medShp[i]->FirstSegment->Dot.vx);
        }
        else
        {
            aminx+=(medShp[i]->FirstSegment->Dot.vx-medShp[i]->NextSegment->Dot.vx);
        }
    }


    // Build it

    Lowest=LowestIsStart(baseShp);
    if (Lowest)
    {
        Trans=baseShp->FirstSegment->Dot;
        Trans2=baseShp->NextSegment->Dot;
    }
    else
    {
        Trans=baseShp->NextSegment->Dot;
        Trans2=baseShp->FirstSegment->Dot;
    }

    

    //Trans2.vx=aminx;

    AppendShp(baseShp,Trans,Vertex(0,0,0),Lowest,aminx,0);

    Trans2=Trans2-Trans;
    

    for (i=0;i<nbmed;i++)
    {

        Lowest=LowestIsStart(medShp[i]);

        if (Lowest)
        {
            Trans=medShp[i]->FirstSegment->Dot;
        }
        else
        {
            Trans=medShp[i]->NextSegment->Dot;
        }

        AppendShp(medShp[i],Trans,Trans2,Lowest,aminx,i+1);
        
        if (Lowest)
        {
            Trans2+=(medShp[i]->NextSegment->Dot-Trans);
        }
        else
        {
            Trans2+=(medShp[i]->FirstSegment->Dot-Trans);
        }

        //Trans2=Trans2-Trans;
    }

    
    //Trans2=Trans2-Trans;

    
    

    Lowest=LowestIsStart(endShp);
    if (Lowest)
    {
        Trans=endShp->FirstSegment->Dot;
        //Trans2=endShp->NextSegment->Dot;
    }
    else
    {
        Trans=endShp->NextSegment->Dot;
        //Trans2=endShp->FirstSegment->Dot;
    }
    

    AppendShp(endShp,Trans,Trans2,Lowest,aminx,10);

}

void SavePrivate(void)
{
	int nbAnims=0;
	int TotalSize=0;
	long *ptr;
	unsigned char *ptr2;


    if (pd!=NULL)
    {
	    TotalSize=sizeof(Assigns)*ass.size()+4;

    

	    ptr=(long*)pd->Allocate(TotalSize);
	    ptr2=(unsigned char*)ptr;
	    ptr2+=4;

	    (*ptr)=ass.size();
	    
	    for (int i=0;i<ass.size();i++)
	    {
		    memcpy(ptr2,(void*)&ass[i],sizeof(Assigns));
		    ptr2+=sizeof(Assigns);
		    ptr=(long*)ptr2;
	    }
    }

}

void LoadPrivate(void)
{
	int nbShp,nbFrm;
	long *ptr;
	unsigned char *ptr2;
    Assigns tmp("temp",0,0,0);

	ptr=(long*)pd->lpBits;

	if (ptr!=NULL)
	{
		ptr2=(unsigned char*)ptr;

		nbShp=(*ptr);
		ptr2+=4;

		for (int i=0;i<nbShp;i++)
		{
			memcpy(&tmp,ptr2,sizeof(Assigns));
            ass.push_back(tmp);
			ptr2+=sizeof(Assigns);
		}
	}
}

/*
    Exports symbols
    Add here all the symbol which can be use anywhere else (exports)
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);

/*
    Process message handler
*/
CBitmap m_Dib;
CWnd *tempo;
CCityDiag *ModDiag;

int Draw();
void LMouseDown(int X,int Y,Vertex *Pos);
void RMouseDown(int X,int Y,Vertex *Pos);
void LMouseUp(int X,int Y,Vertex *Pos);
void RMouseUp(int X,int Y,Vertex *Pos);
void MouseMove(int X,int Y,Vertex *Pos);

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
	int i;
    unsigned int value=0;
	HINSTANCE tempinst=AfxGetInstanceHandle();
	AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_OPEN:
        Parent=(HWND)wParam;
        tempo=CWnd::FromHandle((HWND)wParam);

        ModDiag=new CCityDiag;
        ModDiag->Create((unsigned int)IDD_MODDIAG,tempo);
        
        value=(unsigned int)ModDiag->m_hWnd;
        

        break;
    case KM_CLOSE:
        delete oend;
        delete obase;
        for (i=0;i<5;i++)
            delete omedian[i];

        SavePrivate();
        ModDiag->DestroyWindow();
        break;
    case KM_LOADDESK:
        LoadPrivate();
        break;
    case KM_SAVEDESK:
        SavePrivate();
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
        value=IsCreating;
        break;
    case KM_SETDESK:
        if ((Desk*)wParam!=dk)
		{

            SavePrivate();
			dk=(Desk*)wParam;
			pd=dk->AddPrivate("TATOUINE.DLL");
			LoadPrivate();


		}
        break;
    case KM_GETBITMAP:
        m_Dib.LoadBitmap(IDB_BITMAP);
        value=(unsigned int)&m_Dib;
        break;;
    case KM_DRAW:
        value=Draw();
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
    case KM_SETVIEW:
        View=(OGLView*)wParam;
        break;
	}
	AfxSetResourceHandle(tempinst);
    return value;
}

/*
    Functions used by this plugin
*/

void LMouseDown(int X,int Y,Vertex *Pos)
{
    bool HasFound;
/*
    Shape *tmpShp=dk->cSel->GetShape(X,Y);
    if (tmpShp!=NULL)
    {
        SShape=tmpShp;
		ModDiag->m_ShapeName.SetWindowText(SShape->Name);
        
		ModDiag->m_Base.SetCheck(BST_UNCHECKED);
		ModDiag->m_Median.SetCheck(BST_UNCHECKED);
		ModDiag->m_End.SetCheck(BST_UNCHECKED);

        HasFound=false;
        for (int i=0;i<ass.size();i++)
        {
            if (strcmp(ass[i].Name,SShape->Name)==0)
            {
                if (ass[i].UseBase)
					ModDiag->m_Base.SetCheck(BST_CHECKED);
                if (ass[i].UseMedian)
					ModDiag->m_Median.SetCheck(BST_CHECKED);
                if (ass[i].UseEnd)
					ModDiag->m_End.SetCheck(BST_CHECKED);

                HasFound=true;
            }
        }
        if (!HasFound)
            ass.push_back(Assigns(SShape->Name,false,false,false));
    }

  */
	
	for (Shape *shp=dk->FirstShape;shp!=NULL;shp=shp->Next)
		ass.push_back(Assigns(shp->Name,true,true,true));
}

void LMouseUp(int X,int Y,Vertex *Pos)
{
}

void MouseMove(int X,int Y,Vertex *Pos)
{
    Shape *tmpShp=dk->cSel->GetShape(X,Y);
    if (tmpShp!=NULL)
    {
        LStatus("Pick this shape.");
        SetPointer(LoadCursor(myHinst,MAKEINTRESOURCE(IDC_POINTER_FOUND)));
    }
    else
    {
        LStatus("Pick a shape.");
        SetPointer(LoadCursor(myHinst,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));
    }
}
void RMouseDown(int X,int Y,Vertex *Pos)
{
}

void RMouseUp(int X,int Y,Vertex *Pos)
{
}


int Draw()
{
    Segment *daseg;

	glColor4f(0.7,0.7,0.7,0.7);
    if (genshp!=NULL)
    {
        View->DrawObject(obase,1,0);
        for (int i=0;i<5;i++)
            View->DrawObject(omedian[i],1,0);
        View->DrawObject(oend,1,0);

    }
	return PLUGIN_ALL;
}

#ifdef __cplusplus
    }
#endif
