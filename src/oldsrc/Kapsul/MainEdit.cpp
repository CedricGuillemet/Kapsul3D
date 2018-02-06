#include "stdafx.h"

//#include "memmgr/mmgr.h"

#include "MainEdit.h"
#include "Mainfrm.h"
#include "SelName.h"
#include "ObjProps.h"
//#include "DeskDoc.h"
//#include "TestGLView.h"
//extern HINSTANCE hInst;
//extern OGLView *View;
//#include "GFXOutBar.h"
/*
#include "SelectCam.h"
#include "Kapsul3D.h"
#include "Utils.h"
*/
#define WM_UNSELECTALL WM_USER+9

extern OGLView *View;

//extern HWND hWndMain;
extern char * WriteFilter,*ReadFilter;
extern LibContainer *KLibs;
extern int CurrentCursor;

GenericLib *tmpGen;

int daButs;
HWND StatusBar;

extern CMainFrame* mainf;
extern int FunctionID;

extern bool bCentered;
extern bool bCrossing;
extern bool bSnap;

extern int iEditMode;
bool MovingSel;

extern Desk ClipBoard;
extern GenericLib *CurrentPlug;
extern int daButton;
extern CCoolDialogBar m_wndDialogBar;
#define INSTALLABLE_DRIVER_TYPE_MASK  (PFD_GENERIC_ACCELERATED|PFD_GENERIC_FORMAT)

	enum InfoField {VENDOR,RENDERER,VERSION,ACCELERATION,EXTENSIONS};
	enum ColorsNumber{INDEXED,THOUSANDS,MILLIONS,MILLIONS_WITH_TRANSPARENCY};
	enum ZAccuracy{NORMAL,ACCURATE};

BEGIN_MESSAGE_MAP(MainEdit,CView)
	//{{AFX_MSG_MAP(CView)
    ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_CONFIG_1X2, OnViewConfig1x2)
	ON_COMMAND(ID_VIEW_CONFIG_1X3, OnViewConfig1x3)
	ON_COMMAND(ID_VIEW_CONFIG_2X1, OnViewConfig2x1)
	ON_COMMAND(ID_VIEW_CONFIG_2X2, OnViewConfig2x2)
	ON_COMMAND(ID_VIEW_CONFIG_3X1, OnViewConfig3x1)
	ON_COMMAND(ID_VIEW_CONFIG_FULLSCREEN, OnViewConfigFullscreen)
	ON_COMMAND(ID_VIEW_EXTENDSVIEWS, OnViewExtendsviews)
	ON_COMMAND(ID_VIEW_EXTENDVIEW, OnViewExtendview)
	ON_COMMAND(ID_VIEW_TYPE_BACK, OnViewTypeBack)
	ON_COMMAND(ID_VIEW_TYPE_BOTTOM, OnViewTypeBottom)
	ON_COMMAND(ID_VIEW_TYPE_CAMERA, OnViewTypeCamera)
	ON_COMMAND(ID_VIEW_TYPE_FRONT, OnViewTypeFront)
	ON_COMMAND(ID_VIEW_TYPE_LEFT, OnViewTypeLeft)
	ON_COMMAND(ID_VIEW_TYPE_RIGHT, OnViewTypeRight)
	ON_COMMAND(ID_VIEW_TYPE_TOP, OnViewTypeTop)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
    ON_WM_KEYUP()
	ON_COMMAND(ID_VIEW_RENDERMODE_MAPPED, OnViewRendermodeMapped)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_COMMAND(ID_EDIT_DELETE, OnEditDetete)
	ON_COMMAND(ID_VIEW_RENDERMODE_WIRE, OnViewRendermodeWire)
	ON_COMMAND(ID_EDIT_SELECT_BYNAME, OnViewSelectByName)
	ON_WM_ACTIVATE()
	ON_WM_CHILDACTIVATE()
	ON_MESSAGE(WM_UNSELECTALL,OnWmUnSelectAll)
    ON_WM_KILLFOCUS()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_SKYBOX_LOAD,OnSkyBoxLoad)
	ON_COMMAND(ID_SKYBOX_NONE,OnSkyBoxNone)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_SKYBOX_LOAD, OnUpdateSkyboxLoad)
	ON_WM_MBUTTONDOWN()
//	ON_WM_MBUTTONDBLCLK()
ON_WM_MBUTTONUP()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// ----------------------------------------------------------------------------

IMPLEMENT_DYNCREATE(MainEdit,CView)

MainEdit::MainEdit(HWND daHwnd)
{
	hWnd=daHwnd;

	CircleHui = new Vertex [100];
	temp=new char [256];
	tmp=new char [10];
	TmpName=new char [255];

//    FirstDesk=NULL;
    //NextDesk=NULL;

    // variables

	Snap=false;
	Center=false;
    Crossing=false;
    //gen=NULL;

    PropEnt=NULL;
	IsMoving=false;

	SnapVal.vx=8;
	SnapVal.vy=8;
	SnapVal.vz=8;

	SelectedSel=EDIT_SELECTSINGLE;
    

	dap=new Plan;
}

void AddMainEdit(MainEdit *daMain);
void DelMainEdit(MainEdit *daMain);

MainEdit::MainEdit()
{
	Next=NULL;
	Prev=NULL;
	CircleHui = new Vertex [100];
	temp=new char [256];
	tmp=new char [10];
	TmpName=new char [255];

//    FirstDesk=NULL;
    //NextDesk=NULL;

    // variables

	Snap=false;
	Center=false;
    Crossing=false;
    //gen=NULL;

    PropEnt=NULL;
	IsMoving=false;

	SnapVal.vx=8;
	SnapVal.vy=8;
	SnapVal.vz=8;

	SelectedSel=EDIT_SELECTSINGLE;
	
	
	dap=new Plan;

//	CTestGLDoc *tmpdoc;
/*
	tmpdoc=(CTestGLDoc*)GetDocument();
*/
	dk=NULL;
	AddMainEdit(this);

}

MainEdit::~MainEdit()
{
	delete [] CircleHui;
	delete [] temp;
	delete [] tmp;
	delete [] TmpName;

	delete dap;

	DelMainEdit(this);
}

void MainEdit::DrawViews(void)
{
	Invalidate(TRUE);
}


void MainEdit::Paint()
{
	/*
	PAINTSTRUCT pts;
	BeginPaint(hWnd,&pts);
	if (View!=NULL)
	{
	View->DrawIt();
	DrawGLScene();
	}
//			return TRUE;

	EndPaint(hWnd,&pts);
	*/
}


void MainEdit::KeyDown(int dawParam)
{
	switch (dawParam)
	{
		case VK_SHIFT:
			ButtonState|=ssShift;
			break;
		case VK_CONTROL:
			ButtonState|=ssCtrl;
			break;
	}
}

void MainEdit::KeyUp(int dawParam)
{
	switch (dawParam)
	{
		case VK_SHIFT:
			ButtonState&=!ssShift;
			break;
		case VK_CONTROL:
			ButtonState&=!ssCtrl;
			break;
	}
}

// ----------------------------------------------------------------------------

void MainEdit::FormMouseDown(int Button,int X, int Y)
{
    bool daOk=true;
    bool HasSwapped=false;
    bool IdentEnable=true;
    bool tmpbt;

    daButton=Button;

    if (SetFocus()!=this) 
        return;
/*
	CTestGLView * testglv;

	testglv=(CTestGLView*)(mainf->GetActiveView());

	if (testglv==0) return;

	View=testglv->View;
*/
	//View=CurrentView;

	UpdateHierarchie(dk);
    CDeskDoc *tmpdoc = (CDeskDoc *) GetDocument();
	tmpdoc->SetModifiedFlag(true);

	SetCapture();

	//if (gen!=NULL) gen->SetContext(dk,NULL,View);

	if (FunctionID==EDIT_PLUGINCREATION)
    {
        if (gen->IsCreating())
        {
            daOk=false;
        }

        if (daOk)
        {

        }

    }

    if (IsMoving)
    {
        daOk=false;
    }

    if (daOk)
    {
        if (!dk->SetActive(X,Y))
        {

            View->SwapActive();
			Invalidate(TRUE);
            HasSwapped=true;
			char temp[250];

			Vertex hui=View->GetIsoCoord(X,Y,dk->Active);
			if (bSnap) hui.Snap(SnapVal);

			sprintf(temp,"X: %7.3f Y: %7.3f Z: %7.3f",hui.vx,hui.vy,hui.vz);
			mainf->m_wndStatusBar.SetPaneText( 1, (const char*)temp);		

        }
    }


    if(!HasSwapped)
    {
        if (Button&MK_LBUTTON)
        {
            //if (!IsMoving)
            {


                dk->tmppos[dk->Active]=dk->ViewPos[dk->Active];

                dk->tmpViewSize[dk->Active]=dk->ViewSize[dk->Active];
                dk->TmpViewNg[dk->Active]=dk->ViewNg[dk->Active];
                huitemp=View->GetIsoCoord(X,Y,dk->Active);

				if (bSnap) 
				{
					//Vertex hui2;
					huitemp.Snap(SnapVal);
					/*
					View->Proj((Vertex*)&huitemp,(Vertex*)&hui2,dk->Active);		
					X=hui2.vx;
					Y=hui2.vy;
					*/
				}

                dx=X;
                dy=Y;

                switch(FunctionID)
                {
                    case EDIT_MOVEVIEW:
                        IsMoving=true;
						if (dk->ViewType[dk->Active]==9)
						{

							if (dk->cam[dk->Active]!=NULL)
							{
								dk->cam[dk->Active]->SetMousePos();
								dk->cam[dk->Active]->BeginMove();
							}
						}
						else
						if (dk->ViewType[dk->Active]==8)
						{

							dk->Perspective[dk->Active].SetMousePos();
							dk->Perspective[dk->Active].BeginMove();
						}


                        break;
                    case EDIT_SELECTQUAD:
                        IsMoving=true;
                        break;
                    case EDIT_ROTATEVIEW:

                        IsMoving=true;
                        break;
                    case EDIT_SELECTCIRCLE:
                        IsMoving=true;
                        break;
                    case EDIT_SELECTFENCE:

                        if (dk->cSel->Collapse(dk->Sel,(Vertex*)(&huitemp))!=NULL)
                        {
                            dk->Sel->Close();
							
                            if ((!(Button&MK_CONTROL))&&(!(Button&MK_SHIFT)))
                            {
                                dk->cSel->UnSelectCamera(false);
                                dk->cSel->UnSelectObject(false);
					            dk->cSel->UnSelectShape(false);
                                dk->cSel->UnSelectLights(false);
					            dk->cSel->UnSelectSkeletton(false);
                                dk->DeleteBufVert();
                            }

				            tmpbt=(!(Button&MK_CONTROL));

                            switch (iEditMode)
                            {
                            case 1:
								dk->cSel->SelectObject(dx,dy,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
								dk->cSel->SelectLight(dx,dy,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
								dk->cSel->SelectCam(dx,dy,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
								dk->cSel->SelectShape(dx,dy,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
								dk->cSel->SelectBone(dx,dy,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
    				            //dk->cSel->FenceShapeVert(0,0,X,Y,dk->Sel,tmpbt);
//    				            dk->cSel->FenceSkelVert(X,Y,tmpbt);
//								dk->cSel->FencePatchVert(0,0,X,Y,dk->Sel,tmpbt);
                                break;
                            case 2:
                                dk->cSel->SelectObject(0,0,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_FACE);
								dk->cSel->SelectCam(0,0,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
								dk->cSel->SelectLight(0,0,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
								dk->cSel->SelectShape(0,0,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
								dk->cSel->SelectBone(dx,dy,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_VERTEX);
    				            //dk->cSel->FenceShapeSeg(0,0,X,Y,dk->Sel,tmpbt,bCrossing);
    				            //dk->cSel->FenceBone(0,0,X,Y,dk->Sel,tmpbt,bCrossing);
                                break;
                            case 3:
								dk->cSel->SelectObject(0,0,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
								dk->cSel->SelectCam(0,0,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
								dk->cSel->SelectLight(0,0,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
								dk->cSel->SelectShape(0,0,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
								dk->cSel->SelectBone(dx,dy,X,Y,dk->Sel,tmpbt,bCrossing,SELECT_FENCE,SELECT_WHOLE);
    				            //dk->cSel->FenceShape(0,0,X,Y,dk->Sel,tmpbt,bCrossing);
    				            //dk->cSel->FenceSkel(0,0,X,Y,dk->Sel,bCrossing,tmpbt);
                                break;
                            }

                            if (dk->Sel!=NULL) delete dk->Sel;
                            dk->Sel=new (Shape)(NULL,NULL);
                            IsMoving=false;

                        }
                        else
                        {
							if (dk->Sel==NULL) dk->Sel=new (Shape)(NULL,NULL);

                            if (dk->Sel->Count==0)
                                dk->Sel->AddSegment(&huitemp);

                            dk->Sel->AddSegment(&huitemp);
                            //View->DrawOne(dk->Active);
                            Invalidate(TRUE);
                            IsMoving=true;
                        }
                        break;
                    case EDIT_SELECTSINGLE:
                        if ((!(Button&MK_CONTROL))&&(!(Button&MK_SHIFT)))
                        {
                            dk->cSel->UnSelectCamera(false);
                            dk->cSel->UnSelectObject(false);
					        dk->cSel->UnSelectShape(false);
                            dk->cSel->UnSelectLights(false);
                            //dk->cSel->UnSelectEmitter(false);
					        dk->cSel->UnSelectSkeletton(false);
                            dk->DeleteBufVert();
                        }

				        tmpbt=(!(Button&MK_CONTROL));

                        switch (iEditMode)
                        {
                        case 1:
							dk->cSel->SelectObject(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
							dk->cSel->SelectLight(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
							dk->cSel->SelectCam(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
							dk->cSel->SelectShape(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_VERTEX);
    				        //dk->cSel->SingleShapeVert(X,Y,tmpbt);
//    				        dk->cSel->SingleSkelVert(X,Y,tmpbt);
//							dk->cSel->SinglePatchVert(X,Y,tmpbt);
                            break;
                        case 2:
							dk->cSel->SelectCam(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
							dk->cSel->SelectLight(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
							dk->cSel->SelectObject(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_FACE);
							dk->cSel->SelectShape(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_FACE);
    				        //dk->cSel->SingleShapeSeg(X,Y,tmpbt);
//    				        dk->cSel->SingleBone(X,Y,tmpbt);
                            break;
                        case 3:
							dk->cSel->SelectObject(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
							dk->cSel->SelectLight(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
							dk->cSel->SelectCam(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
							dk->cSel->SelectShape(0,0,X,Y,NULL,tmpbt,bCrossing,SELECT_SINGLE,SELECT_WHOLE);
    				        //dk->cSel->SingleShape(X,Y,tmpbt);
    				        dk->cSel->SingleSkel(X,Y,tmpbt);
                            break;
                        }
                        delete dk->Sel;
                        dk->Sel=new (Shape)(NULL,NULL);

						Invalidate(TRUE);

                        break;
                    case EDIT_PLUGINCREATION:
                        gen->MouseDown(X,Y,huitemp);
                        IsMoving=gen->IsCreating();
                        IsMoving=true;
                        break;
                    case EDIT_ZOOM:
                        IsMoving=true;
                        break;
                    case EDIT_REGIONFIT:
                        IsMoving=true;
                        break;
                    case EDIT_MOVEBUF:
                        IsMoving=true;
                    /*
                        if (!IsMoving)
                        {
                            IsMoving=dk->cSel->SingleCamera(X,Y,true);
                            IsMoving=dk->cSel->SingleObject(X,Y,true);
                        }
                        else
                        {
                            dk->DeleteBufVert();
                            IsMoving=false;
                        }
                        */
						sprintf(temp,"X: 0.00 Y: 0.00 Z: 0.00");
						mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		

						//SetCapture(hWndEdit);
                        break;
                    case EDIT_ROTATEBUF:
                        View->Proj((Vertex*)&dk->Axis,(Vertex*)&Getng,dk->Active);
                        View->Proj((Vertex*)&huitemp,(Vertex*)&Getng2,dk->Active);

                        ngl=ng(Getng.vx,Getng.vy,Getng2.vx,Getng2.vy);
                        dap->PlanOfView(View,dk->Active);
						//SetCapture(hWndEdit);

						sprintf(temp,"Angle 0 degs");
						mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		
  
 
                        IsMoving=true;
                        break;
					case EDIT_SCALEBUF:
						
						dap->PlanOfView(View,dk->Active);
						IsMoving=true;

						sprintf(temp,"X: 100%% Y: 100%% Z: 100%%");
						mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		

						break;
                    case EDIT_PUTAXIS:
                        dk->SetAxis(huitemp);
						
                        //DrawViews();
						Invalidate(TRUE);
						//UpdateModifiedTabDesk();
                        break;
                }
            }
        }
        else
        {
            if (gen!=NULL)
            {
                if (gen->IsCreating())
                {
                    gen->MouseAbort(X,Y,huitemp);
                    IsMoving=gen->IsCreating();
                    IsMoving=true;
                    //DrawViews();
					Invalidate(TRUE);

                }
                else
                {
                    //MainContextMenu->Popup(X,Y);
                    ShowContextMenu(X,Y);
                }
            }
            else
            {
                //MainContextMenu->Popup(X,Y);
                ShowContextMenu(X,Y);
            }
        }
    }

    if (FunctionID==EDIT_PLUGINCREATION)
    {
        if (gen->IsCreating())
        {
            IdentEnable=false;
        }
    }

    if (IsMoving)
    {
        IdentEnable=false;
    }
}
//---------------------------------------------------------------------------

void MainEdit::FormMouseMove(int Button, int X, int Y)
{
    Vertex hui,hui2,hui3;
    double tst,Length;
    double daNgx,daNgy;
    int i;
	Vertex ScaleVal;
	static int omx, omy, mx, my;
    daButton=Button;


	// status bar
    hui=View->GetIsoCoord(X,Y,dk->Active);
	if ((bSnap)&&(FunctionID!=EDIT_MOVEVIEW)) hui.Snap(SnapVal);

	sprintf(temp,"X: %7.3f Y: %7.3f Z: %7.3f",hui.vx,hui.vy,hui.vz);
	mainf->m_wndStatusBar.SetPaneText( 1, (const char*)temp);		



    if ((IsMoving)||(FunctionID==EDIT_PLUGINCREATION))
    {
        switch(FunctionID)
        {
            case EDIT_MOVEVIEW:
                hui=hui-huitemp;
                if (dk->ViewType[dk->Active]==9)
                {

                    if (dk->cam[dk->Active]!=NULL)
                    {
						mx = X;
						my = Y;
						dk->cam[dk->Active]->SetMouse(mx, my,640,400);
                        DrawViews();
                    }
                }
                else
                {
					if (dk->ViewType[dk->Active]==8)
					{
						mx = X;
						my = Y;
						dk->Perspective[dk->Active].SetMouse(mx, my,640,400);
						dk->Perspective[dk->Active].SetCamera();
                        DrawViews();

					}
					else
					{
	                    dk->ViewPos[dk->Active]-=hui;
	                    Invalidate(TRUE);
					}

                }
                break;
            case EDIT_SELECTQUAD:
                hui2=View->GetIsoCoord(dx,Y,dk->Active);
				if (bSnap) hui2.Snap(SnapVal);

                hui3=View->GetIsoCoord(X,dy,dk->Active);
				if (bSnap) hui3.Snap(SnapVal);

                if (dk->Sel!=NULL) delete dk->Sel;
                dk->Sel=new (Shape)(NULL,NULL);
                dk->Sel->IsQuad(huitemp,hui2,hui,hui3);
                //View->DrawOne(dk->Active);
                Invalidate(TRUE);
                break;
            case EDIT_SELECTCIRCLE:
                Length=Pythagore((X-dx),(Y-dy));
                for (i=0;i<100;i++)
				{
                    CircleHui[i]=View->GetIsoCoord((int)(dx+cos((i*PI)/50)*Length),(int)(dy+sin((i*PI)/50)*Length),dk->Active);
					//if (bSnap) CircleHui[i].Snap(SnapVal);

				}

                delete dk->Sel;
                dk->Sel=new (Shape)(NULL,NULL);
                dk->Sel->IsCircle(100,CircleHui);

                //View->DrawOne(dk->Active);
                Invalidate(TRUE);
                break;
            case EDIT_SELECTFENCE:
                dk->Sel->SetSegment(&hui);
                //View->DrawOne(dk->Active);
                Invalidate(TRUE);
                break;

            case EDIT_ROTATEVIEW:
                if (dk->ViewType[dk->Active]==9)
                {
                    if (dk->cam[dk->Active]!=NULL)
                    {
//                        dk->cam[dk->Active]->FreeTargeted=true;
//                        View->cam[View->Active]->SetSource(View->cam[View->Active]->Source-hui);
//                        View->cam[View->Active]->SetDest(hui);
                        daNgx=180;
                        daNgx/=265;
                        daNgx*=(Y-dy);//X-dx);
                        daNgy=180;
                        daNgy/=250;
                        daNgy*=(X-dx);//(Y-dy);
                        /*
                        dk->cam[dk->Active]->ngx=daNgx;
                        dk->cam[dk->Active]->ngy=daNgy;
                        */
                        dk->cam[dk->Active]->SetCamera();
                        //DrawViews();
//                        dk->cam[dk->Active]->FreeTargeted=true;
                    }
                }
                else
                {
                    daNgx=180;
                    daNgx/=265;
                    daNgx*=(X-dx);
                    daNgy=180;
                    daNgy/=250;
                    daNgy*=(Y-dy);
                    dk->ViewNg[dk->Active].vz=dk->TmpViewNg[dk->Active].vz+daNgx;
                    dk->ViewNg[dk->Active].vx=dk->TmpViewNg[dk->Active].vx+daNgy;
                    //View->DrawOne(dk->Active);
                    Invalidate(TRUE);
                }
                break;

            case EDIT_ZOOM:
                tst=(Y-dy);
                if (tst==0)
                {
                    tst=1;
                }
                else
                {
                    if (tst>0)
                    {
                        tst=pow(1.05,tst);
                    }
                    else
                    {
                        tst=1/(-tst);
                    }
                }

                dk->ViewSize[dk->Active].vx=dk->tmpViewSize[dk->Active].vx*tst;
                dk->ViewSize[dk->Active].vy=dk->tmpViewSize[dk->Active].vy*tst;
                //View->DrawOne(dk->Active);
                Invalidate(TRUE);
                break;
            case EDIT_REGIONFIT:
                hui2=View->GetIsoCoord(dx,Y,dk->Active);
				if (bSnap) hui2.Snap(SnapVal);
                hui3=View->GetIsoCoord(X,dy,dk->Active);
				if (bSnap) hui3.Snap(SnapVal);

                delete dk->Sel;
                dk->Sel=new (Shape)(NULL,NULL);
                dk->Sel->IsQuad(huitemp,hui2,hui,hui3);
                //View->DrawOne(dk->Active);
                Invalidate(TRUE);
                break;
            case EDIT_PLUGINCREATION:

                gen->MouseMove(X,Y,hui);
                if (gen->IsCreating()) 
				{
					//Invalidate(TRUE);
                    DrawViews();
				}
                    //DrawViews();
                break;
            case EDIT_MOVEBUF:
				sprintf(temp,"X: %7.2f Y: %7.2f Z: %7.2f",(hui-huitemp).vx,(hui-huitemp).vy,(hui-huitemp).vz);
				mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		

                dk->TranslateBuf(hui-huitemp);
                //DrawViews();
				Invalidate(TRUE);

//                IsMoving=true;
                break;
            case EDIT_ROTATEBUF:
				double tempng;
                View->Proj((Vertex*)&hui,(Vertex*)&Getng2,dk->Active);

				tempng=int(((ng(Getng.vx,Getng.vy,Getng2.vx,Getng2.vy)-ngl)*180)/PI);
                dap->MatrixRotateNormale(((tempng*PI)/180));

				sprintf(temp,"Angle %d degs",(int)tempng);
				mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		

                dk->RotateBuf(dap,dk->Axis);
                //DrawViews();
				Invalidate(TRUE);
                break;

			case EDIT_SCALEBUF:

				

				//View->Proj((Vertex*)&hui,(Vertex*)&Getng2,dk->Active);

				ScaleVal.vx=(X-dx)+100;
				ScaleVal.vx=((ScaleVal.vx<=0)?0:(ScaleVal.vx/100));

				ScaleVal.vy=(Y-dy)+100;
				ScaleVal.vy=((ScaleVal.vy<=0)?0:(ScaleVal.vy/100));

				


				ScaleVal.vz=1;

				if (Button&MK_CONTROL) 
				{
					ScaleVal.vy=ScaleVal.vx;
					if (Button&MK_SHIFT)
					{
						ScaleVal.vz=ScaleVal.vx;
					}
				}
				

				sprintf(temp,"X: %d%% Y: %d%% Z: %d%%",(int)(ScaleVal.vx*100),(int)(ScaleVal.vy*100),(int)(ScaleVal.vz*100));
				mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		

				dap->ScaleMatrix();
				dk->ScaleBuf(dap,dk->Axis,ScaleVal);
				//DrawViews();
				Invalidate(TRUE);

				break;


            default:
                break;
        }
    }




}
//---------------------------------------------------------------------------

void MainEdit::FormMouseUp(int Button, int X, int Y)
{
    Vertex hui,hui2,hui3,hui4,hui5;
    bool IdentEnable=true;
	bool tmpbt;
    daButton=Button;
    CDeskDoc *tmpdoc;
	int TypeSelqc;


	ReleaseCapture();

    hui=View->GetIsoCoord(X,Y,dk->Active);

	if (bSnap) 
	{
		hui.Snap(SnapVal);
	}

    if (IsMoving)
    {
        switch(FunctionID)
        {

            case EDIT_MOVEVIEW:
				{
					if (dk->ViewType[dk->Active]==9)
					{
						if (dk->cam[dk->Active]!=NULL)
							dk->cam[dk->Active]->EndDraw();
					}
					else
					{
						if (dk->ViewType[dk->Active]==8)
							dk->Perspective[dk->Active].EndDraw();
					}


					IsMoving=false;
				}

				break;

            case EDIT_SELECTFENCE:
                break;
            case EDIT_REGIONFIT:
                hui2=View->GetIsoCoord(X,dy,dk->Active);
				if (bSnap) hui2.Snap(SnapVal);
                //dk->ViewPos[dk->Active]=(hui+((huitemp-hui)/2));
				dk->ViewPos[dk->Active]=huitemp;
				dk->ViewPos[dk->Active]-=hui;
				dk->ViewPos[dk->Active]/=2;
				dk->ViewPos[dk->Active]+=hui;

                // en x
                hui3.vx=Pythagore3D(huitemp,hui2);
                // en y
                hui3.vy=Pythagore3D(hui2,hui);

				if ((hui3.vx/dk->ViewEnd[dk->Active].x)>(hui3.vy/dk->ViewEnd[dk->Active].y))
				{
					hui3.vx/=2;
					hui3.vx*=1.1;
					dk->ViewSize[dk->Active]=hui3;
				}
				else
				{

					hui3.vx=dk->ViewEnd[dk->Active].x;
					hui3.vx/=dk->ViewEnd[dk->Active].y;
					hui3.vx*=hui3.vy;
					hui3.vx/=2;
					hui3.vx*=1.1;
					dk->ViewSize[dk->Active]=hui3;
				}

                delete dk->Sel;
                dk->Sel=new (Shape)(NULL,NULL);
                IsMoving=false;
                break;
            case EDIT_PLUGINCREATION:
                gen->MouseUp(X,Y,huitemp);
                IsMoving=gen->IsCreating();
                IsMoving=false;
                tmpdoc = (CDeskDoc *) GetDocument();
                tmpdoc->SetModifiedFlag(TRUE);

                break;
			case EDIT_SELECTCIRCLE:
            case EDIT_SELECTQUAD:
                if ((!(Button&MK_CONTROL))&&(!(Button&MK_SHIFT)))
                {
                    dk->cSel->UnSelectCamera(false);
                    dk->cSel->UnSelectObject(false);
					dk->cSel->UnSelectShape(false);
                    dk->cSel->UnSelectLights(false);
                    //dk->cSel->UnSelectEmitter(false);
					dk->cSel->UnSelectSkeletton(false);
					dk->cSel->UnSelectPatch(false);

                    dk->DeleteBufVert();
                }

				tmpbt=(!(Button&MK_CONTROL));
				TypeSelqc=((FunctionID==EDIT_SELECTQUAD)?SELECT_QUAD:SELECT_CIRCLE);

                switch (iEditMode)
                {
                case 1:
					dk->cSel->SelectObject(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
					dk->cSel->SelectCam(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
					dk->cSel->SelectLight(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
					dk->cSel->SelectShape(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_VERTEX);
					if (TypeSelqc==SELECT_QUAD)
					{
    					//dk->cSel->QuadShapeVert(dx,dy,X,Y,tmpbt);
    					//dk->cSel->QuadSkelVert(dx,dy,X,Y,tmpbt);
//						dk->cSel->QuadPatchVert(dx,dy,X,Y,tmpbt);
					}
					else
					{
    					//dk->cSel->CircleShapeVert(dx,dy,X,Y,tmpbt);
    					//dk->cSel->CircleSkelVert(dx,dy,X,Y,tmpbt);
//						dk->cSel->CirclePatchVert(dx,dy,X,Y,tmpbt);
					}
                    break;
                case 2:
					dk->cSel->SelectObject(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_FACE);
					dk->cSel->SelectLight(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
					dk->cSel->SelectCam(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
					dk->cSel->SelectShape(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
					if (TypeSelqc==SELECT_QUAD)
					{
    					//dk->cSel->QuadShapeSeg(dx,dy,X,Y,tmpbt,bCrossing);
//    					dk->cSel->QuadBone(dx,dy,X,Y,tmpbt,bCrossing);
					}
					else
					{
    					//dk->cSel->CircleShapeSeg(dx,dy,X,Y,tmpbt,bCrossing);
//    					dk->cSel->CircleBone(dx,dy,X,Y,tmpbt,bCrossing);
					}
                    break;
                case 3:
					dk->cSel->SelectObject(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
					dk->cSel->SelectCam(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
					dk->cSel->SelectLight(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
					dk->cSel->SelectShape(dx,dy,X,Y,NULL,tmpbt,bCrossing,TypeSelqc,SELECT_WHOLE);
					if (TypeSelqc==SELECT_QUAD)
					{
    					//dk->cSel->QuadShape(dx,dy,X,Y,tmpbt,bCrossing);
    					dk->cSel->QuadSkel(dx,dy,X,Y,tmpbt,bCrossing);
					}
					else
					{
    					//dk->cSel->CircleShape(dx,dy,X,Y,tmpbt,bCrossing);
    					dk->cSel->CircleSkel(dx,dy,X,Y,tmpbt,bCrossing);
					}
                    break;
                }

                delete dk->Sel;
                dk->Sel=new (Shape)(NULL,NULL);

				//DrawViews();
                Invalidate(TRUE);
                IsMoving=false;
                break;
/*
            case EDIT_SELECTCIRCLE:
                if ((!(Button&MK_CONTROL))&&(!(Button&MK_SHIFT)))
                {
                    dk->cSel->UnSelectCamera(false);
                    dk->cSel->UnSelectObject(false);
					dk->cSel->UnSelectShape(false);
                    dk->cSel->UnSelectLights(false);
                    //dk->cSel->UnSelectEmitter(false);
					dk->cSel->UnSelectSkeletton(false);
					dk->cSel->UnSelectPatch(false);

                    dk->DeleteBufVert();
                }

				tmpbt=(!(Button&MK_CONTROL));

                switch (iEditMode)
                {
                case 1:
                    //dk->cSel->CircleObjVert(dx,dy,X,Y,tmpbt);
					dk->cSel->SelectObject(dx,dy,X,Y,NULL,tmpbt,false,SELECT_CIRCLE,SELECT_VERTEX);
    				dk->cSel->CircleShapeVert(dx,dy,X,Y,tmpbt);
//                    dk->cSel->CircleLightVert(dx,dy,X,Y,tmpbt,bCrossing);
    				//dk->cSel->QuadSkelVert(dx,dy,X,Y,tmpbt);
//                    dk->cSel->CircleCamVert(dx,dy,X,Y,tmpbt,bCrossing);
					dk->cSel->CirclePatchVert(dx,dy,X,Y,tmpbt);
                    break;
                case 2:
                    //dk->cSel->CircleObjFace(dx,dy,X,Y,tmpbt,bCrossing);
					dk->cSel->SelectObject(dx,dy,X,Y,NULL,tmpbt,false,SELECT_CIRCLE,SELECT_FACE);
    				dk->cSel->CircleShapeSeg(dx,dy,X,Y,tmpbt,bCrossing);
//                    dk->cSel->CircleLight(dx,dy,X,Y,tmpbt,bCrossing);
    				dk->cSel->CircleBone(dx,dy,X,Y,tmpbt,bCrossing);
//                    dk->cSel->CircleCam(dx,dy,X,Y,tmpbt,bCrossing);
                    break;
                case 3:
//                    dk->cSel->QuadObject(dx,dy,X,Y,tmpbt);
                    //dk->cSel->CircleObject(dx,dy,X,Y,bCrossing,tmpbt);
					dk->cSel->SelectObject(dx,dy,X,Y,NULL,tmpbt,false,SELECT_CIRCLE,SELECT_WHOLE);
    				dk->cSel->CircleShape(dx,dy,X,Y,tmpbt,bCrossing);
//                    dk->cSel->CircleLight(dx,dy,X,Y,tmpbt,bCrossing);
    				dk->cSel->CircleSkel(dx,dy,X,Y,tmpbt,bCrossing);
//                    dk->cSel->CircleCam(dx,dy,X,Y,tmpbt,bCrossing);
                    break;
                }

                delete dk->Sel;
                dk->Sel=new (Shape)(NULL,NULL);

				//DrawViews();
                Invalidate(TRUE);
                IsMoving=false;
                break;
				*/
			case EDIT_SCALEBUF:
			case EDIT_ROTATEBUF:
            case EDIT_MOVEBUF:
//                dk->DeleteBufVert();
				sprintf(temp,"");
				mainf->m_wndStatusBar.SetPaneText( 2, (const char*)temp);		

				dk->UpdateBuf();
				ReleaseCapture();
                IsMoving=false;

                tmpdoc = (CDeskDoc *) GetDocument();
                tmpdoc->SetModifiedFlag(TRUE);
                break;



            default:
                IsMoving=false;

        }
    }
    //View->DrawOne(dk->Active);
    Invalidate(TRUE);

    if (FunctionID==EDIT_PLUGINCREATION)
    {
        if (gen->IsCreating())
        {
            IdentEnable=false;
        }
    }

    if (IsMoving)
    {
        IdentEnable=false;
    }
}


void MainEdit::SetFunc(int daFunctionID)
{
	FunctionID=daFunctionID;
	
    if (FunctionID!=EDIT_PLUGINCREATION)
        gen->Process(KM_UNSETPLUGIN,0,0);

	switch(FunctionID)
	{

		case EDIT_PUTAXIS:
			LStatus("Click to put axis in new location.");
			break;
		case EDIT_ROTATEVIEW:
			LStatus("Click and drag to rotate View->");
			break;
		case EDIT_MOVEVIEW:
			LStatus("Click and drag to move View->");
			break;
		case EDIT_ZOOM:
			LStatus("Click and drag to zoom/unzoom View->");
			break;
		case EDIT_REGIONFIT:
			LStatus("Select region to zoom in.");
			break;
		case EDIT_SELECTSINGLE:
			LStatus("Click to select [SHIFT] add selection [CTRL] remove.");
			break;
		case EDIT_SELECTFENCE:
			LStatus("Click to create a selection fence [SHIFT] add selection [CTRL] remove.");
			break;
		case EDIT_SELECTQUAD:
			LStatus("Click and drag to create a selection quad [SHIFT] add selection [CTRL] remove.");
			break;
		case EDIT_SELECTCIRCLE:
			LStatus("Click and drag to create a selection circle [SHIFT] add selection [CTRL] remove.");
			break;
		case EDIT_ROTATEBUF:
			LStatus("Rotate selection.");
			break;
		case EDIT_SCALEBUF:
			LStatus("Scale selection.[SHIFT] uniform XY [CONTROL][SHIFT] uniform XYZ");
			break;
		case EDIT_MOVEBUF:
			LStatus("Move selection.");
			break;
		case EDIT_PLUGINCREATION:
			//LStatus("Plug-IN !!!"));
			break;

		default:
			break;


	}
	
}
/*

void  TMainForm::ShowHint(char *daString)
{
    String trans;
    trans=daString;
    StatusBar->Panels->Items[2]->Text=trans;
}
*/
//---------------------------------------------------------------------------

void  MainEdit::ShowContextMenu(int X,int Y)
{
	
    Camera *daCam;
    //Emitter *daEmit;
    CLight *daLight;
    Skeletton *daSkel;
    Shape *daShape;
    Object *daObject;
    
	CMenu ctx,*ctx2;
	POINT mypt;

	
	strcpy(TmpName,"");

    tmpGen=NULL;
    PropEnt=NULL;
    //switch(SendDlgItemMessage(hWndMain,IDC_ENTITY,CB_GETCURSEL,0,0))
    switch(mainf->m_wndMode.m_wndSnap.GetCurSel())
    {
        // all
        case 0:
            daCam=dk->cSel->GetCamera(X,Y);
            if (daCam!=NULL)
            {
                strcpy(TmpName,daCam->Name);
                tmpGen=KLibs->CamProp;
                PropEnt=daCam;
            }
            else
            {
                daShape=dk->cSel->GetShape(X,Y);
                if (daShape!=NULL)
                {
                    strcpy(TmpName,daShape->Name);
                    tmpGen=KLibs->ShapeProp;
                    PropEnt=daShape;
                }
                else
                {
                    daLight=dk->cSel->GetLight(X,Y);
                    if (daLight!=NULL)
                    {
                        strcpy(TmpName,daLight->Name);
                        tmpGen=KLibs->LightProp;
                        PropEnt=daLight;
                    }
                    else
                    {
                        daObject=dk->cSel->GetObjectByTriangle(X,Y);
                        if (daObject!=NULL)
                        {
                            strcpy(TmpName,daObject->Name);
                            tmpGen=(GenericLib*)0x1;//KLibs->ObjectProp; // Big hack
                            PropEnt=daObject;
                        }
                        else
                        {
                            daSkel=dk->cSel->GetSkeletton(X,Y);
                            if (daLight!=NULL)
                            {
                                strcpy(TmpName,daSkel->Name);
                                tmpGen=KLibs->SkelProp;
                                PropEnt=daSkel;
                            }
                        }
                    }
                }
            }
            break;

        // camera
        case 1:
            daCam=dk->cSel->GetCamera(X,Y);
            if (daCam!=NULL)
            {
                strcpy(TmpName,daCam->Name);
                tmpGen=KLibs->CamProp;
                PropEnt=daCam;
            }
            break;
        // Shape
        case 2:
            daShape=dk->cSel->GetShape(X,Y);
            if (daShape!=NULL)
            {
                strcpy(TmpName,daShape->Name);
                tmpGen=KLibs->ShapeProp;
                PropEnt=daShape;
            }
            break;

        // light
        case 3:
            daLight=dk->cSel->GetLight(X,Y);
            if (daLight!=NULL)
            {
                strcpy(TmpName,daLight->Name);
                tmpGen=KLibs->LightProp;
                PropEnt=daLight;
            }
            break;
        //Object
        case 4:
            daObject=dk->cSel->GetObjectByTriangle(X,Y);
            if (daObject!=NULL)
            {
                strcpy(TmpName,daObject->Name);
                tmpGen=(GenericLib*)0x1;//KLibs->ObjectProp; Big hack
                PropEnt=daObject;
            }
            break;

        //Skeletton
        case 5:
            daSkel=dk->cSel->GetSkeletton(X,Y);
            if (daSkel!=NULL)
            {
                strcpy(TmpName,daSkel->Name);
                tmpGen=KLibs->SkelProp;
                PropEnt=daSkel;
            }
            break;

        // Emitter
/*
        case 4:
            daEmit=dk->cSel->GetEmitter(X,Y);
            if (daEmit!=NULL)
            {
                strcpy(TmpName,daEmit->Name);
                tmpGen=KLibs->EmiProp;
                PropEnt=daEmit;
            }
            break;
            */
    }

	ctx.LoadMenu(IDR_CONTEXT);
    ctx2=ctx.GetSubMenu(0);
	mypt.x=X;
	mypt.y=Y;
	ClientToScreen(&mypt);

    if (tmpGen==NULL)
    {
		ctx2->EnableMenuItem(ID_PROPERTIES,MF_GRAYED);

		MENUITEMINFO         mii;       
		ZeroMemory(&mii, sizeof(mii));       
		mii.cbSize = sizeof(mii);       
		mii.fMask = MIIM_TYPE | MIIM_STATE;       
		mii.fType = MFT_STRING;       
		mii.fState = MFS_ENABLED;       
		mii.dwTypeData = TmpName;
		
        ctx2->ModifyMenu(ID_NAME,MF_BYCOMMAND|MF_STRING,0,TmpName);


    }
    else
    {

    }

    ctx2->TrackPopupMenu(0,mypt.x,mypt.y,this);
	DestroyMenu(*ctx2);
	
    //MainContextMenu->Popup(X,Y);
}

/////////////////////////////////////////////////////////////////////////////
// CTestGLView message handlers

void MainEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	/*
// remember where we clicked
	MouseDownPoint=point;
// capture mouse movements even outside window borders
	SetCapture();
	*/
	FormMouseDown((int)nFlags,(int)point.x,(int)point.y);
}

void MainEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	/*
// forget where we clicked
	MouseDownPoint=CPoint(0,0);
// release mouse capture
	ReleaseCapture();
	*/
	FormMouseUp((int)nFlags,(int)point.x,(int)point.y);
}


void MainEdit::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	FormMouseDown((int)nFlags,(int)point.x,(int)point.y);
}

void MainEdit::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	FormMouseUp((int)nFlags,(int)point.x,(int)point.y);
}

void MainEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	/*
// check if we have captured the mouse
	if (GetCapture()==this)
	{
// increment the object rotation angles
		X_Angle+=double(point.y-MouseDownPoint.y)/3.6;
		Y_Angle+=double(point.x-MouseDownPoint.x)/3.6;
// redraw the view
		Invalidate(TRUE);
// remember the mouse point
		MouseDownPoint=point;
	};
	*/
	FormMouseMove((int)nFlags,(int)point.x,(int)point.y);
}


bool MainEdit::ToggleSnap(void)
{
	Snap=!Snap;
	return Snap;
}
bool MainEdit::ToggleWindow(void)
{
	Crossing=!Crossing;
	return Crossing;
}
bool MainEdit::ToggleCenter(void)
{
	Center=!Center;
	return Center;
}

int MainEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1) return -1;
	
// OpenGL rendering context creation
	//PIXELFORMATDESCRIPTOR pfd;
    int         n;
    
// initialize the private member
	m_pCDC= new CClientDC(this);

// choose the requested video mode
	static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
        1,								// version number
        PFD_DRAW_TO_WINDOW |			// support window
        PFD_SUPPORT_OPENGL |			// support OpenGL
        PFD_DOUBLEBUFFER,				// double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        16,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
// let the user change some parameters if he wants
    /*
	BOOL bDoublBuf;
	ColorsNumber cnum;
	ZAccuracy zdepth;
	//VideoMode(cnum,zdepth,bDoublBuf);

	cnum=MILLIONS;
	zdepth=NORMAL;
	bDoublBuf=TRUE;

//set the changes
	if(bDoublBuf) pfd.dwFlags=PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |PFD_DOUBLEBUFFER;
	else pfd.dwFlags=PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;

    pfd.cColorBits=24;
    pfd.cDepthBits=16;
*/
// ask the system for such video mode
    ASSERT(m_pCDC != NULL);
    int pixelformat;
	if ( (pixelformat = ChoosePixelFormat(m_pCDC->GetSafeHdc(), &pfd)) == 0 )
    {
        AfxMessageBox("ChoosePixelFormat failed");
        return FALSE;
    }

// try to set this video mode    
	if (SetPixelFormat(m_pCDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
// the requested video mode is not available so get a default one
        pixelformat = 1;	
		if (DescribePixelFormat(m_pCDC->GetSafeHdc(), pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &pfd)==0)
		{
// neither the requested nor the default are available: fail
			AfxMessageBox("SetPixelFormat failed (no OpenGL compatible video mode)");
			return FALSE;
		}
    }	
// ask the system if the video mode is supported
    n=::GetPixelFormat(m_pCDC->GetSafeHdc());
    ::DescribePixelFormat(m_pCDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

// create a palette if the requested video mode has 256 colors (indexed mode)
//    CreateRGBPalette();

// link the Win Device Context with the OGL Rendering Context
    m_hRC = wglCreateContext(m_pCDC->GetSafeHdc());

// specify the target DeviceContext (window) of the subsequent OGL calls
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	View->PreCalc();

// performs default setting of rendering mode,etc..
	glEnable(GL_DEPTH_TEST);	// Z-Buffer
	glEnable(GL_CULL_FACE);		// Backface Culling
	glEnable(GL_TEXTURE_2D);	// Texturing
		
	// Solid polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
/*		
	// Enable lighting
	glEnable(GL_LIGHTING);
 
	// Lighting settings
	GLfloat AmbientLight[]        = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat DiffuseLight[]        = { 0.75f, 0.75f, 0.75f, 1.0f };
	GLfloat OtherReflectance[]    = { 1.75f, 1.75f, 1.75f, 1.0f };
	GLfloat LightPos[]            = { 0.0f, 0.0f, 0.0f, 1.0f };
			
	// Define light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);	  // Ambient
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);	  // Diffuse
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);	  // Position
	
	glEnable(GL_LIGHT0);

	// Ambient reflectance settings
	glMaterialfv(GL_FRONT, GL_AMBIENT, OtherReflectance);
	
	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
// free the target DeviceContext (window)
    //wglMakeCurrent(NULL,NULL);
/*
    CSkyBox *ds;

    ds=new CSkyBox();
*/
    //glEnable(GL_TEXTURE_2D);
	
	return 0;
}
void MainEdit::OnDraw(CDC* pDC)
{
	/*
	CTestGLDoc *tmpdoc;

	tmpdoc=(CTestGLDoc *)GetDocument();
	dk=tmpdoc->dk;
	*/
	View->dk=dk;
	static BOOL 	bBusy = FALSE;
// use the semaphore to enter this critic section
	if(bBusy) return;
	bBusy = TRUE;

// specify the target DeviceContext of the subsequent OGL calls
	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// call the virtual drawing procedure (to be overridden by user)
	//OnDrawGL();

	View->DrawIt();

// execute OGL commands (flush the OGL graphical pipeline)
	glFinish();

// if double buffering is used it's time to swap the buffers
	SwapBuffers(m_pCDC->GetSafeHdc());
	
// turn the semaphore "green"
	bBusy = FALSE;

// free the target DeviceContext (window)
//    wglMakeCurrent(NULL,NULL);



	// CView::OnDraw(pDC); //????

}


void MainEdit::OnDestroy() 
{
// specify the target DeviceContext (window) of the subsequent OGL calls
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// release definitely OGL Rendering Context
	if (m_hRC!=NULL) ::wglDeleteContext(m_hRC);

// Select our palette out of the dc
	CPalette palDefault;
	palDefault.CreateStockObject(DEFAULT_PALETTE);
	m_pCDC->SelectPalette(&palDefault, FALSE);

// destroy Win Device Context
	if(m_pCDC) delete m_pCDC;

// finally call the base function
	CView::OnDestroy();	
}

BOOL MainEdit::PreCreateWindow(CREATESTRUCT& cs) 
{
// these styles are requested by OpenGL
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

// these styles are meant for a use of this class in a MDI application
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);

	return CView::PreCreateWindow(cs);
}


BOOL MainEdit::OnEraseBkgnd(CDC* pDC) 
{
// OGL has his own background erasing so tell Windows to skip
	return TRUE;
}


void MainEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
//	CTestGLView::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	//Invalidate(TRUE);
	
}

void MainEdit::OnSize(UINT nType, int cx, int cy) 
{

	CDeskDoc *tmpdoc;

	if (dk==NULL)
	{
		tmpdoc=(CDeskDoc *)GetDocument();
		dk=tmpdoc->dk;
	}

	View->dk=dk;

	dk->Height=cy;
	dk->Width=cx;
	dk->Left=0;
	dk->Top=0;

	dk->ComputeSize();

	CView::OnSize(nType, cx, cy);

}
BOOL MainEdit::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
    /*
	ASSERT(m_hMouseCursor!=NULL);
	::SetCursor(m_hMouseCursor);
    */
	if (CurrentCursor==0)
		::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_STANDARD)));
	else
		::SetCursor((HCURSOR)CurrentCursor);
	/*
    switch(CurrentCursor)
    {
    case 1:
        ::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SELSINGLE)));
        break;
    case 2:
        ::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SELSINGLEFOUND)));
        break;
    default:
        ::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_STANDARD)));
        break;

    }
	*/
	return TRUE;
}
void MainEdit::OnViewConfig1x2() 
{
	dk->daViewMode=VIEW_MODE1x2a;
	dk->ComputeSize();
	Invalidate(TRUE);
	
}

void MainEdit::OnViewConfig1x3() 
{
	dk->daViewMode=VIEW_MODE1x3a;
	dk->ComputeSize();
	Invalidate(TRUE);
}

void MainEdit::OnViewConfig2x1() 
{
	dk->daViewMode=VIEW_MODE1x2b;
	dk->ComputeSize();
	Invalidate(TRUE);
}

void MainEdit::OnViewConfig2x2() 
{
	dk->daViewMode=VIEW_MODE2x2;
	dk->ComputeSize();
	Invalidate();
}

void MainEdit::OnViewConfig3x1() 
{
	dk->daViewMode=VIEW_MODE1x3b;
	dk->ComputeSize();
	Invalidate(TRUE);
}

void MainEdit::OnViewConfigFullscreen() 
{
	dk->FullScreen=!dk->FullScreen;
	Invalidate(TRUE);
}

void MainEdit::OnViewExtendsviews() 
{
	Vertex hui,huitemp,hui2,hui3,Min,Max;

	if (dk->GetMinOf(STAT_OBJECT,(Vertex*)&Min) &&
		dk->GetMaxOf(STAT_OBJECT,(Vertex*)&Max) )
	{


		for (int i=0;i<4;i++)
		{

			dk->ViewPos[i]=Min+((Max-Min)/2);
			//TmpEcran=(Max-Min);

			View->Proj((Vertex*)&Min,(Vertex*)&huitemp,i);
			View->Proj((Vertex*)&Max,(Vertex*)&hui,i);


			hui2=View->GetIsoCoord(hui.vx,huitemp.vy,i);
			hui=View->GetIsoCoord(hui.vx,hui.vy,i);


			huitemp=View->GetIsoCoord(huitemp.vx,huitemp.vy,i);


			hui3.vx=Pythagore3D(huitemp,hui2);
			// en y
			hui3.vy=Pythagore3D(hui2,hui);


			if ((hui3.vx/dk->ViewEnd[i].x)>(hui3.vy/dk->ViewEnd[i].y))
			{
				hui3.vx/=2;
				hui3.vx*=1.1;
				dk->ViewSize[i]=hui3;
			}
			else
			{

				hui3.vx=dk->ViewEnd[i].x;
				hui3.vx/=dk->ViewEnd[i].y;
				hui3.vx*=hui3.vy;
				hui3.vx/=2;
				hui3.vx*=1.1;
				dk->ViewSize[i]=hui3;
			}
		}
		Invalidate(TRUE);
	}
}

void MainEdit::OnViewExtendview() 
{
	Vertex hui,huitemp,hui2,hui3,Min,Max;

	if (dk->GetMinOf(STAT_OBJECT,(Vertex*)&Min) &&
		dk->GetMaxOf(STAT_OBJECT,(Vertex*)&Max) )
	{


		dk->ViewPos[dk->Active]=Min+((Max-Min)/2);
		//TmpEcran=(Max-Min);

		View->Proj((Vertex*)&Min,(Vertex*)&huitemp,dk->Active);
		View->Proj((Vertex*)&Max,(Vertex*)&hui,dk->Active);


		hui2=View->GetIsoCoord(hui.vx,huitemp.vy,dk->Active);
		hui=View->GetIsoCoord(hui.vx,hui.vy,dk->Active);


		huitemp=View->GetIsoCoord(huitemp.vx,huitemp.vy,dk->Active);


		hui3.vx=Pythagore3D(huitemp,hui2);
		// en y
		hui3.vy=Pythagore3D(hui2,hui);


		if ((hui3.vx/dk->ViewEnd[dk->Active].x)>(hui3.vy/dk->ViewEnd[dk->Active].y))
		{
			hui3.vx/=2;
			hui3.vx*=1.1;
			dk->ViewSize[dk->Active]=hui3;
		}
		else
		{

			hui3.vx=dk->ViewEnd[dk->Active].x;
			hui3.vx/=dk->ViewEnd[dk->Active].y;
			hui3.vx*=hui3.vy;
			hui3.vx/=2;
			hui3.vx*=1.1;
			dk->ViewSize[dk->Active]=hui3;
		}

		Invalidate(TRUE);
	}

}


void MainEdit::OnViewTypeCamera() 
{
	CSelectCam selcam;
	selcam.dk=dk;
	selcam.DoModal();
	if (selcam.SelCam!=NULL)
	{
		dk->ViewType[dk->Active]=9;
		dk->cam[dk->Active]=selcam.SelCam;
		Invalidate(TRUE);
	}


}

void MainEdit::OnViewTypeFront() 
{
    dk->ViewNg[dk->Active].vx=-90;
    dk->ViewNg[dk->Active].vy=0;
    dk->ViewNg[dk->Active].vz=0;
	dk->ViewType[dk->Active]=0;
	dk->cam[dk->Active]=NULL;
    DrawViews();
}

void MainEdit::OnViewTypeLeft() 
{
    dk->ViewNg[dk->Active].vx=270;
    dk->ViewNg[dk->Active].vy=0;
    dk->ViewNg[dk->Active].vz=270;
	dk->ViewType[dk->Active]=0;
	dk->cam[dk->Active]=NULL;
    DrawViews();
}

void MainEdit::OnViewTypeRight() 
{
    dk->ViewNg[dk->Active].vx=-90;
    dk->ViewNg[dk->Active].vy=0;
    dk->ViewNg[dk->Active].vz=90;
	dk->ViewType[dk->Active]=0;
	dk->cam[dk->Active]=NULL;
    DrawViews();
}

void MainEdit::OnViewTypeTop() 
{
	dk->ViewNg[dk->Active].vx=0;
    dk->ViewNg[dk->Active].vy=0;
    dk->ViewNg[dk->Active].vz=0;
	dk->ViewType[dk->Active]=0;
	dk->cam[dk->Active]=NULL;
	DrawViews();
}

void MainEdit::OnViewTypeBack() 
{
	dk->ViewNg[dk->Active].vx=90;
    dk->ViewNg[dk->Active].vy=180;
    dk->ViewNg[dk->Active].vz=0;
	dk->ViewType[dk->Active]=0;
	dk->cam[dk->Active]=NULL;
	DrawViews();
}

void MainEdit::OnViewTypeBottom() 
{
	dk->ViewNg[dk->Active].vx=0;
    dk->ViewNg[dk->Active].vy=180;
    dk->ViewNg[dk->Active].vz=180;
	dk->ViewType[dk->Active]=0;
	dk->cam[dk->Active]=NULL;
	DrawViews();
}


void MainEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    Vertex hui;
    
    switch(nChar)
    {
    case VK_UP:
	    if (dk->ViewType[dk->Active]==9)
	    {

		    if (dk->cam[dk->Active]!=NULL)
		    {
                dk->cam[dk->Active]->Run(10);
                dk->cam[dk->Active]->SetCamera();
                DrawViews();
		    }
	    }
        else
            if (dk->ViewType[dk->Active]==8)
            {
                dk->Perspective[dk->Active].Run(10);
                dk->Perspective[dk->Active].SetCamera();
                DrawViews();
            }
            else
            {
                hui=View->GetIsoCoord(0,-10,dk->Active)-View->GetIsoCoord(0,0,dk->Active);
	            if (bSnap) hui.Snap(SnapVal);
	            dk->ViewPos[dk->Active]-=hui;
                DrawViews();
            }
        break;
    case VK_DOWN:
	    if (dk->ViewType[dk->Active]==9)
	    {

		    if (dk->cam[dk->Active]!=NULL)
		    {
                dk->cam[dk->Active]->Run(-10);
                dk->cam[dk->Active]->SetCamera();
                DrawViews();
		    }
	    }
        else
            if (dk->ViewType[dk->Active]==8)
            {
                dk->Perspective[dk->Active].Run(-10);
                dk->Perspective[dk->Active].SetCamera();
                DrawViews();
            }
            else
            {
                hui=View->GetIsoCoord(0,10,dk->Active)-View->GetIsoCoord(0,0,dk->Active);
	            if (bSnap) hui.Snap(SnapVal);
	            dk->ViewPos[dk->Active]-=hui;
                DrawViews();
            }

        break;
    case VK_LEFT:
	    if (dk->ViewType[dk->Active]==9)
	    {
		    if (dk->cam[dk->Active]!=NULL)
		    {
                dk->cam[dk->Active]->Strafe(0.10);
                DrawViews();
		    }
	    }
        else
            if (dk->ViewType[dk->Active]==8)
            {
				dk->Perspective[dk->Active].Strafe(0.10);
                DrawViews();
            }
            else
            {
                hui=View->GetIsoCoord(-10,0,dk->Active)-View->GetIsoCoord(0,0,dk->Active);
	            if (bSnap) hui.Snap(SnapVal);
	            dk->ViewPos[dk->Active]-=hui;
                DrawViews();
            }

        break;
    case VK_RIGHT:
	    if (dk->ViewType[dk->Active]==9)
	    {
		    if (dk->cam[dk->Active]!=NULL)
		    {
                dk->cam[dk->Active]->Strafe(-0.10);
                DrawViews();
		    }
	    }
        else
            if (dk->ViewType[dk->Active]==8)
            {
				dk->Perspective[dk->Active].Strafe(-0.10);
                DrawViews();
            }
            else
            {
                hui=View->GetIsoCoord(10,0,dk->Active)-View->GetIsoCoord(0,0,dk->Active);
	            if (bSnap) hui.Snap(SnapVal);
	            dk->ViewPos[dk->Active]-=hui;
                DrawViews();
            }

        break;
    case VK_PRIOR:
	    if (dk->ViewType[dk->Active]==9)
	    {
		    if (dk->cam[dk->Active]!=NULL)
		    {
                dk->cam[dk->Active]->MoveUp(0.1);
                DrawViews();
		    }
	    }
        else
            if (dk->ViewType[dk->Active]==8)
            {
                dk->Perspective[dk->Active].MoveUp(0.1);
                DrawViews();
            }
        break;
    case VK_NEXT:
	    if (dk->ViewType[dk->Active]==9)
	    {
		    if (dk->cam[dk->Active]!=NULL)
		    {
                dk->cam[dk->Active]->MoveUp(-0.1);
                DrawViews();
		    }
	    }
        else
            if (dk->ViewType[dk->Active]==8)
            {
                dk->Perspective[dk->Active].MoveUp(-0.1);
                DrawViews();
            }
        break;

    case VK_HOME:
		if ((dk->ViewType[dk->Active]!=8)&&(dk->ViewType[dk->Active]!=9))
		{
			dk->ViewSize[dk->Active].vx=dk->ViewSize[dk->Active].vx*1.05f;
			dk->ViewSize[dk->Active].vy=dk->ViewSize[dk->Active].vy*1.05f;
			DrawViews();
		}
        break;
    case VK_END:
		if ((dk->ViewType[dk->Active]!=8)&&(dk->ViewType[dk->Active]!=9))
		{
			dk->ViewSize[dk->Active].vx=dk->ViewSize[dk->Active].vx*0.95f;
			dk->ViewSize[dk->Active].vy=dk->ViewSize[dk->Active].vy*0.95f;
			DrawViews();
		}
        break;
    case VK_ESCAPE:
		dk->cSel->UnSelectAll(false);
		dk->DeleteBufVert();
        DrawViews();
        break;
        
    }
    if (gen!=NULL) gen->Process(KM_KEYDOWN,nChar);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void MainEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if (gen!=NULL) gen->Process(KM_KEYUP,nChar);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void MainEdit::OnViewRendermodeMapped() 
{
//    Material *DaMat;

//	dk->daSky=new CSkyBox();
/*
	DaMat=dk->FirstMat;
	while (DaMat!=NULL)
	{

		DaMat->Init();
		DaMat=DaMat->Next;
	}
*/
	dk->State[dk->Active]=1;
    
    DrawViews();

}

void MainEdit::OnFileSaveAs() 
{

    CFileDialog *m_FileDiag;
	m_FileDiag=new CFileDialog(FALSE);
	m_FileDiag->m_ofn.lpstrFilter=WriteFilter;
	if (m_FileDiag->DoModal()==IDOK)
	{
		//theApp.OpenDocumentFile(m_FileDiag->m_ofn.lpstrFile);
        CDeskDoc *tmpdoc = (CDeskDoc *) GetDocument();

        tmpdoc->SetModifiedFlag(FALSE);
        if (gen!=NULL) gen->Process(KM_SAVEDESK,0,0);
        KLibs->WriteGen[(m_FileDiag->m_ofn.nFilterIndex-1)]->Write(dk,m_FileDiag->m_ofn.lpstrFile);
        tmpdoc->genSave=KLibs->WriteGen[(m_FileDiag->m_ofn.nFilterIndex-1)];
        tmpdoc->SetTitle(m_FileDiag->m_ofn.lpstrFile);
		tmpdoc->IsNamed=true;
		tmpdoc->SetModifiedFlag(false);

	}	
  
}

void MainEdit::OnFileSave() 
{
    
    CDeskDoc *tmpdoc = (CDeskDoc *) GetDocument();
	if (!tmpdoc->IsNamed)
	{
        OnFileSaveAs();
		tmpdoc->SetModifiedFlag(false);
    }
    else
    {
		if (!tmpdoc->genSave->WriteSupport)
		{
			OnFileSaveAs();
			tmpdoc->SetModifiedFlag(false);
		}
		else
		{
			tmpdoc->SetModifiedFlag(FALSE);
			tmpdoc->genSave->Process(KM_SAVEDESK,0,0);
			CString tmp=tmpdoc->GetTitle();
			tmpdoc->genSave->Write(dk,tmp.GetBuffer(1));
			tmpdoc->SetModifiedFlag(false);
		}
    }
}

void MainEdit::OnEditCopy() 
{
    ClipBoard.DeleteAll();
	dk->CopySelectedTo(&ClipBoard);
}

void MainEdit::OnEditCut() 
{
	dk->CopySelectedTo(&ClipBoard);
    dk->DeleteSelected();
    DrawViews();
}

void MainEdit::OnEditPaste() 
{
    dk->DeleteBufVert();
    dk->cSel->UnSelectAll(false);
	ClipBoard.CopySelectedTo(dk);
    DrawViews();
}

void MainEdit::OnEditDetete() 
{
    dk->DeleteSelected();
    DrawViews();
}



void MainEdit::OnViewRendermodeWire() 
{
	dk->State[dk->Active]=0;
    DrawViews();
}

void MainEdit::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CView::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	MessageBox("Activate");	
}

void MainEdit::OnChildActivate() 
{
	CView::OnChildActivate();
	
	MessageBox("Activate");	
	
}

void MainEdit::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	MainEdit *cv=NULL;
	cv=(MainEdit *)pActivateView;

    if ((cv!=NULL)&&(bActivate))
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) cv->GetDocument();

		if (!tmpdoc->IsKindOf( RUNTIME_CLASS( CView ) ) ) 
		{
			if (CurrentPlug!=NULL)
				CurrentPlug->SetContext(tmpdoc->dk,NULL,View);
            this->SetFocus();
		}
	}
}
LRESULT MainEdit::OnWmUnSelectAll(WPARAM wParam, LPARAM lParam) 
{
    dk->cSel->UnSelectCamera(false);
    dk->cSel->UnSelectObject(false);
	dk->cSel->UnSelectShape(false);
    dk->cSel->UnSelectLights(false);
    //dk->cSel->UnSelectEmitter(false);
	dk->cSel->UnSelectSkeletton(false);
	dk->cSel->UnSelectPatch(false);

    dk->DeleteBufVert();
	DrawViews();

	return 0;
}


void MainEdit::OnKillFocus( CWnd* pNewWnd )
{
    //if (!pNewWnd->IsKindOf( RUNTIME_CLASS( CView ) ) )
        //this->SetFocus();
}


void MainEdit::OnProperties() 
{
	if (tmpGen!=NULL)
	{
		if (tmpGen==(GenericLib*)0x1) //hack
		{
			CObjProps objprop;
			objprop.daObj=(Object *)PropEnt;
			objprop.DoModal();
		}
		else
		{

			tmpGen->Hwnd=m_wndDialogBar.m_cDialog->m_hWnd;
			
			FunctionID=EDIT_PLUGINCREATION;

			if (gen!=NULL) gen->Close();
			
			gen=tmpGen;
			View->gen=tmpGen;
			tmpGen->MainWin=m_hWnd;

			CMDIChildWnd *pChild = (CMDIChildWnd *) mainf->GetActiveFrame();

			m_wndDialogBar.m_cDialog->SetPlug(tmpGen->Param(),(CWnd *)m_wndDialogBar.m_cDialog);

			if (pChild->GetActiveView()!=NULL)
			{
				CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
				tmpGen->SetContext(tmpdoc->dk,NULL,View);
				CurrentPlug=tmpGen;
			}
			tmpGen->Process(KM_SETOBJECT,(int)PropEnt,0);
		}
	}
}



void MainEdit::OnViewSelectByName()
{
	CSelName seln;
	seln.dk=dk;
	seln.DoModal();
}

void MainEdit::OnSkyBoxLoad()
{
    CFileDialog m_FileDiag(TRUE,"*.skk",NULL,OFN_OVERWRITEPROMPT,
		"Skybox (*.skk)|*.skk||",this);

	if (m_FileDiag.DoModal()==IDOK)
	{
		CString das;
		das=m_FileDiag.GetPathName();
		dk->m_skybox[dk->Active].Load((unsigned char*)das.GetBuffer(10));

	}
}

void MainEdit::OnSkyBoxNone()
{
	dk->m_skybox[dk->Active].UnLoad();
	DrawViews();
}

void MainEdit::OnUpdateSkyboxLoad(CCmdUI *pCmdUI)
{
	if (dk->ViewType[dk->Active]!=0)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);

}

int SvgFunctionID;
void MainEdit::OnMButtonDown(UINT nFlags, CPoint point)
{
	SvgFunctionID=FunctionID;
	FunctionID=EDIT_MOVEVIEW;

    dx=point.x;
    dy=point.y;
	huitemp=View->GetIsoCoord(point.x,point.y,dk->Active);
    IsMoving=true;
	if (dk->ViewType[dk->Active]==9)
	{
		if (dk->cam[dk->Active]!=NULL)
		{
			dk->cam[dk->Active]->SetMousePos();
			dk->cam[dk->Active]->BeginMove();
		}
	}
	else
	if (dk->ViewType[dk->Active]==8)
	{
		dk->Perspective[dk->Active].SetMousePos();
		dk->Perspective[dk->Active].BeginMove();
	}
	CView::OnMButtonDown(nFlags, point);
}

void MainEdit::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (dk->ViewType[dk->Active]==9)
	{
		if (dk->cam[dk->Active]!=NULL)
			dk->cam[dk->Active]->EndDraw();
	}
	else
	{
		if (dk->ViewType[dk->Active]==8)
			dk->Perspective[dk->Active].EndDraw();
	}
	IsMoving=false;

	FunctionID=SvgFunctionID;
	CView::OnMButtonUp(nFlags, point);
}

BOOL MainEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if ((dk->ViewType[dk->Active]!=8)&&(dk->ViewType[dk->Active]!=9))
	{
		if (zDelta>0)
		{
			dk->ViewSize[dk->Active].vx=dk->ViewSize[dk->Active].vx*1.08f;
			dk->ViewSize[dk->Active].vy=dk->ViewSize[dk->Active].vy*1.08f;
			DrawViews();
		}
		else
		{
			dk->ViewSize[dk->Active].vx=dk->ViewSize[dk->Active].vx*0.92f;
			dk->ViewSize[dk->Active].vy=dk->ViewSize[dk->Active].vy*0.92f;
			DrawViews();	
		}
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
