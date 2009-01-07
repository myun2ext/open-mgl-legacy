///////////////////////////////////////////////////////////////////////
//
//	Mgl3DManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __Mgl3DManager_H__
#define __Mgl3DManager_H__

#include "MglGraphicManager.h"

class DLL_EXP CMgl3DManager
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	_MGL_IDirect3DDevice* d3d;	//	D3Dデバイス

public:

	//////////////////////////
	//
	//		公開メソッド
	//

	//	コンストラクタ/デストラクタ
	CMgl3DManager();
	virtual ~CMgl3DManager();

	//	初期化/開放
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd );
	void Release();

};

#endif//__Mgl3DManager_H__
