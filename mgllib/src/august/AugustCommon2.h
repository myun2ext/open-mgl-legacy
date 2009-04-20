#ifndef __AugustCommon2_H__
#define __AugustCommon2_H__

//#define __MWLAGH_NOT_USE_SLIB
#include "agh.h"
#include "mwlagh.h"

#ifdef MGLLIB_EXPORTS
	#define _AGST_DLL_EXP __declspec(dllexport)
	#define _AGST_DLL_TMPL_EXP template class _AGST_DLL_EXP			//	C4275‘Î‰ž
	//#define DLL_TMPL_EXTERN
	//#define DLL_TMPL_EXTERN template
#else
	#define _AGST_DLL_EXP __declspec(dllimport)
	#define _AGST_DLL_TMPL_EXP /*extern*/ template class _AGST_DLL_EXP	//	C4275‘Î‰ž
	//#define DLL_TMPL_EXTERN extern
	//#define DLL_TMPL_EXTERN extern template

	//	2009/04/16 Add.
	#pragma comment(lib, "mgllib.lib")

#endif

class DLL_EXP agh::CControlBase;

#endif//__AugustCommon2_H__
