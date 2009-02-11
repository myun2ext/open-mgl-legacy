//////////////////////////////////////////////////////////
//
//	Mgl3dSquare - 線絵画クラス
//
//////////////////////////////////////////////////////////

#ifndef __Mgl3dSquare_H__
#define __Mgl3dSquare_H__

#include "MglGraphicManager.h"
#include "MglVertexManager.h"
#include "MglD3dTexture.h"

//#pragma warning( disable : 4660 )

//	テクスチャなしVertex
class MGL_NOTEX_VERTEX
{
public:
	float		x,y,z;
	D3DCOLOR	color;
	// ---------------------------------------------
	MGL_NOTEX_VERTEX(){
		x = y = z = 0.0f;
		color = 0;
	}
	static DWORD GetFVF(){ return D3DFVF_XYZ | D3DFVF_DIFFUSE; }
};

//	クラス宣言
//class DLL_EXP CMgl3dSquare : public CMglVertexManagerXT<MGL_NOTEX_VERTEX>
class DLL_EXP CMgl3dSquare : public CMglVertexManagerX
{
public:
	typedef CMyuVertex _VERTEX;

protected:
	//CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	//_MGL_IDirect3DDevice* m_d3d;	//	D3DDeviceへのポインタ
	//CMglD3dTexture *m_tex;
	CMglD3dTexture *m_texList[MGL_TEXTURE_STAGE_MAX];
	CMglTssManager m_tss;

	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}
	void CreatedCheck() {
		if ( m_vertexes.size() != 0 )
			MyuThrow( MGLMSGNO_3DSQUARE(1), "CMgl3dSquare  既に作成済です。" );
	}
	void CreateCheck() {
		if ( m_vertexes.size() == 0 )
			MyuThrow( MGLMSGNO_3DSQUARE(2), "CMgl3dSquare::Draw()  未作成です。" );
	}
	//void SetTuTv(MGLTUTV &tutv);
	void SetTuTv(int no, MGLTUTV &tutv);

public:
	//	コンストラクタ・デストラクタ
	CMgl3dSquare();
	virtual ~CMgl3dSquare(){}

	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );

	void SimpleCreate(float fWidth, float fHeight, D3DCOLOR color);

	void CreateFromTexture(CMglD3dTexture &tex, float fWidth, float fHeight, D3DCOLOR color=D3DCOLOR_WHITE);
	void TextureCreate(CMglD3dTexture &tex, float fWidth, float fHeight, D3DCOLOR color=D3DCOLOR_WHITE){
		CreateFromTexture(tex,fWidth,fHeight,color); }

	void SetTexture(CMglD3dTexture &tex){ SetTexture(0, tex); }
	void SetTexture(int no, CMglD3dTexture &tex);
	void AddTexture(CMglD3dTexture &tex);
	void EraseTexture(int no){
		m_texList[no] = NULL;
		m_tss.StageClear(no);
	}

	void SetTss(int nStage, D3DTEXTURESTAGESTATETYPE tssType, DWORD value){
		SetTextureStageState(nStage, tssType, value); }
	void SetTextureStageState(int nStage, D3DTEXTURESTAGESTATETYPE tssType, DWORD value){
		m_tss.Set(nStage, tssType, value);
	}

	void Draw();//{ CMglVertexManagerX::Draw(D3DPT_TRIANGLESTRIP); }		//	D3DPT_TRIANGLESTRIPだと最後の頂点の色が変になるんだよねぇ・・・なんでだろうねぇ・・・
	//void Draw(){ CMglVertexManagerX::Draw(D3DPT_TRIANGLEFAN); }
	//void Draw(){ CMglVertexManagerXT<MGL_NOTEX_VERTEX>::Draw(D3DPT_TRIANGLESTRIP); }
};

#endif//__Mgl3dSquare_H__
