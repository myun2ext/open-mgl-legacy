//////////////////////////////////////////////////////////
//
//	MyuStringNameMap  v0.10.10 04/12/22
//		- ���O��string�m���map�̃e���v���[�g�N���X
//		  �G���[�����t���BDLL���Ή��B
//
//	v0.10.00 04/12/12
//	�E�쐬
//
//	v0.10.10 04/12/22
//	�EDelete(), Clear() ����
//
//////////////////////////////////////////////////////////

#ifndef __MyuStringNameMap_H__
#define __MyuStringNameMap_H__

//	�N���X�錾
template <typename T>
class DLL_EXP CMyuStringNameMap
{
private:
	//	�f�[�^
	typedef map<string,typename T> T_MAP;
	T_MAP *p_map;

	//	���b�Z�[�W
	char m_szAddErrMsg[256];
	char m_szGetErrMsg[256];

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMyuStringNameMap();
	virtual ~CMyuStringNameMap();

	//	�ǉ�/�擾
	void Add( const char* in_szName, typename T& object );
	typename T* Get( const char* in_szName );
	void Delete( const char* in_szName );

	//	���݂��邩�`�F�b�N
	BOOL IsExist( const char* in_szName );

	//	�S�Ă��N���A
	void DeleteAll();

	//	���̑�
	size_t Size();

	//	���b�Z�[�W�ݒ�
	void SetMessage( const char* in_szAddErrMsg, const char* in_szGetErrMsg );
};

//extern template<> class __declspec(dllimport) CMyuStringNameMap<CMglImage>;

#endif//__MyuStringNameMap_H__