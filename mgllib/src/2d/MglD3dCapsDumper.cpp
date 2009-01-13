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