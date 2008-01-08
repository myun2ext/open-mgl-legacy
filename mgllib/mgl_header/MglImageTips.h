//////////////////////////////////////////////////////////
//
//	MglImageTips

#ifndef __MglImageTips_H__
#define __MglImageTips_H__

#include "MglGraphicManager.h"
//#include "MglTexture.h"
#include "MglImage.h"

//	クラス宣言
class DLL_EXP CMglImageTips// : protected CMglTexture // 継承にしてるんだが良いんかなぁ・・・
{
protected:
	CMglImage m_image;	//	2007/03/21 継承やめてみた
	//	→ Cacher管理にした方がヨサゲかも
	map<string,RECT> m_rectTable;

public:
	//	コンストラクタ・デストラクタ
	CMglImageTips(){}
	virtual ~CMglImageTips(){}

	//	読み込み
	void Load( const char* szFileName );
	//void Load( LPCSTR szImageFile, LPCSTR szTableFile, D3DCOLOR colorKey=DEF_COLORKEY );
	//void Load( LPCSTR szImageFile, map<string,RECT> &rectTable, D3DCOLOR colorKey=DEF_COLORKEY );
	//void Load( LPCSTR szImageFile, map<string,string> &rectTable, D3DCOLOR colorKey=DEF_COLORKEY );

	//	描画（※fSacle未サポート）<- してるんでない…？（2007/02/12）
	void Draw( const char* szRectName, float x, float y, float fScaleX=1.0f, float fScaleY=1.0f, D3DCOLOR color=D3DCOLOR_WHITE );
	int GetTipWidth( const char* szRectName );
	int GetTipHeight( const char* szRectName );
};

typedef CMglImageTips CMglBitmapTips;

#endif//__MglImageTips_H__
