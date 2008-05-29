//////////////////////////////////////////////////////////
//
//	MyuEzGameManager  v0.10.00 05/02/21
//		- ゲーム管理クラス
//
//	v0.09.50 05/02/21
//	・忘れそうなのでとりあえず新規作成
//
//	v0.10.00 05/02/21
//	・とか言ってそれっぽく作ったり。
//
//////////////////////////////////////////////////////////

#ifndef __MyuEzGameManager_H__
#define __MyuEzGameManager_H__

#include "MyuEzWindow.h"

//	クラス宣言
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