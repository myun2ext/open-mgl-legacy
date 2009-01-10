//////////////////////////////////////////////////////////
//
//	MglGraphicManager
//		- DirectX Graphics �Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglGraphicManager.h"
#include "MglTexture.h"
#include "MglD3dCapsDumper.h"

/*
//	VRAM�T�C�Y�擾�p
#include <DDraw.h>
#pragma comment(lib,"ddraw.lib")
*/

/*
#include "MglManager.h"
_EXTERN_MGL_MANAGER;
*/

int g_nSfcCount=0;
int g_2dgCount=0;
CMglGraphicManager *g_pDefaultGd=NULL;

//	�R���X�g���N�^
CMglGraphicManager::CMglGraphicManager()
{
	_MGL_DEBUGLOG( "CMglGraphicManager �̃C���X�^���X����������܂����B" );
	CMglStackInstance("CMglGraphicManager::CMglGraphicManager");

	m_pD3d = NULL;
	m_pD3dDev = NULL;
	m_nDispX = 0;
	m_nDispY = 0;
	ZeroMemory( &m_formatTexture, sizeof(m_formatTexture) ); 
	m_dwD3dDeviceFlg = 0;
	m_dwAlphaOption = MGL_ALPHA_OPT_TRANSLUCENCE;

	m_nTexMem = 0;
	m_dwMaxTextureHeight = 0;
	m_dwMaxTextureWidth = 0;

	//	2007/01/11  �Ȃ񂩃X�v���C�g�Ƃ�Surface���Ƃɂ����������Ȃ��Ă��C���f�l
	m_pSprite = NULL;
	m_bSpriteBegun = FALSE;
	EnableSupportSprite(); //m_bUseSprite = TRUE;
	//m_bSpriteCenterDraw = FALSE;

	g_2dgCount++;
}

//	�f�X�g���N�^
CMglGraphicManager::~CMglGraphicManager()
{
	_MGL_DEBUGLOG( "+ CMglGraphicManager::�f�X�g���N�^" );
	CMglStackInstance("CMglGraphicManager::~CMglGraphicManager");
	Release();
	_MGL_DEBUGLOG( "- CMglGraphicManager::�f�X�g���N�^" );
	g_2dgCount--;
}

//	�J��
void CMglGraphicManager::Release()
{
	_MGL_DEBUGLOG( "+ CMglGraphicManager::Release()" );
	CMglStackInstance("CMglGraphicManager::Release");

	//	�V�[�����I�����Ă���
	if ( m_pD3dDev != NULL )
		m_pD3dDev->EndScene();

	//	�����J������
	_MGL_DEBUGLOG( "�����J���������J�n���܂��B�i���t�@�����X���F%d�j", m_autoReleaseAry.size() );
	for ( ; m_autoReleaseAry.size() > 0; )
	{
		m_autoReleaseAry.begin()->second->Release();
	}
	_MGL_DEBUGLOG( "�����J���������������܂����B" );
	/*for( AUTO_RELESE_ITR itr = m_autoReleaseAry.end(); itr != m_autoReleaseAry.begin(); itr-- )
	{
		_MGL_DEBUGLOG( "itr->second->Release()" );
		itr->second->Release();

		//	�ŁARelease() �̒��� RmRefOfAutoRelease() ���Ă΂�� itr�̑Ώۂ͏������A�ƁB
	}*/

	SAFE_RELEASE( m_pD3dDev );
	SAFE_RELEASE( m_pD3d );
	_MGL_DEBUGLOG( "- CMglGraphicManager::Release()" );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//	�������y�ъJ�n
void CMglGraphicManager::Init( HWND hWnd, int nDispX, int nDispY, BOOL bFullscreen,
							  D3DFORMAT formatTexture, DWORD dwD3dDeviceMode, UINT nAdapterNo )
{
	_MGL_DEBUGLOG( "+ CMglGraphicManager::Init()" );
	CMglStackInstance("CMglGraphicManager::Init");

	//	2008/07/06 �ǉ�
	Release();

	/*	InitEx()�ֈړ�
	m_nDispX = nDispX;
	m_nDispY = nDispY;
	m_formatTexture = format;
	*/

	//	D3D�I�u�W�F�N�g�̐���
	Direct3DCreate();

	//	�f�o�C�X���̎擾
	/*
		2007/07/15  HAL������������REF�͗v��Ȃ����AHAL�Ɏ��s������REF���g�p���Ȃ��Ɓc

	D3DCAPS8 capsHal;
	D3DCAPS8 capsRef;

	_MGL_DEBUGLOG( "HAL�f�o�C�X�̎擾" );
	MyuAssert( m_pD3d->GetDeviceCaps( nAdapterNo, D3DDEVTYPE_HAL, &capsHal ), D3D_OK,
		"CMglGraphicManager::Init()  HAL�f�o�C�X���̎擾�Ɏ��s�B" );

	_MGL_DEBUGLOG( "REF�f�o�C�X�̎擾" );
	MyuAssert( m_pD3d->GetDeviceCaps( nAdapterNo, D3DDEVTYPE_REF, &capsRef ), D3D_OK,
		"CMglGraphicManager::Init()  REF�f�o�C�X���̎擾�Ɏ��s�B" );
	DumpAdapterInfo( &capsHal, &capsRef );
	*/
	D3DCAPS8 caps;
	_MGL_DEBUGLOG( "HAL�f�o�C�X�̎擾..." );
	if ( m_pD3d->GetDeviceCaps( nAdapterNo, D3DDEVTYPE_HAL, &caps ) != D3D_OK )
	{
		_MGL_DEBUGLOG( "HAL�f�o�C�X���̎擾�Ɏ��s�BREF�Ń��g���C" );

		//_MGL_DEBUGLOG( "REF�f�o�C�X�̎擾" );
		MyuAssert( m_pD3d->GetDeviceCaps( nAdapterNo, D3DDEVTYPE_REF, &caps ), D3D_OK,
			"CMglGraphicManager::Init()  HAL/REF�f�o�C�X���̎擾�Ɏ��s�B" );
		_MGL_DEBUGLOG( "REF�f�o�C�X�̎擾�ɐ���" );

		//	dwD3dDeviceMode��REF�ɐݒ�iAuto�Ȃ�j
		if ( dwD3dDeviceMode == D3D_DEVICE_MODE_AUTO ){
			_MGL_DEBUGLOG( "dwD3dDeviceMode��D3D_DEVICE_FLG_REF�ɐݒ肵�܂�" );
			dwD3dDeviceMode = D3D_DEVICE_FLG_REF;
		}
	}
	else
		_MGL_DEBUGLOG( "HAL�f�o�C�X�̎擾�ɐ���" );
	//DumpAdapterInfo( &caps );
	CMglD3dCapsDumper dumper;
	dumper.DumpAdapterInfo( m_pD3d, &caps );

	//	2007/07/15  D3D_DEVICE_MODE_AUTO�Ή�
	if ( dwD3dDeviceMode == D3D_DEVICE_MODE_AUTO ){
		dwD3dDeviceMode = D3D_DEVICE_MODE_DEFAULT;
		_MGL_DEBUGLOG( "dwD3dDeviceMode��D3D_DEVICE_MODE_DEFAULT�ɐݒ肵�܂�" );
	}

	//	�f�B�X�v���C���[�h�̎擾
	D3DDISPLAYMODE dispMode;
	MyuAssert( this->m_pD3d->GetAdapterDisplayMode( nAdapterNo, &dispMode ), D3D_OK,
		"CMglGraphicManager::Init()  �f�B�X�v���C���[�h�̎擾�Ɏ��s�B" );

	if ( dispMode.Format == D3DFMT_X8R8G8B8 )
		_MGL_DEBUGLOG( "dispMode.Format = D3DFMT_X8R8G8B8(32bit)" );
	else if ( dispMode.Format == D3DFMT_R8G8B8 )
		_MGL_DEBUGLOG( "dispMode.Format = D3DFMT_R8G8B8(24bit)" );
	else if ( dispMode.Format == D3DFMT_R5G6B5 )
		_MGL_DEBUGLOG( "dispMode.Format = D3DFMT_R5G6B5(16bit)" );
	else if ( dispMode.Format == D3DFMT_R3G3B2 )
		_MGL_DEBUGLOG( "dispMode.Format = D3DFMT_R3G3B2(256)" );
	else
		_MGL_DEBUGLOG( "dispMode.Format = Unknown(%u)", dispMode.Format );

	if ( dispMode.Format == D3DFMT_R3G3B2 )
		MyuThrow( 0, "��ʂ̐F��16bit�ȏ�ɂ��Ă��������B" );

	D3DPRESENT_PARAMETERS presentParam; 
	ZeroMemory( &presentParam, sizeof(D3DPRESENT_PARAMETERS) );

	//	D3D�f�o�C�X�̃p�����^��ݒ�
	presentParam.BackBufferWidth = nDispX; // GetRealTexSize(nDispX);
	presentParam.BackBufferHeight = nDispY; // GetRealTexSize(nDispY);
	presentParam.BackBufferFormat = dispMode.Format;
	presentParam.BackBufferCount = 1;
	presentParam.MultiSampleType = D3DMULTISAMPLE_NONE;
	presentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParam.hDeviceWindow = hWnd;
	presentParam.FullScreen_RefreshRateInHz  = D3DPRESENT_RATE_DEFAULT;

	if ( bFullscreen == TRUE )
		presentParam.Windowed = FALSE;
	else
		presentParam.Windowed = TRUE;

	//BOOL            EnableAutoDepthStencil;
    //D3DFORMAT       AutoDepthStencilFormat;
    //DWORD           Flags;
    //UINT            FullScreen_PresentationInterval;

	//	Ex�ł̌Ăяo��
	InitEx( &presentParam, dwD3dDeviceMode, formatTexture, nAdapterNo );

	//	g_pDefaultGd�ւ̐ݒ�
	if ( g_2dgCount == 1 )
		g_pDefaultGd = this;
	else
		g_pDefaultGd = NULL;	//	���������c�H�ǂ�E�E�H

	/*
	//	2007/01/11  �X�v���C�g�쐬
	if ( m_bUseSprite )
		MyuAssert( D3DXCreateSprite( m_pD3dDev, &m_pSprite ), D3D_OK,
			"CMglGraphicManager::Init()  D3DXCreateSprite()�Ɏ��s" );
	*/
	InitSprite();

	_MGL_DEBUGLOG( "- CMglGraphicManager::Init()" );
}
void CMglGraphicManager::InitSprite()
{
	if ( m_pD3dDev == NULL )
		MyuThrow( 0, "CMglGraphicManager::InitSprite()  m_pD3dDev��NULL" );
	if ( m_pSprite != NULL )	//	���ɂ���΃X�L�b�v
		return;

	MyuAssert( D3DXCreateSprite( m_pD3dDev, &m_pSprite ), D3D_OK,
		"CMglGraphicManager::Init()  D3DXCreateSprite()�Ɏ��s" );
}

//	D3D�I�u�W�F�N�g�̐����iInitEx()�p�ɕ����j
void CMglGraphicManager::Direct3DCreate()
{
	CMglStackInstance("CMglGraphicManager::Direct3DCreate");

	if ( m_pD3d != NULL )
		//MyuThrow2( 0, 0x0201, "CMglGraphicManager::Direct3DCreate()  D3D�I�u�W�F�N�g�͊�����܂��B" );
		//	2007/07/15  ���ɂ������牽�����Ȃ���ł���łȂ��E�E�E�H
		return;

	//	D3D�I�u�W�F�N�g�̐���
	m_pD3d = Direct3DCreate8( D3D_SDK_VERSION );
	if ( NULL == m_pD3d )
		MyuThrow2( 0, MGLMSGNO_GRP_MANAGER_D3DCREATE_FAILED,
			"CMglGraphicManager::Direct3DCreate()  Direct3DCreate8()�Ɏ��s�B" );
}

//	�������y�ъJ�n��Ex��
void CMglGraphicManager::InitEx( D3DPRESENT_PARAMETERS* pPresentParam, DWORD dwD3dDeviceMode, D3DFORMAT formatTexture, int nAdapterNo, HWND hFocusWindow )
{
	_MGL_DEBUGLOG( "+ CMglGraphicManager::InitEx()" );
	CMglStackInstance("CMglGraphicManager::InitEx");

	m_nDispX = pPresentParam->BackBufferWidth;
	m_nDispY = pPresentParam->BackBufferHeight;
	m_formatTexture = formatTexture;

	if ( hFocusWindow == NULL )
		hFocusWindow = pPresentParam->hDeviceWindow;

/*
	//	�X�e���V���n
	MyuAssert( this->m_pD3d->CheckDeviceFormat( nAdapterNo, D3DDEVTYPE_HAL, dispMode.Format,
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 ), D3D_OK,
		"�X�e���V���s��" );

	MyuAssert( this->m_pD3d->CheckDeviceFormat( nAdapterNo, D3DDEVTYPE_HAL, dispMode.Format,
		D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, dispMode.Format ), D3D_OK,
		"�����_�[�s��" );
	 
	presentParam.EnableAutoDepthStencil = TRUE;
	presentParam.AutoDepthStencilFormat = D3DFMT_D16;
*/

	//	2007/07/15  REF�T�|�[�g
	if ( dwD3dDeviceMode == D3D_DEVICE_FLG_REF ){
		_MGL_DEBUGLOG( "dwD3dDeviceMode��D3D_DEVICE_FLG_REF�ł��B" );
		if ( D3dCreateDevice( D3D_DEVICE_FLG_REF, pPresentParam, nAdapterNo, hFocusWindow ) != TRUE )
			//MyuThrow( 0, "�w�肳�ꂽ�f�o�C�X���[�h(dwD3dDeviceMode=0x%08X)�̓T�|�[�g����Ă��܂���B\r\nDirect3D�f�o�C�X�̐����Ɏ��s���܂����B", dwD3dDeviceMode );
			MyuThrow( 0, "Direct3D�f�o�C�X�̐����Ɏ��s���܂����B\r\n"
				"dwD3dDeviceMode=0x%08X", dwD3dDeviceMode );
	}
	else
	{

		//	D3D�f�o�C�X����
		DWORD dwWork=dwD3dDeviceMode;
		for( DWORD dwMask=1; dwWork != 0; dwMask <<= 1 )
		{
			DWORD dwFlag = dwWork & dwMask;
			if ( dwFlag != 0 )
			{
				if ( D3dCreateDevice( dwFlag, pPresentParam, nAdapterNo, hFocusWindow ) == TRUE )
				{
					m_dwD3dDeviceFlg = dwFlag;
					break;
				}
			}

			//	�t���O��ׂ�
			dwWork -= dwMask;
		}
		if ( dwWork == 0 )
			//MyuThrow( 0, "�w�肳�ꂽ�f�o�C�X���[�h(dwD3dDeviceMode=0x%08X)�̓T�|�[�g����Ă��܂���B\r\nDirect3D�f�o�C�X�̐����Ɏ��s���܂����B", dwD3dDeviceMode );
			MyuThrow( 0, "Direct3D�f�o�C�X�̐����Ɏ��s���܂����B\r\n"
				"dwD3dDeviceMode=0x%08X", dwD3dDeviceMode );
	}


	//	VRAM�������O�ɏo��
	m_nTexMem = m_pD3dDev->GetAvailableTextureMem();
	_MGL_DEBUGLOG( "AvailableTextureMemory = %u KB", (int)(m_nTexMem/1024) );

	//	Vertex��ݒ�
	SetupMyuVertex();

	//	�o�b�N�o�b�t�@�̏����擾
	MyuAssert( GetBackBuffer()->GetDesc( &backBufferDesc ), D3D_OK,
		"CMglGraphicManager::Init()  GetBackBuffer()->GetDesc()�Ɏ��s" );

	//	�A���t�@�u�����h��L���ɂ��Ă���
	SetAlphaMode();

	//	�V�[�����J�n���Ă���
	MyuAssert( m_pD3dDev->BeginScene(), D3D_OK,
		"CMglGraphicManager::Init()  �V�[���̊J�n�Ɏ��s�B" );

	//	�o�b�N�o�b�t�@���N���A���Ă���
	Clear();


	_MGL_DEBUGLOG( "- CMglGraphicManager::InitEx()" );
}

//	Vertex��ݒ�
void CMglGraphicManager::SetupMyuVertex(){
	MyuAssert( this->m_pD3dDev->SetVertexShader( FVF_MYU_VERTEX ), D3D_OK,
		"CMglGraphicManager::Init()  SetVertexShader()�Ɏ��s" );
}

//	Direct3D �� CreateDevice()��Ǝ��t���O�ɂ��Ăяo��
BOOL CMglGraphicManager::D3dCreateDevice( DWORD dwD3dDeviceFlg, D3DPRESENT_PARAMETERS* pPresentParam, int nAdapterNo, HWND hFocusWindow )
{
	//_MGL_DEBUGLOG( "+ CMglGraphicManager::D3dCreateDevice()" );
	CMglStackInstance("CMglGraphicManager::D3dCreateDevice");

	D3DDEVTYPE deviceType=D3DDEVTYPE_FORCE_DWORD;
	DWORD vertexFlag=0;

	switch( dwD3dDeviceFlg )
	{
	//	REF
	case D3D_DEVICE_FLG_REF:
		deviceType = D3DDEVTYPE_REF;
		vertexFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  REF�ɂĎ��s���܂��B" );
		break;

	//	HAL
	case D3D_DEVICE_FLG_HAL:
		deviceType = D3DDEVTYPE_HAL;
		vertexFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  HAL�ɂĎ��s���܂��B" );
		break;

	//	T&L HAL
	case D3D_DEVICE_FLG_T_AND_L_HAL:
		deviceType = D3DDEVTYPE_HAL;
		vertexFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  T&L HAL�ɂĎ��s���܂��B" );
		break;

	//	�\�t�g���n�[�h�̍������_����
	case D3D_DEVICE_FLG_HW_SW_MIX:
		deviceType = D3DDEVTYPE_HAL;
		vertexFlag = D3DCREATE_MIXED_VERTEXPROCESSING;
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  �\�t�g���n�[�h�̍����ɂĎ��s���܂��B" );
		break;

	//	�s���Ȓ萔
	default:
		MyuThrow( 0, "CMglGraphicManager::D3dCreateDevice() �s���ȃf�o�C�X�t���O�ł��B(dwD3dDeviceFlg=0x%08X)", dwD3dDeviceFlg );
	}

	//	D3D�f�o�C�X����
	if( FAILED( this->m_pD3d->CreateDevice(
		nAdapterNo, deviceType, hFocusWindow, vertexFlag | D3DCREATE_MULTITHREADED, pPresentParam, &this->m_pD3dDev ) ) )
    {
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  ���s�B" );
		return FALSE;
	}
	else
	{
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  �����B" );
		return TRUE;
	}
}

//	�t���X�N���[�����̃f�B�X�v���C���[�h���\���ǂ����`�F�b�N����
void CMglGraphicManager::IsValidDisplayMode( int nWidth, int nHeight, D3DFORMAT Format, int nRefreshRate )
{

}

/////////////////////////////////////////////////////////////////////////////////

void CMglGraphicManager::Clear( D3DCOLOR color )
{
	CMglStackInstance("CMglGraphicManager::Clear");
   //m_pD3dDev->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );// ZBuffer���N���A����
	Paint( NULL, color );
}

void CMglGraphicManager::Paint( RECT* rect, D3DCOLOR color )
{
	CMglStackInstance("CMglGraphicManager::Paint");
	if ( m_pD3dDev == NULL )
		MyuThrow( 0, "CMglGraphicManager::Paint()  m_pD3dDev��NULL" );

	int rectCount = 0;
	if ( rect != NULL )
		rectCount = 1;
	//	�ǂ�������Ȃ����Ǒ�������L���X�g��������Ă������񂿂Ⴄ�c�H
    m_pD3dDev->Clear( rectCount, (D3DRECT*)rect, D3DCLEAR_TARGET, color, 1.0f, 0 );// ZBuffer���N���A����
}

////////////////////////////////////////////////////////////////////////
//
//		�g���֗��n���\�b�h
//
////////////////////////////////////////////////////////////////////////


/*	�Ӗ����������̂Ŕp�~�A���Ƃ� SetAlphaMode() �֓���

//	�A���t�@�u�����h�Ɋւ���Z�b�e�B���O���s��
//	alphaOp �� D3DTEXTUREOP
void CMglGraphicManager::SetAlphaBlendSetting( DWORD alphaOp )
{
	m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, alphaOp);
	m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//	�A���t�@�u�����h��L���ɂ��Ă���
	EnabledAlphaBlend();
}

//	�A���t�@�u�����h��L���ɂ���
void CMglGraphicManager::EnabledAlphaBlend() {
	m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

//	�A���t�@�u�����h�𖳌��ɂ���
void CMglGraphicManager::DisableAlphaBlend() {
	m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
*/

//	�A���t�@�l���ǂ��������邩�ݒ肷��
void CMglGraphicManager::SetAlphaMode( DWORD dwAlphaOption )
{
	if ( m_pD3dDev == NULL )
		MyuThrow( 0, "CMglGraphicManager::SetAlphaMode()  m_pD3dDev��NULL" );

	//	����
	if ( dwAlphaOption == MGL_ALPHA_OPT_NOTUSE )
	{
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	//	������
	else if ( dwAlphaOption == MGL_ALPHA_OPT_TRANSLUCENCE )
	{
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDCURRENTALPHA);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//	���Z
	else if ( dwAlphaOption == MGL_ALPHA_OPT_ADD )
	{
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDCURRENTALPHA);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//	���Z
	else if ( dwAlphaOption == MGL_ALPHA_OPT_SUBTRACT )
	{
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDCURRENTALPHA);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//	�����Z
	else if ( dwAlphaOption == MGL_ALPHA_OPT_HALFADD )
	{
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDCURRENTALPHA);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//	DDS
	else if ( dwAlphaOption == MGL_ALPHA_OPT_DDS )
	{
		m_pD3dDev->SetRenderState(D3DRS_ALPHAREF, 0x00000001);
		m_pD3dDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	else
	{
		MyuThrow( 0, "CMglGraphicManager::SetAlphaMode()  �A���t�@�I�v�V���� %u �͕s���ȃI�v�V�����ł��B", dwAlphaOption );
	}

	m_dwAlphaOption=dwAlphaOption;
}


////////////////////////////////////////////////////////////////////////
//
//		�V�[���n���\�b�h
//
////////////////////////////////////////////////////////////////////////

//	��ʂւ̔��f���s��
void CMglGraphicManager::UpdateScreen()
{
	if ( m_pD3dDev == NULL )
		MyuThrow( 0, "CMglGraphicManager::UpdateScreen()  m_pD3dDev��NULL" );

	//	�V�[�����I��
	m_pD3dDev->EndScene();

	//	��ʂւ̔��f
	m_pD3dDev->Present( NULL, NULL, NULL, NULL );

	//	�V�[���̊J�n
	MyuAssert( m_pD3dDev->BeginScene(), D3D_OK,
		"CMglGraphicManager::BeginScene()  �V�[���̊J�n�Ɏ��s�B" );
}

/*
//	�V�[���̊J�n
void CMglGraphicManager::BeginScene()
{
	MyuAssert( m_pD3dDev->BeginScene(), D3D_OK,
		"CMglGraphicManager::BeginScene()  �V�[���̊J�n�Ɏ��s�B" );
}

//	�V�[���̏I��
void CMglGraphicManager::EndScene()
{
	m_pD3dDev->EndScene();
}

//	��ʂւ̔��f
void CMglGraphicManager::Present()
{
	m_pD3dDev->Present( NULL, NULL, NULL, NULL );
}
*/

//	�����J���p
void CMglGraphicManager::AddRefOfAutoRelease( CMyuReleaseBase* pRef )
{
	//	���ɖ������`�F�b�N
	if ( m_autoReleaseAry.find( pRef ) != m_autoReleaseAry.end() )
		MyuThrow( 0, "���Ƀ��t�@�����X 0x%08x �͑��݂��܂��B", pRef );

	//DEBUGLOG( "AutoRelease �p0x%08x ��ǉ����܂��B", pRef );
	m_autoReleaseAry[pRef] = pRef;
}
void CMglGraphicManager::RmRefOfAutoRelease( CMyuReleaseBase* pRef )
{
	//	���݂��邩�`�F�b�N
	AUTO_RELESE_ITR itr = m_autoReleaseAry.find( pRef );
	if ( itr == m_autoReleaseAry.end() )
	{
		/*
		char szWork[256];
		sprintf( szWork, "CMglGraphicManager::RmRefOfAutoRelease()  0x%08x �̃��t�@�����X�͑��݂��܂���B", pRef );
		MessageBox( NULL, szWork, NULL, NULL );
		*/
		return;
		//MyuThrow( 0, "CMglGraphicManager::RmRefOfAutoRelease()  0x%08x �̃��t�@�����X�͑��݂��܂���B", pRef );
	}

	//DEBUGLOG( "AutoRelease �p���t�@�����X 0x%08x ���폜���܂��B", pRef );
	m_autoReleaseAry.erase( pRef );
}

//	�X�v���C�g�`��
void CMglGraphicManager::SpriteDraw( CMglTexture *pTexture, float x, float y, CONST RECT* pSrcRect, D3DCOLOR color,
		float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	//	�`�F�b�N
	if ( m_pSprite == NULL )
		MyuThrow( 99, "CMglGraphicManage::SpriteDraw()  �X�v���C�g�������ɂȂ��Ă��邩�A�X�v���C�g�̏������Ɏ��s���܂����B" );
	if ( pTexture->GetDirect3dTexturePtr() == NULL )
		MyuThrow( 99, "CMglGraphicManage::SpriteDraw()  IDirect3DTexture8 ��NULL�ł��B�e�N�X�`��������������Ă��Ȃ��\��������܂��B" );

	//	2009/01/07
	SpriteBegin();

	////// �v�Z���� /////////////////////////////////

	//	srcRect��NULL���w�肳�ꂽ�ꍇ��BMP�S�Ă�RECT�Ɏw��
	RECT texFullRect;
	if ( pSrcRect == NULL )
	{
		ZeroMemory(&texFullRect,sizeof(texFullRect));

		//	�T�C�Y�ݒ�
		texFullRect.left = 0;
		texFullRect.top = 0;
		texFullRect.right = pTexture->GetBmpWidth();
		texFullRect.bottom = pTexture->GetBmpHeight();

		//	pSrcRect �Ƀ|�C���^��ݒ�
		pSrcRect = &texFullRect;
	}

	//	���S��_�G��@�\
	/*if ( m_bSpriteCenterDraw == TRUE )
	{
		int nSizeX = pSrcRect->right - pSrcRect->left;
		int nSizeY = pSrcRect->bottom - pSrcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}*/

	/* 2007/02/12 ����͑����v��Ȃ��i0.5f�w�肷��΂����j
	//	���S��_�G��@�\
	if ( fRotationCenterX == -1 )	{
		int nSizeX = pSrcRect->right - pSrcRect->left;
		x -= (nSizeX/2) * fScaleX;
	}
	if ( fRotationCenterY == -1 )	{
		int nSizeY = pSrcRect->bottom - pSrcRect->top;
		y -= (nSizeY/2) * fScaleY;
	}
	*/

	//	x, y��D3DXVECTOR2�\���̂Ɋi�[
	D3DXVECTOR2 vctPos;
	vctPos.x = x;
	vctPos.y = y;

	//	�X�P�[��
	D3DXVECTOR2 vctScale;
	vctScale.x = fScaleX;
	vctScale.y = fScaleY;

	//	��]�̒��S
	D3DXVECTOR2 vctRtCenter;
	vctRtCenter.x = (pSrcRect->right - pSrcRect->left) * fRotationCenterX * fScaleX;
	vctRtCenter.y = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY * fScaleY;

	/*	�X�v���C�g�̓A���t�@�I�v�V���������Ȃ����ۂ�
	//	�A���t�@�I�v�V����
	DWORD dwAlphaOptionBkup=0;
	if ( dwAlphaOption != MGL_ALPHA_OPT_NOCHANGE )
	{
		//	�߂����̂��߂Ƀo�b�N�A�b�v������Ă���
		dwAlphaOptionBkup = m_myudg->GetAlphaMode();
		m_myudg->SetAlphaMode( dwAlphaOption );
	}*/

	//	�p�x����Radian�ɁB�X�ɍ���]�ɂȂ��Ă���̂ŉE��]��
	float fRad = AngleToRad(-fAngle);

	//////////////////////////////////////////////////////////////////////////////

	//	�G��
	MyuAssert( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(),
		pSrcRect, &vctScale, &vctRtCenter, fRad, &vctPos, color ), D3D_OK,
		"CMglGraphicManager::SpriteDraw()  m_pSprite->Draw()�Ɏ��s" );
}

//	�X�v���C�g��Begin()
void CMglGraphicManager::SpriteBegin()
{
	if( m_pSprite != NULL && m_bSpriteBegun == FALSE ){
		MyuAssert( m_pSprite->Begin(), D3D_OK,
			"CMglGraphicManager::SpriteBegin()  m_pSprite->Begin()�Ɏ��s" );
		m_bSpriteBegun = TRUE;
	}
}
//	�X�v���C�g��End()
void CMglGraphicManager::SpriteEnd()
{
	if( m_pSprite != NULL && m_bSpriteBegun == TRUE ){
		MyuAssert( m_pSprite->End(), D3D_OK,
			"CMglGraphicManager::SpriteEnd()  m_pSprite->End()�Ɏ��s" );
		m_bSpriteBegun = FALSE;
	}
}

void CMglGraphicManager::DrawPrimitiveUpMyuVertex(MGL_VERTEX *pMglVertexs, int nVertexCount, D3DPRIMITIVETYPE primitiveType)
{
	MyuAssert( m_pD3dDev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, nVertexCount, pMglVertexs, sizeof(MGL_VERTEX)), D3D_OK,
			"CMglGraphicManager::DrawPrimitiveUpMyuVertexSquare()  DrawPrimitiveUP()�Ɏ��s" );
}
														

////////////////////////////////////////////////////////////
//
//	�f�t�H���g CMglGraphicManager �C���X�^���X�֘A
//
CMglGraphicManager* GetDefaultGd()
{
	CMglStackInstance("CMglGraphicManager::GetDefaultGd");
	if ( g_pDefaultGd == NULL )
	{
		MyuThrow2( 0, MGLMSGNO_GRP_MANAGER_MULTI_INSTANCE,
			"CMglGraphicManager �̃C���X�^���X�����݂��Ȃ����������݂��邽�ߏȗ����鎖�͏o���܂���B" );
	}
	return g_pDefaultGd;
}
