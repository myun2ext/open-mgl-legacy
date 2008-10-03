//////////////////////////////////////////////////////////
//
//	MyuLoaderBase
//		- 名前がstring確定なクラス（エラー処理付き）
//
//////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MyuLoaderBase.h"

//	テンプレートのインスタンスをDLL側に明示的に生成
template class DLL_EXP CMyuLoaderBase<CMglImage>;

//	マクロ化
#define TEMPLATE_T template <typename T>

//	チェックしてなかったら確保
#define CHKN_ALLOC()		if ( p_map == NULL ) { p_map = new T_MAP; }

//	コンストラクタ
TEMPLATE_T CMyuLoaderBase<T>::CMyuLoaderBase()
{
	p_map = NULL;
	SetMessage(
		"CMyuLoaderBase::Add()  既に\"%s\"の名前のオブジェクトは存在します。",
		"CMyuLoaderBase::Get()  \"%s\"の名前のオブジェクトは存在しません。" );
}

//	デストラクタ
TEMPLATE_T CMyuLoaderBase<T>::~CMyuLoaderBase()
{
	DeleteAll();
}

//	全てをクリア
TEMPLATE_T void CMyuLoaderBase<T>::DeleteAll()
{
	SAFE_DELETE( p_map );
}

//	追加
TEMPLATE_T void CMyuLoaderBase<T>::Add( const char* in_szName, typename T& object )
{
	CHKN_ALLOC();

	//	既に無いかチェック
	if ( IsExist( in_szName ) == TRUE )
		MyuThrow( 0, m_szAddErrMsg, in_szName );

	(*p_map)[in_szName] = object;
}

//	取得
TEMPLATE_T typename T* CMyuLoaderBase<T>::Get( const char* in_szName )
{
	CHKN_ALLOC();

	//	本当にあるかチェック
	if ( IsExist( in_szName ) == FALSE )
		MyuThrow( 0, m_szGetErrMsg, in_szName );

	return &(*p_map)[in_szName];
}

//	削除
TEMPLATE_T typename void CMyuLoaderBase<T>::Delete( const char* in_szName )
{
	CHKN_ALLOC();

	//	本当にあるかチェック
	if ( IsExist( in_szName ) == FALSE )
		MyuThrow( 0, m_szGetErrMsg, in_szName );

	(*p_map).erase( in_szName );
}

//	存在するかチェック
TEMPLATE_T BOOL CMyuLoaderBase<T>::IsExist( const char* in_szName )
{
	CHKN_ALLOC();

	T_MAP::iterator itr = p_map->find( in_szName );
	if ( itr == p_map->end() )
		return FALSE;
	else
		return TRUE;
}

//	サイズ取得
TEMPLATE_T size_t CMyuLoaderBase<T>::Size()
{
	CHKN_ALLOC();

	return p_map->size();
}

//	メッセージ設定
TEMPLATE_T void CMyuLoaderBase<T>::SetMessage( const char* in_szAddErrMsg, const char* in_szGetErrMsg )
{
	strcpy( m_szAddErrMsg, in_szAddErrMsg );
	strcpy( m_szGetErrMsg, in_szGetErrMsg );
}
