//////////////////////////////////////////////////////////
//
//	MglTimer
//		- タイマー管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglTimer.h"

//	コンストラクタ
CMglTimer::CMglTimer()
{
	//	最初精度を上げる
	timeBeginPeriod(1);

	//	初期化
	Reset();
	//Start();
}

//	デストラクタ
CMglTimer::~CMglTimer()
{
	//	精度を元に戻す
	timeEndPeriod(1);
}

//	初期化
void CMglTimer::Reset()
{
	m_dwPauseTime = 0;
	m_bPause = TRUE;
}

//	タイマー開始
void CMglTimer::Start( DWORD nStartTime )
{
	//	平均時間測定
	m_dwStartGetTime = GetTime();
	m_bPause = FALSE;
}

//	まぁ時間取得、っと。
DWORD CMglTimer::GetTime()
{
	//timeBeginPeriod(1);
	DWORD t = timeGetTime();
	//timeEndPeriod(1);

	return t;
}

//	ポーズ状態ならUnpause。そうでないならStart
void CMglTimer::UnpauseOrStart( DWORD nStartTime )
{
	if ( m_bPause == TRUE )
		Pause();
	else
		Start( nStartTime );
}

//	経過時間取得
DWORD CMglTimer::Get()
{
	if ( m_bPause == FALSE )
	{
		DWORD r = GetTime() - m_dwStartGetTime;

		//	破綻用処理
		if ( r < 0 )
		{
			r += 0x7FFFFFFF;
		}
		return r;
	}
	else
		return m_dwPauseTime;
}

//	タイマー一時停止
void CMglTimer::Pause()
{
	if ( m_bPause == FALSE )
		Pause( TRUE );
	else
		Pause( FALSE );
}

//	タイマー一時停止
void CMglTimer::Pause( BOOL bPauseValue )
{
	if ( bPauseValue == TRUE )
	{
		//	凍結
		m_dwPauseTime = Get();
		m_bPause = TRUE;
	}
	else
	{
		//	解凍
		m_bPause = FALSE;
		m_dwStartGetTime = timeGetTime() + m_dwPauseTime;
	}
}
