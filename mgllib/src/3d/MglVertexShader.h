//////////////////////////////////////////////////////////
//
//	CMglVertexShader - ピクセルシェーダ
//
//////////////////////////////////////////////////////////

#ifndef __MglVertexShader_H__
#define __MglVertexShader_H__

#include "mglafx.h"
#include "MglGraphicManager.h"
#include "MglXShader.h"

//	クラス宣言
class DLL_EXP CMglVertexShader : public CMglDgBase
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
			MyuThrow(MGLMSGNO_SHADER(81), "CMglVertexShader  既にシェーダは作成済です。");
	}
	void CreateCheck(){
		if ( m_pShader == NULL )
			MyuThrow(MGLMSGNO_SHADER(82), "CMglVertexShader  シェーダが作成されていません。");
	}
	void LoadCommon(CONST DWORD* pFunction);

public:
	//	コンストラクタ・デストラクタ
	CMglVertexShader();
	virtual ~CMglVertexShader(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	void LoadFromString( const char* szAssembleString );
	void CreateFromString( const char* szAssembleString ){ LoadFromString(szAssembleString); }

	void SetFVF(DWORD dwFvf){ m_dwFvf = dwFvf; }

	//////////////////////////////////////////////////////////////////////////

	void SetShader();
	void UnsetShader();
	void RemoveShader(){ RemoveShader(); }
	void ReleaseShader(){ RemoveShader(); }

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

#endif//__MglVertexShader_H__
