//////////////////////////////////////////////////////////
//
//	MglLayers2
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglLayers2.h"


//	�R���X�g���N�^
CMglLayers2::CMglLayers2()
{
	p_layerInfos = new LAYERINFOS_MAP;
	p_indexs = new INDEXS_MAP;

	m_pPrevTargetSurface = NULL;
}

//	�f�X�g���N�^
CMglLayers2::~CMglLayers2()
{
	Release();

	SAFE_DELETE( p_layerInfos );
	SAFE_DELETE( p_indexs );
}

//	�J��
void CMglLayers2::Release()
{
	CMglImageManager::Release();
	DeleteAll();
}

//	�S�Ẵ��C���[���폜�i�����_�ł�Release()�Ɠ����j
void CMglLayers2::DeleteAll()
{
	p_layerInfos->clear();
	p_indexs->clear();

	CMglImageManager::DeleteAll();
}

//	������
void CMglLayers2::Init( CMglGraphicManager *in_m_myudg, const char* in_szDummyFile, D3DCOLOR colorKey )
{
	//	�����ϐ��փR�s�[
	strcpy( m_szDummyFile, in_szDummyFile );
	m_colorKey = colorKey;

	//	CMglImageManager��Init()���Ăяo��
	CMglImageManager::Init( in_m_myudg );

	//	�����_�����O�p�T�[�t�F�X�̏�����
	m_renderingSurface.Init( in_m_myudg );
	m_renderingSurface.Create();
}

//	���C���[�̒ǉ�
void CMglLayers2::Add( const char *szBufferName )
{
	CMglImage *pSurface = AddEntry( szBufferName );

	//	CreateFromFile()�͗ǂ��G���[���N�����̂�Exception������������
	try
	{
		pSurface->Create( m_szDummyFile, TRUE, m_colorKey );
		//pSurface->CreateFromFile( m_szDummyFile, TRUE, m_colorKey );
		//pSurface->CreateFromFile( m_szDummyFile, FALSE, m_colorKey );	//	�d���C�C�C_|�P|��

		//	�_�~�[�T�[�t�F�X�̃T�C�Y�`�F�b�N
		if ( pSurface->GetBmpWidth() != m_myudg->GetDispX() ||
			 pSurface->GetBmpHeight() != m_myudg->GetDispY() )
		{
			MyuThrow( 0, "�_�~�[�T�[�t�F�X�͉�ʂ̃T�C�Y�ƈ�v���Ă��Ȃ���΂����܂���B" );
		}

		pSurface->Clear();
	}
	catch( MyuCommonException except )
	{
		static MyuCommonException except2;
		sprintf( except2.szErrMsg, "CMglLayers2::Add(\"%s\")\r\n"
			"0x%08x %s", szBufferName, except.nErrCode, except.szErrMsg );
		throw except2;
	}
	catch( ... )
	{
		MyuThrow( 0, "CMglLayers2::Add()  Unknown Exception Error." );
	}
}

//	���C���[�̒ǉ��iPre�j
CMglImage* CMglLayers2::AddEntry( const char *szBufferName )
{
	//	indexs
	INDEXS_MAP &indexs = *p_indexs;
	LAYERINFOS_MAP &layerInfos = *p_layerInfos;
	indexs[layerInfos.size()] = szBufferName;

	//	layerInfos
	LAYERINFO layerInfo;
	ZeroMemory( &layerInfo, sizeof(LAYERINFO) );
	layerInfo.bShow = TRUE;
	layerInfo.color = 0xffffffff;
	layerInfos[szBufferName] = layerInfo;

	return CMglImageManager::Add( szBufferName );
}

//	���C���[���擾
CMglImage* CMglLayers2::GetRenderingSurface( const char *szLayerName )
{
	InitCheck();

	//	�O��̃����_�����O�𔽉f
	AdaptRenderingSurface();

	//	�^�[�Q�b�g�T�[�t�F�X���擾���A�R�s�[���Ă���
	CMglImageManager::Get( szLayerName )->CopyRectToOther(&m_renderingSurface);

	//	�^�[�Q�b�g�T�[�t�F�X��ێ�
	m_pPrevTargetSurface = CMglImageManager::Get( szLayerName );
	if ( m_pPrevTargetSurface == NULL )
		MyuThrow( 0, "CMglLayers2::GetRenderingSurface()  �Ȃ�NULL�d�ŗ��܂����i��" );

	//	�U�̃����_�����O�p�T�[�t�F�X�𕜋A
	return &m_renderingSurface;
}

//	�O��̃����_�����O�𔽉f
void CMglLayers2::AdaptRenderingSurface()
{
	//	m_pPrevTargetSurface��NULL������Ȃ̂őO��̃����_�����O�͖���
	if ( m_pPrevTargetSurface != NULL )
	{
		m_renderingSurface.CopyRectToOther(m_pPrevTargetSurface);

		//	������
		m_pPrevTargetSurface = NULL;
	}
}

//	ex��ݒ肷��ł�
void CMglLayers2::SetLayerOption( const char *szLayerName, RECT *rect, D3DCOLOR color )
{
	SetLayerOption( szLayerName, rect );
	SetLayerOption( szLayerName, color );
}

//	ex��ݒ肷��ł�
void CMglLayers2::SetLayerOption( const char *szLayerName, RECT *rect )
{
	InitCheck();

	//	�Ă�����́c�H
	if ( p_layerInfos->find( szLayerName ) == p_layerInfos->end() )
	{
		MyuThrow( 0, "CMglLayers2::SetLayerOption()  ���C���[ %s �͑��݂��܂���B", szLayerName );
	}

	LAYERINFOS_MAP &layerInfos = *p_layerInfos;

	if ( rect == NULL )
		ZeroMemory( &layerInfos[szLayerName].rect, sizeof(RECT) );	//	NULL�Ȃ�0,0,0,0
	else
		layerInfos[szLayerName].rect = *rect;						//	�\���̂܂邱�ҁ[
}

//	ex��ݒ肷��ł�
void CMglLayers2::SetLayerOption( const char *szLayerName, D3DCOLOR color )
{
	InitCheck();

	//	�Ă�����́c�H
	if ( p_layerInfos->find( szLayerName ) == p_layerInfos->end() )
	{
		MyuThrow( 0, "CMglLayers2::SetLayerOption()  ���C���[ %s �͑��݂��܂���B", szLayerName );
	}

	LAYERINFOS_MAP &layerInfos = *p_layerInfos;

	layerInfos[szLayerName].color = color;
}


//	��ʂւ̔��f
void CMglLayers2::OnDraw( D3DCOLOR baseColor )
{
	InitCheck();

	//if ( p_buffers->size() == 0 )
	//	MyuThrow( 0, "CMglLayers2::OnDraw() ���C���[����ł��B" );

	//	�O��̃����_�����O�𔽉f
	AdaptRenderingSurface();

	//	�o�b�N�o�b�t�@�Ƀ����_�����O�B���łɉ�ʂ��N���A
	m_myudg->SetRenderBackBuffer();
	m_myudg->Clear( baseColor );

	//	���C���[�������[�v
	for ( int i=0; i<m_buffers.Size(); i++ )
	{
		LAYERINFO *pInfo = &iLayerInfos(i);
		CMglImage *pSfc = iBuffers(i);

		if ( pInfo->bShow == TRUE )
		{
			//pSfc->XDraw();
			//pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );

			if ( pInfo->rect.left == pInfo->rect.right || pInfo->rect.top == pInfo->rect.bottom )
				pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );
			else
				pSfc->Draw( pInfo->rect.left, pInfo->rect.top, &pInfo->rect, pInfo->color );
		}
	}

	m_myudg->UpdateScreen();
}

