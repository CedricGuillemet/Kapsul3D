#if !defined(AFX_CKPluginSkeleton_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_CKPluginSkeleton_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKPluginSkeleton : public CKScenePlugin  
{
public:
	CKPluginSkeleton();
	~CKPluginSkeleton();

	HWND Open(HWND Parent);
	void Close();
	int ScenePluginType();
	void ReSize(int sx,int sy);
	void LoseFocus();

	CString GetName();
	CString GetInfos();

	bool CreatingStatus();
	void SetScene(CKScene *pScene);

	CBitmap *GetBitmap();
	CBitmap *GetHotBitmap();

	void DeleteStuff(void *pData=NULL,int DataType=0);

    void LMouseDown(int X,int Y,Vertex &Pos);
    void RMouseDown(int X,int Y,Vertex &Pos);
    void LMouseUp(int X,int Y,Vertex &Pos);
    void RMouseUp(int X,int Y,Vertex &Pos);
    void MouseMove(int X,int Y,Vertex &Pos);

public:
	HWND SkelettonDiag;
	CKScene *m_Scene;
	CBitmap m_Dib,m_Dib2;
	CMainframe *m_Main;
	bool CreateSeg;
	int TypeEdit;
	CKBone *myBone;
	Vertex Remem;
	Vertex Remem2;
	CKSkeleton *CurSkel;
	CKMesh *CurMesh;
	int dx,dy;
	Vertex remem;
	CKSkeleton *CurrentSkel,*AnimSkel;
	CKBone *CurrentBone;

	void ListSkelettons(void);
};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
