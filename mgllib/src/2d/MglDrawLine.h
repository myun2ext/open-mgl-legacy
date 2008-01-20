//////////////////////////////////////////////////////////
//
//	MglDrawLine - 線絵画クラス
//
//////////////////////////////////////////////////////////

#ifndef __MglDrawLine_H__
#define __MglDrawLine_H__

#include "MglGraphicManager.h"
//#include "MglTexture.h"

//	クラス宣言
class DLL_EXP CMglDrawLine
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	IDirect3DDevice8* m_d3d;			//	D3DDeviceへのポインタ

	//static CMglTexture* m_pLineTex;

	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	//	コンストラクタ・デストラクタ
	CMglDrawLine();
	virtual ~CMglDrawLine(){}

	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd );

	void Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR color=D3DCOLOR_WHITE, float width=1.0f){
		Draw( fStartX,fStartY,fEndX,fEndY, color,color,width ); }
	//void Draw(float x, float y, D3DCOLOR startColor=D3DCOLOR_WHITE, D3DCOLOR endColor=D3DCOLOR_BLACK, float width=1.0f);
	void Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width=1.0f);
	void Draw2(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width=1.0f);

	//CMglTexture* GetInternalTexture(){ return m_pLineTex; }
};

#endif//__MglDrawLine_H__
