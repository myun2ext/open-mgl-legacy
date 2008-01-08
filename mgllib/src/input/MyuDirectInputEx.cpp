#include "stdafx.h"
#include "MyuDirectInputEx.h"


//	コンストラクタ
CMyuDirectInputEx::CMyuDirectInputEx()
{
	nChargeTime = 0;
}

//	デストラクタ
CMyuDirectInputEx::~CMyuDirectInputEx()
{

}


//	キーが押されたか（溜め版）(関係名版)
BOOL CMyuDirectInputEx::IsChargePressKey( const char *szInputName )
{
	INPUT_RELATE *relate = GetRelate(szInputName);

	if ( relate->keyPool == TRUE )
	{
		relate->keyPool = FALSE;
		relate->timer.Start();
		return TRUE;
	}
	else
	{
		if( relate->timer.Get() > (unsigned int)nChargeTime && relate->oldKeyPush ) /* CMyuDirectInputBase::IsPushKey( relate->keyCode ) */
			return TRUE;

		return FALSE;
	}
}

void CMyuDirectInputEx::SetChargeTimerFull( const char *szInputName )
{
	INPUT_RELATE *relate = GetRelate(szInputName);

	relate->timer.Start(999);
	relate->keyPool = FALSE;
	relate->oldKeyPush = TRUE;
}

void CMyuDirectInputEx::SetChargeTime( int nChargeTime_in )
{
	nChargeTime = nChargeTime_in;
}
