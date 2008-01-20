//////////////////////////////////////////////////////////
//
//	MglLayer
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglLayer.h"

//	�R���X�g���N�^
CMglLayer::CMglLayer()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	�f�X�g���N�^
CMglLayer::~CMglLayer()
{

}

///////////////////////////////////////////////////////

//	�o�^
void CMglLayer::Regist( CMglImage *pImage, int z, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	if ( m_list.find(z) != m_list.end() )
		MyuThrow( 66126, "CMglLayer::Regist() z=%d �͊��ɂ���܂��B", z );

	LAYERINFO t;
	ZeroMemory(&t,sizeof(t));

	/*
	t.bShow = bShow;
	t.color = color;
	t.x = x;
	t.y = y;
	t.fScaleX = fScaleX;
	t.fScaleY = fScaleY;
	t.fAngle = fAngle;
	*/
	t.pImage = pImage;

	m_list[z] = t;

	SetParam(z,x,y,bShow,color,fScaleX,fScaleY,fAngle);
}

//	�p�����[�^�ݒ�
void CMglLayer::SetParam( int z, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	ExistChk(z);

	m_list[z].bShow = bShow;
	m_list[z].color = color;
	m_list[z].x = x;
	m_list[z].y = y;
	m_list[z].fScaleX = fScaleX;
	m_list[z].fScaleY = fScaleY;
	m_list[z].fAngle = fAngle;

	m_list[z].fRotationCenterX = 0.5f;
	m_list[z].fRotationCenterY = 0.5f;
}

//	�ړ�
void CMglLayer::Move( int z, float x, float y )
{
	ExistChk(z);
	m_list[z].x += x;
	m_list[z].y += y;
}

//	�p�����[�^�ݒ�i�ʒu�j
void CMglLayer::SetPos( int z, float x, float y )
{
	ExistChk(z);
	m_list[z].x = x;
	m_list[z].y = y;
}

//	�p�����[�^�ݒ�i�F�j
void CMglLayer::SetColor( int z, D3DCOLOR color )
{
	ExistChk(z);
	m_list[z].color = color;
}

//	�p�����[�^�ݒ�i�k�ڗ��j
void CMglLayer::SetScale( int z, float fScaleX, float fScaleY )
{
	ExistChk(z);
	m_list[z].fScaleX = fScaleX;
	m_list[z].fScaleY = fScaleY;
}

//	�p�����[�^�ݒ�i�p�x�j
void CMglLayer::SetAngle( int z, float fAngle )
{
	ExistChk(z);
	m_list[z].fAngle = fAngle;
}

//	�p�����[�^�ݒ�i��`�j
void CMglLayer::SetRect( int z, RECT rect )
{
	ExistChk(z);
	m_list[z].rect = rect;
}

//	�p�����[�^�ݒ�i��]�̒��S�j
void CMglLayer::SetRotationCenter( int z, float fRotationCenterX, float fRotationCenterY )
{
	ExistChk(z);
	m_list[z].fRotationCenterX = fRotationCenterX;
	m_list[z].fRotationCenterY = fRotationCenterY;
}

////////////////////////////////////////////////////////////////

//	�`��
void CMglLayer::Rendering()
{
	InitCheck();

	//	���[�v
	for ( LIST_ITR it = m_list.begin(); it != m_list.end(); it++ )
	{
		LAYERINFO& t = it->second;
		CMglImage* pImage = t.pImage;

		if ( t.bShow == TRUE )
		{
			//pSfc->XDraw();
			//pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );

			RECT* pRect = &t.rect;
			if ( pRect->left == 0 && pRect->right == 0 && pRect->top == 0 && pRect->bottom == 0 )
				pRect = NULL;

			//	�`��
			pImage->Draw(t.x, t.y, pRect, t.color,
				t.fScaleX, t.fScaleY, t.fRotationCenterX, t.fRotationCenterY, t.fAngle );

			/*
			if ( pInfo->rect.left == pInfo->rect.right || pInfo->rect.top == pInfo->rect.bottom )
				pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );
			else
				pSfc->Draw( pInfo->rect.left, pInfo->rect.top, &pInfo->rect, pInfo->color );
			*/
		}
	}

	m_myudg->UpdateScreen();
}

