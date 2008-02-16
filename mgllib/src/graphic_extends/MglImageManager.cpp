//////////////////////////////////////////////////////////
//
//	MglImageManager
//		- �o�b�t�@�����N���X
//
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MglImageManager.h"

//	�R���X�g���N�^
CMglImageManager::CMglImageManager()
{
	//m_bInit = FALSE;
	m_myudg = NULL;
	d3d = NULL;

	//	CMyuStringNameMap�̃��b�Z�[�W
	m_buffers.SetMessage(
		"CMglImageManager::Add()  ����\"%s\"�̖��O�̃T�[�t�F�X�͑��݂��܂��B",
		"CMglImageManager::Get()  \"%s\"�̖��O�̃T�[�t�F�X�͑��݂��܂���B" );
}

//	�f�X�g���N�^
CMglImageManager::~CMglImageManager()
{
	Release();
}


//	������
void CMglImageManager::Init( CMglGraphicManager *in_myudg )
{
	//	Direct3D�n
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();

	//initFlg = TRUE;
}

//	�J��
void CMglImageManager::Release()
{
	DeleteAll();
}

//	�S�ẴT�[�t�F�X���폜�i�����_�ł�Release()�Ɠ����j
void CMglImageManager::DeleteAll()
{
	//_MGL_DEBUGLOG( "+ CMglImageManager::DeleteAll()" );
	m_buffers.DeleteAll();
	//_MGL_DEBUGLOG( "- CMglImageManager::DeleteAll()" );
}

//	�ǉ�
CMglImage* CMglImageManager::Add( const char *szImageFileName, const char *szBufferName,
			    BOOL bRenderTarget, D3DCOLOR colorKey)
{
	CMglImage* pImage = CMglImageManager::Add( szBufferName );
	//pImage->Create( szImageFileName, bRenderTarget, colorKey );
	pImage->Create( (m_strRootDir + szImageFileName).c_str(), bRenderTarget, colorKey );
	return pImage;
}

//	�ǉ�
CMglImage* CMglImageManager::Add( const char *szBufferName )
{
	_MGL_DEBUGLOG( "+ CMglImageManager::Add( \"%s\" )", szBufferName );
	InitCheck();

	CMglImage surface;
	surface.Init( m_myudg );
	m_buffers.Add( szBufferName, surface );

	_MGL_DEBUGLOG( "- CMglImageManager::Add( \"%s\" )", szBufferName );

	return Get( szBufferName );
}

//	�擾
CMglImage* CMglImageManager::Get( const char *szBufferName )
{
	return m_buffers.Get( szBufferName );
}

//	�擾
BOOL CMglImageManager::IsExist( const char *szBufferName )
{
	return m_buffers.IsExist( szBufferName );
}

//	�폜
void CMglImageManager::Delete( const char *szBufferName )
{
	m_buffers.Delete( szBufferName );
}


void CMglImageManager::SetRootDirectory( const char* szRootDir ){
	m_strRootDir = szRootDir;
	PathLastYenedString(m_strRootDir);
}
