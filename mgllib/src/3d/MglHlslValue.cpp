#include "stdafx.h"
#include "MglHLSL.h"

//	SetFloat
void CMglHlslValue::SetFloat( _MGL_D3DXHANDLE szValueName, float fValue )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetFloat( szValueName, (float)fValue ), D3D_OK,
		MGLMSGNO_SHADER(323), "CMglEffectCore::SetFloat()  m_pEffect->SetFloat()‚ÉŽ¸”s" );
}

//	SetInt
void CMglHlslValue::SetInt( _MGL_D3DXHANDLE szValueName, int nValue )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetInt( szValueName, nValue ), D3D_OK,
		MGLMSGNO_SHADER(322), "CMglEffectCore::SetInt()  m_pEffect->SetInt()‚ÉŽ¸”s" );
}

//	SetBool
void CMglHlslValue::SetBool( _MGL_D3DXHANDLE szValueName, BOOL bValue )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetBool( szValueName, bValue ), D3D_OK,
		MGLMSGNO_SHADER(321), "CMglEffectCore::SetBool()  m_pEffect->SetBool()‚ÉŽ¸”s" );
}

//	SetVector
void CMglHlslValue::SetVector( _MGL_D3DXHANDLE szValueName, CONST D3DXVECTOR4* pValue )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetVector( szValueName, pValue ), D3D_OK,
		MGLMSGNO_SHADER(324), "CMglEffectCore::SetVector()  m_pEffect->SetVector()‚ÉŽ¸”s" );
}

//	SetVectorArray
void CMglHlslValue::SetVectorArray( _MGL_D3DXHANDLE szValueName, CONST D3DXVECTOR4* pArray, UINT nCount )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetVectorArray( szValueName, pArray, nCount ), D3D_OK,
		MGLMSGNO_SHADER(324), "CMglEffectCore::SetVectorArray()  m_pEffect->SetVectorArray()‚ÉŽ¸”s" );
}
