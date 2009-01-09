#include "stdafx.h"
#include "Mgl3dImage.h"

//	BMP�̒��_���擾
void CMgl3dImage::GetBmpVertexs3D( MGL_SQUARE_VERTEXS *pMglSqVertexs, float fScaleX, float fScaleY )
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
	MglVertexGen( &pMglSqVertexs->lt, 0,        0,			0.0f, 0.0f );
	MglVertexGen( &pMglSqVertexs->rt, fBmpSrcX, 0,			fBmpScaleX, 0.0f );
	MglVertexGen( &pMglSqVertexs->lb, 0,        fBmpSrcY,	0.0f, fBmpScaleY );
	MglVertexGen( &pMglSqVertexs->rb, fBmpSrcX, fBmpSrcY,	fBmpScaleX, fBmpScaleY );

	//	���_�̃Y����
	//MglMoveVertexs( pMglSqVertexs, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ );
}

//	�`��
void CMgl3dImage::Draw(float x, float y, float z, RECT* srcRect, float fScaleX, float fScaleY, D3DCOLOR color)
{
	//	���_�������擾
	MGL_SQUARE_VERTEXS vertexs;
	GetBmpVertexs3D( &vertexs, fScaleX, fScaleY );

	//	x, y�Ɉړ�
	MglMoveVertexs( &vertexs, x, y );

	//	���_�̐F
	vertexs.lt.color = color;
	vertexs.rt.color = color;
	vertexs.lb.color = color;
	vertexs.rb.color = color;
	
	/*
	vertexs.lt.x /= 100;
	vertexs.rt.x /= 100;
	vertexs.lb.x /= 100;
	vertexs.rb.x /= 100;
	vertexs.lt.y /= 100;
	vertexs.rt.y /= 100;
	vertexs.lb.y /= 100;
	vertexs.rb.y /= 100;
	*/

	/////////////////////////////////////////////////////

	//g_pD3DDevice->SetTexture(0, pTexture->GetDirect3dTexturePtr());	// �e�N�X�`�����Z�b�g
	SetD3dStageTexture();

	// �f�o�C�X�Ɏg�p���钸�_�t�H�[�}�b�g���Z�b�g����i���������A���W�ϊ��L��j
	d3d->SetVertexShader(FVF_MYU_VERTEX);
	
	// �}�g���b�N�X����
	//g_WorldFrame.rotate.y += 0.01f;			// �x�����ɉ�]
	//g_WorldFrame.SetMat();											// ���W�ϊ��p�}�g���b�N�X�쐬
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_WorldFrame.mat);	// ���[���h�}�g���b�N�X�Z�b�g

	// ���_�o�b�t�@���g�p�������ڃf�[�^��n���ĕ`�悷��
	d3d->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &vertexs, sizeof(MGL_VERTEX));
}


