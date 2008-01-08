//////////////////////////////////////////////////////////
//
//	MglImageTips
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglImageTips.h"
#include "MyuSpecialIniReader.h"

//	読み込み
void CMglImageTips::Load( LPCSTR szFileName )
{
	CMyuSpecialIniReader ini;
	ini.Setup(szFileName);

	//	イメージファイル名取得
	const char* szImageFileName = ini.GetString("FILE::IMAGE_FILE");
	if ( *szImageFileName == '\0' )
		MyuThrow( 0, "CMglImageTips::Load()  [FILE]->IMAGE_FILE が見つからないか空です。" );
	//	カラーキー取得
	const char* szColorKeyHex = ini.GetString("FILE::COLOR_KEY","FF00FF");
	D3DCOLOR colorKey = hextonum(szColorKeyHex);
	
	//	矩形テーブル読み込み
	map<string,string> rectTable;
	ini.GetSectionLinesMap( "RECT_TABLE", rectTable );

/*
	//	読み込み
	Load( szImageFileName, rectTable, colorKey );
	//Load( szImageFileName, szFileName, colorKey );
}

//	読み込み
//void CMglImageTips::Load( LPCSTR szImageFile, map<string,RECT> &rectTable, D3DCOLOR colorKey )
void CMglImageTips::Load( LPCSTR szImageFile, map<string,string> &rectTable, D3DCOLOR colorKey )
{
*/
	m_rectTable.clear();

	//	矩形テーブル解析
	map<string,string>::iterator it = rectTable.begin();
	for( ; it!=rectTable.end(); it++ )
	{
		const char* szKeyName = it->first.c_str();
		const char* szValueStr = it->second.c_str();
		
		vector<string> ary;
		if ( string_tokenize( szValueStr, ",", ary ) != 4 )
		{
			MyuThrow( 2,"CMglImageTips::Load()  フォーマットが不正です。\r\n"
						"File: \"%s\"\r\n"
						"Key: %s\r\n"
						"Value: %s", szFileName, szKeyName, szValueStr );
		}

		//	数値になってるかチェック
		if ( isnumstr(ary[0].c_str()) == FALSE ||
			 isnumstr(ary[1].c_str()) == FALSE ||
			 isnumstr(ary[2].c_str()) == FALSE ||
			 isnumstr(ary[3].c_str()) == FALSE )
		{
			MyuThrow( 2,"CMglImageTips::Load()  数値以外が含まれています。\r\n"
						"File: \"%s\"\r\n"
						"Key: %s\r\n"
						"Value: %s", szFileName, szKeyName, szValueStr );
		}

		//	RECT作成
		RECT rect;
		rect.left = atoi(ary[0].c_str());
		rect.top = atoi(ary[1].c_str());
		rect.right = atoi(ary[2].c_str());
		rect.bottom = atoi(ary[3].c_str());

		//	テーブルへ格納
		m_rectTable[szKeyName] = rect;
	}

	//	画像ファイル、本当にある・・・？
	char work[512+10];
	if ( exist_file(szImageFileName) != true )
	{
		//	もしかして同じディレクトリにあんじゃね・・・？
		safe_strcpy( work, szFileName, 256 );
		char *p = strrchr(work,'\\');
		if ( p != NULL )
			safe_strcpy( p+1, szImageFileName, 256 );

		if ( exist_file(work) != true )
			MyuThrow( 0, "CMglImageTips::Load() 画像ファイル \"%s\" が見つかりません。", szImageFileName );
		else
			szImageFileName = work;
	}

	//	画像読み込み
	m_image.Create( szImageFileName, FALSE, colorKey );
	//CMglTexture::CreateTextureFromFile( szImageFileName, FALSE, colorKey );
}

//	新・描画方式
void CMglImageTips::Draw( const char* szRectName, float x, float y,
						 float fScaleX, float fScaleY, D3DCOLOR color )
{
	//	あるかチェック
	if ( m_rectTable.find( szRectName ) == m_rectTable.end() )
		MyuThrow( 3, "CMglImageTips::Draw() %s は不明な矩形テーブルキー名です。", szRectName );

	RECT &rect = m_rectTable[szRectName];
	//m_myudg->SpriteDraw( this, x, y, &rect, color, fScaleX, fScaleY, 0, 0, 0 );
	m_image.Draw( x, y, &rect, color, fScaleX, fScaleY, 0, 0, 0 );

	/*
	//	頂点初期情報取得
	MGL_SQUARE_VERTEXS vertexs;
	this->GetBmpVertexs( &vertexs );

	//	x, yに移動
	MglMoveVertexs( &vertexs, x, y );

	//	頂点の色
	vertexs.lt.color = color;
	vertexs.rt.color = color;
	vertexs.lb.color = color;
	vertexs.rb.color = color;

	//	描画
	CMglTexture::Draw( &vertexs );
	*/
}

int CMglImageTips::GetTipWidth( const char* szRectName )
{
	//	あるかチェック
	if ( m_rectTable.find( szRectName ) == m_rectTable.end() )
		MyuThrow( 3, "CMglImageTips::GetTipWidth() %s は不明な矩形テーブルキー名です。", szRectName );

	RECT *pRect = &m_rectTable[szRectName];
	return pRect->right - pRect->left;
}

int CMglImageTips::GetTipHeight( const char* szRectName )
{
	//	あるかチェック
	if ( m_rectTable.find( szRectName ) == m_rectTable.end() )
		MyuThrow( 3, "CMglImageTips::GetTipHeight() %s は不明な矩形テーブルキー名です。", szRectName );

	RECT *pRect = &m_rectTable[szRectName];
	return pRect->bottom - pRect->top;
}
