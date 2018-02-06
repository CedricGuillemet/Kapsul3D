

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