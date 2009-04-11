//////////////////////////////////////////////////////////
//
//	MyuLoaderBase  v0.10.10 04/12/22
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

#ifndef __MyuLoaderBase_H__
#define __MyuLoaderBase_H__

#include <string>
#include <map>

//	クラス宣言
template <typename T> class DLL_EXP CMyuLoaderBase
{
private:
	//	データ
	//typedef map<string,typename T> T_MAP; <- なにtypenameって？
	//typedef map<string,typename T>::iterator MAP_ITR; <- なにtypenameって？
	typedef map<string,T> T_MAP;
	typedef typename map<string,T>::iterator MAP_ITR;	//	なんかVC++2005で「typename」ってここに付けてみたらコンパイル出来た。（何
	//T_MAP *p_map;	<- なんでこれ動的確保にしてるん？
	//（あ、STLのメモリ領域の問題でか？でもエクスポートすれば問題ないような・・・
	//　つーかヘッダに書けば案外問題なかったりするんじゃね

	T_MAP m_map;

	/*
	//	メッセージ
	char m_szAddErrMsg[256];
	char m_szGetErrMsg[256];*/

protected:
	virtual bool TLoad( typename T& t, const char* szFilename )=0;

public:
	//	コンストラクタ/デストラクタ
	CMyuLoaderBase();
	virtual ~CMyuLoaderBase();

	//	追加/取得
	bool Add( const char* szFilename );
	typename T* Get( const char* szFilename );
	bool Delete( const char* szFilename );

	//	存在するかチェック
	bool IsExist( const char* szFilename );

	//	全てをクリア
	void DeleteAll();

	//	その他
	size_t Size();
};

#endif//__MyuLoaderBase_H__