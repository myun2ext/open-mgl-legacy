#ifndef __AugustCommon2_H__
#define __AugustCommon2_H__

#include "mwlagh.h"

#ifdef MGLLIB_EXPORTS
	#define _AGST_DLL_EXP __declspec(dllexport)
	#define _AGST_DLL_TMPL_EXP template class _AGST_DLL_EXP			//	C4275�Ή�
	//#define DLL_TMPL_EXTERN
	//#define DLL_TMPL_EXTERN template
#else
	#define _AGST_DLL_EXP __declspec(dllimport)
	#define _AGST_DLL_TMPL_EXP /*extern*/ template class _AGST_DLL_EXP	//	C4275�Ή�
	//#define DLL_TMPL_EXTERN extern
	//#define DLL_TMPL_EXTERN extern template
#endif

#endif//__AugustCommon2_H__
