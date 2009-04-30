//////////////////////////////////////////////////////////
//
//	MglText
//		- テキスト
//
//////////////////////////////////////////////////////////

#include "stdafx.h"

//#if _MGL_DXVER == 9
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXFONT_CHANGED

#include "MglText.h"
#include "MglDxSprite.h"

//	コンストラクタ
CMglText::CMglText()
{
	_Init();
}

//	デストラクタ
CMglText::~CMglText()
{
	//Release();
}

////// 作成系 //////////////////////////////////////////////////////

//	作成
void CMglText::Create( int nHeight, const char* szFontName, BOOL bItalic, BOOL bBold )
{
	//CreatedCheck();
	Release();	//	コイツはフォント変更でCreateしまくるのでReleaseしないと駄目か・・・

	int nWeight = FW_DONTCARE;
	if ( bBold )
		nWeight = FW_BOLD;

	if ( szFontName == NULL || *szFontName == '\0' )
		//szFontName = "ＭＳ Ｐゴシック";
		//szFontName = "MS PGothic";
		szFontName = MGL_FONT_NAME_DEFAULT;

	/* 第三引数=Widthは0を指定するとデフォルトの横幅が使用されるっぽい？ */
	MyuAssert( D3DXCreateFont( m_d3d, nHeight, 0, nWeight, 1, bItalic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		szFontName, &m_pI ), D3D_OK,
		"CMglText::Create()  D3DXCreateFont()に失敗。" );

	//m_text = m_pI;
}

//	明示的開放
/*void CMglText::Release()
{
	//SAFE_RELEASE( m_text );
	//bCreateFlg = FALSE;
}*/


////// 絵画系 //////////////////////////////////////////////////////


//	絵画
void CMglText::Draw( const char* szString, int nX, int nY, D3DCOLOR color, DWORD dwOption )
{
	CreateCheck();

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
#if _MGL_DXVER == 9
	//	DirectX9では第一引数としてスプライトを指定するとパフォーマンスが向上するらしい。とりあえず後回しで・・・ (TODO)
	//m_pI->DrawText( NULL, szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );


/*	RECT rect2 = {nX, nY, 0, 0}; //表示領域
	rect = rect2;

    //文字列サイズを計算
    m_pI->DrawText(
        NULL,
        szString,
        -1,             //表示サイズ(-1で全部)
        &rect,          //表示範囲
        DT_CALCRECT,    //表示範囲に調整
        NULL);*/

	m_pD3dDev->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );		// Zバッファを有効にする。
	m_pD3dDev->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );			// Zバッファへの書き込み許可

	CMglDxSprite* pMglSprite = m_myudg->GetTextMglSprite();

	pMglSprite->Begin(D3DXSPRITE_SORT_TEXTURE);

	//	2009/04/05 なんかDT_NOPREFIXつけるとちゃんと出ないみたいだぜ・・・？（何故？
	//m_pI->DrawText( NULL, szString, -1, &rect, DT_NOCLIP | dwOption, color );
	m_pI->DrawText( pMglSprite->GetSpritePtr(), szString, -1, &rect, DT_NOCLIP | dwOption, color );
	
	pMglSprite->End();

	m_pD3dDev->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );		// Zバッファを有効にする。
	m_pD3dDev->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );			// Zバッファへの書き込み許可

#else
	m_pI->DrawText( szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );
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

//	std::vector<std::string> EnumFontNames();

#endif