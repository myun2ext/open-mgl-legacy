#include "stdafx.h"
#include "MglVertexManager.h"

//	�}�N����
//#define CMglVertexManagerXT_CPP(_RETTYPE)	template <typename _VERTEX> _RETTYPE CMglVertexManagerXT<_VERTEX>

//template class DLL_EXP CMglVertexManagerXT<_VERTEX>;

/*template class DLL_EXP CMglVertexManagerT<>;
template class DLL_EXP CMglVertexManagerXT<>;*/

//	�e�N�X�`���̐ݒ�
void _CMglVertexManagerXT_Realize::SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage)
{
	InitCheck();
	//	�e�N�X�`���̐ݒ�
	MyuAssert( d3d->SetTexture(nStage, pTexture), D3D_OK,
		"CMglVertexManagerXT::SetD3dStageTexture()  d3d->SetTexture()�Ɏ��s" );
}

//	���_�o�b�t�@�����ɕϊ�����
void _CMglVertexManagerXT_Realize::CompileToFastMem(D3DPOOL pool, DWORD dwUsage)
{
	InitCheck();
	/*
	//	�O�̂��c���Ă�ƃA���Ȃ̂�Release -> �����̎g���̂ŗv��Ȃ��񂾂�!?
	SAFE_RELEASE(m_pVB);
	*/
	UINT nSize = _GetVertexCount()*m_nVertexSizeof;

	//	2009/01/18 �O�̂��c���Ă��炻�̂܂ܗ��p����񂾂킳�B
	if ( m_pVB == NULL ){
		//	���_�o�b�t�@�̍쐬
#if _MGL_DXVER == 8
		MyuAssert( d3d->CreateVertexBuffer( nSize, dwUsage, m_dwFVF, pool, &m_pVB), D3D_OK,
#else
		MyuAssert( d3d->CreateVertexBuffer( nSize, dwUsage, m_dwFVF, pool, &m_pVB, NULL/* Reserved in DX9 */), D3D_OK,
#endif
			"CMglVertexManagerXT::CompileToFastMem()  d3d->CreateVertexBuffer()�Ɏ��s" );
	}

	//	���b�N
	/*
#if _MGL_DXVER == 8
	BYTE* pLocked;
#elif _MGL_DXVER == 9
	void* pLocked;
#endif*/
	MGL_LOCKED_VERTEX_BUFFER_t* pLocked;

	MyuAssert( m_pVB->Lock( 0, nSize, &pLocked, 0), D3D_OK,
		"CMglVertexManagerXT::CompileToFastMem()  m_pVB->Lock()�Ɏ��s" );

	//	�R�s�[
    memcpy( pLocked, _GetVertexPtr(), nSize );

	//	�A�����b�N
    MyuAssert( m_pVB->Unlock(), D3D_OK,
		"CMglVertexManagerXT::CompileToFastMem()  m_pVB->Unlock()�Ɏ��s" );
}

//	�`��
void _CMglVertexManagerXT_Realize::Draw( D3DPRIMITIVETYPE primitiveType )
{
	InitCheck();
	if ( m_pVB == NULL )
	{
		//MyuThrow(456198, "CMglVertexManagerXT::Draw()  ���̃��\�b�h�����s����O��Compile()���\�b�h���Ăяo���Ă��������B");
		/*
		//	���_�o�b�t�@���g��Ȃ�����
		MyuAssert( d3d->DrawPrimitiveUP(
			primitiveType, _GetVertexCount(), _GetVertexPtr(), m_nVertexSizeof ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->DrawPrimitiveUP()�Ɏ��s" );
		*/

		CompileToFastMem();
	}
	else
	{
		//	���_�o�b�t�@���g������

		//	TODO: CompileToFastMem()���Ȃ��ƑʖڂȋC������ipool, dwUsage�o���Ƃ��Ȃ��ƂˁE�E�E�j

		//	�ݒ肷��ł�
#if _MGL_DXVER == 8
		MyuAssert( d3d->SetStreamSource( 0, m_pVB, m_nVertexSizeof ), D3D_OK,
#else
		MyuAssert( d3d->SetStreamSource( 0, m_pVB, 0/* offset support in D3DDEVCAPS2 only*/, m_nVertexSizeof ), D3D_OK,
#endif
			"CMglVertexManagerXT::Draw()  d3d->SetStreamSource()�Ɏ��s" );
		/*MyuAssert( d3d->SetVertexShader( m_dwFVF ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->SetVertexShader()�Ɏ��s" );*/
		m_myudg->SetFVF( m_dwFVF );

		//	�v���~�e�B�u���̓v���~�e�B�u��ʂɂ��قȂ�E�E�E
		int nPrimitiveCount = -1;
		switch(primitiveType)
		{
		case D3DPT_POINTLIST:
			nPrimitiveCount = _GetVertexCount();
			break;
		case D3DPT_LINELIST:
			nPrimitiveCount = _GetVertexCount()/2;
			break;
		case D3DPT_LINESTRIP:
			nPrimitiveCount = _GetVertexCount()-1;
			break;
		case D3DPT_TRIANGLELIST:
			nPrimitiveCount = _GetVertexCount()/3;
			break;
		case D3DPT_TRIANGLESTRIP:
		case D3DPT_TRIANGLEFAN:
			nPrimitiveCount = _GetVertexCount()/2;
			break;
		}

		//MyuAssert( d3d->DrawPrimitive( primitiveType, 0, _GetVertexCount()-2 ), D3D_OK,
		MyuAssert( d3d->DrawPrimitive( primitiveType, 0, nPrimitiveCount ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->DrawPrimitive()�Ɏ��s" );
	}
}

/*
//	�e�N�X�`���̐ݒ�
CMglVertexManagerXT_CPP(void)::SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage)
{
	//	�e�N�X�`���̐ݒ�
	MyuAssert( d3d->SetTexture(nStage, pTexture), D3D_OK,
		"CMglVertexManagerXT::SetD3dStageTexture()  d3d->SetTexture()�Ɏ��s" );
}

//	���_�o�b�t�@�����ɕϊ�����
CMglVertexManagerXT_CPP(void)::CompileToFastMem(D3DPOOL pool, DWORD dwUsage)
{
	/*
	//	�O�̂��c���Ă�ƃA���Ȃ̂�Release -> �����̎g���̂ŗv��Ȃ��񂾂�!?
	SAFE_RELEASE(m_pVB);
	*//*
	UINT nSize = m_vertexes.size()*sizeof(_VERTEX);

	//	2009/01/18 �O�̂��c���Ă��炻�̂܂ܗ��p����񂾂킳�B
	if ( m_pVB == NULL ){
		//	���_�o�b�t�@�̍쐬
		MyuAssert( d3d->CreateVertexBuffer( nSize, dwUsage, m_dwFVF, pool, &m_pVB), D3D_OK,
			"CMglVertexManagerXT::CompileToFastMem()  d3d->CreateVertexBuffer()�Ɏ��s" );
	}

	//	���b�N
    BYTE* pLocked;
	MyuAssert( m_pVB->Lock( 0, nSize, (BYTE**)&pLocked, 0), D3D_OK,
		"CMglVertexManagerXT::CompileToFastMem()  m_pVB->Lock()�Ɏ��s" );

	//	�R�s�[
    memcpy( pLocked, GetVertexPtr(), nSize );

	//	�A�����b�N
    MyuAssert( m_pVB->Unlock(), D3D_OK,
		"CMglVertexManagerXT::CompileToFastMem()  m_pVB->Unlock()�Ɏ��s" );
}

//	�`��
CMglVertexManagerXT_CPP(void)::Draw( D3DPRIMITIVETYPE primitiveType )
{
	if ( m_pVP == NULL )
	{
		//	���_�o�b�t�@���g��Ȃ�����
		MyuAssert( d3d->DrawPrimitiveUP(
			primitiveType, m_vertexes.size(), GetVertexPtr(), sizeof(_VERTEX) ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->DrawPrimitiveUP()�Ɏ��s" );
	}
	else
	{
		//	���_�o�b�t�@���g������

		//	TODO: CompileToFastMem()���Ȃ��ƑʖڂȋC������ipool, dwUsage�o���Ƃ��Ȃ��ƂˁE�E�E�j

		//	�ݒ肷��ł�
		MyuAssert( d3d->SetStreamSource( 0, m_pVB, sizeof(_VERTEX) ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->SetStreamSource()�Ɏ��s" );
		MyuAssert( d3d->SetVertexShader( m_dwFVF ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->SetVertexShader()�Ɏ��s" );

		MyuAssert( d3d->DrawPrimitive( primitiveType, 0, m_vertexes.size() ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->DrawPrimitive()�Ɏ��s" );
	}
}
*/

////////////////////////////////////////////////
//
//	�R���p�C���e�X�g

CMglVertexManager g__CMglVertexManager_test;
CMglVertexManagerXT<> g__CMglVertexManagerX_test;
