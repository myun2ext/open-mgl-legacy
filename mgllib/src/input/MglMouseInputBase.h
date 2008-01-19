//////////////////////////////////////////////////////////
//
//	MglMouseInputBase - マウス入力クラス
//
//////////////////////////////////////////////////////////

#ifndef __MglMouseInputBase_H__
#define __MglMouseInputBase_H__

#include "MglDirectInputBase.h"

#define STATEBUF_SIZE	(256)

//	クラス宣言
class DLL_EXP CMglMouseInputBase : public CMglDirectInputBase
{
protected:
	_MGL_IDirectInputDevice *m_pDevice;
	BYTE m_stateBuf[STATEBUF_SIZE];

	void Acquire();
	void Unacquire();

	void InitCheck()
	{
		if ( m_pDevice == NULL )
			Init();
	}

public:
	//	コンストラクタ・デストラクタ
	CMglMouseInputBase();
	virtual ~CMglMouseInputBase();

	//	初期化と開放
	void Init( HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();

	void UpdateStateBuf();
	BOOL IsPressKey( BYTE keyCode );		//	Is???
	BOOL IsPressDikey( BYTE keyCode ){ return IsPressKey(keyCode); }
};


#endif//__MglMouseInputBase_H__