#ifndef __AugustCommon2_H__
#define __AugustCommon2_H__

//#define __MWLAGH_NOT_USE_SLIB
#include "agh.h"
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

	//	2009/04/16 Add.
	#pragma comment(lib, "mgllib.lib")

#endif

class _AGST_DLL_EXP agh::CControlBase;


#define AUGUST_VALKEY_					(AGH_VALKEY_USER_FIRST+0x18A60000)
#define AUGUST_VALKEY_GRP				(AUGUST_VALKEY_ + 0x0359)
#define AUGUST_VALKEY_PGRP				(AUGUST_VALKEY_GRP)		//	Alias
#define AUGUST_VALKEY_P_GRP				(AUGUST_VALKEY_GRP)		//	Alias

#define AUGUST_VALKEY_AGRPM				(AUGUST_VALKEY_ + 0x0381)

#define AUGUST_VALKEY_IMG_LOADER		(AUGUST_VALKEY_ + 0x0382)
#define AUGUST_VALKEY_IMAGE_LOADER		(AUGUST_VALKEY_IMG_LOADER)

#define AUGUST_VALKEY_MOUSE				(AUGUST_VALKEY_ + 0x0500)
#define AUGUST_VALKEY_PMOUSE			(AUGUST_VALKEY_MOUSE)	//	Alias
#define AUGUST_VALKEY_P_MOUSE			(AUGUST_VALKEY_MOUSE)	//	Alias


#endif//__AugustCommon2_H__
