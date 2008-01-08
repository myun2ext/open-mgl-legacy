//////////////////////////////////////////////////////////
//
//	MglSurfaceLoader
//		- �o�b�t�@�����N���X
//
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MglSurfaceLoader.h"

//	�R���X�g���N�^
CMglSurfaceLoader::CMglSurfaceLoader()
{
	m_pSfcMgr = NULL;
}

//	�f�X�g���N�^
CMglSurfaceLoader::~CMglSurfaceLoader()
{

}

//	������
void CMglSurfaceLoader::Init( CMglSurfacesManager* pSfcMgr, const char* szDirPath )
{
	m_pSfcMgr = pSfcMgr;
	m_strDirPath = szDirPath;	//	���݂��Ă��邩�`�F�b�N���邩��
	m_loadedList.clear();
}

//	�ǂݍ���
void CMglSurfaceLoader::Load( const char* szImageFile, const char* szName )
{
	InitChk();	//	�������`�F�b�N

	//	szName���ȗ�����Ώꍇ��szImageFile���g�p
	if ( szName == NULL )
		szName = szImageFile;

	//	szName��������Βǉ����Ȃ�
	if ( m_pSfcMgr->IsExist( szName ) == FALSE )
		m_pSfcMgr->Add( szName );

	//	�ǂݍ��ݏ���
	char szNewImagePath[MAX_PATH+1];
	snprintf( szNewImagePath, sizeof(szNewImagePath),
		"%s\\%s", m_strDirPath.c_str(), szImageFile );
	//m_pSfcMgr->Get( szName )->CreateFromFile( szNewImagePath, FALSE );
	m_pSfcMgr->Get( szName )->Create( szNewImagePath, FALSE );

	//	�o���Ă���
	m_loadedList[ szName ] = szImageFile;
}
