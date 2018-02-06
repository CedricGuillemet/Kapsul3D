#include "stdafx.h"

#include "resource.h"
#include <commctrl.h>
#include "ModdSkeletton.h"
#include "ThirdPart.h"

#include "BuildSkel.h"
#include "WeightSkel.h"
#include "AnimSkel.h"
#include "MainFrame.h"
#include "ModSkeleton.h"

CRollupCtrl *m_wndRollupCtrl;
CBuildSkel m_Build;
CWeightSkel m_Weight;
CAnimSkel m_Anim;

CKPluginSkeleton::CKPluginSkeleton()
{
}

CKPluginSkeleton::~CKPluginSkeleton()
{
}

HWND CKPluginSkeleton::Open(HWND Parent)
{
	SWITCH_RESOURCE;
	/*
	FirstAnim=NULL;
	NextAnim=NULL;
	CurrentAnim=NULL;
	*/

    m_wndRollupCtrl=new CRollupCtrl();
    m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,4,164,362), CWnd::FromHandle(Parent), 2);	


    m_Main=new CMainframe;
    m_Main->Create((unsigned int)IDD_MAINFRAME,CWnd::FromHandle(Parent));
    m_Build.m_Plugin=this;
	CreateSeg=0;
    
    return m_Main->m_hWnd;
}

void CKPluginSkeleton::Close()
{
	m_wndRollupCtrl->DestroyWindow();
    m_Main->DestroyWindow();
}
int CKPluginSkeleton::ScenePluginType()
{
	return PLUGIN_OPERATION;
}
void CKPluginSkeleton::ReSize(int sx,int sy)
{
	m_wndRollupCtrl->MoveWindow(0,0,sx,sy,TRUE);
}
void CKPluginSkeleton::LoseFocus()
{
	m_Build.UnSetPlugin();
}

CString CKPluginSkeleton::GetName()
{
	return "Skeletton";
}
CString CKPluginSkeleton::GetInfos()
{
	return "Skeletton";
}

bool CKPluginSkeleton::CreatingStatus()
{
	return CreateSeg;
}
void CKPluginSkeleton::SetScene(CKScene *pScene)
{
	if (pScene!=m_Scene)
	{
        // REMOVED SavePrivate();
		m_Scene=pScene;
		// REMOVED pd=m_Scene->AddPrivate("SKELETTON.DLL");
		// REMOVED LoadPrivate();
		ListSkelettons();
	}
}

CBitmap *CKPluginSkeleton::GetBitmap()
{
	SWITCH_RESOURCE;


	m_Dib.Detach();
	m_Dib.LoadBitmap(IDB_BITMAP);
    return &m_Dib;
}
CBitmap *CKPluginSkeleton::GetHotBitmap()
{
	SWITCH_RESOURCE;

	m_Dib2.Detach();
	m_Dib2.LoadBitmap(IDB_BITMAPHOT);
    return &m_Dib2;
}
void CKPluginSkeleton::DeleteStuff(void *pData,int DataType)
{
}

void CKPluginSkeleton::LMouseDown(int X,int Y,Vertex &Pos)
{
	VertBuf *daBufVert;
	CKBoneAttach *daBA;

	switch (TypeEdit)
	{
		 // Create Skeletton

		case 1:
			if (CreateSeg==0)
			{
				CreateSeg=1;
				m_Scene->AddSkel();
				
				CurrentSkel=m_Scene->NextSkel;
				CurrentSkel->RootPos=Pos;
//				SendDlgItemMessage(daDiag,IDC_OBJECTNAME,WM_SETTEXT,0,(long)CurrentSkel->ObjName);
				CurrentBone=CurrentSkel->AddBone(NULL);
				//CurrentBone->Pos=Pos;
				CurrentSkel->BuildBase();
			}
			else
			{
				ListSkelettons();
				CreateSeg=0;
			}
			break;

		// Add Bone

		case 2:
			if (CreateSeg==0)
			{
				myBone=0;
				myBone=m_Scene->GetBone(X,Y);
				if (myBone!=NULL)
				{
					CurrentBone=myBone;
                
					CurSkel=m_Scene->GetSkeleton(X,Y);
					if (CurSkel!=NULL)
					{
						CurrentSkel=CurSkel;
						CreateSeg=1;
						CurrentBone=CurrentSkel->AddBone(CurrentBone);
					}
				}
				else
				{
					//new skeletton
					m_Scene->AddSkel();
					CurrentSkel=m_Scene->NextSkel;
					CurrentSkel->RootPos=Pos;
					CurrentBone=CurrentSkel->AddBone(NULL);
					CurrentSkel->BuildBase();
					CurrentBone->Pos=Pos;
					CurrentBone=CurrentSkel->AddBone(CurrentBone);
					CurSkel=CurrentSkel;
					CreateSeg=1;
				}
			}
			else
			{
				CurSkel->BuildBase();
				CurrentBone=CurrentSkel->AddBone(CurrentBone);
				//CreateSeg=0;
			}
			break;

		// Assign Object to Skeletton

		case 3:
			if (CreateSeg==0)
			{
				// pickup skeletton
				CurSkel=m_Scene->GetSkeleton(X,Y);
				if (CurSkel!=NULL)
				{
					//SendDlgItemMessage(daDiag,IDC_OBJECTNAME,WM_SETTEXT,0,(long)CurSkel->ObjName);
					CreateSeg=true;
				}

			}
			else
			{
				// pickup Object
				
				CurMesh=m_Scene->FirstMesh;
				/*m_Scene->GetObject(X,Y);
				if (CurMesh!=NULL)
				{
					strcpy(CurSkel->ObjName,CurMesh->Name);

					SetWindowText(GetDlgItem(SkelettonDiag,IDC_OBJECTNAME),CurSkel->ObjName);
					EnableWindow(GetDlgItem(SkelettonDiag,IDC_SELTOBONE),TRUE);
					EnableWindow(GetDlgItem(SkelettonDiag,IDC_GETSEL),TRUE);
					EnableWindow(GetDlgItem(SkelettonDiag,IDC_UNASSIGNED),TRUE);

					//SendDlgItemMessage(daDiag,IDC_OBJECTNAME,WM_SETTEXT,0,(long)CurSkel->ObjName);
					CreateSeg=false;
				}
				*/

			}
				
			break;

		// Set Vert to Bone

		case 4:
			myBone=m_Scene->GetBone(X,Y);
			if (myBone!=NULL)
			{
				myBone->DelAttached();

				CurSkel=m_Scene->GetSkeleton(X,Y);

				daBufVert=m_Scene->FirstBufVert;
				while(daBufVert!=NULL)
				{
					if (!CurSkel->AlreadyAttached(daBufVert->Dest))
					{
						myBone->AddVert(daBufVert->Dest,daBufVert->VertIndex,1);
					}
					daBufVert=daBufVert->Next;
				}
			}
			break;

		// Get Vert of Bone

		case 5:
			m_Scene->UnSelectMesh(false);
			m_Scene->DeleteBufVert();

			myBone=m_Scene->GetBone(X,Y);
			if (myBone!=NULL)
			{
				daBA=myBone->FirstBA;
				while(daBA!=NULL)
				{
					
					m_Scene->AddBufVert(daBA->Origin,daBA->OriginIndex);
					daBA->Origin->Selected=true;

					daBA=daBA->Next;
				}
			}

			break;

		// Move IK
    
		case 6:
			if (CreateSeg==0)
			{
				myBone=0;
				myBone=m_Scene->GetBone(X,Y);
				if (myBone!=NULL)
				{
					CurrentBone=myBone;
					dx=X;
					dy=Y;
					CreateSeg=1;
					//CurrentBone=CurrentSkel->AddBone(CurrentBone);
					remem=myBone->Rot;
					AnimSkel=m_Scene->GetSkeleton(X,Y);
				}
			}
			else
			{
				/*
				int daKey=SendDlgItemMessage(SkelettonDiag,IDC_SLIDER,TBM_GETPOS,0,0);


				CurrentAnim->UpdateKeyFrame(daKey,myBone,myBone->Rot);

*/
				CreateSeg=0;
			}

			break;
		// move dot
		case 7:
			if (CreateSeg==0)
			{
				myBone=0;
				myBone=m_Scene->GetBone(X,Y);
				if (myBone!=NULL)
				{
					CurSkel=m_Scene->GetSkeleton(X,Y);
					CurSkel->BuildBase();

					//CurrentBone=myBone;
					Remem=myBone->Pos;
					Remem2=Pos;
					
					CreateSeg=1;
					//CurrentBone=CurrentSkel->AddBone(CurrentBone);
				}
			}
			else
			{
				CreateSeg=0;
				CurSkel->BuildBase();
				CurSkel->BuildMatrix(1);
            
			}
			break;

		// get unsassigned

		case 8:
			CurSkel=m_Scene->GetSkeleton(X,Y);
			//if (MyVal!=NULL)
			{
				CKMesh *daMesh=(CKMesh*)m_Scene->GetByName(CurSkel->ObjName,PLUGIN_MESH);
				/*
				char temp[100];

				sprintf(temp,"name: %s ->%x , %d vert",CurSkel->ObjName,daObj,daObj->nb2vert);
				MessageBox(NULL,temp,"yep",MB_OK);
*/
				if (daMesh!=NULL)
				{
					m_Scene->UnSelectMesh(false);

					for (int i=0;i<daMesh->nb2vert;i++)
					{
						if (!CurSkel->AlreadyAttached(&daMesh->pv[i]))
						{
							m_Scene->AddBufVert(&daMesh->pv[i],i);
							daMesh->pv[i].Selected=true;
						}
						
					}
				}
				//SendMessage(TWin,WM_DRAWSCENE,0,0);
				DrawViews();


			}
			break;

		// del bone

		case 9:
			myBone=m_Scene->GetBone(X,Y);
			if (myBone!=NULL)
			{
				m_Scene->GetSkeleton(X,Y)->Del(myBone);
			}
			break;
	}

}

void CKPluginSkeleton::RMouseDown(int X,int Y,Vertex &Pos)
{
	if (CreateSeg)
	{
		if (TypeEdit==2)
		{
			CreateSeg=0;
			CurSkel->DelBone(CurrentBone);
		}
	}
}

void CKPluginSkeleton::LMouseUp(int X,int Y,Vertex &Pos)
{
	switch (TypeEdit)
	{
		// Create Skeletton

		case 1:
			break;

		// Add Bone

		case 2:
			break;

		// Assign Object to Skeletton

		case 3:
			break;

		// Set Vert to Bone

		case 4:
			break;

		// Get Vert of Bone

		case 5:
			break;

		// Move IK

		case 6:
			break;

		// Move Dot
		case 7:
			if (CreateSeg)
				myBone->Pos=Remem;
			break;
	}

}

void CKPluginSkeleton::RMouseUp(int X,int Y,Vertex &Pos)
{
	if (CreateSeg)
	{
		if (TypeEdit==2)
		{
			CreateSeg=0;
			CurSkel->DelBone(CurrentBone);
		}
	}
}

void CKPluginSkeleton::MouseMove(int X,int Y,Vertex &Pos)
{
	switch (TypeEdit)
	{
		// Create Skeletton

		case 1:

			if (CreateSeg==1)
			{
				CurrentBone->Pos=Pos;
				CurrentSkel->BuildBase();
				LStatus("Click to set end root");
				//SendMessage(TWin,WM_DRAWSCENE,0,0);
				DrawViews();
			}
			else
			{
				LStatus("Click to set start root");
			}
			break;

		// Add Bone

		case 2:
			if (CreateSeg==1)
			{
				CurrentBone->Pos=Pos;
				CurSkel->BuildBase();
				LStatus("Click to set extremity.");

			}
			else
			{
				LStatus("Pick bone or root.");
				//sprintf(temp,"Got -> %x",m_Scene->GetBone(X,Y));
				//SendMessage(TWin,WM_SETSTATUS,2,(long)temp);

			}
			break;

		// Assign Object to Skeletton

		case 3:
			if (CreateSeg)
			{
				/*
				if (m_Scene->GetObject(X,Y)==NULL)
					LStatus("Choose an object.");
				else
					LStatus("Assign this object to skeletton.");
					*/

			}
			else
			{
				if (m_Scene->GetBone(X,Y)==NULL)
					LStatus("Click a bone to select skeletton.");
				else
					LStatus("Choose this skeletton.");
			}


			break;

		// Set Vert to Bone

		case 4:
			if (m_Scene->GetBone(X,Y)!=NULL)
				LStatus("Click to set selected vertex to this bone.");
			else
				LStatus("No bone to assign vertex.");

			break;

		// Get Vert of Bone

		case 5:
			if (m_Scene->GetBone(X,Y)!=NULL)
				LStatus("Click to get vertex from this bone.");
			else
				LStatus("No bone to get assigned vertex.");

			break;

		// Move IK

		case 6:
			if (CreateSeg==1)
			{

/*
				int aKeys=GetButton();

				if (aKeys&MK_CONTROL)
					myBone->Rot.y=(X-dx);
				else
					if (aKeys&MK_SHIFT)
						myBone->Rot.z=(X-dx);
					else
						myBone->Rot.x=(X-dx);
*/
				myBone->Rot.x=remem.x+(X-dx);
				myBone->Rot.y=remem.y+(Y-dy);

				AnimSkel->BuildMatrix(0);
				//m_Scene->FirstMesh->SetFrameInd(0);

				//SendMessage(TWin,WM_DRAWSCENE,0,0);
				DrawViews();
				LStatus("Rotate Bone X [Ctrl] Y [Shift] Z.");
			}
			else
			{
				LStatus("Click a bone to move it.");
			}

			break;

		// move dot
		case 7:
			if (CreateSeg)
			{
				myBone->Pos=Remem+Pos-Remem2;
				CurSkel->BuildBase();
				LStatus("Click to set new position.");
			}
			else
			{
				LStatus("Click a bone to move it.");
			}
			break;

		// Get unassigned
		case 8:
			if (m_Scene->GetBone(X,Y)==NULL)
				LStatus("Click a bone to select skeletton.");
			else
				LStatus("Choose this skeletton.");
			break;

		// del bone

		case 9:
			if (m_Scene->GetBone(X,Y)==NULL)
				LStatus("Click a bone to delete.");
			else
				LStatus("Delete this bone.");
			break;
	}

}

/*
void CKPluginSkeleton::SetAllFromInd(void)
{
	SendDlgItemMessage(SkelettonDiag,IDC_SLIDER,TBM_SETPOS,true,CurrentFrame);
	AnimName.Format("%d",CurrentFrame);
	SetWindowText(GetDlgItem(SkelettonDiag,IDC_POSFRAMES),AnimName);

}

//REMOVED CPrivateData *pd=NULL;
//GetByName(char name[20],int NameType)

void CKPluginSkeleton::AddAnim(void)
{        
	if (FirstAnim==NULL)
    {
        FirstAnim=new (AnimatKF)(NULL,NULL);
        NextAnim=FirstAnim;
    }
    else
    {
        NextAnim->Next=new (AnimatKF)(NextAnim,NULL);
        NextAnim=NextAnim->Next;
    }
}

void CKPluginSkeleton::DelAnim(AnimatKF *daAnim)
{
    if (daAnim==FirstAnim)
        FirstAnim=FirstAnim->Next;

    if (daAnim==NextAnim)
        NextAnim=NextAnim->Prev;

    if (daAnim->Next!=NULL)
        daAnim->Next->Prev=daAnim->Prev;

    if (daAnim->Prev!=NULL)
        daAnim->Prev->Next=daAnim->Next;

    delete daAnim;
}


AnimatKF *CKPluginSkeleton::GetAnim(CString SkelName,CString AnimName)
{
	AnimatKF *daAnim;

	daAnim=FirstAnim;
	while (daAnim)
	{
		if ((daAnim->Name==AnimName)&&(daAnim->SkelName==SkelName))
			return daAnim;

		daAnim=daAnim->Next;
	}

	return NULL;
}
/*
DWORD WINAPI ThreadTProc(  LPVOID lpParameter)
{
	int LastKF=0;
	Vertex pos;

	if (CurrentAnim!=NULL)
	{

		CurrentAnim->RenderFrame(CurrentFrame);

		CurrentFrame++;

		if (CurrentFrame==CurrentAnim->nbFrames) CurrentFrame=0;
		
		DrawViews();
		SendDlgItemMessage(SkelettonDiag,IDC_SLIDER,TBM_SETPOS,true,CurrentFrame);
		AnimName.Format("%d",CurrentFrame);
		SetWindowText(GetDlgItem(SkelettonDiag,IDC_POSFRAMES),AnimName);
	}
	
	return true;
}
*/

// IDE properties
/*
void CKPluginSkeleton::ListAnims(void)
{
	AnimatKF *daAnim;

	SendDlgItemMessage(SkelettonDiag,IDC_LISTANIMS,CB_RESETCONTENT,0,0);

	daAnim=FirstAnim;
	while (daAnim!=NULL)
	{
		if (daAnim->daSkel==AnimSkel)
		{
			SendDlgItemMessage(SkelettonDiag,IDC_LISTANIMS,CB_ADDSTRING,0,(long)daAnim->Name.GetBuffer(0));
		}
		daAnim=daAnim->Next;
	}

	if (SendDlgItemMessage(SkelettonDiag,IDC_LISTANIMS,CB_GETCOUNT ,0,0)!=0)
	{
		SendDlgItemMessage(SkelettonDiag,IDC_LISTANIMS,CB_SETCURSEL ,0,0);

		EnableWindow(GetDlgItem(SkelettonDiag,IDC_SLIDER),TRUE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_MOVEBONE),TRUE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_PLAY),TRUE);
		//AnimSkel=daSkel;
		
		SendDlgItemMessage(SkelettonDiag,IDC_LISTANIMS,CB_GETLBTEXT,SendDlgItemMessage(SkelettonDiag,IDC_LISTANIMS,CB_GETCURSEL,0,0),(long)AnimName.GetBuffer(0));
		SendDlgItemMessage(SkelettonDiag,IDC_LISTSKEL,CB_GETLBTEXT,SendDlgItemMessage(SkelettonDiag,IDC_LISTSKEL,CB_GETCURSEL,0,0),(long)SkelName.GetBuffer(0));
		CurrentAnim=GetAnim(SkelName,AnimName);

		SendDlgItemMessage(SkelettonDiag,IDC_SLIDER,TBM_SETRANGE,TRUE,MAKELONG(0, CurrentAnim->nbFrames));
		AnimName.Format("%d",CurrentAnim->nbFrames);
		SetWindowText(GetDlgItem(SkelettonDiag,IDC_NBFRAMES),AnimName);
		CurrentFrame=0;
		SetAllFromInd();


		EnableWindow(GetDlgItem(SkelettonDiag,IDC_DELANIM),TRUE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_RENANIM),TRUE);

		EnableWindow(GetDlgItem(SkelettonDiag,IDC_PREVKF),TRUE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_NEXTKF),TRUE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_KILLKF),TRUE);

		EnableWindow(GetDlgItem(SkelettonDiag,IDC_POSFRAMES),TRUE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_NBFRAMES),TRUE);
		
	}
	else
	{
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_SLIDER),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_MOVEBONE),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_PLAY),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_DELANIM),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_RENANIM),FALSE);

		EnableWindow(GetDlgItem(SkelettonDiag,IDC_PREVKF),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_NEXTKF),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_KILLKF),FALSE);

		EnableWindow(GetDlgItem(SkelettonDiag,IDC_POSFRAMES),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_NBFRAMES),FALSE);
		CurrentAnim=NULL;
	}
}
*/
void CKPluginSkeleton::ListSkelettons(void)
{
	CKSkeleton *daSkel;
	SendDlgItemMessage(SkelettonDiag,IDC_LISTSKEL,CB_RESETCONTENT,0,0);

	daSkel=m_Scene->FirstSkel;
	while (daSkel!=NULL)
	{
		SendDlgItemMessage(SkelettonDiag,IDC_LISTSKEL,CB_ADDSTRING,0,(long)daSkel->Name.GetBuffer(1));
		daSkel=daSkel->Next;
	}

	if (SendDlgItemMessage(SkelettonDiag,IDC_LISTSKEL,CB_GETCOUNT ,0,0)!=0)
	{
		SendDlgItemMessage(SkelettonDiag,IDC_LISTSKEL,CB_SETCURSEL ,0,0);
		daSkel=m_Scene->FirstSkel;

		EnableWindow(GetDlgItem(SkelettonDiag,IDC_ASSIGNOBJ),TRUE);
		if (strcmp(daSkel->ObjName,"")!=0)
		{
			SetWindowText(GetDlgItem(SkelettonDiag,IDC_OBJECTNAME),daSkel->ObjName);
			EnableWindow(GetDlgItem(SkelettonDiag,IDC_SELTOBONE),TRUE);
			EnableWindow(GetDlgItem(SkelettonDiag,IDC_GETSEL),TRUE);
			EnableWindow(GetDlgItem(SkelettonDiag,IDC_UNASSIGNED),TRUE);
			AnimSkel=daSkel;
            AnimSkel->m_Mesh->SetNbFrames(2);
            AnimSkel->m_Mesh->SetFrameInd(1);

//			ListAnims();
		}
		else
		{
			EnableWindow(GetDlgItem(SkelettonDiag,IDC_SELTOBONE),FALSE);
			EnableWindow(GetDlgItem(SkelettonDiag,IDC_GETSEL),FALSE);
			EnableWindow(GetDlgItem(SkelettonDiag,IDC_UNASSIGNED),FALSE);
			AnimSkel=NULL;
		}
	}
	else
	{
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_ASSIGNOBJ),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_SELTOBONE),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_GETSEL),FALSE);
		EnableWindow(GetDlgItem(SkelettonDiag,IDC_UNASSIGNED),FALSE);
	}
	
}
/*
// -- Private Datas -----------------------------------------------------------
/* REMOVED
void SavePrivate(void)
{
	int nbAnims=0;
	int TotalSize=0;
	long *ptr;
	unsigned char *ptr2;

    if (pd!=NULL)
    {

	    AnimatKF *pakf=FirstAnim;
	    while(pakf)
	    {
		    nbAnims++;
		    TotalSize+=(pakf->nbKF*sizeof(KF));
		    pakf=pakf->Next;
	    }

	    TotalSize+=(4+(sizeof(AnimatKF)*nbAnims)+(nbAnims*4));


	    ptr=(long*)pd->Allocate(TotalSize);
	    ptr2=(unsigned char*)ptr;
	    ptr2+=4;

	    (*ptr)=nbAnims;
	    pakf=FirstAnim;
	    for (int i=0;i<nbAnims;i++)
	    {
		    memcpy(ptr2,pakf,sizeof(AnimatKF));
		    ptr2+=sizeof(AnimatKF);
		    ptr=(long*)ptr2;
		    (*ptr)=pakf->nbKF;
		    ptr2+=4;

		    KF *pkf;
		    pkf=pakf->FirstKF;
		    for (int j=0;j<pakf->nbKF;j++)
		    {
			    memcpy(ptr2,pkf,sizeof(KF));
			    ptr2+=sizeof(KF);

			    pkf=pkf->Next;
		    }

		    pakf=pakf->Next;
	    }
    }

}

void LoadPrivate(void)
{
	int nbAnims,nbFrm;
	long *ptr;
	unsigned char *ptr2;

	ptr=(long*)pd->lpBits;

	if (ptr!=NULL)
	{
		ptr2=(unsigned char*)ptr;

		nbAnims=(*ptr);
		ptr2+=4;

		for (int i=0;i<nbAnims;i++)
		{
			AnimatKF anm(NULL,NULL);

			memcpy(&anm,ptr2,sizeof(AnimatKF));
			ptr2+=sizeof(AnimatKF);

			anm.daSkel=(CKSkeleton*)m_Scene->GetByName(anm.SkelName,PLUGIN_SKELETON);
			if (anm.daSkel!=NULL)
			{

				AddAnim();
				strcpy(NextAnim->SkelName,anm.SkelName);
				strcpy(NextAnim->Name,anm.Name);
				NextAnim->daSkel=anm.daSkel;
				NextAnim->nbFrames=anm.nbFrames;
			
			
				ptr=(long*)ptr2;
				ptr2+=4;

				nbFrm=(*ptr);
				for (int j=0;j<nbFrm;j++)
				{
					KF keyf(NULL,NULL);
					memcpy(&keyf,ptr2,sizeof(KF));
					ptr2+=sizeof(KF);

					keyf.BDest=NextAnim->daSkel->FindBone(keyf.BoneName);

					if (keyf.BDest!=NULL)
					{
						NextAnim->AddKF();
						strcpy(NextAnim->NextKF->BoneName,keyf.BoneName);
						NextAnim->NextKF->BDest=keyf.BDest;
						NextAnim->NextKF->Key=keyf.Key;
						NextAnim->NextKF->rx=keyf.rx;
						NextAnim->NextKF->ry=keyf.ry;
						NextAnim->NextKF->rz=keyf.rz;
					}

				}
			}
			else
			{
				ptr2+=(4+(nbFrm*sizeof(KF)));
			}

		}
	}
}
*/
