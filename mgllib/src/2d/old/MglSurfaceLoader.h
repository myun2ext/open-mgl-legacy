//////////////////////////////////////////////////////////
//
//	MglSurfaceLoader

#ifndef __MglSurfaceLoader_H__
#define __MglSurfaceLoader_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MglSurfacesManager.h"

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglSurfaceLoader
{
protected:
	CMglSurfacesManager* m_pSfcMgr;
	string m_strDirPath;

	//	リスト
	map<string,string> m_loadedList;	//	<szName,szImageFile>

	//	保護メソッド
	void InitChk() {
		if ( m_pSfcMgr == NULL )
			MyuThrow( 0, "CMglSurfaceLoader::Init()が呼ばれていません。" );
	}

	//	存在チェック
	/*BOOL IsExist( const char* szName ){
		if ( m_loadedList.find( szName ) == m_loadedList.end() )
			return FALSE;
		else
			return TRUE;
	}*/

public:
	//	コンストラクタ・デストラクタ
	CMglSurfaceLoader();
	virtual ~CMglSurfaceLoader();

	void Init( CMglSurfacesManager* pSfcMgr, const char* szDirPath="" );
	void Load( const char* szImageFile, const char* szName=NULL );
};


#endif//__MglSurfaceLoader_H__