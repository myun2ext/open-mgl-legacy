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

	float fBmpSrcX = m_imgInfo.Width / nBmpMax;
	float fBmpSrcY = m_imgInfo.Height / nBmpMax;

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
void CMgl3dImage::Draw()
{

}


