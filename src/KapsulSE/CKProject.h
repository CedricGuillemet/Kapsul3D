#if !defined(AFX_CKPROJECT_H__64692D59_7D67_42F8_A086_CED95F74A97A__INCLUDED_)
#define AFX_CKPROJECT_H__64692D59_7D67_42F8_A086_CED95F74A97A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectTree.h"
#include <vector>
using std::vector;

#include "ProjectTree.h"


class CKProjectFile 
{

public:
	CKProjectFile() {};
	~CKProjectFile() {};

	CString FilePath;
	CString FileName;
	CKHashTable Settings;
};

class CKProject : public CProjectTree //,public CTreeCtrl
{
public:
	CKProject() {m_ProjectName="";};
	~CKProject() {};

	CString m_ProjectName;
	bool m_ProjectModified;

	CKHashTable m_Extensions;
	vector<CString> m_PrjFiles;
	CKHashTable PrjSettings;

	vector<CKProjectFile*> PrjFiles;


	void LoadProject(CString ProjectPath);
	void SaveProject(CString ProjectPath);
	void CloseProject(void);

	void ReadFolder(HTREEITEM LocalRoot,node::const_iterator child);
	CString SaveFolder(HTREEITEM LocalRoot);
	CString SaveFile(HTREEITEM LocalRoot);
	void AddFileToProject(CString dFileName);

	HTREEITEM FindFolder(CString FoldName);
	HTREEITEM RecFindFolder(HTREEITEM LocalRoot,CString FoldName);

	void AddFileEntry(HTREEITEM LocalRoot,CString FullFilePath);

	CKProjectFile* FindFileByName(CString dFileName);
	HTREEITEM prjrt;

protected:
	//{{AFX_MSG(CKProject)

	afx_msg void OnAddFileToProject(void);
	afx_msg void OnProperty();
	afx_msg void OnNewFolder();
	afx_msg void OnBuild();
	afx_msg void OnRun();
	afx_msg void OnDelete();
	afx_msg void OnAddFileToFolder();
	afx_msg void OnOpen();
	afx_msg void OnCompile();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif