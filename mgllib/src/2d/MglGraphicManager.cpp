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
#include "Mgl3dManager.h"

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
	p3d = NULL;
	m_nDispX = 0;
	m_nDispY = 0;
	ZeroMemory( &m_formatTexture, sizeof(m_formatTexture) ); 
	m_dwD3dDeviceFlg = 0;
	m_d3dDevType = D3DDEVTYPE_FORCE_DWORD;
	m_dwAlphaOption = MGL_ALPHA_OPT_TRANSLUCENCE;
	m_bUse3d = FALSE;

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
void CMglGraphicManager::Init( HWND hWnd, int nDispX, int nDispY, BOOL bFullscreen, BOOL bUse3d,
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
	_D3DCAPSx caps;
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

		m_d3dDevType = D3DDEVTYPE_REF;	//	2009/02/09
	}
	else{
		_MGL_DEBUGLOG( "HAL�f�o�C�X�̎擾�ɐ���" );
		m_d3dDevType = D3DDEVTYPE_HAL;	//	2009/02/09
	}
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
		MyuThrow( MGLMSGNO_GRPMGR(20), "��ʂ̐F��16bit�ȏ�ɂ��Ă��������B" );

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

/*
	//	�X�e���V���n
	MyuAssert( this->m_pD3d->CheckDeviceFormat( nAdapterNo, D3DDEVTYPE_HAL, dispMode.Format,
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 ), D3D_OK,
		"�X�e���V���s��" );

	MyuAssert( this->m_pD3d->CheckDeviceFormat( nAdapterNo, D3DDEVTYPE_HAL, dispMode.Format,
		D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, dispMode.Format ), D3D_OK,
		"�����_�[�s��" );
	 
*/
	//	2009/01/31 Z�X�e���V���i3D�j�Ή�
	dumper.DumpDepthStencilTest( m_pD3d, nAdapterNo, dispMode.Format, m_d3dDevType );
	if ( bUse3d ){
		D3DFORMAT depthStencilFormat = D3DFMT_D16;

		/*if ( CheckDepthStencilFormat(nAdapterNo, dispMode.Format, D3DFMT_D32, m_d3dDevType ) == TRUE ) {
			depthStencilFormat = D3DFMT_D32;
			_MGL_DEBUGLOG( "DepthStencilFormat�Ƃ���D3DFMT_D32���g�p���܂��B" );
		}
		else*/ if ( CheckDepthStencilFormat(nAdapterNo, dispMode.Format, D3DFMT_D24S8, m_d3dDevType ) == TRUE ) {
			depthStencilFormat = D3DFMT_D24S8;
			_MGL_DEBUGLOG( "DepthStencilFormat�Ƃ���D3DFMT_D24S8���g�p���܂��B" );
		}
		else if ( CheckDepthStencilFormat(nAdapterNo, dispMode.Format, D3DFMT_D24X8, m_d3dDevType ) == TRUE ) {
			depthStencilFormat = D3DFMT_D24X8;
			_MGL_DEBUGLOG( "DepthStencilFormat�Ƃ���D3DFMT_D24X8���g�p���܂��B" );
		}
		else if ( CheckDepthStencilFormat(nAdapterNo, dispMode.Format, D3DFMT_D16, m_d3dDevType ) == TRUE ) {  
			depthStencilFormat = D3DFMT_D16;
			_MGL_DEBUGLOG( "DepthStencilFormat�Ƃ���D3DFMT_D16���g�p���܂��B" );
		}

		if ( depthStencilFormat != D3DFMT_UNKNOWN ) {
			presentParam.EnableAutoDepthStencil = TRUE;
			presentParam.AutoDepthStencilFormat = depthStencilFormat;
		}
		else
			EzErrBox(hWnd, "���̃f�o�C�X�ł�Z�o�b�t�@�e�X�g���L���ɏo���܂���B�����3D�I�u�W�F�N�g���\������Ȃ��\��������܂��B");
	}
	m_bUse3d = bUse3d;

    //DWORD           Flags;
    //UINT            FullScreen_PresentationInterval;

	//	Ex�ł̌Ăяo��
	InitEx( &presentParam, dwD3dDeviceMode, formatTexture, nAdapterNo );

	//	2009/01/31 3D�Ή�
	if ( bUse3d ){
		Enable3d();
	}

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

void CMglGraphicManager::Enable3d()
{
	p3d = new CMgl3DManager();
	p3d->Init(this);
}

void CMglGraphicManager::InitSprite()
{
	if ( m_pD3dDev == NULL )
		MyuThrow( MGLMSGNO_GRPMGR(80), "CMglGraphicManager::InitSprite()  m_pD3dDev��NULL" );
	if ( m_pSprite != NULL )	//	���ɂ���΃X�L�b�v
		return;

	MyuAssert2( D3DXCreateSprite( m_pD3dDev, &m_pSprite ), D3D_OK,
		MGLMSGNO_GRPMGR(81), "CMglGraphicManager::Init()  D3DXCreateSprite()�Ɏ��s" );
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
#if _MGL_DXVER == 8
	m_pD3d = Direct3DCreate8( D3D_SDK_VERSION );
#else
	m_pD3d = Direct3DCreate9( D3D_SDK_VERSION );
#endif
	if ( NULL == m_pD3d )
		MyuThrow2( MGLMSGNO_GRPMGR(40), MGLMSGNO_GRP_MANAGER_D3DCREATE_FAILED,
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

	//	2007/07/15  REF�T�|�[�g
	if ( dwD3dDeviceMode == D3D_DEVICE_FLG_REF ){
		_MGL_DEBUGLOG( "dwD3dDeviceMode��D3D_DEVICE_FLG_REF�ł��B" );
		if ( D3dCreateDevice( D3D_DEVICE_FLG_REF, pPresentParam, nAdapterNo, hFocusWindow ) != TRUE )
			//MyuThrow( 0, "�w�肳�ꂽ�f�o�C�X���[�h(dwD3dDeviceMode=0x%08X)�̓T�|�[�g����Ă��܂���B\r\nDirect3D�f�o�C�X�̐����Ɏ��s���܂����B", dwD3dDeviceMode );
			MyuThrow( MGLMSGNO_GRPMGR(41), "Direct3D�f�o�C�X�̐����Ɏ��s���܂����B\r\n"
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
			MyuThrow( MGLMSGNO_GRPMGR(43), "Direct3D�f�o�C�X�̐����Ɏ��s���܂����B\r\n"
				"dwD3dDeviceMode=0x%08X", dwD3dDeviceMode );
	}


	//	VRAM�������O�ɏo��
	m_nTexMem = m_pD3dDev->GetAvailableTextureMem();
	_MGL_DEBUGLOG( "AvailableTextureMemory = %u KB", (int)(m_nTexMem/1024) );

	//	Vertex��ݒ�
	SetupMyuVertex();

	//	�o�b�N�o�b�t�@�̏����擾
	MyuAssert2( GetBackBuffer()->GetDesc( &backBufferDesc ), D3D_OK,
		MGLMSGNO_GRPMGR(44), "CMglGraphicManager::Init()  GetBackBuffer()->GetDesc()�Ɏ��s" );

	//	�A���t�@�u�����h��L���ɂ��Ă���
	SetAlphaMode();

	//	�V�[�����J�n���Ă���
	MyuAssert2( m_pD3dDev->BeginScene(), D3D_OK,
		MGLMSGNO_GRPMGR(46), "CMglGraphicManager::Init()  �V�[���̊J�n�Ɏ��s�B" );

	//	�o�b�N�o�b�t�@���N���A���Ă���
	Clear();

	_MGL_DEBUGLOG( "- CMglGraphicManager::InitEx()" );
}

//	Vertex��ݒ�
void CMglGraphicManager::SetFVF(DWORD dwFvf)
{
#if _MGL_DXVER == 8
	MyuAssert2( this->m_pD3dDev->SetVertexShader( dwFvf ), D3D_OK,
		MGLMSGNO_GRPMGR(93), "CMglGraphicManager::SetFVF()  m_pD3dDev->SetVertexShader()�Ɏ��s" );
#else
	MyuAssert2( this->m_pD3dDev->SetFVF( dwFvf ), D3D_OK,
		MGLMSGNO_GRPMGR(93), "CMglGraphicManager::SetFVF()  m_pD3dDev->SetFVF()�Ɏ��s" );
#endif
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
		MyuThrow( MGLMSGNO_GRPMGR(62), "CMglGraphicManager::D3dCreateDevice() �s���ȃf�o�C�X�t���O�ł��B(dwD3dDeviceFlg=0x%08X)", dwD3dDeviceFlg );
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

	if ( m_bUse3d )
		MyuAssert2( m_pD3dDev->Clear( 0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 ), D3D_OK,
			MGLMSGNO_GRPMGR(111), "CMglGraphicManager::Clear()  m_pD3dDev->Clear()�Ɏ��s" );
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
    MyuAssert2( m_pD3dDev->Clear( rectCount, (D3DRECT*)rect, D3DCLEAR_TARGET, color, 1.0f, 0 ), D3D_OK,
		MGLMSGNO_GRPMGR(110), "CMglGraphicManager::Clear()  m_pD3dDev->Clear()�Ɏ��s" );
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
		MyuThrow( MGLMSGNO_GRPMGR(69), "CMglGraphicManager::SetAlphaMode()  m_pD3dDev��NULL" );

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
		MyuThrow( MGLMSGNO_GRPMGR(30), "CMglGraphicManager::UpdateScreen()  m_pD3dDev��NULL" );

	//	�V�[�����I��
	m_pD3dDev->EndScene();

	//	��ʂւ̔��f
	m_pD3dDev->Present( NULL, NULL, NULL, NULL );

	//	�V�[���̊J�n
	MyuAssert2( m_pD3dDev->BeginScene(), D3D_OK,
		MGLMSGNO_GRPMGR(31), "CMglGraphicManager::BeginScene()  �V�[���̊J�n�Ɏ��s�B" );
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
		return;
	//	MyuThrow( MGLMSGNO_GRPMGR(253), "���Ƀ��t�@�����X 0x%08x �͑��݂��܂��B", pRef );

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
		MyuThrow( MGLMSGNO_GRPMGR(83), "CMglGraphicManage::SpriteDraw()  �X�v���C�g�������ɂȂ��Ă��邩�A�X�v���C�g�̏������Ɏ��s���܂����B" );
	if ( pTexture->GetDirect3dTexturePtr() == NULL )
		MyuThrow( MGLMSGNO_GRPMGR(84), "CMglGraphicManage::SpriteDraw()  IDirect3DTexture8 ��NULL�ł��B�e�N�X�`��������������Ă��Ȃ��\��������܂��B" );

	//	2009/01/07
	SpriteBegin();

	////// �v�Z���� /////////////////////////////////

	//	srcRect��NULL���w�肳�ꂽ�ꍇ��BMP�S�Ă�RECT�Ɏw��
	RECT texFullRect;
	if ( pSrcRect == NULL ||
		pSrcRect->left == pSrcRect->right || pSrcRect->top == pSrcRect->bottom ) // 2009/03/31
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


	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
	//	DirectX 9
	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//#if _MGL_DXVER == 9
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXSPRITE_CHANGED
	//	DirectX9�̏ꍇ�͂��[��Ȋ����炵���B

	//	�g��E�k��
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, fScaleX, fScaleY, 0.0f);

	//	��]�̒��S
	//float fCenterX = (pSrcRect->right - pSrcRect->left) * fRotationCenterX * fScaleX;
	//float fCenterY = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY * fScaleY;
	float fCenterX = (pSrcRect->right - pSrcRect->left) * fRotationCenterX;
	float fCenterY = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY;
	D3DXMATRIX matTrans1;
	D3DXMATRIX matTrans2;
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans1, fCenterX, fCenterY, 0);
	D3DXMatrixTranslation(&matTrans2, -fCenterX, -fCenterY, 0);
	D3DXMatrixTranslation(&matTrans, x, y, 0);

	//	�p�x
	D3DXMATRIX matRotation;
	D3DXMatrixRotationZ(&matRotation, D3DXToRadian(fAngle));

	//	����
	/*D3DXMATRIX matrix1;
	D3DXMATRIX matrix;
	D3DXMatrixMultiply(&matrix1, &matRotation, &matTrans);
	D3DXMatrixMultiply(&matrix, &matrix1, &matScale);*/
//	D3DXMATRIX matrix = matTrans2 * matRotation * matTrans1 * matScale * matTrans;
	//D3DXMATRIX matrix = matTrans2 * matRotation * matTrans1 * matScale * matTrans;
	D3DXMATRIX matrix = matTrans1;

/*	
D3DXMATRIX *WINAPI D3DXMatrixTransformation2D(
	&matrix,
	&D3DXVECTOR2(0.5f,0.5f),
	FLOAT ScalingRotation,
	CONST D3DXVECTOR2 * pScaling,
	CONST D3DXVECTOR2 * pRotationCenter,
	FLOAT Rotation,
	CONST D3DXVECTOR2 * pTranslation
);
*/
	//int nWidth = pSrcRect;

	D3DXMatrixTransformation2D(&matrix,
		//&D3DXVECTOR2(200,200),
		&D3DXVECTOR2(0,0),
		0,
		&D3DXVECTOR2(fScaleX,fScaleY),
		&D3DXVECTOR2(0,0),//&D3DXVECTOR2(0.5f,0.5f),
		D3DXToRadian(fAngle),
		//&D3DXVECTOR2(x,y));
		&D3DXVECTOR2(x+fCenterX*fScaleX,y+fCenterY*fScaleY));

	//	�g�����X�t�H�[���Ƃ��Ĕ��f
	MyuAssert2( m_pSprite->SetTransform(&matrix), D3D_OK,
		MGLMSGNO_GRPMGR(85), "CMglGraphicManager::SpriteDraw()  m_pSprite->SetTransform()�Ɏ��s" );

	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(), pSrcRect, 
					 &D3DXVECTOR3(fCenterX, fCenterY, 0),
//					 &D3DXVECTOR3(0.5f, 0.5f, 0),
					 NULL, color), D3D_OK,
					 //&D3DXVECTOR3(fCenterX, fCenterY, 0), color), D3D_OK,
		MGLMSGNO_GRPMGR(86), "CMglGraphicManager::SpriteDraw()  m_pSprite->Draw()�Ɏ��s" );

//	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(), NULL, NULL, NULL, color), D3D_OK,
//		MGLMSGNO_GRPMGR(86), "CMglGraphicManager::SpriteDraw()  m_pSprite->Draw()�Ɏ��s" );

	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
	//	DirectX 8
	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
#else
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
	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(),
		pSrcRect, &vctScale, &vctRtCenter, fRad, &vctPos, color ), D3D_OK,
		MGLMSGNO_GRPMGR(87), "CMglGraphicManager::SpriteDraw()  m_pSprite->Draw()�Ɏ��s" );
#endif
}

//	�X�v���C�g��Begin()
void CMglGraphicManager::SpriteBegin()
{
	if( m_pSprite == NULL )
		MyuThrow(MGLMSGNO_GRPMGR(91), "Sprite���쐬����Ă��܂���B");

	if( m_pSprite != NULL && m_bSpriteBegun == FALSE ){
//#if _MGL_DXVER == 9
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXSPRITE_CHANGED
		MyuAssert2( m_pSprite->Begin(0), D3D_OK,
#else
		MyuAssert2( m_pSprite->Begin(), D3D_OK,
#endif
			MGLMSGNO_GRPMGR(89), "CMglGraphicManager::SpriteBegin()  m_pSprite->Begin()�Ɏ��s" );
		m_bSpriteBegun = TRUE;
	}
}
//	�X�v���C�g��End()
void CMglGraphicManager::SpriteEnd()
{
	if( m_pSprite == NULL )
		MyuThrow(MGLMSGNO_GRPMGR(92), "Sprite���쐬����Ă��܂���B");

	if( m_pSprite != NULL && m_bSpriteBegun == TRUE ){
		MyuAssert2( m_pSprite->End(), D3D_OK,
			MGLMSGNO_GRPMGR(90), "CMglGraphicManager::SpriteEnd()  m_pSprite->End()�Ɏ��s" );
		m_bSpriteBegun = FALSE;
	}
}

void CMglGraphicManager::DrawPrimitiveUpMyuVertex(MGL_VERTEX *pMglVertexs, int nVertexCount, D3DPRIMITIVETYPE primitiveType)
{
	MyuAssert2( m_pD3dDev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, nVertexCount, pMglVertexs, sizeof(MGL_VERTEX)), D3D_OK,
			MGLMSGNO_GRPMGR(130), "CMglGraphicManager::DrawPrimitiveUpMyuVertexSquare()  DrawPrimitiveUP()�Ɏ��s" );
}

//	Z�o�b�t�@�̃t�H�[�}�b�g�Ή��󋵂��`�F�b�N
BOOL CMglGraphicManager::CheckDepthStencilFormat( UINT nAdapterNo,
	D3DFORMAT displayFormat, D3DFORMAT targetDsFormat, D3DDEVTYPE deviceType )
{
	//	�X�e���V���n
	/*MyuAssert( this->m_pD3d->CheckDeviceFormat( nAdapterNo, D3DDEVTYPE_HAL, dispMode.Format,
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 ), D3D_OK,
		"�X�e���V���s��" );*/

	return m_pD3d->CheckDeviceFormat( nAdapterNo,
		deviceType, displayFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, targetDsFormat ) == S_OK ? TRUE : FALSE;
}

D3DFORMAT CMglGraphicManager::CheckAutoDepthStencilFormat( UINT nAdapterNo,
	D3DFORMAT displayFormat, D3DDEVTYPE deviceType )
{
	D3DFORMAT depthStencilFormat = D3DFMT_D16;

	if ( CheckDepthStencilFormat(nAdapterNo, displayFormat, D3DFMT_D24S8, deviceType ) == TRUE )
		depthStencilFormat = D3DFMT_D24S8;
	else if ( CheckDepthStencilFormat(nAdapterNo, displayFormat, D3DFMT_D24X8, deviceType ) == TRUE ) 
		depthStencilFormat = D3DFMT_D24X8;
	
	return depthStencilFormat;
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
		MyuThrow2( MGLMSGNO_GRPMGR(196), MGLMSGNO_GRP_MANAGER_MULTI_INSTANCE,
			"CMglGraphicManager �̃C���X�^���X�����݂��Ȃ����������݂��邽�ߏȗ����鎖�͏o���܂���B" );
	}
	return g_pDefaultGd;
}

BOOL CheckDefaultGd()
{
	if ( g_pDefaultGd == NULL )
		return FALSE;
	return TRUE;
}
