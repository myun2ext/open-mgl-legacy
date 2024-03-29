#ifndef __mgl_common_H__
#define __mgl_common_H__

#include "mglafx.h"

#include "MyuDebugLog.h"
#include "MyuCommonException.h"
#include "MglExceptionThrowerBase.h"
#include "MglExceptionCode.h"
#include "mglmsg.h"
#include "MglClassMsg.h"	//	2008/06/30  mgl_common.h に移動
#include "MyuSimpleStackTrace.h"

extern CMyuSimpleStackTrace g_stackTrace;

//////////////////////////////////////////////

//	クラス宣言
class CMglStackInstance : public CMyuStackInstance
{
public:
	CMglStackInstance(const char* szFunctionName) :
		CMyuStackInstance(&g_stackTrace,szFunctionName){}
};

class CMglInterfaceBase
{
public:
	void Delete();	//	mgl_global.cppに
};

#endif//__mgl_common_H__
