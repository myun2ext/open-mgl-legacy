//////////////////////////////////////////////////////////
//
//	MyuCommonException
//		- MGL共通のException
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include <windows.h>
#include "MyuCommonException.h"
#include <stdio.h>

#include "MglManager.h"

//	MglExceptionThrowerBase.cpp用意すんのメンドウっす
#include "MglExceptionThrowerBase.h"
void CMglExceptionThrowerBase::MglThrow( int nErrCode, const char* szMsg, ... )
{
	MglException exp;
	ZeroMemory( &exp, sizeof(exp) );

	exp.nInternalCode = nErrCode;
	safe_strcpy( exp.szClass, m_strClass.c_str(), sizeof(exp.szClass) );
	safe_strcpy( exp.szMethod, m_strMethod.c_str(), sizeof(exp.szMethod) );
	
	va_list vl;
	va_start( vl, szMsg );
	vsnprintf( exp.szMsg, sizeof(exp.szMsg), szMsg, vl );
	va_end( vl );

	/*
	char szDebugLogStr[ERRMSG_BUF];
	snprintf( szDebugLogStr, sizeof(szDebugLogStr), "%s", tExcep.szErrMsg );
	_MGL_DEBUGLOG("");
	_MGL_DEBUGLOG("<<ThrowException>>  %s", szDebugLogStr );
	*/

	//	投げる
	throw exp;
}



//////////////////////////////////////////
//
//				 Ver2.00
//
//////////////////////////////////////////

void MyuThrow2( int in_nApiResultCode, int in_nInternalCode, const char* in_szErrMsg, ... )
{
	MyuCommonException tExcep;

	tExcep.nErrCode = in_nApiResultCode;
	va_list vl;
	va_start( vl, in_szErrMsg );
	ZeroMemory( tExcep.szErrMsg, sizeof(tExcep.szErrMsg) );
	_vsnprintf( tExcep.szErrMsg, sizeof(tExcep.szErrMsg)-1, in_szErrMsg, vl );
	va_end( vl );

	char szDebugLogStr[ERRMSG_BUF];
	ZeroMemory( szDebugLogStr, sizeof(szDebugLogStr) );
	_snprintf( szDebugLogStr, sizeof(szDebugLogStr)-1, "%s", tExcep.szErrMsg );
	_MGL_DEBUGLOG("");
	_MGL_DEBUGLOG("<<ThrowException>>  %s", szDebugLogStr );
	_MGL_DEBUGLOG("StackTrace:\n%s", g_stackTrace.Dump().c_str() );

	throw tExcep;
}

/*
//	Ver2.00用
void MyuThrow2( int in_nApiResultCode, int in_nInternalCode, const char* in_szErrMsg, ... )
{
	MyuCommonException2 tExcep;

	tExcep.nApiResultCode = in_nApiResultCode;
	tExcep.nInternalCode = in_nInternalCode;
	va_list vl;
	va_start( vl, in_szErrMsg );
	ZeroMemory( tExcep.szErrMsg, sizeof(tExcep.szErrMsg) );
	_vsnprintf( tExcep.szErrMsg, sizeof(tExcep.szErrMsg)-1, in_szErrMsg, vl );
	va_end( vl );

	char szDebugLogStr[ERRMSG_BUF];
	ZeroMemory( szDebugLogStr, sizeof(szDebugLogStr) );
	_snprintf( szDebugLogStr, sizeof(szDebugLogStr)-1, "%s", tExcep.szErrMsg );
	_MGL_DEBUGLOG("");
	_MGL_DEBUGLOG("<<ThrowException>>  %s", szDebugLogStr );

	throw tExcep;
}
*/

void MyuAssert2( long in_nApiResultCode, long nOK, int in_nInternalCode, const char* in_szErrMsg, ... )
{
	if ( in_nApiResultCode != nOK )
	{
		char szWork[ERRMSG_BUF];

		va_list vl;
		va_start( vl, in_szErrMsg );
		ZeroMemory( szWork, sizeof(szWork) );
		_vsnprintf( szWork, sizeof(szWork)-1, in_szErrMsg, vl );
		va_end( vl );

		MyuThrow2( in_nApiResultCode, in_nInternalCode, szWork );
	}
}

void* MyuAssertNull( void* p, const char* in_szErrMsg, ... )
{
	if ( p == NULL )
	{
		char szWork[ERRMSG_BUF];

		va_list vl;
		va_start( vl, in_szErrMsg );
		ZeroMemory( szWork, sizeof(szWork) );
		_vsnprintf( szWork, sizeof(szWork)-1, in_szErrMsg, vl );
		va_end( vl );

		MyuThrow2( 0, 0, szWork );
	}
	return p;
}

//////////////////////////////////////////
//
//				 Ver1.00
//
//////////////////////////////////////////

void MyuThrow( int nErrCode, const char* szErrMsg, ... )
{
	MyuCommonException tExcep;

	tExcep.nErrCode = nErrCode;
	va_list vl;
	va_start( vl, szErrMsg );
	vsprintf( tExcep.szErrMsg, szErrMsg, vl );
	va_end( vl );

	char szDebugLogStr[1024];
	sprintf( szDebugLogStr, "%s", tExcep.szErrMsg );
	_MGL_DEBUGLOG("");
	_MGL_DEBUGLOG("<<ThrowException>>  %s", szDebugLogStr );
	_MGL_DEBUGLOG("StackTrace:\n%s", g_stackTrace.Dump().c_str() );

	throw tExcep;
}

void MyuAssert( long nResult, long nOK, const char* szErrMsg, ... )
{
	if ( nResult != nOK )
	{
		MyuCommonException tExcep;

		tExcep.nErrCode = nResult;
		va_list vl;
		va_start( vl, szErrMsg );
		//vsprintf( tExcep.szErrMsg, szErrMsg, vl );
		vsnprintf( tExcep.szErrMsg, sizeof(tExcep.szErrMsg), szErrMsg, vl );
		va_end( vl );

		char szDebugLogStr[1024];
		sprintf( szDebugLogStr, "%s", tExcep.szErrMsg );
		_MGL_DEBUGLOG("");
		_MGL_DEBUGLOG("<<ThrowException>>  %s", szDebugLogStr );
		_MGL_DEBUGLOG("StackTrace:\n%s", g_stackTrace.Dump().c_str() );

		throw tExcep;
	}
}


void MglAssert2( const char* szFile, int nLine, long nResult, long nOK, const char* szErrMsg, ... )
{
	if ( nResult != nOK )
	{
		MglException2 tExcep;

		tExcep.nErrCode = nResult;
		tExcep.szpFile = szFile;
		tExcep.nLine = nLine;

		va_list vl;
		va_start( vl, szErrMsg );
		//vsprintf( tExcep.szErrMsg, szErrMsg, vl );
		vsnprintf( tExcep.szErrMsg, sizeof(tExcep.szErrMsg), szErrMsg, vl );
		va_end( vl );

		char szDebugLogStr[1024];
		sprintf( szDebugLogStr, "%s", tExcep.szErrMsg );
		_MGL_DEBUGLOG("");
		_MGL_DEBUGLOG("<<ThrowException:MglException2>>  %s", szDebugLogStr );

		throw tExcep;
	}
}

