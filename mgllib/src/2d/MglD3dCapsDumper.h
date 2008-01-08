#ifndef __MglD3dCapsDumper_H__
#define __MglD3dCapsDumper_H__

#define CAPS_DUMP_LOG				"MglDXGlphCaps.log"

//	ÉNÉâÉXêÈåæ
class CMglD3dCapsDumper
{
private:
	void DumpCaps( FILE *fp, D3DCAPS8* pCaps );
	void DumpFlagItem( FILE *fp, DWORD dwValue, DWORD dwMask, const char* szName );

public:
	//void DumpAdapterInfo( D3DCAPS8* pCapsHal, D3DCAPS8* pCapsRef );
	void DumpAdapterInfo( IDirect3D8* m_pD3d, D3DCAPS8* pCaps );

};

#endif//__MglD3dCapsDumper_H__