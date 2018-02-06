#include "stdafx.h"
#include "CKProject.h"
#include "Newfolder.h"

BEGIN_MESSAGE_MAP(CKProject,CProjectTree)
	//{{AFX_MSG_MAP(CProjectTree)
	ON_COMMAND(ID__ADDFILESTOPROJECT, OnAddFileToProject)
	ON_COMMAND(ID__PROPERTY, OnProperty)
	ON_COMMAND(ID_NEWFOLDER, OnNewFolder)
	ON_COMMAND(ID__BUILD, OnBuild)
	ON_COMMAND(ID__RUN, OnRun)
	ON_COMMAND(ID__REMOVE, OnDelete)
	ON_COMMAND(ID__ADDFILESTOFOLDER, OnAddFileToFolder)
	ON_COMMAND(ID__OPEN, OnOpen)
	ON_COMMAND(ID__COMPILE, OnCompile)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern CMainFrame *mainf;
extern CString ReadFilter;
extern CKapsulApp theApp;

void CKProject::ReadFolder(HTREEITEM LocalRoot,node::const_iterator child)
{
	char value[256];
	char File[MAX_PATH],Ext[MAX_PATH];


	child->get_attr("name",value);
	CString Foldname(value);
	HTREEITEM fldrt=InsertItem(value,1,1,LocalRoot);
	child->get_attr("xpd",value);
	bool xpd=false;
	if (value[0]=='1') xpd=true;

	child->get_attr("extension",value);
	m_Extensions.SetEntry(Foldname,CString(value));

	node::const_iterator child3(child->begin()), child_end(child->end());
	for (; child3 != child_end; ++child3) 
	{
		if (child3->is_text()) continue;

		if (strcmp(child3->get_name() ,"File")==0)
		{
			child3->get_attr("name",value);

			CKProjectFile* perf;
			perf=new CKProjectFile;
			
			_splitpath(value,NULL,NULL,File,Ext);
			strcat(File,Ext);

			perf->FileName=File;
			perf->FilePath=value;

			PrjFiles.push_back(perf);
			InsertItem(File,2,2,fldrt);
		}

		if (strcmp(child3->get_name() ,"Folder")==0)
		{
			ReadFolder(fldrt,child3);
		}
	}
	if (xpd) Expand(fldrt,TVE_EXPAND);
}



void CKProject::LoadProject(CString ProjectPath)
{
	init init;
	DeleteAllItems();
    int i=0;
    CString temp,temp2;
    
	// MAP Paths
	char value[256];
	
	tree_parser parser(ProjectPath);

	if (!parser) 
//		MessageBox(NULL,"Project not found.","Error reading project",MB_ICONERROR|MB_OK);
		MessageBox("Project not found.","Error reading project",MB_ICONERROR|MB_OK);
	else
	{
		CloseProject();

		m_ProjectName=ProjectPath;

		node &root = parser.get_root_node();

		node::const_iterator child(root.begin()), child_end(root.end());
		for (; child != child_end; ++child) 
		{
			if (child->is_text()) continue;


			// standards options
			if (strcmp(child->get_name() ,"Project")==0)
			{
				child->get_attr("name",value);
				prjrt=InsertItem(value,0,0);

				node::const_iterator child2(child->begin()), child_end(child->end());
				for (; child2 != child_end; ++child2) 
				{
					if (child2->is_text()) continue;
						
					if (strcmp(child2->get_name() ,"Folder")==0)
					{
						ReadFolder(prjrt,child2);
					}
				}
			}
		}
	}
	/*
	HTREEITEM prjrt=InsertItem("UnamedProject",0,0);

	HTREEITEM Grp1=InsertItem("Maps",1,1,prjrt);
	HTREEITEM Grp2=InsertItem("Meshes",1,1,prjrt);
	HTREEITEM Grp3=InsertItem("Scripts",1,1,prjrt);
*/
	Expand(prjrt,TVE_EXPAND);
	//SaveProject(&m_Project,"pouet");

}


CString CKProject::SaveFile(HTREEITEM LocalRoot)
{
	CString out="";

	out+="<File name=\"";
	out+=FindFileByName(GetItemText(LocalRoot))->FilePath;
	out+="\" />\n";

	return out;
}

CString CKProject::SaveFolder(HTREEITEM LocalRoot)
{
	HTREEITEM it2;
	CString out="";

	out+="<Folder name=\"";
	out+=GetItemText(LocalRoot);
	out+="\" extension=\"";
	out+=m_Extensions.GetString(GetItemText(LocalRoot));
	out+="\" xpd=\"";
	out+=(EnsureVisible(LocalRoot)?"1":"0");
	out+="\" >\n";

	// files
	it2=GetChildItem(LocalRoot);
	while (it2!=NULL)
	{
		switch(GetItemId(it2))
		{
		case 1: //folder
			out+=SaveFolder(it2);
			break;
		case 2: // file
			out+=SaveFile(it2);
			break;
		}

		it2=GetNextItem(it2,TVGN_NEXT);
	}


	out+="</Folder>\n";

	return out;
}

void CKProject::SaveProject(CString ProjectPath)
{
	CString out;
	HTREEITEM it;
	int extInd=0;
	int FileInd=0;

	out="<?xml version=\"1.0\" standalone=\"yes\"?>\n"
		"<Workspace>\n"
		"<!-- \n"
		"	Kapsul Project\n"
		"-->\n"
		"<Project name=\"";
	
	it=GetFirstVisibleItem();
	out+=GetItemText(it);
	out+="\">\n";

	it=GetChildItem(it);
	// projects
	while (it!=NULL)
	{
		switch(GetItemId(it))
		{
		case 1: //folder
			out+=SaveFolder(it);
			break;
		case 2: // file
			out+=SaveFile(it);
			break;
		}

		it=GetNextItem(it,TVGN_NEXT);
	}

	out+="</Project>\n</Workspace>";

	FILE *fp=fopen("Yop.xml","wt");
	if (fp!=NULL)
	{
		fwrite(out.GetBuffer(0),out.GetLength(),1,fp);
		fclose(fp);
	}
	
}

CKProjectFile* CKProject::FindFileByName(CString dFileName)
{
	for (vector<CKProjectFile*>::iterator i = PrjFiles.begin(); i != PrjFiles.end(); i++)
	{
		if ((*i)->FileName==dFileName)
		{
			return (*i);
		}
	}
	return NULL;
}

void CKProject::AddFileToProject(CString dFileName)
{
	char File[MAX_PATH],Ext[MAX_PATH];
	_splitpath(dFileName,NULL,NULL,File,Ext);

	CString sExt;
	strcat(File,Ext);
	sExt=Ext;
	sExt.MakeUpper();

	for (int i=0;i<m_Extensions.GetNbEntries();i++)
	{
		m_Extensions.GetEntry(i)->vals.MakeUpper();
		if (m_Extensions.GetEntry(i)->vals.Find(sExt)!=-1)
		{
			HTREEITEM fold=FindFolder(m_Extensions.GetEntry(i)->m_Name);
			if (fold!=NULL)
			{
				AddFileEntry(fold,dFileName);
				return;

			}
			else
			{
				AddFileEntry(prjrt,dFileName);
				return;
			}
		}
	}
	AddFileEntry(prjrt,dFileName);
}

HTREEITEM CKProject::RecFindFolder(HTREEITEM LocalRoot,CString FoldName)
{
	HTREEITEM it2;
	HTREEITEM RetVal=NULL;
	it2=GetChildItem(LocalRoot);
	while (it2!=NULL)
	{
		if (GetItemId(it2)==1)
		{
			if (GetItemText(it2)==FoldName) return it2;
			RetVal=RecFindFolder(it2,FoldName);
			if (RetVal!=NULL) return RetVal;
		}

		it2=GetNextItem(it2,TVGN_NEXT);
	}
	return RetVal;

}

HTREEITEM CKProject::FindFolder(CString FoldName)
{
	HTREEITEM it,RetVal=NULL;
	it=GetFirstVisibleItem();
	it=GetChildItem(it);

	// projects
	while (it!=NULL)
	{
		if (GetItemId(it)==1)
		{
		
			if (GetItemText(it)==FoldName) return it;
			RetVal=RecFindFolder(it,FoldName);
			if (RetVal!=NULL) return RetVal;
		}

		it=GetNextItem(it,TVGN_NEXT);
	}

	return RetVal;
}

void CKProject::AddFileEntry(HTREEITEM LocalRoot,CString FullFilePath)
{
	char File[MAX_PATH],Ext[MAX_PATH];
	_splitpath(FullFilePath,NULL,NULL,File,Ext);
	strcat(File,Ext);

	InsertItem(File,2,2,LocalRoot);

	CKProjectFile* perf;
	perf=new CKProjectFile;
	
	perf->FileName=File;
	perf->FilePath=FullFilePath;

	PrjFiles.push_back(perf);
}

void CKProject::OnAddFileToProject(void)
{
	CString fileName;
	BXFileDialog dlg(TRUE, TRUE, TRUE);


	LPTSTR pch = ReadFilter.GetBuffer(1);//szFilter.GetBuffer(0); // modify the buffer in place
	                                    // MFC delimits with '|' not '\0'
	while ((pch = _tcschr(pch, '|')) != NULL)
			*pch++ = '\0';

	CString strTitle("Select files to open");

	dlg.m_ofn.lpstrFilter = ReadFilter ;
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlg.m_ofn.hwndOwner = AfxGetMainWnd()->m_hWnd; 
	dlg.m_ofn.Flags|= OFN_ALLOWMULTISELECT ;

	dlg.SetAppearance(BXFileDialog::eAppearance::APPEARANCE_VSDOTNET);

	if (dlg.DoModal()==IDOK)
	{
		int nCount = 0;
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			//OpenCmdLine(dlg.GetNextPathName(pos).GetBuffer(0));
			AddFileToProject(dlg.GetNextPathName(pos));
			nCount++;
		}
		m_ProjectModified=true;
	}
}
void CKProject::OnProperty() 
{
	MessageBox("On property");
}

void CKProject::OnNewFolder() 
{
	CNewFolder nfd;

	if (nfd.DoModal()==IDOK)
	{
		CString FolderName,FolderExt;

		HTREEITEM dait;
		FolderName=nfd.FolderName;
		FolderExt=nfd.FolderExt;

		dait=InsertItem(FolderName,1,1,GetFirstSelectedItem());
		SelectItem(dait);
		m_Extensions.SetEntry(FolderName,FolderExt);
		m_ProjectModified=true;
	}
}

void CKProject::OnBuild()
{
	MessageBox("Build");
}

void CKProject::OnRun()
{
	MessageBox("Run");
}

void CKProject::OnDelete()
{
	HTREEITEM it=GetFirstSelectedItem();
	while (it!=NULL)
	{
		CString itfi=GetItemText(it);
		CKProjectFile* prjf=FindFileByName(itfi);
		if (prjf!=NULL)
		{
			DeleteItem(it);
			//PrjFiles.erase(prjf);
		}
		it=GetNextSelectedItem(it);
		m_ProjectModified=true;
	}
}

void CKProject::OnAddFileToFolder()
{
	CString fileName;
	BXFileDialog dlg(TRUE, TRUE, TRUE);


	LPTSTR pch = ReadFilter.GetBuffer(1);//szFilter.GetBuffer(0); // modify the buffer in place
	                                    // MFC delimits with '|' not '\0'
	while ((pch = _tcschr(pch, '|')) != NULL)
			*pch++ = '\0';

	CString strTitle("Select files to open");

	dlg.m_ofn.lpstrFilter = ReadFilter ;
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlg.m_ofn.hwndOwner = AfxGetMainWnd()->m_hWnd; 
	dlg.m_ofn.Flags|= OFN_ALLOWMULTISELECT ;

	dlg.SetAppearance(BXFileDialog::eAppearance::APPEARANCE_VSDOTNET);

	if (dlg.DoModal()==IDOK)
	{
		int nCount = 0;
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			//OpenCmdLine(dlg.GetNextPathName(pos).GetBuffer(0));
			//AddFileToProject();
			AddFileEntry(GetFirstSelectedItem(),dlg.GetNextPathName(pos));
			nCount++;
		}
		m_ProjectModified=true;
	}
}

void CKProject::OnOpen()
{
	HTREEITEM it=GetFirstSelectedItem();
	while (it!=NULL)
	{
		CString itfi=GetItemText(it);
		CKProjectFile* prjf=FindFileByName(itfi);
		if (prjf!=NULL)
		{
			// test file existenz :)
			FILE *fp=fopen(prjf->FilePath.GetBuffer(0),"rb");
			if (fp==NULL)
			{
				if(MessageBox("The file doesn't exist. Do you want to create it?","File not found",MB_YESNO)==IDYES)
				{
					fp=fopen(prjf->FilePath.GetBuffer(0),"wb");
					fclose(fp);
					theApp.OpenCmdLine(prjf->FilePath.GetBuffer(0));
				}
			}
			else
			{
				fclose(fp);
				theApp.OpenCmdLine(prjf->FilePath.GetBuffer(0));
			}
		}
		it=GetNextSelectedItem(it);
	}
}

void CKProject::OnCompile()
{
	MessageBox("Compile");
}

void CKProject::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	HTREEITEM it=GetFirstSelectedItem();
	if (GetItemId(it)==2)
		OnOpen();
	else
		CProjectTree::OnLButtonDblClk(nFlags, point);
}

// Erase All
void CKProject::CloseProject(void)
{
	DeleteAllItems();
	m_ProjectName="";
	m_ProjectModified=false;

	m_Extensions.EraseAll();
	PrjSettings.EraseAll();

	PrjFiles.erase(PrjFiles.begin(),PrjFiles.end());
}