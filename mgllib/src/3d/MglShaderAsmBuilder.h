//////////////////////////////////////////////////////////
//
//	CMglShaderAsmBuilder - ピクセルシェーダ
//
//////////////////////////////////////////////////////////

#ifndef __MglShaderAsmBuilder_H__
#define __MglShaderAsmBuilder_H__

#include "mglafx.h"
#include "MglGraphicManager.h"
#include "MglXShader.h"

//	クラス宣言
class DLL_EXP CMglShaderAsmBuilder : public CMglDgBase
{
protected:
#if _MGL_DXVER == 9
	_IDirect3DVertexShaderX* m_pShader;
#else
	DWORD m_pShader;
#endif
	DWORD m_dwFvf;

	//-------------------------------------------------------------

	void CreatedCheck(){
		if ( m_pShader != NULL )
			MyuThrow(MGLMSGNO_SHADER(81), "CMglShaderAsmBuilder  既にシェーダは作成済です。");
	}
	void CreateCheck(){
		if ( m_pShader == NULL )
			MyuThrow(MGLMSGNO_SHADER(82), "CMglShaderAsmBuilder  シェーダが作成されていません。");
	}
	void LoadCommon(CONST DWORD* pFunction);

public:
	//	コンストラクタ・デストラクタ
	CMglShaderAsmBuilder();
	CMglShaderAsmBuilder(DWORD dwFvf){
		SetFVF(dwFvf);
	}
	virtual ~CMglShaderAsmBuilder(){ Release(); }
	void Release();

	void Load(DWORD dwFvf, const char* szShaderScriptFile){
		SetFVF(dwFvf);
		Load(szShaderScriptFile);
	}
	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	void LoadFromString(DWORD dwFvf, const char* szAssembleString ){
		SetFVF(dwFvf);
		LoadFromString(szAssembleString);
	}
	void LoadFromString( const char* szAssembleString );
	void CreateFromString( const char* szAssembleString ){ LoadFromString(szAssembleString); }

	void SetFVF(DWORD dwFvf){ m_dwFvf = dwFvf; }

	//////////////////////////////////////////////////////////////////////////

	void SetShader();
	void UnsetShader();
	void RemoveShader(){ UnsetShader(); }
	void ReleaseShader(){ UnsetShader(); }

	void SetParam(DWORD dwRegisterNo, MGL_VERTEX_SHADER_PARAM &param){
		SetParam(0, CMglShaderAsmBuilderParam(param), 1); }
	void SetShaderParam(DWORD dwRegisterNo, MGL_VERTEX_SHADER_PARAM &param){
		SetShaderParam(0, CMglShaderAsmBuilderParam(param), 1); }

	void SetParam(const void* lpData, DWORD dwDataBlockCount=1){
		SetParam(0, lpData, dwDataBlockCount); }
	void SetShaderParam(const void* lpData, DWORD dwDataBlockCount=1){
		SetShaderParam(0, lpData, dwDataBlockCount); }

	void SetParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount){
		SetShaderParam(dwStartRegisterNo, lpData, dwDataBlockCount); }
	void SetParam(DWORD dwStartRegisterNo, CMglShaderAsmBuilderParam &param){
		SetShaderParam(dwStartRegisterNo, param); }

	void SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount);
	void SetShaderParam(DWORD dwStartRegisterNo, CMglShaderAsmBuilderParam &param);
};

#endif//__MglShaderAsmBuilder_H__
