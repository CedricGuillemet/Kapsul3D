# Microsoft Developer Studio Project File - Name="KGUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=KGUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KGUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KGUI.mak" CFG="KGUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KGUI - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "KGUI - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KGUI - Win32 Release"

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
# ADD LINK32 dinput8.lib dxguid.lib opengl32.lib glu32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../workspace/KGUI.dll" /ALIGN:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "KGUI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "KAPSUL_EXPORT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dinput8.lib dxguid.lib opengl32.lib glu32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../workspace/KGUI.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "KGUI - Win32 Release"
# Name "KGUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST2.cpp
# End Source File
# Begin Source File

SOURCE=.\cgfiltyp.cpp
# End Source File
# Begin Source File

SOURCE=.\DropBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\FileTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\hyperlink.cpp
# End Source File
# Begin Source File

SOURCE=.\KDirectInput8.cpp
# End Source File
# Begin Source File

SOURCE=.\KGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\KGUI.def
# End Source File
# Begin Source File

SOURCE=.\KGUI.rc
# End Source File
# Begin Source File

SOURCE=.\KSlid.cpp
# End Source File
# Begin Source File

SOURCE=.\NumEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\NumSpinCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PaintZone.cpp
# End Source File
# Begin Source File

SOURCE=.\RollupCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TimeTracker.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\BtnST2.h
# End Source File
# Begin Source File

SOURCE=.\cgfiltyp.h
# End Source File
# Begin Source File

SOURCE=.\DropBtn.h
# End Source File
# Begin Source File

SOURCE=.\FileTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\hyperlink.h
# End Source File
# Begin Source File

SOURCE=.\KDirectInput8.h
# End Source File
# Begin Source File

SOURCE=.\KGUI.H
# End Source File
# Begin Source File

SOURCE=.\KSlid.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\NumEdit.h
# End Source File
# Begin Source File

SOURCE=.\NumSpinCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PaintZone.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RollupCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SortedArray.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TimeTracker.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\KGUI.rc2
# End Source File
# End Group
# Begin Group "Obj inspector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objInspector\ColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\objInspector\ColorButton.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\objInspector\ColourPopup.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\FileEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\objInspector\FileEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\GfxTools.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\MemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\objInspector\MemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\MemoEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\objInspector\MemoEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\ObjectInspector.cpp
# End Source File
# Begin Source File

SOURCE=.\objInspector\ObjectInspector.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\OXDllExt.h
# End Source File
# Begin Source File

SOURCE=.\objInspector\OXMaskedEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\objInspector\OXMaskedEdit.h
# End Source File
# End Group
# Begin Group "OpenDialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OpenDlg\cmn.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OpenDlg\cmn_resource.h
# End Source File
# Begin Source File

SOURCE=.\OpenDlg\CoolBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenDlg\CoolBtn.h
# End Source File
# Begin Source File

SOURCE=.\OpenDlg\memdc.h
# End Source File
# Begin Source File

SOURCE=.\OpenDlg\Office2000Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenDlg\office2000dlg.h
# End Source File
# Begin Source File

SOURCE=.\OpenDlg\SelBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenDlg\SelBtn.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
