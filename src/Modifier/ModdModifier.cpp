/*
    MOdDModifier.cpp

  Implementation of the Modifier parameters dialog

*/
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"
#include "headers.h"

extern "C"
{

extern int TypeEd;
void FlipNormalFaces(void);
void UnifyNormalFaces(void);

LRESULT CALLBACK ModifierDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
            SetPluginActive();
			switch (LOWORD(wParam))
			{
			case IDC_UP:
                TypeEd=1;
				break;/*
			case IDC_DOWN:
                TypeEd=2;
				break;
                */
			case IDC_LEFT:
                TypeEd=3;
				break;
                /*
			case IDC_RIGHT:
                TypeEd=4;
				break;
                */
			case IDC_UPDOWN:
                TypeEd=5;
				break;
			case IDC_LEFTRIGHT:
                TypeEd=6;
				break;
			case IDC_UPDOWN2:
                TypeEd=7;
				break;
			case IDC_LEFTRIGHT2:
                TypeEd=8;
				break;
			case IDC_UPDOWN3:
                TypeEd=9;
				break;
			case IDC_LEFTRIGHT3:
                TypeEd=10;
				break;
			case IDC_ANY:
                TypeEd=11;
				break;
            case IDC_FLIPNORMALS:
                FlipNormalFaces();
                break;
            case IDC_UNIFYNORMALS:
                UnifyNormalFaces();
                break;
			}
			return TRUE;
	}
    return FALSE;
}

}
