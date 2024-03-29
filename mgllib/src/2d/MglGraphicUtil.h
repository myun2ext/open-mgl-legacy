//////////////////////////////////////////////////////////
//
//	MglGraphicUtil  v0.10.05 04/12/28
//		- MglGraphicManager関連でのマクロや関数を宣言
//
//	v0.10.05 04/12/18
//	・マクロ強化
//
//////////////////////////////////////////////////////////

#ifndef __MglGraphicUtil_H__
#define __MglGraphicUtil_H__

/*
#ifdef  MGL_USE_DIRECTX_VERSION_9
typedef IDirect3DDevice9	MGL_D3D_DEVICE;
typedef IDirect3D9			MGL_D3D;
#else
typedef IDirect3DDevice8	MGL_D3D_DEVICE;
typedef IDirect3D8			MGL_D3D;
#endif//MGL_USE_DIRECTX_VERSION_9
*/

////////////////////////////////
//
//		マクロ
//
#define D3DCOLOR_A(a)			((D3DCOLOR)((((a)&0xff)<<24)|(0x00ffffff)))
#define D3DCOLORW_A(a)			D3DCOLOR_A(WrapByte(a))
#define D3DCOLORW_ARGB(a,r,g,b)	D3DCOLOR_ARGB(WrapByte(a),WrapByte(r),WrapByte(g),WrapByte(b))
#define D3DCOLORW_RGBA(r,g,b,a)	D3DCOLOR_RGBA(WrapByte(r),WrapByte(g),WrapByte(b),WrapByte(a))
#define D3DCOLORW_XRGB(r,g,b)	D3DCOLOR_XRGB(WrapByte(r),WrapByte(g),WrapByte(b))

//	ものくろー
#define D3DCOLOR_MONO(v)		D3DCOLOR_XRGB(v,v,v)
#define D3DCOLORW_MONO(v)		D3DCOLOR_XRGB(WrapByte(v),WrapByte(v),WrapByte(v))

#define D3DCOLOR_BLUE			((D3DCOLOR)0xff0000ff)
#define D3DCOLOR_GREEN			((D3DCOLOR)0xff00ff00)
#define D3DCOLOR_RED			((D3DCOLOR)0xffff0000)
#define D3DCOLOR_PINK			((D3DCOLOR)0xffff00ff)
#define D3DCOLOR_CYAN			((D3DCOLOR)0xff00ffff)
#define D3DCOLOR_YELLOW			((D3DCOLOR)0xffffff00)
#define D3DCOLOR_WHITE			((D3DCOLOR)0xffffffff)
#define D3DCOLOR_BLACK			((D3DCOLOR)0xff000000)
#define D3DCOLOR_FULLWHITE		((D3DCOLOR)0xffffffff)	//	D3DCOLOR_WHITEに同じ

//	2008/12/14  もう過去の遺物だ。いい加減消してもいいだろう・・・
//#pragma message("メッセージ: D3DCOLOR_* マクロは D3DCOLOR_NA* マクロへ置換されています。(2007/01/01)")

#define D3DCOLOR_NABLUE			((D3DCOLOR)0x000000ff)
#define D3DCOLOR_NAGREEN		((D3DCOLOR)0x0000ff00)
#define D3DCOLOR_NARED			((D3DCOLOR)0x00ff0000)
#define D3DCOLOR_NAPINK			((D3DCOLOR)0x00ff00ff)
#define D3DCOLOR_NACYAN			((D3DCOLOR)0x0000ffff)
#define D3DCOLOR_NAYELLOW		((D3DCOLOR)0x00ffff00)
#define D3DCOLOR_NAWHITE		((D3DCOLOR)0x00ffffff)
#define D3DCOLOR_NABLACK		((D3DCOLOR)0x00000000)

#define D3DCOLOR_FULLALPHA		((D3DCOLOR)0xff000000)
#define D3DCOLOR_FA				((D3DCOLOR)0xff000000)
#define D3DCOLOR_ZEROALPHA		((D3DCOLOR)0x00000000)

//	フィルター
#define D3DCOLOR_ZEROALPHA_FILTER(COLOR)	(COLOR&0x00ffffff)
#define D3DCOLOR_NA(COLOR)					(COLOR&0x00ffffff)
#define D3DCOLOR_NOA(COLOR)					(COLOR&0x00ffffff)
#define D3DCOLOR_NOALPHA(COLOR)				(COLOR&0x00ffffff)
#define D3DCOLOR_FULLALPHA_FILTER(COLOR)	(COLOR|0xff000000)

//#define D3DCOLOR_AMASK(COLOR)				(COLOR&0x00ffffff)
#define D3DCOLOR_AMASK(COLOR)				(COLOR&0xff000000)
#define D3DCOLOR_RMASK(COLOR)				(COLOR&0x00ff0000)
#define D3DCOLOR_GMASK(COLOR)				(COLOR&0x0000ff00)
#define D3DCOLOR_BMASK(COLOR)				(COLOR&0x000000ff)

#define D3DCOLOR_GETA(COLOR)				(D3DCOLOR_AMASK(COLOR)>>24)
#define D3DCOLOR_GETR(COLOR)				(D3DCOLOR_RMASK(COLOR)>>16)
#define D3DCOLOR_GETG(COLOR)				(D3DCOLOR_GMASK(COLOR)>>8)
#define D3DCOLOR_GETB(COLOR)				(D3DCOLOR_BMASK(COLOR))
/*//	2008/05/25  こっちの方が高速か？ -> 関数の復帰値で使えないし変数にアクセスしてる時点で遅いような…
#define D3DCOLOR_GETA(COLOR)				(((BYTE*)(&COLOR))[3])
#define D3DCOLOR_GETR(COLOR)				(((BYTE*)(&COLOR))[2])
#define D3DCOLOR_GETG(COLOR)				(((BYTE*)(&COLOR))[1])
#define D3DCOLOR_GETB(COLOR)				(((BYTE*)(&COLOR))[0])*/

/*
#define D3DCOLOR_BLUE			((D3DCOLOR)0x000000ff)
#define D3DCOLOR_GREEN			((D3DCOLOR)0x0000ff00)
#define D3DCOLOR_RED			((D3DCOLOR)0x00ff0000)
#define D3DCOLOR_PINK			((D3DCOLOR)0x00ff00ff)
#define D3DCOLOR_CYAN			((D3DCOLOR)0x0000ffff)
#define D3DCOLOR_YELLOW			((D3DCOLOR)0x00ffff00)
#define D3DCOLOR_WHITE			((D3DCOLOR)0x00ffffff)
#define D3DCOLOR_BLACK			((D3DCOLOR)0x00000000)
*/		

typedef struct _MGL_D3DXVECTOR3 : public D3DXVECTOR3
{
public:
    _MGL_D3DXVECTOR3(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
} MGL_D3DXVECTOR3, MGL_VECTOR3, MGLVECTOR3, MGLXVECTOR3;

////////////////////////////////
//
//		関数
//

//	実テクスチャサイズを算出
inline int GetRealTexSize( int nVirtualSize )
{
	int i;
	for ( i=2; i < nVirtualSize; i <<= 1 )
		;
	return i;
}

//int GetWindowSX();
//int GetWindowSY();

inline BYTE WrapByte( int x )
{
	if ( x > 255 )
		return 255;
	if ( x < 0 )
		return 0;
	return x;
}

DLL_EXP RECT* _Rect( int left, int top, int right, int bottom, RECT *destRect=NULL );
DLL_EXP RECT* _Rect2( int left, int top, int width, int height, RECT *destRect=NULL );
DLL_EXP RECT* EzRect( int left, int top, int right, int bottom, RECT *destRect=NULL );
DLL_EXP RECT* EzRect2( int left, int top, int width, int height, RECT *destRect=NULL );
inline RECT Rect( int left, int top, int right, int bottom){
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	return rect;
}

DLL_EXP const char* GetD3DResultString( DWORD nD3dResult );

DLL_EXP BOOL GetScreenSize( int* pnWidth, int* pnHeight );

////////////////////////////////////////////////

namespace mglex
{
	DLL_EXP D3DXVECTOR3* D3DXMatrixToVector3( D3DXVECTOR3 *pOutVector3, CONST D3DXMATRIX *pInMatrix );
	inline D3DXVECTOR3 D3DXMatrixToVector3(CONST D3DXMATRIX *pInMatrix){
		D3DXVECTOR3 work;
		D3DXMatrixToVector3(&work, pInMatrix);
		return work;
	}

	DLL_EXP D3DXMATRIX* D3DXMatrixRotation( D3DXMATRIX *pOut, float fRadianX, float fRadianY, float fRadianZ );
	inline D3DXMATRIX D3DXMatrixRotation(float fRadianX, float fRadianY, float fRadianZ){
		D3DXMATRIX work;
		D3DXMatrixRotation(&work, fRadianX, fRadianY, fRadianZ);
		return work;
	}
}

#endif//__MglGraphicUtil_H__
