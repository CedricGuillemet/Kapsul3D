# Microsoft Developer Studio Project File - Name="DocScript" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DocScript - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DocScript.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DocScript.mak" CFG="DocScript - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DocScript - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DocScript - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DocScript - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 opengl32.lib Kore.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../workspace/plugins/DocScript.dll"

!ELSEIF  "$(CFG)" == "DocScript - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D EDITPADC_CLASS=AFX_EXT_CLASS /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib Kore.lib edtlib.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../workspace/plugins/DocScript.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DocScript - Win32 Release"
# Name "DocScript - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Hooking.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\SampleDoc.h
# End Source File
# Begin Source File

SOURCE=.\SampleView.h
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

SOURCE=.\mg_cur.cur
# End Source File
# End Group
# Begin Group "mfc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asp.cpp
# End Source File
# Begin Source File

SOURCE=.\basic.cpp
# End Source File
# Begin Source File

SOURCE=.\batch.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalEditView.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalEditView.inl
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextBuffer.inl
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView.inl
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView2.cpp
# End Source File
# Begin Source File

SOURCE=.\cedefs.h
# End Source File
# Begin Source File

SOURCE=.\CEditReplaceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CEditReplaceDlg.h
# End Source File
# Begin Source File

SOURCE=.\CFindTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CFindTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\childfrm.cpp
# End Source File
# Begin Source File

SOURCE=.\childfrm.h
# End Source File
# Begin Source File

SOURCE=.\cplusplus.cpp
# End Source File
# Begin Source File

SOURCE=.\dcl.cpp
# End Source File
# Begin Source File

SOURCE=.\editcmd.h
# End Source File
# Begin Source File

SOURCE=.\editreg.h
# End Source File
# Begin Source File

SOURCE=.\editres.rc
# End Source File
# Begin Source File

SOURCE=.\fortran.cpp
# End Source File
# Begin Source File

SOURCE=.\fpattern.cpp
# End Source File
# Begin Source File

SOURCE=.\fpattern.h
# End Source File
# Begin Source File

SOURCE=.\html.cpp
# End Source File
# Begin Source File

SOURCE=.\is.cpp
# End Source File
# Begin Source File

SOURCE=.\java.cpp
# End Source File
# Begin Source File

SOURCE=.\lisp.cpp
# End Source File
# Begin Source File

SOURCE=.\pascal.cpp
# End Source File
# Begin Source File

SOURCE=.\perl.cpp
# End Source File
# Begin Source File

SOURCE=.\php.cpp
# End Source File
# Begin Source File

SOURCE=.\python.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\rexx.cpp
# End Source File
# Begin Source File

SOURCE=.\rsrc.cpp
# End Source File
# Begin Source File

SOURCE=.\Sample.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\sgml.cpp
# End Source File
# Begin Source File

SOURCE=.\sh.cpp
# End Source File
# Begin Source File

SOURCE=.\siod.cpp
# End Source File
# Begin Source File

SOURCE=.\sql.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\tex.cpp
# End Source File
# End Group
# End Target
# End Project
