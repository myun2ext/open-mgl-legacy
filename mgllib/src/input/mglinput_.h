#ifndef __mglinput_2_H__
#define __mglinput_2_H__

#include "mglafx.h"

/*
//////////////////////
//
//	DLLエクスポート
//

#ifdef MGLLIB_EXPORTS
	#define DLL_EXP __declspec(dllexport)
#else
	#define DLL_EXP __declspec(dllimport)
#endif

/////////////////////////////////////

/*#include <msl.h>	//	07/01/01 Add.
#include <mwl.h>	//	07/01/02 Add.*//*

//#include "mglstd.h"

// VC でのSTLの警告を取り除きます。
#pragma warning( disable : 4786 ) 
#pragma warning( disable : 4251 )	//	template class でexportしてるのに出すなょｳｾﾞｰ(;´Д`)ゞ

#include <string>
#include <vector>
#include <map>
using namespace std;

#include <stdio.h>
#include <windows.h>
//#include "MyuDebugLog.h"
#include "MyuCommonException.h"
#include "MglExceptionThrowerBase.h"
#include "mglmsg.h"

//extern CMyuDebugLog g_workLog;

//	MGLマネージャ
/*
#define _MGL_MANAGER_INSTANCE	_g_mglManager
#define _EXTERN_MGL_MANAGER		extern CMglManager _MGL_MANAGER_INSTANCE
#define _MGL_DEBUGLOG			_MGL_MANAGER_INSTANCE.g_debugLog.Print
*/

/*
//	DirectInput系
#ifdef _MGL_USE_DXVER9
	#pragma comment(lib, "dinput9.lib")
	#define DIRECTINPUT_VERSION		(0x0900)
	
#elif _MGL_USE_DXVER10
	#pragma comment(lib, "dinput10.lib")
	#define DIRECTINPUT_VERSION		(0x1000)
	
#else
	#pragma comment(lib, "dinput8.lib")
	#define DIRECTINPUT_VERSION		(0x0800)

#endif

#include <dinput.h>
*/


#endif//__mglinput_2_H__