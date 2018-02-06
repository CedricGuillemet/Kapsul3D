#if !defined UTILS_CPP
#define UTILS_CPP

#include "KLocalization.h"
#include "kgui.h"

void KAPSUL_DESC DMPOutputString(int Level,char *format, ...);
void KAPSUL_DESC DMPOutputString(char *format, ...);
void KAPSUL_DESC DMPOutputErase(void);
void KAPSUL_DESC SetDMPHWND(CEdit *m_Edit);
void KAPSUL_DESC LStatus(char *format, ...);
void KAPSUL_DESC RStatus(char *format, ...);
void KAPSUL_DESC SetStatusHWND(HWND hwnd,CWnd *_wndRedraw,HWND hStatus);
void KAPSUL_DESC SetPluginActive(void);
void KAPSUL_DESC SetFuncPtr(int *_daPtr,bool *_Crossing,bool *_AngleSnap,bool *_Snap,bool *_Centroid,CKOption *_KOption);
void KAPSUL_DESC DrawViews(void);
void KAPSUL_DESC DrawView(int ViewNb);
void KAPSUL_DESC SetPointer(HCURSOR cursor);
bool KAPSUL_DESC GetSnap(void);
void KAPSUL_DESC SetSnap(bool SnapVal);
bool KAPSUL_DESC GetAngleSnap(void);
void KAPSUL_DESC SetAngleSnap(bool SnapVal);
bool KAPSUL_DESC GetCrossing(void);
void KAPSUL_DESC SetButtonPtr(int *_daPtr);
bool KAPSUL_DESC GetCentroid(void);
KAPSUL_DESC CKImage* GetDefaultImage(void);

int KAPSUL_DESC GetButton();

long KAPSUL_DESC GetGOption();
HWND KAPSUL_DESC GetMainFrame();

void KAPSUL_DESC SetLib(CKPluginManager *Lib);
KAPSUL_DESC CKPluginManager *GetLib();
void KAPSUL_DESC UpdateHierarchie(CKScene *dk);
void KAPSUL_DESC SetHierarchieTree(HWND _HierTree);
bool KAPSUL_DESC WriteResourceToDisk(CString DestName,UINT ResID,LPCTSTR ResGrp);

CString KAPSUL_DESC GetFullPath(CString FileName);
char KAPSUL_DESC *GetFileName(char *FileName);
char KAPSUL_DESC *GetFileNameNoExt(char *FileName);
bool KAPSUL_DESC ExtPresent(CString FileName,CString Ext);
KAPSUL_DESC CKLocalization * GetLocal(void);
void KAPSUL_DESC SetLocal(CKLocalization *m_Loc);

// -- Maths Stuffs ------
KAPSUL_DESC double Interpolate(MYPOINT pt1,MYPOINT pt2,double x);
KAPSUL_DESC void QSortSeg(SegSort *list,int nb2SegList);
KAPSUL_DESC int IsInSort(const void * elt1, const void * elt2);
KAPSUL_DESC double SegDistance(MYPOINT sdeb,MYPOINT sfin,MYPOINT spt);
KAPSUL_DESC Vertex ng3d(Vertex v1,Vertex v2);
KAPSUL_DESC double Pythagore(double a,double b);
KAPSUL_DESC double Pythagore3D(Vertex a,Vertex b);
KAPSUL_DESC void QSortDouble(double *daTab,int nb2double);
KAPSUL_DESC double ng(double x1,double y1,double x2,double y2);
KAPSUL_DESC float RandomNum();
KAPSUL_DESC void RotationToDirection(float pitch,float yaw,Vertex *direction);
KAPSUL_DESC bool InvertMatrix(double src[16], double inverse[16]);
KAPSUL_DESC void Identity(double m[16]);
KAPSUL_DESC double DotProduct(Vertex *v1, Vertex *v2);
KAPSUL_DESC Vertex CrossProduct(Vertex *v1, Vertex *v2);
KAPSUL_DESC unsigned int log2(unsigned int val);
KAPSUL_DESC int intersect_triangle(Vertex &orig, Vertex &dir,Vertex &vert0, Vertex &vert1, Vertex &vert2,double *t, double *u, double *v);
KAPSUL_DESC int BrowseDialog(char *strPath);

KAPSUL_DESC void SetXYZPtr(CNumSpinCtrl	*pSpinX,CNumEdit *pEditX,CNumSpinCtrl *pSpinY,CNumEdit *pEditY,CNumSpinCtrl	*pSpinZ,CNumEdit *pEditZ);
KAPSUL_DESC void SetXYZ(float X);
KAPSUL_DESC void SetXYZ(float X,float Y);
KAPSUL_DESC void SetXYZ(float X,float Y,float Z);

#endif

