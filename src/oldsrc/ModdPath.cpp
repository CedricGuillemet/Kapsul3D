/*
    MOdDPath.cpp

  Implementation of the Modifier parameters dialog

*/
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"
#include "headers.h"

extern "C"
{

extern int TypeEd;
extern int VectorUp;
extern int CreateSeg;

LRESULT CALLBACK PathDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		case WM_INITDIALOG:
//            SendDlgItemMessage(hDlg,IDC_XUP,BM_SETCHECK,BST_CHECKED,0);
				return TRUE;

		case WM_COMMAND:
            SetPluginActive();
            CreateSeg=0;
			switch (LOWORD(wParam))
			{
            case IDC_SHAPE:
                TypeEd=1;
                
                break;
            case IDC_PATH:
                TypeEd=2;
                break;

            case IDOK:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
            case IDC_MOVEDOT:
                TypeEd=3;
                break;
            case IDC_GENERATE:
                break;
            case IDC_SCALE:
                TypeEd=4;
                break;
            case IDC_ROTATE:
                TypeEd=5;
                break;
            case IDC_MOVESHAPE:
                TypeEd=6;
                break;
                /*
            case IDC_XUP:
                VectorUp=1;
                DrawViews();
                break;
            case IDC_YUP:
                VectorUp=2;
                DrawViews();
                break;
            case IDC_ZUP:
                VectorUp=3;
                DrawViews();
                break;
*/
            case IDC_SURFACE:
//                ToSurface(dk->FirstShape);
                break;

            
            default:
                break;
			}
			break;
	}
    return FALSE;
}

}
