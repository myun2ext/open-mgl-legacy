//////////////////////////////////////////////////////////
//
//	AugustMouseInput
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustMouseInput.h"
#include "MglInput.h"

using namespace agh;
using namespace std;

class DLL_EXP agh::CControlBase;

///////////////////////////////////////////////////////////////

//#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	�R�A�̊��N���X
class CAugustMouseCore : public agh::CMouseCoreBase
{
protected:
	CMglMouseInput m_mouse;
	_AGH_POINT m_oldCurPos;

private:
	_AGH_POINT GetMoveCount(agh::MOUSECODE_t mouseCode)
	{
		if ( mouseCode == agh::CMouseBase::CBUTTON ){

			long z = m_mouse.GetZMoveCount();
			if ( z == 0 )
				return _AGH_POINT(INVALID_POINT, INVALID_POINT);

			return _AGH_POINT(z, INVALID_POINT);	//	x��z������Ay�͎g���ĂȂ��B
		}
		else
		{
			/*	2��Ăяo���̂͌덷�������N�����\��������i�ƌ������N���Ă���ۂ��j�̂Ŏ��߂�
			_AGH_POINT moveCount = GetCursorPos() - m_oldCurPos;
			m_oldCurPos = GetCursorPos();
			*/
			_AGH_POINT curPos = GetCursorPos();
			_AGH_POINT moveCount = curPos - m_oldCurPos;
			m_oldCurPos = curPos;

			if ( moveCount.x == 0 && moveCount.y == 0 )	//	x��y���ړ���0�Ȃ�R�[���o�b�N���Ă΂Ȃ��悤�ɂ���
				return _AGH_POINT(INVALID_POINT, INVALID_POINT);
			else	
				return moveCount;

			/*
			long x = m_mouse.GetXMoveCount();
			long y = m_mouse.GetYMoveCount();
			
			if ( x != 0 && y != 0 )
				return _AGH_POINT(x, y);

			else	//	x��y���ړ���0�Ȃ�R�[���o�b�N���Ă΂Ȃ��悤�ɂ���
				return _AGH_POINT(INVALID_POINT, INVALID_POINT);*/
		}
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustMouseCore(){}
	virtual ~CAugustMouseCore(){}

	//	������
	void Init(HWND hWnd)
	{
		m_mouse.Init(hWnd);
		m_oldCurPos = GetCursorPos();
	}

	//////////////////////////////////////////////////////////

	/* override */
	virtual _AGH_POINT IsOnMouseEvt(agh::MOUSE_EVTTYPE_t evtType, agh::MOUSECODE_t mouseCode)
	{
		//	�ړ�
		if ( evtType == AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_MOVE )
			return GetMoveCount(mouseCode);

		BOOL isOnEvt = FALSE;

		//	mouseCode���L���Ȕ͈͓����ǂ����H
		if ( mouseCode >= AGH_MOUSECODE_LBUTTON && mouseCode <= AGH_MOUSECODE_8TH_BTN )
		{
			switch(evtType)
			{
			//	������Ă����
			case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_PRESS:
				isOnEvt = m_mouse.IsPressButton(mouseCode - 0x11);
				break;

			//	�����ꂽ�u��
			case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_DOWN:
				isOnEvt = m_mouse.IsOnDownButton(mouseCode - 0x11);
				break;

			//	�����ꂽ�u��
			case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_UP:
				isOnEvt = m_mouse.IsOnUpButton(mouseCode - 0x11);
				break;

//			//	�ړ�
//			case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_MOVE:
//				return GetMoveCount(mouseCode);
			}
		}

		//	�L���ȏꍇ�͌��݂̃J�[�\���ʒu���A�����ȏꍇ��(-9999,-9999)��Ԃ��B
		//	�i���Ȃ݂Ɉړ��̏ꍇ�͊���switch���̒���return���Ă���j
		if ( isOnEvt )
			return GetCursorPos();
		else
			return _AGH_POINT(INVALID_POINT, INVALID_POINT);
	}
	
	virtual _AGH_POINT GetCursorPos(){
		::POINT point = m_mouse.GetCursorPos();
		return _AGH_POINT(point.x, point.y);
	}

	agh::CPoint GetPrimitiveMoveCount()
	{
		return agh::CPoint( m_mouse.GetXMoveCount(), m_mouse.GetYMoveCount() );
	}

	//	�o�b�t�@�̍X�V
	void Update()
	{
		m_mouse.UpdateStateBuf();
	}
};

////////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CAugustMouseInput::CAugustMouseInput()
{
	m_pCore = new CAugustMouseCore();
}

//	�f�X�g���N�^
CAugustMouseInput::~CAugustMouseInput()
{
	delete m_pCore;
}

//	�o�^����Init���Ăяo��
void CAugustMouseInput::OnRegist()
{
	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustMouseInput::Init()  �E�C���h�E�n���h���̎擾�Ɏ��s");

	m_pParent->SetValPtr(AUGUST_VALKEY_MOUSE, this);	//	2009/05/18

	((CAugustMouseCore*)m_pCore)->Init(hWnd);
}

//	���t���[������Update()�Ăяo���̖Y��Ă��E�E�E
bool CAugustMouseInput::OnFrame()
{
	//	�X�e�[�^�X�o�b�t�@�̍X�V
	((CAugustMouseCore*)m_pCore)->Update();

	//	�X�[�p�[�N���X��OnFrame()�Ăяo��
	return agh::CMouseBase::OnFrame();
}

//	�J�[�\���擾�̎���
_AGH_POINT CAugustMouseInput::GetCursorPos()
{
	return ((CAugustMouseCore*)m_pCore)->GetCursorPos();
}

agh::CPoint CAugustMouseInput::GetPrimitiveMoveCount()
{
	return ((CAugustMouseCore*)m_pCore)->GetPrimitiveMoveCount();
}
