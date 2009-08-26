///////////////////////////////////////////////////////////////////////
//
//	MglCoManager
//		- CoInitialize/Uninitialize 管理クラス
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglCoManager_H__
#define __MglCoManager_H__

//#include "Objbase.h"
#include <windows.h>

//	クラス宣言
class DLL_EXP CMglCoManager
{
protected:
	bool m_bInitialized;

public:
	//	コンストラクタ/デストラクタ
	CMglCoManager(){ m_bInitialized = false; }
	virtual ~CMglCoManager(){ Release(); }

	//	初期化
	void Init(){
		if ( !m_bInitialized ){
			CoInitialize(NULL);
			m_bInitialized = true;
		}
	}

	//	解放
	void Release(){
		if ( m_bInitialized ){
			CoUninitialize();
			m_bInitialized = false;
		}
	}
};

#endif//__MglCoManager_H__
