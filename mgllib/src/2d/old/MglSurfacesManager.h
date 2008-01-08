//////////////////////////////////////////////////////////
//
//	MglSurfacesManager

#ifndef __MglSurfacesManager_H__
#define __MglSurfacesManager_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MyuStringNameMap.h"

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CMglSurfacesManager
{
protected:
	//	�T�[�t�F�X�}�b�v
	CMyuStringNameMap<CMglImage> m_buffers;

	//	�ی상���o�ϐ�
	BOOL initFlg;
	CMglGraphicManager* myudg;	//	CMglGraphicManager�ւ̃|�C���^���i�[
	IDirect3DDevice8* d3d;	//	D3DDevice�ւ̃|�C���^
	string m_strMgrName;

	//	�ی상�\�b�h
	void InitCheck() {
		if ( initFlg == FALSE )
			MyuThrow( 0, "CMglSurfacesManager Init()����ԍŏ��ɌĂ�ł��������B" );
	}

public:
	//	�������E�J���n���\�b�h
	CMglSurfacesManager();
	virtual ~CMglSurfacesManager();
	void Init( CMglGraphicManager *in_myudg, const char* szMgrName="" );
	void Release();	//	�J��
	void DeleteAll();	//	�S�ẴT�[�t�F�X���폜�i�����_�ł�Release()�Ɠ����j

	CMglImage* Add( const char *szBufferName );
	CMglImage* Get( const char *szBufferName );
	void Delete( const char *szBufferName );
	BOOL IsExist( const char* szBufferName ){ return m_buffers.IsExist(szBufferName); }

	//	�I�y���[�^[]
	CMglImage* operator[]( const char *szBufferName ) { return Get(szBufferName); };
};


#endif//__MglSurfacesManager_H__