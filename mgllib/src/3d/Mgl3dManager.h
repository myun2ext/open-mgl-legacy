///////////////////////////////////////////////////////////////////////
//
//	Mgl3dManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __Mgl3dManager_H__
#define __Mgl3dManager_H__

#include "MglGraphicManager.h"
#include "MglMatrixManager.h"

//	クラス宣言
class DLL_EXP CMgl3dManager : public CMglMatrixManager //public virtual CMglDgBase
{
private:
	//	内部メソッド（チェック用）
	/*void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}*/

protected:

public:

	//////////////////////////
	//
	//		公開メソッド
	//

	//	コンストラクタ/デストラクタ
	CMgl3dManager();
	virtual ~CMgl3dManager();

	//	初期化/開放
	virtual void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	virtual void Release();

	/////////////////////////////////////////////////////////////////

	void OnFrame(){}

};
typedef CMgl3dManager CMgl3DManager;

#endif//__Mgl3dManager_H__
