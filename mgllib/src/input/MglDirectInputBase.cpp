#include "stdafx.h"
#include "MglDirectInputBase.h"


//	静的メンバ変数のインスタンス
IDirectInput8* CMglDirectInputBase::m_pDi = NULL;
int CMglDirectInputBase::m_nRef=0;


//	コンストラクタ
CMglDirectInputBase::CMglDirectInputBase()
{
	m_nRef++;	//	参照カウンタ
}

//	デストラクタ
CMglDirectInputBase::~CMglDirectInputBase()
{
	m_nRef--;	//	参照カウンタ

	//	所有者が誰も居なくなった段階で開放
	if ( m_nRef <= 0 )
		SAFE_RELEASE( m_pDi );
}

//	初期化
void CMglDirectInputBase::InitBase()
{
	if ( m_pDi != NULL )
		return;	//	既に初期化済みよーん

	//	DirectInput8を初期化
	MyuAssert( DirectInput8Create(
		GetModuleHandle(NULL), /*DIRECTINPUT_VERSION*/ 0x0800, IID_IDirectInput8, (void**)&m_pDi, NULL ),
		DI_OK, "CMglDirectInputBase::Init()  DirectInput8Create()に失敗" );
}

void CMglDirectInputBase::FinalRelease()
{
	SAFE_RELEASE( m_pDi );
}
