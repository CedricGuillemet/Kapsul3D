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

#ifndef DeskH
#define DeskH

#include "Kapsul3D.h"

class __declspec( dllexport ) Desk
{
    private:



    public:
        Desk(Desk *daPrev,Desk *daNext);
        ~Desk();

    Desk *Prev,*Next;


    // -- Shape ----------------------------------------------------------------

    Shape *NextShape,*FirstShape;
    AddShape();


    // -- Selection ------------------------------------------------------------

    InsertShape(Shape *InsShape);
    Shape *Sel;
    Selection *cSel;

    DelSkeletton(Skeletton *daSkel);
    DelShape(Shape *daShape);
    DelObject(Object *daObj);
    bool DelShapeSeg(void);
    // -- Camera ---------------------------------------------------------------

    Camera *NextCam,*FirstCam;
    AddCam();
    //char * GenerateCamName();
    DelCam(Camera *daCam);
    Camera *GetCamera(char * CamName);

    // -- Object ---------------------------------------------------------------

    Object *NextObject,*FirstObject;
    AddObject();
    AddObject(Object *daObj);
    Object *GetObject(char *ObjName);

    // -- Particle -------------------------------------------------------------
/*
    Emitter *NextEmit,*FirstEmit;
    AddEmit();
*/
    // -- Private Data ---------------------------------------------------------

    CPrivateData *NextData,*FirstData;
    CPrivateData *AddPrivate(char *Name);
    CPrivateData *GetPrivate(char *Name);

    // -- Skeletton ------------------------------------------------------------

    Skeletton *NextSkel,*FirstSkel;
    AddSkel();
    AddPath();

    // -- Material -------------------------------------------------------------
/*
    Material *NextMat,*FirstMat;
    AddMat();
    Material *GetMaterial(char *MatName);
*/
    CTexture *NextTexture,*FirstTexture;
    CTexture *AddTex(char *TexName);

    // -- FileName -------------------------------------------------------------
	char *FileName;
    char *Name;
    bool IsNamed;
    void SetName(char *val);

    // -- Vert Buf -------------------------------------------------------------

    VertBuf *FirstBufVert,*NextBufVert;
    void AddBufVert(Vertex *DaVert,int Index=0);
    void AddBufVert(Vertex *DaVert,Object *Obj,int Index=0);
    void DeleteBufVert(void);
    void TranslateBuf(Vertex Trans);
    void Flush(void);
    void UpdateBuf(void);    
    void RotateBuf(Plan *dap,Vertex Center);
	void ScaleBuf(Plan *dap,Vertex Center,Vertex ScaleVal);
    Vertex GetMinBuf(void);
    Vertex GetMaxBuf(void);
    void RemoveBufUnselected(void);

    void CopySelectedTo(Desk *DstDk);

    void DeleteSelected(void);

    // -- Lights ---------------------------------------------------------------

    Light *FirstLight,*NextLight;
    AddLight();
	DelLight(Light *daLight);

    // -- Script ---------------------------------------------------------------

    Script *FirstScript,*NextScript;
    AddScript();

    // -- Modified -------------------------------------------------------------
    
    bool Modified;

    char *temp;

    int FrameInd;

    // -- Min/Max --------------------------------------------------------------

    bool GetMinOf(long Stat,Vertex *Dest);
    bool GetMaxOf(long Stat,Vertex *Dest);

    // -- AXIS -----------------------------------------------------------------

    Vertex Axis;
	void SetAxis(Vertex daAxis);

    // -- Shape to surface -----------------------------------------------------

	// infos de vues
	bool FullScreen;

	Camera **cam;
	float *light1_pos;

	Vertex *ViewNg,*ViewPos,*ViewSize,*tmppos,*tmpViewSize,*TmpViewNg;

    POINT *ViewStart,*ViewEnd;
    int *ViewType;
    int Active;
    int AncActive;

    int **viewport;
    double **mvmatrix,**projmatrix;

    int viewport2;
    double *mvmatrix2,*projmatrix2;

    void ComputeSize(void);
    bool SetActive(int X, int Y);

	float aspect,Height,Width,Left,Top;
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

	// names
	char *CurrentName;

	bool GenerateName(int NameType);
	void *GetByName(char name[20],int NameType);

	// snap
	Vertex snap;

	CSkyBox *daSky;

	// KeyFrame

    // Maps
    CMaps *maps;
    void DeleteAll(void);

	// perspective
	Camera Perspective;


//	KeyFrame * FirstKF,*NextKF;
	void AddKF(void);

};
//---------------------------------------------------------------------------
#endif
