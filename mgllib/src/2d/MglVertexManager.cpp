#include "stdafx.h"
#include "MglVertexManager.h"

//	�}�N����
#define CMglVertexManagerXT_CPP(_RETTYPE) template <typename _VERTEX> _RETTYPE CMglVertexManagerXT<_VERTEX>


//	�e�N�X�`���̐ݒ�
CMglVertexManagerXT_CPP(void)::SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage)
{
	//	�e�N�X�`���̐ݒ�
	MyuAssert( d3d->SetTexture(nStage, pTexture), D3D_OK,
		"CMglVertexManagerXT::SetD3dStageTexture()  d3d->SetTexture()�Ɏ��s" );
}

//	�`��
CMglVertexManagerXT_CPP(void)::Draw( D3DPRIMITIVETYPE primitiveType )
{
	MyuAssert( d3d->DrawPrimitiveUP(
		primitiveType, m_vertexes.size(), &m_vertexes[0], sizeof(_VERTEX) ), D3D_OK,
		"CMglVertexManagerXT::Draw()  DrawPrimitiveUP()�Ɏ��s" );
}


////////////////////////////////////////////////
//
//	�R���p�C���e�X�g

CMglVertexManager g__CMglVertexManager_test;
CMglVertexManagerXT<> g__CMglVertexManagerX_test;
