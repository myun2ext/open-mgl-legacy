//////////////////////////////////////////////////////////
//
//	MglMouseInputBase - �}�E�X���̓N���X
//
//////////////////////////////////////////////////////////

#ifndef __MglMouseInputBase_H__
#define __MglMouseInputBase_H__

#include "MglDirectInputDeviceBase.h"

//	�N���X�錾
class DLL_EXP CMglMouseInputBase : public CMglDirectInputDeviceBase
{
protected:
	/*void InitCheck()	2008/11/28 ����Ȃ��Ȃ��E�E�E�H
	{
		if ( m_pDevice == NULL )
			Init();
	}*/

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglMouseInputBase();
	virtual ~CMglMouseInputBase();

	//	�������ƊJ��
	void Init( HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );

	DIMOUSESTATE2* UpdateStateBuf(){ return (DIMOUSESTATE2*)CMglDirectInputDeviceBase::UpdateStateBuf(); }
	DIMOUSESTATE2* GetStateBuf(){ return (DIMOUSESTATE2*)CMglDirectInputDeviceBase::GetStateBuf(); }
	//DIMOUSESTATE2* GetStateBuf(){ return (DIMOUSESTATE2*)CMglDirectInputDeviceBase::GetStateBuf(); }
};


#endif//__MglMouseInputBase_H__