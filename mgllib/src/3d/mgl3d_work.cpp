#include "stdafx.h"
#include "mgl3d.h"

#define PI (3.1415926535f)

void CMglImage3D::Draw3d()
{
 	static int i=0;
	i++;

    D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	float time = (float)timeGetTime();
	//TODO: D3DXMatrixRotationY(&mRotY, time/600.0f);
	//D3DXMatrixRotationY(&mRotY, 600.0f);
	D3DXMatrixRotationY(&mRotY, 0.0f);
//	D3DXMatrixRotationX(&mRotX, time/300.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
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
    //lpD3DDEV->SetVertexShader( D3DFVF_CUSTOMVERTEX );
    //lpD3DDEV->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 3 );
	Draw();
}


