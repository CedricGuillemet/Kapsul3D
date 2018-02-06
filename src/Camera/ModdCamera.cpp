/*
    MOdDCamera.cpp

  Implementation of the Modifier parameters dialog

*/
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"
#include <headers.h>

extern "C"
{

extern Camera *CurrentCam;

LRESULT CALLBACK CameraDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(1600,320));
			SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETRANGE ,0,MAKELONG(1200,240));
			SendDlgItemMessage(hDlg,IDC_SPIN3,UDM_SETRANGE ,0,MAKELONG(150,10));

			SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETPOS ,0,MAKELONG((short) 640, 0));
			SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_SETPOS ,0,MAKELONG((short) 480, 0));
			SendDlgItemMessage(hDlg,IDC_SPIN3,UDM_SETPOS ,0,MAKELONG((short) 60, 0));
			return TRUE;

		case WM_COMMAND:
			break;

		case WM_VSCROLL:
			if (CurrentCam!=NULL)
			{
				CurrentCam->ResoX=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
				CurrentCam->ResoY=SendDlgItemMessage(hDlg,IDC_SPIN2,UDM_GETPOS ,0,0);
				CurrentCam->Fov=SendDlgItemMessage(hDlg,IDC_SPIN3,UDM_GETPOS ,0,0);
				//SendMessage(MyVal->TWin,WM_DRAWSCENE,0,0);
			}
			SetPluginActive();

			break;
	}
    return FALSE;
}

}

