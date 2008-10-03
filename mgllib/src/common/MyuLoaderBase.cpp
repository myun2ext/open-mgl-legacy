//////////////////////////////////////////////////////////
//
//	MyuLoaderBase
//		- ���O��string�m��ȃN���X�i�G���[�����t���j
//
//////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MyuLoaderBase.h"

//	�e���v���[�g�̃C���X�^���X��DLL���ɖ����I�ɐ���
template class DLL_EXP CMyuLoaderBase<CMglImage>;

//	�}�N����
#define TEMPLATE_T template <typename T>

//	�`�F�b�N���ĂȂ�������m��
#define CHKN_ALLOC()		if ( p_map == NULL ) { p_map = new T_MAP; }

//	�R���X�g���N�^
TEMPLATE_T CMyuLoaderBase<T>::CMyuLoaderBase()
{
	p_map = NULL;
	SetMessage(
		"CMyuLoaderBase::Add()  ����\"%s\"�̖��O�̃I�u�W�F�N�g�͑��݂��܂��B",
		"CMyuLoaderBase::Get()  \"%s\"�̖��O�̃I�u�W�F�N�g�͑��݂��܂���B" );
}

//	�f�X�g���N�^
TEMPLATE_T CMyuLoaderBase<T>::~CMyuLoaderBase()
{
	DeleteAll();
}

//	�S�Ă��N���A
TEMPLATE_T void CMyuLoaderBase<T>::DeleteAll()
{
	SAFE_DELETE( p_map );
}

//	�ǉ�
TEMPLATE_T void CMyuLoaderBase<T>::Add( const char* in_szName, typename T& object )
{
	CHKN_ALLOC();

	//	���ɖ������`�F�b�N
	if ( IsExist( in_szName ) == TRUE )
		MyuThrow( 0, m_szAddErrMsg, in_szName );

	(*p_map)[in_szName] = object;
}

//	�擾
TEMPLATE_T typename T* CMyuLoaderBase<T>::Get( const char* in_szName )
{
	CHKN_ALLOC();

	//	�{���ɂ��邩�`�F�b�N
	if ( IsExist( in_szName ) == FALSE )
		MyuThrow( 0, m_szGetErrMsg, in_szName );

	return &(*p_map)[in_szName];
}

//	�폜
TEMPLATE_T typename void CMyuLoaderBase<T>::Delete( const char* in_szName )
{
	CHKN_ALLOC();

	//	�{���ɂ��邩�`�F�b�N
	if ( IsExist( in_szName ) == FALSE )
		MyuThrow( 0, m_szGetErrMsg, in_szName );

	(*p_map).erase( in_szName );
}

//	���݂��邩�`�F�b�N
TEMPLATE_T BOOL CMyuLoaderBase<T>::IsExist( const char* in_szName )
{
	CHKN_ALLOC();

	T_MAP::iterator itr = p_map->find( in_szName );
	if ( itr == p_map->end() )
		return FALSE;
	else
		return TRUE;
}

//	�T�C�Y�擾
TEMPLATE_T size_t CMyuLoaderBase<T>::Size()
{
	CHKN_ALLOC();

	return p_map->size();
}

//	���b�Z�[�W�ݒ�
TEMPLATE_T void CMyuLoaderBase<T>::SetMessage( const char* in_szAddErrMsg, const char* in_szGetErrMsg )
{
	strcpy( m_szAddErrMsg, in_szAddErrMsg );
	strcpy( m_szGetErrMsg, in_szGetErrMsg );
}
