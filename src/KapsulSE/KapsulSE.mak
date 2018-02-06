# Microsoft Developer Studio Generated NMAKE File, Based on KapsulSE.dsp
!IF "$(CFG)" == ""
CFG=KapsulSE - Win32 Debug
!MESSAGE No configuration specified. Defaulting to KapsulSE - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "KapsulSE - Win32 Release" && "$(CFG)" != "KapsulSE - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "KapsulSE - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\workspace\KapsulSE.exe"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\Animate.obj"
	-@erase "$(INTDIR)\AnimOutput.obj"
	-@erase "$(INTDIR)\BackWorldCap.obj"
	-@erase "$(INTDIR)\BCMenu.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChooseMode.obj"
	-@erase "$(INTDIR)\ChoosePrim.obj"
	-@erase "$(INTDIR)\ChooseSel.obj"
	-@erase "$(INTDIR)\CKProject.obj"
	-@erase "$(INTDIR)\CoolDialogBar.obj"
	-@erase "$(INTDIR)\CoolScroll.obj"
	-@erase "$(INTDIR)\CSkyView.obj"
	-@erase "$(INTDIR)\DeskDoc.obj"
	-@erase "$(INTDIR)\FOToolBar.obj"
	-@erase "$(INTDIR)\KapsulDoc.obj"
	-@erase "$(INTDIR)\KapsulSE.obj"
	-@erase "$(INTDIR)\KapsulSE.pch"
	-@erase "$(INTDIR)\KapsulSE.res"
	-@erase "$(INTDIR)\KapsulView.obj"
	-@erase "$(INTDIR)\KInstall.obj"
	-@erase "$(INTDIR)\KMainEdit.obj"
	-@erase "$(INTDIR)\KMaterialEditor.obj"
	-@erase "$(INTDIR)\KRenderIt.obj"
	-@erase "$(INTDIR)\KSelectRenderer.obj"
	-@erase "$(INTDIR)\KStatusBar.obj"
	-@erase "$(INTDIR)\KViewEdit.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MatBrowser.obj"
	-@erase "$(INTDIR)\MltiTree.obj"
	-@erase "$(INTDIR)\MyAnimateBar.obj"
	-@erase "$(INTDIR)\MyDeskBar.obj"
	-@erase "$(INTDIR)\MyStatusBar.obj"
	-@erase "$(INTDIR)\MyToolBar.obj"
	-@erase "$(INTDIR)\NbFrames.obj"
	-@erase "$(INTDIR)\NewFolder.obj"
	-@erase "$(INTDIR)\NewProject.obj"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\OptionsEditing.obj"
	-@erase "$(INTDIR)\OptionsIncPaths.obj"
	-@erase "$(INTDIR)\OptionsMapPaths.obj"
	-@erase "$(INTDIR)\OptionsPrefabPaths.obj"
	-@erase "$(INTDIR)\OutputDump.obj"
	-@erase "$(INTDIR)\PathDropList.obj"
	-@erase "$(INTDIR)\ProjectTree.obj"
	-@erase "$(INTDIR)\scbarcf.obj"
	-@erase "$(INTDIR)\scbarg.obj"
	-@erase "$(INTDIR)\SelectCam.obj"
	-@erase "$(INTDIR)\SelTypeDoc.obj"
	-@erase "$(INTDIR)\sizecbar.obj"
	-@erase "$(INTDIR)\SkyBoxEd.obj"
	-@erase "$(INTDIR)\SortStringArray.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\SplitPath.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TrCtrlVw.obj"
	-@erase "$(INTDIR)\TScrollDlg.obj"
	-@erase "$(INTDIR)\TVTestDlg.obj"
	-@erase "$(INTDIR)\TweakUV.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\webbrowser2.obj"
	-@erase "$(INTDIR)\WinAppEx.obj"
	-@erase "..\workspace\KapsulSE.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\KapsulSE.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\KapsulSE.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KapsulSE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib glu32.lib Htmlhelp.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\KapsulSE.pdb" /machine:I386 /out:"../workspace/KapsulSE.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\Animate.obj" \
	"$(INTDIR)\AnimOutput.obj" \
	"$(INTDIR)\BackWorldCap.obj" \
	"$(INTDIR)\BCMenu.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ChooseMode.obj" \
	"$(INTDIR)\ChoosePrim.obj" \
	"$(INTDIR)\ChooseSel.obj" \
	"$(INTDIR)\CKProject.obj" \
	"$(INTDIR)\CoolDialogBar.obj" \
	"$(INTDIR)\CoolScroll.obj" \
	"$(INTDIR)\CSkyView.obj" \
	"$(INTDIR)\DeskDoc.obj" \
	"$(INTDIR)\FOToolBar.obj" \
	"$(INTDIR)\KapsulDoc.obj" \
	"$(INTDIR)\KapsulSE.obj" \
	"$(INTDIR)\KapsulView.obj" \
	"$(INTDIR)\KInstall.obj" \
	"$(INTDIR)\KMainEdit.obj" \
	"$(INTDIR)\KMaterialEditor.obj" \
	"$(INTDIR)\KRenderIt.obj" \
	"$(INTDIR)\KSelectRenderer.obj" \
	"$(INTDIR)\KStatusBar.obj" \
	"$(INTDIR)\KViewEdit.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MatBrowser.obj" \
	"$(INTDIR)\MltiTree.obj" \
	"$(INTDIR)\MyAnimateBar.obj" \
	"$(INTDIR)\MyDeskBar.obj" \
	"$(INTDIR)\MyStatusBar.obj" \
	"$(INTDIR)\MyToolBar.obj" \
	"$(INTDIR)\NbFrames.obj" \
	"$(INTDIR)\NewFolder.obj" \
	"$(INTDIR)\NewProject.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\OptionsEditing.obj" \
	"$(INTDIR)\OptionsIncPaths.obj" \
	"$(INTDIR)\OptionsMapPaths.obj" \
	"$(INTDIR)\OptionsPrefabPaths.obj" \
	"$(INTDIR)\OutputDump.obj" \
	"$(INTDIR)\PathDropList.obj" \
	"$(INTDIR)\ProjectTree.obj" \
	"$(INTDIR)\scbarcf.obj" \
	"$(INTDIR)\scbarg.obj" \
	"$(INTDIR)\SelectCam.obj" \
	"$(INTDIR)\SelTypeDoc.obj" \
	"$(INTDIR)\sizecbar.obj" \
	"$(INTDIR)\SkyBoxEd.obj" \
	"$(INTDIR)\SortStringArray.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\SplitPath.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TrCtrlVw.obj" \
	"$(INTDIR)\TScrollDlg.obj" \
	"$(INTDIR)\TVTestDlg.obj" \
	"$(INTDIR)\TweakUV.obj" \
	"$(INTDIR)\webbrowser2.obj" \
	"$(INTDIR)\WinAppEx.obj" \
	"$(INTDIR)\KapsulSE.res"

"..\workspace\KapsulSE.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "..\workspace\KapsulSE.exe" "$(OUTDIR)\KapsulSE.bsc"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\AboutDlg.sbr"
	-@erase "$(INTDIR)\Animate.obj"
	-@erase "$(INTDIR)\Animate.sbr"
	-@erase "$(INTDIR)\AnimOutput.obj"
	-@erase "$(INTDIR)\AnimOutput.sbr"
	-@erase "$(INTDIR)\BackWorldCap.obj"
	-@erase "$(INTDIR)\BackWorldCap.sbr"
	-@erase "$(INTDIR)\BCMenu.obj"
	-@erase "$(INTDIR)\BCMenu.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\ChooseMode.obj"
	-@erase "$(INTDIR)\ChooseMode.sbr"
	-@erase "$(INTDIR)\ChoosePrim.obj"
	-@erase "$(INTDIR)\ChoosePrim.sbr"
	-@erase "$(INTDIR)\ChooseSel.obj"
	-@erase "$(INTDIR)\ChooseSel.sbr"
	-@erase "$(INTDIR)\CKProject.obj"
	-@erase "$(INTDIR)\CKProject.sbr"
	-@erase "$(INTDIR)\CoolDialogBar.obj"
	-@erase "$(INTDIR)\CoolDialogBar.sbr"
	-@erase "$(INTDIR)\CoolScroll.obj"
	-@erase "$(INTDIR)\CoolScroll.sbr"
	-@erase "$(INTDIR)\CSkyView.obj"
	-@erase "$(INTDIR)\CSkyView.sbr"
	-@erase "$(INTDIR)\DeskDoc.obj"
	-@erase "$(INTDIR)\DeskDoc.sbr"
	-@erase "$(INTDIR)\FOToolBar.obj"
	-@erase "$(INTDIR)\FOToolBar.sbr"
	-@erase "$(INTDIR)\KapsulDoc.obj"
	-@erase "$(INTDIR)\KapsulDoc.sbr"
	-@erase "$(INTDIR)\KapsulSE.obj"
	-@erase "$(INTDIR)\KapsulSE.pch"
	-@erase "$(INTDIR)\KapsulSE.res"
	-@erase "$(INTDIR)\KapsulSE.sbr"
	-@erase "$(INTDIR)\KapsulView.obj"
	-@erase "$(INTDIR)\KapsulView.sbr"
	-@erase "$(INTDIR)\KInstall.obj"
	-@erase "$(INTDIR)\KInstall.sbr"
	-@erase "$(INTDIR)\KMainEdit.obj"
	-@erase "$(INTDIR)\KMainEdit.sbr"
	-@erase "$(INTDIR)\KMaterialEditor.obj"
	-@erase "$(INTDIR)\KMaterialEditor.sbr"
	-@erase "$(INTDIR)\KRenderIt.obj"
	-@erase "$(INTDIR)\KRenderIt.sbr"
	-@erase "$(INTDIR)\KSelectRenderer.obj"
	-@erase "$(INTDIR)\KSelectRenderer.sbr"
	-@erase "$(INTDIR)\KStatusBar.obj"
	-@erase "$(INTDIR)\KStatusBar.sbr"
	-@erase "$(INTDIR)\KViewEdit.obj"
	-@erase "$(INTDIR)\KViewEdit.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MatBrowser.obj"
	-@erase "$(INTDIR)\MatBrowser.sbr"
	-@erase "$(INTDIR)\MltiTree.obj"
	-@erase "$(INTDIR)\MltiTree.sbr"
	-@erase "$(INTDIR)\MyAnimateBar.obj"
	-@erase "$(INTDIR)\MyAnimateBar.sbr"
	-@erase "$(INTDIR)\MyDeskBar.obj"
	-@erase "$(INTDIR)\MyDeskBar.sbr"
	-@erase "$(INTDIR)\MyStatusBar.obj"
	-@erase "$(INTDIR)\MyStatusBar.sbr"
	-@erase "$(INTDIR)\MyToolBar.obj"
	-@erase "$(INTDIR)\MyToolBar.sbr"
	-@erase "$(INTDIR)\NbFrames.obj"
	-@erase "$(INTDIR)\NbFrames.sbr"
	-@erase "$(INTDIR)\NewFolder.obj"
	-@erase "$(INTDIR)\NewFolder.sbr"
	-@erase "$(INTDIR)\NewProject.obj"
	-@erase "$(INTDIR)\NewProject.sbr"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\Options.sbr"
	-@erase "$(INTDIR)\OptionsEditing.obj"
	-@erase "$(INTDIR)\OptionsEditing.sbr"
	-@erase "$(INTDIR)\OptionsIncPaths.obj"
	-@erase "$(INTDIR)\OptionsIncPaths.sbr"
	-@erase "$(INTDIR)\OptionsMapPaths.obj"
	-@erase "$(INTDIR)\OptionsMapPaths.sbr"
	-@erase "$(INTDIR)\OptionsPrefabPaths.obj"
	-@erase "$(INTDIR)\OptionsPrefabPaths.sbr"
	-@erase "$(INTDIR)\OutputDump.obj"
	-@erase "$(INTDIR)\OutputDump.sbr"
	-@erase "$(INTDIR)\PathDropList.obj"
	-@erase "$(INTDIR)\PathDropList.sbr"
	-@erase "$(INTDIR)\ProjectTree.obj"
	-@erase "$(INTDIR)\ProjectTree.sbr"
	-@erase "$(INTDIR)\scbarcf.obj"
	-@erase "$(INTDIR)\scbarcf.sbr"
	-@erase "$(INTDIR)\scbarg.obj"
	-@erase "$(INTDIR)\scbarg.sbr"
	-@erase "$(INTDIR)\SelectCam.obj"
	-@erase "$(INTDIR)\SelectCam.sbr"
	-@erase "$(INTDIR)\SelTypeDoc.obj"
	-@erase "$(INTDIR)\SelTypeDoc.sbr"
	-@erase "$(INTDIR)\sizecbar.obj"
	-@erase "$(INTDIR)\sizecbar.sbr"
	-@erase "$(INTDIR)\SkyBoxEd.obj"
	-@erase "$(INTDIR)\SkyBoxEd.sbr"
	-@erase "$(INTDIR)\SortStringArray.obj"
	-@erase "$(INTDIR)\SortStringArray.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\SplitPath.obj"
	-@erase "$(INTDIR)\SplitPath.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TipDlg.sbr"
	-@erase "$(INTDIR)\TrCtrlVw.obj"
	-@erase "$(INTDIR)\TrCtrlVw.sbr"
	-@erase "$(INTDIR)\TScrollDlg.obj"
	-@erase "$(INTDIR)\TScrollDlg.sbr"
	-@erase "$(INTDIR)\TVTestDlg.obj"
	-@erase "$(INTDIR)\TVTestDlg.sbr"
	-@erase "$(INTDIR)\TweakUV.obj"
	-@erase "$(INTDIR)\TweakUV.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\webbrowser2.obj"
	-@erase "$(INTDIR)\webbrowser2.sbr"
	-@erase "$(INTDIR)\WinAppEx.obj"
	-@erase "$(INTDIR)\WinAppEx.sbr"
	-@erase "$(OUTDIR)\KapsulSE.bsc"
	-@erase "$(OUTDIR)\KapsulSE.pdb"
	-@erase "..\workspace\KapsulSE.exe"
	-@erase "..\workspace\KapsulSE.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\KapsulSE.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\KapsulSE.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KapsulSE.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AboutDlg.sbr" \
	"$(INTDIR)\Animate.sbr" \
	"$(INTDIR)\AnimOutput.sbr" \
	"$(INTDIR)\BackWorldCap.sbr" \
	"$(INTDIR)\BCMenu.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\ChooseMode.sbr" \
	"$(INTDIR)\ChoosePrim.sbr" \
	"$(INTDIR)\ChooseSel.sbr" \
	"$(INTDIR)\CKProject.sbr" \
	"$(INTDIR)\CoolDialogBar.sbr" \
	"$(INTDIR)\CoolScroll.sbr" \
	"$(INTDIR)\CSkyView.sbr" \
	"$(INTDIR)\DeskDoc.sbr" \
	"$(INTDIR)\FOToolBar.sbr" \
	"$(INTDIR)\KapsulDoc.sbr" \
	"$(INTDIR)\KapsulSE.sbr" \
	"$(INTDIR)\KapsulView.sbr" \
	"$(INTDIR)\KInstall.sbr" \
	"$(INTDIR)\KMainEdit.sbr" \
	"$(INTDIR)\KMaterialEditor.sbr" \
	"$(INTDIR)\KRenderIt.sbr" \
	"$(INTDIR)\KSelectRenderer.sbr" \
	"$(INTDIR)\KStatusBar.sbr" \
	"$(INTDIR)\KViewEdit.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MatBrowser.sbr" \
	"$(INTDIR)\MltiTree.sbr" \
	"$(INTDIR)\MyAnimateBar.sbr" \
	"$(INTDIR)\MyDeskBar.sbr" \
	"$(INTDIR)\MyStatusBar.sbr" \
	"$(INTDIR)\MyToolBar.sbr" \
	"$(INTDIR)\NbFrames.sbr" \
	"$(INTDIR)\NewFolder.sbr" \
	"$(INTDIR)\NewProject.sbr" \
	"$(INTDIR)\Options.sbr" \
	"$(INTDIR)\OptionsEditing.sbr" \
	"$(INTDIR)\OptionsIncPaths.sbr" \
	"$(INTDIR)\OptionsMapPaths.sbr" \
	"$(INTDIR)\OptionsPrefabPaths.sbr" \
	"$(INTDIR)\OutputDump.sbr" \
	"$(INTDIR)\PathDropList.sbr" \
	"$(INTDIR)\ProjectTree.sbr" \
	"$(INTDIR)\scbarcf.sbr" \
	"$(INTDIR)\scbarg.sbr" \
	"$(INTDIR)\SelectCam.sbr" \
	"$(INTDIR)\SelTypeDoc.sbr" \
	"$(INTDIR)\sizecbar.sbr" \
	"$(INTDIR)\SkyBoxEd.sbr" \
	"$(INTDIR)\SortStringArray.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\SplitPath.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TipDlg.sbr" \
	"$(INTDIR)\TrCtrlVw.sbr" \
	"$(INTDIR)\TScrollDlg.sbr" \
	"$(INTDIR)\TVTestDlg.sbr" \
	"$(INTDIR)\TweakUV.sbr" \
	"$(INTDIR)\webbrowser2.sbr" \
	"$(INTDIR)\WinAppEx.sbr"

"$(OUTDIR)\KapsulSE.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib glu32.lib Htmlhelp.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\KapsulSE.pdb" /debug /machine:I386 /out:"../workspace/KapsulSE.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\Animate.obj" \
	"$(INTDIR)\AnimOutput.obj" \
	"$(INTDIR)\BackWorldCap.obj" \
	"$(INTDIR)\BCMenu.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ChooseMode.obj" \
	"$(INTDIR)\ChoosePrim.obj" \
	"$(INTDIR)\ChooseSel.obj" \
	"$(INTDIR)\CKProject.obj" \
	"$(INTDIR)\CoolDialogBar.obj" \
	"$(INTDIR)\CoolScroll.obj" \
	"$(INTDIR)\CSkyView.obj" \
	"$(INTDIR)\DeskDoc.obj" \
	"$(INTDIR)\FOToolBar.obj" \
	"$(INTDIR)\KapsulDoc.obj" \
	"$(INTDIR)\KapsulSE.obj" \
	"$(INTDIR)\KapsulView.obj" \
	"$(INTDIR)\KInstall.obj" \
	"$(INTDIR)\KMainEdit.obj" \
	"$(INTDIR)\KMaterialEditor.obj" \
	"$(INTDIR)\KRenderIt.obj" \
	"$(INTDIR)\KSelectRenderer.obj" \
	"$(INTDIR)\KStatusBar.obj" \
	"$(INTDIR)\KViewEdit.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MatBrowser.obj" \
	"$(INTDIR)\MltiTree.obj" \
	"$(INTDIR)\MyAnimateBar.obj" \
	"$(INTDIR)\MyDeskBar.obj" \
	"$(INTDIR)\MyStatusBar.obj" \
	"$(INTDIR)\MyToolBar.obj" \
	"$(INTDIR)\NbFrames.obj" \
	"$(INTDIR)\NewFolder.obj" \
	"$(INTDIR)\NewProject.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\OptionsEditing.obj" \
	"$(INTDIR)\OptionsIncPaths.obj" \
	"$(INTDIR)\OptionsMapPaths.obj" \
	"$(INTDIR)\OptionsPrefabPaths.obj" \
	"$(INTDIR)\OutputDump.obj" \
	"$(INTDIR)\PathDropList.obj" \
	"$(INTDIR)\ProjectTree.obj" \
	"$(INTDIR)\scbarcf.obj" \
	"$(INTDIR)\scbarg.obj" \
	"$(INTDIR)\SelectCam.obj" \
	"$(INTDIR)\SelTypeDoc.obj" \
	"$(INTDIR)\sizecbar.obj" \
	"$(INTDIR)\SkyBoxEd.obj" \
	"$(INTDIR)\SortStringArray.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\SplitPath.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TrCtrlVw.obj" \
	"$(INTDIR)\TScrollDlg.obj" \
	"$(INTDIR)\TVTestDlg.obj" \
	"$(INTDIR)\TweakUV.obj" \
	"$(INTDIR)\webbrowser2.obj" \
	"$(INTDIR)\WinAppEx.obj" \
	"$(INTDIR)\KapsulSE.res"

"..\workspace\KapsulSE.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("KapsulSE.dep")
!INCLUDE "KapsulSE.dep"
!ELSE 
!MESSAGE Warning: cannot find "KapsulSE.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "KapsulSE - Win32 Release" || "$(CFG)" == "KapsulSE - Win32 Debug"
SOURCE=.\AboutDlg.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\AboutDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\AboutDlg.obj"	"$(INTDIR)\AboutDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\Animate.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\Animate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\Animate.obj"	"$(INTDIR)\Animate.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\AnimOutput.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\AnimOutput.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\AnimOutput.obj"	"$(INTDIR)\AnimOutput.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\BackWorldCap.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\BackWorldCap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\BackWorldCap.obj"	"$(INTDIR)\BackWorldCap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\BCMenu.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\BCMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\BCMenu.obj"	"$(INTDIR)\BCMenu.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\ChooseMode.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\ChooseMode.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\ChooseMode.obj"	"$(INTDIR)\ChooseMode.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\ChoosePrim.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\ChoosePrim.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\ChoosePrim.obj"	"$(INTDIR)\ChoosePrim.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\ChooseSel.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\ChooseSel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\ChooseSel.obj"	"$(INTDIR)\ChooseSel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\CKProject.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\CKProject.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\CKProject.obj"	"$(INTDIR)\CKProject.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\CoolDialogBar.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\CoolDialogBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\CoolDialogBar.obj"	"$(INTDIR)\CoolDialogBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\CoolScroll.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\CoolScroll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\CoolScroll.obj"	"$(INTDIR)\CoolScroll.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\CSkyView.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\CSkyView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\CSkyView.obj"	"$(INTDIR)\CSkyView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\DeskDoc.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\DeskDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\DeskDoc.obj"	"$(INTDIR)\DeskDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\FOToolBar.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\FOToolBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\FOToolBar.obj"	"$(INTDIR)\FOToolBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KapsulDoc.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KapsulDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KapsulDoc.obj"	"$(INTDIR)\KapsulDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KapsulSE.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KapsulSE.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KapsulSE.obj"	"$(INTDIR)\KapsulSE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KapsulSE.rc

"$(INTDIR)\KapsulSE.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\KapsulView.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KapsulView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KapsulView.obj"	"$(INTDIR)\KapsulView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KInstall.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KInstall.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KInstall.obj"	"$(INTDIR)\KInstall.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KMainEdit.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KMainEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KMainEdit.obj"	"$(INTDIR)\KMainEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KMaterialEditor.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KMaterialEditor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KMaterialEditor.obj"	"$(INTDIR)\KMaterialEditor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KRenderIt.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KRenderIt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KRenderIt.obj"	"$(INTDIR)\KRenderIt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KSelectRenderer.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KSelectRenderer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KSelectRenderer.obj"	"$(INTDIR)\KSelectRenderer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KStatusBar.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KStatusBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KStatusBar.obj"	"$(INTDIR)\KStatusBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\KViewEdit.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\KViewEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\KViewEdit.obj"	"$(INTDIR)\KViewEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\MatBrowser.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\MatBrowser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\MatBrowser.obj"	"$(INTDIR)\MatBrowser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\MltiTree.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\MltiTree.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\MltiTree.obj"	"$(INTDIR)\MltiTree.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\MyAnimateBar.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\MyAnimateBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\MyAnimateBar.obj"	"$(INTDIR)\MyAnimateBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\MyDeskBar.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\MyDeskBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\MyDeskBar.obj"	"$(INTDIR)\MyDeskBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\MyStatusBar.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\MyStatusBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\MyStatusBar.obj"	"$(INTDIR)\MyStatusBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\MyToolBar.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\MyToolBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\MyToolBar.obj"	"$(INTDIR)\MyToolBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\NbFrames.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\NbFrames.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\NbFrames.obj"	"$(INTDIR)\NbFrames.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\NewFolder.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\NewFolder.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\NewFolder.obj"	"$(INTDIR)\NewFolder.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\NewProject.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\NewProject.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\NewProject.obj"	"$(INTDIR)\NewProject.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\Options.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\Options.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\Options.obj"	"$(INTDIR)\Options.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\OptionsEditing.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\OptionsEditing.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\OptionsEditing.obj"	"$(INTDIR)\OptionsEditing.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\OptionsIncPaths.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\OptionsIncPaths.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\OptionsIncPaths.obj"	"$(INTDIR)\OptionsIncPaths.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\OptionsMapPaths.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\OptionsMapPaths.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\OptionsMapPaths.obj"	"$(INTDIR)\OptionsMapPaths.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\OptionsPrefabPaths.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\OptionsPrefabPaths.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\OptionsPrefabPaths.obj"	"$(INTDIR)\OptionsPrefabPaths.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\OutputDump.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\OutputDump.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\OutputDump.obj"	"$(INTDIR)\OutputDump.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\PathDropList.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\PathDropList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\PathDropList.obj"	"$(INTDIR)\PathDropList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\ProjectTree.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\ProjectTree.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\ProjectTree.obj"	"$(INTDIR)\ProjectTree.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\scbarcf.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\scbarcf.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\scbarcf.obj"	"$(INTDIR)\scbarcf.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\scbarg.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\scbarg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\scbarg.obj"	"$(INTDIR)\scbarg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\SelectCam.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\SelectCam.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\SelectCam.obj"	"$(INTDIR)\SelectCam.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\SelTypeDoc.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\SelTypeDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\SelTypeDoc.obj"	"$(INTDIR)\SelTypeDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\sizecbar.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\sizecbar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\sizecbar.obj"	"$(INTDIR)\sizecbar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\SkyBoxEd.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\SkyBoxEd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\SkyBoxEd.obj"	"$(INTDIR)\SkyBoxEd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\SortStringArray.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\SortStringArray.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\SortStringArray.obj"	"$(INTDIR)\SortStringArray.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\Splash.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\Splash.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\SplitPath.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\SplitPath.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\SplitPath.obj"	"$(INTDIR)\SplitPath.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\KapsulSE.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\KapsulSE.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\KapsulSE.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\KapsulSE.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TipDlg.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\TipDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\TipDlg.obj"	"$(INTDIR)\TipDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\TrCtrlVw.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\TrCtrlVw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\TrCtrlVw.obj"	"$(INTDIR)\TrCtrlVw.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\TScrollDlg.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\TScrollDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\TScrollDlg.obj"	"$(INTDIR)\TScrollDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\TVTestDlg.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\TVTestDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\TVTestDlg.obj"	"$(INTDIR)\TVTestDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\TweakUV.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\TweakUV.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\TweakUV.obj"	"$(INTDIR)\TweakUV.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\webbrowser2.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\webbrowser2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\webbrowser2.obj"	"$(INTDIR)\webbrowser2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 

SOURCE=.\WinAppEx.cpp

!IF  "$(CFG)" == "KapsulSE - Win32 Release"


"$(INTDIR)\WinAppEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ELSEIF  "$(CFG)" == "KapsulSE - Win32 Debug"


"$(INTDIR)\WinAppEx.obj"	"$(INTDIR)\WinAppEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KapsulSE.pch"


!ENDIF 


!ENDIF 

