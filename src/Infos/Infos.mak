# Microsoft Developer Studio Generated NMAKE File, Based on Infos.dsp
!IF "$(CFG)" == ""
CFG=Infos - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Infos - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Infos - Win32 Release" && "$(CFG)" != "Infos - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Infos.mak" CFG="Infos - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Infos - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Infos - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Infos - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\infos.dll"


CLEAN :
	-@erase "$(INTDIR)\Infos.pch"
	-@erase "$(INTDIR)\InfosRes.res"
	-@erase "$(INTDIR)\ModdInfos.obj"
	-@erase "$(INTDIR)\ModInfos.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\infos.exp"
	-@erase "$(OUTDIR)\infos.lib"
	-@erase "..\plugins\infos.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Infos.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\InfosRes.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Infos.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib core.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\infos.pdb" /machine:I386 /out:"../plugins/infos.dll" /implib:"$(OUTDIR)\infos.lib" 
LINK32_OBJS= \
	"$(INTDIR)\ModdInfos.obj" \
	"$(INTDIR)\ModInfos.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\InfosRes.res"

"..\plugins\infos.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Infos - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\infos.dll"


CLEAN :
	-@erase "$(INTDIR)\Infos.pch"
	-@erase "$(INTDIR)\InfosRes.res"
	-@erase "$(INTDIR)\ModdInfos.obj"
	-@erase "$(INTDIR)\ModInfos.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\infos.exp"
	-@erase "$(OUTDIR)\infos.lib"
	-@erase "$(OUTDIR)\infos.pdb"
	-@erase "..\plugins\infos.dll"
	-@erase "..\plugins\infos.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Infos.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\InfosRes.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Infos.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib core.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\infos.pdb" /debug /machine:I386 /out:"../plugins/infos.dll" /implib:"$(OUTDIR)\infos.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ModdInfos.obj" \
	"$(INTDIR)\ModInfos.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\InfosRes.res"

"..\plugins\infos.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Infos.dep")
!INCLUDE "Infos.dep"
!ELSE 
!MESSAGE Warning: cannot find "Infos.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Infos - Win32 Release" || "$(CFG)" == "Infos - Win32 Debug"
SOURCE=.\InfosRes.rc

"$(INTDIR)\InfosRes.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ModdInfos.cpp

"$(INTDIR)\ModdInfos.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Infos.pch"


SOURCE=.\ModInfos.cpp

"$(INTDIR)\ModInfos.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Infos.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Infos - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Infos.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Infos.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Infos - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Infos.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Infos.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

