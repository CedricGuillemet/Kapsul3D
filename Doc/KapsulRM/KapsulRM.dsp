# Microsoft Developer Studio Project File - Name="KapsulRM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KapsulRM - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KapsulRM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KapsulRM.mak" CFG="KapsulRM - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KapsulRM - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "KapsulRM - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KapsulRM - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "KapsulRM - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "KapsulRM - Win32 Release"
# Name "KapsulRM - Win32 Debug"
# Begin Group "informations"

# PROP Default_Filter "*.html"
# End Group
# Begin Group "sdk"

# PROP Default_Filter "*.html"
# Begin Group "Messages"

# PROP Default_Filter "*.html"
# Begin Source File

SOURCE=.\SDK\Messages\index.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_CLOSE.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_DRAW.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETBITMAP.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETFILEDESC.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETFILTER.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETINFOS.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETNAME.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETREADSUPPORT.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETSECONDARYTYPE.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETTYPE.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_GETWRITESUPPORT.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_ISCREATING.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_ISPROPERTY.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_KEYDOWN.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_KEYUP.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_LMOUSEDOWN.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_LMOUSEUP.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_MOUSEMOVE.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_MOVEWINDOW.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_OPEN.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_READFILE.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_RMOUSEDOWN.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_RMOUSEUP.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_SAVEDESK.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_SETDESK.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_SETOBJECT.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_SETVIEW.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\KM_WRITEFILE.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\menu.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\Menuav.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Messages\Messages.html
# End Source File
# End Group
# Begin Group "vcppwizard"

# PROP Default_Filter "*.html"
# End Group
# Begin Group "metadata"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SDK\metadata\finalcss.css
# End Source File
# Begin Source File

SOURCE=.\SDK\metadata\index.html
# End Source File
# Begin Source File

SOURCE=.\SDK\metadata\Menuav.html
# End Source File
# Begin Source File

SOURCE=.\SDK\metadata\metadata.html
# End Source File
# End Group
# Begin Source File

SOURCE=.\SDK\finalcss.css
# End Source File
# Begin Source File

SOURCE=.\SDK\index.html
# End Source File
# Begin Source File

SOURCE=.\SDK\main.html
# End Source File
# Begin Source File

SOURCE=.\SDK\menu.html
# End Source File
# Begin Source File

SOURCE=.\SDK\Menuav.html
# End Source File
# End Group
# Begin Group "UserManual"

# PROP Default_Filter "*.html"
# Begin Group "Plugins"

# PROP Default_Filter ""
# End Group
# Begin Group "StandardGUI"

# PROP Default_Filter "*.html"
# End Group
# End Group
# Begin Source File

SOURCE=.\copyright.html
# End Source File
# Begin Source File

SOURCE=.\finalcss.css
# End Source File
# Begin Source File

SOURCE=.\index.html
# End Source File
# Begin Source File

SOURCE=.\main.html
# End Source File
# Begin Source File

SOURCE=.\Menuav.html
# End Source File
# Begin Source File

SOURCE=.\titre.html
# End Source File
# Begin Source File

SOURCE=.\vide.html
# End Source File
# End Target
# End Project
