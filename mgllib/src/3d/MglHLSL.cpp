#include "stdafx.h"
#include "MglHLSL.h"

//	�R���X�g���N�^
CMglEffectCore::CMglEffectCore()
{
	m_pEffect = NULL;
	m_pBufErrorInfo = NULL;

	m_nPassCount = 0;
	m_bBegun = false;
	m_bPassBegun = false;
}

//	�J��
void CMglEffectCore::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pBufErrorInfo);
}

//	�G�t�F�N�g�t�@�C���ǂݍ���
void CMglEffectCore::Load(const char* szShaderScriptFile)
{
	CreatedCheck();

	//	�t�@�C�����{���ɂ��邩�ǂ����H
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(202), "CMglEffectCore::Load()  �t�@�C�� \"%s\" �͌�����܂���B", szShaderScriptFile);

	//	�G�t�F�N�g�t�@�C���ǂݍ��݁[
	/*MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK, <- �Ȃ�GetCompileErrorMsg()����Ɏ��s����Ă��܂��炵���E�E�E�܂��œK���Ƃ��ł��ˁE�E�E
		MGLMSGNO_SHADER(12), "CMglEffectCore::Load()  D3DXAssembleShaderFromFile()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );*/
#if _MGL_DXVER == 8
	HRESULT hr = D3DXCreateEffectFromFile( m_d3d, szShaderScriptFile, &m_pEffect, &m_pBufErrorInfo );
#else
	HRESULT hr = D3DXCreateEffectFromFile( m_d3d, szShaderScriptFile, NULL, NULL, 0, NULL, &m_pEffect, &m_pBufErrorInfo );
#endif
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(213), "CMglEffectCore::Load()  ���̃G���[�̂��� D3DXCreateEffectFromFile() �͎��s���܂����B\r\n\r\n%s", GetCompileErrorMsg() );
}

//	�����񂩂�ǂݍ���
void CMglEffectCore::LoadFromString(const char* szAssembleString)
{
	CreatedCheck();

	//	�G�t�F�N�g�ǂݍ��݁[
	/*MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString), <- �Ȃ�GetCompileErrorMsg()����Ɏ��s����Ă��܂��炵���E�E�E�܂��œK���Ƃ��ł��ˁE�E�E
		0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglEffectCore::LoadFromString()  D3DXAssembleShader()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );*/
#if _MGL_DXVER == 8
	HRESULT hr = D3DXCreateEffect( m_d3d, szAssembleString, strlen(szAssembleString), &m_pEffect, &m_pBufErrorInfo );
#else
	HRESULT hr = D3DXCreateEffect( m_d3d, szAssembleString, strlen(szAssembleString),
		NULL, NULL, 0, NULL, &m_pEffect, &m_pBufErrorInfo );
#endif
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(214), "CMglEffectCore::LoadFromString()  ���̃G���[�̂��� D3DXCreateEffect() �͎��s���܂����B\r\n\r\n%s", GetCompileErrorMsg() );
}

//	�G���[���b�Z�[�W�擾
const char* CMglEffectCore::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "(No Error Buffer.)";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

////////////////////////////////////////////////////////////////

//	�e�N�j�b�N��ݒ�
void CMglEffectCore::SetTechnique( _MGL_D3DXHANDLE szTechniqueName )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetTechnique( szTechniqueName ), D3D_OK,
		MGLMSGNO_SHADER(240), "CMglEffectCore::SetTechnique()  m_pEffect->SetTechnique()�Ɏ��s" );
}

//	���̃e�N�j�b�N�ɁiNULL�w��ōŏ��̃e�N�j�b�N�j
void CMglEffectCore::NextTechnique( D3DXHANDLE hPrevTechnique )
{
	SetTechnique( FindNextValidTechnique(hPrevTechnique) );
}

//	FindNextValidTechnique
_MGL_D3DXHANDLE CMglEffectCore::FindNextValidTechnique( _MGL_D3DXHANDLE hPrevTechnique )
{
	CreateCheck();

	//	FindNextValidTechnique
	_MGL_D3DXHANDLE h=NULL;
	MyuAssert2( m_pEffect->FindNextValidTechnique( hPrevTechnique, &h ), D3D_OK,
		MGLMSGNO_SHADER(241), "CMglEffectCore::FindNextValidTechnique()  m_pEffect->FindNextValidTechnique()�Ɏ��s" );

	return h;
}

////////////////////////////////////////////////////////////////

//	Begin()
UINT CMglEffectCore::Begin( bool bRestoreCurrentRenderStates )
{
	CreateCheck();

	if ( m_bBegun )
		End();	//	�p�X���Ԃ��Ȃ��Ƃ����Ȃ����Ȃ��E�E�E

	DWORD dwFlags = 0;
	if ( !bRestoreCurrentRenderStates )
		dwFlags = /*D3DXFX_DONOTSAVESHADERSTATE |*/ D3DXFX_DONOTSAVESTATE ;

	//	Begin
	MyuAssert2( m_pEffect->Begin( &m_nPassCount, dwFlags ), D3D_OK,
		MGLMSGNO_SHADER(280), "CMglEffectCore::Begin()  m_pEffect->Begin()�Ɏ��s" );

	m_bBegun = true;

	return m_nPassCount;
}
UINT CMglEffectCore::Begin() {
	return Begin(true);
}

//	End()
void CMglEffectCore::End()
{
	CreateCheck();

	//	2009/22/28 - DirectX9�Ή�
	EndPass();

	MyuAssert2( m_pEffect->End(), D3D_OK,
		MGLMSGNO_SHADER(281), "CMglEffectCore::End()  m_pEffect->End()�Ɏ��s" );

	m_bBegun = false;
	m_nPassCount = 0;
}

//	Pass() -> BeginPass()
void CMglEffectCore::BeginPass(UINT nPassNo)
{
	CreateCheck();

	if ( !m_bBegun )
		Begin();

	if ( m_nPassCount < nPassNo )
		MyuThrow(MGLMSGNO_SHADER(289),
			"CMglHlsl  ���̃e�N�j�b�N�ł͈̔͊O�̃p�X�ԍ����w�肵�܂����B%d <--> %d", m_nPassCount, nPassNo );

#if _MGL_DXVER == 8
	MyuAssert2( m_pEffect->Pass(nPassNo), D3D_OK,
		MGLMSGNO_SHADER(284), "CMglEffectCore::BeginPass()  m_pEffect->Pass(%s)�Ɏ��s", nPassNo );
#else
	EndPass();
	MyuAssert2( m_pEffect->BeginPass(nPassNo), D3D_OK,
		MGLMSGNO_SHADER(284), "CMglEffectCore::BeginPass()  m_pEffect->BeginPass(%s)�Ɏ��s", nPassNo );

	m_bPassBegun = true;
#endif
}

//	EndPass()
void CMglEffectCore::EndPass()
{
#if _MGL_DXVER != 8
	CreateCheck();

	if ( m_bPassBegun )
		MyuAssert2( m_pEffect->EndPass(), D3D_OK,
			MGLMSGNO_SHADER(285), "CMglEffectCore::EndPass()  m_pEffect->EndPass()�Ɏ��s" );
	m_bPassBegun = false;
#endif
}

//	�o�b�t�@�擾
/*_MGL_ID3DXEffect_* CMglEffectCore::GetEffectPtr()
{
	InitCheck();
	CreateCheck();

	return m_pEffect;
}
*/
