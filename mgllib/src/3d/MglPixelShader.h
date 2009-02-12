//////////////////////////////////////////////////////////
//
//	CMglPixelShader - ピクセルシェーダ
//
//////////////////////////////////////////////////////////

#ifndef __MglPixelShader_H__
#define __MglPixelShader_H__

#include "mglafx.h"
#include "MglGraphicManager.h"
#include "MglXShader.h"

//------------------------------------------------------------------------------

typedef D3DXVECTOR4 MGL_PIXEL_SHADER_PARAM;

//	ピクセルシェーダのパラメタ
class CMglPixelShaderParam
{
protected:
	std::vector<MGL_PIXEL_SHADER_PARAM> m_params;

public:
	void Add(MGL_PIXEL_SHADER_PARAM &param){ m_params.push_back(param); }
	void Add(float r, float g, float b, float a){ m_params.push_back(D3DXVECTOR4(r,g,b,a)); }
	//void Remove(int index){ m_params.remove(index); }
	void Clear(){ m_params.clear(); }

	MGL_PIXEL_SHADER_PARAM& Get(int index){ return m_params[index]; }
	MGL_PIXEL_SHADER_PARAM& operator [](int index){ return m_params[index]; }

	const void* GetHeadPtr(){ return &m_params[0]; }
	int size(){ return m_params.size(); }
	int GetSize(){ return m_params.size(); }
	int GetCount(){ return m_params.size(); }
};

//------------------------------------------------------------------------------


//	クラス宣言
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
			MyuThrow(MGLMSGNO_SHADER(1), "CMglPixelShader  既にシェーダは作成済です。");
	}
	void CreateCheck(){
		if ( m_pShader == NULL )
			MyuThrow(MGLMSGNO_SHADER(2), "CMglPixelShader  シェーダが作成されていません。");
	}
	void LoadCommon(CONST DWORD* pFunction);

public:
	//	コンストラクタ・デストラクタ
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
	void UnsetShader();
	void RemoveShader(){ UnsetShader(); }
	void ReleaseShader(){ UnsetShader(); }

	void SetParam(DWORD dwRegisterNo, MGL_PIXEL_SHADER_PARAM &param){
		SetParam(0, (const float*)param, 1); }
	void SetShaderParam(DWORD dwRegisterNo, MGL_PIXEL_SHADER_PARAM &param){
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
	void SetParam(DWORD dwStartRegisterNo, CMglPixelShaderParam &param){
		SetShaderParam(dwStartRegisterNo, param); }

	void SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount);
	void SetShaderParam(DWORD dwStartRegisterNo, CMglPixelShaderParam &param);
};

#endif//__MglPixelShader_H__
