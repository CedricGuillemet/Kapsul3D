# Microsoft Developer Studio Project File - Name="KapsulSE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KapsulSE - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KapsulSE.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KapsulSE.mak" CFG="KapsulSE - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KapsulSE - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "KapsulSE - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KapsulSE - Win32 Release"

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
# ADD LINK32 Kore.lib opengl32.lib glu32.lib Htmlhelp.lib /nologo /subsystem:windows /machine:I386 /out:"../workspace/KapsulSE.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Kore.lib opengl32.lib glu32.lib Htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../workspace/KapsulSE.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "KapsulSE - Win32 Release"
# Name "KapsulSE - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Animate.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\BackWorldCap.cpp
# End Source File
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseMode.cpp
# End Source File
# Begin Source File

SOURCE=.\ChoosePrim.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseSel.cpp
# End Source File
# Begin Source File

SOURCE=.\CKProject.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolScroll.cpp
# End Source File
# Begin Source File

SOURCE=.\CSkyView.cpp
# End Source File
# Begin Source File

SOURCE=.\DeskDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\FOToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\KapsulDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\KapsulSE.cpp
# End Source File
# Begin Source File

SOURCE=.\KapsulSE.rc
# End Source File
# Begin Source File

SOURCE=.\KapsulView.cpp
# End Source File
# Begin Source File

SOURCE=.\KInstall.cpp
# End Source File
# Begin Source File

SOURCE=.\KMainEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\KMaterialEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\KRenderIt.cpp
# End Source File
# Begin Source File

SOURCE=.\KSelectRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\KStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\KViewEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MatBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\MltiTree.cpp
# End Source File
# Begin Source File

SOURCE=.\MyAnimateBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDeskBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MyStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\NbFrames.cpp
# End Source File
# Begin Source File

SOURCE=.\NewFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProject.cpp
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

SOURCE=.\OptionsPrefabPaths.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputDump.cpp
# End Source File
# Begin Source File

SOURCE=.\PathDropList.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectTree.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarcf.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectCam.cpp
# End Source File
# Begin Source File

SOURCE=.\SelTypeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
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
# Begin Source File

SOURCE=.\TweakUV.cpp
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.cpp
# End Source File
# Begin Source File

SOURCE=.\WinAppEx.cpp
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

SOURCE=.\AnimOutput.h
# End Source File
# Begin Source File

SOURCE=.\BackWorldCap.h
# End Source File
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\BmpData.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChooseMode.h
# End Source File
# Begin Source File

SOURCE=.\ChoosePrim.h
# End Source File
# Begin Source File

SOURCE=.\ChooseSel.h
# End Source File
# Begin Source File

SOURCE=.\CKProject.h
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

SOURCE=.\editcmd.h
# End Source File
# Begin Source File

SOURCE=.\editreg.h
# End Source File
# Begin Source File

SOURCE=.\FOToolBar.h
# End Source File
# Begin Source File

SOURCE=.\KapsulDoc.h
# End Source File
# Begin Source File

SOURCE=.\KapsulSE.h
# End Source File
# Begin Source File

SOURCE=.\KInstall.h
# End Source File
# Begin Source File

SOURCE=.\KMainEdit.h
# End Source File
# Begin Source File

SOURCE=.\KMaterialEditor.h
# End Source File
# Begin Source File

SOURCE=.\KRenderIt.h
# End Source File
# Begin Source File

SOURCE=.\KSelectRenderer.h
# End Source File
# Begin Source File

SOURCE=.\KStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\KViewEdit.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MatBrowser.h
# End Source File
# Begin Source File

SOURCE=.\MltiTree.h
# End Source File
# Begin Source File

SOURCE=.\MyAnimateBar.h
# End Source File
# Begin Source File

SOURCE=.\MyDeskBar.h
# End Source File
# Begin Source File

SOURCE=.\MyStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\MyToolBar.h
# End Source File
# Begin Source File

SOURCE=.\NbFrames.h
# End Source File
# Begin Source File

SOURCE=.\NewFolder.h
# End Source File
# Begin Source File

SOURCE=.\NewProject.h
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

SOURCE=.\OptionsPrefabPaths.h
# End Source File
# Begin Source File

SOURCE=.\OutputDump.h
# End Source File
# Begin Source File

SOURCE=.\PathDropList.h
# End Source File
# Begin Source File

SOURCE=.\ProjectTree.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\scbarcf.h
# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\SelectCam.h
# End Source File
# Begin Source File

SOURCE=.\SelTypeDoc.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\SkyBoxEd.h
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
# Begin Source File

SOURCE=.\TweakUV.h
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.h
# End Source File
# Begin Source File

SOURCE=.\WinAppEx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\About_esque.jpg
# End Source File
# Begin Source File

SOURCE=.\res\About_Kapsul.jpg
# End Source File
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\bandeau_MADsha.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bandeaucredits.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bendhorz.cur
# End Source File
# Begin Source File

SOURCE=.\res\bendvert.cur
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

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmphi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmplow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CentroidHot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CentroidNormal.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Copy of ToolBar.bmp"
# End Source File
# Begin Source File

SOURCE=.\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00003.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00004.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00005.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur200.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur204.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=".\res\Desk file.ico"
# End Source File
# Begin Source File

SOURCE=.\res\deskbuil.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DeskBuild.bmp
# End Source File
# Begin Source File

SOURCE=.\res\deskhier.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DeskHierar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\deskmaps.bmp
# End Source File
# Begin Source File

SOURCE=.\res\deskpref.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DeskPrefabs.bmp
# End Source File
# Begin Source File

SOURCE=.\res\deskproj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DeskProject.bmp
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

SOURCE=.\res\hpatch.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hprefab.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hproject.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hroot1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hscript.bmp
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

SOURCE=".\res\Icon-List.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Icon-List1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Icon-List2.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\icon_listDesk2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon_listDesk3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon_listDesl.bmp
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

SOURCE=.\res\kapsul_big.jpg
# End Source File
# Begin Source File

SOURCE=.\res\KapsulDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\KapsulSE.ico
# End Source File
# Begin Source File

SOURCE=.\res\KapsulSE.rc2
# End Source File
# Begin Source File

SOURCE=.\res\KapsulSE_big.jpg
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

SOURCE=.\res\maindesk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
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

SOURCE=.\res\modify2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\mxt-kapsul-splash-new.JPG"
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

SOURCE=.\res\pointer.cur
# End Source File
# Begin Source File

SOURCE=.\res\pointer_.cur
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

SOURCE=.\res\SelCircleHot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelCircleNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\selectba.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelFenceHot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelFenceNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelModeFace.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelModeFaceLO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelModeObject.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelModeObjectLO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelModeVertex.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelModeVertexLO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelQuadHot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelQuadNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\selsingl.cur
# End Source File
# Begin Source File

SOURCE=.\selsingl.cur
# End Source File
# Begin Source File

SOURCE=.\res\SelSingleHot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SelSingleNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\spliter.cur
# End Source File
# Begin Source File

SOURCE=.\res\squizhor.cur
# End Source File
# Begin Source File

SOURCE=.\res\squizver.cur
# End Source File
# Begin Source File

SOURCE=.\res\standard.cur
# End Source File
# Begin Source File

SOURCE=".\res\Status Centroid.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Status CentroidNB.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Status Crossing.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Status CrossingNB.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Status Snap.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Status SnapNB.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\statusan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\statussc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\taperhor.cur
# End Source File
# Begin Source File

SOURCE=.\res\taperver.cur
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
# Begin Source File

SOURCE=.\res\X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Y.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Z.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\about_kapsul.html
# End Source File
# Begin Source File

SOURCE=..\WorkSpace\Entities.xml
# End Source File
# End Target
# End Project
# Section KapsulSE : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser2
# 	2:10:HeaderFile:webbrowser2.h
# 	2:8:ImplFile:webbrowser2.cpp
# End Section
# Section KapsulSE : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser2.h
# 	2:16:DefaultSinkClass:CWebBrowser2
# End Section
