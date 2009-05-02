call "%VS90COMNTOOLS%\vsvars32.bat"

@REM SET TOOL="%VS90%\Common7\IDE\VCExpress.exe"
@SET TOOL=VCExpress.exe
@SET OPT=/Build Release Debug /Log
@SET CMD_R=%TOOL% %SLN% /Build Release /Log
@SET CMD_D=%TOOL% %SLN% /Build Debug /Log

@SET SLN=mgllib_VC90.sln
%TOOL% %SLN% /Build Release /Log 
%TOOL% %SLN% /Build Debug /Log

_geninc