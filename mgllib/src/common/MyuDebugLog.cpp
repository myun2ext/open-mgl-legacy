//////////////////////////////////////////////////////////
//
//	MyuDebugLog
//		- デバッグログクラス
//
//////////////////////////////////////////////////////////

#include <windows.h>
#include "MyuDebugLog.h"

//	コンストラクタ
CMyuDebugLog::CMyuDebugLog()
{
	m_fp = NULL;
	m_nSpace = 0;
}

//	デストラクタ
CMyuDebugLog::~CMyuDebugLog()
{
	Close();
}

//	オープン
void CMyuDebugLog::Open( const char* szLogFile )
{
	m_fp = fopen( szLogFile, "w" );
	//if ( m_fp == NULL )
	//	MyuThrow( 0, "CMyuDebugLog::Open()  ログファイル %s のオープンに失敗。", szLogFile );
}

//	クローズ
void CMyuDebugLog::Close()
{
	if ( m_fp != NULL )
	{
		fclose( m_fp );
		m_fp = NULL;
	}
}

//	出力
/*
################# インデント機能について #################

	formatの開始文字を'+'にすると、インデントを下げます。
	formatの開始文字を'-'にすると、インデントを上げます。
*/
void CMyuDebugLog::Print( const char* format, ... )
{
	if ( m_fp == NULL )
		return;
		//MyuThrow( 0, "ログファイルがオープンされていません。" );

	//////////////////////////
	//
	//		インデント
	//

	//	マイナスは先に
	if ( *format == '-' )
		m_nSpace-=2;
	
	char szIndent[256];
	ZeroMemory( szIndent, sizeof( szIndent ));
	if ( m_nSpace < 0 )
		strcpy( szIndent, "<<Indent Error!!>>" );
	else
		memset( szIndent, ' ', m_nSpace );

	//	プラスは後に
	if ( *format == '+' )
		m_nSpace+=2;

	//////////////////////////////

	char szTime[256];
	char szWork[2048];

	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);//getting current time
	sprintf( szTime, "%02d:%02d:%02d.%03d", SysTime.wHour,SysTime.wMinute, SysTime.wSecond,SysTime.wMilliseconds);
	sprintf( szWork, "%s  %s%s\n", szTime, szIndent, format );

	va_list vl;
	va_start( vl, format );
	vfprintf( m_fp, szWork, vl );
	va_end( vl );
	fflush( m_fp );
}
