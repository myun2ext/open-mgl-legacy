//////////////////////////////////////////////////////////
//
//	MglDxSurface - DirectXのサーフェス管理クラス
//

#ifndef __MglDxSurface_H__
#define __MglDxSurface_H__

#include "MglGraphicManager.h"

//	エクスポート
DLL_TMPL_EXP CMglDgIBase< _MGL_IDirect3DSurface >;

//	クラス宣言
class DLL_EXP CMglDxSurface : public CMglDgIBase< _MGL_IDirect3DSurface >
{
protected:
	//CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納

	//	Direct3D系
	//_MGL_IDirect3DDevice* d3d;			//	D3DDeviceへのポインタ
	//_MGL_IDirect3DSurface* m_pSurface;	//	サーフェス

	void CreateCheck() {
		InitCheck();	//	2008/06/28 これもやらないと駄目でない・・・？
		//if ( createFlg == FALSE ){
		if ( m_pI == NULL )
			MyuThrow( 0, "CMglDxSurface 未作成であるにも関わらず操作を行おうとしました。Create()系メソッドを呼んでください。" );
	}

public:
	//	コンストラクタ・デストラクタ
	CMglDxSurface();
	virtual ~CMglDxSurface();

	//	初期化と開放
	
	void SetSurface( _MGL_IDirect3DSurface *pSurface ){
		m_pI = pSurface;
		m_pI->AddRef();
	}
	
	////////////////////////////////////////////////////////////////////////////
};


#endif//__MglDxSurface_H__
