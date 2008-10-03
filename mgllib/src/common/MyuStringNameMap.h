//////////////////////////////////////////////////////////
//
//	MyuStringNameMap  v0.10.10 04/12/22
//		- 名前がstring確定なmapのテンプレートクラス
//		  エラー処理付き。DLL化対応。
//
//	v0.10.00 04/12/12
//	・作成
//
//	v0.10.10 04/12/22
//	・Delete(), Clear() 実装
//
//////////////////////////////////////////////////////////

#ifndef __MyuStringNameMap_H__
#define __MyuStringNameMap_H__

//	クラス宣言
template <typename T>
class DLL_EXP CMyuStringNameMap
{
private:
	//	データ
	typedef map<string,typename T> T_MAP;
	T_MAP *p_map;

	//	メッセージ
	char m_szAddErrMsg[256];
	char m_szGetErrMsg[256];

public:
	//	コンストラクタ/デストラクタ
	CMyuStringNameMap();
	virtual ~CMyuStringNameMap();

	//	追加/取得
	void Add( const char* in_szName, typename T& object );
	typename T* Get( const char* in_szName );
	void Delete( const char* in_szName );

	//	存在するかチェック
	BOOL IsExist( const char* in_szName );

	//	全てをクリア
	void DeleteAll();

	//	その他
	size_t Size();

	//	メッセージ設定
	void SetMessage( const char* in_szAddErrMsg, const char* in_szGetErrMsg );
};

//extern template<> class __declspec(dllimport) CMyuStringNameMap<CMglImage>;

#endif//__MyuStringNameMap_H__