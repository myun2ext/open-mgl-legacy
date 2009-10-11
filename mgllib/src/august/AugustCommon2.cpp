#include "stdafx.h"
#include "AugustCommon2.h"
#include "MglManager.h"

//	—áŠO‚ð“Š‚°‚é
void AugustThrow( unsigned long nCode, const char* szMsgFormat, ... )
{
	AugustException exp;

	exp.nCode = nCode;
	va_list vl;
	va_start( vl, szMsgFormat );
	vsnprintf( exp.szMsg, sizeof(exp.szMsg), szMsgFormat, vl );
	va_end( vl );

	char szDebugLogStr[1024];
	sprintf( szDebugLogStr, "%s", exp.szMsg );
	_MGL_DEBUGLOG("");
	_MGL_DEBUGLOG("<<Throw:AugustException>>  %s", szDebugLogStr );
	_MGL_DEBUGLOG("StackTrace:\n%s", g_stackTrace.Dump().c_str() );

	throw exp;
}

void _AGST_DLL_EXP _AugustPaintRect(AGHCOLOR color, agh::CRect rect)
{

}
