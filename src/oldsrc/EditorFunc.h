#if !defined(EDITFUNC_H_)
#define EDITFUNC_H_

void BeginScale(int X,int Y,Vertex *Pos);
void ScaleBuffer(int X,int Y,Vertex *Pos);

void BeginCutter(int X,int Y,Vertex *Pos);
void ValidateCutter(int X,int Y,Vertex *Pos);

void ClickSelectObject(int X,int Y,Vertex *Pos);

void BeginRotate(int X,int Y,Vertex *Pos);
void RotateBuffer(int X,int Y,Vertex *Pos);

void BeginCreateBox(int X,int Y,Vertex *Pos);
void CreateBox(int X,int Y,Vertex *Pos);

bool BeginMoveBuffer(int X,int Y,Vertex *Pos);
void MoveBuffer(int X,int Y,Vertex *Pos);

void BeginMoveVertex(int X,int Y,Vertex *Pos);
void MoveVertex(int X,int Y,Vertex *Pos);

void BeginMoveEdge(int X,int Y,Vertex *Pos);
void MoveEdge(int X,int Y,Vertex *Pos);

void BeginTranslatecoords(int X,int Y,Vertex *Pos) ;
void Translatecoords(int X,int Y,Vertex *Pos);

void BeginScalecoords(int X,int Y,Vertex *Pos);
void Scalecoords(int X,int Y,Vertex *Pos);

void BeginRotatecoords(int X,int Y,Vertex *Pos);
void Rotatecoords(int X,int Y,Vertex *Pos);

void SetSelectedToAfterUndo(void);
void SetSelectedToBeforeUndo(void);


void UnionObject(CKMesh *Obj1,CKMesh *Obj2);
void SubObject(CKMesh *Obj2,CKMesh *Obj1);
//void CalcTexCoord(CKMesh *Obj,int tsx,int tsy,Vertex Origin,double uvu,double uvv);
void HollowObject(CKMesh *Obj);
void CreateCube(Vertex Start,double X,double Y,double Z,bool Snap=true);
void CreateCubeSpecial(Vertex Start,double X,double Y,double Z,bool Snap=true);
void CreateNGon(Vertex Start,double Length,double Height,Vertex mX,Vertex mY,Vertex mZ,int nSide);
void SetSelectedNGon(int nbSide);
void Symetry(Vertex value);
void RotateBuf(Vertex Vect,double ng);
int GetView();
void HollowSelectedObject(CKScene *pScene);
void SubSelectedObject(void);
void UpdateBspTree(CKMesh *daObj);
void AddSelectedObject(void);
bool AddObject(CKMesh *Obj2,CKMesh *Obj1);
void ApplyTexture(char *TexName);
CKMesh *BuildCutter(Vertex v1,Vertex v2);
int GetNbSelectedObjects(void);
void Spherize(double ScVal);
#endif