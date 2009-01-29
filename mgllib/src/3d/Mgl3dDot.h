//////////////////////////////////////////////////////////
//
//	Mgl3dDot - 線絵画クラス
//
//////////////////////////////////////////////////////////

#ifndef __Mgl3dDot_H__
#define __Mgl3dDot_H__

#include "MglGraphicManager.h"
#include "MglVertexManager.h"

////////////////////////////////////

//	FVF Define
#define	FVF_MGL_DOT ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE )

//	Vertex Struct
class MGL_DOT_VERTEX
{
public:
	float		x,y,z;
	D3DCOLOR	color;
	float		point;	//	点の大きさ
	// ---------------------------------------------
	MGL_DOT_VERTEX(){
		x = y = z = 0.0f;
		color = 0;
		point = 1.0f;
	}
	static DWORD GetFVF(){ return FVF_MGL_DOT; }
};

//	DLL Exports (inhibit for C4275)
DLL_TMPL_EXP CMglVertexManagerT<MGL_DOT_VERTEX>;
DLL_TMPL_EXP CMglVertexManagerXT<MGL_DOT_VERTEX>;

/////////////////////////////////////////////////////////////////////

//	クラス宣言
class DLL_EXP CMgl3dDots : public CMglVertexManagerXT<MGL_DOT_VERTEX>
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	IDirect3DDevice8* m_d3d;			//	D3DDeviceへのポインタ

	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	//	コンストラクタ・デストラクタ
	CMgl3dDots();
	virtual ~CMgl3dDots(){}

	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
};

#endif//__Mgl3dDot_H__
