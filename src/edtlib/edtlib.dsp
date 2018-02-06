# Microsoft Developer Studio Project File - Name="edtlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=edtlib - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "edtlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "edtlib.mak" CFG="edtlib - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "edtlib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "edtlib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "edtlib - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "edtlib - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "edtlib - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "release"
# PROP BASE Intermediate_Dir "release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release"
# PROP Intermediate_Dir "release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D EDITPADC_CLASS=AFX_EXT_CLASS /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /implib:"..\output\edtlib.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "edtlib - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "debug"
# PROP BASE Intermediate_Dir "debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D EDITPADC_CLASS=AFX_EXT_CLASS /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x405 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"debug\edtlibd.dll" /implib:"..\output\edtlibd.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "edtlib - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "edtlib___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "edtlib___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "urelease"
# PROP Intermediate_Dir "urelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /G5 /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D EDITPADC_CLASS=AFX_EXT_CLASS /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDLL" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D EDITPADC_CLASS=AFX_EXT_CLASS /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\output\edtlibu.dll" /implib:"..\output\edtlibu.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "edtlib - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "edtlib___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "edtlib___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "udebug"
# PROP Intermediate_Dir "udebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D EDITPADC_CLASS=AFX_EXT_CLASS /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_WINDLL" /D "_AFXEXT" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D EDITPADC_CLASS=AFX_EXT_CLASS /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\output\edtlibd.dll" /implib:"..\output\edtlibd.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "edtlib - Win32 Release"
# Name "edtlib - Win32 Debug"
# Name "edtlib - Win32 Unicode Release"
# Name "edtlib - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Parsers"

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

SOURCE=.\cplusplus.cpp
# End Source File
# Begin Source File

SOURCE=.\dcl.cpp
# End Source File
# Begin Source File

SOURCE=.\fortran.cpp
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

SOURCE=.\rexx.cpp
# End Source File
# Begin Source File

SOURCE=.\rsrc.cpp
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

SOURCE=.\tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\tex.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\aboutdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ccrystaleditview.cpp
# End Source File
# Begin Source File

SOURCE=.\ccrystaltextbuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\ccrystaltextview.cpp
# End Source File
# Begin Source File

SOURCE=.\ccrystaltextview2.cpp
# End Source File
# Begin Source File

SOURCE=.\ceditreplacedlg.cpp
# End Source File
# Begin Source File

SOURCE=.\cfindtextdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\chcondlg.cpp
# End Source File
# Begin Source File

SOURCE=.\crystaleditviewex.cpp
# End Source File
# Begin Source File

SOURCE=.\crystalparser.cpp
# End Source File
# Begin Source File

SOURCE=.\crystaltextblock.cpp
# End Source File
# Begin Source File

SOURCE=.\cs2cs.cpp
# End Source File
# Begin Source File

SOURCE=.\dib.cpp
# End Source File
# Begin Source File

SOURCE=.\dibstat.cpp
# End Source File
# Begin Source File

SOURCE=.\edfaddlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edfopdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\editoroptionspage.cpp
# End Source File
# Begin Source File

SOURCE=.\editpg1.cpp
# End Source File
# Begin Source File

SOURCE=.\editpg2.cpp
# End Source File
# Begin Source File

SOURCE=.\editpg3.cpp
# End Source File
# Begin Source File

SOURCE=.\editres.rc

!IF  "$(CFG)" == "edtlib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "edtlib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "edtlib - Win32 Unicode Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "edtlib - Win32 Unicode Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\edtlib.cpp
# End Source File
# Begin Source File

SOURCE=.\edtlib.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\edtlib.rc
# End Source File
# Begin Source File

SOURCE=.\fileinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\filepath.cpp
# End Source File
# Begin Source File

SOURCE=.\filesup.cpp
# End Source File
# Begin Source File

SOURCE=.\filevent.cpp
# End Source File
# Begin Source File

SOURCE=.\foldrdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\fontcomb.cpp
# End Source File
# Begin Source File

SOURCE=.\fontpg.cpp
# End Source File
# Begin Source File

SOURCE=.\fontpg.rc

!IF  "$(CFG)" == "edtlib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "edtlib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "edtlib - Win32 Unicode Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "edtlib - Win32 Unicode Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fpattern.cpp
# End Source File
# Begin Source File

SOURCE=.\gotodlg.cpp
# End Source File
# Begin Source File

SOURCE=.\hexedvw.cpp
# End Source File
# Begin Source File

SOURCE=.\hlink.cpp
# End Source File
# Begin Source File

SOURCE=.\memcombo.cpp
# End Source File
# Begin Source File

SOURCE=.\psheet2.cpp
# End Source File
# Begin Source File

SOURCE=.\regexp.cpp
# End Source File
# Begin Source File

SOURCE=.\registry.cpp
# End Source File
# Begin Source File

SOURCE=.\richevw2.cpp
# End Source File
# Begin Source File

SOURCE=.\splash.cpp
# End Source File
# Begin Source File

SOURCE=.\statbar.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\tipdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ttipctl2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\aboutdlg.h
# End Source File
# Begin Source File

SOURCE=.\ccrystaleditview.h
# End Source File
# Begin Source File

SOURCE=.\ccrystaleditview.inl
# End Source File
# Begin Source File

SOURCE=.\ccrystaltextbuffer.h
# End Source File
# Begin Source File

SOURCE=.\ccrystaltextbuffer.inl
# End Source File
# Begin Source File

SOURCE=.\ccrystaltextview.h
# End Source File
# Begin Source File

SOURCE=.\ccrystaltextview.inl
# End Source File
# Begin Source File

SOURCE=.\ceditreplacedlg.h
# End Source File
# Begin Source File

SOURCE=.\cfindtextdlg.h
# End Source File
# Begin Source File

SOURCE=.\chcondlg.h
# End Source File
# Begin Source File

SOURCE=.\crystaleditviewex.h
# End Source File
# Begin Source File

SOURCE=.\crystalparser.h
# End Source File
# Begin Source File

SOURCE=.\crystaltextblock.h
# End Source File
# Begin Source File

SOURCE=.\cs2cs.h
# End Source File
# Begin Source File

SOURCE=.\dib.h
# End Source File
# Begin Source File

SOURCE=.\dibstat.h
# End Source File
# Begin Source File

SOURCE=.\edfaddlg.h
# End Source File
# Begin Source File

SOURCE=.\edfopdlg.h
# End Source File
# Begin Source File

SOURCE=.\editcmd.h
# End Source File
# Begin Source File

SOURCE=.\editoroptionspage.h
# End Source File
# Begin Source File

SOURCE=.\editpg1.h
# End Source File
# Begin Source File

SOURCE=.\editpg2.h
# End Source File
# Begin Source File

SOURCE=.\editpg3.h
# End Source File
# Begin Source File

SOURCE=.\editreg.h
# End Source File
# Begin Source File

SOURCE=.\edtlib.h
# End Source File
# Begin Source File

SOURCE=.\fileinfo.h
# End Source File
# Begin Source File

SOURCE=.\filepath.h
# End Source File
# Begin Source File

SOURCE=.\filesup.h
# End Source File
# Begin Source File

SOURCE=.\filesup.inl
# End Source File
# Begin Source File

SOURCE=.\filevent.h
# End Source File
# Begin Source File

SOURCE=.\foldrdlg.h
# End Source File
# Begin Source File

SOURCE=.\fontcomb.h
# End Source File
# Begin Source File

SOURCE=.\fontpg.h
# End Source File
# Begin Source File

SOURCE=.\fontpgrc.h
# End Source File
# Begin Source File

SOURCE=.\fpattern.h
# End Source File
# Begin Source File

SOURCE=.\gotodlg.h
# End Source File
# Begin Source File

SOURCE=.\hexedvw.h
# End Source File
# Begin Source File

SOURCE=.\hlink.h
# End Source File
# Begin Source File

SOURCE=.\memcombo.h
# End Source File
# Begin Source File

SOURCE=.\memcombo.inl
# End Source File
# Begin Source File

SOURCE=.\psheet2.h
# End Source File
# Begin Source File

SOURCE=.\regexp.h
# End Source File
# Begin Source File

SOURCE=.\registry.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\richevw2.h
# End Source File
# Begin Source File

SOURCE=.\splash.h
# End Source File
# Begin Source File

SOURCE=.\statbar.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\tipdlg.h
# End Source File
# Begin Source File

SOURCE=.\ttipctl2.h
# End Source File
# Begin Source File

SOURCE=.\wispelld.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\editpad.ico
# End Source File
# Begin Source File

SOURCE=.\res\editpadb.ico
# End Source File
# Begin Source File

SOURCE=.\res\editpaddoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\editpadr.ico
# End Source File
# Begin Source File

SOURCE=.\res\editpadt.ico
# End Source File
# Begin Source File

SOURCE=.\res\edtlib.rc2
# End Source File
# Begin Source File

SOURCE=.\res\fonttype.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hlink.cur
# End Source File
# Begin Source File

SOURCE=.\res\hlinkbad.cur
# End Source File
# Begin Source File

SOURCE=.\res\hlnkurl.ico
# End Source File
# Begin Source File

SOURCE=.\res\litbulb2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mg_cur.cur
# End Source File
# Begin Source File

SOURCE=.\res\mg_icons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WORDP48.bmp
# End Source File
# End Group
# End Target
# End Project
