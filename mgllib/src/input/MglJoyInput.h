#ifndef __MglJoyInput_H__
#define __MglJoyInput_H__

//#include "CMglJoyManager.h"

#define ERR_STICK_VALUE		(0xFFFFFFFF)

//	クラス宣言
class DLL_EXP CMglJoyInput
{
protected:
	//DIDEVCAPS m_devCaps;
	IDirectInputDevice8* m_pDevice;	//	Attachされるだけなので開放はしないよん

	//	JOYの設定
	long m_nNeutralX;
	long m_nNeutralY;
	long m_nMargin;
	BOOL m_bJoySetupFlg;

	void Acquire();

	void CHKINIT(){ if(m_pDevice==NULL) MyuThrow( 2121, "CMglJoyInput::Attach()を実行してください。" ); }
	void CHKINFOSET(){ if(m_bJoySetupFlg!=TRUE) MyuThrow( 2121, "CMglJoyInput::SetJoyStickInfo()を実行してください。" ); }

public:
	//	コンストラクタとデストラクタ
	CMglJoyInput();
	virtual ~CMglJoyInput();

	//	Attachする
	void Attach( IDirectInputDevice8* pDevice ){ m_pDevice = pDevice; }

	//	各取得メソッド
	BOOL IsPushBotton( int nBottomNo );
	BOOL IsUp();
	BOOL IsDown();
	BOOL IsLeft();
	BOOL IsRight();
	BOOL GetX( long* pnX );
	BOOL GetY( long* pnY );

	DIJOYSTATE2* GetState( DIJOYSTATE2* pStateBuf );

	//	Joyの設定
	void SetJoyStickInfo( long nNeutralX, long nNeutralY, long nMargin )
	{
		m_nNeutralX = nNeutralX;
		m_nNeutralY = nNeutralY;
		m_nMargin = nMargin;
		m_bJoySetupFlg = TRUE;
	}

	//	直接 DIJOYSTATE2 を取得
};

#endif//__MglJoyInput_H__
