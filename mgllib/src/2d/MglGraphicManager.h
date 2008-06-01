///////////////////////////////////////////////////////////////////////
//
//	MglGraphicManager  v0.10.62 05/03/10
//		- DirectX Graphics �Ǘ��N���X
//
//	v0.10.01 04/11/15
//	�EClearBackBuffer()�ǉ�
//
//	v0.10.02 04/12/09
//	�ERelease()�ɂė�����o�O�C���im_pD3dDev��NULL�`�F�b�N�j
//
//	v0.10.20 04/12/13
//	�EDirect3D CreateDevice() ���̃t���O���w��ł���悤�Ɋg��
//
//	v0.10.21 04/12/13
//	�EPaint()����
//
//	v0.10.25 04/12/17
//	�ESetAlphaBlendSetting() ����p�~���ASetAlphaMode() ������
//	�EGetAlphaMode() ������
//
//	v0.10.26 04/12/22
//	�EDDS�p�̃A���t�@�I�v�V�������������Ă݂�B
//
//	v0.10.30 05/01/04
//	�E�f�o�C�X�����_���v����悤��
//
//	v0.10.31 05/02/28
//	�E�o�b�N�o�b�t�@���N���A���Ă���
//
//	v0.10.60 05/02/28
//	�EInitEx()�ADirect3DCreate()�̎���
//
//	v0.10.61 05/03/02
//	�Em_format��m_formatTexture�ɁB
//	�@m_formatTexture�̌����������������̂ŏC���B
//
//	v0.10.62 05/03/10
//	�EMGL_ALPHA_OPT_DEFAULT�ǉ�
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglGraphicManager_H__
#define __MglGraphicManager_H__

//#include "MyuDebugLog.h"
#include "MglManager.h"

#include "MglGraphicUtil.h"
#include "MyuReleaseBase.h"
#include "MglVertex.h"

/*
//	���_�\����
#define	FVF_MYU_VERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
typedef struct
{
	float		x,y,z;				//�ʒu���
	float		rhw;				//���_�ϊ��l
	D3DCOLOR	color;				//�|���S���J���[
	float		tu,tv;				//�e�N�X�`�����W
}MYU_VERTEX;
*/

//	Direct3D CreateDevice() ���̓Ǝ��t���O
#define D3D_DEVICE_FLG_T_AND_L_HAL	(0x00000001)
#define D3D_DEVICE_FLG_HAL			(0x00000002)
#define D3D_DEVICE_FLG_HW_SW_MIX	(0x00000004)
#define D3D_DEVICE_FLG_REF			(0x00000008)
#define D3D_DEVICE_MODE_DEFAULT		( D3D_DEVICE_FLG_T_AND_L_HAL | D3D_DEVICE_FLG_HAL )
#define D3D_DEVICE_MODE_AUTO		(0xffffffff)

//	�A���t�@�I�v�V����
#define MGL_ALPHA_OPT_NOTUSE		(0)		//	�Ȃ�
#define MGL_ALPHA_OPT_TRANSLUCENCE	(1)		//	������
#define MGL_ALPHA_OPT_ADD			(2)		//	���Z
#define MGL_ALPHA_OPT_SUBTRACT		(3)		//	���Z
#define MGL_ALPHA_OPT_HALFADD		(4)		//	�����Z
#define MGL_ALPHA_OPT_DDS			(9)		//	DDS
#define MGL_ALPHA_OPT_NOCHANGE		(0xffffffff)	//	�ύX�Ȃ�
#define MGL_ALPHA_OPT_DEFAULT		(MGL_ALPHA_OPT_TRANSLUCENCE)

//#define CAPS_DUMP_LOG				"MglDXGlphCaps.log"

extern int g_nSfcCount;
extern int g_2dgCount;

#define DELREF()	if( m_myudg != NULL && g_2dgCount > 0 ){ m_myudg->RmRefOfAutoRelease( this ); }else{}

class CMglTexture;
///////////////////////////////////////
//
//		�N���X�錾
//
class DLL_EXP CMglGraphicManager
{
protected:
	//	DirectX�n�錾
	_MGL_IDirect3D* m_pD3d;			//	D3D
	_MGL_IDirect3DDevice* m_pD3dDev;	//	D3D�f�o�C�X

	int m_nDispX, m_nDispY;		//	��ʃT�C�Y
	D3DFORMAT m_formatTexture;	//	�t�H�[�}�b�g
	DWORD m_dwD3dDeviceFlg;		//	Direct3D�f�o�C�X�̃��[�h(T&L��)
	DWORD m_dwAlphaOption;		//	�A���t�@�I�v�V�����BGetAlphaMode()�p�ɕێ�

	//	�f�o�C�X���
	UINT m_nTexMem;				//	�c��e�N�X�`��������
	DWORD m_dwMaxTextureHeight;	//	�ő�e�N�X�`������
	DWORD m_dwMaxTextureWidth;	//	�ő�e�N�X�`����

	//	�����J���p�z��
	map<CMyuReleaseBase*,CMyuReleaseBase*> m_autoReleaseAry;
	typedef map<CMyuReleaseBase*,CMyuReleaseBase*>::iterator AUTO_RELESE_ITR;

	//	2007/01/11  �Ȃ񂩃X�v���C�g�Ƃ�Surface���Ƃɂ����������Ȃ��Ă��C���f�l
	ID3DXSprite* m_pSprite;			//	�X�v���C�g
	BOOL m_bUseSprite;
	//BOOL m_bSpriteCenterDraw;

	//////////////////////////////////////////////////////////////////////////

	//	�����I���\�b�h
	void Direct3DCreate();
	BOOL D3dCreateDevice( DWORD dwD3dDeviceFlg, D3DPRESENT_PARAMETERS* pPresentParam,
		int nAdapterNo=D3DADAPTER_DEFAULT, HWND hFocusWindow=NULL );
	void IsValidDisplayMode( int nWidth, int nHeight, D3DFORMAT Format, int nRefreshRate );
	//void GetVramInfo( DWORD *dwpTotal, DWORD *dwpFree );

public:
	//	���J�����o�ϐ�
	D3DSURFACE_DESC backBufferDesc;		//	�o�b�N�o�b�t�@���

	//////////////////////////
	//
	//		���J���\�b�h
	//

	//	�R���X�g���N�^/�f�X�g���N�^
	CMglGraphicManager();
	virtual ~CMglGraphicManager();

	//	������/�J��
	void Init( HWND hWnd, int nDispX, int nDispY, BOOL bFullscreen, D3DFORMAT formatTexture=D3DFMT_A8R8G8B8,
		DWORD dwD3dDeviceMode=D3D_DEVICE_MODE_AUTO, UINT nAdapterNo=D3DADAPTER_DEFAULT );
//		DWORD dwD3dDeviceMode=D3D_DEVICE_MODE_DEFAULT );
	void InitEx( D3DPRESENT_PARAMETERS* pPresentParam, DWORD dwD3dDeviceMode, D3DFORMAT formatTexture,
		int nAdapterNo, HWND hFocusWindow=NULL );

	void Release();

	//	�֗��n���\�b�h
	IDirect3DSurface8* GetBackBuffer()
	{
		IDirect3DSurface8* p;
		MyuAssert( m_pD3dDev->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &p ), D3D_OK,
			"CMglGraphicManager::GetBackBuffer()  GetBackBuffer()�Ɏ��s" );
		return p;
	}

	void SetRenderBackBuffer() {
		m_pD3dDev->SetRenderTarget( GetBackBuffer(), NULL );
	}

	/*	�ǂ��������̂Ŕp�~�A���Ƃ� SetAlphaMode() �ɓ���
	void SetAlphaBlendSetting( DWORD alphaOp=D3DTOP_BLENDCURRENTALPHA );
	void EnabledAlphaBlend(); */
	void SetAlphaMode( DWORD dwAlphaOption=MGL_ALPHA_OPT_DEFAULT );

	void Clear( D3DCOLOR color=D3DCOLOR_BLACK );
	//void Clear( D3DCOLOR color=D3DCOLOR_NABLACK ); // 2007/02/11 NA���ƃ}�Y���Ȃ��c�H
	void Paint( RECT* rect, D3DCOLOR color );
	void Paint( int left, int top, int right, int bottom, D3DCOLOR color ){
		RECT rect;
		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;
		Paint(&rect, color);
	}

	//	2007/01/11  �X�v���C�g�`��
	void InitSprite();
	void SpriteDraw( CMglTexture *pTexture, float x=0, float y=0, CONST RECT* pSrcRect=NULL, D3DCOLOR color=D3DCOLOR_WHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f );
	//	float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=-1, float fRotationCenterY=-1, float fAngle=0.0f );
	/*void EnableCenterDraw() {	m_bSpriteCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bSpriteCenterDraw = FALSE; }*/
	void SpriteBegin(){ if( m_pSprite != NULL ) m_pSprite->Begin(); }
	void SpriteEnd(){ if( m_pSprite != NULL ) m_pSprite->End(); }

	//	�V�[���n���\�b�h
	void UpdateScreen();
	/*
	void BeginScene();
	void EndScene();
	void Present();
	*/

	//	�����J���p
	void AddRefOfAutoRelease( CMyuReleaseBase* pRef );
	void RmRefOfAutoRelease( CMyuReleaseBase* pRef );

	//	�v���p�e�B�n���\�b�h
	int GetDispX() { return m_nDispX; }
	int GetDispY() { return m_nDispY; }
	int GetWidth() { return m_nDispX; }
	int GetHeight() { return m_nDispY; }
	D3DFORMAT GetFormat() { return m_formatTexture; }
	_MGL_IDirect3DDevice* GetD3dDevPtr() { return m_pD3dDev; }
	_MGL_IDirect3DDevice* GetD3dDevice() { return m_pD3dDev; }
	DWORD GetD3dDeviceFlg() { return m_dwD3dDeviceFlg; }
	DWORD GetAlphaMode() { return m_dwAlphaOption; }
	void EnableSupportSprite(){ m_bUseSprite = TRUE; }
	void DisableSupportSprite(){ m_bUseSprite = FALSE; }
};

////////////////////////////////////////////////////////////
//
//	�f�t�H���g CMglGraphicManager �C���X�^���X�֘A
//
extern CMglGraphicManager *g_pDefaultGd;	//	������̃N���X�p�Ɏc���Ă�������

//	2007/01/03  �V�����C���^�[�t�F�[�X�i�G���[�`�F�b�N���j
DLL_EXP CMglGraphicManager* GetDefaultGd();

//	�`�F�b�N
inline BOOL CheckDefaultGd()
{
	if ( g_pDefaultGd == NULL )
		return FALSE;
	return TRUE;
}

#endif//__MglGraphicManager_H__
