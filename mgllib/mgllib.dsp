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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "src" /I "src/august" /I "src/2d" /I "src/3d" /I "src/graphic_extends" /I "src/common" /I "src/window" /I "src/game" /I "src/input" /I "src/audio" /I "src/mglgui" /I "vox" /I "../MSL/include" /I "../MWL/include" /I "../AGH/include/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MGLLIB_EXPORTS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../bin/Release/mgllib.dll" /implib:"../lib/mgllib.lib" /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "src" /I "src/august" /I "src/2d" /I "src/3d" /I "src/graphic_extends" /I "src/common" /I "src/window" /I "src/game" /I "src/input" /I "src/audio" /I "src/mglgui" /I "vox" /I "../MSL/include" /I "../MWL/include" /I "../AGH/include/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MGLLIB_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../bin/Debug/mgllib.dll" /implib:"../lib/mgllib.lib" /pdbtype:sept /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none

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
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\2d\MglBitmapData.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglBitmapData.h
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

SOURCE=.\src\2d\MglGraphicUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglGraphicUtil.h
# End Source File
# End Group
# Begin Group "Layer"

# PROP Default_Filter ""
# Begin Group "Effect Layer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\2d\MglBlinkLayer.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglFadeLayer.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\2d\MglAnimationLayer.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglBitmapTextLayer.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglFadeLayer.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglImageLayer.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglLayerBase4.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglLayers4.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglLayers4.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglTextLayer.h
# End Source File
# End Group
# Begin Group "MGL GUI"

# PROP Default_Filter ""
# Begin Group "MFC"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "Vertex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\2d\MglVertex.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglVertex.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglVertexManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglVertexManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\2d\mgl2d.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglD3dTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglD3dTexture.h
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

SOURCE=.\src\2d\MglImage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglImage.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglSprite.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglSprite.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglText.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglText9.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglTexture.h
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglTexture2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\2d\MglTexture2.h
# End Source File
# End Group
# Begin Group "3D Graphics Files"

# PROP Default_Filter ""
# Begin Group "Shader"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\3d\MglHLSL.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglHLSL.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglHlslValue.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglPixelShader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglPixelShader.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglVertexShader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglVertexShader.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglXShader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglXShader.h
# End Source File
# End Group
# Begin Group "Matrix"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\3d\Mgl3dManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\Mgl3dManager.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglCameraMatrixManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglCameraMatrixManager.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglMatrixManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglMatrixManager.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglWorldMatrixManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglWorldMatrixManager.h
# End Source File
# End Group
# Begin Group "Model"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\3d\Mgl3dDot.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\Mgl3dDot.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\Mgl3dImage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\Mgl3dImage.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\Mgl3dSquare.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\Mgl3dSquare.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglCustomMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglCustomMesh.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglMesh.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\3d\mgl3d.h
# End Source File
# Begin Source File

SOURCE=.\src\3d\mgl3d_work.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglLight.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3d\MglLight.h
# End Source File
# End Group
# Begin Group "Common Files"

# PROP Default_Filter ""
# Begin Group "Exception"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\common\MglException.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MglExceptionCode.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MglExceptionThrowerBase.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuCommonException.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuCommonException.h
# End Source File
# End Group
# Begin Group "Class"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\common\MglClassBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\MglClassBuilder.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MglClassMsg.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MglManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\MglManager.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuDebugLog.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuDebugLog.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuFunctions.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuLoaderBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuLoaderBase.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuReleaseBase.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuSingleton.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuStringNameMap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\common\MyuStringNameMap.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\common\mgl.h
# End Source File
# Begin Source File

SOURCE=.\src\common\mgl_common.h
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

SOURCE=.\src\common\mglheads.h
# End Source File
# Begin Source File

SOURCE=.\src\common\mglmsg.h
# End Source File
# Begin Source File

SOURCE=.\src\common\MglStandardTypes.h
# End Source File
# End Group
# Begin Group "Window Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\window\MglEzGameFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\src\window\MglEzGameFrame.h
# End Source File
# Begin Source File

SOURCE=.\src\window\mglframe.h
# End Source File
# Begin Source File

SOURCE=.\src\window\MyuEzGameManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\window\MyuEzGameManager.h
# End Source File
# Begin Source File

SOURCE=.\src\window\MyuEzWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\src\window\MyuEzWindow.h
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

SOURCE=.\src\input\MglDirectInputDeviceBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglDirectInputDeviceBase.h
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
# Begin Source File

SOURCE=.\src\input\MglMouseInput.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglMouseInput.h
# End Source File
# Begin Source File

SOURCE=.\src\input\MglMouseInputBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\input\MglMouseInputBase.h
# End Source File
# End Group
# Begin Group "Audio Files"

# PROP Default_Filter ""
# Begin Group "2G"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\audio\MglAudioBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglAudioBase.h
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglDirectShowBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglDirectShowBase.h
# End Source File
# End Group
# Begin Group "BGM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\audio\MglBgm.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglBgm.h
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglBgmBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglBgmBase.h
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglMp3Dshow.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglMp3Dshow.h
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglOgg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audio\MglOgg.h
# End Source File
# End Group
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
# End Group
# Begin Group "August Framework"

# PROP Default_Filter ""
# Begin Group "AGH"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\AGH\include\agh.h
# End Source File
# Begin Source File

SOURCE=..\AGH\include\agh_ControlBase.h
# End Source File
# Begin Source File

SOURCE=..\AGH\include\agh_defs.h
# End Source File
# Begin Source File

SOURCE=..\AGH\include\agh_EffectControl.h
# End Source File
# Begin Source File

SOURCE=..\AGH\include\agh_Events.h
# End Source File
# Begin Source File

SOURCE=..\AGH\include\agh_ScreenBase.h
# End Source File
# End Group
# Begin Group "old"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\mglgui\MglAghImage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mglgui\MglAghImage.h
# End Source File
# Begin Source File

SOURCE=.\src\mglgui\MglguiScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mglgui\MglguiScreen.h
# End Source File
# Begin Source File

SOURCE=.\src\mglgui\MglguiScreen_Events.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mglgui\MglguiText.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mglgui\MglguiText.h
# End Source File
# Begin Source File

SOURCE=.\src\mglgui\MglguiWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mglgui\MglguiWindow.h
# End Source File
# End Group
# Begin Group "3D Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\august\August3dManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\august\August3dManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\august\AugustCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustCommon.h
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustEzGameFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustEzGameFrame.h
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustImage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustImage.h
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustScreen.h
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustScreen_Events.cpp
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustText.cpp
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustText.h
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\src\august\AugustWindow.h
# End Source File
# Begin Source File

SOURCE=.\src\august\mglaugust.h
# End Source File
# End Group
# Begin Group "Intellisense Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\audevcod.h"
# End Source File
# Begin Source File

SOURCE=..\MSL\include\auto_fp.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\BaseTsd.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3d8.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3d8caps.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8caps.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3d8types.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8types.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3dx8.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3dx8core.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8core.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3dx8effect.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8effect.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3dx8math.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8math.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3dx8math.inl
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8math.inl"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3dx8mesh.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8mesh.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3dx8shape.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8shape.h"
# End Source File
# Begin Source File

SOURCE=C:\dxsdk90b\Include\d3dx8tex.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8tex.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dls1.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmdls.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmerror.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmplugin.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusbuff.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusicc.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusici.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\DShow.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dxfile.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\Guiddef.h"
# End Source File
# Begin Source File

SOURCE=..\MSL\include\int_string.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\msl.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\msl_ra_list.h
# End Source File
# Begin Source File

SOURCE=..\..\MSL\trunk\MSL\header\msl_ra_list.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\msl_stlcommon.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslcharset.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslcommon.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslfile.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslfile2.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslnet.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslrand.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslstd.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslstl.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslstr.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslstr2.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\msltime.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwl.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwl_filedlg.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlcommon.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlfile.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MwlFileUtil.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlmsg.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlstd.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\myu_dynamic_string.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\myu_super_stream.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\MyuCharbuf.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuCharCnv.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\MyuDynamicArray.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuDynamicDll.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\MyuFgets.h
# End Source File
# Begin Source File

SOURCE=..\..\..\MSL\MWL\classes\MyuIniReader.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuIniReader.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuIniWriter.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuProcessManager.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuRegReader.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\MyuSimpleStackTrace.h
# End Source File
# Begin Source File

SOURCE=..\..\..\MSL\MWL\classes\MyuSpecialIniReader.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuSpecialIniReader.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuThreadBase.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuThreadManager.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\PropIdl.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\Reason.h"
# End Source File
# Begin Source File

SOURCE=..\MSL\include\StlSerializer.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\StrAlign.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\Tvout.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\WinEFS.h"
# End Source File
# End Group
# Begin Group "追放 Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\_exile\MglLayer3.cpp
# End Source File
# Begin Source File

SOURCE=.\src\_exile\MglLayer3.h
# End Source File
# Begin Source File

SOURCE=.\src\_exile\MglLayers2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\_exile\MglLayers2.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\include_test_mgl.cpp
# SUBTRACT CPP /YX /Yc /Yu
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
