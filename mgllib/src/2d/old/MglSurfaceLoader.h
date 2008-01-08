//////////////////////////////////////////////////////////
//
//	MglSurfaceLoader

#ifndef __MglSurfaceLoader_H__
#define __MglSurfaceLoader_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MglSurfacesManager.h"

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CMglSurfaceLoader
{
protected:
	CMglSurfacesManager* m_pSfcMgr;
	string m_strDirPath;

	//	���X�g
	map<string,string> m_loadedList;	//	<szName,szImageFile>

	//	�ی상�\�b�h
	void InitChk() {
		if ( m_pSfcMgr == NULL )
			MyuThrow( 0, "CMglSurfaceLoader::Init()���Ă΂�Ă��܂���B" );
	}

	//	���݃`�F�b�N
	/*BOOL IsExist( const char* szName ){
		if ( m_loadedList.find( szName ) == m_loadedList.end() )
			return FALSE;
		else
			return TRUE;
	}*/

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglSurfaceLoader();
	virtual ~CMglSurfaceLoader();

	void Init( CMglSurfacesManager* pSfcMgr, const char* szDirPath="" );
	void Load( const char* szImageFile, const char* szName=NULL );
};


#endif//__MglSurfaceLoader_H__