// Entity.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Entity.h"
#include "Kapsul3D.h"
#include "Lightp.h"
#include "Particle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CEntityApp

BEGIN_MESSAGE_MAP(CEntityApp, CWinApp)
	//{{AFX_MSG_MAP(CEntityApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntityApp construction

CEntityApp::CEntityApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEntityApp object

CEntityApp theApp;

CKEntity *CreateEntityInterface(CString EntType)
{
	if (EntType=="Light")
	{
		return new CKEntityLight;
	}
	else
	if (EntType=="Particle_System")
	{
		return new CKEntityParticle;
	}
	return NULL;
}

void DeleteEntityInterface(CKEntity *pEntity)
{
	delete pEntity;
}

PrimBmp Prims;

PrimBmp* FillEntityPrimitives(void)
{
	HINSTANCE temp=AfxGetResourceHandle();
	AfxSetResourceHandle(theApp.m_hInstance);

	Prims.NbBmps=2;
	
	Prims.Bmp[0].Detach();
	Prims.Bmp[1].Detach();


	Prims.Bmp[0].LoadBitmap(MAKEINTRESOURCE(IDB_ENTLIGHTIN));
	Prims.PrimNb[0]=0;

	Prims.Bmp[1].LoadBitmap(MAKEINTRESOURCE(IDB_ENTPARTICLEIN));
	Prims.PrimNb[1]=1;

	AfxSetResourceHandle(temp);

	return &Prims;
}

