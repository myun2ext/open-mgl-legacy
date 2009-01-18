#ifndef __MglVertexManager_H__
#define __MglVertexManager_H__

#include "MglGraphicManager.h"

//	クラス宣言
template <typename _VERTEX = MYUX_VERTEX>
class CMglVertexManagerManagerXT : public CMglVertexManagerManagerT<_VERTEX>
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	_MGL_IDirect3DDevice* d3d;		//	D3DDeviceへのポインタ

public:
	//	コンストラクタ・デストラクタ
	CMglVertexManagerManagerXT(){
		m_myudg = NULL;
		d3d = NULL;
	}
	virtual ~CMglVertexManagerManagerXT(){ Release(); }

	//	初期化と開放
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd ){
		m_myudg = in_myudg;
		d3d = m_myudg->GetD3dDevPtr();
	}
	void Release(){

	}

};

#endif//__MglVertexManager_H__
