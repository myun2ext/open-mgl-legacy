//////////////////////////////////////////////////////////
//
//	MglBitmapText
//		- ビットマップテキスト表示クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglBitmapText.h"

//	コンストラクタ
CMglBitmapText::CMglBitmapText()
{
	m_myudg = NULL;
	m_nOneCharWidth = 0;
	m_nOneCharHeight = 0;
	initFlg = FALSE;
}

//	デストラクタ
CMglBitmapText::~CMglBitmapText()
{

}

//	初期化
void CMglBitmapText::Init( CMglGraphicManager *in_myudg, const char* szBitmapFile,
	int nOneCharWidth, int nOneCharHeight, const char* szStringSequence )
{
	m_myudg = in_myudg;
	sfcBitmapFont.Init( m_myudg );
	//sfcBitmapFont.CreateFromFile( szBitmapFile, FALSE );
	sfcBitmapFont.Create( szBitmapFile, FALSE );
	m_stringSequence = szStringSequence;
	m_nOneCharWidth = nOneCharWidth;
	m_nOneCharHeight = nOneCharHeight;

	initFlg = TRUE;
}


//	絵画
void CMglBitmapText::Draw( const char* szDrawString, float x, float y, D3DCOLOR color )
{
	InitCheck();
	DrawEx( szDrawString, 1.0f, 1.0f, 0, 0, 0, x, y, color );
}

//	絵画
void CMglBitmapText::Draw( int nDrawNum, float x, float y, D3DCOLOR color )
{
	char szDrawString[32];
	sprintf( szDrawString, "%d", nDrawNum );
	Draw( szDrawString, x, y, color );
}


//	絵画Ex
void CMglBitmapText::DrawEx( int nDrawNum, float fScaleX, float fScaleY,
	float fRotationCenterX, float fRotationCenterY, float fAngle, float x, float y, D3DCOLOR color, DWORD dwAlphaOption )
{
	char szDrawString[32];
	sprintf( szDrawString, "%d", nDrawNum );
	DrawEx( szDrawString, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, color );
}

//	絵画Ex
void CMglBitmapText::DrawEx( const char* szDrawString, float fScaleX, float fScaleY,
	float fRotationCenterX, float fRotationCenterY, float fAngle, float x, float y, D3DCOLOR color, DWORD dwAlphaOption )
{
	//DrawEx2( szDrawString, m_nOneCharWidth * fScaleX, m_nOneCharHeight * fScaleX,
	//	fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, color );
	DrawEx2( szDrawString, 0, 0, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, color );
}


//	絵画Ex2
void CMglBitmapText::DrawEx2( int nDrawNum, int nCharSpace, int nLineSpace, float fScaleX, float fScaleY,
	float fRotationCenterX, float fRotationCenterY, float fAngle, float x, float y, D3DCOLOR color, DWORD dwAlphaOption )
{
	char szDrawString[32];
	sprintf( szDrawString, "%d", nDrawNum );
	DrawEx2( szDrawString, nCharSpace, nLineSpace, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, color );
}

//	絵画Ex2
void CMglBitmapText::DrawEx2( const char* szDrawString, int nCharSpace, int nLineSpace, float fScaleX, float fScaleY,
	float fRotationCenterX, float fRotationCenterY, float fAngle, float x, float y, D3DCOLOR color, DWORD dwAlphaOption )
{
	InitCheck();

	int nDrawPosX = x;
	int nDrawPosY = y;
	int nWidthEx = m_nOneCharWidth * fScaleX + nCharSpace;		//	一文字一文字の間隔
	int nHeightEx = m_nOneCharHeight * fScaleY + nLineSpace;	//	一文字一文字の間隔

	//	絵画する文字列を一つ一つ見ていくループ
	for( const char* pDrawChar=szDrawString; *pDrawChar != '\0'; pDrawChar++ )
	{
		//	改行だったら
		if ( *pDrawChar == '\n' )
		{
			nDrawPosY += nHeightEx;
			nDrawPosX = x;
			continue;
		}

		int nBitmapLineNo = 0;
		int nBitmapXCount = 0;

		//	ビットマップの文字列を一つ一つ見ていくループ
		for( const char* pBitmapChar=m_stringSequence.c_str(); *pBitmapChar != '\0'; pBitmapChar++ )
		{
			//	改行だったら一行進める
			if ( *pBitmapChar == '\n' )
			{
				nBitmapLineNo++;
				nBitmapXCount = 0;
				continue;
			}

			//	一致したら絵画
			if ( *pBitmapChar == *pDrawChar )
			{
				RECT rect;
				int nBitmapX = nBitmapXCount * m_nOneCharWidth;
				int nBitmapY = nBitmapLineNo * m_nOneCharHeight;
				_Rect2( nBitmapX, nBitmapY, m_nOneCharWidth, m_nOneCharHeight, &rect );

				//	絵画
				//sfcBitmapFont.DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, nDrawPosX, nDrawPosY, &rect, color );
				sfcBitmapFont.Draw( nDrawPosX, nDrawPosY, &rect, color, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle );
				break;
			}

			nBitmapXCount++;
		}

		nDrawPosX += nWidthEx;
	}
}

