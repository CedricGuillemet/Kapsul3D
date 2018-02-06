// MatBrowser.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulSE.h"
#include "MatBrowser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatBrowser dialog

#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	75

extern int iEditMode;
extern CKOption *KOption;

DWORD WINAPI ThreadProc(  LPVOID lpParameter   )
{
	CMatBrowser *curpr;	
	curpr=(CMatBrowser*)lpParameter;


	if (curpr->m_Choose.GetCurSel()!=-1)
	{
		curpr->m_Choose.GetLBText(curpr->m_Choose.GetCurSel(),curpr->m_strImageDir);

		curpr->m_Progress.ShowWindow(SW_SHOWNORMAL);
		curpr->GetImageFileNames();
		curpr->DrawThumbnails();

		curpr->m_List.Arrange(LVA_SNAPTOGRID);
		curpr->m_Progress.ShowWindow(SW_HIDE);
	}
	return 0;
}


CMatBrowser::CMatBrowser(CWnd* pParent /*=NULL*/)
	: CDialog(CMatBrowser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatBrowser)
	//}}AFX_DATA_INIT
}


void CMatBrowser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatBrowser)
	DDX_Control(pDX, IDC_CBCHOOSE, m_Choose);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatBrowser, CDialog)
	//{{AFX_MSG_MAP(CMatBrowser)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_CBCHOOSE, OnSelchangeCbchoose)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatBrowser message handlers
//extern "C" COption *KOption;

BOOL  CMatBrowser::GetImageFileNames(void)
{			
	CString	strPath, strPattern;
	CFile	ImgFile;	
	BYTE	data[8] = {'\0'};	
    char Cards[6][7]={{"\\*.bmp"},{"\\*.jpg"},{"\\*.tif"},{"\\*.gif"},{"\\*.pcx"},{"\\*.tga"}};//,{"\\*.dds"}};
	BOOL	bRC = TRUE;
	
	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;
	std::vector<CString>	VectorImageNames;

    for (int i=0;i<6;i++)
    {
	    strPattern = m_strImageDir + CString(Cards[i]);//"\\*.bmp";
	    hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
	    if(hFind != INVALID_HANDLE_VALUE)
	    {

	        // filter off the system files and directories
	        if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
	           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
	           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
	           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
	        {  	  
		        // open the file
		        strPath = m_strImageDir + "\\" + FindFileData.cFileName;
                VectorImageNames.push_back(CString(FindFileData.cFileName));
	        }  

	        // loop through to add all of them to our vector	
            bRC = TRUE;

	        while(bRC)
	        {
		        bRC = ::FindNextFile(hFind, &FindFileData);
		        if(bRC)
		        {
			        // filter off the system files and directories
			        if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
			           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
			           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
			           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
			        {
				        VectorImageNames.push_back(CString(FindFileData.cFileName));
			        }
		        }
	        } // end of while loop

	        // close the search handle
	        ::FindClose(hFind);
        }
    }

	// update the names, if any
	if(!VectorImageNames.empty())
	{
		// reset the image name vector
		m_VectorImageNames.erase(m_VectorImageNames.begin(), m_VectorImageNames.end());

		// copy the new image file names into vector
		std::vector<CString>::iterator	iter;		
		for(iter = VectorImageNames.begin(); iter != VectorImageNames.end(); iter++)
			m_VectorImageNames.push_back(*iter);		
/*
        char temp[100];
        wsprintf(temp,"found %d files",VectorImageNames.size());
//        ::MessageBox(NULL,temp,temp,MB_OK);
*/
        m_Progress.SetRange(0,VectorImageNames.size());

		return TRUE;
	}

	return FALSE;

}

void  CMatBrowser::DrawThumbnails(void)
{
	CBitmap*    pImage = NULL;	
	HBITMAP     hBitmap = NULL;
    //BITMAPINFOHEADER *hbmi;
    BITMAPINFO hbm;
	HPALETTE    hPal = NULL;
	HDC			hMemDC = NULL;	
	HGDIOBJ		hOldObj = NULL;
	POINT		pt;
    int IndImg=0;

	//CFile		ImgFile;
	//CDib		dib;
    CKImage      dib;
	CString		strPath;
	int			nWidth, nHeight;

	// no images
	if(m_VectorImageNames.empty())
		return;

	// set the length of the space between thumbnails
	// you can also calculate and set it based on the length of your list control
	int nGap = 6;

	// hold the window update to avoid flicking
	m_List.SetRedraw(FALSE);

	// reset our image list
	for(int i=0; i<m_ImageListThumb.GetImageCount(); i++)
		m_ImageListThumb.Remove(i);	

	// remove all items from list view
	if(m_List.GetItemCount() != 0)
		m_List.DeleteAllItems();

	// set the size of the image list
	m_ImageListThumb.SetImageCount(m_VectorImageNames.size());
	i = 0;

	// draw the thumbnails
	std::vector<CString>::iterator	iter;
	for(iter = m_VectorImageNames.begin(); iter != m_VectorImageNames.end(); iter++)
	{		

		// load the bitmap
		strPath = m_strImageDir + "\\" + *iter;
		//ImgFile.Open(strPath, CFile::modeRead);
		//dib.Read(ImgFile);
        dib.LoadFile(strPath);
		dib.Dither(IMG_TYPE_COL24,true);
        memcpy((void*)&hbm.bmiHeader,(void*)GlobalLock(dib.m_hDib),sizeof(BITMAPINFOHEADER));
		//ImgFile.Close();

		// borrow our dib header to create our thumbnail bitmap
		nWidth = dib.GetWidth();
		nHeight = dib.GetHeight();
        /*
		dib.m_pBMI->bmiHeader.biWidth = THUMBNAIL_WIDTH;
		dib.m_pBMI->bmiHeader.biHeight = THUMBNAIL_HEIGHT;
*/

		// create thumbnail bitmap section
		hBitmap = ::CreateDIBSection(NULL, 
									 &hbm,
								     DIB_RGB_COLORS, 
								     NULL, 
								     NULL, 
								     0); 

		// restore dib header
        /*
		dib.m_pBMI->bmiHeader.biWidth = nWidth;
		dib.m_pBMI->bmiHeader.biHeight = nHeight;
*/
		// select thumbnail bitmap into screen dc
		hMemDC = ::CreateCompatibleDC(NULL);	
		hOldObj = ::SelectObject(hMemDC, hBitmap);
	  
        /*
		// grayscale image, need palette
		if(dib.m_pPalette != NULL)
		{
			hPal = ::SelectPalette(hMemDC, (HPALETTE)dib.m_pPalette->GetSafeHandle(), FALSE);
			::RealizePalette(hMemDC);
		}
        */
	  
		// set stretch mode
		::SetStretchBltMode(hMemDC, COLORONCOLOR);

		// populate the thumbnail bitmap bits
        /*
		::StretchDIBits(hMemDC, 0, 0, 
						THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, 
						0, 0, 
						dib.m_pBMI->bmiHeader.biWidth, 
						dib.m_pBMI->bmiHeader.biHeight, 
						dib.m_pBits, 
						dib.m_pBMI, 
						DIB_RGB_COLORS, 
						SRCCOPY);
                        */

        long DrawFlags=/*DIB_DRAW_CENTER_HORZ|DIB_DRAW_CENTER_VERT|*/DIB_DRAW_USE_GDI|DIB_DRAW_SETPALETTE;

        if (nWidth>THUMBNAIL_WIDTH) DrawFlags|=DIB_DRAW_STRETCH_REDUCEX;
        if (nHeight>THUMBNAIL_HEIGHT) DrawFlags|=DIB_DRAW_STRETCH_REDUCEY;
        /*
        if (nWidth<THUMBNAIL_WIDTH) DrawFlags|=DIB_DRAW_STRETCH_EXPANDX;
        if (nHeight<THUMBNAIL_HEIGHT) DrawFlags|=DIB_DRAW_STRETCH_EXPANDY;
        */

/*
        long DrawFlags=DIB_DRAW_STRETCH_REDUCEX|DIB_DRAW_STRETCH_EXPANDX|DIB_DRAW_USE_GDI|
            DIB_DRAW_STRETCH_REDUCEY|DIB_DRAW_STRETCH_EXPANDY|DIB_DRAW_USE_GDI|DIB_DRAW_SETPALETTE;//|DIB_DRAW_USE_GDI;
*/
        //DIB_DRAW_STRETCH_EXPANDX|DIB_DRAW_STRETCH_EXPANDY|
        dib.Draw(hMemDC,CRect(0,0,THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT),DrawFlags,CRect(0,0,nWidth,nHeight) );

		// restore DC object
		::SelectObject(hMemDC, hOldObj);
	  
		// restore DC palette
        /*
		if(dib.m_pPalette != NULL)
			::SelectPalette(hMemDC, (HPALETTE)hPal, FALSE);
	  */
		// clean up
		::DeleteObject(hMemDC);
		
		// attach the thumbnail bitmap handle to an CBitmap object
		pImage = new CBitmap();		 
		pImage->Attach(hBitmap);

		// add bitmap to our image list
		m_ImageListThumb.Replace(i, pImage, NULL);

		// put item to display
		// set the image file name as item text
		m_List.InsertItem(i, m_VectorImageNames[i], i);

		// get current item position	 
		m_List.GetItemPosition(i, &pt);	 
	  
		// shift the thumbnail to desired position
		pt.x = nGap + i*(THUMBNAIL_WIDTH + nGap);
		//m_List.SetItemPosition(i, pt);
		i++;
			
        GlobalUnlock(dib.m_hDib);
		delete pImage;

        IndImg++;
        m_Progress.SetPos(IndImg);
	}

	// let's show the new thumbnails
	m_List.SetRedraw(TRUE); 
}

void CMatBrowser::UpdateCBPath(void)
{
	//CKOption *KOption=(COption*)GetGOption();

    if (KOption->GetnbMapDir()>0)
    {
        m_Choose.ResetContent();

        for (int i=0;i<KOption->GetnbMapDir();i++)
        {
			m_Choose.AddString(KOption->GetMapDir(i));

        }
        m_Choose.SetCurSel(0);
    }

	

	DWORD thId;
	HANDLE thHand=::CreateThread(NULL,NULL,ThreadProc,this,NULL,&thId);
}

BOOL CMatBrowser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Progress.ShowWindow(SW_HIDE);

    m_ImageListThumb.DeleteImageList( );
	m_ImageListThumb.Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR32, 0, 1);
	m_List.SetImageList(&m_ImageListThumb, LVSIL_NORMAL);

	m_Choose.SetDroppedWidth(350);
	UpdateCBPath();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatBrowser::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (IsWindow(m_List.m_hWnd))
	{
		m_Choose.SetWindowPos(NULL,0,0,1,1,SWP_NOSIZE|SWP_NOZORDER);
		m_List.MoveWindow(0,34,cx,cy-34);
		m_Progress.MoveWindow(0,24,cx,10,SWP_NOSIZE|SWP_NOZORDER);
	}
}

void CMatBrowser::OnOK( )
{
}

void CMatBrowser::OnCancel( )
{
}

void CMatBrowser::OnSelchangeCbchoose() 
{

	DWORD thId;
	HANDLE thHand=::CreateThread(NULL,NULL,ThreadProc,this,NULL,&thId);
	
}


void CMatBrowser::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	// retrieve message info.
	LPNMITEMACTIVATE pItemAct = (LPNMITEMACTIVATE)pNMHDR;

	// determine which item receives the click
	LVHITTESTINFO  hitTest;
	memset(&hitTest, '\0', sizeof(LVHITTESTINFO));
	hitTest.pt = pItemAct->ptAction;
	m_List.SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hitTest);

	// draw the selected image
	if(hitTest.iItem != m_nSelectedItem && hitTest.iItem >= 0)
	{
		m_nSelectedItem = hitTest.iItem;
        m_Texture=m_strImageDir + "\\" + m_VectorImageNames[m_nSelectedItem];
//		DrawSelectedImage();
	}

	// select the item clicked
	*pResult = 0;
}

void CMatBrowser::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if(pLVKeyDow->wVKey == VK_LEFT || pLVKeyDow->wVKey == VK_RIGHT)
	{	
		// get total number of items in the list
		int nTotal = m_List.GetItemCount();

		// rule out the situation of an empty list
		if(nTotal == 0)
		{
			*pResult = 1; // current record stays selected
			return;
		}
    
		// reset selected item index
		int  nNewItem = -1;

		// set the selection
		if(pLVKeyDow->wVKey == VK_LEFT)	// left arrow
		{
			if(m_nSelectedItem > 0)
				nNewItem = m_nSelectedItem - 1;
		}
		else	// right arrow
		{
			if(m_nSelectedItem < nTotal-1)
				nNewItem = m_nSelectedItem + 1;
		}

		// update the selection
		if(nNewItem != -1)
		{
			// update the selected item index
			m_nSelectedItem = nNewItem;

			// draw the selected image
//			DrawSelectedImage();
		}	 
	}
	
	// high-light the selected item
	*pResult = 0;
}
void CMatBrowser::ApplyTexture(CString TexName)
{
	CKTexture *datex=m_Scene->GetTexByShortName(TexName);

	if (datex==NULL)
	{
		datex=m_Scene->AddTex(TexName);
		datex->Type=TEXTURE_FILE;
		datex->Load();
	}

	if (iEditMode==2)
	{
		// apply the polygons
		for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			for (int i=0;i<daMesh->nb2poly;i++)
			{
				if (daMesh->pl[i].Selected)
				{
					daMesh->pl[i].Maps[0]=datex;
				}
			}
		}
	}
	else
	if (iEditMode==3)
	{
		// apply per object
		for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			if (daMesh->Selected)
			{
				daMesh->ApplyTexture(datex);
			}
		}
		// apply per patch
		for (CKPatch *daPatch=m_Scene->FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
		{
			if (daPatch->Selected)
				daPatch->ApplyTexture(datex);
		}
	}
}


void CMatBrowser::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ApplyTexture(m_Texture.GetBuffer(10));	
	*pResult = 0;
	DrawViews();
}

void CMatBrowser::SelectTexture(CString TextureName) 
{
	CString dapth,daname;
	char Drive[MAX_PATH],Path[MAX_PATH],Filename[MAX_PATH],Ext[MAX_PATH];

	_splitpath(TextureName,Drive,Path,Filename,Ext);
	dapth=Drive;
	dapth+=Path;
	dapth=dapth.Mid(0,(dapth.GetLength()-1));

	daname=Filename;
	daname+=Ext;

	if (m_Choose.SelectString( -1, dapth)!=CB_ERR)
	{
		DWORD thId;
		HANDLE thHand=::CreateThread(NULL,NULL,ThreadProc,this,NULL,&thId);

		LVFINDINFO vdinfo;
		vdinfo.flags=LVFI_STRING;
		vdinfo.psz=daname;
		m_List.SetHotItem(m_List.FindItem(&vdinfo));
	}	


}