#include "stdafx.h"
#include <Kapsul3D.h>
#include "UVMapper.h"
#include "Interface.h"



HINSTANCE g_Inst;

AFX_EXTENSION_MODULE ExtensionDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove t his if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("UVMapper.DLL Initializing!\n");

		g_Inst=hInstance;
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(ExtensionDLL, hInstance))
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

		new CDynLinkLibrary(ExtensionDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("UVMapper.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(ExtensionDLL);
	}
	return 1;   // ok
}


CKUVMapper* CreateSceneInterface()
{
	return new CKUVMapper();
}

void DeleteSceneInterface(CKUVMapper* Interface)
{
	delete Interface;
}