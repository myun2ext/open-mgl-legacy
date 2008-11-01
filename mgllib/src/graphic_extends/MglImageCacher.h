//////////////////////////////////////////////////////////
//
//	MglImageCacher

#ifndef __MglImageCacher_H__
#define __MglImageCacher_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
//#include "MglSurfaceLoader.h"
#include "MglImageManager.h"

//	�N���X�錾  /////////////////////////////////////////////////////////
//class CMglImageCacher : public CMglSurfaceLoader
class DLL_EXP CMglImageCacher : public CMglImageManager
{
protected:

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglImageCacher();
	virtual ~CMglImageCacher();

	//	�\�߃L���b�V�����Ă����i������΁j
	void Cache( const char* szImageFile ){
		if ( m_buffers.IsExist( szImageFile ) == FALSE )
			CMglImageManager::Add( szImageFile )->Create(szImageFile);
			//CMglImageManager::Add( szImageFile );
	}

	//	�L���b�V��������
	void Uncache( const char* szImageFile ){ m_buffers.Delete( szImageFile ); }

	//	�擾�n
	//CMglImage* Get( const char *szBufferName ){ return m_pSfcMgr->Get(szBufferName); }//szImageFile�ł���ł���c�H
	//CMglImage* operator[]( const char *szBufferName ) { return Get(szBufferName); };
	CMglImage* Get( const char *szImageFile ){
		CMglImageCacher::Cache(szImageFile);
		return CMglImageManager::Get(szImageFile);
	}
	CMglImage* operator[]( const char *szImageFile ) { return CMglImageCacher::Get(szImageFile); };
};

extern CMglImageCacher g_mglGlobalImageCacher;

#endif//__MglImageCacher_H__