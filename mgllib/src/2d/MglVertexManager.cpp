#include "stdafx.h"
#include "MglVertexManager.h"

//	マクロ化
#define CMglVertexManagerXT_CPP(_RETTYPE) template <typename _VERTEX> _RETTYPE CMglVertexManagerXT<_VERTEX>


//	テクスチャの設定
CMglVertexManagerXT_CPP(void)::SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage)
{
	//	テクスチャの設定
	MyuAssert( d3d->SetTexture(nStage, pTexture), D3D_OK,
		"CMglVertexManagerXT::SetD3dStageTexture()  d3d->SetTexture()に失敗" );
}

//	描画
CMglVertexManagerXT_CPP(void)::Draw( D3DPRIMITIVETYPE primitiveType )
{
	MyuAssert( d3d->DrawPrimitiveUP(
		primitiveType, m_vertexes.size(), &m_vertexes[0], sizeof(_VERTEX) ), D3D_OK,
		"CMglVertexManagerXT::Draw()  DrawPrimitiveUP()に失敗" );
}


////////////////////////////////////////////////
//
//	コンパイルテスト

CMglVertexManager g__CMglVertexManager_test;
CMglVertexManagerXT<> g__CMglVertexManagerX_test;
