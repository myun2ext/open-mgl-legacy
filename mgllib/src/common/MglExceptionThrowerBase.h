#ifndef __MglExceptionThrowerBase_H__
#define __MglExceptionThrowerBase_H__

//	Ver3.0
typedef struct
{
	int nInternalCode;
	int nApiResultCode;
	char szClass[64];
	char szMethod[64];
	char szMsg[512];
} MglException;


//	クラス宣言
class DLL_EXP CMglExceptionThrowerBase
{
protected:
	string m_strClass;
	string m_strMethod;

	//	設定
	void SetEtClass( const char* szClass ){ m_strClass = szClass; }
	void SetEtMethod( const char* szMethod ){ m_strMethod = szMethod; }

	//	throw
	void MglThrow( int nErrCode, const char* szMsg, ... );
	/*{
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
		*//*

		//	投げる
		throw exp;
	}*/
	//void MglAssert( long in_nApiResultCode, long nOK, int in_nInternalCode, const char* in_szErrMsg, ... );
	//void MglThrowAPI( int in_nApiResultCode, int in_nInternalCode, const char* in_szErrMsg, ... );
	//void MglAssertAPI( long in_nApiResultCode, long nOK, int in_nInternalCode, const char* in_szErrMsg, ... );

public:
	//	コンストラクタ
	CMglExceptionThrowerBase(){}

	//	デストラクタ
	virtual ~CMglExceptionThrowerBase(){}
};

#endif//__MglExceptionThrowerBase_H__
