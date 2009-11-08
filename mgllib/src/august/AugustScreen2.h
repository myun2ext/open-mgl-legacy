//////////////////////////////////////////////////////////
//
//	AugustScreen2
//
//////////////////////////////////////////////////////////

#ifndef __AugustScreen2_H__
#define __AugustScreen2_H__

#include "AugustWindow2.h"
#include "AugustGraphicsManager.h"
#include "MwlMxpThreadBase.h"

//////////////////////////////////////////////////////////////////////////////////////

class CMyuFPS;

class _AGST_DLL_EXP CAugustFpsManager : public agh::CControlBase
{
protected:
	CMyuFPS* m_pInternal;
public:
	CAugustFpsManager();
	virtual ~CAugustFpsManager();

	void DoWait();
	void SetFps(int nFps);
	float GetAveFps();
	float GetFps();

	void SetFPS(int nFps){ SetFps(nFps); }
	float GetAveFPS(){ return GetAveFps(); }
	float GetFPS(){ return GetFps(); }
};

/////////////////////////////////////////////////////////////////////////

#define _CAugustScreen2_THREAD_BASE CMwlMxpThreadBase
//#define _CAugustScreen2_WINDOW_BASE CMwlAghWindow
#define _CAugustScreen2_WINDOW_BASE CAugustWindow2

class _CAugustScreen2_THREAD_BASE;
class _CAugustScreen2_WINDOW_BASE;
class agh::CScreenBase;
class CMyuReleaseBase;

//	�N���X�錾  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustScreen2 : public CAugustWindow2, public CMyuThreadBase
class CAugustScreen2 : public _CAugustScreen2_WINDOW_BASE, public _CAugustScreen2_THREAD_BASE
{
private:
	//typedef CAugustWindow2 _BASE;
	typedef _CAugustScreen2_WINDOW_BASE _BASE, _WIN_BASE, _WINDOW_BASE;
	typedef _CAugustScreen2_THREAD_BASE _THREAD_BASE;

	bool _AGST_DLL_EXP ThreadFuncMain();

	void PreWindowCloseRelease();

protected:
	CAugustGraphicsManager m_grp;	//	Control
	CAugustFpsManager m_fps;		//	Control
	void* m_vphWnd;

	//	2009/08/27 - �E�C���h�E���J������O��Release���Ăяo���ׂ��N���X�̃��X�g
	std::vector<CMyuReleaseBase*> m_releaseList;

	/////////////////////////////////////////////////////////

	//HWND m_hWnd;
	//bool m_bUseMouseHandle; v2����͗v��Ȃ�������
	bool m_bEndFlg;

protected:
	bool _AGST_DLL_EXP DoFpsWait();
	bool _AGST_DLL_EXP ThreadFunc(int anyParam);	//	From mxp::CThreadBase overrided
	bool _AGST_DLL_EXP WaitEndThread();

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	/**
	  �����ɂ����� OnControl, OnBackground �͉��Ɉړ����Ƃ�����B
	**/

	virtual _AGST_DLL_EXP void OnDraw();
	virtual _AGST_DLL_EXP bool OnClose();
	virtual _AGST_DLL_EXP void OnClosedWindow();
	virtual bool OnFrame(){return OnFrameDoUser();}

	//	���̃N���X����
	virtual bool OnFrameDoUser(){return true;}
	//virtual bool OnFrameKeyboardInput();
	//virtual bool OnFrameMouseInput();

	virtual bool OnInitFirst(){ return true; }	//	false��Ԃ��ƃv���O�����I��
	virtual bool OnReady(){ return OnGraphicInitEnded(); }	//	false��Ԃ��ƃv���O�����I��
	virtual bool OnGraphicInitEnded(){ return true; }	//	false��Ԃ��ƃv���O�����I��
	virtual bool OnInited(){ return true; }	//	false��Ԃ��ƃv���O�����I��
	virtual _AGST_DLL_EXP void MainLoop();

	/////////////////////////////////////////////////////////////
	//	���̃N���X�Ŏ������� 

	virtual void OnCreatedWindow(){
		_BASE::OnCreatedWindow();

		//m_vphWnd = (void*)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_HWND),
		//	"CAugustScreen2::OnCreatedWindow()  �E�C���h�E�n���h���̎擾�Ɏ��s");
		m_vphWnd = (void*)GetValPtr(MWLAGH_VALKEY_HWND);

		//	2009/05/03  �ǉ����Ă˂������E�E�E
		_BASE::RegistSubControl(&m_grp);
		_BASE::RegistSubControl(&m_fps);

		_THREAD_BASE::StartThread(0);
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	//_AGST_DLL_EXP CAugustScreen2();	DLL_EXP���_���I�[�b�^�C�I
	//			�i�����ڂ������ׂĂȂ����Ǐ�肭�s���Ȃ����ۂ��B�����p�����Ă�N���X�̃R���X�g���N�^���Ă΂�ĂȂ��j
	CAugustScreen2()
	{
		m_bEndFlg = false;
		m_vphWnd = NULL;
		//m_bUseMouseHandle = false;

		SetValPtr(AUGUST_VALKEY_SCREEN, this);
	}
	virtual ~CAugustScreen2(){}

	///////////////////////////////////////////////////////

	/*
	//	friend�ɂ��������������낤���E�E�E�H
	void _AddToReleaseList(CMyuReleaseBase* pInstance){
		m_releaseList.push_back(pInstance);
	}
	*/
	//virtual void Start();	//	�X���b�h�I���҂����邽�߂̃I�[�o�[���C�h
	virtual _AGST_DLL_EXP bool DoFrame();
};

class CAugustScreen2_X : public CAugustScreen2
{
public:
	CAugustScreen2_X(){}
	virtual ~CAugustScreen2_X(){}

	void AddToReleaseList(CMyuReleaseBase* pInstance){
		m_releaseList.push_back(pInstance);
	}
};

typedef CAugustScreen2 CAugustFrame2, CAugustWindowFrame2;

#endif//__AugustScreen2_H__
