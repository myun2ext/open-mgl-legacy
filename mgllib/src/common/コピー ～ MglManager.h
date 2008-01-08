#ifndef __MglManager_H__
#define __MglManager_H__

#include "MyuDebugLog.h"

//extern CMyuDebugLog g_mglDebugLog;

/*
#define _MGL_MANAGER_INSTANCE	_g_mglManager
#define _EXTERN_MGL_MANAGER		extern CMglManager _MGL_MANAGER_INSTANCE
#define _MGL_DEBUGLOG			_MGL_MANAGER_INSTANCE.m_debugLog.Print

_EXTERN_MGL_MANAGER;
*/


//	ログのファイル名
#define MGL_MAIN_DEBUG_LOG_NAME	"MglDebugLog.log"

//	クラス宣言
class CMglManager//  : public CMyuSingleton<CMglManager>
{
private:

public:
	CMglManager(){}
	virtual ~CMglManager(){}

	CMyuDebugLog m_debugLog;

	static CMglManager* _me()
	{
		static CMglManager* _pMe = NULL;
		if ( _pMe == NULL )
		{
			_pMe = new CMglManager;
			MessageBox(NULL,"Singleton",NULL,NULL);
		}

		return _pMe;
	}

	void UseDebugLog()
	{
		_me()->m_debugLog.Open( MGL_MAIN_DEBUG_LOG_NAME );
	}
};

//	使用者用
#define _MGL_DEBUGLOG			CMglManager::_me()->m_debugLog.Print

//extern CMglManager _g_mglManager;

#endif//__MglManager_H__