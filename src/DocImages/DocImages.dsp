# Microsoft Developer Studio Project File - Name="DocImages" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DocImages - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DocImages.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DocImages.mak" CFG="DocImages - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DocImages - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DocImages - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DocImages - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 opengl32.lib Kore.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../workspace/plugins/DocImages.dll"

!ELSEIF  "$(CFG)" == "DocImages - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib Kore.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../workspace/plugins/DocImages.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DocImages - Win32 Release"
# Name "DocImages - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CImageDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CImageDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorChooser.cpp
# End Source File
# Begin Source File

SOURCE=.\ContrasteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CorrectionCouleursDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateFilterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DocImagesRes.rc
# End Source File
# Begin Source File

SOURCE=.\GTColorSelectorWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GTColorSliderWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GTColorWellWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GTDrawHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\Hooking.cpp
# End Source File
# Begin Source File

SOURCE=.\PaletteDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PaletteWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SnapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CImageDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\CImageDemoView.h
# End Source File
# Begin Source File

SOURCE=.\ColorChooser.h
# End Source File
# Begin Source File

SOURCE=.\ContrasteDlg.h
# End Source File
# Begin Source File

SOURCE=.\CorrectionCouleursDlg.h
# End Source File
# Begin Source File

SOURCE=.\CreateFilterDlg.h
# End Source File
# Begin Source File

SOURCE=.\GTColorSelectorWnd.h
# End Source File
# Begin Source File

SOURCE=.\GTColorSliderWnd.h
# End Source File
# Begin Source File

SOURCE=.\GTColorWellWnd.h
# End Source File
# Begin Source File

SOURCE=.\GTDrawHelper.h
# End Source File
# Begin Source File

SOURCE=.\PaletteDialog.h
# End Source File
# Begin Source File

SOURCE=.\PaletteWnd.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SnapDialog.h
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
# Begin Source File

SOURCE=.\res\CImageDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\CImageDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\pour_mil.ico
# End Source File
# End Group
# End Target
# End Project
