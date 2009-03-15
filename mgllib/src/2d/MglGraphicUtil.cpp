//////////////////////////////////////////////////////////
//
//	MglGraphicUtil
//		- MglGraphicManager関連でのマクロや関数を宣言
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglGraphicUtil.h"


//////////////////////////////
//
//		簡単RECT系関数
//
static RECT g_rect;

RECT* _Rect( int left, int top, int right, int bottom, RECT *destRect )
{
	if ( destRect == NULL )
		destRect = &g_rect;

	destRect->left = left;
	destRect->top = top;
	destRect->right = right;
	destRect->bottom = bottom;

	return destRect;
}

RECT* _Rect2( int left, int top, int width, int height, RECT *destRect )
{
	if ( destRect == NULL )
		destRect = &g_rect;

	destRect->left = left;
	destRect->top = top;
	destRect->right = left+width;
	destRect->bottom = top+height;

	return destRect;
}

RECT* EzRect( int left, int top, int right, int bottom, RECT *destRect )
{
	if ( destRect == NULL )
		destRect = &g_rect;

	destRect->left = left;
	destRect->top = top;
	destRect->right = right;
	destRect->bottom = bottom;

	return destRect;
}

RECT* EzRect2( int left, int top, int width, int height, RECT *destRect )
{
	if ( destRect == NULL )
		destRect = &g_rect;

	destRect->left = left;
	destRect->top = top;
	destRect->right = left+width;
	destRect->bottom = top+height;

	return destRect;
}

const char* GetD3DResultString( DWORD nD3dResult )
{
	static char buf[1024];
	switch( nD3dResult )
	{
	case D3D_OK:
		sprintf( buf, "D3D_OK/S_OK :: エラーは発生していません。" ); break;

	case D3DERR_CONFLICTINGRENDERSTATE:
		sprintf( buf, "D3DERR_CONFLICTINGRENDERSTATE" ); break;

	case D3DERR_CONFLICTINGTEXTUREFILTER:
		sprintf( buf, "D3DERR_CONFLICTINGTEXTUREFILTER" ); break;

	case D3DERR_CONFLICTINGTEXTUREPALETTE:
		sprintf( buf, "D3DERR_CONFLICTINGTEXTUREPALETTE" ); break;

	case D3DERR_DEVICELOST:
		sprintf( buf, "D3DERR_DEVICELOST :: デバイスがロストしています。" ); break;

	case D3DERR_DEVICENOTRESET:
		sprintf( buf, "D3DERR_DEVICENOTRESET :: デバイスはリセットできません。" ); break;

	case D3DERR_DRIVERINTERNALERROR:
		sprintf( buf, "D3DERR_DRIVERINTERNALERROR :: 内部ドライバエラー。" ); break;

	case D3DERR_INVALIDCALL:
		sprintf( buf, "D3DERR_INVALIDCALL :: メソッドの呼び出しが無効です。" ); break;

	case D3DERR_INVALIDDEVICE:
		sprintf( buf, "D3DERR_INVALIDDEVICE :: 要求されたデバイスの種類が有効ではありません。" ); break;

	case D3DERR_MOREDATA:
		sprintf( buf, "D3DERR_INVALIDDEVICE :: 指定されたバッファ サイズに保持できる以上のデータが存在します。" ); break;

	case D3DERR_NOTAVAILABLE:
		sprintf( buf, "D3DERR_NOTAVAILABLE :: このデバイスは、照会されたテクニックをサポートしていません。" ); break;

	case D3DERR_NOTFOUND:
		sprintf( buf, "D3DERR_NOTFOUND :: 要求された項目が見つかりません。" ); break;

	case D3DERR_OUTOFVIDEOMEMORY:
		sprintf( buf, "D3DERR_OUTOFVIDEOMEMORY :: ビデオメモリが不足しています。" ); break;

	case D3DERR_TOOMANYOPERATIONS:
		sprintf( buf, "D3DERR_TOOMANYOPERATIONS" ); break;

	case D3DERR_UNSUPPORTEDALPHAARG:
		sprintf( buf, "D3DERR_UNSUPPORTEDALPHAARG" ); break;

	case D3DERR_UNSUPPORTEDALPHAOPERATION:
		sprintf( buf, "D3DERR_UNSUPPORTEDALPHAOPERATION" ); break;

	case D3DERR_UNSUPPORTEDCOLOROPERATION:
		sprintf( buf, "D3DERR_UNSUPPORTEDCOLOROPERATION" ); break;

	case D3DERR_UNSUPPORTEDFACTORVALUE:
		sprintf( buf, "D3DERR_UNSUPPORTEDFACTORVALUE" ); break;

	case D3DERR_UNSUPPORTEDTEXTUREFILTER:
		sprintf( buf, "D3DERR_UNSUPPORTEDTEXTUREFILTER" ); break;

	case D3DERR_WRONGTEXTUREFORMAT:
		sprintf( buf, "D3DERR_WRONGTEXTUREFORMAT" ); break;

	case E_FAIL:
		sprintf( buf, "E_FAIL :: Direct3D サブシステム内で原因不明のエラーが発生しました。" ); break;

	case E_INVALIDARG:
		sprintf( buf, "E_INVALIDARG :: 無効なパラメータが戻ってくる関数に渡された。" ); break;

	/*
	case E_INVALIDCALL:
		sprintf( buf, "E_INVALIDCALL :: メソッドの呼び出しが無効です。" ); break;
	*/

	case E_OUTOFMEMORY:
		sprintf( buf, "E_OUTOFMEMORY :: メモリが不足しています。" ); break;

	default:
		sprintf( buf, "unknown :: Error Code = %d", nD3dResult );
	}

	return buf;
}

//	画面サイズの取得
BOOL GetScreenSize( int* pnWidth, int* pnHeight )
{
	HDC hDc = GetDC(NULL);
	if ( hDc == NULL )
		return FALSE;

	*pnWidth = GetDeviceCaps( hDc, HORZRES );
	*pnHeight = GetDeviceCaps( hDc, VERTRES );

	return TRUE;
}

/////////////////////////////////////////////////

NSMGLEX_START

//	D3DXMATRIX から D3DXVECTOR3 への変換
D3DXVECTOR3* D3DXMatrixToVector3
    ( D3DXVECTOR3 *pOutVector3, CONST D3DXMATRIX *pInMatrix )
{
	CONST D3DXMATRIX& m = *pInMatrix;

	pOutVector3->x =
		m.m[3][0] * m.m[0][0] +
		m.m[3][1] * m.m[1][0] +
		m.m[3][2] * m.m[2][0];

	pOutVector3->y =
		m.m[3][0] * m.m[0][1] +
		m.m[3][1] * m.m[1][1] +
		m.m[3][2] * m.m[2][1];

	pOutVector3->z =
		m.m[3][0] * m.m[0][2] +
		m.m[3][1] * m.m[1][2] +
		m.m[3][2] * m.m[2][2];

	return pOutVector3;
}

//	D3DXMatrixRotation系三ついっぺんに
D3DXMATRIX* D3DXMatrixRotation( D3DXMATRIX *pOut, float fAngleX, float fAngleY, float fAngleZ )
{
	D3DXMATRIX matX;
	D3DXMatrixRotationX(&matX, fAngleX);
	D3DXMATRIX matY;
	D3DXMatrixRotationY(&matY, fAngleY);
	D3DXMATRIX matZ;
	D3DXMatrixRotationZ(&matZ, fAngleZ);

	*pOut = matX * matY * matZ;
	return pOut;
}

NSMGLEX_END
