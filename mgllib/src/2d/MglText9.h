//////////////////////////////////////////////////////////
//
//	MglText  v0.10.01 04/01/30
//		- テキスト
//
//	v0.10.00 04/12/13
//	・新規作成
//
//	v0.10.01 04/01/30
//	・SetFont()をSetDrawParam()に名称変更
//
//////////////////////////////////////////////////////////

#ifndef __MglText_H__
#define __MglText_H__

#include "MglGraphicManager.h"
#include <stdarg.h>

#define MGL_TEXT_DEFAULT_FONT_SIZE	(12)
//#define FONT_NAME_MS_GOTHIC			"

#if _MGL_DXVER == 8

//	クラス宣言
class DLL_EXP CMglText : public CMyuReleaseBase
{
private:
	//	一応両方保持しとくげま
	CMglGraphicManager* m_myudg;			//	DGクラスへのポインタを格納
	_MGL_IDirect3DDevice* m_d3d;			//	D3DDeviceへのポインタ

	//	インターフェース
	ID3DXFont *m_text;

	//	作成されたか記憶するフラグ
	BOOL bCreateFlg;

	//	フォント設定
	BOOL bSetParamFlg;
	int m_nX;
	int m_nY;
	DWORD m_dwOption;
	D3DCOLOR m_color;

	void SetParamCheck() {
		if ( bSetParamFlg != TRUE )
			MyuThrow( 0, "CMglText::Draw(),fDraw()  SetDrawParam()が設定されていないのに引数を省略しました。" );
	}
	void _Init(){
		m_myudg = NULL;
		m_d3d = NULL;
		m_text = NULL;
		bCreateFlg = FALSE;
		bSetParamFlg = FALSE;
	}

public:
	CMglText(){
		_Init();
		if ( CheckDefaultGd() )
			Create();	//	デフォルトフォント
	}
	CMglText(CMglGraphicManager* in_myudg){
		_Init();
		InitAndCreate(in_myudg,MGL_TEXT_DEFAULT_FONT_SIZE);	//	デフォルトフォント
	}
	virtual ~CMglText();

	//	初期化及び作成
	void InitAndCreate( CMglGraphicManager* in_myudg, HFONT hFont );
	void InitAndCreate( CMglGraphicManager* in_myudg, int nHeight );
	void InitAndEzCreate( CMglGraphicManager* in_myudg, int nHeight ){ InitAndCreate(in_myudg, nHeight); }	//	古い

	//	in_myudg省略形。関数名違っても内容同じ
	void Create( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	void Create( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }
	void Init( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	void Init( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }
	void Setup( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	void Setup( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }

	//	一杯指定
	void Create( CMglGraphicManager* in_myudg, int nHeight, const char* szFontName,
		BOOL bItalic=FALSE, BOOL bBold=FALSE, BOOL bUnderLine=FALSE, BOOL bStrikeOut=FALSE, float fAngle=0.0f );
	void Create( int nHeight, const char* szFontName,
		BOOL bItalic=FALSE, BOOL bBold=FALSE, BOOL bUnderLine=FALSE, BOOL bStrikeOut=FALSE, float fAngle=0.0f )
	{	Create( GetDefaultGd(), nHeight, szFontName, bItalic, bBold, bUnderLine, bStrikeOut, fAngle); }

	//	全引数省略
	void Create(){ Init(MGL_TEXT_DEFAULT_FONT_SIZE); }
	void Init(){ Init(MGL_TEXT_DEFAULT_FONT_SIZE); }

	//	明示的開放
	void Release();

	//	絵画
	void Draw( const char* szString, int nX, int nY, D3DCOLOR color, DWORD dwOption=0 );
	void Draw( const char* szString, D3DCOLOR color ) {
		SetParamCheck();
		Draw( szString, m_nX, m_nY, color, m_dwOption );
	}
	void Draw( const char* szString, int nX, int nY ) {
		SetParamCheck();
		Draw( szString, nX, nY, m_color, m_dwOption );
	}
	void Draw( const char* szString ){ FDraw( szString ); }
	void FDraw( const char* szString, ... );
	void SetDrawParam( int in_nX, int in_nY, D3DCOLOR in_color, DWORD in_dwOption=0 );
};

#else


#endif

typedef CMglText CMglGraphicText;

#endif//__MglText_H__
