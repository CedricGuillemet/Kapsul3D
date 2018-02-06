# Microsoft Developer Studio Project File - Name="Kore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Kore - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Kore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Kore.mak" CFG="Kore - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Kore - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Kore - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Kore - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "KAPSUL_EXPORT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 libxml2.lib wsock32.lib freetype211.lib KImage.lib /nologo /subsystem:windows /dll /machine:I386 /def:".\Kore.def" /force /out:"../workspace/Kore.dll" /implib:"../workspace/Kore.lib" /ALIGN:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Kore - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_AFXEXT" /D "_WINDLL" /D "KORE_COMPIL" /D "KAPSUL_EXPORT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libxml2.lib wsock32.lib freetype211.lib KImage.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /def:".\Kore.def" /out:"../workspace/Kore.dll" /implib:"../workspace/Kore.lib" /pdbtype:sept /ALIGN:4096
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Kore - Win32 Release"
# Name "Kore - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\KBone.cpp

!IF  "$(CFG)" == "Kore - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "Kore - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KBSPTree.cpp

!IF  "$(CFG)" == "Kore - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "Kore - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KCamera.cpp

!IF  "$(CFG)" == "Kore - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "Kore - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KEntity.cpp

!IF  "$(CFG)" == "Kore - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "Kore - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KEntityManager.cpp
# End Source File
# Begin Source File

SOURCE=.\KFilePlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\KFontManager.cpp
# End Source File
# Begin Source File

SOURCE=.\KGenericMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\KHandles.cpp
# End Source File
# Begin Source File

SOURCE=.\KHashTable.cpp
# End Source File
# Begin Source File

SOURCE=.\KLocalization.cpp
# End Source File
# Begin Source File

SOURCE=.\KMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\KObjectBase.cpp
# End Source File
# Begin Source File

SOURCE=.\KOctree.cpp
# End Source File
# Begin Source File

SOURCE=.\KOctreeNode.cpp
# End Source File
# Begin Source File

SOURCE=.\KOption.cpp
# End Source File
# Begin Source File

SOURCE=.\Kore.cpp
# End Source File
# Begin Source File

SOURCE=.\Kore.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Kore.rc
# End Source File
# Begin Source File

SOURCE=.\KPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\KPlan.cpp
# End Source File
# Begin Source File

SOURCE=.\KPluginManager.cpp
# End Source File
# Begin Source File

SOURCE=.\KPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\KRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\KScene.cpp
# End Source File
# Begin Source File

SOURCE=.\KSceneBase.cpp
# End Source File
# Begin Source File

SOURCE=.\KSceneOperation.cpp
# End Source File
# Begin Source File

SOURCE=.\KScenePlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\KSceneSelection.cpp
# End Source File
# Begin Source File

SOURCE=.\KShape.cpp
# End Source File
# Begin Source File

SOURCE=.\Kskeleton.cpp
# End Source File
# Begin Source File

SOURCE=.\KSkyBox.cpp
# End Source File
# Begin Source File

SOURCE=.\KTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\KTextureSpace.cpp
# End Source File
# Begin Source File

SOURCE=.\KTextureSpacePacker.cpp
# End Source File
# Begin Source File

SOURCE=.\KUndoRedo.cpp
# End Source File
# Begin Source File

SOURCE=.\KUndoRedoEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\KUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VertBuf.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\glext.h
# End Source File
# Begin Source File

SOURCE=.\Kapsul3D.h
# End Source File
# Begin Source File

SOURCE=.\KBone.h
# End Source File
# Begin Source File

SOURCE=.\KBoundBox.h
# End Source File
# Begin Source File

SOURCE=.\KBSPTree.h
# End Source File
# Begin Source File

SOURCE=.\KCamera.h
# End Source File
# Begin Source File

SOURCE=.\KEntity.h
# End Source File
# Begin Source File

SOURCE=.\KEntityManager.h
# End Source File
# Begin Source File

SOURCE=.\KFilePlugin.h
# End Source File
# Begin Source File

SOURCE=.\KFontManager.h
# End Source File
# Begin Source File

SOURCE=.\KGenericMesh.h
# End Source File
# Begin Source File

SOURCE=.\KHandles.h
# End Source File
# Begin Source File

SOURCE=.\KHashTable.h
# End Source File
# Begin Source File

SOURCE=.\KLocalization.h
# End Source File
# Begin Source File

SOURCE=.\KMatrix.h
# End Source File
# Begin Source File

SOURCE=.\KMesh.h
# End Source File
# Begin Source File

SOURCE=.\KObjectBase.h
# End Source File
# Begin Source File

SOURCE=.\KOctree.h
# End Source File
# Begin Source File

SOURCE=.\KOctreeNode.h
# End Source File
# Begin Source File

SOURCE=.\KOption.h
# End Source File
# Begin Source File

SOURCE=.\KPatch.h
# End Source File
# Begin Source File

SOURCE=.\KPlan.h
# End Source File
# Begin Source File

SOURCE=.\KPluginManager.h
# End Source File
# Begin Source File

SOURCE=.\KPolygon.h
# End Source File
# Begin Source File

SOURCE=.\KRenderer.h
# End Source File
# Begin Source File

SOURCE=.\KScene.h
# End Source File
# Begin Source File

SOURCE=.\KSceneBase.h
# End Source File
# Begin Source File

SOURCE=.\KSceneOperation.h
# End Source File
# Begin Source File

SOURCE=.\KScenePlugin.h
# End Source File
# Begin Source File

SOURCE=.\KSceneSelection.h
# End Source File
# Begin Source File

SOURCE=.\KSegment.h
# End Source File
# Begin Source File

SOURCE=.\KShape.h
# End Source File
# Begin Source File

SOURCE=.\Kskeleton.h
# End Source File
# Begin Source File

SOURCE=.\KSkyBox.h
# End Source File
# Begin Source File

SOURCE=.\KTexture.h
# End Source File
# Begin Source File

SOURCE=.\KTextureSpace.h
# End Source File
# Begin Source File

SOURCE=.\KTextureSpacePacker.h
# End Source File
# Begin Source File

SOURCE=.\KUndoRedo.h
# End Source File
# Begin Source File

SOURCE=.\KUndoRedoEntry.h
# End Source File
# Begin Source File

SOURCE=.\KUtils.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VertBuf.h
# End Source File
# Begin Source File

SOURCE=.\Vertex.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\checkered_floor1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\checkered_floor1.jpg
# End Source File
# Begin Source File

SOURCE=.\res\font.bmp
# End Source File
# Begin Source File

SOURCE=.\res\font.jpg
# End Source File
# Begin Source File

SOURCE=.\res\Kore.rc2
# End Source File
# End Group
# Begin Group "libxml wrapper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\xmlwrapper\event_parser.cxx
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\event_parser.h
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\init.cxx
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\init.h
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\node.cxx
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\node.h
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\node_iterator.cxx
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\node_iterator.h
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\tree_parser.cxx
# End Source File
# Begin Source File

SOURCE=.\xmlwrapper\tree_parser.h
# End Source File
# End Group
# End Target
# End Project
