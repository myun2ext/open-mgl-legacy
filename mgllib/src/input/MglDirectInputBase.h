///////////////////////////////////////////////////////////////////////
//
//	CMglDirectInputBase
//	IDirectInput8 ���Ǘ�����N���X�B
//	�C���X�^���X�͈������点�Ȃ��B�݂�Ȃň��IDirectInput8 �����p���Ďg�킹��B
//	�Ȃ̂ŕʂ�virtual�p���Ƃ�����K�v���͖���
//	�Q�ƃJ�E���^��0�ɂȂ�ƃC���X�^���X�͊J�������B
//
///////////////////////////////////////////////////////////////////////
#ifndef __MglDirectInputBase_H__
#define __MglDirectInputBase_H__

//	�N���X�錾
class DLL_EXP CMglDirectInputBase
{
private:
	static int m_nRef;

protected:
	//	�݂�Ȃŋ��p���� IDirectInput8 �C���X�^���X
	static IDirectInput8 *m_pDi;

	//	�R�C�c���Ăяo��
	void InitBase();

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglDirectInputBase();
	virtual ~CMglDirectInputBase();

	void FinalRelease();
};


#endif//__MglDirectInputBase_H__