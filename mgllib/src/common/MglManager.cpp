//////////////////////////////////////////////////////////
//
//	MglManager
//		- MGL�̐F�X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglManager.h"


//	����Singleton�i�P�Ȃ�namespace�j
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
//	�C���X�^���X
//CMglManager _MGL_MANAGER_INSTANCE;
//CMglManager _g_mglManager;

//	�R���X�g���N�^
CMglManager::CMglManager()
{

}

//	�f�X�g���N�^
CMglManager::~CMglManager()
{

}
*/

/*
//	�����𕜋A
CMglManager* CMglManager::_me()
{
	static CMglManager* _pMe = NULL;
	if ( _pMe == NULL )
		_pMe = new CMglManager;

	return _pMe;
}
*/