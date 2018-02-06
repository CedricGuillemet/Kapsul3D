#include "stdafx.h"
//#include <Kapsul3D.h>

#include "PathModDiag.h"
#include "resource.h"
#include "Lathe.h"
#include "Mapping.h"
#include "Path.h"
//#include <commctrl.h>
//#include "ModdPath.h"
// call in C only, Mfc in plugins are hard to implement.



HINSTANCE g_Inst;

static AFX_EXTENSION_MODULE PathDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove t his if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Path.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(PathDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(PathDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Path.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(PathDLL);
	}
	return 1;   // ok
}

/* 
    Plugins structure and private datas
*/


HWND Parent;

bool IsCreating;
CKScene *GScene;
CKDrawScene *GDrawScene;
double Valu=1,Valv=1;
double trX,trY;
double anctrX,anctrY;
CPathModDiag *m_Diag;
extern CKMesh *CurLatheMesh;
extern CKShape *CurLatheShp;
extern CLathe m_Lathe;
extern CMapping m_Mapping;
extern CPath m_Path;
/*
    My datas
*/

#ifdef __cplusplus
    extern "C" {
#endif

typedef struct
{
    Vertex *Dot;
    bool HasScale;
    double ScaleX,ScaleY;
    bool HasRotate;
    double RotatX,RotatY,RotatZ;

} ModifVert;

ModifVert AllModif[100];
int ModifAv;
int tmpMod;

bool CreateSeg;
Vertex Remem;
HWND daview;
HWND Rec;
void *Main;
bool HasMoveCr;
HWND daDiag;
HWND TWin;
int TypeEd;
CKMesh *Mesh;
int VectorUp;
Vertex *MoveVert;
Vertex PrevVal;
int dx,dy;
Vertex DaVal;
Vertex DaVal2;

CKShape *SPath,*SShape;
// put here your datas

/*
    constants
*/

static char PluginName[]={"Lofting"};
static char PluginInfos[]={"Lofting"};

/*
    My stuffs
*/

// put here your code
int FindModif(Vertex *vt)
{
    int i;

    for (i=0;i<ModifAv;i++)
    {
        if (AllModif[i].Dot==vt) return i;   
    }

    return -1;
}
int Delaunay(int N, double* x, double* y, int& numTriangles, TriangleList*& triangle)
{
    int result;

    double** point = new double*[N+3];
    int i;
    for (i = 0; i < N+3; i++)
        point[i] = new double[2];
    for (i = 0; i < N; i++)
    {
        point[i][0] = x[i];
        point[i][1] = y[i];
    }

    const double EPSILON = 0.00001;
    const int TSIZE = 75;
    const double RANGE = 10.0;

    double xmin = point[0][0], xmax = xmin;
    double ymin = point[0][1], ymax = ymin;

    for (i = 1; i < N; i++)
    {
        double value = point[i][0];
        if ( xmax < value )
            xmax = value;
        if ( xmin > value )
            xmin = value;

        value = point[i][1];
        if ( ymax < value )
            ymax = value;
        if ( ymin > value )
            ymin = value;
    }

    double xrange = xmax-xmin, yrange = ymax-ymin;
    double maxrange = xrange;
    if ( maxrange < yrange )
        maxrange = yrange;

    // need to scale the data later to do a correct triangle count
    double maxrange2 = maxrange*maxrange;

    // tweak the points by very small random numbers
    double bgs = EPSILON*maxrange;
    srand(367);   
    for (i = 0; i < N; i++) 
    {
        point[i][0] += bgs*(0.5-rand()/double(RAND_MAX));
        point[i][1] += bgs*(0.5-rand()/double(RAND_MAX));
    }

    double wrk[2][3] =
    {
        { 5*RANGE, -RANGE, -RANGE },
        { -RANGE, 5*RANGE, -RANGE }
    };
    for (i = 0; i < 3; i++)
    {
        point[N+i][0] = xmin+xrange*wrk[0][i];
        point[N+i][1] = ymin+yrange*wrk[1][i];
    }

    int i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i11;
    int nts, ii[3];
    double xx;

    int tsz = 2*TSIZE;
    int** tmp = new int*[tsz+1];
    tmp[0] = new int[2*(tsz+1)];
    for (i0 = 1; i0 < tsz+1; i0++)
        tmp[i0] = tmp[0] + 2*i0;
    i1 = 2*(N + 2);

    int* id = new int[i1];
    for (i0 = 0; i0 < i1; i0++) 
        id[i0] = i0; 

    int** a3s = new int*[i1];
    a3s[0] = new int[3*i1];
    for (i0 = 1; i0 < i1; i0++)
        a3s[i0] = a3s[0] + 3*i0;
    a3s[0][0] = N;
    a3s[0][1] = N+1;
    a3s[0][2] = N+2;

    double** ccr = new double*[i1];  // circumscribed centers and radii
    ccr[0] = new double[3*i1];
    for (i0 = 1; i0 < i1; i0++)
        ccr[i0] = ccr[0] + 3*i0;
    ccr[0][0] = 0.0;
    ccr[0][1] = 0.0;
    ccr[0][2] = +999999999999;//+NAN;// FLT_MAX;

    nts = 1;  // number of triangles
    i4 = 1;

    // compute triangulation
    for (i0 = 0; i0 < N; i0++)
    {  
        i1 = i7 = -1;
        i9 = 0;
        for (i11 = 0; i11 < nts; i11++)
        {
            i1++;
            while ( a3s[i1][0] < 0 ) 
                i1++;
            xx = ccr[i1][2];
            for (i2 = 0; i2 < 2; i2++)
            {  
                double z = point[i0][i2]-ccr[i1][i2];
                xx -= z*z;
                if ( xx < 0 )
                    goto Corner3;
            }
            i9--;
            i4--;
            id[i4] = i1;
            for (i2 = 0; i2 < 3; i2++)
            {  
                ii[0] = 0;
                if (ii[0] == i2) 
                    ii[0]++;
                for (i3 = 1; i3 < 2; i3++)
                {  
                    ii[i3] = ii[i3-1] + 1;
                    if (ii[i3] == i2) 
                        ii[i3]++;
                }
                if ( i7 > 1 )
                {  
                    i8 = i7;
                    for (i3 = 0; i3 <= i8; i3++)
                    {  
                        for (i5 = 0; i5 < 2; i5++)
                            if ( a3s[i1][ii[i5]] != tmp[i3][i5] )
                                goto Corner1;
                        for (i6 = 0; i6 < 2; i6++) 
                            tmp[i3][i6] = tmp[i8][i6];
                        i7--;
                        goto Corner2;
Corner1:;
                    }
                }
                if ( ++i7 > tsz )
                {
                    // temporary storage exceeded, increase TSIZE
                    result = 0;
                    goto ExitDelaunay;
                }
                for (i3 = 0; i3 < 2; i3++) 
                    tmp[i7][i3] = a3s[i1][ii[i3]];
Corner2:;
            }
            a3s[i1][0] = -1;
Corner3:;
        }

        for (i1 = 0; i1 <= i7; i1++)
        {  
            for (i2 = 0; i2 < 2; i2++)
                for (wrk[i2][2] = 0, i3 = 0; i3 < 2; i3++)
                {
                    wrk[i2][i3] = point[tmp[i1][i2]][i3]-point[i0][i3];
                    wrk[i2][2] += 
                        0.5*wrk[i2][i3]*(point[tmp[i1][i2]][i3]+point[i0][i3]);
                }

            xx = wrk[0][0]*wrk[1][1]-wrk[1][0]*wrk[0][1];
            ccr[id[i4]][0] = (wrk[0][2]*wrk[1][1]-wrk[1][2]*wrk[0][1])/xx;
            ccr[id[i4]][1] = (wrk[0][0]*wrk[1][2]-wrk[1][0]*wrk[0][2])/xx;

            for (ccr[id[i4]][2] = 0, i2 = 0; i2 < 2; i2++) 
            {  
                double z = point[i0][i2]-ccr[id[i4]][i2];
                ccr[id[i4]][2] += z*z;
                a3s[id[i4]][i2] = tmp[i1][i2];
            }

            a3s[id[i4]][2] = i0;
            i4++;
            i9++;
        }
        nts += i9;
    }

    // count the number of triangles
    numTriangles = 0;
    i0 = -1;
    for (i11 = 0; i11 < nts; i11++)
    {  
        i0++;
        while ( a3s[i0][0] < 0 ) 
            i0++;
        if ( a3s[i0][0] < N )
        {  
            for (i1 = 0; i1 < 2; i1++) 
                for (i2 = 0; i2 < 2; i2++) 
                    wrk[i1][i2] = 
                        point[a3s[i0][i1]][i2]-point[a3s[i0][2]][i2];

            xx = wrk[0][0]*wrk[1][1]-wrk[0][1]*wrk[1][0];

            if ( fabs(xx) > EPSILON*maxrange2 )
                numTriangles++;
        }
    }

    // create the triangles
    triangle = new TriangleList[numTriangles];

    numTriangles = 0;
    i0 = -1;
    for (i11 = 0; i11 < nts; i11++)
    {
        i0++;
        while ( a3s[i0][0] < 0 )
            i0++;
        if ( a3s[i0][0] < N )
        {
            for (i1 = 0; i1 < 2; i1++)
                for (i2 = 0; i2 < 2; i2++)
                    wrk[i1][i2] =
                        point[a3s[i0][i1]][i2]-point[a3s[i0][2]][i2];

            xx = wrk[0][0]*wrk[1][1]-wrk[0][1]*wrk[1][0];

            if ( fabs(xx) > EPSILON*maxrange2 )
            {  
                int delta = xx < 0 ? 1 : 0;
                TriangleList& tri = triangle[numTriangles];
                tri[0] = a3s[i0][0];
                tri[1] = a3s[i0][1+delta];
                tri[2] = a3s[i0][2-delta];
                numTriangles++;
            }
        }
    }

    //delete [] triangle;

    result = 1;

ExitDelaunay:;
    delete[] tmp[0];
    delete[] tmp;
    delete[] id;
    delete[] a3s[0];
    delete[] a3s;
    delete[] ccr[0];
    delete[] ccr;
    for (i = 0; i < N+3; i++)
        delete[] point[i];
    delete[] point;

    return result;
}

double davertx[10000],daverty[10000];

int ToSurface(CKShape *daShp,int TroncFaces)
{ 
    CKMesh *value;

    Vertex bout,mwt,mwt2,mwt3;
	int stopiteasy=0,stopitok=0;
    int nb2SIB1=0;
    TriangleList* datriangle;
	Vertex temp;
    CKSegment *daSeg;
    int vtav,numTriangles,trav;
    int i;


    vtav=0;


    daSeg=daShp->FirstSegment;

    while(daSeg!=NULL)
    {
        davertx[vtav]=daSeg->Dot.vx;
        daverty[vtav]=daSeg->Dot.vy;

        vtav++;
        nb2SIB1++;

        daSeg=daSeg->Next;

        if (daSeg==daShp->FirstSegment) break;

    }

	
	Delaunay(nb2SIB1,davertx,daverty,numTriangles,datriangle);

    if (numTriangles==0)
    {
        return NULL;
    }

    value=Mesh;
    value->AllocatePoly(numTriangles*2,0);


    // -- Medium weight --------------------------------------------------------

    trav=0;

    for (i=0;i<numTriangles;i++)
    {
        
        mwt.vx=(davertx[datriangle[i][0]]+davertx[datriangle[i][1]]+davertx[datriangle[i][2]])/3;
        mwt.vy=(daverty[datriangle[i][0]]+daverty[datriangle[i][1]]+daverty[datriangle[i][2]])/3;
        mwt.vz=0;


		if (daShp->IsVertInShape(mwt,NULL))
        {
			value->pl[trav].Allocate(value,1,3);
          value->pl[trav].nbvert[0]=datriangle[i][0];
          value->pl[trav].nbvert[1]=datriangle[i][1];
          value->pl[trav].nbvert[2]=datriangle[i][2];
          value->pl[trav].Tex[0][0]=datriangle[i][0];
          value->pl[trav].Tex[0][1]=datriangle[i][1];
          value->pl[trav].Tex[0][2]=datriangle[i][2];

          trav++;
		  value->pl[trav].Allocate(value,1,3);
          value->pl[trav].nbvert[0]=datriangle[i][2]+TroncFaces;
          value->pl[trav].nbvert[1]=datriangle[i][1]+TroncFaces;
          value->pl[trav].nbvert[2]=datriangle[i][0]+TroncFaces;
          value->pl[trav].Tex[0][0]=datriangle[i][2]+TroncFaces;
          value->pl[trav].Tex[0][1]=datriangle[i][1]+TroncFaces;
          value->pl[trav].Tex[0][2]=datriangle[i][0]+TroncFaces;

          trav++;

          
        }

    }

    delete [] datriangle;
    value->nb2poly=trav;
    value->AllocatePoly(trav,0);

    return trav;
}


void GenerateObject(void)
{
    
    Vertex vt1,vt2;
    Vertex tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8,tmp9;
    Vertex tmp10,tmp11,tmp12,tmp13,tmp14,tmpprev;
    Vertex rotv;
    int VertAv=0;
    int FaceAv=0;
    Vertex Ordinate;
	int i,j,k;
    int SCount,PCount,trav;
    double TotalLength,Length=0;
    int atmpMod;
	int nbSteps=5;


	CKSegment *daSeg,*daSeg2;
	double modelview2[16],modelview[16],InverseModel[16],InverseModel2[16];
	Vertex Src,Dst;

    SCount=SShape->GetCount();
    PCount=SPath->GetCount();

	double koiv=100.0f/((float)PCount*(float)nbSteps);
	double koivv=0;
	
    if (Mesh!=NULL)
        delete Mesh;

	

    Mesh=new (CKMesh)(GScene,NULL,NULL);
    trav=ToSurface(SShape,(PCount*SCount));
    //trav=0;
    Mesh->AllocatePoly((SCount*2)*(PCount*nbSteps)+trav,((PCount*nbSteps)+1)*SCount);
	
	Mesh->AllocateUV(0,((PCount*nbSteps)+1)*SCount);

	Valv=2;
	Valu=(PCount*nbSteps);

	glPushMatrix();
	glMatrixMode( GL_MODELVIEW );

    TotalLength=SPath->GetLength();

    j=0;
	daSeg=SPath->FirstSegment;
	while(daSeg!=NULL)
	{

	
		for (int koi=0;koi<nbSteps;koi++)
		{

		//glViewport(0,0,640,480);
		glLoadIdentity();
		Src=SPath->GetSpline(koivv);
		koivv+=koiv;
		Dst=SPath->GetSpline(koivv);
		/*
		if (daSeg->Next==NULL)
			Dst=daSeg->Dot;
		else
			Dst=daSeg->Next->Dot;

		if (daSeg->Prev==NULL)
			Src=daSeg->Dot;
		else
			Src=daSeg->Prev->Dot;
			*/
			
        //gluLookAt(Src.vx,Src.vy,Src.vz,Dst.vx,Dst.vy,Dst.vz, (VectorUp==1)?1.0:0.0,(VectorUp==2)?1.0:0.0,(VectorUp==3)?1.0:0.0);
        Vertex upvect=Dst-Src;
        upvect.Normalize();

        memset(modelview2,0,sizeof(double)*16);
        atmpMod=FindModif(&daSeg->Dot);

        glLoadIdentity();

        if (atmpMod!=-1)
        {
            
            if (AllModif[atmpMod].HasRotate)
            {
                glRotatef(AllModif[atmpMod].RotatX,0,0,1);
                glRotatef(AllModif[atmpMod].RotatY,0,1,0);
                //glRotatef(AllModif[tmpMod].RotatZ,1,0,0);
            }

            if (AllModif[atmpMod].HasScale)
                glScalef(AllModif[atmpMod].ScaleX,AllModif[atmpMod].ScaleY,1);
                //glScalef(2,0.5,1);

            
        }

        glGetDoublev(GL_MODELVIEW_MATRIX,modelview2);
        
        glLoadIdentity();

        gluLookAt(Src.vx,Src.vy,Src.vz,Dst.vx,Dst.vy,Dst.vz, 0,0,1/*upvect.vy,upvect.vz,upvect.vx*/);

        

        Length=SPath->GetLength(j);

		glGetDoublev(GL_MODELVIEW_MATRIX,modelview);

        //for (i=0;i<16;i++) modelview[i]*=modelview2[i];

		InvertMatrix(modelview,InverseModel);
        InvertMatrix(modelview2,InverseModel2);

        double avx,avy,avz;

        k=0;
		daSeg2=SShape->FirstSegment;
		while(daSeg2!=NULL)
		{

			avx=(daSeg2->Dot.vx+trX)*InverseModel2[0]+(daSeg2->Dot.vy+trY)*InverseModel2[4]+daSeg2->Dot.vz*InverseModel2[8];
			avy=(daSeg2->Dot.vx+trX)*InverseModel2[1]+(daSeg2->Dot.vy+trY)*InverseModel2[5]+daSeg2->Dot.vz*InverseModel2[9];
			avz=(daSeg2->Dot.vx+trX)*InverseModel2[2]+(daSeg2->Dot.vy+trY)*InverseModel2[6]+daSeg2->Dot.vz*InverseModel2[10];

			Mesh->pv[VertAv].vx=avx*InverseModel[0]+avy*InverseModel[4]+avz*InverseModel[8];
			Mesh->pv[VertAv].vy=avx*InverseModel[1]+avy*InverseModel[5]+avz*InverseModel[9];
			Mesh->pv[VertAv].vz=avx*InverseModel[2]+avy*InverseModel[6]+avz*InverseModel[10];
			Mesh->pv[VertAv]+=Src;//daSeg->Dot;


            Mesh->puv[0][VertAv].u=(Valu*koivv/100.0f);///TotalLength)*Length;
            Mesh->puv[0][VertAv].v=(Valv/(double)SShape->GetCount())*k;

			VertAv++;
            k++;

			daSeg2=daSeg2->Next;
			if (daSeg2==SShape->FirstSegment) break;

		}
		}

        j++;
		daSeg=daSeg->Next;
		if (daSeg==SPath->FirstSegment) break;

	}

	glPopMatrix();

    FaceAv=0;

    for (i=0;i<(PCount*nbSteps);i++)
    {
        for (j=0;j<SCount;j++)
        {
			Mesh->pl[FaceAv+trav].Allocate(Mesh,1,3);
            Mesh->pl[FaceAv+trav].nbvert[0]=j+i*(SCount);
            Mesh->pl[FaceAv+trav].nbvert[1]=j+(SCount)+i*(SCount);
            Mesh->pl[FaceAv+trav].nbvert[2]=((j+1)%(SCount))+(SCount)+i*(SCount);

            Mesh->pl[FaceAv+trav].Tex[0][0]=j+i*(SCount);
            Mesh->pl[FaceAv+trav].Tex[0][1]=j+(SCount)+i*(SCount);
            Mesh->pl[FaceAv+trav].Tex[0][2]=((j+1)%(SCount))+(SCount)+i*(SCount);
            FaceAv++;

			Mesh->pl[FaceAv+trav].Allocate(Mesh,1,3);
            Mesh->pl[FaceAv+trav].nbvert[0]=j+i*(SCount);
            Mesh->pl[FaceAv+trav].nbvert[1]=((1+j)%(SCount))+(SCount)+i*(SCount);
            Mesh->pl[FaceAv+trav].nbvert[2]=((j+1)%(SCount))+i*(SCount);

            Mesh->pl[FaceAv+trav].Tex[0][0]=j+i*(SCount);
            Mesh->pl[FaceAv+trav].Tex[0][1]=((1+j)%(SCount))+(SCount)+i*(SCount);
            Mesh->pl[FaceAv+trav].Tex[0][2]=((j+1)%(SCount))+i*(SCount);
            FaceAv++;
			
        }
        //nb2scalesegv++;

    }


}

/*
    Exports symbols
    Add here all the symbol which can be use anywhere else (exports)
*/

unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam);
int Draw(int daState,int WichOne);
void LMouseDown(int X,int Y,Vertex *Pos);
void LMouseUp(int X,int Y,Vertex *Pos);
void MouseMove(int X,int Y,Vertex *Pos);
void RMouseDown(int X,int Y,Vertex *Pos);
void RMouseUp(int X,int Y,Vertex *Pos);

/*
    Process message handler
*/
CBitmap m_Dib;
CRollupCtrl *m_wndRollupCtrl;
CWnd *tempo;
unsigned int __declspec(dllexport) Process(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
    unsigned int value=0;
    HINSTANCE tempinst=AfxGetInstanceHandle();
	AfxSetResourceHandle(g_Inst);

    switch (Msg)
    {
    case KM_OPEN:
		Parent=(HWND)wParam;
        tempo=CWnd::FromHandle((HWND)wParam);


        m_wndRollupCtrl=new CRollupCtrl();
        m_wndRollupCtrl->Create(WS_VISIBLE|WS_CHILD, CRect(4,4,164,362), tempo, 2);	


        m_Diag=new CPathModDiag;
        m_Diag->Create((unsigned int)IDD_MODDIAG,tempo);
        
        
        value=(unsigned int)m_Diag->m_hWnd;
        break;
    case KM_CLOSE:
        m_wndRollupCtrl->DestroyWindow();
        m_Diag->DestroyWindow();
        break;
    case KM_GETNAME:
        value=(unsigned int)&PluginName;
        break;
    case KM_GETINFOS:
        value=(unsigned int)&PluginInfos;
        break;
    case KM_GETTYPE:
        value=PLUGIN_CREATION;
        break;
    case KM_GETSECONDARYTYPE:
        value=PLUGIN_MESH;
        break;
    case KM_ISPROPERTY:
        value=0;
        break;
    case KM_ISCREATING:
        value=CreateSeg;
        break;
    case KM_SETSCENE:
        GScene=(CKScene*)wParam;
        break;
    case KM_GETBITMAP:
        m_Dib.LoadBitmap(IDB_BITMAP);
        value=(unsigned int)&m_Dib;
        break;
    case KM_DRAW:
        value=Draw(wParam,lParam);
        break;
    case KM_LMOUSEDOWN:
        LMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_RMOUSEDOWN:
        RMouseDown(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_LMOUSEUP:
        LMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_RMOUSEUP:
        RMouseUp(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_MOUSEMOVE:
        MouseMove(LOWORD(wParam),HIWORD(wParam),(Vertex *)(lParam));
        break;
    case KM_SETVIEW:
        GDrawScene=(CKDrawScene*)wParam;
        break;
    case KM_MOVEWINDOW:
        m_wndRollupCtrl->MoveWindow(0,0,164,(int)lParam,TRUE);
        value=(int)lParam;
        break;

    }
	AfxSetResourceHandle(tempinst);
 
    return value;
}

/*
    Functions used by this plugin
*/

int Draw(int daState,int WichOne)
{
	glPushMatrix();
	if (CurLatheMesh!=NULL)
	{
		GDrawScene->DrawMesh(CurLatheMesh,daState,WichOne);
	}
    if (Mesh!=NULL)
    {
        glEnable(GL_DEPTH_TEST);
        GDrawScene->DrawMesh(Mesh,daState,0);
    

/*
    glColor4f(1,1,1,1);

    for (int i=0;i<Mesh->nb2faces;i++)
    {
        glColor4f(1,1,1,1);

        glBegin(GL_LINE_STRIP);
        glVertex3f(Mesh->pv[Mesh->pf[i]->nbvert[0]]->vx,Mesh->pv[Mesh->pf[i]->nbvert[0]]->vy,Mesh->pv[Mesh->pf[i]->nbvert[0]]->vz);
        glVertex3f(Mesh->pv[Mesh->pf[i]->nbvert[1]]->vx,Mesh->pv[Mesh->pf[i]->nbvert[1]]->vy,Mesh->pv[Mesh->pf[i]->nbvert[1]]->vz);
        glVertex3f(Mesh->pv[Mesh->pf[i]->nbvert[2]]->vx,Mesh->pv[Mesh->pf[i]->nbvert[2]]->vy,Mesh->pv[Mesh->pf[i]->nbvert[2]]->vz);
        glVertex3f(Mesh->pv[Mesh->pf[i]->nbvert[0]]->vx,Mesh->pv[Mesh->pf[i]->nbvert[0]]->vy,Mesh->pv[Mesh->pf[i]->nbvert[0]]->vz);
        glEnd();
    }

*/
    }

	glPopMatrix();
	return PLUGIN_ALL;
}

void LMouseDown(int X,int Y,Vertex *Pos)
{
    CKShape *tmpShp;

    switch (TypeEd)
    {
    case 1:
        tmpShp=GScene->cSel->GetShape(X,Y);
        if (tmpShp!=NULL)
        {
            SShape=tmpShp;
            ModifAv=0;
            trX=0;
            trY=0;
            //SetWindowText(GetDlgItem(PathDiagHWND,IDC_SHAPENAME),SShape->Name);
            if (SPath!=NULL)
                GenerateObject();
        }
        break;
    case 2:
        tmpShp=GScene->cSel->GetShape(X,Y);
        if (tmpShp!=NULL)
        {
            SPath=tmpShp;
            ModifAv=0;
            trX=0;
            trY=0;

            //SetWindowText(GetDlgItem(PathDiagHWND,IDC_PATHNAME),SPath->Name);
            if (SShape!=NULL)
                GenerateObject();
        }
        break;
        // Move Dot
    case 3:
        if (!CreateSeg)
        {
            Vertex *daSeg;
            daSeg=GScene->cSel->GetShapeVert(X,Y);
            if (daSeg!=NULL)
            {
                CreateSeg=1;
                PrevVal=(*daSeg);
                MoveVert=daSeg;
                DaVal.vx=daSeg->vx-Pos->vx;

                DaVal.vy=daSeg->vy-Pos->vy;
                DaVal.vz=daSeg->vz-Pos->vz;

                if ((SShape!=NULL)&&(SPath!=NULL))
                    GenerateObject();

            }

        }
        else
        {
            CreateSeg=0;
        }
        break;
    case 4:
        //scale
        if (!CreateSeg)
        {
            Vertex *daSeg;
            daSeg=GScene->cSel->GetShapeVert(X,Y);
            if (daSeg!=NULL)
            {
                CreateSeg=1;
                tmpMod=FindModif(daSeg);
                if (tmpMod==-1)
                    tmpMod=(ModifAv==99)?-1:ModifAv++;

                if (tmpMod!=-1)
                {
                    AllModif[tmpMod].Dot=daSeg;
                    dx=X;
                    dy=Y;
                    AllModif[tmpMod].HasScale=true;
                }
            }

        }
        else
        {
            CreateSeg=0;
        }

        break;
    case 5:
        //rotate
        if (!CreateSeg)
        {
            Vertex *daSeg;
            daSeg=GScene->cSel->GetShapeVert(X,Y);
            if (daSeg!=NULL)
            {
                CreateSeg=1;
                tmpMod=FindModif(daSeg);
                if (tmpMod==-1)
                    tmpMod=(ModifAv==99)?-1:ModifAv++;

                if (tmpMod!=-1)
                {

                    AllModif[tmpMod].Dot=daSeg;
                    dx=X;
                    dy=Y;
                    AllModif[tmpMod].HasRotate=true;
                }
            }

        }
        else
        {
            CreateSeg=0;
        }
        break;
    case 6:
        // Move
        if (!CreateSeg)
        {
            anctrX=trX;
            anctrY=trY;
            dx=X;
            dy=Y;
            CreateSeg=1;
            
        }
        else
        {
            CreateSeg=0;
        }

        break;
	case 10:
		// select shape for lathing
		tmpShp=GScene->cSel->GetShape(X,Y);
        if (tmpShp!=NULL)
        {
            CurLatheShp=tmpShp;
            ModifAv=0;
            trX=0;
            trY=0;
            //SetWindowText(GetDlgItem(PathDiagHWND,IDC_SHAPENAME),SShape->Name);
            if (CurLatheShp!=NULL)
			{
				m_Lathe.m_ShapeName.SetWindowText(CurLatheShp->Name);

                //GenerateObject();
				if (CurLatheMesh==NULL)
				{
					CurLatheMesh=new CKMesh();
					CurLatheMesh->Tex1=GScene->FirstTexture;

				}
				double Valu,Valv;
				Valu=m_Mapping.m_SlidU.GetPos();
				Valv=m_Mapping.m_SlidV.GetPos();

				Valu/=10;
				Valv/=10;

				CurLatheMesh->Lathing(CurLatheShp,m_Lathe.m_LatheVal.GetPos(),Valu,Valv);

				DrawViews();
			}
        }
		break;
        
    }
}

void LMouseUp(int X,int Y,Vertex *Pos)
{
}

void MouseMove(int X,int Y,Vertex *Pos)
{
    CKShape *tmpShp;

    switch (TypeEd)
    {
    case 1:
        tmpShp=GScene->cSel->GetShape(X,Y);
        if (tmpShp!=NULL)
        {
            LStatus("Pick this shape to extrude");
            SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_FOUND)));
        }
        else
        {
            LStatus("Pick a shape to extrude");
            SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));
        }
        break;
    case 2:
        tmpShp=GScene->cSel->GetShape(X,Y);
        if (tmpShp!=NULL)
        {
            LStatus("Pick this shape for path extruder");
            SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_FOUND)));

        }
        else
        {
            LStatus("Pick a extruder shape");
            SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));

        }
        break;
        // Move Dot
    case 3:
        if (CreateSeg)
        {
            *MoveVert=DaVal+(*Pos);
            GenerateObject();
            DrawViews();
        }
        break;
    case 4:
        // scale
        if (CreateSeg)
        {
            AllModif[tmpMod].ScaleX=(X-dx)+100;
            AllModif[tmpMod].ScaleX=((AllModif[tmpMod].ScaleX<=0)?0:(AllModif[tmpMod].ScaleX/100));

			AllModif[tmpMod].ScaleY=(Y-dy)+100;
			AllModif[tmpMod].ScaleY=((AllModif[tmpMod].ScaleY<=0)?0:(AllModif[tmpMod].ScaleY/100));

            LStatus("Scale X: %5.2f Y: %5.2f",AllModif[tmpMod].ScaleX,AllModif[tmpMod].ScaleY);
            GenerateObject();
            DrawViews();
        }
        else
        {
            Vertex *daSeg;
            daSeg=GScene->cSel->GetShapeVert(X,Y);

            if (daSeg!=NULL)
            {
                LStatus("Scale this Vertex");
                SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_FOUND)));

            }
            else
            {
                LStatus("Select a path vertex to scale");
                SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));

            }


        }
        break;
    case 5:
        // rotate
        if (CreateSeg)
        {
            AllModif[tmpMod].RotatX=(X-dx);
			AllModif[tmpMod].RotatY=(Y-dy);

            LStatus("Rotation X: %5.2f Y: %5.2f",AllModif[tmpMod].RotatX,AllModif[tmpMod].RotatY);
            GenerateObject();
            DrawViews();
        }
        else
        {
            Vertex *daSeg;
            daSeg=GScene->cSel->GetShapeVert(X,Y);

            if (daSeg!=NULL)
            {
                LStatus("Rotate this Vertex");
                SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_FOUND)));

            }
            else
            {
                LStatus("Select a path vertex to rotate");
                SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));

            }


        }
        break;
    case 6:
        if (CreateSeg)
        {
            trX=(X-dx)+anctrX;
            trY=(-Y+dy)+anctrY;
            LStatus("Translate X: %5.2f Y: %5.2f ",trX,trY);
            GenerateObject();
            DrawViews();

        }
        break;
    case 10:
        tmpShp=GScene->cSel->GetShape(X,Y);
        if (tmpShp!=NULL)
        {
            LStatus("Pick this shape to lathe");
            SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_FOUND)));
        }
        else
        {
            LStatus("Pick a shape to lathe");
            SetPointer(LoadCursor(g_Inst,MAKEINTRESOURCE(IDC_POINTER_NOTFOUND)));
        }
        break;

    }

}

void RMouseDown(int X,int Y,Vertex *Pos)
{
}

void RMouseUp(int X,int Y,Vertex *Pos)
{
    switch (TypeEd)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        if (CreateSeg)
        {
            *MoveVert=PrevVal;
            CreateSeg=0;
        }
        break;
    case 4:
        break;
    }
}


#ifdef __cplusplus
    }
#endif


