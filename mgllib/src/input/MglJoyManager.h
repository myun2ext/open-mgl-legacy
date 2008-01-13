#ifndef __MglJoyManager_H__
#define __MglJoyManager_H__

#include "MglDirectInputBase.h"

//	�N���X�錾
class DLL_EXP CMglJoyManager : public CMglDirectInputBase
{
protected:
	vector<_MGL_IDirectInputDevice*> m_joystkDevAry;

	//BOOL bInitFlg;

	//void CHKINIT(){ if(bInitFlg!=TRUE) ExInit(); }

public:
	//	�R���X�g���N�^�ƃf�X�g���N�^
	CMglJoyManager();
	virtual ~CMglJoyManager();

	//	�����������B�ʏ�͎����I�ɌĂ΂�邪�A�����ōׂ��ȃI�v�V�������w�肷�邱�Ƃ��\
	void ExInit( DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void ExInit( HWND hWnd, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();	//	�J��

	//	�f�o�C�X�����擾����
	int GetJoyCount(){ return m_joystkDevAry.size(); }

	//	�f�o�C�X���擾����
	_MGL_IDirectInputDevice* GetJoyDevice( int nDeviceNo )
	{
		if ( nDeviceNo > GetJoyCount()-1 )
			MyuThrow( 0, "CMglJoyInput::IsPushBotton  �W���C�f�o�C�X�ԍ� %d �͑��݂��܂���B", nDeviceNo );
		return m_joystkDevAry[nDeviceNo];
	}
};

#endif//__MglJoyManager_H__
