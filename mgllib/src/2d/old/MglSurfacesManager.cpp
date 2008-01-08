//////////////////////////////////////////////////////////
//
//	MglSurfacesManager
//		- �o�b�t�@�����N���X
//
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MglSurfacesManager.h"

//	�R���X�g���N�^
CMglSurfacesManager::CMglSurfacesManager()
{
	initFlg = FALSE;

	//	CMyuStringNameMap�̃��b�Z�[�W
	m_buffers.SetMessage(
		"CMglSurfacesManager::Add()  ����\"%s\"�̖��O�̃T�[�t�F�X�͑��݂��܂��B",
		"CMglSurfacesManager::Get()  \"%s\"�̖��O�̃T�[�t�F�X�͑��݂��܂���B" );
}

//	�f�X�g���N�^
CMglSurfacesManager::~CMglSurfacesManager()
{
	Release();
}


//	������
void CMglSurfacesManager::Init( CMglGraphicManager *in_myudg, const char* szMgrName )
{
	//	Direct3D�n
	myudg = in_myudg;
	d3d = myudg->GetD3dDevPtr();
	m_strMgrName = szMgrName;

	initFlg = TRUE;
}

//	�J��
void CMglSurfacesManager::Release()
{
	DeleteAll();
}

//	�S�ẴT�[�t�F�X���폜�i�����_�ł�Release()�Ɠ����j
void CMglSurfacesManager::DeleteAll()
{
	//_MGL_DEBUGLOG( "+ CMglSurfacesManager::DeleteAll()" );
	m_buffers.DeleteAll();
	//_MGL_DEBUGLOG( "- CMglSurfacesManager::DeleteAll()" );
}

//	�ǉ�
CMglImage* CMglSurfacesManager::Add( const char *szBufferName )
{
	_MGL_DEBUGLOG( "+ CMglSurfacesManager::Add( \"%s\" )", szBufferName );
	InitCheck();

	CMglImage surface;
	surface.Init( myudg );

	//	�T�[�t�F�X���̐���
	if ( m_strMgrName != "" ){
		char szSurfaceName[256];
		snprintf( szSurfaceName, sizeof(szSurfaceName),
			"%s[\"%s\"]", m_strMgrName.c_str(), szBufferName );
		surface.SetName( szSurfaceName );
	}
	else
		surface.SetName( szBufferName );

	m_buffers.Add( szBufferName, surface );

	_MGL_DEBUGLOG( "- CMglSurfacesManager::Add( \"%s\" )", szBufferName );

	return Get( szBufferName );
}

//	�擾
CMglImage* CMglSurfacesManager::Get( const char *szBufferName )
{
	return m_buffers.Get( szBufferName );
}

//	�폜
void CMglSurfacesManager::Delete( const char *szBufferName )
{
	m_buffers.Delete( szBufferName );
}
