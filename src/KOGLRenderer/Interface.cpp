#include "stdafx.h"
#include <Kapsul3D.h>
#include "KOGLRenderer.h"

CKOGLRenderer* CreateRenderInterface(CKScene *Scene)
{
	return new CKOGLRenderer(Scene);
}

void DeleteRenderInterface(CKOGLRenderer* Interface)
{
	delete Interface;
}