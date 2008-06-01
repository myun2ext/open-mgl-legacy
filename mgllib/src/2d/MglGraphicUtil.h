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

#pragma message("メッセージ: D3DCOLOR_* マクロは D3DCOLOR_NA* マクロへ置換されています。(2007/01/01)")

#define D3DCOLOR_NABLUE			((D3DCOLOR)0x000000ff)
#define D3DCOLOR_NAGREEN		((D3DCOLOR)0x0000ff00)
#define D3DCOLOR_NARED			((D3DCOLOR)0x00ff0000)
#define D3DCOLOR_NAPINK			((D3DCOLOR)0x00ff00ff)
#define D3DCOLOR_NACYAN			((D3DCOLOR)0x0000ffff)
#define D3DCOLOR_NAYELLOW		((D3DCOLOR)0x00ffff00)
#define D3DCOLOR_NAWHITE		((D3DCOLOR)0x00ffffff)
#define D3DCOLOR_NABLACK		((D3DCOLOR)0x00000000)

#define D3DCOLOR_FULLALPHA		((D3DCOLOR)0xff000000)
#define D3DCOLOR_ZEROALPHA		((D3DCOLOR)0x00000000)

//	フィルター
#define D3DCOLOR_ZEROALPHA_FILTER(COLOR)	(COLOR&0x00ffffff)
#define D3DCOLOR_FULLALPHA_FILTER(COLOR)	(COLOR|0xff000000)

#define D3DCOLOR_AMASK(COLOR)				(COLOR&0x00ffffff)
#define D3DCOLOR_RMASK(COLOR)				(COLOR&0x00ff0000)
#define D3DCOLOR_GMASK(COLOR)				(COLOR&0x0000ff00)
#define D3DCOLOR_BMASK(COLOR)				(COLOR&0x000000ff)

/*#define D3DCOLOR_GETA(COLOR)				(D3DCOLOR_AMASK(COLOR)<<24)
#define D3DCOLOR_GETR(COLOR)				(D3DCOLOR_AMASK(COLOR)<<16)
#define D3DCOLOR_GETG(COLOR)				(D3DCOLOR_AMASK(COLOR)<<8)
#define D3DCOLOR_GETB(COLOR)				(D3DCOLOR_AMASK(COLOR))*/
//	2008/05/25  こっちの方が高速か？
#define D3DCOLOR_GETA(COLOR)				(((BYTE*)(&COLOR))[3])
#define D3DCOLOR_GETR(COLOR)				(((BYTE*)(&COLOR))[2])
#define D3DCOLOR_GETG(COLOR)				(((BYTE*)(&COLOR))[1])
#define D3DCOLOR_GETB(COLOR)				(((BYTE*)(&COLOR))[0])

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

////////////////////////////////
//
//		関数
//

//	実テクスチャサイズを算出
inline int GetRealTexSize( int nVirtualSize )
{
	for ( int i=2; i < nVirtualSize; i <<= 1 );
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

DLL_EXP const char* GetD3DResultString( DWORD nD3dResult );

DLL_EXP BOOL GetScreenSize( int* pnWidth, int* pnHeight );


#endif//__MglGraphicUtil_H__
