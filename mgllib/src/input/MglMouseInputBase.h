//////////////////////////////////////////////////////////
//
//	MglMouseInputBase - マウス入力クラス
//
//////////////////////////////////////////////////////////

#ifndef __MglMouseInputBase_H__
#define __MglMouseInputBase_H__

#include "MglDirectInputDeviceBase.h"

//	クラス宣言
class DLL_EXP CMglMouseInputBase : public CMglDirectInputDeviceBase
{
protected:
	/*void InitCheck()	2008/11/28 いらなくない・・・？
	{
		if ( m_pDevice == NULL )
			Init();
	}*/

public:
	//	コンストラクタ・デストラクタ
	CMglMouseInputBase();
	virtual ~CMglMouseInputBase();

	//	初期化と開放
	void Init( HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );

	DIMOUSESTATE2* UpdateStateBuf(){ return (DIMOUSESTATE2*)CMglDirectInputDeviceBase::UpdateStateBuf(); }
	DIMOUSESTATE2* GetStateBuf(){ return (DIMOUSESTATE2*)CMglDirectInputDeviceBase::GetStateBuf(); }
	//DIMOUSESTATE2* GetStateBuf(){ return (DIMOUSESTATE2*)CMglDirectInputDeviceBase::GetStateBuf(); }
};


#endif//__MglMouseInputBase_H__