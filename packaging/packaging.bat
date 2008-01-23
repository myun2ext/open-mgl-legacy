@echo off

REM :: ���ϐ��ݒ�
SET MAKEDIR=openmgl_xxxxxx
SET SRC_DIR=..\mgllib
SET DOC_DIR=..\docs
SET DIST_DIR=..\_dist
SET FIRST_DIR=%CD%

REM :: ���ɂ�������폜
del /q /s %MAKEDIR%

REM :: _geninc.bat, build.cmd�Ăяo��
cd %SRC_DIR%
call "%SRC_DIR%\build.cmd"
call "%SRC_DIR%\_geninc.bat"
cd %FIRST_DIR%

REM :: �f�B���N�g������
mkdir %MAKEDIR%
mkdir %MAKEDIR%\mgllib
mkdir %MAKEDIR%\mgllib\debug_dll
mkdir %MAKEDIR%\mgllib\mgl_header
mkdir %MAKEDIR%\mgllib_src
mkdir %MAKEDIR%\mgllib_src\src
mkdir %MAKEDIR%\docs

REM :: DLL�̃R�s�[
xcopy "%DIST_DIR%\Release\mgllib.dll" ".\%MAKEDIR%\mgllib\" /y
xcopy "%DIST_DIR%\Release\mgllib.lib" ".\%MAKEDIR%\mgllib\" /y
xcopy "%SRC_DIR%\vox\Vox.dll" ".\%MAKEDIR%\mgllib\" /y
xcopy "%DIST_DIR%\Debug\mgllib.dll" ".\%MAKEDIR%\mgllib\debug_dll\" /y
REM xcopy "%DIST_DIR%\Debug\mgllib.lib" ".\%MAKEDIR%\mgllib\debug_dll\" /y
xcopy "%SRC_DIR%\vox\Vox_d.dll" ".\%MAKEDIR%\mgllib\debug_dll\" /y

REM :: mgl_header�̃R�s�[
xcopy "%SRC_DIR%\mgl_header\*" ".\%MAKEDIR%\mgllib\mgl_header\" /y

REM :: �\�[�X�̃R�s�[
xcopy "%SRC_DIR%\mgllib.dsp" ".\%MAKEDIR%\mgllib_src" /y
xcopy "%SRC_DIR%\mgllib.dsw" ".\%MAKEDIR%\mgllib_src" /y
xcopy "%SRC_DIR%\resource.h" ".\%MAKEDIR%\mgllib_src" /y
xcopy "%SRC_DIR%\Script1.rc" ".\%MAKEDIR%\mgllib_src" /y
xcopy "%SRC_DIR%\src" ".\%MAKEDIR%\mgllib_src\src" /y /s /e

REM :: �h�L�������g�̃R�s�[
xcopy "%DOC_DIR%" ".\%MAKEDIR%\docs" /y /s /e
