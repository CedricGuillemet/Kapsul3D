
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KOGLRENDERER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KOGLRENDERER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#include <Kapsul3D.h>
// This class is exported from the KOGLRenderer.dll
class CKOGLRenderer : public CKRenderer 
{
private:
	HWND m_hWnd;
public:
	CKOGLRenderer(HWND window);
	// TODO: add your methods here.
};
