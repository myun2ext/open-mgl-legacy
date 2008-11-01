//////////////////////////////////////////////////////////
//
//	MglImageCacher

#ifndef __MglImageCacher_H__
#define __MglImageCacher_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
//#include "MglSurfaceLoader.h"
#include "MglImageManager.h"

//	クラス宣言  /////////////////////////////////////////////////////////
//class CMglImageCacher : public CMglSurfaceLoader
class DLL_EXP CMglImageCacher : public CMglImageManager
{
protected:

public:
	//	コンストラクタ・デストラクタ
	CMglImageCacher();
	virtual ~CMglImageCacher();

	//	予めキャッシュしておく（無ければ）
	void Cache( const char* szImageFile ){
		if ( m_buffers.IsExist( szImageFile ) == FALSE )
			CMglImageManager::Add( szImageFile )->Create(szImageFile);
			//CMglImageManager::Add( szImageFile );
	}

	//	キャッシュを消す
	void Uncache( const char* szImageFile ){ m_buffers.Delete( szImageFile ); }

	//	取得系
	//CMglImage* Get( const char *szBufferName ){ return m_pSfcMgr->Get(szBufferName); }//szImageFileでいんでしょ…？
	//CMglImage* operator[]( const char *szBufferName ) { return Get(szBufferName); };
	CMglImage* Get( const char *szImageFile ){
		CMglImageCacher::Cache(szImageFile);
		return CMglImageManager::Get(szImageFile);
	}
	CMglImage* operator[]( const char *szImageFile ) { return CMglImageCacher::Get(szImageFile); };
};

extern CMglImageCacher g_mglGlobalImageCacher;

#endif//__MglImageCacher_H__