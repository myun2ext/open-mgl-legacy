#include "stdafx.h"
#include "MglInput.h"
#include "MyuFunctions.h"
#include "MyuDebugLog.h"

#define GET_MSGNO(V)	(MGLMSGNO_INPUT((V)+0x0300))

//	文字列宣言
#define JOY_FIRST_STR	"JOY"
#define JOY_BOTTON_STR	"BTN"
#define KB_FIRST_STR	"KBD"
#define KB_FIRST_STR2	"KB"

//	コンストラクタ
CMglInput::CMglInput()
{
	m_bInitFlg = FALSE;
	SetEtClass("CMglInput");
}

//	デストラクタ
CMglInput::~CMglInput()
{

}

//	初期化処理
void CMglInput::Init( HWND hWnd, DWORD dwCooperativeFlag )
{
	//	チェック
	if ( m_bInitFlg == TRUE )
		MglThrow( GET_MSGNO(9), "CMglInput::Init()  このメソッドは既に呼び出されています。" );

	//	デフォルトのhWnd取得
	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	m_joyAry.clear();

	//	各クラスを初期化
	//m_keyboard.ExInit( hWnd, dwCooperativeFlag );
	CMglKeyboardInput::Init( hWnd, dwCooperativeFlag );
	m_joyMgr.ExInit( hWnd, dwCooperativeFlag );

	//	JoyのAttach
	for( int i=0; i<m_joyMgr.GetJoyCount(); i++ )
	{
		CMglJoyInput joy;
		joy.Attach( m_joyMgr.GetJoyDevice(i) );
		m_joyAry.push_back(joy);
	}

	//	キーボードの関連付け配列生成
	//m_keyboard.GenRtAry();

	//	2008/06/28  マウス対応
	mouse.Init(hWnd);

	//	フラグを立てる
	m_bInitFlg = TRUE;
}

//	その入力が今押されている状態にあるか
//	形式：JOY0-BTN0, KBD-A, KBD-ESC
BOOL CMglInput::IsOn( const char* szInputName )
{
	SetEtMethod("IsOn");

	if ( m_bInitFlg != TRUE )
		MglThrow( GET_MSGNO(9), "Init()を実行するまでこのメソッドを呼び出すことは出来ません。" );

	//	大文字小文字を揃える
	char szWorkInputName[256];
	safe_strcpy( szWorkInputName, szInputName, sizeof(szWorkInputName) );
	strtoupper( szWorkInputName, szWorkInputName );

	const char *pSz = szWorkInputName;

	//	Joy系？
	if ( strncmp( pSz, JOY_FIRST_STR, strlen(JOY_FIRST_STR) ) == 0 )
	{
		pSz += strlen(JOY_FIRST_STR);

		//	何番の？
		int nJoyDevNum = *pSz - '0';
		if ( nJoyDevNum < 0 || nJoyDevNum > 9 )
			MglThrow( GET_MSGNO(1), "szInputName \"%s\" は不正です。", szInputName );
		pSz++;

		//	"-"か"_"になっているかチェック
		if ( *pSz != '_' && *pSz != '-' )
			MglThrow( GET_MSGNO(2), "szInputName \"%s\" は不正です。", szInputName );
		pSz++;

		//	そのJoyってあるのか？
		CHKJOYNO(nJoyDevNum);

		return IsOnJoy( &m_joyAry[nJoyDevNum], pSz );
	}

	//	キーボード系？
	else if ( strncmp( pSz, KB_FIRST_STR, strlen(KB_FIRST_STR) ) == 0 )
	{
		pSz += strlen(KB_FIRST_STR);

		//	"-"か"_"になっているかチェック
		if ( *pSz != '_' && *pSz != '-' )
			MglThrow( GET_MSGNO(5), "szInputName \"%s\" は不正です。", szInputName );
		pSz++;

		return IsOnKbd( pSz );
	}
	//	キーボード系？2
	else if ( strncmp( pSz, KB_FIRST_STR2, strlen(KB_FIRST_STR2) ) == 0 )
	{
		pSz += strlen(KB_FIRST_STR2);

		//	"-"か"_"になっているかチェック
		if ( *pSz != '_' && *pSz != '-' )
			MglThrow( GET_MSGNO(5), "szInputName \"%s\" は不正です。", szInputName );
		pSz++;

		return IsOnKbd( pSz );
	}

	else
	{
		MglThrow( GET_MSGNO(9), "szInputName \"%s\" は不正です。", szInputName );
	}

	return FALSE;
}

//	Joyの入力
BOOL CMglInput::IsOnJoy( CMglJoyInput* pJoy, const char* szJoyInputName )
{
	const char *pSz = szJoyInputName;

	//	ボタン
	if ( strncmp( pSz, JOY_BOTTON_STR, strlen(JOY_BOTTON_STR) ) == 0 )
	{
		pSz += strlen(JOY_BOTTON_STR);

		//	ボタン番号
		int nBottonNo=0;
		if ( ec_atoi( pSz, &nBottonNo ) != TRUE )
			MglThrow( GET_MSGNO(3), "CMglInput::IsOnJoy() JOYx-\"%s\" は不正です。", szJoyInputName );

		return pJoy->IsPushBotton( nBottonNo );
	}
	else
	{
		//	複数文字(文字列)
		if ( strcmp( pSz, "UP" ) == 0 )
			return pJoy->IsUp();
		else if ( strcmp( pSz, "DOWN" ) == 0 )
			return pJoy->IsDown();
		else if ( strcmp( pSz, "LEFT" ) == 0 )
			return pJoy->IsLeft();
		else if ( strcmp( pSz, "RIGHT" ) == 0 )
			return pJoy->IsRight();

		else
			MglThrow( GET_MSGNO(4), "CMglInput::IsOnJoy() JOYx-\"%s\" は不正です。", szJoyInputName );
		
		return 999;	//	実際は通らないけどVCのコンパイラを欺くため
	}
}

//	キーボードの入力
BOOL CMglInput::IsOnKbd( const char* szInputName )
{
	const char *pSz = szInputName;

	//	一文字以上あるかのチェック
	if ( *pSz == '\0' )
		MglThrow( GET_MSGNO(6), "szInputName (KBD) \"%s\" は不正です。", szInputName );

	//	一文字か？複数文字(文字列)か？
	BYTE diKeycode = 0x00;
	if ( *(pSz+1) == '\0' )
	{
		//	一文字
		//char cName = *pSz;
		//diKeycode = m_kbFastRtAry[ cName ];
		//diKeycode = m_keyboard.GetDik(*pSz);
		diKeycode = GetDik(*pSz);

		if ( diKeycode == 0x00 )
			MglThrow( GET_MSGNO(10), "szInputName (KBD) \"%s\" は不明なキーボード文字を表現しています。", szInputName );
	}
	else
	{

//	マクロで短くするー
#define STRTODI( NAME, DIKEYCODE )	else if ( strcmp( pSz, NAME ) == 0 ) diKeycode = DIKEYCODE

		//	複数文字(文字列)
		if ( 0 == 1 );
		STRTODI( "ESC",				DIK_ESCAPE );
		STRTODI( "ESCAPE",			DIK_ESCAPE );
		STRTODI( "ENTER",			DIK_RETURN );
		STRTODI( "RETURN",			DIK_RETURN );
		STRTODI( "SPACE",			DIK_SPACE );
		STRTODI( "LCTRL",			DIK_LCONTROL );
		STRTODI( "DIK_LCONTROL",	DIK_LCONTROL );

		STRTODI( "UP",		DIK_UP );
		STRTODI( "DOWN",	DIK_DOWN );
		STRTODI( "LEFT",	DIK_LEFT );
		STRTODI( "RIGHT",	DIK_RIGHT );

#undef STRTODI

		else
			MglThrow( GET_MSGNO(11), "szInputName (KBD) \"%s\" は不明なキーボード文字を表現しています。", szInputName );
	}

	//	やっとこさステートを取得
	//m_keyboard.UpdateStateBuf();	//	1000回くらい実行しても全然平気だった
	CMglKeyboardInput::UpdateStateBuf();	//	1000回くらい実行しても全然平気だった
	//return m_keyboard.IsOnKey( diKeycode );
	return CMglKeyboardInput::IsPressKey( diKeycode );
}

//	押された瞬間ならTRUEを、そうでない場合はFALSEを返す
BOOL CMglInput::GetIsOnEvent( const char* szInputName )
{
	EVEMAP_ITR itrEveMap = m_onEventMap.find( szInputName );

	//	とりあえず取得しとく
	BOOL bNowFlg = IsOn( szInputName );

	//	ある？
	if ( itrEveMap != m_onEventMap.end() )
	{
		BOOL bPrevFlg = itrEveMap->second;
		if ( bPrevFlg == TRUE )
		{
			//	前回はTRUE
			m_onEventMap[szInputName] = bNowFlg;
			return FALSE;
		}
		else
		{
			//	前回はFALSE
			m_onEventMap[szInputName] = bNowFlg;
			return bNowFlg;
		}
	}
	else
	{
		//	初回なので取得された値をそのまま復帰
		m_onEventMap[szInputName] = bNowFlg;	//	記憶
		return bNowFlg;
	}
}

//	イベントの設定
void CMglInput::SetOnEvent( const char* szInputName, BOOL bEvent )
{
	EVEMAP_ITR itrEveMap = m_onEventMap.find( szInputName );

	//	ありません！
	if ( itrEveMap == m_onEventMap.end() )
		MglThrow( GET_MSGNO(7), "szInputName \"%s\" は存在しません。", szInputName );

	m_onEventMap[szInputName] = bEvent;
}

//	Joyの設定
void CMglInput::SetJoyStickInfo( int nDeviceNo, long nNeutralX, long nNeutralY, long nMargin )
{
	CHKJOYNO(nDeviceNo);
	m_joyAry[nDeviceNo].SetJoyStickInfo( nNeutralX, nNeutralY, nMargin );
}
