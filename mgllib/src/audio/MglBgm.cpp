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
	//SAFE_DELETE_TMPL<CMglMp3Dshow*>((CMglMp3Dshow**)&m_pMp3Dshow);
	//SAFE_DELETE_TMPL<CMglOgg*>((CMglOgg**)&m_pOgg);
	SAFE_DELETE_TMPL(CMglMp3Dshow,m_pMp3Dshow);
	SAFE_DELETE_TMPL(CMglOgg,m_pOgg);
	/*SAFE_DELETE((CMglMp3Dshow*)m_pMp3Dshow);
	SAFE_DELETE((CMglOgg*)m_pOgg);*/
}


void CMglBgm::Init()
{
	m_pMp3Dshow->Init();
	m_pOgg->Init();
}

void CMglBgm::Release()
{
	m_pMp3Dshow->Release();
	m_pOgg->Release();
}

void CMglBgm::Load( const char* szAudioFile )
{
	CMyuFilePath fp(szAudioFile);
	const char *szExt = fp.GetExt();

	if ( strcmp(szExt,"ogg") == 0 )
		m_pBgm = m_pOgg;
	else
		m_pBgm = m_pMp3Dshow;

	m_pBgm->Load(szAudioFile);
}
