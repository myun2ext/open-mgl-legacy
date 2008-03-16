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
void CMglLayer::Regist( CMglImage *pImage, int depth, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	if ( m_list.find(depth) != m_list.end() )
		MyuThrow( 66126, "CMglLayer::Regist() depth=%d �͊��ɂ���܂��B", depth );

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

	m_list[depth] = t;

	SetParam(depth,x,y,bShow,color,fScaleX,fScaleY,fAngle);
}

//	�p�����[�^�ݒ�
void CMglLayer::SetParam( int depth, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	ExistChk(depth);

	m_list[depth].bShow = bShow;
	m_list[depth].color = color;
	m_list[depth].x = x;
	m_list[depth].y = y;
	m_list[depth].fScaleX = fScaleX;
	m_list[depth].fScaleY = fScaleY;
	m_list[depth].fAngle = fAngle;

	m_list[depth].fRotationCenterX = 0.5f;
	m_list[depth].fRotationCenterY = 0.5f;
}

//	�ړ�
void CMglLayer::Move( int depth, float x, float y )
{
	ExistChk(depth);
	m_list[depth].x += x;
	m_list[depth].y += y;
}

//	�p�����[�^�ݒ�i�ʒu�j
void CMglLayer::SetPos( int depth, float x, float y )
{
	ExistChk(depth);
	m_list[depth].x = x;
	m_list[depth].y = y;
}

//	�p�����[�^�ݒ�i�F�j
void CMglLayer::SetColor( int depth, D3DCOLOR color )
{
	ExistChk(depth);
	m_list[depth].color = color;
}

//	�p�����[�^�ݒ�i�k�ڗ��j
void CMglLayer::SetScale( int depth, float fScaleX, float fScaleY )
{
	ExistChk(depth);
	m_list[depth].fScaleX = fScaleX;
	m_list[depth].fScaleY = fScaleY;
}

//	�p�����[�^�ݒ�i�p�x�j
void CMglLayer::SetAngle( int depth, float fAngle )
{
	ExistChk(depth);
	m_list[depth].fAngle = fAngle;
}

//	�p�����[�^�ݒ�i��`�j
void CMglLayer::SetRect( int depth, RECT rect )
{
	ExistChk(depth);
	m_list[depth].rect = rect;
}

//	�p�����[�^�ݒ�i��]�̒��S�j
void CMglLayer::SetRotationCenter( int depth, float fRotationCenterX, float fRotationCenterY )
{
	ExistChk(depth);
	m_list[depth].fRotationCenterX = fRotationCenterX;
	m_list[depth].fRotationCenterY = fRotationCenterY;
}

////////////////////////////////////////////////////////////////

//	�`��
void CMglLayer::Rendering()
{
	InitCheck();

	//	2008/02/17  �\���̏��ԋt���Ǝv���E�E�E�i��끁��Ԑ[�����̂���`�悵�Ă����ׂ��j
	//	���[�v
	//for ( LIST_ITR it = m_list.begin(); it != m_list.end(); it++ )
	/*LIST_ITR it = m_list.end();
	for(;;)*/
	for( LIST_RITR it = m_list.rbegin(); it != m_list.rend(); it++ )
	{
		//it--;

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

		/*if ( it == m_list.begin() )
			break;*/
	}

	m_myudg->UpdateScreen();
}

