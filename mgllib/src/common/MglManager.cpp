//////////////////////////////////////////////////////////
//
//	MglManager
//		- MGLの色々
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglManager.h"


//	似非Singleton（単なるnamespace）
namespace MglManager
{
	CMe::CMe()
	{
		EnableDebugLog();
	}

	CMe me;

	void EnableDebugLog() { me.m_debugLog.Open( MGL_MAIN_DEBUG_LOG_NAME ); }
	void DisableDebugLog() { me.m_debugLog.Close(); }
}

/*
//	インスタンス
//CMglManager _MGL_MANAGER_INSTANCE;
//CMglManager _g_mglManager;

//	コンストラクタ
CMglManager::CMglManager()
{

}

//	デストラクタ
CMglManager::~CMglManager()
{

}
*/

/*
//	自分を復帰
CMglManager* CMglManager::_me()
{
	static CMglManager* _pMe = NULL;
	if ( _pMe == NULL )
		_pMe = new CMglManager;

	return _pMe;
}
*/