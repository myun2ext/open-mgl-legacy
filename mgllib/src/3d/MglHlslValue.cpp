#include "stdafx.h"
#include "MglHLSL.h"

//	Float
void CMglHlslValue::SetFloat( _MGL_D3DXHANDLE szValueName, float fValue )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetFloat( szValueName, (float)fValue ), D3D_OK,
		MGLMSGNO_SHADER(320), "CMglEffectCore::SetFloat()  m_pEffect->SetFloat()‚ÉŽ¸”s" );
}

#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXEFFECT_CHANGED

//	Int
void CMglHlslValue::SetInt( _MGL_D3DXHANDLE szValueName, int nValue )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetInt( szValueName, nValue ), D3D_OK,
		MGLMSGNO_SHADER(322), "CMglEffectCore::SetInt()  m_pEffect->SetInt()‚ÉŽ¸”s" );
}

//	Bool
void CMglHlslValue::SetBool( _MGL_D3DXHANDLE szValueName, BOOL bValue )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetBool( szValueName, bValue ), D3D_OK,
		MGLMSGNO_SHADER(324), "CMglEffectCore::SetBool()  m_pEffect->SetBool()‚ÉŽ¸”s" );
}

//	Vector
void CMglHlslValue::SetVector( _MGL_D3DXHANDLE szValueName, CONST D3DXVECTOR4 &vValue )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetVector( szValueName, &vValue ), D3D_OK,
		MGLMSGNO_SHADER(326), "CMglEffectCore::SetVector()  m_pEffect->SetVector()‚ÉŽ¸”s" );
}

//	VectorArray
void CMglHlslValue::SetVectorArray( _MGL_D3DXHANDLE szValueName, CONST D3DXVECTOR4* pArray, UINT nCount )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetVectorArray( szValueName, pArray, nCount ), D3D_OK,
		MGLMSGNO_SHADER(328), "CMglEffectCore::SetVectorArray()  m_pEffect->SetVectorArray()‚ÉŽ¸”s" );
}

//	Matrix
void CMglHlslValue::SetMatrix( _MGL_D3DXHANDLE szValueName, CONST D3DXMATRIX &matrix )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetMatrix( szValueName, &matrix ), D3D_OK,
		MGLMSGNO_SHADER(330), "CMglEffectCore::SetMatrix()  m_pEffect->SetMatrix()‚ÉŽ¸”s" );
}

//	”CˆÓ‚Ì’l
void CMglHlslValue::SetValue( _MGL_D3DXHANDLE szValueName, CONST VOID* pValue, UINT nSize )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetValue( szValueName, pValue, nSize ), D3D_OK,
		MGLMSGNO_SHADER(332), "CMglEffectCore::SetValue()  m_pEffect->SetValue()‚ÉŽ¸”s" );
}

#endif//_MGL_D3DXVER >= MGL_D3DXVER_ID3DXEFFECT_CHANGED
