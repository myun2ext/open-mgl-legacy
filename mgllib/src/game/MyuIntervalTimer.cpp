//////////////////////////////////////////////////////////
//
//	MyuIntervalTimer  v0.10.00 05/02/03
//		- 間隔タイマー管理クラス（平均時間計測等）
//
//	v0.10.00 05/02/03
//	・CMyuTimerから分離
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyuIntervalTimer.h"

//	コンストラクタ
CMyuIntervalTimer::CMyuIntervalTimer()
{
	//	平均時間
	m_bInitFlg = FALSE;

	//	デフォルト初期化
	Setup( INTERVAL_TYPE_TIME, 1000 );
}

//	デストラクタ
CMyuIntervalTimer::~CMyuIntervalTimer()
{

}

//	初期化
void CMyuIntervalTimer::Setup( int in_nAveIntervalType, int in_nAveIntervalVal )
{
	m_nAveCnt = 0;
	m_fAveTime = 0;
	m_nAveTtlTime = 0;

	m_nAveIntervalType = in_nAveIntervalType;
	m_nAveIntervalVal = in_nAveIntervalVal;

	m_bInitFlg = TRUE;
	m_timer.Start();	//	いらない・・・？
}

//	更新
void CMyuIntervalTimer::Update()
{
	//	平均時間測定
	m_nAveTtlTime += m_timer.Get();
	m_nAveCnt++;

	BOOL bSum=FALSE;

	//	カウント方式
	if ( m_nAveIntervalType == INTERVAL_TYPE_COUNT )
	{
		if ( m_nAveCnt > m_nAveIntervalVal )
			bSum = TRUE;
	}

	//	時間方式
	else
	{
		if ( m_nAveTtlTime >= m_nAveIntervalVal )
			bSum = TRUE;
	}

	//	合計するー？
	if ( bSum == TRUE )
	{
		if ( m_nAveTtlTime >= m_nAveIntervalVal ) {
			m_fAveTime = (float)m_nAveTtlTime / (float)m_nAveCnt;
			m_nAveCnt = 0;
			m_nAveTtlTime = 0;
		}
	}
	
	//	リセットはいりまーす
	m_timer.Start();
}

