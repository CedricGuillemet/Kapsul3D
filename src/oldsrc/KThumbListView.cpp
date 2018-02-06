// ThumbListView.cpp : implementation file
//

#include "stdafx.h"
/*
//#include "tpshad.h"
#include "ThumbListView.h"
#include "kfiledialog.h"
//#include "dib.h"
*/
// CKThumbListView

#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	75

IMPLEMENT_DYNAMIC(CKThumbListView, CListCtrl)
CKThumbListView::CKThumbListView()
{
    m_TypeView=0;
}   

CKThumbListView::~CKThumbListView()
{
}

extern CKPluginManager *daLib;


BEGIN_MESSAGE_MAP(CKThumbListView, CListCtrl)
    ON_NOTIFY_REFLECT(NM_CLICK, OnClickListThumb)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClickListThumb)
    ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydownListThumb)
END_MESSAGE_MAP()

void CKThumbListView::OnClickListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
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

		CString dtr=GetItemText(pItemAct->iItem,1);

		if (!dtr.IsEmpty())
		{
			((CKFileDialog*)GetParent())->m_FileName.SetWindowText(GetItemText(pItemAct->iItem,pItemAct->iSubItem));
			SelectedFile=GetItemText(pItemAct->iItem,pItemAct->iSubItem);
		}
		else
			SelectedFile="";
		//DrawSelectedImage();
	}

	// select the item clicked
	*pResult = 0;
}
void CKThumbListView::OnDblClickListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// retrieve message info.
	LPNMITEMACTIVATE pItemAct = (LPNMITEMACTIVATE)pNMHDR;

	// determine which item receives the click
	LVHITTESTINFO  hitTest;
	memset(&hitTest, '\0', sizeof(LVHITTESTINFO));
	hitTest.pt = pItemAct->ptAction;
	/*m_ListThumbnail.*/SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hitTest);

	// draw the selected image
	if(/*hitTest.iItem != m_nSelectedItem && */hitTest.iItem >= 0)
	{
		m_nSelectedItem = hitTest.iItem;

		CString dtr=GetItemText(pItemAct->iItem,1);
		if (dtr.IsEmpty())
		{
			// get dir
			m_strImageDir+=GetItemText(pItemAct->iItem,pItemAct->iSubItem);
			m_strImageDir+="\\";
			GetImageFileNames();	// gather the image file names
			DrawThumbnails();
			((CKFileDialog*)GetParent())->m_TreeCtl.SetSelectedPath(m_strImageDir,false);
			((CKFileDialog*)GetParent())->m_FileName.SetWindowText(GetItemText(pItemAct->iItem,pItemAct->iSubItem));

		}
		else
		{
			//SelectFile
			CString ZipName,ZipRep;
			CString tempnewdir=m_strImageDir;
			tempnewdir+=GetItemText(pItemAct->iItem,pItemAct->iSubItem)+"\\";

			CKPlugin *daGen=daLib->GetSupportedResManager(tempnewdir,ZipName,ZipRep);
			if ((daGen!=NULL)&&(ZipRep.IsEmpty()))
			{
				// is a resource
				m_strImageDir=tempnewdir;
				GetImageFileNames();	// gather the image file names
				DrawThumbnails();
				((CKFileDialog*)GetParent())->m_TreeCtl.SetSelectedPath(m_strImageDir,false);
				((CKFileDialog*)GetParent())->m_FileName.SetWindowText(GetItemText(pItemAct->iItem,pItemAct->iSubItem));

			}
			else
			{
				// is really a selected file 
				((CKFileDialog*)GetParent())->OnBnClickedOk();
			}
		}
		//DrawSelectedImage();
	}

	// select the item clicked
	*pResult = 0;
}

void CKThumbListView::OnKeydownListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
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

BOOL  CKThumbListView::GetImageFileNames()
{			
	CString	strPath, strPattern;
	CFile	ImgFile;	
	BYTE	data[8] = {'\0'};	
	
	
	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;
	std::vector<PackListFiles>	VectorImageNames;
    //std::vector<FolderFileEntry>	Vffn;

	CKFileDialog* daPar=((CKFileDialog*)GetParent());

    m_VectorImageNames.erase(m_VectorImageNames.begin(), m_VectorImageNames.end());
    DeleteAllItems();

    // is resource
    CString ZipName,ZipRep;

	CKPlugin *daGen=daLib->GetSupportedResManager(m_strImageDir,ZipName,ZipRep);
	if (daGen!=NULL)
	{
		// archive
		daGen->Process(KM_SETRESOURCE,(UINT)ZipName.GetBuffer(0),0);
		//CString httg=ZipRep+"\\";
		int getents=daGen->Process(KM_LISTFILES,(UINT)ZipRep.GetBuffer(0),0);
		for (int jop=0;jop<getents;jop++)
		{
			PackListFiles *KEnts;
			KEnts=(PackListFiles *)daGen->Process(KM_LISTFILEENTRY,jop,1);
			CString sPath2 = ZipName;
			sPath2+="\\";
			sPath2+=KEnts->FileName;
			if (!KEnts->IsFile)
			{
				m_VectorImageNames.push_back(PackListFiles(KEnts->FileName,KEnts->Size,KEnts->Date,KEnts->IsFile));
			}
			else
			{
				for (int hj=0;hj<daPar->XTensions[daPar->ExtInd].Wilds.size();hj++)
				{
					if (daPar->XTensions[daPar->ExtInd].Wilds[hj]!="*")
					{
						CString dacard("."+daPar->XTensions[daPar->ExtInd].Wilds[hj]);
						if (KEnts->FileName.Find(dacard)!=-1)
							m_VectorImageNames.push_back(PackListFiles(KEnts->FileName,KEnts->Size,KEnts->Date,KEnts->IsFile));
					}
					
					else
						m_VectorImageNames.push_back(PackListFiles(KEnts->FileName,KEnts->Size,KEnts->Date,KEnts->IsFile));
						
				}
			}
		}
		daGen->Process(KM_CLOSERESOURCE);

	}

	else
	{
		CString date,size;
		BOOL	bRC = TRUE;
		CString ZipName,ZipRep;


		// Directories
		strPattern = m_strImageDir + "*.*";
		hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
		
		if (hFind!=INVALID_HANDLE_VALUE)
		{
			// filter off the system files and directories
			if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)&&
				!(strcmp(FindFileData.cFileName,".")==0)&&
				!(strcmp(FindFileData.cFileName,"..")==0))
			{  	  

				if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					m_VectorImageNames.push_back(PackListFiles(FindFileData.cFileName,0,CTime(FindFileData.ftLastWriteTime),false));
				else
				{
					CString tempnewdir=m_strImageDir;
					tempnewdir+=FindFileData.cFileName;
					tempnewdir+="\\";

					CKPlugin *daGen=daLib->GetSupportedResManager(tempnewdir,ZipName,ZipRep);
					if (daGen!=NULL)
					{
						m_VectorImageNames.push_back(PackListFiles(FindFileData.cFileName,0,CTime(FindFileData.ftLastWriteTime),false));
					}
				}
			}  
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
					if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
						m_VectorImageNames.push_back(PackListFiles(FindFileData.cFileName,0,CTime(FindFileData.ftLastWriteTime),false));
					else
					{
						CString tempnewdir=m_strImageDir;
						tempnewdir+=FindFileData.cFileName;
						tempnewdir+="\\";

						CKPlugin *daGen=daLib->GetSupportedResManager(tempnewdir,ZipName,ZipRep);
						if (daGen!=NULL)
						{
							m_VectorImageNames.push_back(PackListFiles(FindFileData.cFileName,0,CTime(FindFileData.ftLastWriteTime),false));
						}
					}

				}
			}  
			
		} // end of while loop
		
			// Files

		for (int hj=0;hj<daPar->XTensions[daPar->ExtInd].Wilds.size();hj++)
		{
			bRC = TRUE;

			//VectorImageNames.erase(VectorImageNames.begin(), VectorImageNames.end());
/*
			if (daPar->XTensions[daPar->ExtInd].Wilds[hj].IsEmpty())
				strPattern = m_strImageDir + "*.*";
			else
			*/
				strPattern = m_strImageDir + "*."+daPar->XTensions[daPar->ExtInd].Wilds[hj];

			hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
			
			if (hFind!=INVALID_HANDLE_VALUE)
			{
				// filter off the system files and directories
				if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
					!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
					!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)&&
					!(strcmp(FindFileData.cFileName,".")==0)&&
					!(strcmp(FindFileData.cFileName,"..")==0))
				{  	  

					if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
						m_VectorImageNames.push_back(PackListFiles(FindFileData.cFileName,FindFileData.nFileSizeLow,CTime(FindFileData.ftLastWriteTime),1));
				}  
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
						if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
							m_VectorImageNames.push_back(PackListFiles(FindFileData.cFileName,FindFileData.nFileSizeLow,CTime(FindFileData.ftLastWriteTime),true));
					}
				}  
				
			} // end of while loop
			
			// close the search handle
			::FindClose(hFind);

		}
	}
return TRUE;

}

void  CKThumbListView::DrawThumbnails()
{
	CBitmap*    pImage = NULL;	
	HBITMAP     hBitmap = NULL;
	HPALETTE    hPal = NULL;
	HDC			hMemDC = NULL;	
	HGDIOBJ		hOldObj = NULL;
	POINT		pt;

	CFile		ImgFile;
//	CDib		dib;
	CString		strPath;
	int			i=0;
    int nGap = 6;

	// draw the thumbnails
	std::vector<PackListFiles>::iterator	iter;
	for(iter = m_VectorImageNames.begin(); iter != m_VectorImageNames.end(); iter++)
	{		
		
		// put item to display
		// set the image file name as item text
        SHFILEINFO sfi;
		

		CString nul1,nul2;
		bool FocusInPack=(daLib->GetSupportedResManager(m_strImageDir,nul1,nul2)!=NULL);
        CString tmpstr=m_strImageDir+m_VectorImageNames[i].FileName;
		if (FocusInPack)
		{
			char temppath[512];
			GetTempPath(512,temppath);

			if (m_VectorImageNames[i].IsFile)
			{
				CString daf=temppath+m_VectorImageNames[i].FileName;
				FILE *ctf=fopen(daf,"wb");
				SHGetFileInfo(daf, 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON |SHGFI_TYPENAME | SHGFI_SMALLICON);
				fclose(ctf);
				DeleteFile(daf);
			}
			else
				SHGetFileInfo(temppath, 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON |SHGFI_TYPENAME | SHGFI_SMALLICON);

		}
		else
		{
	        SHGetFileInfo(tmpstr, 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON |SHGFI_TYPENAME | SHGFI_SMALLICON);
		}
        

		InsertItem(i, m_VectorImageNames[i].FileName, sfi.iIcon);
        //InsertItem(i, m_VectorImageNames[i].Name, i);

		CString addl;
		if (m_VectorImageNames[i].IsFile)
		{
			addl.Format("%d KB",(m_VectorImageNames[i].Size/1024));
			SetItemText(i,1,addl);
		}
		
		SetItemText(i,2,sfi.szTypeName/*m_VectorImageNames[i].IsFile?"File":"Folder"*/);

		addl=m_VectorImageNames[i].Date.Format("%d/%m/%Y %H:%M");;

        SetItemText(i,3,addl);
        

		// get current item position	 
		/*m_ListThumbnail.*/ //GetItemPosition(i, &pt);	 
	  
		// shift the thumbnail to desired position
		pt.x = nGap + i*(THUMBNAIL_WIDTH + nGap);
		/*m_ListThumbnail.*/ //SetItemPosition(i, pt);
		i++;
			
		delete pImage;
	}

	// let's show the new thumbnails
	///*m_ListThumbnail.*/SetRedraw(TRUE); 
    Arrange(LVA_DEFAULT);
}


// CKThumbListView message handlers

/*
void CKThumbListView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    *pResult = 0;
}
*/
/*
void CKThumbListView::OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
}
*/
//BOOL CKThumbListView::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
//{
//    // TODO: Add your specialized code here and/or call the base class
//
//    return CListCtrl::Create(dwStyle, rect, pParentWnd, nID);
//}

//BOOL CKThumbListView::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
//{
//    // TODO: Add your specialized code here and/or call the base class
//    BOOL ret=CListCtrl::Create(dwStyle, rect, pParentWnd, nID);
//
//    return ret;
//}

void CKThumbListView::Init(void)
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