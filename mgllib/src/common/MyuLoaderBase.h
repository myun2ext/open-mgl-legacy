//////////////////////////////////////////////////////////
//
//	MyuLoaderBase  v0.10.10 04/12/22
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

#ifndef __MyuLoaderBase_H__
#define __MyuLoaderBase_H__

#include <string>
#include <map>

//	�N���X�錾
template <typename T> class DLL_EXP CMyuLoaderBase
{
private:
	//	�f�[�^
	typedef map<string,typename T> T_MAP;
	typedef map<string,typename T>::iterator MAP_ITR;
	//T_MAP *p_map;	<- �Ȃ�ł��ꓮ�I�m�ۂɂ��Ă��H
	//�i���ASTL�̃������̈�̖��ł��H�ł��G�N�X�|�[�g����Ζ��Ȃ��悤�ȁE�E�E
	//�@�[���w�b�_�ɏ����ΈĊO���Ȃ������肷��񂶂��

	T_MAP m_map;

	/*
	//	���b�Z�[�W
	char m_szAddErrMsg[256];
	char m_szGetErrMsg[256];*/

protected:
	virtual void TLoad( typename T& t, const char* szFilename )=0;

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMyuLoaderBase();
	virtual ~CMyuLoaderBase();

	//	�ǉ�/�擾
	bool Add( const char* szFilename );
	typename T* Get( const char* szFilename );
	bool Delete( const char* szFilename );

	//	���݂��邩�`�F�b�N
	bool IsExist( const char* szFilename );

	//	�S�Ă��N���A
	void DeleteAll();

	//	���̑�
	size_t Size();
};

#endif//__MyuLoaderBase_H__