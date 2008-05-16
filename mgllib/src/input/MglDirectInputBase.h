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

//#include "mglinput_.h"
//#include <dinput.h>

//	DirectInput�n
#ifdef _MGL_USE_DXVER9
	#ifndef IDirectInput9
		#pragma message("�G���[: IDirectInput9 ����`����Ă��܂���B<dinput.h> �̃o�[�W�������m�F���Ă��������B�i���������� Visual C++ �W���� dinput.h ��ǂݍ���ł���H�j")
		#error IDirectInput9 was not defined!! Please confirm the version of <dinput.h>. (Do because it is <dinput.h> of the Visual C++ standard?)

	#endif
#elif _MGL_USE_DXVER10
	#ifndef IDirectInput10
		#pragma message("�G���[: IDirectInput10 ����`����Ă��܂���B<dinput.h> �̃o�[�W�������m�F���Ă��������B�i���������� Visual C++ �W���� dinput.h ��ǂݍ���ł���H�j")
		#error IDirectInput10 was not defined!! Please confirm the version of <dinput.h>. (Do because it is <dinput.h> of the Visual C++ standard?)
	#endif
#else
	#ifndef IDirectInput8
		#pragma message("�G���[: IDirectInput8 ����`����Ă��܂���B<dinput.h> �̃o�[�W�������m�F���Ă��������B�i���������� Visual C++ �W���� dinput.h ��ǂݍ���ł���H�j")
		#error IDirectInput8 was not defined!! Please confirm the version of <dinput.h>. (Do because it is <dinput.h> of the Visual C++ standard?)
		//#error IDirectInput8 was not defined.
	#endif
#endif


//	�N���X�錾
class DLL_EXP CMglDirectInputBase
{
private:
	static int m_nRef;

protected:
	//	�݂�Ȃŋ��p���� IDirectInput �C���X�^���X
	static _MGL_IDirectInput *m_pDi;

	//	�R�C�c���Ăяo��
	void InitBase();

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglDirectInputBase();
	virtual ~CMglDirectInputBase();

	void FinalRelease();
};


#endif//__MglDirectInputBase_H__
