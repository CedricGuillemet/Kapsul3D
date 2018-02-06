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


void UnionObject(Object *Obj1,Object *Obj2);
void SubObject(Object *Obj2,Object *Obj1);
//void CalcTexCoord(Object *Obj,int tsx,int tsy,Vertex Origin,double uvu,double uvv);
void HollowObject(Object *Obj);
void CreateCube(Vertex Start,double X,double Y,double Z,bool Snap=true);
void CreateCubeSpecial(Vertex Start,double X,double Y,double Z,bool Snap=true);
void CreateNGon(Vertex Start,double Length,double Height,Vertex mX,Vertex mY,Vertex mZ,int nSide);
void SetSelectedNGon(int nbSide);
void Symetry(Vertex value);
void RotateBuf(Vertex Vect,double ng);
int GetView();
void HollowSelectedObject(void);
void SubSelectedObject(void);
void UpdateBspTree(Object *daObj);
void AddSelectedObject(void);
bool AddObject(Object *Obj2,Object *Obj1);
void ApplyTexture(char *TexName);
Object *BuildCutter(Vertex v1,Vertex v2);
int GetNbSelectedObjects(void);
#endif