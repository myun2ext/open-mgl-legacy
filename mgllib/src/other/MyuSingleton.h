//////////////////////////////////////////////////////////
//
//	MyuSingleton  v0.10.00 05/02/28
//		- Singletonデザインパターン用テンプレートクラス
//
//	v0.10.00 05/02/28
//	・新規作成
//
//////////////////////////////////////////////////////////

#ifndef __MyuSingleton_H__
#define __MyuSingleton_H__

//	テンプレートクラス宣言
template <typename T> class CMyuSingleton
{
private:

public:
	CMyuSingleton(){}
	virtual ~CMyuSingleton(){}

	static T* _me()
	{
		static T* _pMe = NULL;
		if ( _pMe == NULL )
			_pMe = new T;

		MessageBox(NULL,"aa",NULL,NULL);

		return _pMe;
		/*
		static T instanceMe;
		return &instanceMe;
		*/
	}
};

#endif//__MyuSingleton_H__