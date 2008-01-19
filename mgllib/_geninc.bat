set EXTERNAL_DIR=..\_dist\mgl_header

del %EXTERNAL_DIR% /Q
mkdir %EXTERNAL_DIR%
xcopy src\2d\*.h %EXTERNAL_DIR%
xcopy src\graphic_extends\*.h %EXTERNAL_DIR%
xcopy src\audio\*.h %EXTERNAL_DIR%
xcopy src\common\*.h %EXTERNAL_DIR%
xcopy src\game\*.h %EXTERNAL_DIR%
xcopy src\input\*.h %EXTERNAL_DIR%
xcopy src\other\*.h %EXTERNAL_DIR%
xcopy vox\*.h %EXTERNAL_DIR%
del %EXTERNAL_DIR%\ÉRÉsÅ[*
