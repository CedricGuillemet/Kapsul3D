
#if !defined(AFX_CKPluginModifier_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_CKPluginModifier_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct 
{
    int daTag;
    CKPolygon *daf;
}UnifFace;

/*
class ModifPoly
{
public:
	ModifPoly() {};
	~ModifPoly() {};

	CKPolygon *pl;
	CKMesh *m_Mesh;
};
*/
typedef struct
{
    Vertex *Dot;
    bool HasScale;
    double ScaleX,ScaleY;
    bool HasRotate;
    double RotatX,RotatY,RotatZ;

} ModifVert;

class CKPluginModifier : public CKScenePlugin
{
public:
	CKPluginModifier();
	virtual ~CKPluginModifier();

	virtual HWND Open(HWND Parent);
	virtual void Close();
	virtual int ScenePluginType();
	virtual void ReSize(int sx,int sy);
	virtual void LoseFocus();
	int GetCursor(int X,int Y);
	virtual CString GetName();
	virtual CString GetInfos();

	virtual bool CreatingStatus();
	virtual void SetScene(CKScene *pScene);
	virtual void DeleteStuff(void *pData=NULL,int DataType=0);
	virtual void UpdateSelection();
	void UpdateStuff(void *pObject,int PlugType);

	virtual DWORD OwnerDraw(CKRenderer *pRenderer,int ViewNb);

	virtual CBitmap *GetBitmap();

    virtual void LMouseDown(int X,int Y,Vertex &Pos);
    virtual void RMouseDown(int X,int Y,Vertex &Pos);
    virtual void LMouseUp(int X,int Y,Vertex &Pos);
    virtual void RMouseUp(int X,int Y,Vertex &Pos);
    virtual void MouseMove(int X,int Y,Vertex &Pos);

public:

	CKScene *m_Scene;
	int CreateSeg;
	Vertex remem,Remem2,Remem;
	int TypeEd;
	int TypeEdit;
	CModDiag *ModDiag;
	CBitmap m_Dib,m_Dib2;
	CKPlan Crp;
	CKPlan dap;
	int dx,dy;
	CKUndoRedo *CurrentUndo;

	int LastAction;

	void FlipNormalFaces(void);
	void UnifyNormalFaces(void);
	void RecurseUnif(UnifFace *dau,int nbu,int v1,int v2);

	void SetSelectedToAfterUndo(void);
	void SetSelectedToBeforeUndo(void);
	void BeginCutter(int X,int Y,Vertex *Pos);
	void ValidateCutter(int X,int Y,Vertex *Pos);
	void UnionObject(CKMesh *Obj1,CKMesh *Obj2);
	void SubObject(CKMesh *Obj2,CKMesh *Obj1);
	bool AddMesh(CKMesh *Obj2,CKMesh *Obj1);
	void UpdateBSPTrees( );
	void HollowObject(CKMesh *Obj);
	void Symetry(Vertex value);
	void Spherize(double ScVal);
	void RotateBuf(Vertex Vect,double ng);
	void HollowSelectedObject();
	void UpdateBspTree(CKMesh *daMesh);
	void SubSelectedObject(void);
	void AddSelectedObject(void);
	CKMesh *BuildCutter(Vertex v1,Vertex v2);
	int GetNbSelectedObjects(void);

	// Modif Polys

	vector<CKMesh*> m_BufMesh;
	CKMesh *m_Mesh2DelStart;
	CKMesh *CurLatheMesh;
	CKShape *CurLatheShp;

	void PutSelectedToBuf(void);
	void Explode(float Decal);
	void ApplyModifs(void);
	void DelSelectedMesh(void);
	void ExtrudIt();
	vector<CKShape*> m_shp;

	void Fractalize();
	int m_Seed;
	int m_TailleOrg;

	// extrud
	CKShape *SPath,*SShape;
	int ModifAv;
	int trX,trY;
	void GenerateObject(void);
	int ToSurface(CKShape *daShp,int TroncFaces);
	int Delaunay(int N, double* x, double* y, int& numTriangles, TriangleList*& triangle);
	int FindModif(Vertex *vt);
	CKMesh *LoftMesh;
	ModifVert AllModif[100];
	Vertex PrevVal,*MoveVert,DaVal;
	int tmpMod;

	bool bSplinedPath,bSplinedShape;

	void SubDivide(int Iter);

	CKUVEdit m_KUVEdit;

};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
