#include "stdafx.h"
#include "MglMesh.h"

//	BMP�̒��_���擾
void CMglMesh::GetBmpVertexs3D( MGL_SQUARE_VERTEXS *pMglSqVertexs, float fScaleX, float fScaleY )
{
	//GetBmpVertexs(pMglSqVertexs);

	int nBmpSrcX = m_imgInfo.Width;
	int nBmpSrcY = m_imgInfo.Height;

	int nBmpMax;
	if ( m_imgInfo.Width > m_imgInfo.Height )
		nBmpMax = m_imgInfo.Width;
	else
		nBmpMax = m_imgInfo.Height;

	float fBmpSrcX = (m_imgInfo.Width*1.0f) / nBmpMax * fScaleX;
	float fBmpSrcY = (m_imgInfo.Height*1.0f) / nBmpMax * fScaleY;

	//	2007/01/10  �X�P�[���擾
	//	# �e�N�X�`���̈��2�̔{���ɂȂ�B���̓���0.?f��BMP�̗̈悩���Z�o����
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	const float fBmpScaleX = (float)nBmpSrcX / (float)texDesc.Width;
	const float fBmpScaleY = (float)nBmpSrcY / (float)texDesc.Height;

	//	���_��񐶐�
	MglVertexGen( &pMglSqVertexs->lt, 0,        0,			0, 0.0f, 0.0f );
	MglVertexGen( &pMglSqVertexs->rt, fBmpSrcX, 0,			0, fBmpScaleX, 0.0f );
	MglVertexGen( &pMglSqVertexs->lb, 0,        fBmpSrcY,	0, 0.0f, fBmpScaleY );
	MglVertexGen( &pMglSqVertexs->rb, fBmpSrcX, fBmpSrcY,	0, fBmpScaleX, fBmpScaleY );

	//	���_�̃Y����
	//MglMoveVertexs( pMglSqVertexs, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ );
}

/*
//	BMP�̒��_���擾
void CMglMesh::SetupVertexes( float x, float y, float z, RECT* srcRect, float fTexScaleX, float fTexScaleY, D3DCOLOR color )
{
	//GetBmpVertexs(pMglSqVertexs);

	int nBmpSrcX = m_imgInfo.Width;
	int nBmpSrcY = m_imgInfo.Height;

	int nBmpMax;
	if ( m_imgInfo.Width > m_imgInfo.Height )
		nBmpMax = m_imgInfo.Width;
	else
		nBmpMax = m_imgInfo.Height;

	float fBmpSrcX = m_imgInfo.Width / nBmpMax * fScaleX;
	float fBmpSrcY = m_imgInfo.Height / nBmpMax * fScaleY;

	//	2007/01/10  �X�P�[���擾
	//	# �e�N�X�`���̈��2�̔{���ɂȂ�B���̓���0.?f��BMP�̗̈悩���Z�o����
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	const float fBmpScaleX = (float)nBmpSrcX / (float)texDesc.Width;
	const float fBmpScaleY = (float)nBmpSrcY / (float)texDesc.Height;

	//	���_��񐶐�
	MglVertexGen( &pMglSqVertexs->lt, 0+x,        0+y,			z, 0.0f, 0.0f, color );
	MglVertexGen( &pMglSqVertexs->rt, fBmpSrcX+x, 0+y,			z, fBmpScaleX, 0.0f, color );
	MglVertexGen( &pMglSqVertexs->lb, 0+x,        fBmpSrcY+y,	z, 0.0f, fBmpScaleY, color );
	MglVertexGen( &pMglSqVertexs->rb, fBmpSrcX+x, fBmpSrcY+y,	z, fBmpScaleX, fBmpScaleY, color );

	//	���_�̃Y����
	//MglMoveVertexs( pMglSqVertexs, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ );
}
*/

//	���_���̐ݒ�
void CMglMesh::SetupVertexes(float x, float y, float z, RECT* srcRect, float fTexScaleX, float fTexScaleY, D3DCOLOR color)
{
	GetBmpVertexs3D( &m_vertexs, fTexScaleX, fTexScaleY );
	MglMoveVertexs( &m_vertexs, x, y, z );
	MglVertexsFillColor( &m_vertexs, color );
}

//	�`��
void CMglMesh::Draw(float x, float y, float z, RECT* srcRect, float fTexScaleX, float fTexScaleY, D3DCOLOR color)
{
	SetupVertexes(x,y,z,srcRect,fTexScaleX,fTexScaleY,color);

	SetD3dStageTexture();
	m_myudg->SetupMyuVertex();
	
	// �}�g���b�N�X����
	//g_WorldFrame.rotate.y += 0.01f;			// �x�����ɉ�]
	//g_WorldFrame.SetMat();											// ���W�ϊ��p�}�g���b�N�X�쐬
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_WorldFrame.mat);	// ���[���h�}�g���b�N�X�Z�b�g

	// ���_�o�b�t�@���g�p�������ڃf�[�^��n���ĕ`�悷��
	m_myudg->DrawPrimitiveUpMyuVertexSquare( &m_vertexs );
}


