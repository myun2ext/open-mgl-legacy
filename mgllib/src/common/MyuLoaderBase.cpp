//////////////////////////////////////////////////////////
//
//	MyuLoaderBase
//		- ���O��string�m��ȃN���X�i�G���[�����t���j
//
//////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MyuLoaderBase.h"

//	�}�N����
#define TEMPLATE_T template <typename T>

//	�R���X�g���N�^
TEMPLATE_T CMyuLoaderBase<T>::CMyuLoaderBase()
{
}

//	�f�X�g���N�^
TEMPLATE_T CMyuLoaderBase<T>::~CMyuLoaderBase()
{
}

//	�S�Ă��N���A
TEMPLATE_T void CMyuLoaderBase<T>::DeleteAll()
{
	m_map.clear();
}

//	�ǉ�
TEMPLATE_T bool CMyuLoaderBase<T>::Add( const char* szFilename )
{
	//	���ɖ������`�F�b�N
	if ( IsExist( szFilename ) == true )
		return false;

	//(*p_map)[szFilename] = T();
	m_map[szFilename] = T();
}

//	�擾
TEMPLATE_T typename T* CMyuLoaderBase<T>::Get( const char* szFilename )
{
	//	�{���ɂ��邩�`�F�b�N
	if ( IsExist( szFilename ) == false )
		return false;

	//return &(*p_map)[szFilename];
	return &m_map[szFilename];
}

//	�폜
TEMPLATE_T typename bool CMyuLoaderBase<T>::Delete( const char* szFilename )
{
	//	�{���ɂ��邩�`�F�b�N
	if ( IsExist( szFilename ) == false )
		return false;

	m_map.erase( szFilename );
}

//	���݂��邩�`�F�b�N
TEMPLATE_T bool CMyuLoaderBase<T>::IsExist( const char* szFilename )
{
	MAP_ITR itr = m_map.find( szFilename );
	if ( itr == m_map.end() )
		return false;
	else
		return true;
}

//	�T�C�Y�擾
TEMPLATE_T size_t CMyuLoaderBase<T>::Size()
{
	//return p_map->size();
	return m_map.size();
}
