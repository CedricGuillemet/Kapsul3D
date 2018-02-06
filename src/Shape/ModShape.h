
#if !defined(AFX_CKPluginShape_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_CKPluginShape_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKPluginShape : public CKScenePlugin  
{
public:
	CKPluginShape();
	virtual ~CKPluginShape();

	virtual HWND Open(HWND Parent);
	virtual void Close();
	virtual int ScenePluginType();
	virtual void ReSize(int sx,int sy);
	virtual void LoseFocus();

	virtual CString GetName();
	virtual CString GetInfos();

	virtual bool CreatingStatus();
	virtual void SetScene(CKScene *pScene);

	virtual PrimBmp* GetAllPrimitives();
	virtual void SetPrimitive(int PrimitiveNb);
	virtual void DeleteStuff(void *pData=NULL,int DataType=0);


    virtual void LMouseDown(int X,int Y,Vertex &Pos);
    virtual void RMouseDown(int X,int Y,Vertex &Pos);
    virtual void LMouseUp(int X,int Y,Vertex &Pos);
    virtual void RMouseUp(int X,int Y,Vertex &Pos);
    virtual void MouseMove(int X,int Y,Vertex &Pos);

public:
	bool CreateSeg;
	bool CreateSeg2;
	Vertex Remem;
	int TypeEdit;
	int dx,dy;
	double nga,ngb;
	double Radius;
	CKSegment *CurSeg,*PrevCurSeg,*CurSegEd,*CurSeg2;
	CKShape *CurShape,*CurShapeEd,*CurShape2;
	int nbSegArc,nbSegNGon,nbSegStar;
	int TypeEd;
	Vertex svg;
	CKPlan Crp;
	bool daOk;
	double lng1,lng2;
	double ang1,ang2;
	CMainFrame *Diag;
	CKScene *m_Scene;
	PrimBmp daBmps;

	void CreateQuad(Vertex Center,double X,double Y);
	void CreateNGon(Vertex Center,double radius,double ngb,int nb2Seg);
	void CreateStar(Vertex Center,double radius1,double radius2,double ngb,int nb2Seg);
	void CreateArc(Vertex Center,double radius,double ngb,double ng2,int nb2Seg);

	void UpdateShape(void);
};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
