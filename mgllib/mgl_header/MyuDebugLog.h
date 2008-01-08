//////////////////////////////////////////////////////////
//
//	MyuEasyWin  v0.13.04 05/02/21
//		- デバッグログクラス
//
//	v0.10.00 04/xx/xx
//	・新規作成
//
//	v0.13.04 05/02/21
//	・Close()でファイルポインタNULLにしてなかった。あぶねーｗ
//
//////////////////////////////////////////////////////////

#ifndef __MyuDebugLog_H__
#define __MyuDebugLog_H__

#include <stdio.h>
#include <stdarg.h>

//////////////////////////////////////////////
//
//	DLLエクスポート（mglafx.hをincludeするので）
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

//	クラス宣言
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