
#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include <SHLOBJ.H>		// req'd for Browse dialog

//#include "memmgr/mmgr.h"

HWND FrameOut;

int *daFunctionID;
bool *Crossing,*Snap,*Centroid,*AngleSnap;
int *BtnPtr;
CWnd *wndRedraw;
CKOption *KOption2;
CKPluginManager *daLib;
HWND HierTree;
CEdit *DumpEdit;
extern HINSTANCE ghInstDLL;
HWND Status;

void KAPSUL_DESC LStatus(char *format, ...)
{
	unsigned char buffer[1024];

	va_list	msg;

	va_start(msg, format);
	vsprintf((char*)buffer, format, msg);

    SendMessage(Status,WM_SETTEXT,0,(long)buffer);
}

void KAPSUL_DESC RStatus(char *format, ...)
{
	unsigned char buffer[1024];

	va_list	msg;

	va_start(msg, format);
	vsprintf((char*)buffer, format, msg);

    SendMessage(Status,WM_SETTEXT,0,(long)buffer);
}

void KAPSUL_DESC SetStatusHWND(HWND hwnd,CWnd *_wndRedraw,HWND hStatus)
{
    FrameOut=hwnd;
	Status=hStatus;
    wndRedraw=_wndRedraw;
}

void KAPSUL_DESC SetPluginActive(void)
{
    *daFunctionID=EDIT_PLUGINCREATION;
}

void KAPSUL_DESC SetFuncPtr(int *_daPtr,bool *_Crossing,bool *_AngleSnap,bool *_Snap,bool *_Centroid,CKOption *_KOption)
{
    daFunctionID=_daPtr;
	AngleSnap=_AngleSnap;
	Centroid=_Centroid;
    KOption2 = _KOption;

	Snap=_Snap;
}

void KAPSUL_DESC SetButtonPtr(int *_daPtr)
{
    BtnPtr=_daPtr;
}

int KAPSUL_DESC GetButton()
{
    return (*BtnPtr);
}

void KAPSUL_DESC DrawViews(void)
{
    ::SendMessage(FrameOut,WM_DRAWSCENE,-1,0);
}

void KAPSUL_DESC DrawView(int ViewNb)
{
    ::SendMessage(FrameOut,WM_DRAWSCENE,ViewNb,0);
}

void KAPSUL_DESC SetLib(CKPluginManager *Lib)
{
	daLib=Lib;
}

void KAPSUL_DESC SetPointer(HCURSOR cursor)
{
	if (cursor==0)
	{
		SendMessage(FrameOut,WM_SETMOUSECURSOR,0,0);
	}
	else
	    SendMessage(FrameOut,WM_SETMOUSECURSOR,(unsigned int)cursor,0);
}

bool KAPSUL_DESC GetSnap(void)
{
	return (*Snap);
}

void KAPSUL_DESC SetSnap(bool SnapVal)
{
	(*Snap)=SnapVal;
}

bool KAPSUL_DESC GetAngleSnap(void)
{
	return (*AngleSnap);
}

void KAPSUL_DESC SetAngleSnap(bool SnapVal)
{
	(*AngleSnap)=SnapVal;
}

bool KAPSUL_DESC GetCrossing(void)
{
	return (*Crossing);
}

long KAPSUL_DESC GetGOption()
{
    return (long)KOption2;
}


HWND KAPSUL_DESC GetMainFrame()
{
	return FrameOut;
}

bool KAPSUL_DESC GetCentroid(void)
{
	return (*Centroid);
}


void UpdateHierarchie(CKScene *Scene)
{
	if (!Scene->m_IsReading)
	{
		::SendMessage(HierTree,WM_DRAWSCENE,(long)Scene,0);
	}
}

void SetHierarchieTree(HWND _HierTree)
{
	HierTree=_HierTree;
}

void WriteLogToFile(char *Log)
{
	FILE *fp=fopen(KOption2->LogFileName(),"a+t");
	if (fp!=NULL)
	{
		fwrite(Log,strlen(Log),1,fp);
		fflush(fp);
		fclose(fp);
	}
}

void DMPOutputString(char *format, ...)
{
	if (KOption2->DefaultSpamLevel()>=KOption2->MinimumSpamLevel())
	{
		char buffer[1024];
		CString temp;

		va_list	msg;

		va_start(msg, format);
		vsprintf((char*)buffer, format, msg);

		if (KOption2->LogToFile())
			WriteLogToFile(buffer);

		DumpEdit->GetWindowText(temp);
		temp+=buffer;
		DumpEdit->SetWindowText(temp);
		DumpEdit->LineScroll(64000);
	}
}

void DMPOutputString(int Level,char *format, ...)
{
	if (Level>=KOption2->MinimumSpamLevel())
	{
		char buffer[1024];
		CString temp;

		va_list	msg;

		va_start(msg, format);
		vsprintf((char*)buffer, format, msg);

		if (KOption2->LogToFile())
			WriteLogToFile(buffer);

		DumpEdit->GetWindowText(temp);
		temp+=buffer;
		DumpEdit->SetWindowText(temp);
		DumpEdit->LineScroll(64000);
	}
}

void SetDMPHWND(CEdit *m_Edit)
{
	DumpEdit=m_Edit;
}

void DMPOutputErase(void)
{
	DumpEdit->SetWindowText("");
	if (KOption2->LogToFile())
		DeleteFile(KOption2->LogFileName());
}

bool WriteResourceToDisk(CString DestName,UINT ResID,LPCTSTR ResGrp)
{

	HRSRC	hrsc = FindResource(NULL, MAKEINTRESOURCE(ResID),ResGrp);
	if (!hrsc)
	{
		DMPOutputString("Unable to find help resource\r\n");
		return false;
	}

	DWORD	helpSize = SizeofResource(NULL, hrsc);
	if (!helpSize)
	{
		DMPOutputString("Unable to locate help resource\r\n");
		return false;
	}

	HGLOBAL	hHelp = LoadResource(NULL, hrsc);
	if (!hHelp)
	{
		DMPOutputString("Unable to load help resource\r\n");
		return false;
	}

	void *	helpMem = LockResource(hHelp);
	if (!helpMem)
	{
		DMPOutputString("Unable to lock help resource\r\n");
		return false;
	}

	FILE *	fp = fopen(DestName, "wb");
	if (fp)
	{
		fwrite(helpMem, helpSize, 1, fp);
		fclose(fp);
	}
	return true;
}

#define NBFORMATS 11

static CString szExtArray[] =  
{  
	"",".jpg",".png",".tif",".bmp",".jpeg",".gif",".pcx",".dds",".tga",".dds"
}; 

CString temp; 
//COption *KOption = NULL; 
CString DefTexName="DefaultTexture";
CString Prevfn="",PrevRes="";
CString GetFullPath(CString FileName) 
{ 
	CString szFileName; 
	char temp2[512];
	FILE *fp; 
	if (CString(FileName)==Prevfn)
		return PrevRes.GetBuffer(0);
	
	Prevfn=FileName;

	for(int jk = 0; jk < NBFORMATS;jk++) 
	{ 
		szFileName=FileName; 
		szFileName+=szExtArray[jk]; 
		
		GetCurrentDirectory(512,temp2); 
		temp=temp2;
		if (temp[temp.GetLength()-1]!='\\') 
			temp+="\\"; 
		
		temp+=szFileName; 
		
		fp=fopen(temp,"rb"); 
		if (fp!=NULL) 
		{ 
			fclose(fp); 
			PrevRes=temp;
			return temp; 
		} 
		
		for (int i=0;i < KOption2->GetnbMapDir();i++) 
		{ 
			temp=KOption2->GetMapDir(i); 
			if ((temp[temp.GetLength()-1])!='\\') 
				temp+="\\"; 
			
			temp+=szFileName; 
			
			fp=fopen(temp,"rb"); 
			if (fp!=NULL) 
			{ 
				fclose(fp); 
				PrevRes=temp;
				return temp; 
			} 
		} 
		
	} 
	
	
	
	return DefTexName; 
} 

char Name[MAX_PATH],Ext[64];

char *GetFileName(char *FileName) 
{
	_splitpath(FileName,NULL,NULL,Name,Ext);
	strcat(Name,Ext);
	return Name;
}

// filename from complete path w/o ext (.map)
char *GetFileNameNoExt(char *FileName) 
{
	_splitpath(FileName,NULL,NULL,Name,Ext);
	return Name;
}

// check if the filename has the good extension
bool ExtPresent(CString FileName,CString Ext)
{
	if (Ext.IsEmpty())
	{
		DMPOutputString("Extension string not found in plugin.\r\nSaving without extension check.\r\n");
		return true;
	}
	int ptr1=FileName.Find(Ext,0);
	int ptr2=FileName.GetLength()-Ext.GetLength();

	if (ptr1==ptr2)
		return true;
	else 
		return false;
}

CKLocalization *Loc2;

CKLocalization * GetLocal(void)
{
	return Loc2;
}

void SetLocal(CKLocalization *m_Loc)
{
	Loc2=m_Loc;
}

//------------------------------------------------------------------------------
#include "stdafx.h"
//#include "Maths.h"


//#include "memmgr/mmgr.h"

// -- Angle --------------------------------------------------------------------

double ng(double x1,double y1,double x2,double y2)
{

	double track;
	double	ret;

    if ((x2==x1)&&(y2==y1))
    {
        ret=0;
    }
    else
    {
    	track=(x1-x2);
    	track/=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    	track=acos(track);
    	track*=180;
	    track/=PI;
    	ret=track;
    	if (y1>y2) ret=-ret;
    	ret+=180;

        ret*=PI;
        ret/=180;
    }

	return(ret);
}
  /*
double ngRad(double x1,double y1,double x2,double y2)
{

	double track;
	double	ret;

    if ((x2==x1)&&(y2==y1))
    {
        ret=0;
    }
    else
    {
    	track=(x1-x2);
    	track/=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    	track=acos(track);
    	ret=track;
    	if (y1>y2) ret=-ret;
    	ret+=PI;
    }

	return(ret);
}
*/
Vertex ng3d(Vertex v1,Vertex v2)
{

    Vertex value;

    value.x=-ng(v1.x,v1.y,v2.x,v2.y);

    value.y=Pythagore(v2.x-v1.x,v2.y-v1.y);
    value.y/=Pythagore(value.y,v2.z-v1.z);
    value.y=acos(value.y);
    if (v1.z>v2.z) value.y=-value.y;

    value.y+=(float)(PI/2.0f);


    value.z=0;

    return value;


}

// -- Pythagore ----------------------------------------------------------------

double Pythagore(double a,double b)
{
    return sqrt(a*a+b*b);
}

double Pythagore3D(Vertex a,Vertex b)
{
    Vertex c;

    c=a-b;
    return sqrt(fabs(c.x*c.x+c.y*c.y)+c.z*c.z);
}

// -- Interpolation ------------------------------------------------------------

double Interpolate(MYPOINT pt1,MYPOINT pt2,double x)
{

    if ((pt2.x-pt1.x)!=0)
    {
        return ((pt2.y-pt1.y)/(pt2.x-pt1.x))*(x-pt1.x)+pt1.y;
    }
    else
    {
        return pt2.x;
    }

}

// -- Compris ------------------------------------------------------------------
/*
bool ComprisOut(double binf, double bsupp,double val)
{
    return (((val>binf)&&(val<bsupp))||((val<binf)&&(val>bsupp)));
}
            */
            /*
bool ComprisIn(double binf, double bsupp,double val)
{
    return (((val>=binf)&&(val<=bsupp))||((val<=binf)&&(val>=bsupp)));
}
*/
        /*
// -- Sorting segment ----------------------------------------------------------

void QSortSeg(SegSort *list,int nb2SegList)
{
    qsort((void *)list, nb2SegList, sizeof(SegSort), SegSortComp);
}

int SegSortComp(const void *a, const void *b)
{
    SegSort * a1, * b1;

    a1 = ( SegSort * ) a;
    b1 = ( SegSort * ) b;

    if ( a1->xy < b1->xy ) return -1;
    if ( a1->xy == b1->xy ) return 0;
    return 1;
}

*/

int IsInSort(const void * elt1, const void * elt2)
{
    double daElt1,daElt2;

    daElt1=(*(double*)elt1);

    daElt2=(*(double*)elt2);
    if (daElt1>daElt2) return 1;
    if (daElt1==daElt2) return 0;
    return -1;

}

// -- distance entre un point et un segment ------------------------------------

double SegDistance(MYPOINT sdeb,MYPOINT sfin,MYPOINT spt)
{
    double value;
    double a,b,c1,c2;
	double difx1,dify1;
	double sy,fy;
    MYPOINT inters;

    difx1=(sdeb.x-sfin.x);
    dify1=(sdeb.y-sfin.y);
    a=dify1;
    b=difx1;

    value=99999;

    // pas bien mais bon...
    // a optimizer!!!
    if ((a==0)||(b==0))
    {
        if (a==0)
        {
            inters.y=sdeb.y;
            inters.x=spt.x;
        }
        else
        {
            // b==0
            inters.x=sdeb.x;
            inters.y=spt.y;
        }
    }
    else
    {
        // calcul de c dans y = (a/b) x + c
        // et y=-(b/a) x + c pour le point (ligne perpendiculaire)
        // segment
        c1=(sdeb.y-((a/b)*sdeb.x));
        // point
        c2=(spt.y+((b/a)*spt.x));

        // point d'intersection
        inters.x=((c2-c1)/( (a/b)+(b/a)));
        inters.y=(((a/b)*inters.x)+c1);
    }

    // on classe les y du segment
    if (sdeb.y==sfin.y)
    {
        if (sdeb.x>sfin.x)
        {
            sy=sfin.x;
            fy=sdeb.x;
        }
        else
        {
            fy=sfin.x;
            sy=sdeb.x;
        }

        // le point d'intersection fait-il parti du segment
        if ( (inters.x>=sy)&&(inters.x<=fy))
        {
            // le point d'intersection fait parti du segment

            value=sqrt((spt.x-inters.x)*(spt.x-inters.x)+
                            (spt.y-inters.y)*(spt.y-inters.y));
        }

    }
    else
    {
        if (sdeb.y>sfin.y)
        {
            sy=sfin.y;
            fy=sdeb.y;
        }
        else
        {
            fy=sfin.y;
            sy=sdeb.y;
        }

        // le point d'intersection fait-il parti du segment
        if ( (inters.y>=sy)&&(inters.y<=fy))
        {
            // le point d'intersection fait parti du segment

            value=sqrt((spt.x-inters.x)*(spt.x-inters.x)+
                            (spt.y-inters.y)*(spt.y-inters.y));
        }
    }

    return value;

}
                                                                                
// -- tri d'un tableau de double -----------------------------------------------
/*
int SortDouble( const void *a, const void *b)
{
    double va,vb;
    va=(*(double*)a);
    vb=(*(double*)b);
    if (va==vb) return 0;
    if (va<vb) return -1;
    return 1;
}

void QSortDouble(double *daTab,int nb2double)
{
    qsort((void *)daTab, nb2double, sizeof(double), SortDouble);
}
*/
// -----------------------------------------------------------------------------

//const int HALF_RAND = (RAND_MAX / 2);

float RandomNum()
{
	int rn;
	rn = rand();
	return ((float)(rn - (RAND_MAX / 2)) / (float)(RAND_MAX / 2));
}

void RotationToDirection(float pitch,float yaw,Vertex *direction)
{
	direction->x = (float)(-sin(yaw) * cos(pitch));
	direction->y = (float)sin(pitch);
	direction->z = (float)(cos(pitch) * cos(yaw));
}

// -- Matrice identité ---------------------------------------------------------

void Identity(double m[16])
{
    m[0+4*0] = 1; m[0+4*1] = 0; m[0+4*2] = 0; m[0+4*3] = 0;
    m[1+4*0] = 0; m[1+4*1] = 1; m[1+4*2] = 0; m[1+4*3] = 0;
    m[2+4*0] = 0; m[2+4*1] = 0; m[2+4*2] = 1; m[2+4*3] = 0;
    m[3+4*0] = 0; m[3+4*1] = 0; m[3+4*2] = 0; m[3+4*3] = 1;
}


// -- inversion de matrice -----------------------------------------------------

bool InvertMatrix(double src[16], double inverse[16])
{
    double t;
    int i, j, k, swap;
    double tmp[4][4];

    Identity(inverse);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tmp[i][j] = src[i*4+j];
        }
    }

    for (i = 0; i < 4; i++) {
        /* look for largest element in column. */
        swap = i;
        for (j = i + 1; j < 4; j++) {
            if (fabs(tmp[j][i]) > fabs(tmp[i][i])) {
                swap = j;
            }
        }

        if (swap != i) {
            /* swap rows. */
            for (k = 0; k < 4; k++) {
                t = tmp[i][k];
                tmp[i][k] = tmp[swap][k];
                tmp[swap][k] = t;

                t = inverse[i*4+k];
                inverse[i*4+k] = inverse[swap*4+k];
                inverse[swap*4+k] = t;
            }
        }

        if (tmp[i][i] == 0) {
        /* no non-zero pivot.  the matrix is singular, which
           shouldn't happen.  This means the user gave us a bad
            matrix. */
            return false;
        }

        t = tmp[i][i];
        for (k = 0; k < 4; k++) {
            tmp[i][k] /= t;
            inverse[i*4+k] /= t;
        }
        for (j = 0; j < 4; j++) {
            if (j != i) {
                t = tmp[j][i];
                for (k = 0; k < 4; k++) {
                    tmp[j][k] -= tmp[i][k]*t;
                    inverse[j*4+k] -= inverse[i*4+k]*t;
                }
            }
        }
    }
    return true;
}

// -- Normalisation de vecteur -------------------------------------------------

double Normalize(Vertex &vect)
{
    double length;

    length = sqrt(vect.x*vect.x+vect.y*vect.y+vect.z*vect.z);
    vect.x /= length;
    vect.y /= length;
    vect.z /= length;

    return length;
}


double DotProduct(Vertex *v1, Vertex *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z + v2->z));
}

/* return the cross product result = v1 cross v2 */
Vertex CrossProduct(Vertex *v1, Vertex *v2)
{
    Vertex result;
	result.x = (v1->y * v2->z) - (v1->z * v2->y);
	result.y = (v1->z * v2->x) - (v1->x * v2->z);
	result.z = (v1->x * v2->y) - (v1->y * v2->x);
    return result;
}




unsigned int log2(unsigned int val)
{
	unsigned int  r = 0;
	while(val>>=1) 
    { 
        r++; 
    }
	return r;
}


#define EPSILON 0.000001
/*
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2]; 
*/
#define CROSS(dest,v1,v2) \
          dest.x=v1.y*v2.z-v1.z*v2.y; \
          dest.y=v1.z*v2.x-v1.x*v2.z; \
          dest.z=v1.x*v2.y-v1.y*v2.x;
#define DOT(v1,v2) (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z)
#define SUB(dest,v1,v2) \
          dest.x=v1.x-v2.x; \
          dest.y=v1.y-v2.y; \
          dest.z=v1.z-v2.z; 

static Vertex edge1, edge2, tvec, pvec, qvec;
static double det,inv_det;

int intersect_triangle(Vertex &orig, Vertex &dir,
                   Vertex &vert0, Vertex &vert1, Vertex &vert2,
                   double *t, double *u, double *v)
{
   
   

   /* find vectors for two edges sharing vert0 */
   SUB(edge1, vert1, vert0);
   SUB(edge2, vert2, vert0);

   /* begin calculating determinant - also used to calculate U parameter */
   CROSS(pvec, dir, edge2);

   /* if determinant is near zero, ray lies in plane of triangle */
   det = DOT(edge1, pvec);

#ifdef TEST_CULL           /* define TEST_CULL if culling is desired */
   if (det < EPSILON)
      return 0;

   /* calculate distance from vert0 to ray origin */
   SUB(tvec, orig, vert0);

   /* calculate U parameter and test bounds */
   *u = DOT(tvec, pvec);
   if (*u < 0.0 || *u > det)
      return 0;

   /* prepare to test V parameter */
   CROSS(qvec, tvec, edge1);

    /* calculate V parameter and test bounds */
   *v = DOT(dir, qvec);
   if (*v < 0.0 || *u + *v > det)
      return 0;

   /* calculate t, scale parameters, ray intersects triangle */
   *t = DOT(edge2, qvec);
   inv_det = 1.0 / det;
   *t *= inv_det;
   *u *= inv_det;
   *v *= inv_det;
#else                    /* the non-culling branch */
   if (det > -EPSILON && det < EPSILON)
     return 0;
   inv_det = 1.0 / det;

   /* calculate distance from vert0 to ray origin */
   SUB(tvec, orig, vert0);

   /* calculate U parameter and test bounds */
   *u = DOT(tvec, pvec) * inv_det;
   if (*u < 0.0 || *u > 1.0)
     return 0;

   /* prepare to test V parameter */
   CROSS(qvec, tvec, edge1);

   /* calculate V parameter and test bounds */
   *v = DOT(dir, qvec) * inv_det;
   if (*v < 0.0 || *u + *v > 1.0)
     return 0;

   /* calculate t, ray intersects triangle */
   *t = DOT(edge2, qvec) * inv_det;
#endif
   return 1;
}




/* ============================================================================
 * Function     : DirBrowseCallbackProc
 * Purpose      : Callback procedure for DirBrowseDialog
 *              : 1) Initialise to cwd on startup
 *              : 2) Set status text to the selected directory
 * ==========================================================================*/
static int __stdcall BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData)
{
    TCHAR szDir[MAX_PATH] = {NULL};

    if (uMsg == BFFM_INITIALIZED)
    {
    //  Browse dialog initialised - set it to the cwd
        if (GetCurrentDirectory(sizeof(szDir)/sizeof(TCHAR), szDir))
            SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
    }
    else if (uMsg == BFFM_SELCHANGED)
    {
     // Fail if non filesystem  ie "//server" selected : BIF_RETURNONLYFSDIRS
        if ( ! SHGetPathFromIDList((LPITEMIDLIST) lp ,szDir))
            EnableWindow(GetDlgItem(hwnd, IDOK), FALSE); // disable the OK button

     // Set the status window to the currently selected path (or NULL).
        SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
    }

    return 0;
}
/* ============================================================================
 * Function      : DirBrowseDialog
 * Purpose       : Display a directory browser
 * Parameters    : char * strPath : path selected
 * Return        : -1    : memory allocation for shell failed
 *               : TRUE  : path selected
 *                 FALSE : if cancelled or unsuccessful
 * ==========================================================================*/
int BrowseDialog(char *strPath)
{
    BOOL retStatus = FALSE;
    BROWSEINFO bi;
    LPITEMIDLIST pidl;
    LPMALLOC pMalloc;    // set a pointer to the shell's IMalloc interface

    if ( ! (SUCCEEDED(SHGetMalloc(&pMalloc) ))) // USC : No memory for shell
        return -1;

    // Populate browse info structure
    ZeroMemory(&bi,sizeof(bi));
    bi.hwndOwner = NULL;
    bi.pidlRoot  = NULL;
    bi.pszDisplayName = NULL;
    bi.lpszTitle = "Select a new working directory";
    bi.ulFlags   = BIF_RETURNONLYFSDIRS; // Only "directories"
    bi.ulFlags  |= BIF_STATUSTEXT;       // Show the status window
    bi.lpfn      = BrowseCallbackProc;

    // Display browse dialog
    pidl = SHBrowseForFolder(&bi);

    if (pidl != NULL) // pidl == NULL if cancelled the selection
    {
        // FALSE if "//server" selected - but this is caught in the BrowseCallbackProc
        // FALSE if cancelled
        retStatus = SHGetPathFromIDList(pidl, strPath);

        pMalloc->Free(pidl);    // Free the PIDL returned by SHBrowseForFolder.
    }

    pMalloc->Release();         // Release the shell's allocator.

    return retStatus ? TRUE : FALSE;
}


KAPSUL_DESC CKImage* GetDefaultImage(void)
{
	CKImage *ImgRet;
	ImgRet=new CKImage;
	if (!ImgRet->LoadFromRessource(ghInstDLL,MAKEINTRESOURCE(IDR_TEXTURE), IMG_FORMAT_BMPWIN, "IMAGES"))
	{
		delete ImgRet;
		ImgRet=NULL;
	}
	return ImgRet;
}

KAPSUL_DESC CKPluginManager *GetLib()
{
	return daLib;
}

CNumSpinCtrl *SpinX,*SpinY,*SpinZ;
CNumEdit *EditX,*EditY,*EditZ;

KAPSUL_DESC void SetXYZPtr(CNumSpinCtrl	*pSpinX,CNumEdit *pEditX,CNumSpinCtrl *pSpinY,CNumEdit *pEditY,CNumSpinCtrl	*pSpinZ,CNumEdit *pEditZ)
{
	SpinX=pSpinX;
	SpinY=pSpinY;
	SpinZ=pSpinZ;

	EditX=pEditX;
	EditY=pEditY;
	EditZ=pEditZ;
}
KAPSUL_DESC void SetXYZ(float X)
{
	SpinX->SetPos(X);
	SpinY->SetPos(0);
	SpinZ->SetPos(0);

	SpinX->EnableWindow(true);
	EditX->EnableWindow(true);
	SpinY->EnableWindow(false);
	EditY->EnableWindow(false);
	SpinZ->EnableWindow(false);
	EditZ->EnableWindow(false);

}

KAPSUL_DESC void SetXYZ(float X,float Y)
{
	SpinX->SetPos(X);
	SpinY->SetPos(Y);
	SpinZ->SetPos(0);

	SpinX->EnableWindow(true);
	EditX->EnableWindow(true);
	SpinY->EnableWindow(true);
	EditY->EnableWindow(true);
	SpinZ->EnableWindow(false);
	EditZ->EnableWindow(false);

}

KAPSUL_DESC void SetXYZ(float X,float Y,float Z)
{
	SpinX->SetPos(X);
	SpinY->SetPos(Y);
	SpinZ->SetPos(Z);

	SpinX->EnableWindow(true);
	EditX->EnableWindow(true);
	SpinY->EnableWindow(true);
	EditY->EnableWindow(true);
	SpinZ->EnableWindow(true);
	EditZ->EnableWindow(true);

}
