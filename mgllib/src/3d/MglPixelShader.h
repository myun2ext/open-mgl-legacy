//////////////////////////////////////////////////////////
//
//	CMglPixelShader - �s�N�Z���V�F�[�_
//
//////////////////////////////////////////////////////////

#ifndef __MglPixelShader_H__
#define __MglPixelShader_H__

#include "mglafx.h"
#include "MglGraphicManager.h"
#include "MglXShader.h"

//	�N���X�錾
class DLL_EXP CMglPixelShader : public CMglDgBase
{
protected:
#if _MGL_DXVER == 9
	_IDirect3DPixelShaderX* m_pShader;
#else
	DWORD m_pShader;
#endif

	//-------------------------------------------------------------

	void CreatedCheck(){
		if ( m_pShader != NULL )
			MyuThrow(MGLMSGNO_SHADER(1), "CMglPixelShader  ���ɃV�F�[�_�͍쐬�ςł��B");
	}
	void CreateCheck(){
		if ( m_pShader == NULL )
			MyuThrow(MGLMSGNO_SHADER(2), "CMglPixelShader  �V�F�[�_���쐬����Ă��܂���B");
	}
	void LoadCommon(CONST DWORD* pFunction);

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglPixelShader();
	virtual ~CMglPixelShader(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	void LoadFromString( const char* szAssembleString );
	void CreateFromString( const char* szAssembleString ){ LoadFromString(szAssembleString); }

	//////////////////////////////////////////////////////////////////////////

	void SetShader();

	void SetParam(DWORD dwRegisterNo, MGL_SHADER_PARAM &param){
		SetParam(0, (const float*)param, 1); }
	void SetShaderParam(DWORD dwRegisterNo, MGL_SHADER_PARAM &param){
		SetShaderParam(0, (const float*)param, 1); }

	void SetParam(DWORD dwRegisterNo, float r, float g, float b, float a){
		SetParam(0, (const float*)D3DXVECTOR4(r,g,b,a), 1); }
	void SetShaderParam(DWORD dwRegisterNo, float r, float g, float b, float a){
		SetShaderParam(0, (const float*)D3DXVECTOR4(r,g,b,a), 1); }

	void SetParam(const void* lpData, DWORD dwDataBlockCount=1){
		SetParam(0, lpData, dwDataBlockCount); }
	void SetShaderParam(const void* lpData, DWORD dwDataBlockCount=1){
		SetShaderParam(0, lpData, dwDataBlockCount); }

	void SetParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount){
		SetShaderParam(dwStartRegisterNo, lpData, dwDataBlockCount); }
	void SetParam(DWORD dwStartRegisterNo, CMglShaderParam &param){
		SetShaderParam(dwStartRegisterNo, param); }

	void SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount);
	void SetShaderParam(DWORD dwStartRegisterNo, CMglShaderParam &param);
};

#endif//__MglPixelShader_H__