//////////////////////////////////////////////////////////
//
//	MyuEzGameManager  v0.10.00 05/02/21
//		- �Q�[���Ǘ��N���X
//
//	v0.09.50 05/02/21
//	�E�Y�ꂻ���Ȃ̂łƂ肠�����V�K�쐬
//
//	v0.10.00 05/02/21
//	�E�Ƃ������Ă�����ۂ��������B
//
//////////////////////////////////////////////////////////

#ifndef __MyuEzGameManager_H__
#define __MyuEzGameManager_H__

#include "MyuEzWindow.h"

//	�N���X�錾
class DLL_EXP CMyuEzGameManager : public CMyuEzWindow
{
private:
	BOOL m_bGameAlive;

public:
	CMyuEzGameManager();
	virtual ~CMyuEzGameManager();

	BOOL IsGameAlive()
	{
		if ( CMyuEzWindow::IsAlive() != TRUE )
			return FALSE;
		return m_bGameAlive;
	}
	void SetGameEnd() { m_bGameAlive = FALSE; }
};

#endif//__MyuEzGameManager_H__