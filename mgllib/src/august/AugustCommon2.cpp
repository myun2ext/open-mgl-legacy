#include "stdafx.h"
#include "AugustCommon2.h"
#include "AugustGraphicsManager.h"
#include "MglManager.h"
#include "MglGraphicManager.h"

//	��O�𓊂���
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

//	CAugustGraphicsManager ���� CMglGraphicManager* �̎擾
_AGST_DLL_EXP CMglGraphicManager* _AGrpMgr_GetGrp(CAugustGraphicsManager* pAGrpMgr)
{
	return pAGrpMgr->GetMglGrp();
}

//	�y�C���g
_AGST_DLL_EXP void _AugustPaintRect(CMglGraphicManager* pMglGrp, const agh::CRect &rect, AGHCOLOR color)
{
	pMglGrp->Paint( (::RECT*)&rect, (D3DCOLOR)color);
}
