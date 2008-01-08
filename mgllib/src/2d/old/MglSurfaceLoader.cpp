//////////////////////////////////////////////////////////
//
//	MglSurfaceLoader
//		- バッファ統括クラス
//
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MglSurfaceLoader.h"

//	コンストラクタ
CMglSurfaceLoader::CMglSurfaceLoader()
{
	m_pSfcMgr = NULL;
}

//	デストラクタ
CMglSurfaceLoader::~CMglSurfaceLoader()
{

}

//	初期化
void CMglSurfaceLoader::Init( CMglSurfacesManager* pSfcMgr, const char* szDirPath )
{
	m_pSfcMgr = pSfcMgr;
	m_strDirPath = szDirPath;	//	存在しているかチェックいるかも
	m_loadedList.clear();
}

//	読み込み
void CMglSurfaceLoader::Load( const char* szImageFile, const char* szName )
{
	InitChk();	//	初期化チェック

	//	szNameが省略されば場合はszImageFileを使用
	if ( szName == NULL )
		szName = szImageFile;

	//	szNameが既あれば追加しない
	if ( m_pSfcMgr->IsExist( szName ) == FALSE )
		m_pSfcMgr->Add( szName );

	//	読み込み処理
	char szNewImagePath[MAX_PATH+1];
	snprintf( szNewImagePath, sizeof(szNewImagePath),
		"%s\\%s", m_strDirPath.c_str(), szImageFile );
	//m_pSfcMgr->Get( szName )->CreateFromFile( szNewImagePath, FALSE );
	m_pSfcMgr->Get( szName )->Create( szNewImagePath, FALSE );

	//	覚えておく
	m_loadedList[ szName ] = szImageFile;
}
