# Microsoft Developer Studio Project File - Name="PackZip" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PackZip - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PackZip.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PackZip.mak" CFG="PackZip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PackZip - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PackZip - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PackZip - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../inc/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 opengl32.lib Kore.lib zlib.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../workspace/plugins/PackZip.dll" /libpath:"../../lib"

!ELSEIF  "$(CFG)" == "PackZip - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../inc/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib Kore.lib zlib.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../workspace/plugins/PackZip.dll" /pdbtype:sept /libpath:"../../lib/"

!ENDIF 

# Begin Target

# Name "PackZip - Win32 Release"
# Name "PackZip - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ModPackZip.cpp
# End Source File
# Begin Source File

SOURCE=.\PackZipRes.rc
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# End Group
# Begin Group "ZipSrc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\zip_src\zconf.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipArchive.cpp
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipArchive.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipAutoBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipAutoBuffer.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipBigFile.cpp
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipBigFile.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipCentralDir.cpp
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipCentralDir.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipException.cpp
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipException.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipFileHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipFileHeader.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipInternalInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipInternalInfo.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\zip_src\ZipStorage.h
# End Source File
# Begin Source File

SOURCE=.\zip_src\zlib.h
# End Source File
# End Group
# End Target
# End Project
