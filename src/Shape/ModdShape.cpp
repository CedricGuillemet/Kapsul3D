/*
    MOdDShape.cpp

  Implementation of the Modifier parameters dialog

*/
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"
#include <headers.h>
extern "C"
{

extern bool CreateSeg;
extern bool CreateSeg2;
extern Vertex Remem;
extern OGLView *View;
extern void *Main;
extern int TypeEdit;
extern int dx,dy;
extern double nga,ngb;
extern double Radius;
extern Segment *CurSeg,*PrevCurSeg,*CurSegEd,*CurSeg2;
extern Shape *CurShape,*CurShapeEd,*CurShape2;
extern int nbSegArc,nbSegNGon,nbSegStar;
extern int TypeEd;
extern Vertex svg;
extern int X,Y;
extern Plan Crp;
extern bool daOk;

void RMouseUp(int X,int Y,Vertex *Pos);

void CreateNGon(Vertex Center,double radius,double ngb,int nb2Seg);
void CreateStar(Vertex Center,double radius1,double radius2,double ngb,int nb2Seg);
void CreateArc(Vertex Center,double radius,double ngb,double ng2,int nb2Seg);

LRESULT CALLBACK ShapeDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char temp[50];

	switch (message)
	{
		/*
		case WM_INITDIALOG:
				SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETBUDDY ,0,(long)GetDlgItem(hDlg,IDC_EDIT1));
				return TRUE;
		*/
		case WM_VSCROLL:
			
			switch (TypeEdit)
			{
				case 5:
					nbSegStar=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS,0,0);
                    if (CurShapeEd!=NULL)
                    {
					    CreateStar(Remem,Radius,sqrt((dx-X)*(dx-X)+(dy-Y)*(dy-Y)),nga,nbSegStar);
						DrawViews();
                    }
					break;
				case 4:
					nbSegArc=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS,0,0);
                    if (CurShapeEd!=NULL)
                    {
					    CreateArc(Remem,Radius,nga,ngb,nbSegArc);
						DrawViews();
                    }
					break;
				case 2:
					nbSegNGon=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS,0,0);
                    if (CurShapeEd!=NULL)
                    {
					    CreateNGon(Remem,sqrt((dx-X)*(dx-X)+(dy-Y)*(dy-Y)),-ng(dx,dy,X,Y),nbSegNGon);
						DrawViews();
                    }
					break;
			}
			
			break;

		case WM_COMMAND:
			if (CreateSeg||CreateSeg2)
			{
				Vertex Null;
				RMouseUp(0,0,&Vertex(0,0,0));
				View->DrawIt();
			}

			switch(LOWORD(wParam))
			{
				case IDC_LINE:
					TypeEdit=1;
					CurShapeEd=NULL;
					ShowWindow(GetDlgItem(hDlg,IDC_STEPS),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_STEP),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_TOUR),SW_HIDE);
					break;
				case IDC_NGON:
					TypeEdit=2;
					CurShapeEd=NULL;
					//SendDlgItemMessage(hDlg,IDC_
					ShowWindow(GetDlgItem(hDlg,IDC_STEPS),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_STEP),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_TOUR),SW_SHOWNORMAL);
					SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,3));
					SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSegNGon,0));
					nbSegNGon=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS,0,0);
					break;
					/*
				case IDC_TOPLANE:
					TypeEdit=6;
					CurShapeEd=NULL;
					ShowWindow(GetDlgItem(hDlg,IDC_STEPS),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_STEP),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_TOUR),SW_HIDE);
					

					break;
					*/
				case IDC_QUAD:
					TypeEdit=3;
					CurShapeEd=NULL;
					ShowWindow(GetDlgItem(hDlg,IDC_STEPS),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_STEP),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_HIDE);
					ShowWindow(GetDlgItem(hDlg,IDC_TOUR),SW_HIDE);

					break;
				case IDC_ARC:
					TypeEdit=4;
					CurShapeEd=NULL;
					ShowWindow(GetDlgItem(hDlg,IDC_STEPS),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_STEP),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_TOUR),SW_SHOWNORMAL);
					SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,3));
					SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSegArc,0));
					nbSegArc=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS,0,0);
					break;
				case IDC_STAR:
					TypeEdit=5;
					CurShapeEd=NULL;
					ShowWindow(GetDlgItem(hDlg,IDC_STEPS),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_STEP),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_SPIN1),SW_SHOWNORMAL);
					ShowWindow(GetDlgItem(hDlg,IDC_TOUR),SW_SHOWNORMAL);
					SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(200,6));
					SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG(nbSegStar,0));
					nbSegStar=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS,0,0);

					break;
			}
			SetPluginActive();
			break;
	}
    return FALSE;
}

}
