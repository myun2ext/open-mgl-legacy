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
	SAFE_DELETE(m_pHitTestMap);
}

///////////////////////////////////////////////////////

//	�o�^
CMglLayers4::LIST_ITR CMglLayers4::Regist( layer_t *pLayer, LIST_ITR it, bool isShouldDeleteLayer, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	LAYERINFO t;
	ZeroMemory(&t,sizeof(t));
	t.pLayer = pLayer;
	t.isShuoldDeleteLayerPtr = isShouldDeleteLayer;
	LIST_ITR newIt = m_list.insert(it,t);

	SetParam(newIt,x,y,bShow,color,fScaleX,fScaleY,fAngle);

	return newIt;
}

//	�p�����[�^�ݒ�
void CMglLayers4::SetParam( LIST_ITR it, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	ExistChk(it);

	it->bShow = bShow;
	it->color = color;
	it->x = x;
	it->y = y;
	it->fScaleX = fScaleX;
	it->fScaleY = fScaleY;
	it->fAngle = fAngle;

	it->fRotationCenterX = 0.5f;
	it->fRotationCenterY = 0.5f;
}

//	�ړ�
void CMglLayers4::Move( LIST_ITR it, float x, float y )
{
	ExistChk(it);
	it->x += x;
	it->y += y;
}

//	�p�����[�^�ݒ�i�ʒu�j
void CMglLayers4::SetPos( LIST_ITR it, float x, float y )
{
	ExistChk(it);
	it->x = x;
	it->y = y;
}

//	�p�����[�^�ݒ�i�F�j
void CMglLayers4::SetColor( LIST_ITR it, D3DCOLOR color )
{
	ExistChk(it);
	it->color = color;
}

//	�p�����[�^�ݒ�i�k�ڗ��j
void CMglLayers4::SetScale( LIST_ITR it, float fScaleX, float fScaleY )
{
	ExistChk(it);
	it->fScaleX = fScaleX;
	it->fScaleY = fScaleY;
}

//	�p�����[�^�ݒ�i�p�x�j
void CMglLayers4::SetAngle( LIST_ITR it, float fAngle )
{
	ExistChk(it);
	it->fAngle = fAngle;
}

//	�p�����[�^�ݒ�i��`�j
void CMglLayers4::SetRect( LIST_ITR it, RECT rect )
{
	ExistChk(it);
	it->rect = rect;
}

//	�p�����[�^�ݒ�i��]�̒��S�j
void CMglLayers4::SetRotationCenter( LIST_ITR it, float fRotationCenterX, float fRotationCenterY )
{
	ExistChk(it);
	it->fRotationCenterX = fRotationCenterX;
	it->fRotationCenterY = fRotationCenterY;
}

//	�p�����[�^�ݒ�i���[�U�l�j
void CMglLayers4::SetUserParam( LIST_ITR it, DWORD dwUser )
{
	ExistChk(it);
	it->dwUser = dwUser;
}
DWORD CMglLayers4::GetUserParam( LIST_ITR it )
{
	ExistChk(it);
	return it->dwUser;
}

////////////////////////////////////////////////////////////////

//	�`��
void CMglLayers4::Rendering()
{
	InitCheck();

	//	2008/02/17  �\���̏��ԋt���Ǝv���E�E�E�i��끁��Ԑ[�����̂���`�悵�Ă����ׂ��j
	//	���[�v
	for ( LIST_ITR it = m_list.begin(); it != m_list.end(); it++ )
	//for( LIST_RITR it = m_list.rbegin(); it != m_list.rend(); it++ )
	{
		LAYERINFO& t = *it;
		layer_t* pLayer = t.pLayer;

		if ( pLayer == (void*)0xcdcdcdcd )
			MyuThrow(999,"pLayer is 0xcdcdcdcd.");

		if ( t.bShow == TRUE )
		{
			//	2008/06/29  ����Ƃ���ł��g���̂Ŋ֐���
			LayerSingleDraw(t);

			pLayer->SendMessage(MGL_LAYER_CMSGCODE_ON_FRAME);

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

//	���C���[�P�̂̕`��
void CMglLayers4::LayerSingleDraw(LAYERINFO& t)
{
	layer_t* pLayer = t.pLayer;

	//pSfc->XDraw();
	//pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );

	RECT* pRect = &t.rect;
	if ( pRect->left == 0 && pRect->right == 0 && pRect->top == 0 && pRect->bottom == 0 )
		pRect = NULL;

	//	�`��
	pLayer->Draw(t.x, t.y, pRect, t.color,
		t.fScaleX, t.fScaleY, t.fRotationCenterX, t.fRotationCenterY, t.fAngle );
}

//	�폜����
void CMglLayers4::Delete(LIST_ITR it)
{
	//LAYERINFO& t = m_list.get(it);
	LAYERINFO& t = *it;
	layer_t* pLayer = t.pLayer;

	//	2008/05/16  ���C���[��Release()�Ăяo��
	pLayer->Release();

	//	�|�C���^���J�����ׂ��ł���ΊJ������
	//if ( pLayer->IsShouldRelease() )
	if ( t.isShuoldDeleteLayerPtr )
		delete pLayer;

	//	���X�g���珜��
	m_list.erase(it);
}

//	�S�Ă��폜
void CMglLayers4::Clear()
{
	InitCheck();

	//	���X�g�����[�v���Ĉ�ÂJ��
	//for( LIST_ITR it=m_list.begin(); it!=m_list.end(); it++ )
	for(;;){
		LIST_ITR it = m_list.begin();
		if ( it == m_list.end() )
			break;
		Delete(it);
	}

	//	�ꉞ���s���Ă��������H
	m_list.clear();
}

//	HitTest
//	 : �w�肳�ꂽ�ʒu�̈�ԏ�̃��C���[���擾����
CMglLayers4::LIST_ITR CMglLayers4::HitTest(int x, int y)
{
	//	���[�v
	//for ( LIST_ITR it = m_list.begin(); it != m_list.end(); it++ )
	for( LIST_RITR it = m_list.rbegin(); it != m_list.rend(); it++ )
	{
		LAYERINFO& t = *it;
		layer_t* pLayer = t.pLayer;

		if ( t.bShow == TRUE )
		{
			RECT rect = pLayer->GetRect();
			rect.left += t.x;
			rect.right += t.x;
			rect.top += t.y;
			rect.bottom += t.y;

			if ( x >= rect.left && x <= rect.right &&
				 y >= rect.top  && y <= rect.bottom )
				return it.base();
		}
	}
	return m_list.end();
}


//	HitTest
//	 : �w�肳�ꂽ�ʒu�̈�ԏ�̃��C���[���擾����
CMglLayers4::LIST_ITR CMglLayers4::HitTest2(int x, int y)
{
	if ( m_pHitTestMap == NULL )
		m_pHitTestMap = new CMglLayers4HitTest(m_myudg);

	//	���[�v
	//for ( LIST_ITR it = m_list.begin(); it != m_list.end(); it++ )
	for( LIST_RITR it = m_list.rbegin(); it != m_list.rend(); it++ )
	{
		LAYERINFO& t = *it;
		layer_t* pLayer = t.pLayer;

		if ( t.bShow == TRUE )
		{
			RECT rect = pLayer->GetRect();
			rect.left += t.x;
			rect.right += t.x;
			rect.top += t.y;
			rect.bottom += t.y;

			if ( x >= rect.left && x <= rect.right &&
				 y >= rect.top  && y <= rect.bottom )
				return it.base();
		}
	}
	return m_list.end();
}

//	HitTest - 2008/06/29
//	 : �w�肳�ꂽ�ʒu�̈�ԏ�̃��C���[���擾����
CMglLayers4::LIST_ITR CMglLayers4::HitTest3(int x, int y)
{
	CMglStackInstance("CMglLayers4::HitTest3");

	if ( m_pHitTestMap == NULL )
		m_pHitTestMap = new CMglLayers4HitTest(m_myudg);

	//	���[�v
	//for ( LIST_ITR it = m_list.begin(); it != m_list.end(); it++ )
	for( LIST_RITR it = m_list.rbegin(); it != m_list.rend(); it++ )
	{
		LAYERINFO& t = *it;
		//layer_t* pLayer = t.pLayer;

		if ( t.bShow == TRUE )
		{
			CMglImage imgRender;
			CMglImage imgCopied;
			imgRender.Create(m_myudg, TRUE);
			imgCopied.Create(m_myudg);

			imgRender.SetRender();			//	�����_�����O��ύX
			LayerSingleDraw(t);				//	�`��
			m_myudg->SetRenderBackBuffer();	//	�����_�����O�挳�ɖ߂�

			//	���҂�
			imgCopied.CopyRectToThis(&imgRender);

			imgRender.Draw();
			m_myudg->UpdateScreen();

			/*	�C�`�C�`�`�F�b�N���Ă�����̂�߂�
			BOOL bCheck=FALSE;
			D3DCOLOR color = imgTest.GetIternalBitmapData()->GetNE(x,y, &bCheck);
			if ( bCheck == FALSE )
			*/
			if ( D3DCOLOR_GETA(imgCopied.GetIternalBitmapData()->Get(x,y)) != 0 ){
				/*//	�����_�����O������ɖ߂�
				m_myudg->SetRenderBackBuffer();*/

				return (--it.base());	//	2008/06/30  --���Ă�������肭�������c�B
			}
		}
	}

	//	�����_�����O������ɖ߂�
	m_myudg->SetRenderBackBuffer();
	return m_list.end();
}