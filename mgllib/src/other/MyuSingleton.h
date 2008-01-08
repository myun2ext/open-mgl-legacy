//////////////////////////////////////////////////////////
//
//	MyuSingleton  v0.10.00 05/02/28
//		- Singleton�f�U�C���p�^�[���p�e���v���[�g�N���X
//
//	v0.10.00 05/02/28
//	�E�V�K�쐬
//
//////////////////////////////////////////////////////////

#ifndef __MyuSingleton_H__
#define __MyuSingleton_H__

//	�e���v���[�g�N���X�錾
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