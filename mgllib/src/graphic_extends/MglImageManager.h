//////////////////////////////////////////////////////////
//
//	MglImageManager  v0.20.00 07/03/18
//		- �o�b�t�@�����N���X
//
//	v0.10.02 04/11/14
//	�EInitCheck()�g���Ė������c�B
//	�E���C���[����Ȃ���B�T�[�t�F�X����c�B
//
//	v0.10.50 04/11/19
//	�ESTL�̃�����������
//
//	v0.12.00 04/12/12
//	�ECMyuStringNameMap���g�p����悤�ɏC��
//
//	v0.12.10 04/12/22
//	�EDelete(), Clear()����

//07/03/18
//
//////////////////////////////////////////////////////////

#ifndef __MglImageManager_H__
#define __MglImageManager_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MyuStringNameMap.h"

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CMglImageManager
{
protected:
	//	�T�[�t�F�X�}�b�v
	CMyuStringNameMap<CMglImage> m_buffers;

	//	�ی상���o�ϐ�
	//BOOL m_bInit;
	CMglGraphicManager* m_myudg;	//	CMglGraphicManager�ւ̃|�C���^���i�[
	_MGL_IDirect3DDevice* d3d;			//	D3DDevice�ւ̃|�C���^
	string m_strRootDir;

	//	�ی상�\�b�h
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}
	/*void InitCheck() {
		if ( initFlg == FALSE )
			MyuThrow( 0, "CMglImageManager Init()����ԍŏ��ɌĂ�ł��������B" );
	}*/

public:
	//	�������E�J���n���\�b�h
	CMglImageManager();
	virtual ~CMglImageManager();
	void Init( CMglGraphicManager *in_myudg );
	void Release();	//	�J��
	void DeleteAll();	//	�S�ẴT�[�t�F�X���폜�i�����_�ł�Release()�Ɠ����j

	//void SetRootDirectory( const char* szRootDir ){ m_strRootDir = szRootDir; PathLastYenedString(m_strRootDir); }
	void SetRootDirectory( const char* szRootDir );
	CMglImage* Add( const char *szBufferName );
	CMglImage* AddFile( const char *szBufferName ){
		return Add(szBufferName, szBufferName);	}
	CMglImage* Add( const char *szImageFileName, const char *szBufferName,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY );
	CMglImage* Get( const char *szBufferName );
	BOOL IsExist( const char *szBufferName );
	void Delete( const char *szBufferName );

	//	�I�y���[�^[]
	CMglImage* operator[]( const char *szBufferName ) { return Get(szBufferName); };
};

typedef CMglImageManager CMglImageBuffer;
typedef CMglImageManager CMglImagePool;
typedef CMglImageManager CMglImageLoader;

#endif//__MglImageManager_H__