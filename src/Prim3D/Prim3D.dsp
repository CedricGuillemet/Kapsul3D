# Microsoft Developer Studio Project File - Name="Prim3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Prim3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Prim3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Prim3D.mak" CFG="Prim3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Prim3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Prim3D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Prim3D - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "KAPSUL_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"Debug/Prim3D.pdb" /debug /machine:I386 /def:".\Prim3D.def" /out:"../workspace/plugins/Prim3D.dll" /implib:"Debug/Prim3D.lib" /pdbtype:sept /ALIGN:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Prim3D - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "KAPSUL_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib Kore.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../workspace/plugins/Prim3D.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Prim3D - Win32 Release"
# Name "Prim3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Face.cpp
# End Source File
# Begin Source File

SOURCE=.\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\Mapping.cpp
# End Source File
# Begin Source File

SOURCE=.\ModPrim3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Parameters.cpp
# End Source File
# Begin Source File

SOURCE=.\Prim3D.def

!IF  "$(CFG)" == "Prim3D - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Prim3D - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Prim3DRes.rc
# End Source File
# Begin Source File

SOURCE=.\PrimDiag.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TreeParam.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Face.h
# End Source File
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# Begin Source File

SOURCE=.\Mapping.h
# End Source File
# Begin Source File

SOURCE=.\ModPrim3D.h
# End Source File
# Begin Source File

SOURCE=.\Parameters.h
# End Source File
# Begin Source File

SOURCE=.\PrimDiag.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ResSwitch.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TreeParam.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bone.bmp
# End Source File
# Begin Source File

SOURCE=.\res\complexs.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ConeIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Coneout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CubeIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cubeout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CylinderIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cylinderout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Grid3DIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Grid3Dout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GridIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Gridout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hemisIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hemisout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PatchIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Patchout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\simplest.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SphereIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Sphereout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TorusIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Torusout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TreeIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Treeout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TubeIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tubeout.bmp
# End Source File
# End Group
# Begin Group "tree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tree\tree\Branch.cpp
# End Source File
# Begin Source File

SOURCE=.\tree\tree\Branch.h
# End Source File
# Begin Source File

SOURCE=.\tree\tree\Branches.cpp
# End Source File
# Begin Source File

SOURCE=.\tree\tree\Branches.h
# End Source File
# Begin Source File

SOURCE=.\tree\tree\BranchNoise.cpp
# End Source File
# Begin Source File

SOURCE=.\tree\tree\BranchNoise.h
# End Source File
# Begin Source File

SOURCE=.\tree\tree\Leaves.cpp
# End Source File
# Begin Source File

SOURCE=.\tree\tree\Leaves.h
# End Source File
# Begin Source File

SOURCE=.\tree\tree\Tree.cpp
# End Source File
# Begin Source File

SOURCE=.\tree\tree\Tree.h
# End Source File
# End Group
# End Target
# End Project
