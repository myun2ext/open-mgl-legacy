//////////////////////////////////////////////////////////
//
//	MglText
//		- テキスト
//
//////////////////////////////////////////////////////////

#include "stdafx.h"

//#if _MGL_DXVER == 8
#if _MGL_D3DXVER < MGL_D3DXVER_ID3DXFONT_CHANGED
#include "MglText.h"

//	コンストラクタ
/*CMglText::CMglText()
{
	_Init();

	//	デフォルトフォント
	Create();
}*/

//	デストラクタ
CMglText::~CMglText()
{
	Release();
}

////// 作成系 //////////////////////////////////////////////////////

//	サイズ指定による作成
void CMglText::InitAndCreate( CMglGraphicManager* in_myudg, int nHeight )
{
	Release();	//	一応リリース

	HFONT hFont = CreateFont( nHeight, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 0, 0, 4, 0, "" );
	if ( hFont == NULL )
		MyuThrow( 0, "CMglText::InitAndCreate()  CreateFont()に失敗。" );

	InitAndCreate( in_myudg, hFont );

	//	20007/01/02
	DeleteObject(hFont);
}

//	szFontNameのデフォルトは空文字またはNULL
void CMglText::Create( CMglGraphicManager* in_myudg, int nHeight, const char* szFontName,
		BOOL bItalic, BOOL bBold, BOOL bUnderLine, BOOL bStrikeOut, float fAngle )
{
	Release();	//	一応リリース

	int nWeight = FW_DONTCARE;
	if ( bBold )
		nWeight = FW_BOLD;

	HFONT hFont = CreateFont( nHeight, 0, (int)(fAngle*10), (int)(fAngle*10),
		nWeight, bItalic, bUnderLine, bStrikeOut, DEFAULT_CHARSET, 0, 0, 4, 0, szFontName );

	if ( hFont == NULL )
		MyuThrow( 0, "CMglText::InitAndCreate()  CreateFont()に失敗。" );

	InitAndCreate( in_myudg, hFont );

	//	20007/01/02
	DeleteObject(hFont);
}
	
//	初期化及び作成
void CMglText::InitAndCreate( CMglGraphicManager* in_myudg, HFONT hFont )
{
	Release();	//	一応リリース

	if ( bCreateFlg == TRUE )
		MyuThrow( 0, "CMglText::InitAndCreate()  既に InitAndCreate() は実行されています。" );

	if ( hFont == NULL )
		MyuThrow( 0, "CMglText::InitAndCreate()  hFontがNULLです。" );

	m_myudg = in_myudg;
	m_d3d = m_myudg->GetD3dDevPtr();

	//	自動開放用にリファレンスを追加
	m_myudg->AddRefOfAutoRelease( this );

	MyuAssert( D3DXCreateFont( m_d3d, hFont, &m_text ),
		D3D_OK, "CMglText::InitAndCreate()  D3DXCreateFont()に失敗。" );

	bCreateFlg = TRUE;
}

//	明示的開放
void CMglText::Release()
{
	//	自動開放用のリファレンスを削除
	DELREF();

	SAFE_RELEASE( m_text );

	bCreateFlg = FALSE;
}


////// 絵画系 //////////////////////////////////////////////////////


//	絵画
void CMglText::Draw( const char* szString, int nX, int nY, D3DCOLOR color, DWORD dwOption )
{
	if ( bCreateFlg == FALSE )
		MyuThrow( 0, "CMglText::Draw()  InitAndCreate() または InitAndEzCreate() を実行してください。" );

	RECT rect;
	if ( (dwOption & DT_RIGHT) != 0 )
		_Rect( 0, nY, nX, m_myudg->GetDispY(), &rect );
	else
		_Rect( nX, nY, m_myudg->GetDispX(), m_myudg->GetDispY(), &rect );

	//MyuAssert( m_text->DrawText( szString, -1, &rect, DT_NOCLIP | dwOption, color ),
	//	D3D_OK, "CMglText::Draw()  m_text->DrawText()に失敗。" );

	//	DirectX8のヘルプだと正常終了が0だが最新のDirectX9のヘルプを見ると
	//	「論理的単位を使ってテキストの高さを返す」になっている…。
	//	論理的単位でチェックしてDirectX8で動かなかったら嫌なのでチェックするのやめます(;´Д`)ゞ
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXSPRITE_CHANGED
	//	DirectX9では第一引数としてスプライトを指定するとパフォーマンスが向上するらしい。とりあえず後回しで・・・ (TODO)
	m_text->DrawText( NULL, szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );
#else
	m_text->DrawText( szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );
#endif
}

//	フォーマットDraw()
void CMglText::FDraw( const char* szString, ... )
{
	SetParamCheck();

	char szFormatedString[1024];
	if ( strlen( szString ) > sizeof(szFormatedString)-1 )
		MyuThrow( 0, "CMglText::FDraw()は %d バイトを越える文字列を扱うことは出来ません。", sizeof(szFormatedString)-1 );

	va_list vl;
	va_start( vl, szString );
	vsprintf( szFormatedString, szString, vl );
	va_end( vl );

	Draw( szFormatedString, m_nX, m_nY, m_color, m_dwOption );
}

//	フォントを設定
void CMglText::SetDrawParam( int in_nX, int in_nY, D3DCOLOR in_color, DWORD in_dwOption )
{
	m_nX = in_nX;
	m_nY = in_nY;
	m_dwOption = in_dwOption;
	m_color = in_color;
	bSetParamFlg = TRUE;
}

#endif