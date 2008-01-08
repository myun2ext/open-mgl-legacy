#ifndef __MyuDirectInputEx_H__
#define __MyuDirectInputEx_H__

#include "MyuDirectInput.h"

//	ÉNÉâÉXêÈåæ
class CMyuDirectInputEx : CMyuDirectInput
{
private:
	int nChargeTime;

public:
	CMyuDirectInputEx();
	virtual ~CMyuDirectInputEx();

	BOOL IsChargePressKey( const char *szInputName );
	void SetChargeTimerFull( const char *szInputName );
	void SetChargeTime( int nChargeTime_in );
};

#endif//__MyuDirectInputEx_H__