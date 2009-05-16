#include "stdafx.h"
#include "AugustWindow2.h"

/*
int CAugustWindow2::Start( const char* szWindowTitle, const char* szWinClassName,
	int nWinWidthSize, int nWinHeightSize, int nWinXPos=MYU_WINPOS_AUTO, int nWinYPos=MYU_WINPOS_AUTO,
	DWORD dwWinStyle=MYU_WINDOW_DEFAULT_STYLE, int nWindowShow=SW_SHOWDEFAULT )
{

	return Start(szWindowTitle, szWinClassName, nWinWidthSize, nWinHeightSize,
		nWinXPos, nWinYPos, dwWinStyle, nWindowShow );
}
*/
void CAugustWindow2::Start()
{
	try	//	例外処理受け付け開始
	{
		_BASE::Start();
	}
	//	例外処理 V3.0
	catch( MglException& exp )
	{
		HWND hWnd = (HWND)GetHwnd();

		char work[1024];
		snprintf( work, sizeof(work),
			"Myu Game Library Error :\r\n"
			"  Location : %s::%s()   Error Code : 0x%08X\r\n"
			"\r\n"
			"%s",
			exp.szClass, exp.szMethod, exp.nInternalCode, exp.szMsg );

		::MessageBox( hWnd, work, NULL, MB_ICONERROR );
	}
	//	例外処理
	catch( MyuCommonException& except )
	{
		HWND hWnd = (HWND)GetHwnd();

		char work[512];
		//snprintf( work,sizeof(work), "ErrNo : 0x%08X\r\n%s", except.nErrCode, except.szErrMsg );
		snprintf( work,sizeof(work),
			"ErrNo : 0x%08X\r\n%s\r\n"
			"\r\n"
			"%s",
			except.nErrCode, except.szErrMsg,
			g_stackTrace.Dump().c_str() );
		::MessageBox( hWnd, work, NULL, MB_ICONERROR );
	}
}
