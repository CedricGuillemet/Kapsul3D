/*
    MOdDInfos.cpp

  Implementation of the Modifier parameters dialog

*/
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"

extern "C"
{

LRESULT CALLBACK InfosDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            default:
                break;
            }
			break;

		case WM_VSCROLL:
			break;
	}
    return FALSE;
}

}
