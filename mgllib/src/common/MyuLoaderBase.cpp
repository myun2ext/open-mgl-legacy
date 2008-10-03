//////////////////////////////////////////////////////////
//
//	MyuLoaderBase
//		- 名前がstring確定なクラス（エラー処理付き）
//
//////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MyuLoaderBase.h"

//	マクロ化
#define TEMPLATE_T template <typename T>

//	コンストラクタ
TEMPLATE_T CMyuLoaderBase<T>::CMyuLoaderBase()
{
}

//	デストラクタ
TEMPLATE_T CMyuLoaderBase<T>::~CMyuLoaderBase()
{
}

//	全てをクリア
TEMPLATE_T void CMyuLoaderBase<T>::DeleteAll()
{
	m_map.clear();
}

//	追加
TEMPLATE_T bool CMyuLoaderBase<T>::Add( const char* szFilename )
{
	//	既に無いかチェック
	if ( IsExist( szFilename ) == true )
		return false;

	//(*p_map)[szFilename] = T();
	m_map[szFilename] = T();
}

//	取得
TEMPLATE_T typename T* CMyuLoaderBase<T>::Get( const char* szFilename )
{
	//	本当にあるかチェック
	if ( IsExist( szFilename ) == false )
		return false;

	//return &(*p_map)[szFilename];
	return &m_map[szFilename];
}

//	削除
TEMPLATE_T typename bool CMyuLoaderBase<T>::Delete( const char* szFilename )
{
	//	本当にあるかチェック
	if ( IsExist( szFilename ) == false )
		return false;

	m_map.erase( szFilename );
}

//	存在するかチェック
TEMPLATE_T bool CMyuLoaderBase<T>::IsExist( const char* szFilename )
{
	MAP_ITR itr = m_map.find( szFilename );
	if ( itr == m_map.end() )
		return false;
	else
		return true;
}

//	サイズ取得
TEMPLATE_T size_t CMyuLoaderBase<T>::Size()
{
	//return p_map->size();
	return m_map.size();
}
