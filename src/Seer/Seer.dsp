# Microsoft Developer Studio Project File - Name="Seer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Seer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Seer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Seer.mak" CFG="Seer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Seer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Seer - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Seer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Seer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Seer - Win32 Release"
# Name "Seer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\SRC\Callasm.c
# End Source File
# Begin Source File

SOURCE=.\SRC\Compiler.c
# End Source File
# Begin Source File

SOURCE=.\SRC\Consts.c
# End Source File
# Begin Source File

SOURCE=.\SRC\DECLARE.C
# End Source File
# Begin Source File

SOURCE=.\SRC\DICT.C
# End Source File
# Begin Source File

SOURCE=.\SRC\EXPR.C
# End Source File
# Begin Source File

SOURCE=.\SRC\HEADERS.C
# End Source File
# Begin Source File

SOURCE=.\SRC\INITIAL.C
# End Source File
# Begin Source File

SOURCE=.\SRC\Instance.c
# End Source File
# Begin Source File

SOURCE=.\SRC\PARSER.C
# End Source File
# Begin Source File

SOURCE=.\SRC\Pmem.c
# End Source File
# Begin Source File

SOURCE=.\SRC\PREPROC.C
# End Source File
# Begin Source File

SOURCE=.\SRC\PROTECT.C
# End Source File
# Begin Source File

SOURCE=.\SRC\Script.c
# End Source File
# Begin Source File

SOURCE=.\SRC\VARS.C
# End Source File
# Begin Source File

SOURCE=.\SRC\Vcpucode.c
# End Source File
# Begin Source File

SOURCE=.\SRC\Vcpudeco.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\SRC\Code.h
# End Source File
# Begin Source File

SOURCE=.\SRC\FIXED.H
# End Source File
# Begin Source File

SOURCE=.\SRC\INTERNAL.H
# End Source File
# End Group
# End Target
# End Project
