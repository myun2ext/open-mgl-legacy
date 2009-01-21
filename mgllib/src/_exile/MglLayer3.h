//////////////////////////////////////////////////////////
//
//	MglLayer3 - ���C���[
//
//////////////////////////////////////////////////////////

#ifndef __MglLayer3_H__
#define __MglLayer3_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MglImageManager.h"

//	�����I�}�N��
//#define iLayerInfos(V1)	layerInfos[indexs[V1]]
//#define iBuffers(V1)		buffers[indexs[V1]]
/*#define iLayerInfos(V1)		p_layerInfos->find( p_indexs->find(V1)->second )->second
#define iBuffers(V1)		m_buffers.Get( p_indexs->find(V1)->second.c_str() )*/

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CMglLayer3
{
private:
	CMglGraphicManager* m_myudg;	//	CMglGraphicManager�ւ̃|�C���^���i�[
	_MGL_IDirect3DDevice* m_d3d;			//	D3DDevice�ւ̃|�C���^

	typedef struct {
		BOOL bShow;			//	�\�����邩
		RECT rect;			//	��`�̈�
		//RECT* pRect;		//	��`�̈�B�w�肳��Ă����rect�̃|�C���^���A�w�肳��ĂȂ����NULL������
		D3DCOLOR color;		//	�A���t�@�l | �J���[

		//	2008/01/20  �g��
		float x, y;				//	�ꏊ
		float fScaleX, fScaleY;	//	�k�ڗ�
		float fRotationCenterX;
		float fRotationCenterY;
		float fAngle;			//	�p�x

		CMglImage *pImage;		//	�C���[�W�ւ̃|�C���^
	} LAYERINFO;

	/*
	//map<string,LAYERINFO> layerInfos;
	//map<int,string> indexs;
	typedef map<string,LAYERINFO> LAYERINFOS_MAP;
	LAYERINFOS_MAP *p_layerInfos;
	INDEXS_MAP *p_indexs;
	*/

	//	���X�g
	//list<LAYERINFO> m_list;
	map<int,LAYERINFO> m_list;
	map<CMglImage*,int> m_imagePtrMap;	//	CMglImage��荂���Ɍ������邽�߂̃}�b�v
	typedef map<int,LAYERINFO>::iterator LIST_ITR;
	typedef map<int,LAYERINFO>::reverse_iterator LIST_RITR;

	/*
	//	�����_�����O�p�T�[�t�F�X
	CMglImage m_renderingSurface;

	//	�O��͂ǂ̃T�[�t�F�X�Ƀ����_�����O���悤�Ƃ�����
	CMglImage* m_pPrevTargetSurface;

	//	�O��̃����_�����O��K�p����
	void AdaptRenderingSurface();
	*/

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

	LAYERINFO& ExistChk(int depth){
		if ( m_list.find(depth) == m_list.end() )
			MyuThrow( 222, "CMglLayer3 : depth=%d �͌�����܂���B", depth );
		return m_list[depth];
	}


public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMglLayer3();
	virtual ~CMglLayer3();

	//	������
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){
		m_myudg = in_myudg;
		m_d3d = m_myudg->GetD3dDevPtr();
	}

	//	�o�^/�폜
	//void Regist( CMglImage *pImage, const char *szIdentifierName );
	//void Regist( CMglImage *pImage, int depth );
	void Regist( CMglImage *pImage, int depth,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f );
	void SetParam( int depth,
		float x, float y, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f );
	void Move( int depth, float x, float y );
	void SetPos( int depth, float x, float y );
	void SetColor( int depth, D3DCOLOR color );
	void SetScale( int depth, float fScale ){
		SetScale(depth,fScale,fScale); }
	void SetScale( int depth, float fScaleX, float fScaleY );
	void SetAngle( int depth, float fAngle );
	void SetRect( int depth, RECT rect );
	void SetCenter( int depth, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f ){
		SetRotationCenter(depth,fRotationCenterX,fRotationCenterY); }
	void SetRotationCenter( int depth, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f );

	void MoveDepth( int oldDepth, int newDepth );	//	������

	//	�擾
	CMglImage* Get( int depth ){
		if ( m_list.find(depth) == m_list.end() )
			return NULL;
		return m_list[depth].pImage;
	}

	//	�擾
	int Find( CMglImage *pImage ){
		if ( m_imagePtrMap.find(pImage) == m_imagePtrMap.end() )
			return NULL;
		return m_imagePtrMap[pImage];
	}

	//	�N���A����
	void Clear(){ m_list.clear(); m_imagePtrMap.clear(); }

	//	�`��
	void Draw(){ Rendering(); }
	void DrawAll(){ Rendering(); }
	void AllDraw(){ Rendering(); }
	void Rendering();

	//	�v���p�e�B�n���\�b�h
	/*void Show( const char* szIdentifierName ) { iLayerInfos(i).bShow = TRUE; };
	void Hide( const char* szIdentifierName ) { iLayerInfos(i).bShow = TRUE; };*/
	void Show( int depth ) { ExistChk(depth).bShow = TRUE; }
	void Hide( int depth ) { ExistChk(depth).bShow = FALSE; }

	/*
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
	*/
};


#endif//__MglLayer3_H__
