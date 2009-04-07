#ifndef __AugustCtrlBase_H__
#define __AugustCtrlBase_H__

#include "agh.h"

//	クラス宣言
class DLL_EXP CAugustCtrlBase
{
protected:
	void *m_pImplRoot;
public:
	//	コンストラクタ・デストラクタ
	CAugustCtrlBase(){ m_pImplRoot = NULL; }
	virtual ~CAugustCtrlBase(){}

	virtual agh::CControlBase* _GetAghControl()=0;
	virtual void* _GetImplRoot(){ return m_pImplRoot; }
};

#endif//__AugustCtrlBase_H__
