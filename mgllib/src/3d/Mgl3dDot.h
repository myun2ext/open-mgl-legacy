//////////////////////////////////////////////////////////
//
//	Mgl3dDot - 線絵画クラス
//
//////////////////////////////////////////////////////////

#ifndef __Mgl3dDot_H__
#define __Mgl3dDot_H__

#include "MglGraphicManager.h"
//#include "MglTexture.h"

//	クラス宣言
class DLL_EXP CMgl3dDot
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	IDirect3DDevice8* m_d3d;			//	D3DDeviceへのポインタ

	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	//	コンストラクタ・デストラクタ
	CMgl3dDot();
	virtual ~CMgl3dDot(){}

	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd );
};

#endif//__Mgl3dDot_H__
