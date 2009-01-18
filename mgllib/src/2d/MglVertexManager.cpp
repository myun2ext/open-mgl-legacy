#include "stdafx.h"
#include "MglVertexManager.h"

//	マクロ化
#define CMglVertexManagerXT_CPPCL(_RETTYPE) template <typename _VERTEX> _RETTYPE CMglVertexManagerXT<_VERTEX>

//	テクスチャの設定
CMglVertexManagerXT_CPPCL(void)::SetD3dStageTexture(DWORD nStage)
{
	//	テクスチャの設定
	MyuAssert( d3d->SetTexture(nStage, m_pTexture), D3D_OK,
		"CMglVertexManagerXT::SetD3dTexture()  d3d->SetTexture()に失敗" );
}

CMglVertexManager g__CMglVertexManager_test;
CMglVertexManagerXT<> g__CMglVertexManagerX_test;
