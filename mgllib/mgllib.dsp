# Microsoft Developer Studio Project File - Name="mgllib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=mgllib - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "mgllib.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "mgllib.mak" CFG="mgllib - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "mgllib - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "mgllib - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mgllib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./Release"
# PROP Intermediate_Dir "./Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MGLLIB_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "src" /I "src/2d" /I "src/graphic_extends" /I "src/common" /I "src/other" /I "src/game" /I "src/input" /I "vox" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MGLLIB_EXPORTS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../bin/Release/mgllib.dll"

!ELSEIF  "$(CFG)" == "mgllib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MGLLIB_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "src" /I "src/2d" /I "src/graphic_extends" /I "src/common" /I "src/other" /I "src/game" /I "src/input" /I "vox" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MGLLIB_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../bin/Debug/mgllib.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "mgllib - Win32 Release"
# Name "mgllib - Win32 Debug"
# Begin Group "2D Graphics Files"

# PROP Default_Filter ""
# Begin Group "Extends Pack"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageAnimator.cpp
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageAnimator.h
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageCacher.cpp
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageCacher.h
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageFader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageFader.h
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageManager.h
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageTips.cpp
# End Source File
# Begin Source File

SOURCE=.\src\graphic_extends\MglImageTips.h
# End Source File
# End Group
# Begin Group "_old"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\src\2d\mgl2d.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglBitmapText.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglBitmapText.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglD3dCapsDumper.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglD3dCapsDumper.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglGraphicManager.cpp

!IF  "$(CFG)" == "mgllib - Win32 Release"

!ELSEIF  "$(CFG)" == "mgllib - Win32 Debug"

# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\2d\MglGraphicManager.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglGraphicUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglGraphicUtil.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglImage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglImage.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglText.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglText.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglTexture.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglVertex.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglVertex.h
# End Source File
# End Group
# Begin Group "Common Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\common\mgl.h
# End Source File
# Begin Source File

SOURCE=.\src\common\mgl_global.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\mgl_global.h
# End Source File
# Begin Source File

SOURCE=.\src\common\mglafx.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MglExceptionThrowerBase.h
# End Source File
# Begin Source File

SOURCE=.\src\common\mglheads.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MglManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\MglManager.h
# End Source File
# Begin Source File

SOURCE=.\src\common\mglmsg.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuCommonException.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuCommonException.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuDebugLog.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuDebugLog.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuReleaseBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuReleaseBase.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuStringNameMap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuStringNameMap.h
# End Source File
# End Group
# Begin Group "Other Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\other\MglEzGameFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\MglEzGameFrame.h
# End Source File
# Begin Source File

SOURCE=.\src\other\mglframe.h
# End Source File
# Begin Source File

SOURCE=.\src\other\MyuEzGameManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\MyuEzGameManager.h
# End Source File
# Begin Source File

SOURCE=.\src\other\MyuEzWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\MyuEzWindow.h
# End Source File
# Begin Source File

SOURCE=.\src\other\MyuFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\MyuFunctions.h
# End Source File
# Begin Source File

SOURCE=.\src\other\MyuSingleton.h
# End Source File
# End Group
# Begin Group "Audio Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\audio\MglAudio.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglAudio.h
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglDirectMusicBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglDirectMusicBase.h
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglOgg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglOgg.h
# End Source File
# End Group
# Begin Group "Game Utility Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\game\MglTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\game\MglTimer.h
# End Source File
# Begin Source File

SOURCE=.\src\game\MyuFPS.cpp
# End Source File
# Begin Source File

SOURCE=.\src\game\MyuFPS.h
# End Source File
# Begin Source File

SOURCE=.\src\game\MyuIntervalTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\game\MyuIntervalTimer.h
# End Source File
# End Group
# Begin Group "Input Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\input\MglDirectInputBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglDirectInputBase.h
# End Source File
# Begin Source File

SOURCE=.\src\input\MglInput.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglInput.h
# End Source File
# Begin Source File

SOURCE=.\src\input\mglinput_.h
# End Source File
# Begin Source File

SOURCE=.\src\input\MglJoyInput.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglJoyInput.h
# End Source File
# Begin Source File

SOURCE=.\src\input\MglJoyManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglJoyManager.h
# End Source File
# Begin Source File

SOURCE=.\src\input\MglKeyboardInput.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglKeyboardInput.h
# End Source File
# Begin Source File

SOURCE=.\src\input\MglKeyboardInputBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglKeyboardInputBase.h
# End Source File
# End Group
# Begin Group "Intellisense Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\MSL\MWL\classes\MyuIniReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\MSL\MWL\classes\MyuSpecialIniReader.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\include_test_mgl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\common\MglException.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# Begin Source File

SOURCE=.\src\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\src\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\vox\Vox.h
# End Source File
# End Target
# End Project
