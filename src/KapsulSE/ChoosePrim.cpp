// ChoosePrim.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "ChoosePrim.h"
#include "resource.h"
#include "FOToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoosePrim dialog
extern CKPluginManager *GKPlugins;


void CopyBitmap(CBitmap *Dst,CBitmap *Src)
{
	BYTE *Dumpit;

	BITMAP bmpx;
	if (!Src->GetBitmap(&bmpx)) return;
	Dumpit=new BYTE[bmpx.bmWidthBytes*bmpx.bmHeight];

	Src->GetBitmapBits( bmpx.bmWidthBytes*bmpx.bmHeight,Dumpit);

	Dst->CreateBitmap(bmpx.bmWidth,bmpx.bmHeight,bmpx.bmPlanes,bmpx.bmBitsPixel,Dumpit);
	delete [] Dumpit;
}

PrimBmp *gobmp[10];
int CurPrimInd;
int CurAbsPrim=0;
extern CKScenePlugin *GCurPlug;
extern CTVTestDlg	*m_DesksBrowser;
extern CMainFrame *MainFrm;

int ghji[100],ghji2[100];


CChoosePrim::CChoosePrim(CWnd* pParent /*=NULL*/)
	: CDialog(CChoosePrim::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChoosePrim)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT


}

CChoosePrim::~CChoosePrim()
{
}

void CChoosePrim::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChoosePrim)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CChoosePrim::Init(void)
{
	int i,j;
	int adav=0;
	nbButtons=0;
	for (i=0;i<GKPlugins->PrimitivePlugins.size();i++)
	{
		gobmp[i]=(PrimBmp*)GKPlugins->PrimitivePlugins[i]->GetAllPrimitives();
		for (j=0;j<gobmp[i]->NbBmps;j++)
		{
			m_Plugins[j+nbButtons]=GKPlugins->PrimitivePlugins[i];
			Indices[j+nbButtons]=gobmp[i]->PrimNb[j];
			CopyBitmap(&Bmp[j+nbButtons],&gobmp[i]->Bmp[j]);
			ghji[adav]=i;
			ghji2[adav]=j;
			adav++;
		}
		nbButtons+=gobmp[i]->NbBmps;
	}
}
CKScenePlugin *CurGenLib;
BEGIN_MESSAGE_MAP(CChoosePrim, CDialog)
	//{{AFX_MSG_MAP(CChoosePrim)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void SetCreationPlugin(void)
{
	CMDIChildWnd *pChild;

	if (GCurPlug!=CurGenLib)
	{
		if (GCurPlug!=NULL) GCurPlug->Close();
		GCurPlug=CurGenLib;
		GCurPlug->m_hWnd=m_DesksBrowser->m_cDialog.m_hWnd;
		//GDrawScene->m_Plugin=GCurPlug;
		pChild = (CMDIChildWnd *) MainFrm->GetActiveFrame();

		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		tmpdoc->m_Renderer->m_Plugin=GCurPlug;

		m_DesksBrowser->m_cDialog.SetPlug(GCurPlug->Open(GCurPlug->m_hWnd),(CWnd *)&m_DesksBrowser->m_cDialog);
	}
	else
	{
		GCurPlug=CurGenLib;
		GCurPlug->m_hWnd=m_DesksBrowser->m_cDialog.m_hWnd;
		//GDrawScene->m_Plugin=GCurPlug;
		pChild = (CMDIChildWnd *) MainFrm->GetActiveFrame();

		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		tmpdoc->m_Renderer->m_Plugin=GCurPlug;

	}
	
	FunctionID=EDIT_PLUGINPRIMITIVE;

    if (pChild->GetActiveView()!=NULL)
    {
		CDeskDoc *tmpdoc = (CDeskDoc *) pChild->GetActiveView()->GetDocument();
		GCurPlug->SetScene(tmpdoc->m_Scene);
		GCurPlug->SetPrimitive(CurPrimInd);
    }
}
/////////////////////////////////////////////////////////////////////////////
// CChoosePrim message handlers
void DrawArrow(CImageList *m_imageList,int btnIndex)
{

	HICON hIcon = m_imageList->ExtractIcon(btnIndex);
	ICONINFO m_iconInfo; GetIconInfo(hIcon, &m_iconInfo);
	BITMAP m_bmpInfo; GetObject(m_iconInfo.hbmColor, sizeof(m_bmpInfo), &m_bmpInfo);

	// create a memory device context to draw into
	CDC m_dc; m_dc.CreateCompatibleDC(NULL);

	// prepare the mask
	CBitmap m_mask; m_mask.CreateBitmapIndirect(&m_bmpInfo);

	CBitmap* m_pOldBitmap = (CBitmap*) m_dc.SelectObject(&m_mask);

	CBrush m_brush; m_brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* m_pOldBrush = (CBrush*) m_dc.SelectObject(&m_brush);

	// draw the mask
	m_imageList->Draw(&m_dc, btnIndex, CPoint(0, 0), ILD_MASK);

	// draw the arrow at the right-bottom side of the bitmap
	POINT points[] = {	{m_bmpInfo.bmWidth-7, m_bmpInfo.bmHeight-1},
						{m_bmpInfo.bmWidth-1, m_bmpInfo.bmHeight-1},
						{m_bmpInfo.bmWidth-1, m_bmpInfo.bmHeight-7} };

	m_dc.Polygon(points, 3);
	m_dc.FloodFill(m_bmpInfo.bmWidth-3, m_bmpInfo.bmHeight-2, RGB(0, 0, 0));

	m_dc.SelectObject(m_pOldBrush); m_brush.DeleteObject();
	m_dc.SelectObject(m_pOldBitmap);

	// draw the arrow the image bitmap
	CBitmap m_bitmap; m_bitmap.Attach(m_iconInfo.hbmColor);

	m_pOldBitmap = (CBitmap*) m_dc.SelectObject(&m_bitmap);

	static COLORREF arrowColor = RGB(255, 0, 0);

	m_brush.CreateSolidBrush(arrowColor);
	m_pOldBrush = (CBrush*) m_dc.SelectObject(&m_brush);

	CPen m_pen; m_pen.CreatePen(PS_SOLID, 1, arrowColor);
	CPen* m_pOldPen = (CPen*) m_dc.SelectObject(&m_pen);

	m_dc.Polygon(points, 3);
	m_dc.FloodFill(m_bmpInfo.bmWidth-3, m_bmpInfo.bmHeight-2, arrowColor);

	m_dc.SelectObject(m_pOldBrush);
	m_dc.SelectObject(m_pOldBitmap);
	m_dc.SelectObject(m_pOldPen);

	// replace the bitmap with the new bitmap (the one with the arrow)
	m_imageList->Replace(btnIndex, &m_bitmap, &m_mask);

	m_bitmap.DeleteObject();
	m_pen.DeleteObject();
	m_brush.DeleteObject();
	m_mask.DeleteObject();

	m_dc.DeleteDC();
}

void CChoosePrim::SetButton(int nbBt)
{
	int i;
	BITMAP bmpx;
	COLORREF crBack= GetSysColor(COLOR_BTNFACE);
	//if (!BmpIn[nbBt].GetBitmap(&bmpx)) return;
	
	gobmp[ghji[CurAbsPrim]]->Bmp[ghji2[CurAbsPrim]].GetBitmap(&bmpx);

	dump=new BYTE[bmpx.bmWidthBytes*bmpx.bmHeight];

	

	
	CurPrimInd=Indices[nbBt];
	CurGenLib=m_Plugins[nbBt];

	
	gobmp[ghji[CurAbsPrim]]->Bmp[ghji2[CurAbsPrim]].GetBitmapBits( bmpx.bmWidthBytes*bmpx.bmHeight,dump);
/*
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
	m_HotList->Replace(8, &bmpgi, &bmpgi);
	//DrawArrow(m_HotList,8);


	gobmp[ghji[CurAbsPrim]]->BmpIn[ghji2[CurAbsPrim]].GetBitmapBits( bmpx.bmWidthBytes*bmpx.bmHeight,dump);
*/
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
	m_NormalList->Replace(8, &bmpg, &bmpg);
	DrawArrow(m_NormalList,8);

	delete [] dump;
	//daParent->Invalidate(true);
}

void CChoosePrim::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonUp(nFlags, point);

	int nbBt;
	float tmpy=floor((float)nbButtons/5.0f)*24+24;
	if ( (point.x>0)&&(point.y>0)&&(point.x<(24*5))&&(point.y<tmpy) )
	{
		nbBt= ((floor( (float) point.y/24.0f) ) *5.0f );
		nbBt+=(((float)point.x/24.0f));
	}
	else
		nbBt=999;

	if (nbBt<nbButtons)
	{
		Buttons[nbBt]->OnLButtonUp(nFlags,point);
		
		SetDaPrime(nbBt);
		daParent->SendMessage(WM_MOUSEMOVE, WPARAM(nFlags), 0);//MAKELPARAM(point.x, point.y));
	}

	ReleaseCapture();
	DestroyWindow();
	//ShowWindow(SW_HIDE);
}
void CChoosePrim::SetDaPrime(int nbBt)
{
	MainFrm->m_Primitives.GetToolBarCtrl().SetState(MainFrm->PrimitivesIds[CurAbsPrim],BST_UNCHECKED);
	CurAbsPrim=nbBt;
	SetButton(nbBt);
	daParent->Invalidate(true);
	CurPrimInd=Indices[nbBt];
	CurGenLib=m_Plugins[nbBt];
	SetCreationPlugin();
	MainFrm->m_Primitives.GetToolBarCtrl().SetState(MainFrm->PrimitivesIds[CurAbsPrim],BST_CHECKED);
}

BOOL CChoosePrim::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i,j;
	
	
	SetWindowPos(NULL,0,0,24*5+6,ceil((float)nbButtons/5.0f)*24+6,SWP_NOREPOSITION|SWP_NOZORDER);


	SetCapture();

	

	for (i=0;i<nbButtons;i++)
	{
		Bmp[i].DeleteObject();

	}

	nbButtons=0;
	for (i=0;i<GKPlugins->PrimitivePlugins.size();i++)
	{
		for (j=0;j<gobmp[i]->NbBmps;j++)
		{
			CopyBitmap(&Bmp[j+nbButtons],&gobmp[i]->Bmp[j]);
			//CopyBitmap(&BmpOut[j+nbButtons],&gobmp[i]->BmpOut[j]);
		}
		nbButtons+=gobmp[i]->NbBmps;
	}

	
	for (i=0;i<nbButtons;i++)
	{
		int posx=(i%5)*24;
		int posy=floor((float)i/5.0f)*24;
		RECT rcx;
		rcx.left=posx;
		rcx.right=posx+24;
		rcx.top=posy;
		rcx.bottom=posy+24;

		Buttons[i]=new CButtonST();
		Buttons[i]->Create("",WS_CHILD|WS_VISIBLE,rcx,this,(16330+i));
		Buttons[i]->SetBitmaps(Bmp[i],0x0c0c0c0);//,bmp2,COLORREF(255,255,255));
	}	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoosePrim::OnMouseMove(UINT nFlags, CPoint point) 
{
	
	int nbBt;
	if ( (point.x>0)&&(point.y>0)&&(point.x<(24*5))&&(point.y<(floor((float)nbButtons/5.0f)+1)*24) )
		nbBt=(((float)point.x/24.0f) +( floor((float)point.y/24.0f)) *5.0f );
	else
		nbBt=999;
	
	for (int i=0;i<nbButtons;i++)
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

BOOL CChoosePrim::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (HIWORD(wParam)==BN_CLICKED)
	{
		CString tmp;
		tmp.Format("Ctrl %d",LOWORD(wParam));
//		MessageBox(tmp);	
	}

	
	return CDialog::OnCommand(wParam, lParam);
}

void CChoosePrim::OnDestroy() 
{
	
	for (int i=0;i<nbButtons;i++)
	{

		Buttons[i]->DestroyWindow();
		delete Buttons[i];
		/*
		BmpIn[i].DeleteObject();
		BmpOut[i].DeleteObject();
		*/

	}
	CDialog::OnDestroy();
			
}
