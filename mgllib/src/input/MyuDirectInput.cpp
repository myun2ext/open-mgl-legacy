//////////////////////////////////////////////////////////
//
//	MyuDirectInput
//		- DirectInputクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyuDirectInput.h"

//	コンストラクタ
CMyuDirectInput::CMyuDirectInput()
{
	nRelateCnt = 0;
	m_autoGetBuf = FALSE;
}

//	デストラクタ
CMyuDirectInput::~CMyuDirectInput()
{

}

//	初期化
void CMyuDirectInput::Init( HWND hWnd, BOOL in_autoGetBuf )
{
	CMyuKeyboardInput::Init( hWnd );
	m_autoGetBuf = in_autoGetBuf;
}


//	キーボード入力を名前に関連付ける
void CMyuDirectInput::RelateKey( const char *szInputName, BYTE keyCode )
{
	if( nRelateCnt+1 >= RELATE_MAX )
		MyuThrow( 0, "CMyuDirectInput::RelateKey()  これ以上関連付けることは出来ません" );

	if( strlen(szInputName) >= RELATE_NAME_MAX )
		MyuThrow( 0, "CMyuDirectInput::RelateKey()  szInputName(%s)が長すぎます", szInputName );

	strcpy( relate[nRelateCnt].szInputName, szInputName );
	relate[nRelateCnt].keyCode = keyCode;
	relate[nRelateCnt].oldKeyPush = FALSE;
	relate[nRelateCnt].keyPool = FALSE;

	nRelateCnt++;
}

//	キーがその瞬間に押されているか(関係名版)
BOOL CMyuDirectInput::IsPushKey( const char *szInputName )
{
	//	自動でGetBuf()を実行
	if ( m_autoGetBuf == TRUE )
		GetBuf();

	return CMyuKeyboardInput::IsPushKey( GetRelate(szInputName)->keyCode );
}

//	キーが押されたか（OnEvent的なもの）(関係名版)
BOOL CMyuDirectInput::IsDownKey( const char *szInputName )
{
	if ( m_autoGetBuf == TRUE )
		MyuThrow( 0, "IsDownKey()を使用する場合、AutoGetBufを使用することは出来ません。" );

	INPUT_RELATE *relate = GetRelate(szInputName);

	if ( relate->keyPool == TRUE )
	{
		relate->keyPool = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//	IsKeyPressのためにオーバーロード
void CMyuDirectInput::GetBuf()
{
	//	まずは普通にCMyuKeyboardInputのを呼び出す
	CMyuKeyboardInput::GetBuf();

	//	IsKeyPressのために
	INPUT_RELATE *p;
	for( int i=0; i<nRelateCnt; i++ )
	{
		p = &relate[i];
		BOOL nowIsPush = CMyuKeyboardInput::IsPushKey( p->keyCode );
		if ( nowIsPush )
		{
			int a =0;
		}

		//	前のキーが押されていなく、今回押されていた場合
		if( p->oldKeyPush == FALSE && nowIsPush == TRUE )
		{
			p->keyPool = TRUE;
		}
		p->oldKeyPush = nowIsPush;
	}
}


//	名前からRelate[i]へのポインタを取得
INPUT_RELATE* CMyuDirectInput::GetRelate( const char *szInputName )
{
	INPUT_RELATE *p;
	for( int i=0; i<nRelateCnt; i++ )
	{
		p = &relate[i];

		if( strcmp( szInputName, p->szInputName ) == 0 )
		{
			return p;
		}
	}
	MyuThrow( 0, "CMyuDirectInput::GetRelate()  入力名 %s は存在しません", szInputName );
	return NULL;	//	ここに来ることはありえませんが警告がうざいので
}