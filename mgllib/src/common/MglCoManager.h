///////////////////////////////////////////////////////////////////////
//
//	MglCoManager
//		- CoInitialize/Uninitialize �Ǘ��N���X
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglCoManager_H__
#define __MglCoManager_H__

//#include "Objbase.h"
#include <windows.h>

//	�N���X�錾
class DLL_EXP CMglCoManager
{
protected:
	bool m_bInitialized;

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMglCoManager(){ m_bInitialized = false; }
	virtual ~CMglCoManager(){ Release(); }

	//	������
	void Init(){
		if ( !m_bInitialized ){
			CoInitialize(NULL);
			m_bInitialized = true;
		}
	}

	//	���
	void Release(){
		if ( m_bInitialized ){
			CoUninitialize();
			m_bInitialized = false;
		}
	}
};

#endif//__MglCoManager_H__
