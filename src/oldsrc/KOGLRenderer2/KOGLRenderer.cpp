// KOGLRenderer.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include <kapsul3D.h>
#include "KOGLRenderer.h"


// This is the constructor of a class that has been exported.
// see KOGLRenderer.h for the class definition
CKOGLRenderer::CKOGLRenderer(HWND window)
{ 
	m_hWnd=window;
	return; 
}


