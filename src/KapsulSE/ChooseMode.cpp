// ChoosePrim.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "ChooseMode.h"
#include "resource.h"
#include "FOToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseMode dialog

extern int GCurSelect;

CChooseMode::CChooseMode(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseMode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Bmp[0].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEVERTEX));
	Bmp[1].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEFACE));
	Bmp[2].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEOBJECT));
}

CChooseMode::~CChooseMode()
{
}

void CChooseMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseMode)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseMode, CDialog)
	//{{AFX_MSG_MAP(CChooseMode)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseMode message handlers
void DrawArrow(CImageList *m_imageList,int btnIndex);
extern int iEditMode;

extern CKViewEdit *FirstCKViewEdit;
void CChooseMode::SetButton(int nbBt)
{
	int i;
	BITMAP bmpx;

	if (!Bmp[0].GetSafeHandle())
	{
		Bmp[0].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEVERTEX));
		Bmp[1].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEFACE));
		Bmp[2].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEOBJECT));
	}

	if (!Bmp[nbBt].GetBitmap(&bmpx)) return ;
	dump=new BYTE[bmpx.bmWidthBytes*bmpx.bmHeight];

	COLORREF crBack= GetSysColor(COLOR_BTNFACE);

	/*
	Bmp[nbBt].GetBitmapBits( bmpx.bmWidthBytes*bmpx.bmHeight,dump);

	for (i=0;i<bmpx.bmWidthBytes*bmpx.bmHeight;i+=(bmpx.bmBitsPixel/8))
		if ( ( (dump[i]==0)&&(dump[i+1]==0)&&(dump[i+2]==0) ) ||
			( (dump[i]==192)&&(dump[i+1]==192)&&(dump[i+2]==192) ) )
		{
			dump[i]=GetBValue(crBack);
			dump[i+1]=GetGValue(crBack);
			dump[i+2]=GetRValue(crBack);
		}


	bmpgi.Detach();
	bmpgi.CreateBitmap(bmpx.bmWidth,bmpx.bmHeight,bmpx.bmPlanes,bmpx.bmBitsPixel,dump);
	m_HotList->Replace(6, &bmpgi, &bmpgi);
	//DrawArrow(m_HotList,6);

*/
	Bmp[nbBt].GetBitmapBits( bmpx.bmWidthBytes*bmpx.bmHeight,dump);

	for (i=0;i<bmpx.bmWidthBytes*bmpx.bmHeight;i+=(bmpx.bmBitsPixel/8))
		if ( ( (dump[i]==0)&&(dump[i+1]==0)&&(dump[i+2]==0) ) ||
			( (dump[i]==192)&&(dump[i+1]==192)&&(dump[i+2]==192) ) )
		{
			dump[i]=GetBValue(crBack);
			dump[i+1]=GetGValue(crBack);
			dump[i+2]=GetRValue(crBack);
		}

	bmpg.Detach();
	bmpg.CreateBitmap(bmpx.bmWidth,bmpx.bmHeight,bmpx.bmPlanes,bmpx.bmBitsPixel,dump);
	m_NormalList->Replace(6, &bmpg, &bmpg);
	DrawArrow(m_NormalList,6);

	delete [] dump;
	
	switch (nbBt)
	{
		case 0:
		{
			CKViewEdit *pcList;

			iEditMode=1;
			//GDrawScene->Primitive=1;

			pcList=FirstCKViewEdit;
			while(pcList!=NULL)
			{
				CKScene *m_Scene=pcList->m_Scene;
				m_Scene->UnSelectAll(false);
				m_Scene->DeleteBufVert();
				m_Scene->UpdateSmthSel();
				pcList->DrawViews();
				pcList=pcList->Next;
			}
		}
		break;

		case 1:
		{
			CKViewEdit *pcList;

			iEditMode=2;
			//GDrawScene->Primitive=2;
			pcList=FirstCKViewEdit;
			while(pcList!=NULL)
			{
				CKScene *m_Scene=pcList->m_Scene;
				m_Scene->UnSelectAll(false);
				m_Scene->DeleteBufVert();
				m_Scene->UpdateSmthSel();
				pcList->DrawViews();
				pcList=pcList->Next;
			}
		}
		break;

		case 2:
		{
			CKViewEdit *pcList;

			iEditMode=3;
			//GDrawScene->Primitive=3;
			pcList=FirstCKViewEdit;
			while(pcList!=NULL)
			{
				CKScene *m_Scene=pcList->m_Scene;
				m_Scene->UnSelectAll(false);
				m_Scene->DeleteBufVert();
				m_Scene->UpdateSmthSel();
				pcList->DrawViews();
				pcList=pcList->Next;
			}
		}
	}

	daParent->SendMessage(WM_MOUSEMOVE, 0, 0);//MAKELPARAM(point.x, point.y));
	daParent->Invalidate(true);

}

void CChooseMode::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonUp(nFlags, point);

	int nbBt;
	if ( (point.x>=0)&&(point.y>0)&&(point.x<=(24))&&(point.y<=120) )
		nbBt=(point.y/24 );
	else
		nbBt=999;

	if (nbBt<3)
	{
		

		Buttons[nbBt]->OnLButtonUp(nFlags,point);
		SetButton(nbBt);


	}

	ReleaseCapture();
	DestroyWindow();
	//ShowWindow(SW_HIDE);
}

BOOL CChooseMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i;
	
	
	SetWindowPos(NULL,0,0,24+6,3*24+6,SWP_NOREPOSITION|SWP_NOZORDER);


	SetCapture();

	//nbButtons=65;
	for (i=0;i<3;i++)
	{
		Bmp[i].DeleteObject();
		
	}

	Bmp[0].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEVERTEX));
	Bmp[1].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEFACE));
	Bmp[2].LoadBitmap(MAKEINTRESOURCE(IDB_SELMODEOBJECT));

	for (i=0;i<3;i++)
	{
		int posx=0;
		int posy=i*24;
		RECT rcx;
		rcx.left=posx;
		rcx.right=posx+24;
		rcx.top=posy;
		rcx.bottom=posy+24;

		Buttons[i]=new CButtonST();
		Buttons[i]->Create("",WS_CHILD|WS_VISIBLE,rcx,this,(1610+i));
		Buttons[i]->SetBitmaps(Bmp[i],0x0c0c0c0);//,bmp2,COLORREF(255,255,255));
		Buttons[i]->ShowWindow(SW_SHOWNORMAL);
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseMode::OnMouseMove(UINT nFlags, CPoint point) 
{
	int nbBt;
	if ( (point.x>=0)&&(point.y>0)&&(point.x<=(24))&&(point.y<=120) )
		nbBt=(point.y/24 );
	else
		nbBt=999;
	
	for (int i=0;i<3;i++)
	{
		if (i==nbBt)
		{
			if (Buttons[i]->m_bMouseOnButton!=TRUE)
			{
				Buttons[i]->m_bMouseOnButton = TRUE;
				Buttons[i]->Invalidate();
			}
		}
		else
		{
			if (Buttons[i]->m_bMouseOnButton!=false)
			{
				Buttons[i]->m_bMouseOnButton = FALSE;
				Buttons[i]->Invalidate();
			}
		}
	}

}

BOOL CChooseMode::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (HIWORD(wParam)==BN_CLICKED)
	{
		switch (LOWORD(wParam))
		{
		case 1410:
			GCurSelect=EDIT_SELECTSINGLE;
			break;
		case 1411:
			GCurSelect=EDIT_SELECTQUAD;
			break;
		case 1412:
			GCurSelect=EDIT_SELECTCIRCLE;
			break;
		case 1413:
			GCurSelect=EDIT_SELECTFENCE;
			break;
		}
		/*
		if ( (FunctionID==EDIT_SELECTSINGLE)||(FunctionID==EDIT_SELECTFENCE)||
			(FunctionID==EDIT_SELECTQUAD)||(FunctionID==EDIT_SELECTCIRCLE) )
			*/
		FunctionID=GCurSelect;

	}

	
	return CDialog::OnCommand(wParam, lParam);
}

void CChooseMode::OnDestroy() 
{
	
	for (int i=0;i<3;i++)
	{

		Buttons[i]->DestroyWindow();
		delete Buttons[i];
		Bmp[i].DeleteObject();

	}
	CDialog::OnDestroy();
			
}
