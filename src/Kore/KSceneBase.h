// Kapsul Core Library
// Copyright © 1999 - 2001, Cédric Guillemet
//
// Contact: lacrapul@club-internet.fr
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef CKSceneBaseH
#define CKSceneBaseH

#include "Kapsul3D.h"
#include "KRenderer.h"

class UndoEntryCount
{
public:
	void *TargetPtr;
	int TargetType;
	inline UndoEntryCount(void *tgptr,int tgtype)
	{
		TargetPtr=tgptr;
		TargetType=tgtype;
	}
	~UndoEntryCount() {}
};


class CKBackPic
{
public:
	CKBackPic(CKScene *pScene) 
	{
		Opacity=0.5f;
		Active=false;
		Keep=true;
		tex=new CKTexture(pScene);
	};

	~CKBackPic() {};
	bool Active;
	bool Keep;
	MYPOINT Origin;
	MYPOINT Size;
	float Opacity;
	CKTexture *tex;
};

class ViewInfos
{
public:
	ViewInfos() {WheelChange=false;};
	~ViewInfos() {};

	int ViewType; // save view type
	CKCamera *cam;
	Vertex ViewNg,ViewPos,ViewSize;

	// redo
	int RedoViewType; // save view type
	CKCamera *Redocam;
	Vertex RedoViewNg,RedoViewPos,RedoViewSize;
	bool WheelChange;
};

class KAPSUL_DESC CKSceneBase
{
    private:
		bool RecCountSkel(CKBone *daBone);


    public:
		CKBackPic *m_bkTop,*m_bkFront,*m_bkLeft;
		Vertex ClipOrigin,ClipSize;

	    void InitAllTag(int Value,int PlugType);
		void UpdateTaged(int PlugType);


		
		int GetNbSelectedMeshs(void);

	    void *GetByUnique(unsigned int _Unique,int Type);
        CKSceneBase(/*CKSceneBase *daPrev,CKSceneBase *daNext*/);
        ~CKSceneBase();

    //CKSceneBase *Prev,*Next;


    // -- Shape ----------------------------------------------------------------

    
    CKShape *AddShape();
	void AddShape(CKShape *daShp);


    // -- Selection ------------------------------------------------------------

//    void InsertShape(CKShape *InsShape);
    CKShape *Sel;
    //KSelection *cSel;
	//void SelectAll(void);

	// -- Suppress

    void DelSkeleton(CKSkeleton *pSkel);
    void DelShape(CKShape *pShape);
    void DelMesh(CKMesh *pObj);
	void DelPatch(CKPatch *pPatch);
	void DelEntity(CKEntity *pEntity);
	void DelCamera(CKCamera *pCam);

    bool DelShapeSeg(void);
    // -- Camera ---------------------------------------------------------------

    CKCamera *AddCam();
    //char * GenerateCamName();
    
    //Camera *GetCamera(char * CamName);

    // -- CKMesh ---------------------------------------------------------------


    CKMesh * AddMesh();
    void AddMesh(CKMesh *pMesh);

	// -- Patch ----------------------------------------------------------------

    
    CKPatch *AddPatch();
	

    
	vector<CKSkeleton *>m_Skels;
	vector<CKCamera *>m_Cameras;
	vector<CKMesh *>m_Meshes;
	vector<CKEntity *>m_Entities;
	vector<CKShape *>m_Shapes;
	vector<CKPatch *>m_Patches;

    CKSkeleton *AddSkeleton();

    // -- Material -------------------------------------------------------------

    CKTexture *NextTexture,*FirstTexture;
    CKTexture *AddTex(CString TexName);
	CKTexture *GetTexByShortName(CString TexName);
	void DelTex(CKTexture *daTex);
	bool IsTextureStillUsed(CKTexture *daTex);
	//void RecalcTextureIndices(void);
	int TexUnique;

    // -- Vert Buf -------------------------------------------------------------

    VertBuf *FirstBufVert,*NextBufVert;
    void AddBufVert(Vertex *DaVert,int Index=0);
    void AddBufVert(Vertex *DaVert,CKMesh *Obj,int Index=0);
	void AddBufVert(Vertex *DaVert,CKPatch *daPatch,int Index);
	void AddBufVert(Vertex *DaVert,CKCamera *Cam,int Index);
	void AddBufVert(Vertex *DaVert,CKShape *Shp,CKSegment *Seg);
	void AddBufVert(Vertex *DaVert,CKSkeleton *daSkel,CKBone *daBone=NULL);
	void AddBufVert(Vertex *DaVert,CKEntity *daEnt,int Index);

    void DeleteBufVert(void);
	inline void DeleteBufVert(VertBuf *daBufVert);

    void TranslateBuf(CKPlan *dap,Vertex Trans);
	void TranslateBuf(Vertex Trans);
    void Flush(void);
    void UpdateBuf(void);    
    void RotateBuf(CKPlan *dap,Vertex Center);
	void ScaleBuf(CKPlan *dap,Vertex Center,Vertex ScaleVal);
	bool SymBuf(Vertex Factor);
	bool TaperBuf(double Facteur,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center);
	bool SquizBuf(double Facteur,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center);
	bool BendBuf(double ngb,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center);

    Vertex GetMinBuf(void);
    Vertex GetMaxBuf(void);
    void RemoveBufUnselected(void);

    void CopySelectedTo(CKSceneBase *DstDk);

    void DeleteSelected(void);


	CKHandles Hand3D;
	CKHandles HandUV;

    // -- Script ---------------------------------------------------------------

    // -- Modified -------------------------------------------------------------
    
    bool Modified;

    CString temp;

    int FrameInd;

    // -- Min/Max --------------------------------------------------------------

    bool GetMinMax(long Stat,Vertex *DstMin,Vertex *DstMax);
	

    // -- AXIS -----------------------------------------------------------------

    Vertex Axis;
	void SetAxis(Vertex daAxis);

    // -- Shape to surface -----------------------------------------------------

	// infos de vues
	bool FullScreen;

	CKCamera **cam;
	Vertex *ViewNg,*ViewPos;
	CKCamera Perspective[4];

	vector<ViewInfos*> VUndoInf[4];
	vector<ViewInfos*> VRedoInf[4];

	void ActiveViewToUndo();
	void UndoViewChange();
	void RedoViewChange();
	void ActiveViewToCurrentRedo();
	ViewInfos *LatestVI;
	//void ActiveViewToRedo();
	
	void SetVIWheel(bool UseWheel);
	bool GetVIWheel();

	// --
	Vertex *ViewSize,*tmppos,*tmpViewSize,*TmpViewNg;

	//float *light1_pos;
    POINT *ViewStart,*ViewEnd;
    int *ViewType;
    int Active;
    int AncActive;

	CKRenderer *m_Renderer;

    //int **viewport;
	/*
    double **mvmatrix,**projmatrix;

    int viewport2;
    double *mvmatrix2,*projmatrix2;
*/
    void ComputeSize(void);
    bool SetActive(int X, int Y);

	float Height,Width,Left,Top;
    int *State;

	void ReSize(int daWidth,int daHeight);
	int daViewMode;

	// inherant a l'editeur seulement
	int TabId;

	// Delete
	bool DelShapeVert(void);

	// edit
	bool Snap,Crossing,Center;
	Vertex SnapVal;
	int AngleSnapVal;
	int SnapValCounter;
	int AngleValCounter;
	bool m_GridVisible[4];

	// names
	CString CurrentName;

	bool GenerateName(int NameType);
	void *GetByName(CString name,int NameType);

	// snap
	//Vertex snap;

	//CSkyBox *daSky;

	// KeyFrame

    // Maps
    //CMaps *maps;
    void DeleteAll(void);

	// perspective
	
	CKSkyBox m_skybox[4];

	// UV Edit
	UVCoordsEdit *UVEdit;
	int m_CountUV;
	bool m_UVSelUpdate;
	//void SelectedToUVBuffer(int Layer);
	//void EnableUVSelectionUpdate(bool Enable);
	//void TranslateUVBuf(CKPlan *dap,MYPOINT Trans);
/*
	void UpdateUVBuf(void);;
	void RotateUVBuf(CKPlan *dap,MYPOINT Center,float angle);
	void ScaleUVBuf(CKPlan *dap,MYPOINT Center,MYPOINT ScaleVal);
*/
//	KeyFrame * FirstKF,*NextKF;
	void AddKF(void);

	// Undo/Redo
	CKUndoRedo *FirstUndo,*NextUndo;
	CKUndoRedo *FirstRedo,*NextRedo;

	CKUndoRedo *AddUndo(CString _PlugName,int _nbEntries);
	void AddRedo(CKUndoRedo *daUndo);
	void AddUndo(CKUndoRedo *daRedo);
	void Undo(CKScenePlugin *gen);
	void Redo(void);
	void SetSelectedToAfterUndo(CString PlugName,int UndoType);
	void SetSelectedToBeforeUndo(CString PlugName,int UndoType);
	void SetSelectedToAfterUndoNoADD(); //char *PlugName,int UndoType)
	void SetSelectedToBeforeUndoNoADD();

	void SetRenderer(CKRenderer *pRenderer);

	// entity
	CKEntity *FirstEntity,*NextEntity;
	CKEntity *AddEntity(CString EntType);
	void AddEntity(CKEntity *pEntity);

	// selection hooks
	Vertex HookMinSel,HookMaxSel;
	UVCoords UVMinSel,UVMaxSel;
	bool SomeThingSel;

	int MeshCreationCounter;
	void ChangeGrid(int NewGridInd);
	void ChangeAngle(int NewAngleInd);
	vector <UndoEntryCount*> UndoRedoEntriesCount;

	void SetSceneForReading(bool IsReading);
	int nbAddedMesh,nbAddedShape,nbAddedPatch,nbAddedSkel,nbAddedCamera,nbAddedEntity;
	bool m_IsReading;

//	void UpdateMinMaxUVBuf(void);
/*
    CDC* m_pCDC;	// WinGDI Device Context
    HGLRC m_hRC;	// OpenGL Rendering Context
*/
	/*
	bool BendUVBuf(double ngb,int Sens,MYPOINT center);
	bool SquizUVBuf(double Facteur,int Sens,MYPOINT center);
	bool TaperUVBuf(double Facteur,int Sens,MYPOINT center);
*/
	void InitDefaultTexture();
	virtual void UpdateSmthSel(void);
};
//---------------------------------------------------------------------------
#endif
