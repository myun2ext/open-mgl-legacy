//////////////////////////////////////////////////////////
//
//	MyuEasyWin  v0.13.04 05/02/21
//		- �f�o�b�O���O�N���X
//
//	v0.10.00 04/xx/xx
//	�E�V�K�쐬
//
//	v0.13.04 05/02/21
//	�EClose()�Ńt�@�C���|�C���^NULL�ɂ��ĂȂ������B���Ԃˁ[��
//
//////////////////////////////////////////////////////////

#ifndef __MyuDebugLog_H__
#define __MyuDebugLog_H__

#include <stdio.h>
#include <stdarg.h>

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

//	�N���X�錾
class DLL_EXP CMyuDebugLog
{
private:
	FILE *m_fp;
	int m_nSpace;

public:
	CMyuDebugLog();
	virtual ~CMyuDebugLog();

	void Open( const char* szLogFile );
	void Close();
	void Print( const char* format, ... );
};

#endif//__MyuDebugLog_H__