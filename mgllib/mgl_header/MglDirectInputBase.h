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

//	クラス宣言
class DLL_EXP CMglDirectInputBase
{
private:
	static int m_nRef;

protected:
	//	みんなで共用する IDirectInput8 インスタンス
	static IDirectInput8 *m_pDi;

	//	コイツを呼び出す
	void InitBase();

public:
	//	コンストラクタ・デストラクタ
	CMglDirectInputBase();
	virtual ~CMglDirectInputBase();

	void FinalRelease();
};


#endif//__MglDirectInputBase_H__