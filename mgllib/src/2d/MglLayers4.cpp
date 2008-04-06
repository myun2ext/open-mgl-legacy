//////////////////////////////////////////////////////////
//
//	MglLayers4
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglLayers4.h"

//	�R���X�g���N�^
CMglLayers4::CMglLayers4()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	�f�X�g���N�^
CMglLayers4::~CMglLayers4()
{

}

///////////////////////////////////////////////////////

//	�o�^
void CMglLayers4::Regist( layer_t *pLayer, LIST_ITR it, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	if ( m_list.find(it) != m_list.end() )
		MyuThrow( 66126, "CMglLayers4::Regist() it=%d �͊��ɂ���܂��B", it );

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
	t.pLayer = pLayer;

	m_list[it] = t;

	SetParam(it,x,y,bShow,color,fScaleX,fScaleY,fAngle);
}

//	�p�����[�^�ݒ�
void CMglLayers4::SetParam( LIST_ITR it, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	ExistChk(it);

	m_list[it].bShow = bShow;
	m_list[it].color = color;
	m_list[it].x = x;
	m_list[it].y = y;
	m_list[it].fScaleX = fScaleX;
	m_list[it].fScaleY = fScaleY;
	m_list[it].fAngle = fAngle;

	m_list[it].fRotationCenterX = 0.5f;
	m_list[it].fRotationCenterY = 0.5f;
}

//	�ړ�
void CMglLayers4::Move( LIST_ITR it, float x, float y )
{
	ExistChk(it);
	m_list[it].x += x;
	m_list[it].y += y;
}

//	�p�����[�^�ݒ�i�ʒu�j
void CMglLayers4::SetPos( LIST_ITR it, float x, float y )
{
	ExistChk(it);
	m_list[it].x = x;
	m_list[it].y = y;
}

//	�p�����[�^�ݒ�i�F�j
void CMglLayers4::SetColor( LIST_ITR it, D3DCOLOR color )
{
	ExistChk(it);
	m_list[it].color = color;
}

//	�p�����[�^�ݒ�i�k�ڗ��j
void CMglLayers4::SetScale( LIST_ITR it, float fScaleX, float fScaleY )
{
	ExistChk(it);
	m_list[it].fScaleX = fScaleX;
	m_list[it].fScaleY = fScaleY;
}

//	�p�����[�^�ݒ�i�p�x�j
void CMglLayers4::SetAngle( LIST_ITR it, float fAngle )
{
	ExistChk(it);
	m_list[it].fAngle = fAngle;
}

//	�p�����[�^�ݒ�i��`�j
void CMglLayers4::SetRect( LIST_ITR it, RECT rect )
{
	ExistChk(it);
	m_list[it].rect = rect;
}

//	�p�����[�^�ݒ�i��]�̒��S�j
void CMglLayers4::SetRotationCenter( LIST_ITR it, float fRotationCenterX, float fRotationCenterY )
{
	ExistChk(it);
	m_list[it].fRotationCenterX = fRotationCenterX;
	m_list[it].fRotationCenterY = fRotationCenterY;
}

////////////////////////////////////////////////////////////////

//	�`��
void CMglLayers4::Rendering()
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

		LAYERINFO& t = m_list.get(it.base());
		layer_t* pLayer = t.pLayer;

		if ( t.bShow == TRUE )
		{
			//pSfc->XDraw();
			//pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );

			RECT* pRect = &t.rect;
			if ( pRect->left == 0 && pRect->right == 0 && pRect->top == 0 && pRect->bottom == 0 )
				pRect = NULL;

			//	�`��
			pLayer->Draw(t.x, t.y, pRect, t.color,
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

