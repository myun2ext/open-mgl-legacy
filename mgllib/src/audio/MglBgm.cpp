#include "stdafx.h"
#include "MglBgm.h"
#include "MglMp3Dshow.h"
#include "MglOgg.h"

//	コンストラクタ
CMglBgm::CMglBgm()
{
	m_pMp3Dshow = new CMglMp3Dshow();
	//m_pOgg = new CMglOgg();
	m_pOgg = NULL;
	m_pBgm = NULL;
	m_hWnd = NULL;
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


void CMglBgm::Init( HWND hWnd )
{
	Release();

	m_pMp3Dshow->Init( hWnd );
	//m_pOgg->Init();

	m_hWnd = hWnd;
}

void CMglBgm::Release()
{
	m_pMp3Dshow->Release();
	if ( m_pOgg != NULL )
		m_pOgg->Release();
	m_pBgm = NULL;
}

void CMglBgm::Load( const char* szAudioFile )
{
	//	2009/09/07  あれ？必要じゃなーい・・・？
	//Release();	-> 駄目ｗｗｗｗInitしたのも消えちゃうｗｗｗｗ　でも多重Loadの場合はどうすれば・・・（各クラス任せか？あ、あと再生停止しとけばいいか）

	if ( m_pBgm != NULL )
		UnLoad();
		//Release();

	InitCheck();

	/////////////////////////////////////

	CMyuFilePath fp(szAudioFile);
	const char *szExt = fp.GetExt();

	//if ( strcmp(szExt,"ogg") == 0 )
	if ( stricmp(szExt,"ogg") == 0 )
	{
		if ( m_pOgg == NULL ){
			m_pOgg = new CMglOgg();
			m_pOgg->Init(m_hWnd);
		}
		m_pBgm = m_pOgg;
	}
	else
		m_pBgm = m_pMp3Dshow;

	m_pBgm->Load(szAudioFile);
}
