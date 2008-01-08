//////////////////////////////////////////////////////////
//
//	MyuFPS
//		- FPS管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyuFPS.h"

#define WAIT_TIME		(GET_WAIT_FROM_FPS(m_nFPS))

//	コンストラクタ
CMyuFPS::CMyuFPS()
{
	m_nFPS = DEFAULT_FPS;
	m_fNowFps = 0;
	m_dwAdjust = 0;
	//m_timer.Init( INTERVAL_TYPE_TIME, 100 );
}

//	デストラクタ
CMyuFPS::~CMyuFPS()
{

}

//	スリープ処理
void CMyuFPS::Sleep()
{
	//Sleep(0);	//	これしないと時間が上手く取得できない(ﾉД`)

	int nGetTime = m_timer.Get();
	int nWaitTime = (m_dwAdjust>>16) - nGetTime;

	//	スリープ。でもSleep精度は最低でも1msなので
	//	1ms少なめにSleepし↓で空回し
	if ( nWaitTime > 0 )
		::Sleep( nWaitTime-1 );

	//	↑の説明どおり。空回し。
	while( m_timer.Get() < (m_dwAdjust>>16) );

	//	いち早くタイマー更新
	m_timer.Update();

	int nFrameTime = nWaitTime+nGetTime;

	if ( nWaitTime < 0 )
		m_fNowFps = GET_FPS_FROM_TIME( nGetTime );
	else
		m_fNowFps = GET_FPS_FROM_TIME( nFrameTime );

	//	- 0x100 ← オーバーヘッドとか考慮して詐欺る（爆
	m_dwAdjust += ( WAIT_TIME - nFrameTime ) * 0x10000 - 0x100;	
}
