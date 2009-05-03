//////////////////////////////////////////////////////////
//
//	MyuCommonException  v1.80
//		- MGL���ʂ�Exception
//
//	v1.00  xx/xx/xx
//	�E�V�K�쐬
//
//	v1.80  05/02/24
//	�E�b��V�o�[�W����
//
//	v1.85  05/02/24
//	�E�ꉞ MyuThrow2()�AMyuAssert2() �Ƃ��AVer1.00�Ƌ����ł���悤�ɁB
//
//	v1.90  05/02/24
//	�E�Ƃ肠���� MyuThrow2()�AMyuAssert2() ���Ă�ł�
//	�@MyuCommonException�𓊂���悤�ȍ\����
//
//////////////////////////////////////////////////////////

#ifndef _MYUCOMMONEXCEPTION_H
#define _MYUCOMMONEXCEPTION_H

//////////////////////////////////////////////
//
//	DLL�G�N�X�|�[�g�imglafx.h��include����̂Łj
//
#ifdef MGLLIB_EXPORTS
#define DLL_EXP __declspec(dllexport)
#endif

#ifdef MGLLIB_INPORTS
#define DLL_EXP __declspec(dllimport)
#endif

#ifndef DLL_EXP
#define DLL_EXP
#endif

/////////////////////////////////////

#include <stdarg.h>

#define ERRMSG_BUF		(1024)


//	Ver2.00
typedef struct
{
	int nInternalCode;
	int nApiResultCode;
	char szErrMsg[ERRMSG_BUF];
} MyuCommonException2;

DLL_EXP void MyuThrow2( int in_nApiResultCode, int in_nInternalCode, const char* in_szErrMsg, ... );
DLL_EXP void MyuAssert2( long in_nApiResultCode, long nOK, int in_nInternalCode, const char* in_szErrMsg, ... );
DLL_EXP void* MyuAssertNull( void* p, const char* in_szErrMsg, ... );

DLL_EXP void MglThrow( int nErrCode, const char* szMsg, ... );

/*
inline MyuEzErrorMessageBox( HWND hWnd, MyuCommonException2 *exp )
{
	char szLog[1024];
	if ( except.nErrCode == 0 )
		sprintf( szLog, "%s", except.szErrMsg );
	else
		sprintf( szLog, "%s\r\n( %s )", except.szErrMsg, GetD3DResultString(except.nErrCode) );
	MessageBox( hWnd, szLog, "MGL Error", MB_ICONERROR );
}
*/

//	Ver1.0
typedef struct
{
	int nErrCode;
	char szErrMsg[1024];
} MyuCommonException;


DLL_EXP void MyuThrow( int nErrCode, const char* szErrMsg, ... );
DLL_EXP void MyuAssert( long nResult, long nOK, const char* szErrMsg, ... );

#endif //_MYUCOMMONEXCEPTION_H
