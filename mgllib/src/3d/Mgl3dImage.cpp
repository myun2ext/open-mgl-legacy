#include "stdafx.h"
#include "Mgl3dImage.h"

#define PI (3.1415926535f)

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


void CMgl3dImage::Draw()
{
 	static int i=0;
	i++;

    D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	float time = (float)timeGetTime();
	//i = time/300;
	//TODO: D3DXMatrixRotationY(&mRotY, time/600.0f);
	//D3DXMatrixRotationY(&mRotY, 600.0f);
	D3DXMatrixRotationY(&mRotY, 10.0f+i);
//	D3DXMatrixRotationX(&mRotX, time/300.0f);
	D3DXMatrixRotationX(&mRotX, 10.0f+i);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	mWorld = mRotX * mRotY * mTrans;
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView
					,&D3DXVECTOR3(0-(i/100.0f),2.0f,2.0f-(i/100.0f))	// �J�����ʒu
					,&D3DXVECTOR3(0+(i/1000.0f),0,0)		// �J�����̒��ړ_
					,&D3DXVECTOR3(0,1,0)		// ��̌���
					);
	D3DXMatrixPerspectiveFovLH(&mProj
		,60.0f*PI/180.0f						// ����p
		,1.0f									// �A�X�y�N�g��
		,0.01f									// �ŋߐڋ���
		,100.0f									// �ŉ�������
		);
	d3d->SetTransform(D3DTS_WORLD, &mWorld);
	d3d->SetTransform(D3DTS_VIEW,  &mView);
	d3d->SetTransform(D3DTS_PROJECTION, &mProj);

	//lpD3DDEV->SetStreamSource( 0, pVB, sizeof(CUSTOMVERTEX) );
    d3d->SetVertexShader( FVF_MYU_VERTEX );
    //lpD3DDEV->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 3 );
	Draw();
}


