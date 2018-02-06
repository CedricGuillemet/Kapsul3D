# Microsoft Developer Studio Project File - Name="Kapsul" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Kapsul - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Kapsul.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Kapsul.mak" CFG="Kapsul - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Kapsul - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Kapsul - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Kapsul - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Kore.lib opengl32.lib glu32.lib /nologo /subsystem:windows /machine:I386 /out:"../workspace/Kapsul.exe" /ALIGN:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Kapsul - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Kore.lib opengl32.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../workspace/Kapsul.exe" /pdbtype:sept /ALIGN:4096
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Kapsul - Win32 Release"
# Name "Kapsul - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Animate.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimateDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView2.cpp
# End Source File
# Begin Source File

SOURCE=.\CEditReplaceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CFindTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolScroll.cpp
# End Source File
# Begin Source File

SOURCE=.\cplusplus.cpp
# End Source File
# Begin Source File

SOURCE=.\CSkyView.cpp
# End Source File
# Begin Source File

SOURCE=.\DeskDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DesksShowDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DirTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\EntiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EntityName.cpp
# End Source File
# Begin Source File

SOURCE=.\Kapsul.cpp
# End Source File
# Begin Source File

SOURCE=.\Kapsul.rc
# End Source File
# Begin Source File

SOURCE=.\KapsulDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\KapsulView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MatBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\MatBrowserDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MltiTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ModeBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\NbFrames.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjProps.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsEditing.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsIncPaths.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsMapPaths.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleView.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectCam.cpp
# End Source File
# Begin Source File

SOURCE=.\SelName.cpp
# End Source File
# Begin Source File

SOURCE=.\SelTypeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SkyBoxEd.cpp
# End Source File
# Begin Source File

SOURCE=.\SortStringArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitPath.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Subclass.cpp
# End Source File
# Begin Source File

SOURCE=.\TestProps.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TrCtrlVw.cpp
# End Source File
# Begin Source File

SOURCE=.\TScrollDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TVTestDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\Animate.h
# End Source File
# Begin Source File

SOURCE=.\AnimateDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\BmpData.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalEditView.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalEditView.inl
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextBuffer.inl
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView.inl
# End Source File
# Begin Source File

SOURCE=.\cedefs.h
# End Source File
# Begin Source File

SOURCE=.\CEditReplaceDlg.h
# End Source File
# Begin Source File

SOURCE=.\CFindTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CoolDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\CoolScroll.h
# End Source File
# Begin Source File

SOURCE=.\CSkyView.h
# End Source File
# Begin Source File

SOURCE=.\DeskDoc.h
# End Source File
# Begin Source File

SOURCE=.\DesksShowDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\DirTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\editcmd.h
# End Source File
# Begin Source File

SOURCE=.\editreg.h
# End Source File
# Begin Source File

SOURCE=.\EntiDlg.h
# End Source File
# Begin Source File

SOURCE=.\EntityName.h
# End Source File
# Begin Source File

SOURCE=.\Kapsul.h
# End Source File
# Begin Source File

SOURCE=.\KapsulDoc.h
# End Source File
# Begin Source File

SOURCE=.\KapsulView.h
# End Source File
# Begin Source File

SOURCE=.\MainEdit.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MatBrowser.h
# End Source File
# Begin Source File

SOURCE=.\MatBrowserDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\MenuBar.h
# End Source File
# Begin Source File

SOURCE=.\MltiTree.h
# End Source File
# Begin Source File

SOURCE=.\ModeBar.h
# End Source File
# Begin Source File

SOURCE=.\MyToolBar.h
# End Source File
# Begin Source File

SOURCE=.\NbFrames.h
# End Source File
# Begin Source File

SOURCE=.\ObjProps.h
# End Source File
# Begin Source File

SOURCE=.\Options.h
# End Source File
# Begin Source File

SOURCE=.\OptionsEditing.h
# End Source File
# Begin Source File

SOURCE=.\OptionsIncPaths.h
# End Source File
# Begin Source File

SOURCE=.\OptionsMapPaths.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SampleChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\SampleDoc.h
# End Source File
# Begin Source File

SOURCE=.\SampleView.h
# End Source File
# Begin Source File

SOURCE=.\SelectCam.h
# End Source File
# Begin Source File

SOURCE=.\SelName.h
# End Source File
# Begin Source File

SOURCE=.\SelTypeDoc.h
# End Source File
# Begin Source File

SOURCE=.\SkyBoxEd.h
# End Source File
# Begin Source File

SOURCE=.\SortStringArray.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\SplitPath.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Subclass.h
# End Source File
# Begin Source File

SOURCE=.\TestProps.h
# End Source File
# Begin Source File

SOURCE=.\TipDlg.h
# End Source File
# Begin Source File

SOURCE=.\TrCtrlVw.h
# End Source File
# Begin Source File

SOURCE=.\TScrollDlg.h
# End Source File
# Begin Source File

SOURCE=.\TVTestDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bandeau_MADsha.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bandeaucredits.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
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

SOURCE=.\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur200.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur204.cur
# End Source File
# Begin Source File

SOURCE=".\res\Desk file.ico"
# End Source File
# Begin Source File

SOURCE=.\res\dragging.cur
# End Source File
# Begin Source File

SOURCE=.\res\fpoint.cur
# End Source File
# Begin Source File

SOURCE=.\res\hbone1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hlight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hroot1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hskelett.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico0.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\icr_hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\idi_hobj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_kaps.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\K.JPG
# End Source File
# Begin Source File

SOURCE=.\res\K_MADsha.jpg
# End Source File
# Begin Source File

SOURCE=.\res\Kapsul.ico
# End Source File
# Begin Source File

SOURCE=.\res\Kapsul.rc2
# End Source File
# Begin Source File

SOURCE=.\res\kapsul_big.jpg
# End Source File
# Begin Source File

SOURCE=.\res\KapsulDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\killkf.ico
# End Source File
# Begin Source File

SOURCE=.\res\Lights.bmp
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\mg_icons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mg_icons.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Mode IK.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\mode.bmp
# End Source File
# Begin Source File

SOURCE=.\res\modifvie.bmp
# End Source File
# Begin Source File

SOURCE=.\res\modify.bmp
# End Source File
# Begin Source File

SOURCE=.\res\nextkf.ico
# End Source File
# Begin Source File

SOURCE=.\res\nodraggi.cur
# End Source File
# Begin Source File

SOURCE=.\res\pause.ico
# End Source File
# Begin Source File

SOURCE=.\res\play.ico
# End Source File
# Begin Source File

SOURCE=.\res\prevkf.ico
# End Source File
# Begin Source File

SOURCE=".\res\Prog file.ico"
# End Source File
# Begin Source File

SOURCE=".\res\script file.ico"
# End Source File
# Begin Source File

SOURCE=.\res\selectba.bmp
# End Source File
# Begin Source File

SOURCE=.\res\selsingl.cur
# End Source File
# Begin Source File

SOURCE=.\selsingl.cur
# End Source File
# Begin Source File

SOURCE=.\res\spliter.cur
# End Source File
# Begin Source File

SOURCE=.\res\standard.cur
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\viewconf.bmp
# End Source File
# End Group
# End Target
# End Project
