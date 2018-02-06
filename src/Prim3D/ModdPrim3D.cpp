/*
MOdDPrim3D.cpp

  Implementation of the Modifier parameters dialog
  
*/
#include "stdafx.h"
#include <commctrl.h>
#include <Kapsul3D.h>
#include <Headers.h>
#include "resource.h"
#include "Tree/tree/tree.h"

extern "C" 
{
    
    LRESULT CALLBACK Prim3DDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        /*
        case WM_SHOWWINDOW:
        Sleep(1000);
        KLibs=new(LibContainer);
        KLibs->RegisterLibs("plugins\\","plugins\\","plugins\\","plugins\\");
        
          EndDialog(hDlg, LOWORD(wParam));
          break;
            */
            
        case WM_INITDIALOG:
            ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_HIDE);
            SendDlgItemMessage(hDlg,IDC_SPIN3,UDM_SETRANGE ,0,MAKELONG(1000,1));
            SendDlgItemMessage(hDlg,IDC_SPIN3,UDM_SETPOS ,0,MAKELONG(10,0));
            SendDlgItemMessage(hDlg,IDC_SPIN4,UDM_SETRANGE ,0,MAKELONG(1000,1));
            SendDlgItemMessage(hDlg,IDC_SPIN4,UDM_SETPOS ,0,MAKELONG(10,0));
            
            SendDlgItemMessage(hDlg,IDC_LEAFSIZE,TBM_SETRANGE ,TRUE,MAKELONG(5,50));
            SendDlgItemMessage(hDlg,IDC_LEAFSIZE,TBM_SETPOS ,TRUE,2);
            SendDlgItemMessage(hDlg,IDC_BRANCHSIZE,TBM_SETRANGE ,TRUE,MAKELONG(1,50));
            SendDlgItemMessage(hDlg,IDC_BRANCHSIZE,TBM_SETPOS ,TRUE,10);
            SendDlgItemMessage(hDlg,IDC_THRESHOLD,TBM_SETRANGE ,TRUE,MAKELONG(0,100));
            SendDlgItemMessage(hDlg,IDC_THRESHOLD,TBM_SETPOS ,TRUE,50);
            SendDlgItemMessage(hDlg,IDC_TWIST,TBM_SETRANGE ,TRUE,MAKELONG(0,180));
            SendDlgItemMessage(hDlg,IDC_TWIST,TBM_SETPOS ,TRUE,60);
            SendDlgItemMessage(hDlg,IDC_BRANCH,TBM_SETRANGE ,TRUE,MAKELONG(0,100));
            SendDlgItemMessage(hDlg,IDC_BRANCH,TBM_SETPOS ,TRUE,70);
            SendDlgItemMessage(hDlg,IDC_BRANCHBIAS,TBM_SETRANGE ,TRUE,MAKELONG(0,100));
            SendDlgItemMessage(hDlg,IDC_BRANCHBIAS,TBM_SETPOS ,TRUE,75);
            SendDlgItemMessage(hDlg,IDC_BRANCHNOISE,TBM_SETRANGE ,TRUE,MAKELONG(0,100));
            SendDlgItemMessage(hDlg,IDC_BRANCHNOISE,TBM_SETPOS ,TRUE,50);
            
            ShowWindow(GetDlgItem(hDlg,IDC_LEAFSIZE),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_BRANCHSIZE),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_THRESHOLD),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_TWIST),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_BRANCH),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_BRANCHBIAS),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_BRANCHNOISE),SW_HIDE);
            
            ShowWindow(GetDlgItem(hDlg,IDC_SPIN3),SW_SHOWNORMAL);
            ShowWindow(GetDlgItem(hDlg,IDC_SPIN4),SW_SHOWNORMAL);
            ShowWindow(GetDlgItem(hDlg,IDC_MAPPINGV),SW_SHOWNORMAL);
            ShowWindow(GetDlgItem(hDlg,IDC_MAPPINGU),SW_SHOWNORMAL);
            
            ShowWindow(GetDlgItem(hDlg,IDC_LIB1),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB2),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB3),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB4),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB5),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB6),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB7),SW_HIDE);
            
            
            /*
            leaf_size_slider = new Slider(0.5, 5.0, 2.0); //10
            branch_size_slider = new Slider(0.01, 0.5, 0.1); //100
            threshhold_slider = new Slider(0.0, 1.0, 0.5);//100
            twist_slider = new Slider(0.0, 180.0, 60.0);
            branch_slider = new Slider(0.0, 1.0, 0.7); //100
            branch_bias_slider = new Slider(0.0, 1.0, 0.75); //100
            branch_noise_slider = new Slider(0.0, 1.0, 0.5);
            */
            return TRUE;
            
        case WM_COMMAND:
            ShowWindow(GetDlgItem(hDlg,IDC_LEAFSIZE),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_BRANCHSIZE),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_THRESHOLD),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_TWIST),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_BRANCH),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_BRANCHBIAS),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_BRANCHNOISE),SW_HIDE);
            
            ShowWindow(GetDlgItem(hDlg,IDC_LIB1),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB2),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB3),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB4),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB5),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB6),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIB7),SW_HIDE);
            ShowWindow(GetDlgItem(hDlg,IDC_LIBU),SW_SHOWNORMAL);
            ShowWindow(GetDlgItem(hDlg,IDC_LIBV),SW_SHOWNORMAL);
            
            
            ShowWindow(GetDlgItem(hDlg,IDC_CONTOUR1),SW_SHOWNORMAL);
            ShowWindow(GetDlgItem(hDlg,IDC_CONTOUR2),SW_SHOWNORMAL);
            
            ShowWindow(GetDlgItem(hDlg,IDC_SPIN3),SW_SHOWNORMAL);
            ShowWindow(GetDlgItem(hDlg,IDC_SPIN4),SW_SHOWNORMAL);
            ShowWindow(GetDlgItem(hDlg,IDC_MAPPINGV),SW_SHOWNORMAL);
            ShowWindow(GetDlgItem(hDlg,IDC_MAPPINGU),SW_SHOWNORMAL);

            switch(LOWORD(wParam))
            {
            case IDC_CUBE:
                TypeEdit=7;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_HIDE);
                CurrentObj=NULL;
                
                break;
            case IDC_HEMIS:
                TypeEdit=10;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_HIDE);
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,3));
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSegHemis,0));
                CurrentObj=NULL;
                
                
                break;
            case IDC_SPHERE:
                TypeEdit=4;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_HIDE);
                
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,3));
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSegSphere,0));
                CurrentObj=NULL;
                
                
                break;
            case IDC_GRID:
                TypeEdit=3;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_SHOWNORMAL);
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,1));
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSeg1Grid,0));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETRANGE ,0,MAKELONG(200,1));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETPOS ,0,MAKELONG(nbSeg2Grid,0));
                CurrentObj=NULL;
                
                
                break;
            case IDC_TORUS:
                TypeEdit=8;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_SHOWNORMAL);
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,1));
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSeg1Torus,0));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETRANGE ,0,MAKELONG(200,3));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETPOS ,0,MAKELONG(nbSeg2Torus,0));
                CurrentObj=NULL;
                
                break;
            case IDC_TREE:
                TypeEdit=11;
                ShowWindow(GetDlgItem(hDlg,IDC_LEAFSIZE),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_BRANCHSIZE),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_THRESHOLD),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_TWIST),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_BRANCH),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_BRANCHBIAS),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_BRANCHNOISE),SW_SHOWNORMAL);
                
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_HIDE);
                
                ShowWindow(GetDlgItem(hDlg,IDC_CONTOUR1),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_CONTOUR2),SW_HIDE);
                
                ShowWindow(GetDlgItem(hDlg,IDC_LIB1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_LIB2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_LIB3),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_LIB4),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_LIB5),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_LIB6),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_LIB7),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_LIBU),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_LIBV),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN3),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN4),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_MAPPINGV),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_MAPPINGU),SW_HIDE);
                CurrentObj=NULL;
                LeafObj=NULL;
                break;
                /*
                case IDC_STAIRS:
                TypeEdit=2;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_HIDE);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_HIDE);
                CurrentObj=NULL;
                
                  break;
                */
            case IDC_CYLINDER:
                TypeEdit=5;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_SHOWNORMAL);
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,1));
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSeg1Cylinder,0));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETRANGE ,0,MAKELONG(200,3));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETPOS ,0,MAKELONG(nbSeg2Cylinder,0));
                CurrentObj=NULL;
                
                break;
            case IDC_CONE:
                TypeEdit=6;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_SHOWNORMAL);
                
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,1));
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSeg1Cone,0));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETRANGE ,0,MAKELONG(200,3));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETPOS ,0,MAKELONG(nbSeg2Cone,0));
                CurrentObj=NULL;
                
                break;
            case IDC_TUBE:
                TypeEdit=9;
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_SPIN2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC1A),SW_SHOWNORMAL);
                ShowWindow(GetDlgItem(hDlg,IDC_STATIC2A),SW_SHOWNORMAL);
                
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,1));
                SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSeg1Tube,0));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETRANGE ,0,MAKELONG(200,3));
                SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETPOS ,0,MAKELONG(nbSeg2Tube,0));
                CurrentObj=NULL;
                
                break;
                
            }
            Radius1=0;
            Radius2=0;
            Radius3=0;
            OriginNg=0;
            SetPluginActive();
            break;
        case WM_HSCROLL:
            {
                float daval;
                daval=SendDlgItemMessage(hDlg,IDC_LEAFSIZE,TBM_GETPOS ,0,0);
                daval/=10;
                mytree.setLeafSize(daval);
                
                daval=SendDlgItemMessage(hDlg,IDC_BRANCHSIZE,TBM_GETPOS ,0,0);
                daval/=100;
                mytree.setBranchSize(daval);
                
                daval=SendDlgItemMessage(hDlg,IDC_THRESHOLD,TBM_GETPOS ,0,0);
                daval/=100;
                mytree.setThreshhold(daval);
                
                daval=SendDlgItemMessage(hDlg,IDC_BRANCHNOISE,TBM_GETPOS ,0,0);
                daval/=100;
                mytree.setBranchNoise(daval);
                
                daval=SendDlgItemMessage(hDlg,IDC_BRANCHBIAS,TBM_GETPOS ,0,0);
                daval/=100;
                mytree.setBranchBias(daval);
                
                daval=SendDlgItemMessage(hDlg,IDC_BRANCH,TBM_GETPOS ,0,0);
                daval/=100;
                mytree.setBranch(daval);
                
                daval=SendDlgItemMessage(hDlg,IDC_TWIST,TBM_GETPOS ,0,0);
                mytree.setTwist(daval);
                
                mytree.build(CurrentObj,LeafObj,&Remem);

                DrawViews();
            }
            
            break;
        case WM_VSCROLL:
            {
                switch(TypeEdit)
                {
                    //case IDC_CUBE:
                case 7:
                    
                    break;
                    //case IDC_HEMIS:
                case 10:
                    nbSegHemis=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
                    break;
                    //case IDC_SPHERE:
                case 4:
                    nbSegSphere=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
                    break;
                    //case IDC_GRID:
                case 3:
                    nbSeg1Grid=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
                    nbSeg2Grid=SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_GETPOS ,0,0);
                    break;
                    //case IDC_TORUS:
                case 8:
                    nbSeg1Torus=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
                    nbSeg2Torus=SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_GETPOS ,0,0);
                    break;
                    //case IDC_STAIRS:
                    //    break;
                    //case IDC_CYLINDER:
                case 5:
                    nbSeg1Cylinder=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
                    nbSeg2Cylinder=SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_GETPOS ,0,0);
                    break;
                    //case IDC_CONE:
                case 6:
                    nbSeg1Cone=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
                    nbSeg2Cone=SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_GETPOS ,0,0);
                    break;
                    //case IDC_TUBE:
                case 9:
                    nbSeg1Tube=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
                    nbSeg2Tube=SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_GETPOS ,0,0);
                    break;
                }
                
                Valu=SendDlgItemMessage(hDlg,IDC_SPIN3,UDM_GETPOS ,0,0);
                Valu/=10.0f;
                Valv=SendDlgItemMessage(hDlg,IDC_SPIN4,UDM_GETPOS ,0,0);
                Valv/=10.0f;
                
                
                
                if  (CurrentObj!=NULL)
                {
                    switch(TypeEdit)
                    {
                        //case IDC_CUBE:
                    case 7:
                        CreateCube(Remem,svgX,svgY,Radius1);
                        break;
                        //case IDC_HEMIS:
                    case 10:
                        CreateHemis(Remem,Radius1,nbSegHemis);
                        break;
                        //case IDC_SPHERE:
                    case 4:
                        CreateSphere(Remem,Radius1,nbSegSphere);
                        break;
                        //case IDC_GRID:
                    case 3:
                        CreateGrid(Remem,oX-dx,oY-dy,nbSeg1Grid,nbSeg2Grid);
                        break;
                        //case IDC_TORUS:
                    case 8:
                        CreateTorus(Remem,Radius1,Radius2,nbSeg1Torus,nbSeg2Torus);
                        break;
                        //case IDC_CYLINDER:
                    case 5:
                        CreateCyl(Remem,Radius1,Radius2,nbSeg1Cylinder,nbSeg2Cylinder);
                        break;
                        //case IDC_CONE:
                    case 6:
                        //CreateCone(Remem,Radius1,Radius2,Radius3,nbSeg1Cone,nbSeg2Cone);
                        CreateCone(Remem,Radius2,Radius1,Radius3,nbSeg1Cone,nbSeg2Cone);
                        break;
                        //case IDC_TUBE:
                    case 9:
                        CreateTube(Remem,Radius1,Radius2,Radius3,nbSeg1Tube,nbSeg2Tube);
                        break;
                    case 11:
                        //CurrentObj->de
                        break;
                    }
                    DrawViews();
                    
                    
                }
            }
            break;
            
            
    }
    return FALSE;
    
}


}