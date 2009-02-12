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

//------------------------------------------------------------------------------

typedef D3DXMATRIX MGL_VERTEX_SHADER_PARAM;

//	ピクセルシェーダのパラメタ
class CMglVertexShaderParam
{
protected:
	std::vector<MGL_VERTEX_SHADER_PARAM> m_params;

public:
	CMglVertexShaderParam(){}
	CMglVertexShaderParam(D3DXMATRIX &param){
		Add(param);
	}
	CMglVertexShaderParam(D3DXMATRIX &mWorld, D3DXMATRIX &mView, D3DXMATRIX &mProjection){
		Add(mWorld, mView, mProjection);
	}

	void Add(D3DXMATRIX &mWorld, D3DXMATRIX &mView, D3DXMATRIX &mProjection){
		Add( mWorld * mView * mProjection );
	}
	void Add(D3DXMATRIX &param){
		D3DXMATRIX trans;
		D3DXMatrixTranspose(&trans, &param);
		m_params.push_back(trans);
		//m_params.push_back(param);
	}
	//void Remove(int index){ m_params.remove(index); }
	void Clear(){ m_params.clear(); }

	MGL_VERTEX_SHADER_PARAM& Get(int index){ return m_params[index]; }
	MGL_VERTEX_SHADER_PARAM& operator [](int index){ return m_params[index]; }

	const void* GetHeadPtr(){ return &m_params[0]; }
	operator const void*(){ return &m_params[0]; }
	operator void*(){ return &m_params[0]; }

	int size(){ return m_params.size(); }
	int GetSize(){ return m_params.size(); }
	int GetCount(){ return m_params.size(); }
};

//------------------------------------------------------------------------------
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
	void RemoveShader(){ UnsetShader(); }
	void ReleaseShader(){ UnsetShader(); }

	void SetParam(DWORD dwRegisterNo, MGL_VERTEX_SHADER_PARAM &param){
		SetParam(0, CMglVertexShaderParam(param), 1); }
	void SetShaderParam(DWORD dwRegisterNo, MGL_VERTEX_SHADER_PARAM &param){
		SetShaderParam(0, CMglVertexShaderParam(param), 1); }

	void SetParam(const void* lpData, DWORD dwDataBlockCount=1){
		SetParam(0, lpData, dwDataBlockCount); }
	void SetShaderParam(const void* lpData, DWORD dwDataBlockCount=1){
		SetShaderParam(0, lpData, dwDataBlockCount); }

	void SetParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount){
		SetShaderParam(dwStartRegisterNo, lpData, dwDataBlockCount); }
	void SetParam(DWORD dwStartRegisterNo, CMglVertexShaderParam &param){
		SetShaderParam(dwStartRegisterNo, param); }

	void SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount);
	void SetShaderParam(DWORD dwStartRegisterNo, CMglVertexShaderParam &param);
};

#endif//__MglVertexShader_H__
