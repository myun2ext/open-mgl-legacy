//////////////////////////////////////////////////////////
//
//	MyuDirectInput
//		- DirectInputクラス
//
//////////////////////////////////////////////////////////

#ifndef __MyuDirectInput_H__
#define __MyuDirectInput_H__

#include "MyuKeyboardInput.h"
#include "MyuTimer.h"

#define RELATE_NAME_MAX	(64)	//	関連付け名サイズ
#define RELATE_MAX		(256)	//	最大関連付け構造体数

//	関連付け構造体風クラス
//	（構造体だとクラスを持てないので…）
//typedef struct
class DLL_EXP INPUT_RELATE
{
public:
	char szInputName[RELATE_NAME_MAX];
	BYTE keyCode;
	/* ジョイパッド等 */

	BOOL oldKeyPush;
	BOOL keyPool;
	CMyuTimer timer;
};

//	関連付け構造体
/*typedef struct
{
	char szInputName[RELATE_NAME_MAX];
	BYTE keyCode;
	/* ジョイパッド等 *

	BOOL oldKeyPush;
	BOOL keyPool;

} INPUT_RELATE;
*/

////////////////////////////////////////////
//
//		クラス宣言
//
class DLL_EXP CMyuDirectInput : public CMyuKeyboardInput
{
protected:
	INPUT_RELATE relate[RELATE_MAX];
	int nRelateCnt;
	BOOL m_autoGetBuf;

	//	内部メソッド
	INPUT_RELATE* GetRelate( const char *szInputName );

public:
	CMyuDirectInput();
	virtual ~CMyuDirectInput();

	void Init( HWND hWnd, BOOL in_autoGetBuf=FALSE );
	void ClearList();

	void RelateKey( const char *szInputName, BYTE keyCode );
	BOOL IsDownKey( const char *szInputName );
	//BOOL IsUpKey( const char *szInputName );
	BOOL IsPushKey( const char *szInputName );
	void GetBuf();
};


#endif//__MyuDirectInput_H__