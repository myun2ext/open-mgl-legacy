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

//	���_�o�b�t�@�����ɕϊ�����
CMglVertexManagerXT_CPP(void)::CompileToFastMem()
{
	/*
	hr = d3d->CreateVertexBuffer( m_vertexes.size()*sizeof(_VERTEX),0,
					D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB);
    if(FAILED(hr)) return E_FAIL;

    VOID* pVertices;
	hr = pVB->Lock( 0, sizeof(vertices), (BYTE**)&pVertices, 0);
    if(FAILED(hr)) return E_FAIL;
    memcpy( pVertices, vertices, sizeof(vertices) );
    pVB->Unlock();

	lpD3DDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	*/
}


////////////////////////////////////////////////
//
//	�R���p�C���e�X�g

CMglVertexManager g__CMglVertexManager_test;
CMglVertexManagerXT<> g__CMglVertexManagerX_test;
