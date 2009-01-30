//////////////////////////////////////////////////////////
//
//	MglTexture2 - テクスチャ管理クラス
//
//	なお、CreateTextureFromFile() で作成されたテクスチャは
//	三角形を二枚組み合わせた四角形であるのでこの事に注意されたし！

#ifndef __MglTexture2_H__
#define __MglTexture2_H__

#include "MglD3dTexture.h"
#include "MglVertexManager.h"


//	クラス宣言
class DLL_EXP CMglTexture2// : public CMyuReleaseBase
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納

	//	Direct3D系
	_MGL_IDirect3DDevice* d3d;			//	D3DDeviceへのポインタ

	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	//	コンストラクタ・デストラクタ
	CMglTexture2();
	virtual ~CMglTexture2(){ Release(); }

	//	初期化と開放
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	void Release();

};

#endif//__MglTexture2_H__
