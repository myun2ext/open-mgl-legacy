//////////////////////////////////////////////////////////
//
//	August3dManager
//
//////////////////////////////////////////////////////////

#ifndef __August3dManager_H__
#define __August3dManager_H__

#include "agh.h"
#include "AugustCommon.h"
#include "Mgl3dManager.h"

#pragma warning( disable : 4275 ) 

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugust3dManager : public CAugustVisualControlBase
{
private:
	CMglGraphicManager *m_pGrp;

protected:
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);

public:
	//	コンストラクタ
	CAugust3dManager(){
		m_pGrp = NULL;
	}
};

#endif//__August3dManager_H__
