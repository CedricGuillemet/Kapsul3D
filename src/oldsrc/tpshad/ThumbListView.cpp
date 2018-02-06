// ThumbListView.cpp : implementation file
//

#include "stdafx.h"
#include "tpshad.h"
#include "ThumbListView.h"
#include "kfiledialog.h"
#include "dib.h"

// CThumbListView

#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	75

IMPLEMENT_DYNAMIC(CThumbListView, CListCtrl)
CThumbListView::CThumbListView()
{
    m_TypeView=0;
}   

CThumbListView::~CThumbListView()
{
}


BEGIN_MESSAGE_MAP(CThumbListView, CListCtrl)
    ON_NOTIFY_REFLECT(NM_CLICK, OnClickListThumb)
    ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydownListThumb)
END_MESSAGE_MAP()

void CThumbListView::OnClickListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	// retrieve message info.
	LPNMITEMACTIVATE pItemAct = (LPNMITEMACTIVATE)pNMHDR;

	// determine which item receives the click
	LVHITTESTINFO  hitTest;
	memset(&hitTest, '\0', sizeof(LVHITTESTINFO));
	hitTest.pt = pItemAct->ptAction;
	/*m_ListThumbnail.*/SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hitTest);

	// draw the selected image
	if(hitTest.iItem != m_nSelectedItem && hitTest.iItem >= 0)
	{
		m_nSelectedItem = hitTest.iItem;

		((CKFileDialog*)GetParent())->m_FileName.SetWindowText(GetItemText(pItemAct->iItem,pItemAct->iSubItem));
		//DrawSelectedImage();
	}

	// select the item clicked
	*pResult = 0;
}

void CThumbListView::OnKeydownListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if(pLVKeyDow->wVKey == VK_LEFT || pLVKeyDow->wVKey == VK_RIGHT)
	{	
		// get total number of items in the list
		int nTotal = /*m_ListThumbnail.*/GetItemCount();

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
			//DrawSelectedImage();
		}	 
	}
	
	// high-light the selected item
	*pResult = 0;
}

BOOL  CThumbListView::GetImageFileNames()
{			
	CString	strPath, strPattern;
	CFile	ImgFile;	
	BYTE	data[8] = {'\0'};	
	BOOL	bRC = TRUE;
	
	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;
	std::vector<FolderFileEntry>	VectorImageNames;
    //std::vector<FolderFileEntry>	Vffn;

    m_VectorImageNames.erase(m_VectorImageNames.begin(), m_VectorImageNames.end());
    DeleteAllItems();

    // is resource
    char ZipName[MAX_PATH],ZipRep[MAX_PATH];

if (GetZipName(m_strImageDir.GetBuffer(1),ZipName,ZipRep))
  {
      // archive

      if (ZipRep[strlen(ZipRep)-1]=='\\') ZipRep[strlen(ZipRep)-1]=0;

      pak.SetArchive(ZipName,true);

      int RepAv=0;
      bool IsFolder;
      char *fname=pak.GetFolderFiles(ZipRep,RepAv++,NULL,IsFolder,VectorImageNames);
      
  }
    //
else
{
    CString date,size;

	    strPattern = m_strImageDir + "*.*";
	    hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
	    if(hFind == INVALID_HANDLE_VALUE)
	    {
		    return FALSE;
	    }

	    // filter off the system files and directories
	    if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
	    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
	    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)&&
        !(strcmp(FindFileData.cFileName,".")==0)&&
        !(strcmp(FindFileData.cFileName,"..")==0))
	    {  	  
            date.Format("%d",FindFileData.ftCreationTime);
            if (FindFileData.nFileSizeLow>10240)
                if (FindFileData.nFileSizeLow>(1024*1024))
                        size.Format("%d Mo",FindFileData.nFileSizeLow/(1024*1024));
                else
                    size.Format("%d Ko",FindFileData.nFileSizeLow/(1024));
            else
                size.Format("%d",FindFileData.nFileSizeLow);

            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    VectorImageNames.push_back(FolderFileEntry(FindFileData.cFileName,"Folder","",date));
            else
                VectorImageNames.push_back(FolderFileEntry(FindFileData.cFileName,"File",size,date));
	    }  

	    // loop through to add all of them to our vector	
	    while(bRC)
	    {
		    bRC = ::FindNextFile(hFind, &FindFileData);
		    if(bRC)
		    {
			    // filter off the system files and directories
			    if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
			    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
			    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)&&
                !(strcmp(FindFileData.cFileName,".")==0)&&
                !(strcmp(FindFileData.cFileName,"..")==0))
			    {
                    date.Format("%d",FindFileData.ftCreationTime);
            if (FindFileData.nFileSizeLow>10240)
                if (FindFileData.nFileSizeLow>(1024*1024))
                        size.Format("%d Mo",FindFileData.nFileSizeLow/(1024*1024));
                else
                    size.Format("%d Ko",FindFileData.nFileSizeLow/(1024));
            else
                size.Format("%d Mo",FindFileData.nFileSizeLow);

            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    VectorImageNames.push_back(FolderFileEntry(FindFileData.cFileName,"Folder","",date));
            else
                VectorImageNames.push_back(FolderFileEntry(FindFileData.cFileName,"File",size,date));
			    }
		    }  
    		
	    } // end of while loop

	    // close the search handle
	    ::FindClose(hFind);
  }
	// update the names, if any
	if(!VectorImageNames.empty())
	{
		// reset the image name vector
		m_VectorImageNames.erase(m_VectorImageNames.begin(), m_VectorImageNames.end());

		// copy the new image file names into vector
        
		std::vector<FolderFileEntry>::iterator	iter;		
		for(iter = VectorImageNames.begin(); iter != VectorImageNames.end(); iter++)
			m_VectorImageNames.push_back(*iter);		
          
		//std::vector<FolderFileEntry>::iterator	iter;	
        /*
        int iter;
        for(iter = 0;iter<VectorImageNames.size(); iter++)
			m_VectorImageNames.push_back(VectorImageNames[iter]);		
*/
		return TRUE;
	}

	return FALSE;

}

void  CThumbListView::DrawThumbnails()
{
	CBitmap*    pImage = NULL;	
	HBITMAP     hBitmap = NULL;
	HPALETTE    hPal = NULL;
	HDC			hMemDC = NULL;	
	HGDIOBJ		hOldObj = NULL;
	POINT		pt;

	CFile		ImgFile;
	CDib		dib;
	CString		strPath;
	int			nWidth, nHeight,i=0;
    int nGap = 6;

    switch (m_TypeView)
    {
        case 0:
            
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
    /*  thumbnails
	// no images
	if(m_VectorImageNames.empty())
		return;

	// set the length of the space between thumbnails
	// you can also calculate and set it based on the length of your list control
	

	// hold the window update to avoid flicking
	SetRedraw(FALSE);

	// reset our image list
	for(int i=0; i<m_ImageListThumb.GetImageCount(); i++)
		m_ImageListThumb.Remove(i);	
    

	// remove all items from list view
	if(GetItemCount() != 0)
		DeleteAllItems();


	// set the size of the image list
	m_ImageListThumb.SetImageCount(m_VectorImageNames.size());
	i = 0;
*/
	// draw the thumbnails
	std::vector<FolderFileEntry>::iterator	iter;
	for(iter = m_VectorImageNames.begin(); iter != m_VectorImageNames.end(); iter++)
	{		
		// load the bitmap
		//strPath = m_strImageDir + iter[i].Name;
        /*
		ImgFile.Open(strPath, CFile::modeRead);
		dib.Read(ImgFile);
		ImgFile.Close();

		// borrow our dib header to create our thumbnail bitmap
		nWidth = dib.m_pBMI->bmiHeader.biWidth;
		nHeight = dib.m_pBMI->bmiHeader.biHeight;
		dib.m_pBMI->bmiHeader.biWidth = THUMBNAIL_WIDTH;
		dib.m_pBMI->bmiHeader.biHeight = THUMBNAIL_HEIGHT;

		// create thumbnail bitmap section
		hBitmap = ::CreateDIBSection(NULL, 
									 dib.m_pBMI, 
								     DIB_RGB_COLORS, 
								     NULL, 
								     NULL, 
								     0); 

		// restore dib header
		dib.m_pBMI->bmiHeader.biWidth = nWidth;
		dib.m_pBMI->bmiHeader.biHeight = nHeight;

		// select thumbnail bitmap into screen dc
		hMemDC = ::CreateCompatibleDC(NULL);	
		hOldObj = ::SelectObject(hMemDC, hBitmap);
	  
		// grayscale image, need palette
		if(dib.m_pPalette != NULL)
		{
			hPal = ::SelectPalette(hMemDC, (HPALETTE)dib.m_pPalette->GetSafeHandle(), FALSE);
			::RealizePalette(hMemDC);
		}
	  
		// set stretch mode
		::SetStretchBltMode(hMemDC, COLORONCOLOR);

		// populate the thumbnail bitmap bits
		::StretchDIBits(hMemDC, 0, 0, 
						THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, 
						0, 0, 
						dib.m_pBMI->bmiHeader.biWidth, 
						dib.m_pBMI->bmiHeader.biHeight, 
						dib.m_pBits, 
						dib.m_pBMI, 
						DIB_RGB_COLORS, 
						SRCCOPY);

		// restore DC object
		::SelectObject(hMemDC, hOldObj);
	  
		// restore DC palette
		if(dib.m_pPalette != NULL)
			::SelectPalette(hMemDC, (HPALETTE)hPal, FALSE);
	  
		// clean up
		::DeleteObject(hMemDC);
		
		// attach the thumbnail bitmap handle to an CBitmap object
		pImage = new CBitmap();		 
		pImage->Attach(hBitmap);

		// add bitmap to our image list
		m_ImageListThumb.Replace(i, pImage, NULL);
*/
		// put item to display
		// set the image file name as item text
        SHFILEINFO sfi;
		char temppath[512];

        CString tmpstr=m_strImageDir+m_VectorImageNames[i].Name;
		//CString daf=tmpstr;
		/*
		GetTempPath(512,temppath);
		daf=temppath+m_VectorImageNames[i].Name;
		FILE *ctf2=fopen(tmpstr,"wb");
		if (ctf2==NULL)
		{
			GetSystemDirectory(temppath,512);
			daf=temppath;
		}
		else
		{
			fclose(ctf2);
			FILE *ctf=fopen(daf,"wb");
		}

	*/

        if (m_TypeView==0)
            SHGetFileInfo(tmpstr, 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON );
        if (m_TypeView==1)
            SHGetFileInfo(tmpstr, 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON);

	//	DeleteFile(daf);
        

		InsertItem(i, m_VectorImageNames[i].Name, sfi.iIcon);
        //InsertItem(i, m_VectorImageNames[i].Name, i);

        SetItemText(i,1,m_VectorImageNames[i].Size);
        SetItemText(i,2,m_VectorImageNames[i].Type);
        SetItemText(i,3,m_VectorImageNames[i].Date);
        

		// get current item position	 
		/*m_ListThumbnail.*/GetItemPosition(i, &pt);	 
	  
		// shift the thumbnail to desired position
		pt.x = nGap + i*(THUMBNAIL_WIDTH + nGap);
		/*m_ListThumbnail.*/SetItemPosition(i, pt);
		i++;
			
		delete pImage;
	}

	// let's show the new thumbnails
	///*m_ListThumbnail.*/SetRedraw(TRUE); 
    Arrange(LVA_DEFAULT);
}


// CThumbListView message handlers

/*
void CThumbListView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    *pResult = 0;
}

void CThumbListView::OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
}
*/
//BOOL CThumbListView::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
//{
//    // TODO: Add your specialized code here and/or call the base class
//
//    return CListCtrl::Create(dwStyle, rect, pParentWnd, nID);
//}

//BOOL CThumbListView::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
//{
//    // TODO: Add your specialized code here and/or call the base class
//    BOOL ret=CListCtrl::Create(dwStyle, rect, pParentWnd, nID);
//
//    return ret;
//}

void CThumbListView::Init(void)
{
    /*
    m_ImageListThumb.Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
    SetImageList(&m_ImageListThumb, LVSIL_NORMAL);
*/

    SHFILEINFO sfi;
    m_Icons=(HIMAGELIST) SHGetFileInfo(_T("C:\\"), 0, &sfi, sizeof(SHFILEINFO),SHGFI_SYSICONINDEX |SHGFI_ICON);

    m_SmallIcons=(HIMAGELIST) SHGetFileInfo(_T("C:\\"), 0, &sfi, sizeof(SHFILEINFO),SHGFI_SYSICONINDEX |SHGFI_SMALLICON);
    //m_ImageListThumb.Attach(hlm);
   
    SetImageList(CImageList::FromHandle(m_Icons), LVSIL_NORMAL);
    SetImageList(CImageList::FromHandle(m_SmallIcons), LVSIL_SMALL);
}