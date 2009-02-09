#include "stdafx.h"
#include "MglD3dCapsDumper.h"
#include "MglManager.h"


////////////////////////////////////////////////////////////////////////
//
//		Capsのダンプ
//
////////////////////////////////////////////////////////////////////////

//void CMglD3dCapsDumper::DumpAdapterInfo( D3DCAPS8* pCapsHal, D3DCAPS8* pCapsRef )
void CMglD3dCapsDumper::DumpAdapterInfo( _IDirect3DX* m_pD3d, _D3DCAPSx* pCaps )
{
	_MGL_DEBUGLOG( "+ CMglD3dCapsDumper::DumpAdapterInfo()" );

	FILE *fp=fopen( CAPS_DUMP_LOG, "w" );
	if ( fp == NULL )
		MyuThrow( 0, "CMglD3dCapsDumper::DumpCapsAll()  ログファイルのオープンに失敗。" );


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
	switch( caps->DeviceType )
	{
	case D3DDEVTYPE_HAL:
		fprintf( fp, "DeviceType :               D3DDEVTYPE_HAL\n" );
		break;
	case D3DDEVTYPE_REF:
		fprintf( fp, "DeviceType :               D3DDEVTYPE_REF\n" );
		break;
	case D3DDEVTYPE_SW:
		fprintf( fp, "DeviceType :               D3DDEVTYPE_SW\n" );
		break;
	}
	//fprintf( fp, "DeviceType :               %u\n", caps->DeviceType );
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
デバイスの能力を示すフラグ。 
D3DDEVCAPS_CANBLTSYSTONONLOCAL 
デバイスは、システムメモリ テクスチャから非ローカル ビデオメモリ テクスチャへのブリットをサポートする。 
D3DDEVCAPS_CANRENDERAFTERFLIP 
デバイスは、ページ フリップの後で、レンダリング コマンドをキューに入れることができる。このフラグはアプリケーションの動作を変えるものではない。単にデバイスが比較的高速であることを示すものである。 
D3DDEVCAPS_DRAWPRIMTLVERTEX 
デバイスは、DrawPrimitive 対応のハードウェア アブストラクション レイヤ (HAL) をエクスポートする。 
D3DDEVCAPS_EXECUTESYSTEMMEMORY 
デバイスは、システム メモリにある実行バッファを使用できる。 
D3DDEVCAPS_EXECUTEVIDEOMEMORY 
デバイスは、ビデオ メモリにある実行バッファを使用できる。 
D3DDEVCAPS_HWRASTERIZATION 
デバイスには、シーンのラスタ化用のハードウェア アクセラレーションがある。 
D3DDEVCAPS_HWTRANSFORMANDLIGHT 
デバイスは、ハードウェアでトランスフォーム & ライティングをサポートできる。 
D3DDEVCAPS_NPATCHES 
デバイスは、N パッチをサポートする。 
D3DDEVCAPS_PUREDEVICE 
デバイスは、ハードウェアでラスタ化、トランスフォーム、ライティング、およびシェーディングをサポートできる。 
D3DDEVCAPS_QUINTICRTPATCHES 
デバイスは、5 次ベジェおよび B スプラインをサポートしている。 
D3DDEVCAPS_RTPATCHES 
デバイスは、矩形および三角形パッチをサポートしている。 
D3DDEVCAPS_RTPATCHHANDLEZERO 
このデバイス能力が設定されている場合、ハードウェア アーキテクチャで情報をキャッシュする必要がなく、キャッシュされていないパッチ (ハンドル 0) は、キャッシュされたパッチと同様、効率的に描画される。D3DDEVCAPS_RTPATCHHANDLEZERO の設定はハンドル 0 のパッチが描画できることを意味するのではないことに注意すること。ハンドル 0 のパッチは、この能力が設定されているかどうかに関係なく、常に描画できる。 
D3DDEVCAPS_SEPARATETEXTUREMEMORIES 
デバイスは、独立したメモリ プールからテクスチャ処理を行っている。 
D3DDEVCAPS_TEXTURENONLOCALVIDMEM 
デバイスは、非ローカル ビデオ メモリからテクスチャを取得できる。 
D3DDEVCAPS_TEXTURESYSTEMMEMORY 
デバイスは、システム メモリからテクスチャを取得できる。 
D3DDEVCAPS_TEXTUREVIDEOMEMORY 
デバイスは、デバイス メモリからテクスチャを取得できる。 
D3DDEVCAPS_TLVERTEXSYSTEMMEMORY 
デバイスは、トランスフォーム済みライティング済みの頂点用に、システム メモリのバッファを使用できる。 
D3DDEVCAPS_TLVERTEXVIDEOMEMORY 
デバイスは、トランスフォーム済みライティング済みの頂点用に、ビデオ メモリのバッファを使用できる。 
*/

	////////////////////////////////////////////////////////////////////////////////////

	fprintf( fp, "PresentationIntervals :    0x%08x\n", caps->PresentationIntervals );
	fprintf( fp, "CursorCaps :               0x%08x\n", caps->CursorCaps );
	fprintf( fp, "DevCaps :                  0x%08x\n\n", caps->DevCaps );

	fprintf( fp, "PrimitiveMiscCaps :        0x%08x\n", caps->PrimitiveMiscCaps );
	fprintf( fp, "RasterCaps :               0x%08x\n\n", caps->RasterCaps );

	fprintf( fp, "ZCmpCaps :                 0x%08x\n", caps->ZCmpCaps );
	fprintf( fp, "SrcBlendCaps :             0x%08x\n", caps->SrcBlendCaps );
	fprintf( fp, "DestBlendCaps :            0x%08x\n", caps->DestBlendCaps );
	fprintf( fp, "AlphaCmpCaps :             0x%08x\n\n", caps->AlphaCmpCaps );

	fprintf( fp, "ShadeCaps :                0x%08x\n", caps->ShadeCaps );
	fprintf( fp, "TextureCaps :              0x%08x\n", caps->TextureCaps );
	fprintf( fp, "TextureFilterCaps :        0x%08x\n", caps->TextureFilterCaps ); // D3DPTFILTERCAPS for IDirect3DTexture8's
	fprintf( fp, "CubeTextureFilterCaps :    0x%08x\n", caps->CubeTextureFilterCaps ); // D3DPTFILTERCAPS for IDirect3DCubeTexture8's
	fprintf( fp, "VolumeTextureFilterCaps :  0x%08x\n", caps->VolumeTextureFilterCaps ); // D3DPTFILTERCAPS for IDirect3DVolumeTexture8's
	fprintf( fp, "TextureAddressCaps :       0x%08x\n", caps->TextureAddressCaps ); // D3DPTADDRESSCAPS for IDirect3DTexture8's
	fprintf( fp, "VolumeTextureAddressCaps : 0x%08x\n\n", caps->VolumeTextureAddressCaps ); // D3DPTADDRESSCAPS for IDirect3DVolumeTexture8's

	fprintf( fp, "LineCaps :                 0x%08x\n", caps->LineCaps ); // D3DLINECAPS
	fprintf( fp, "StencilCaps :              0x%08x\n", caps->StencilCaps );
	fprintf( fp, "FVFCaps :                  0x%08x\n", caps->FVFCaps );
	fprintf( fp, "\n" );

	fprintf( fp, "MaxTextureWidth :          %u\n", caps->MaxTextureWidth );
	fprintf( fp, "MaxTextureHeight :         %u\n", caps->MaxTextureHeight );
	fprintf( fp, "MaxTextureRepeat :         %u\n", caps->MaxTextureRepeat );
	fprintf( fp, "MaxTextureAspectRatio :    %u\n", caps->MaxTextureAspectRatio );
	fprintf( fp, "MaxTextureBlendStages :    %u\n", caps->MaxTextureBlendStages );
	fprintf( fp, "MaxSimultaneousTextures :  %u\n", caps->MaxSimultaneousTextures );
	fprintf( fp, "\n" );

	fprintf( fp, "TextureOpCaps :            0x%08x\n\n", caps->TextureOpCaps );

	fprintf( fp, "VertexProcessingCaps :     0x%08x\n\n", caps->VertexProcessingCaps );
	fprintf( fp, "MaxActiveLights :          %u\n", caps->MaxActiveLights );
	fprintf( fp, "MaxUserClipPlanes :        %u\n", caps->MaxUserClipPlanes );
	fprintf( fp, "MaxVertexBlendMatrices :   %u\n", caps->MaxVertexBlendMatrices );
	fprintf( fp, "MaxVertexBlendMatrixIndex :%u\n", caps->MaxVertexBlendMatrixIndex );
	fprintf( fp, "MaxVertexW :               %f\n", caps->MaxVertexW );
 	fprintf( fp, "\n" );

	fprintf( fp, "MaxPointSize :             %u\n", caps->MaxPointSize );
	fprintf( fp, "MaxPrimitiveCount :        %u\n", caps->MaxPrimitiveCount );
	fprintf( fp, "MaxVertexIndex :           %u\n", caps->MaxVertexIndex );
	fprintf( fp, "MaxStreams :               %u\n", caps->MaxStreams );
	fprintf( fp, "MaxStreamStride :          %u\n\n", caps->MaxStreamStride );

	//fprintf( fp, "VertexShaderVersion :      0x%08x\n", caps->VertexShaderVersion );
	//fprintf( fp, "PixelShaderVersion :       0x%08x\n", caps->PixelShaderVersion );
	fprintf( fp, "VertexShaderVersion(DWORD):0x%08x\n", caps->VertexShaderVersion );
	fprintf( fp, "PixelShaderVersion(DWORD): 0x%08x\n", caps->PixelShaderVersion );
	fprintf( fp, "VertexShaderVersion :      %s\n", GetShaderVersionString(caps->VertexShaderVersion).c_str() );
	fprintf( fp, "PixelShaderVersion :       %s\n", GetShaderVersionString(caps->PixelShaderVersion ).c_str() );
	fprintf( fp, "MaxVertexShaderConst :     %u\n", caps->MaxVertexShaderConst );
	fprintf( fp, "MaxPixelShaderValue :      %f\n\n", caps->MaxPixelShaderValue );

/*
    /* Device Info *
    D3DDEVTYPE  DeviceType;
    UINT    AdapterOrdinal;

    /* Caps from DX7 Draw *
x   DWORD   Caps;
x   DWORD   Caps2;
x   DWORD   Caps3;
x   DWORD   PresentationIntervals;

    /* Cursor Caps *
x   DWORD   CursorCaps;

    /* 3D Device Caps *
XX  DWORD   DevCaps;

** X Start
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
** X End 

xx  DWORD   MaxTextureWidth, MaxTextureHeight;
    DWORD   MaxVolumeExtent;

x   DWORD   MaxTextureRepeat;
x   DWORD   MaxTextureAspectRatio;
    DWORD   MaxAnisotropy;
x   float   MaxVertexW;

    float   GuardBandLeft;
    float   GuardBandTop;
    float   GuardBandRight;
    float   GuardBandBottom;

    float   ExtentsAdjust;
x   DWORD   StencilCaps;

x   DWORD   FVFCaps;
x   DWORD   TextureOpCaps;
x   DWORD   MaxTextureBlendStages;
x   DWORD   MaxSimultaneousTextures;

x   DWORD   VertexProcessingCaps;
x   DWORD   MaxActiveLights;
x   DWORD   MaxUserClipPlanes;
x   DWORD   MaxVertexBlendMatrices;
x   DWORD   MaxVertexBlendMatrixIndex;

x   float   MaxPointSize;

x   DWORD   MaxPrimitiveCount;          // max number of primitives per DrawPrimitive call
x   DWORD   MaxVertexIndex;
x   DWORD   MaxStreams;
x   DWORD   MaxStreamStride;            // max stride for SetStreamSource

x   DWORD   VertexShaderVersion;
x   DWORD   MaxVertexShaderConst;       // number of vertex shader constant registers

x   DWORD   PixelShaderVersion;
x   float   MaxPixelShaderValue;        // max value of pixel shader arithmetic component

*/
}

void CMglD3dCapsDumper::DumpFlagItem( FILE *fp, DWORD dwValue, DWORD dwMask, const char* szName )
{
	if ( dwValue & dwMask )
		fprintf( fp, "%30s :   true\n", szName );
	else
		fprintf( fp, "%30s :   false\n", szName );

}

//	頂点/ピクセルシェーダーのバージョン文字列取得 (from DWORD)
std::string CMglD3dCapsDumper::GetShaderVersionString( DWORD dwShaderVersion )
{
	char work[20];
	sprintf(work, "%d.%d",
		D3DSHADER_VERSION_MAJOR(dwShaderVersion),
		D3DSHADER_VERSION_MINOR(dwShaderVersion));
	return work;
}

void CMglD3dCapsDumper::DumpDepthStencilTest( _IDirect3DX* m_pD3d, UINT nAdapterNo,
	D3DFORMAT displayFormat, D3DDEVTYPE deviceType )
{
	FILE *fp=fopen( CAPS_DUMP_LOG, "a" );
	if ( fp == NULL )
		MyuThrow( 0, "CMglD3dCapsDumper::DumpCapsAll()  ログファイルのオープンに失敗。" );

	///////////////////////////////////////////////////////////////////////////////////////////

	fprintf( fp, "\n\n==== DepthStencilFormatTest ======================\n\n" );

	DumpDepthStencilTestItem( m_pD3d, nAdapterNo, displayFormat, deviceType, D3DFMT_D32, fp, "D3DFMT_D32" );
	DumpDepthStencilTestItem( m_pD3d, nAdapterNo, displayFormat, deviceType, D3DFMT_D24S8, fp, "D3DFMT_D24S8" );
	DumpDepthStencilTestItem( m_pD3d, nAdapterNo, displayFormat, deviceType, D3DFMT_D24X8, fp, "D3DFMT_D24X8" );
	DumpDepthStencilTestItem( m_pD3d, nAdapterNo, displayFormat, deviceType, D3DFMT_D24X4S4, fp, "D3DFMT_D24X4S4" );
	DumpDepthStencilTestItem( m_pD3d, nAdapterNo, displayFormat, deviceType, D3DFMT_D15S1, fp, "D3DFMT_D15S1" );
	DumpDepthStencilTestItem( m_pD3d, nAdapterNo, displayFormat, deviceType, D3DFMT_D16, fp, "D3DFMT_D16" );
	DumpDepthStencilTestItem( m_pD3d, nAdapterNo, displayFormat, deviceType, D3DFMT_D16_LOCKABLE, fp, "D3DFMT_D16_LOCKABLE" );

	/*
	if ( CheckDepthStencilFormat(nAdapterNo, displayFormat, D3DFMT_D32, deviceType ) == TRUE )
		fprintf( fp, "DriverVersion :            %d,%u\n\n", adapterInfo.DriverVersion.HighPart, adapterInfo.DriverVersion.LowPart );
	
	if ( CheckDepthStencilFormat(nAdapterNo, displayFormat, D3DFMT_D24S8, deviceType ) == TRUE ) {
		depthStencilFormat = D3DFMT_D24S8;
		_MGL_DEBUGLOG( "DepthStencilFormatとしてD3DFMT_D24S8を使用します。" );
	}
	else if ( CheckDepthStencilFormat(nAdapterNo, displayFormat, D3DFMT_D24X8, deviceType ) == TRUE ) {
		depthStencilFormat = D3DFMT_D24X8;
		_MGL_DEBUGLOG( "DepthStencilFormatとしてD3DFMT_D24X8を使用します。" );
	}
	else if ( CheckDepthStencilFormat(nAdapterNo, displayFormat, D3DFMT_D16, deviceType ) == TRUE ) {  
		depthStencilFormat = D3DFMT_D16;
		_MGL_DEBUGLOG( "DepthStencilFormatとしてD3DFMT_D16を使用します。" );
	}
	*/

	fclose( fp );
}

void CMglD3dCapsDumper::DumpDepthStencilTestItem( _IDirect3DX* m_pD3d, UINT nAdapterNo,
	D3DFORMAT displayFormat, D3DDEVTYPE deviceType, D3DFORMAT targetFormat, FILE* fp, const char* szFormatName )
{
//	if ( CheckDepthStencilFormat(nAdapterNo, displayFormat, targetFormat, deviceType ) == TRUE )
	if ( m_pD3d->CheckDeviceFormat( nAdapterNo,
		deviceType, displayFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, targetFormat ) == S_OK )

		fprintf( fp, "%-20s       o Supported\n", szFormatName );
	else
		fprintf( fp, "%-20s       x Unsupported\n", szFormatName );
}

/*
//	DirectDrawを使ってディスプレイサイズを取得
void CMglD3dCapsDumper::GetVramInfo( DWORD *dwpTotal, DWORD *dwpFree )
{
	//ディスプレイドライバ
	IDirectDraw7* pDDraw=NULL;
	MyuAssert( DirectDrawCreateEx(NULL,(void**)(&pDDraw),IID_IDirectDraw7,NULL), DD_OK,
		"CMglD3dCapsDumper::GetVramInfo()  DirectDrawCreateEx()に失敗。" );

	//VRAM
	DDSCAPS2 ddsCaps2; 
	ZeroMemory(&ddsCaps2, sizeof(ddsCaps2)); 
	ddsCaps2.dwCaps=DDSCAPS_VIDEOMEMORY; 

	MyuAssert( pDDraw->GetAvailableVidMem( &ddsCaps2, dwpTotal, dwpFree ), DD_OK,
		"CMglD3dCapsDumper::GetVramInfo()  pDDraw->GetAvailableVidMem()に失敗。" );

	SAFE_RELEASE(pDDraw);
}
*/