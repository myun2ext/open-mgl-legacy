#include "stdafx.h"
#include "MglBgm.h"
#include "MglMp3Dshow.h"
#include "MglOgg.h"

//	コンストラクタ
CMglBgm::CMglBgm()
{
	m_pMp3Dshow = new CMglMp3Dshow();
	m_pOgg = new CMglOgg();
}

//	デストラクタ
CMglBgm::~CMglBgm()
{
	SAFE_DELETE_t<CMglMp3Dshow*>((CMglMp3Dshow**)&m_pMp3Dshow);
	SAFE_DELETE_t<CMglOgg*>((CMglOgg**)&m_pOgg);
	/*SAFE_DELETE((CMglMp3Dshow*)m_pMp3Dshow);
	SAFE_DELETE((CMglOgg*)m_pOgg);*/
}


void CMglBgm::Init()
{

}

void CMglBgm::Release()
{

}

void CMglBgm::Load( const char* szAudioFile )
{

}
