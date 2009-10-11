#ifndef __AugustCommon2_H__
#define __AugustCommon2_H__

//#define __MWLAGH_NOT_USE_SLIB
#include "agh.h"
#include "mwlagh.h"

#include "MyuCommonException.h"
#include "mglmsg.h"


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


#define AUGUST_VALKEY_					(AGH_VALKEY_USER_FIRST+0x18A60000)	//	���Ȃ������ɓK���Ȑ����B18A6

#define AUGUST_VALKEY_SCREEN			(AUGUST_VALKEY_ + 0x0200)

#define AUGUST_VALKEY_GRP				(AUGUST_VALKEY_ + 0x0359)
#define AUGUST_VALKEY_PGRP				(AUGUST_VALKEY_GRP)		//	Alias
#define AUGUST_VALKEY_P_GRP				(AUGUST_VALKEY_GRP)		//	Alias

#define AUGUST_VALKEY_AGRPM				(AUGUST_VALKEY_ + 0x0381)

#define AUGUST_VALKEY_IMG_LOADER		(AUGUST_VALKEY_ + 0x0382)
#define AUGUST_VALKEY_IMAGE_LOADER		(AUGUST_VALKEY_IMG_LOADER)

#define AUGUST_VALKEY_AGRPM				(AUGUST_VALKEY_ + 0x0381)

#define AUGUST_VALKEY_MOUSE				(AUGUST_VALKEY_ + 0x0500)
#define AUGUST_VALKEY_PMOUSE			(AUGUST_VALKEY_MOUSE)	//	Alias
#define AUGUST_VALKEY_P_MOUSE			(AUGUST_VALKEY_MOUSE)	//	Alias

#define AUGUST_VALKEY_SOUNDMGR			(AUGUST_VALKEY_ + 0x0600)
#define AUGUST_VALKEY_PSOUND			(AUGUST_VALKEY_SOUNDMGR)
#define AUGUST_VALKEY_PSOUNDMGR			(AUGUST_VALKEY_SOUNDMGR)
#define AUGUST_VALKEY_P_SOUND			(AUGUST_VALKEY_SOUNDMGR)
#define AUGUST_VALKEY_P_SOUNDMGR		(AUGUST_VALKEY_SOUNDMGR)


////////////////////////////////////////////////////////////////////////////////

//#define AugustThrow	MyuThrow


//	��O�^
#define _AUGUST_EXCEPTION_MSG_MAX		(1024)
typedef struct
{
	unsigned long nCode;
	//str::string strMsg;
	char szMsg[_AUGUST_EXCEPTION_MSG_MAX+1];
}
AugustException;


//	��O�𓊂���
void _AGST_DLL_EXP AugustThrow( unsigned long nCode, const char* szMsgFormat, ... );


/////////////////////

#define AUGUST_MSGNO_COMMON__(no)			MGLMSGNO_AUGUST(0x1000000+no)
#define AUGUST_MSGNO_CONTROL_BASE_(no)		AUGUST_MSGNO_COMMON__(0x1030)

#define AUGUST_MSGNO_NO_PARENT				AUGUST_MSGNO_CONTROL_BASE_(1)	/*	�e�R���g���[��������܂���	*/

/***********************************************************************************/


//	August Framework �N���X�̊��
template <typename T>
class CAugustControlBaseT : public T
{
public:
	/*	agh::CControlBase �Œ�`����Ă��鎖�����҂��Ă��郁�\�b�h�i�Č������܂�����񂾂��ǁj  */
	//virtual bool IsRegisted()=0;

protected:
	std::string m_strClassName;

	void SetClassName(const char* szClassName){ m_strClassName = szClassName; }

	void RegistCheck(){
		if ( IsRegisted() == false )
			//AugustThrow( 9999, "%s  �e�̃R���g���[�������݂��܂���BRegistControl()�ɂĐe�R���g���[���ւ̓o�^���s���Ă��������B", m_strClassName.c_str() );
			AugustThrow( AUGUST_MSGNO_NO_PARENT, "%s �ɑ΂�������s���ɂ͐e�R���g���[���Ƃ̊֘A�t�����K�v�ł��B\r\n[�e�R���g���[��].RegistControl() �ɂĐe�R���g���[���ւ̊֘A�t�����s���Ă��������B", m_strClassName.c_str() );
	}
	void RegistedCheck(){ RegistCheck(); }

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//CAugustControlBase(){}
	CAugustControlBaseT(const char* szClassName){ SetClassName(szClassName); }
	virtual ~CAugustControlBaseT(){}
};

typedef CAugustControlBaseT<agh::CControlBase> CAugustControlBase;



/***********************************************************************************/


////////////////////////////////////////////////////
//
//	CAugustVisualControlBaseT
//


//	�������\�b�h
void _AGST_DLL_EXP _AugustPaintRect(AGHCOLOR color, agh::CRect rect);

class CAugustGraphicsManager;
class CMglGraphicManager;

//	�N���X�錾
template <typename T> /* T=CAugustControlBaseT�A�Ȃ���CAugustControlBaseT���p�������N���X�ł��鎖���O��	*/
class CAugustVisualControlBaseT : public T
{
protected:
	CAugustGraphicsManager* m_pAGrpMgr;
	CMglGraphicManager *m_pGrp;

_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist(){
		m_pAGrpMgr = (CAugustGraphicsManager*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_AGRPM),
			"%s:  AUGUST_VALKEY_IMAGE_LOADER �̎擾�Ɏ��s�B", m_strClassName.c_str() );
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//CAugustControlBase(){}
	CAugustVisualControlBaseT(const char* szClassName) : T(szClassName) { m_pAGrpMgr = NULL; }
	virtual ~CAugustVisualControlBaseT(){}

	//////////////////////////////////////////

	virtual void PaintBackground(AGHCOLOR color){ _AugustPaintRect(color, m_rect); }
	//virtual void PaintBackground(AGHCOLOR color);
};



/***********************************************************************************/



//	Load()���������郁�\�b�h�̊��N���X
class CAugustLoadable
{
public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustLoadable(){}
	virtual ~CAugustLoadable(){}

	virtual bool Load(const char* szFileName)=0;
};

#endif//__AugustCommon2_H__





#if 1 == 0
//	August Framework �N���X�̊��
class _AGST_DLL_EXP CAugustControlBase : public virtual agh::CControlBase
{
public:
	/*	agh::CControlBase �Œ�`����Ă��鎖�����҂��Ă��郁�\�b�h�i�Č������܂�����񂾂��ǁj  */
	//virtual bool IsRegisted()=0;

protected:
	std::string m_strClassName;

	void SetClassName(const char* szClassName){ m_strClassName = szClassName; }

	void RegistCheck(){
		if ( IsRegisted() == false )
			//AugustThrow( 9999, "%s  �e�̃R���g���[�������݂��܂���BRegistControl()�ɂĐe�R���g���[���ւ̓o�^���s���Ă��������B", m_strClassName.c_str() );
			AugustThrow( MGLMSGNO_AUGUST(0x01001031), "%s �ɂ͐e�R���g���[�����K�v�ł��B [�e�R���g���[��].RegistControl() �ɂĐe�R���g���[���ւ̓o�^���s���Ă��������B", m_strClassName.c_str() );
	}
	void RegistedCheck(){ RegistCheck(); }

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//CAugustControlBase(){}
	CAugustControlBase(const char* szClassName){ SetClassName(szClassName); }
	virtual ~CAugustControlBase(){}
};
#endif


/***********************************************************************************/