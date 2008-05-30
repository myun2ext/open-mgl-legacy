//////////////////////////////////////////////////////////
//
//	MglLayers2  v0.16.60 04/12/22
//		- MglGraphicManager ���C���[�N���X
//
//	v0.15.05 04/11/14
//	�EInit()�̎d�l�ύX�B�i�J���[�L�[�ǉ����N���A�j
//	�E���C���[����Ȃ���B�T�[�t�F�X����c�B
//
//	v0.16.00 04/11/15
//	�E���C���[�̎d�l��啝�ɕύX�B�T�[�t�F�X���f�[�^��
//	�@�V�X�e���������Ɏ����A�����_�����O����Ƃ���
//	�@VRAM�ɃR�s�[���Ă���悤�ɁB
//
//	v0.16.50 04/11/19
//	�EMglImageBuffers��STL�̃������������ɑΉ�
//
//	v0.16.55 04/12/14
//	�ESetRender() �y�� SetRenderAndClear() �ǉ�
//
//	v0.16.56 04/12/17
//	�E�_�~�[�T�[�t�F�X�̃T�C�Y�`�F�b�N�����ǉ�
//
//	v0.16.60 04/12/22
//	�E�J���������Â������̂ŏC��
//	�EDelete(), Clear()����
//
//////////////////////////////////////////////////////////

#ifndef __MglLayers2_H__
#define __MglLayers2_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MglImageManager.h"

//	�����I�}�N��
//#define iLayerInfos(V1)	layerInfos[indexs[V1]]
//#define iBuffers(V1)		buffers[indexs[V1]]
#define iLayerInfos(V1)		p_layerInfos->find( p_indexs->find(V1)->second )->second
#define iBuffers(V1)		m_buffers.Get( p_indexs->find(V1)->second.c_str() )

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CMglLayers2 : public CMglImageManager
{
private:
	typedef struct {
		BOOL bShow;			//	�\�����邩
		RECT rect;			//	��`�̈�
		D3DCOLOR color;		//	�A���t�@�l | �J���[
	} LAYERINFO;

	//map<string,LAYERINFO> layerInfos;
	//map<int,string> indexs;
	typedef map<string,LAYERINFO> LAYERINFOS_MAP;
	typedef map<int,string> INDEXS_MAP;
	LAYERINFOS_MAP *p_layerInfos;
	INDEXS_MAP *p_indexs;

	//	�����_�����O�p�T�[�t�F�X
	CMglImage m_renderingSurface;

	//	�O��͂ǂ̃T�[�t�F�X�Ƀ����_�����O���悤�Ƃ�����
	CMglImage* m_pPrevTargetSurface;

	//	CreateFromFile�p�ɋL��
	char m_szDummyFile[MAX_PATH+1];
	D3DCOLOR m_colorKey;

	//	�O��̃����_�����O��K�p����
	void AdaptRenderingSurface();

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMglLayers2();
	virtual ~CMglLayers2();

	//	�������E�J���n���\�b�h
	void Init( CMglGraphicManager *in_myudg, const char* in_szDummyFile, D3DCOLOR colorKey=DEF_COLORKEY );
	void Release();		//	�J��
	void DeleteAll();	//	�S�Ẵ��C���[���폜�i�����_�ł�Release()�Ɠ����j

	void Add( const char *szBufferName );
	CMglImage* AddEntry( const char *szBufferName );
	CMglImage* GetRenderingSurface( const char *szLayerName );
	//	Get()�� CMglImageBuffers �Ŏ����ς݂Ȃ̂ł���Ȃ�㩂�
	//CMglImage* Get( const char *szLayerName );
	void SetLayerOption( const char *szLayerName, RECT *rect, D3DCOLOR color );
	void SetLayerOption( const char *szLayerName, RECT *rect );
	void SetLayerOption( const char *szLayerName, D3DCOLOR color );
	void OnDraw( D3DCOLOR baseColor=0 );

	//	�֗��Ȋg�����\�b�h
	void SetRender( const char *szLayerName )			{ Get( szLayerName )->SetRender(); }
	void SetRenderAndClear( const char *szLayerName )	{ SetRender( szLayerName ); Get( szLayerName )->Clear(); }

	//	�v���p�e�B�n���\�b�h
	void SetEnable( int i ) { iLayerInfos(i).bShow = TRUE; };
	void SetDisable( int i ) { iLayerInfos(i).bShow = FALSE; };
	void ChangeEnable( int i ) {
		if ( iLayerInfos(i).bShow == TRUE ) { iLayerInfos(i).bShow = FALSE; }
		else								{ iLayerInfos(i).bShow = TRUE;  }
	}

	void SetEnable( char *szLayerName )
		{ (*p_layerInfos)[szLayerName].bShow = TRUE; };
	void SetDisable( char *szLayerName )
		{ (*p_layerInfos)[szLayerName].bShow = FALSE; };
	void ChangeEnable( char *szLayerName ) {
		if ( (*p_layerInfos)[szLayerName].bShow == TRUE ) { (*p_layerInfos)[szLayerName].bShow = FALSE; }
		else											  { (*p_layerInfos)[szLayerName].bShow = TRUE;  }
	}
};


#endif//__MglLayers2_H__
