# Microsoft Developer Studio Project File - Name="Modifier" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Modifier - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Modifier.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Modifier.mak" CFG="Modifier - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Modifier - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Modifier - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Modifier - Win32 Release"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "KAPSUL_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kore.lib entity.lib /nologo /subsystem:windows /dll /machine:I386 /def:".\Modifier.def" /out:"../workspace/plugins/Modifier.dll" /ALIGN:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Modifier - Win32 Debug"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "KAPSUL_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kore.lib Entity.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../workspace/plugins/Modifier.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Modifier - Win32 Release"
# Name "Modifier - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CalcTex.cpp
# End Source File
# Begin Source File

SOURCE=.\Divide.cpp
# End Source File
# Begin Source File

SOURCE=.\Explode.cpp
# End Source File
# Begin Source File

SOURCE=.\Extrud.cpp
# End Source File
# Begin Source File

SOURCE=.\Fractalize.cpp
# End Source File
# Begin Source File

SOURCE=.\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\KUVEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Lathe.cpp
# End Source File
# Begin Source File

SOURCE=.\LightCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\ModDiag.cpp
# End Source File
# Begin Source File

SOURCE=.\Modifier.cpp
# End Source File
# Begin Source File

SOURCE=.\Modifier.def

!IF  "$(CFG)" == "Modifier - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Modifier - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ModifierRes.rc
# End Source File
# Begin Source File

SOURCE=.\ModModifier.cpp
# End Source File
# Begin Source File

SOURCE=.\Normals.cpp
# End Source File
# Begin Source File

SOURCE=.\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\PrecalcLight.cpp
# End Source File
# Begin Source File

SOURCE=.\Spherize.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Subdiv.cpp
# End Source File
# Begin Source File

SOURCE=.\UVMapperDiag.cpp
# End Source File
# Begin Source File

SOURCE=.\UVParam.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CalcTex.h
# End Source File
# Begin Source File

SOURCE=.\Divide.h
# End Source File
# Begin Source File

SOURCE=.\Explode.h
# End Source File
# Begin Source File

SOURCE=.\Extrud.h
# End Source File
# Begin Source File

SOURCE=.\Fractalize.h
# End Source File
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# Begin Source File

SOURCE=.\KUVEdit.h
# End Source File
# Begin Source File

SOURCE=.\Lathe.h
# End Source File
# Begin Source File

SOURCE=.\LightCalc.h
# End Source File
# Begin Source File

SOURCE=.\ModDiag.h
# End Source File
# Begin Source File

SOURCE=.\Modifier.h
# End Source File
# Begin Source File

SOURCE=.\ModModifier.h
# End Source File
# Begin Source File

SOURCE=.\Normals.h
# End Source File
# Begin Source File

SOURCE=.\Path.h
# End Source File
# Begin Source File

SOURCE=.\PrecalcLight.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ResSwitch.h
# End Source File
# Begin Source File

SOURCE=.\Spherize.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Subdiv.h
# End Source File
# Begin Source File

SOURCE=.\UVMapperDiag.h
# End Source File
# Begin Source File

SOURCE=.\UVParam.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bend.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap.bmp
# End Source File
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

SOURCE=.\res\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clipper.bmp
# End Source File
# Begin Source File

SOURCE=.\res\csgmerge.bmp
# End Source File
# Begin Source File

SOURCE=.\res\csgsub.bmp
# End Source File
# Begin Source File

SOURCE=.\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\hollow.bmp
# End Source File
# Begin Source File

SOURCE=.\selsingl.cur
# End Source File
# Begin Source File

SOURCE=.\res\squiz.bmp
# End Source File
# Begin Source File

SOURCE=.\res\taper.bmp
# End Source File
# End Group
# End Target
# End Project
