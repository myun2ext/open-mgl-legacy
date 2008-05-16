///////////////////////////////////////////////////////////////////////
//
//	CMglDirectInputBase
//	IDirectInput8 を管理するクラス。
//	インスタンスは一つしか作らせない。みんなで一つのIDirectInput8 を共用して使わせる。
//	なので別にvirtual継承とかする必要性は無い
//	参照カウンタが0になるとインスタンスは開放される。
//
///////////////////////////////////////////////////////////////////////
#ifndef __MglDirectInputBase_H__
#define __MglDirectInputBase_H__

//#include "mglinput_.h"
//#include <dinput.h>

//	DirectInput系
#ifdef _MGL_USE_DXVER9
	#ifndef IDirectInput9
		#pragma message("エラー: IDirectInput9 が定義されていません。<dinput.h> のバージョンを確認してください。（もしかして Visual C++ 標準の dinput.h を読み込んでいる？）")
		#error IDirectInput9 was not defined!! Please confirm the version of <dinput.h>. (Do because it is <dinput.h> of the Visual C++ standard?)

	#endif
#elif _MGL_USE_DXVER10
	#ifndef IDirectInput10
		#pragma message("エラー: IDirectInput10 が定義されていません。<dinput.h> のバージョンを確認してください。（もしかして Visual C++ 標準の dinput.h を読み込んでいる？）")
		#error IDirectInput10 was not defined!! Please confirm the version of <dinput.h>. (Do because it is <dinput.h> of the Visual C++ standard?)
	#endif
#else
	#ifndef IDirectInput8
		#pragma message("エラー: IDirectInput8 が定義されていません。<dinput.h> のバージョンを確認してください。（もしかして Visual C++ 標準の dinput.h を読み込んでいる？）")
		#error IDirectInput8 was not defined!! Please confirm the version of <dinput.h>. (Do because it is <dinput.h> of the Visual C++ standard?)
		//#error IDirectInput8 was not defined.
	#endif
#endif


//	クラス宣言
class DLL_EXP CMglDirectInputBase
{
private:
	static int m_nRef;

protected:
	//	みんなで共用する IDirectInput インスタンス
	static _MGL_IDirectInput *m_pDi;

	//	コイツを呼び出す
	void InitBase();

public:
	//	コンストラクタ・デストラクタ
	CMglDirectInputBase();
	virtual ~CMglDirectInputBase();

	void FinalRelease();
};


#endif//__MglDirectInputBase_H__
