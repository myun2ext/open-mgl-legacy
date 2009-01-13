#include "stdafx.h"
#include "MglD3dCapsDumper.h"
#include "MglManager.h"


////////////////////////////////////////////////////////////////////////
//
//		Caps�̃_���v
//
////////////////////////////////////////////////////////////////////////

//void CMglD3dCapsDumper::DumpAdapterInfo( D3DCAPS8* pCapsHal, D3DCAPS8* pCapsRef )
void CMglD3dCapsDumper::DumpAdapterInfo( _IDirect3DX* m_pD3d, _D3DCAPSx* pCaps )
{
	_MGL_DEBUGLOG( "+ CMglD3dCapsDumper::DumpAdapterInfo()" );

	FILE *fp=fopen( CAPS_DUMP_LOG, "w" );
	if ( fp == NULL )
		MyuThrow( 0, "CMglD3dCapsDumper::DumpCapsAll()  ���O�t�@�C���̃I�[�v���Ɏ��s�B" );


	fprintf( fp, "==== AdapterInfo =================================\n\n" );
	for( int i=0; i<m_pD3d->GetAdapterCount(); i++ )
	{
		_D3DADAPTER_IDENTIFIERx adapterInfo;
		//m_pD3d->GetAdapterIdentifier( i, 0, &adapterInfo );
#if _MGL_DXVER == 9
		m_pD3d->GetAdapterIdentifier( i, 0, &adapterInfo );
#else
		m_pD3d->GetAdapterIdentifier( i, D3DENUM_NO_WHQL_LEVEL, &adapterInfo );
#endif

		fprintf( fp, "Description :              %s\n", adapterInfo.Description );
		fprintf( fp, "Driver :                   %s\n", adapterInfo.Driver );
		fprintf( fp, "DriverVersion :            %d,%u\n\n", adapterInfo.DriverVersion.HighPart, adapterInfo.DriverVersion.LowPart );
	}

	//fprintf( fp, "\n\n==== HAL =========================================\n\n" );
	fprintf( fp, "\n\n==== Caps =========================================\n\n" );
	DumpCaps( fp, pCaps );

	/*
	fprintf( fp, "\n\n==== REF =========================================\n\n" );
	DumpCaps( fp, pCapsRef );*/
  
	fclose( fp );

	_MGL_DEBUGLOG( "- CMglD3dCapsDumper::DumpAdapterInfo()" );
}

void CMglD3dCapsDumper::DumpCaps( FILE *fp, _D3DCAPSx* caps )
{
	fprintf( fp, "DeviceType :               %u\n", caps->DeviceType );
	fprintf( fp, "AdapterOrdinal :           %u\n\n", caps->AdapterOrdinal );

	fprintf( fp, "Caps :                     0x%08x\n", caps->Caps );
	fprintf( fp, "Caps2 :                    0x%08x\n", caps->Caps2 );
	fprintf( fp, "Caps3 :                    0x%08x\n\n", caps->Caps3 );

	////////////////////////////////////////////////////////////////////////////////////

	DumpFlagItem( fp, caps->Caps2, D3DCAPS2_CANMANAGERESOURCE, "Driver Manage Resource" );

	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_CANBLTSYSTONONLOCAL, "CanBLTSYSTONONLOCAL" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_CANRENDERAFTERFLIP, "CanRENDERAFTERFLIP" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_DRAWPRIMTLVERTEX, "DrawPrimitive HAL Export" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_EXECUTESYSTEMMEMORY, "Execute SYSTEM MEMORY" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_EXECUTEVIDEOMEMORY, "EXECUTE VIDEO MEMORY" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_HWRASTERIZATION, "HW RASTERIZATION" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_HWTRANSFORMANDLIGHT, "HW TRANSFORM AND LIGHT" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_NPATCHES, "NPATCHES" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_PUREDEVICE, "PURE DEVICE" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_QUINTICRTPATCHES, "QUINTICRTPATCHES" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_RTPATCHES, "RTPATCHES" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_RTPATCHHANDLEZERO, "RTPATCHHANDLEZERO" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_SEPARATETEXTUREMEMORIES, "SEPARATETEXTUREMEMORIES" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_TEXTURENONLOCALVIDMEM, "TEXTURE NON LOCAL VID MEM" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_TEXTURESYSTEMMEMORY, "TEXTURE SYSTEM MEMORY" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_TEXTUREVIDEOMEMORY, "TEXTURE VIDEO MEMORY" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_TLVERTEXSYSTEMMEMORY, "TL VERTEX SYSTE MMEMORY" );
	DumpFlagItem( fp, caps->DevCaps, D3DDEVCAPS_TLVERTEXVIDEOMEMORY, "TL VERTEX VIDEO MEMORY" );
	fprintf( fp, "\n" );

/*
DevCaps 
�f�o�C�X�̔\�͂������t���O�B 
D3DDEVCAPS_CANBLTSYSTONONLOCAL 
�f�o�C�X�́A�V�X�e�������� �e�N�X�`������񃍁[�J�� �r�f�I������ �e�N�X�`���ւ̃u���b�g���T�|�[�g����B 
D3DDEVCAPS_CANRENDERAFTERFLIP 
�f�o�C�X�́A�y�[�W �t���b�v�̌�ŁA�����_�����O �R�}���h���L���[�ɓ���邱�Ƃ��ł���B���̃t���O�̓A�v���P�[�V�����̓����ς�����̂ł͂Ȃ��B�P�Ƀf�o�C�X����r�I�����ł��邱�Ƃ��������̂ł���B 
D3DDEVCAPS_DRAWPRIMTLVERTEX 
�f�o�C�X�́ADrawPrimitive �Ή��̃n�[�h�E�F�A �A�u�X�g���N�V���� ���C�� (HAL) ���G�N�X�|�[�g����B 
D3DDEVCAPS_EXECUTESYSTEMMEMORY 
�f�o�C�X�́A�V�X�e�� �������ɂ�����s�o�b�t�@���g�p�ł���B 
D3DDEVCAPS_EXECUTEVIDEOMEMORY 
�f�o�C�X�́A�r�f�I �������ɂ�����s�o�b�t�@���g�p�ł���B 
D3DDEVCAPS_HWRASTERIZATION 
�f�o�C�X�ɂ́A�V�[���̃��X�^���p�̃n�[�h�E�F�A �A�N�Z�����[�V����������B 
D3DDEVCAPS_HWTRANSFORMANDLIGHT 
�f�o�C�X�́A�n�[�h�E�F�A�Ńg�����X�t�H�[�� & ���C�e�B���O���T�|�[�g�ł���B 
D3DDEVCAPS_NPATCHES 
�f�o�C�X�́AN �p�b�`���T�|�[�g����B 
D3DDEVCAPS_PUREDEVICE 
�f�o�C�X�́A�n�[�h�E�F�A�Ń��X�^���A�g�����X�t�H�[���A���C�e�B���O�A����уV�F�[�f�B���O���T�|�[�g�ł���B 
D3DDEVCAPS_QUINTICRTPATCHES 
�f�o�C�X�́A5 ���x�W�F����� B �X�v���C�����T�|�[�g���Ă���B 
D3DDEVCAPS_RTPATCHES 
�f�o�C�X�́A��`����юO�p�`�p�b�`���T�|�[�g���Ă���B 
D3DDEVCAPS_RTPATCHHANDLEZERO 
���̃f�o�C�X�\�͂��ݒ肳��Ă���ꍇ�A�n�[�h�E�F�A �A�[�L�e�N�`���ŏ����L���b�V������K�v���Ȃ��A�L���b�V������Ă��Ȃ��p�b�` (�n���h�� 0) �́A�L���b�V�����ꂽ�p�b�`�Ɠ��l�A�����I�ɕ`�悳���BD3DDEVCAPS_RTPATCHHANDLEZERO �̐ݒ�̓n���h�� 0 �̃p�b�`���`��ł��邱�Ƃ��Ӗ�����̂ł͂Ȃ����Ƃɒ��ӂ��邱�ƁB�n���h�� 0 �̃p�b�`�́A���̔\�͂��ݒ肳��Ă��邩�ǂ����Ɋ֌W�Ȃ��A��ɕ`��ł���B 
D3DDEVCAPS_SEPARATETEXTUREMEMORIES 
�f�o�C�X�́A�Ɨ����������� �v�[������e�N�X�`���������s���Ă���B 
D3DDEVCAPS_TEXTURENONLOCALVIDMEM 
�f�o�C�X�́A�񃍁[�J�� �r�f�I ����������e�N�X�`�����擾�ł���B 
D3DDEVCAPS_TEXTURESYSTEMMEMORY 
�f�o�C�X�́A�V�X�e�� ����������e�N�X�`�����擾�ł���B 
D3DDEVCAPS_TEXTUREVIDEOMEMORY 
�f�o�C�X�́A�f�o�C�X ����������e�N�X�`�����擾�ł���B 
D3DDEVCAPS_TLVERTEXSYSTEMMEMORY 
�f�o�C�X�́A�g�����X�t�H�[���ς݃��C�e�B���O�ς݂̒��_�p�ɁA�V�X�e�� �������̃o�b�t�@���g�p�ł���B 
D3DDEVCAPS_TLVERTEXVIDEOMEMORY 
�f�o�C�X�́A�g�����X�t�H�[���ς݃��C�e�B���O�ς݂̒��_�p�ɁA�r�f�I �������̃o�b�t�@���g�p�ł���B 
*/

	////////////////////////////////////////////////////////////////////////////////////

	fprintf( fp, "PresentationIntervals :    0x%08x\n", caps->PresentationIntervals );
	fprintf( fp, "CursorCaps :               0x%08x\n", caps->CursorCaps );
	fprintf( fp, "DevCaps :                  0x%08x\n\n", caps->DevCaps );

	fprintf( fp, "MaxTextureWidth :          %u\n", caps->MaxTextureWidth );
	fprintf( fp, "MaxTextureHeight :         %u\n", caps->MaxTextureHeight );
	fprintf( fp, "MaxTextureRepeat :         %u\n", caps->MaxTextureRepeat );
	fprintf( fp, "MaxTextureAspectRatio :    %u\n\n", caps->MaxTextureAspectRatio );

	fprintf( fp, "TextureOpCaps :            0x%08x\n\n", caps->TextureOpCaps );


/*
    /* Device Info *
    D3DDEVTYPE  DeviceType;
    UINT    AdapterOrdinal;

    /* Caps from DX7 Draw *
    DWORD   Caps;
    DWORD   Caps2;
    DWORD   Caps3;
    DWORD   PresentationIntervals;

    /* Cursor Caps *
    DWORD   CursorCaps;

    /* 3D Device Caps *
    DWORD   DevCaps;

    DWORD   PrimitiveMiscCaps;
    DWORD   RasterCaps;
    DWORD   ZCmpCaps;
    DWORD   SrcBlendCaps;
    DWORD   DestBlendCaps;
    DWORD   AlphaCmpCaps;
    DWORD   ShadeCaps;
    DWORD   TextureCaps;
    DWORD   TextureFilterCaps;          // D3DPTFILTERCAPS for IDirect3DTexture8's
    DWORD   CubeTextureFilterCaps;      // D3DPTFILTERCAPS for IDirect3DCubeTexture8's
    DWORD   VolumeTextureFilterCaps;    // D3DPTFILTERCAPS for IDirect3DVolumeTexture8's
    DWORD   TextureAddressCaps;         // D3DPTADDRESSCAPS for IDirect3DTexture8's
    DWORD   VolumeTextureAddressCaps;   // D3DPTADDRESSCAPS for IDirect3DVolumeTexture8's

    DWORD   LineCaps;                   // D3DLINECAPS

    DWORD   MaxTextureWidth, MaxTextureHeight;
    DWORD   MaxVolumeExtent;

    DWORD   MaxTextureRepeat;
    DWORD   MaxTextureAspectRatio;
    DWORD   MaxAnisotropy;
    float   MaxVertexW;

    float   GuardBandLeft;
    float   GuardBandTop;
    float   GuardBandRight;
    float   GuardBandBottom;

    float   ExtentsAdjust;
    DWORD   StencilCaps;

    DWORD   FVFCaps;
    DWORD   TextureOpCaps;
    DWORD   MaxTextureBlendStages;
    DWORD   MaxSimultaneousTextures;

    DWORD   VertexProcessingCaps;
    DWORD   MaxActiveLights;
    DWORD   MaxUserClipPlanes;
    DWORD   MaxVertexBlendMatrices;
    DWORD   MaxVertexBlendMatrixIndex;

    float   MaxPointSize;

    DWORD   MaxPrimitiveCount;          // max number of primitives per DrawPrimitive call
    DWORD   MaxVertexIndex;
    DWORD   MaxStreams;
    DWORD   MaxStreamStride;            // max stride for SetStreamSource

    DWORD   VertexShaderVersion;
    DWORD   MaxVertexShaderConst;       // number of vertex shader constant registers

    DWORD   PixelShaderVersion;
    float   MaxPixelShaderValue;        // max value of pixel shader arithmetic component
*/
}

void CMglD3dCapsDumper::DumpFlagItem( FILE *fp, DWORD dwValue, DWORD dwMask, const char* szName )
{
	if ( dwValue & dwMask )
		fprintf( fp, "%30s :   true\n", szName );
	else
		fprintf( fp, "%30s :   false\n", szName );

}

/*
//	DirectDraw���g���ăf�B�X�v���C�T�C�Y���擾
void CMglD3dCapsDumper::GetVramInfo( DWORD *dwpTotal, DWORD *dwpFree )
{
	//�f�B�X�v���C�h���C�o
	IDirectDraw7* pDDraw=NULL;
	MyuAssert( DirectDrawCreateEx(NULL,(void**)(&pDDraw),IID_IDirectDraw7,NULL), DD_OK,
		"CMglD3dCapsDumper::GetVramInfo()  DirectDrawCreateEx()�Ɏ��s�B" );

	//VRAM
	DDSCAPS2 ddsCaps2; 
	ZeroMemory(&ddsCaps2, sizeof(ddsCaps2)); 
	ddsCaps2.dwCaps=DDSCAPS_VIDEOMEMORY; 

	MyuAssert( pDDraw->GetAvailableVidMem( &ddsCaps2, dwpTotal, dwpFree ), DD_OK,
		"CMglD3dCapsDumper::GetVramInfo()  pDDraw->GetAvailableVidMem()�Ɏ��s�B" );

	SAFE_RELEASE(pDDraw);
}
*/