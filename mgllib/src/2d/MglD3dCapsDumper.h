#ifndef __MglD3dCapsDumper_H__
#define __MglD3dCapsDumper_H__

#define CAPS_DUMP_LOG				"MglDXGlphCaps.log"

//	ÉNÉâÉXêÈåæ
class CMglD3dCapsDumper
{
private:
	void DumpCaps( FILE *fp, _D3DCAPSx* pCaps );
	void DumpFlagItem( FILE *fp, DWORD dwValue, DWORD dwMask, const char* szName );
	std::string GetShaderVersionString( DWORD dwShaderVersion );
	void DumpDepthStencilTestItem( _IDirect3DX* m_pD3d, UINT nAdapterNo,
		D3DFORMAT displayFormat, D3DDEVTYPE deviceType, D3DFORMAT targetFormat, FILE* fp, const char* szFormatName );

public:
	//void DumpAdapterInfo( D3DCAPS8* pCapsHal, D3DCAPS8* pCapsRef );
	void DumpAdapterInfo( _IDirect3DX* m_pD3d, _D3DCAPSx* pCaps );

	void DumpDepthStencilTest( _IDirect3DX* m_pD3d, UINT nAdapterNo,
		D3DFORMAT displayFormat, D3DDEVTYPE deviceType );
};

#endif//__MglD3dCapsDumper_H__