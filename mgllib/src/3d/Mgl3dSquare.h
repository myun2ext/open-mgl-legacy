//////////////////////////////////////////////////////////
//
//	Mgl3dSquare - 線絵画クラス
//
//////////////////////////////////////////////////////////

#ifndef __Mgl3dSquare_H__
#define __Mgl3dSquare_H__

#include "MglGraphicManager.h"
#include "MglVertexManager.h"
//#include "MglTexture.h"

#pragma warning( disable : 4660 ) 

//	クラス宣言
class DLL_EXP CMgl3dSquare : public CMglVertexManagerX
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
	CMgl3dSquare();
	virtual ~CMgl3dSquare(){}

	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
};

#endif//__Mgl3dSquare_H__
