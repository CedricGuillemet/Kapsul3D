/*
    MOdDLight.cpp

  Implementation of the Modifier parameters dialog

*/
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"
#include <commdlg.h>
#include <headers.h>

extern "C"
{

extern unsigned char r,g,b;
extern Light *CurrentLight;
extern HINSTANCE myHinst;

LRESULT CALLBACK LightDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CHOOSECOLOR ch;
	COLORREF temp[16];

	switch (message)
	{
		case WM_INITDIALOG:
				SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_SETRANGE ,0,MAKELONG(600,0));
				SendDlgItemMessage(hDlg,IDC_SPOT,BM_SETCHECK ,BST_CHECKED,0);

				return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_COLOR:
					memset(&ch,0,sizeof(ch));
					ch.lStructSize=sizeof(ch);
					ch.Flags=CC_FULLOPEN|CC_SHOWHELP | CC_RGBINIT ;
					ch.hwndOwner=hDlg;
					ch.lpCustColors=temp;
					ch.hInstance=(HWND)myHinst;
					ch.rgbResult=RGB(r, g, b) ;
					if (ChooseColor(&ch))
					{
						r=ch.rgbResult&255;
						g=(ch.rgbResult>>8)&255;
						b=(ch.rgbResult>>16)&255;

						if (CurrentLight!=NULL)
						{
							CurrentLight->r=r;
							CurrentLight->g=g;
							CurrentLight->b=b;
						}

						InvalidateRect(hDlg,NULL,FALSE);

					}
  
					break;
				default:
					break;
			}
			SetPluginActive();
			break;
		case WM_VSCROLL:
			if (CurrentLight!=NULL)
			{
				if (CurrentLight->Type==1)
					CurrentLight->Radius=(float)SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0)/100.0f;
				else
					CurrentLight->Radius=SendDlgItemMessage(hDlg,IDC_SPIN1,UDM_GETPOS ,0,0);
				DrawViews();
			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				BeginPaint(hDlg, &ps);
			HDC hdc=GetDC(hDlg);
			RECT rc;

			HBRUSH hbr;

			hbr=CreateSolidBrush(RGB(r, g, b));
 

			rc.left=62;
			rc.top=60;
			rc.right=112;
			rc.bottom=80;

			FillRect(hdc,&rc,hbr);
			EndPaint(hDlg, &ps); 
			return TRUE;
			}
 			break;

	}
    return FALSE;
}

}

