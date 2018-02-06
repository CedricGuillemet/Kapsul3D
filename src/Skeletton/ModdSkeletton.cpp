/*
    MOdDSkeletton.cpp

  Implementation of the Modifier parameters dialog

*/
#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"
#include <headers.h>
#include <math.h>
#include "ThirdPart.h"
extern "C"
{

extern bool CreateSeg;
extern int TypeEdit;
extern Desk *dk;

extern double avx,avy,avz;
extern bool IsPlaying;
extern HINSTANCE myHinst;

char LibVal[50];
int TypeAnimName;
DWORD WINAPI ThreadTProc(  LPVOID lpParameter);
void ListAnims(void);

extern AnimatKF *FirstAnim,*NextAnim,*CurrentAnim;
extern Skeletton *AnimSkel;
void AddAnim(void);
extern char AnimName[33],SkeleName[33];
AnimatKF *GetAnim(char *SkelName,char * AnimName);
void DelAnim(AnimatKF *daAnim);
extern int CurrentFrame;
extern HWND SkelettonDiagHWND;
// Animation name handler


LRESULT CALLBACK AnimNameDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			SetWindowText(GetDlgItem(hDlg,IDC_ANIMMODIF),LibVal);
			if (TypeAnimName==2) SetWindowText(GetDlgItem(hDlg,IDC_NAME),CurrentAnim->Name);
			return TRUE;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDOK:
				switch (TypeAnimName)
				{
				case 1:
					// Add
					AddAnim();
					GetWindowText(GetDlgItem(hDlg,IDC_NAME),LibVal,32);
					NextAnim->SetName(LibVal);
					NextAnim->daSkel=AnimSkel;
					NextAnim->SetSkelName(NextAnim->daSkel->Name);
					NextAnim->nbFrames=99;
					CurrentFrame=0;
					// relist
					ListAnims();
					CurrentAnim=NextAnim;
					SetAllFromInd();
					wsprintf(AnimName,"%d",NextAnim->nbFrames);
					SetWindowText(GetDlgItem(SkelettonDiagHWND,IDC_NBFRAMES),AnimName);
					CurrentAnim->RenderFrame(CurrentFrame);
					DrawViews();
					SendDlgItemMessage(SkelettonDiagHWND,IDC_LISTANIMS,CB_SETCURSEL,SendDlgItemMessage(SkelettonDiagHWND,IDC_LISTANIMS,CB_FINDSTRING ,0,(long)LibVal),0);

					// select
					break;
					
				case 2:
					{
						GetWindowText(GetDlgItem(hDlg,IDC_NAME),LibVal,32);
						CurrentAnim->SetName(LibVal);
						AnimatKF *tmpakf=CurrentAnim;
						ListAnims();
						CurrentAnim=tmpakf;
						SendDlgItemMessage(SkelettonDiagHWND,IDC_LISTANIMS,CB_SETCURSEL,SendDlgItemMessage(SkelettonDiagHWND,IDC_LISTANIMS,CB_FINDSTRING ,0,(long)LibVal),0);
					}
					break;
				case 3:
					{
						int NewnbFrames=CurrentAnim->nbFrames;
						GetWindowText(GetDlgItem(hDlg,IDC_NAME),LibVal,32);
						if (sscanf(LibVal,"%d",&NewnbFrames)!=EOF)
						{
							SetWindowText(GetDlgItem(SkelettonDiagHWND,IDC_NBFRAMES),LibVal);
							CurrentAnim->RescaleAndSet(NewnbFrames);
							if (CurrentFrame>NewnbFrames) CurrentFrame=NewnbFrames;
							SetAllFromInd();
							wsprintf(AnimName,"%d",NewnbFrames);
							SetWindowText(GetDlgItem(SkelettonDiagHWND,IDC_NBFRAMES),AnimName);
							SendDlgItemMessage(SkelettonDiagHWND,IDC_SLIDER,TBM_SETRANGE,TRUE,MAKELONG(0, NewnbFrames));
						}
					}
					break;
				}
			case IDCANCEL:
				EndDialog(hDlg,0);
				break;
			}
			break;
	}

	return FALSE;
}

// plugin Dialog box handler

LRESULT CALLBACK SkelettonDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			SendDlgItemMessage(hDlg,IDC_PREVKF,BM_SETIMAGE,IMAGE_ICON,(long)LoadIcon(myHinst,MAKEINTRESOURCE(IDI_PREVKF)));
			SendDlgItemMessage(hDlg,IDC_NEXTKF,BM_SETIMAGE,IMAGE_ICON,(long)LoadIcon(myHinst,MAKEINTRESOURCE(IDI_NEXTKF)));
			SendDlgItemMessage(hDlg,IDC_KILLKF,BM_SETIMAGE,IMAGE_ICON,(long)LoadIcon(myHinst,MAKEINTRESOURCE(IDI_KILLKF)));
			SendDlgItemMessage(hDlg,IDC_PLAY,BM_SETIMAGE,IMAGE_ICON,(long)LoadIcon(myHinst,MAKEINTRESOURCE(IDI_PLAY)));
			return TRUE;

		case WM_TIMER:
			ThreadTProc(NULL);
			break;

		case WM_HSCROLL:
			CurrentFrame=SendDlgItemMessage(hDlg,IDC_SLIDER,TBM_GETPOS,0,0);
			CurrentAnim->RenderFrame(CurrentFrame);
			wsprintf(AnimName,"%d",CurrentFrame);
			SetWindowText(GetDlgItem(hDlg,IDC_POSFRAMES),AnimName);
			DrawViews();
			break;


		case WM_COMMAND:
            switch (HIWORD(wParam))
            {
                case CBN_SELCHANGE:
					SendDlgItemMessage(hDlg,IDC_LISTSKEL,CB_GETLBTEXT,SendDlgItemMessage(hDlg,IDC_LISTSKEL,CB_GETCURSEL,0,0),(long)SkeleName);
					AnimSkel=(Skeletton*)dk->GetByName(SkeleName,PLUGIN_SKELETTON);
                    AnimSkel->daObj->SetNbFrames(2);
                    AnimSkel->daObj->SetFrameInd(1);

					SendDlgItemMessage(hDlg,IDC_LISTANIMS,CB_GETLBTEXT,SendDlgItemMessage(hDlg,IDC_LISTANIMS,CB_GETCURSEL,0,0),(long)AnimName);
					CurrentAnim=GetAnim(SkeleName,AnimName);
					SendDlgItemMessage(hDlg,IDC_SLIDER,SBM_SETPOS,0,0);
					CurrentAnim->RenderFrame(CurrentFrame);
					DrawViews();
					wsprintf(AnimName,"%d",CurrentAnim->nbFrames);
					SetWindowText(GetDlgItem(SkelettonDiagHWND,IDC_NBFRAMES),AnimName);
					CurrentFrame=0;
					SetAllFromInd();
					SendDlgItemMessage(hDlg,IDC_SLIDER,TBM_SETRANGE,TRUE,MAKELONG(0, CurrentAnim->nbFrames));


                    break;
                default:
                    break;
            }

			switch (LOWORD(wParam))
			{
				case IDC_ADDROOT:
					TypeEdit=1;
					CreateSeg=false;
					SetPluginActive();
					break;
				case IDC_ADDBONE:
					TypeEdit=2;
					CreateSeg=false;
					SetPluginActive();
					break;
				case IDC_GETSEL:
					TypeEdit=5;
					CreateSeg=false;
					SetPluginActive();
					break;
				case IDC_SELTOBONE:
					TypeEdit=4;
					CreateSeg=false;
					SetPluginActive();
					break;
				case IDC_ASSIGNOBJ:
					TypeEdit=3;
					CreateSeg=false;
					SetPluginActive();
					break;
				case IDC_MOVEBONE:
					TypeEdit=6;
					CreateSeg=false;
					SetPluginActive();
					break;
				case IDC_MOVEDOT:
					TypeEdit=7;
					CreateSeg=false;
					SetPluginActive();
					break;
				case IDC_UNASSIGNED:
					TypeEdit=8;
					CreateSeg=false;
					SetPluginActive();
					break;
				case IDC_DELBONE:
					TypeEdit=9;
					CreateSeg=false;
					SetPluginActive();
					break;
                    
				case IDC_PLAY:
					{
						if(IsPlaying)
						{
							IsPlaying=false;
							SendDlgItemMessage(hDlg,IDC_PLAY,BM_SETIMAGE,IMAGE_ICON,(long)LoadIcon(myHinst,MAKEINTRESOURCE(IDI_PLAY)));
							KillTimer(hDlg,2);
						}
						else
						{
							IsPlaying=true;
							SendDlgItemMessage(hDlg,IDC_PLAY,BM_SETIMAGE,IMAGE_ICON,(long)LoadIcon(myHinst,MAKEINTRESOURCE(IDI_STOP)));
							SetTimer(hDlg,2,50,NULL);
						}

					}
					break;
				case IDC_NBFRAMES:
					TypeAnimName=3;
					strcpy(LibVal,"Enter number of frames.");
					DialogBox(myHinst,MAKEINTRESOURCE(IDD_ANIMNAME),hDlg,(DLGPROC)AnimNameDlg);
					break;
				case IDC_ADDANIM:
					TypeAnimName=1;
					strcpy(LibVal,"Enter name of new animation.");
					DialogBox(myHinst,MAKEINTRESOURCE(IDD_ANIMNAME),hDlg,(DLGPROC)AnimNameDlg);
					break;
				case IDC_DELANIM:
					if (MessageBox(NULL,"Are you sure you want to delete this animation?","Question.",MB_YESNO)==IDYES)
					{
						DelAnim(GetAnim(AnimSkel->Name,CurrentAnim->Name));
						ListAnims();
						if (CurrentAnim!=NULL)
						{
							CurrentAnim->RenderFrame(CurrentFrame);
							DrawViews();
						}
					}
					break;
				case IDC_RENANIM:
					TypeAnimName=2;
					strcpy(LibVal,"Rename animation.");
					DialogBox(myHinst,MAKEINTRESOURCE(IDD_ANIMNAME),hDlg,(DLGPROC)AnimNameDlg);
					break;

				case IDC_NEXTKF:
					CurrentFrame=CurrentAnim->FindKFAfter(CurrentFrame);
					CurrentAnim->RenderFrame(CurrentFrame);
					DrawViews();
					SetAllFromInd();
					break;
				case IDC_PREVKF:
					CurrentFrame=CurrentAnim->FindKFBefore(CurrentFrame);
					CurrentAnim->RenderFrame(CurrentFrame);
					DrawViews();
					SetAllFromInd();
					break;
				case IDC_KILLKF:
					CurrentAnim->DelKFAtFrame(CurrentFrame);
					CurrentAnim->RenderFrame(CurrentFrame);
					DrawViews();
					SetAllFromInd();
					break;

			}
			break;
	}
    return FALSE;
}

}

