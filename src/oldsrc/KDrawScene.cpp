//---------------------------------------------------------------------------
#include "stdafx.h"

//#include "memmgr/mmgr.h"



extern CKOption *KOption2;

CKDrawScene::CKDrawScene()
{
	m_Plugin=NULL;
    Primitive=1;
	m_Scene=NULL;
	font=NULL;
}


void CKDrawScene::PreCalc(void)
{


}

CKDrawScene::~CKDrawScene()
{

	// if no desk were presents
	
}

void  CKDrawScene::DrawIt(void)
{
    int i;
    i=0;


	if (m_Scene!=NULL)
	{

    if (m_Scene->FullScreen)
    {
            if (m_Scene->ViewType[m_Scene->Active]==0) DrawView(m_Scene->ViewPos[m_Scene->Active],m_Scene->ViewNg[m_Scene->Active],m_Scene->ViewSize[m_Scene->Active],m_Scene->ViewStart[m_Scene->Active],m_Scene->ViewEnd[m_Scene->Active],m_Scene->Active);
			else if ((m_Scene->ViewType[m_Scene->Active]==8)||(m_Scene->ViewType[m_Scene->Active]==9)) DrawViewCamera(m_Scene->ViewPos[m_Scene->Active],m_Scene->ViewNg[m_Scene->Active],m_Scene->ViewSize[m_Scene->Active],m_Scene->ViewStart[m_Scene->Active],m_Scene->ViewEnd[m_Scene->Active],m_Scene->Active);
			else if (m_Scene->ViewType[m_Scene->Active]==4) DrawUV(m_Scene->ViewPos[m_Scene->Active],m_Scene->ViewNg[m_Scene->Active],m_Scene->ViewSize[m_Scene->Active],m_Scene->ViewStart[m_Scene->Active],m_Scene->ViewEnd[m_Scene->Active],m_Scene->Active);
	}
	else
	{

		for (i=0;i<4;i++)
		{
            if (m_Scene->ViewType[i]==0) DrawView(m_Scene->ViewPos[i],m_Scene->ViewNg[i],m_Scene->ViewSize[i],m_Scene->ViewStart[i],m_Scene->ViewEnd[i],i);
			else if ((m_Scene->ViewType[i]==8)||(m_Scene->ViewType[i]==9)) DrawViewCamera(m_Scene->ViewPos[i],m_Scene->ViewNg[i],m_Scene->ViewSize[i],m_Scene->ViewStart[i],m_Scene->ViewEnd[i],i);
			else if (m_Scene->ViewType[i]==4) DrawUV(m_Scene->ViewPos[i],m_Scene->ViewNg[i],m_Scene->ViewSize[i],m_Scene->ViewStart[i],m_Scene->ViewEnd[i],i);
        }
    }
	}
}










