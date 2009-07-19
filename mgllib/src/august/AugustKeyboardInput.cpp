//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustKeyboardInput.h"
#include "MglInput.h"

using namespace agh;
using namespace std;

class DLL_EXP agh::CControlBase;

///////////////////////////////////////////////////////////////

#define AUGUST_KEYCODE_TABLE_SIZE	(256)

//#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	コアの基底クラス
class CAugustKeyboardCore : public agh::CKeyboardCoreBase
{
protected:
	CMglKeyboardInput m_input;

	static int m_keyCodeTable[AUGUST_KEYCODE_TABLE_SIZE];
	static bool m_bKeyCodeTableInited;

private:
	void GenKcTable();

public:
	virtual bool IsOnKeyEvt(agh::KB_EVTTYPE_t evtType, agh::KEYCODE_t keyCode)
	{
		switch(evtType)
		{
		//	押されている間
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_PRESS:
			
			break;

		//	キーボードが押された瞬間
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN:
			break;

		//	キーボードが話された瞬間
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP:
			break;
		}

		return false;
	}
};

int CAugustKeyboardCore::m_keyCodeTable[AUGUST_KEYCODE_TABLE_SIZE];
bool CAugustKeyboardCore::m_bKeyCodeTableInited = false;

//	テーブルの生成
void CAugustKeyboardCore::GenKcTable()
{
	if ( m_bKeyCodeTableInited == true )
		return;

	ZeroMemory( m_keyCodeTable, sizeof(m_keyCodeTable) );

	//	配列の生成
	m_keyCodeTable['0'] = DIK_0;
	m_keyCodeTable['1'] = DIK_1;
	m_keyCodeTable['2'] = DIK_2;
	m_keyCodeTable['3'] = DIK_3;
	m_keyCodeTable['4'] = DIK_4;
	m_keyCodeTable['5'] = DIK_5;
	m_keyCodeTable['6'] = DIK_6;
	m_keyCodeTable['7'] = DIK_7;
	m_keyCodeTable['8'] = DIK_8;
	m_keyCodeTable['9'] = DIK_9;

	m_keyCodeTable['A'] = DIK_A;
	m_keyCodeTable['B'] = DIK_B;
	m_keyCodeTable['C'] = DIK_C;
	m_keyCodeTable['D'] = DIK_D;
	m_keyCodeTable['E'] = DIK_E;
	m_keyCodeTable['F'] = DIK_F;
	m_keyCodeTable['G'] = DIK_G;
	m_keyCodeTable['H'] = DIK_H;
	m_keyCodeTable['I'] = DIK_I;
	m_keyCodeTable['J'] = DIK_J;
	m_keyCodeTable['K'] = DIK_K;
	m_keyCodeTable['L'] = DIK_L;
	m_keyCodeTable['M'] = DIK_M;
	m_keyCodeTable['N'] = DIK_N;
	m_keyCodeTable['O'] = DIK_O;
	m_keyCodeTable['P'] = DIK_P;
	m_keyCodeTable['Q'] = DIK_Q;
	m_keyCodeTable['R'] = DIK_R;
	m_keyCodeTable['S'] = DIK_S;
	m_keyCodeTable['T'] = DIK_T;
	m_keyCodeTable['U'] = DIK_U;
	m_keyCodeTable['V'] = DIK_V;
	m_keyCodeTable['W'] = DIK_W;
	m_keyCodeTable['X'] = DIK_X;
	m_keyCodeTable['Y'] = DIK_Y;
	m_keyCodeTable['Z'] = DIK_Z;

	//	記号系  2007/01/02
	m_keyCodeTable['-'] = DIK_MINUS;
	m_keyCodeTable[','] = DIK_COMMA;
	m_keyCodeTable['.'] = DIK_PERIOD;
	m_keyCodeTable['/'] = DIK_SLASH;
	m_keyCodeTable[';'] = DIK_SEMICOLON;
	m_keyCodeTable[':'] = DIK_COLON;
	m_keyCodeTable['@'] = DIK_AT;
	m_keyCodeTable['['] = DIK_LBRACKET;
	m_keyCodeTable[']'] = DIK_RBRACKET;
	m_keyCodeTable['\\'] = DIK_YEN;
	m_keyCodeTable['^'] = DIK_CIRCUMFLEX;
	//m_keyCodeTable['?'] = DIK_SLASH;	//	ダミー

	m_keyCodeTable['a'] = DIK_A;
	m_keyCodeTable['b'] = DIK_B;
	m_keyCodeTable['c'] = DIK_C;
	m_keyCodeTable['d'] = DIK_D;
	m_keyCodeTable['e'] = DIK_E;
	m_keyCodeTable['f'] = DIK_F;
	m_keyCodeTable['g'] = DIK_G;
	m_keyCodeTable['h'] = DIK_H;
	m_keyCodeTable['i'] = DIK_I;
	m_keyCodeTable['j'] = DIK_J;
	m_keyCodeTable['k'] = DIK_K;
	m_keyCodeTable['l'] = DIK_L;
	m_keyCodeTable['m'] = DIK_M;
	m_keyCodeTable['n'] = DIK_N;
	m_keyCodeTable['o'] = DIK_O;
	m_keyCodeTable['p'] = DIK_P;
	m_keyCodeTable['q'] = DIK_Q;
	m_keyCodeTable['r'] = DIK_R;
	m_keyCodeTable['s'] = DIK_S;
	m_keyCodeTable['t'] = DIK_T;
	m_keyCodeTable['u'] = DIK_U;
	m_keyCodeTable['v'] = DIK_V;
	m_keyCodeTable['w'] = DIK_W;
	m_keyCodeTable['x'] = DIK_X;
	m_keyCodeTable['y'] = DIK_Y;
	m_keyCodeTable['z'] = DIK_Z;

	//	小文字はどうする・・・？
	/*
	if ( m_bCaptialReverse )
	{
		m_keyCodeTable['a'] = DIK_A;
		m_keyCodeTable['b'] = DIK_B;
		m_keyCodeTable['c'] = DIK_C;
		m_keyCodeTable['d'] = DIK_D;
		m_keyCodeTable['e'] = DIK_E;
		m_keyCodeTable['f'] = DIK_F;
		m_keyCodeTable['g'] = DIK_G;
			:
			:
	*/

	//	GetOnKeyList 用の追加リスト 2007/01/01
	m_keyCodeTable[ASCII_BS] =		DIK_BACKSPACE;
	//m_keyCodeTable[ASCII_TAB] =	DIK_TAB;
	m_keyCodeTable['\t'] =			DIK_TAB;
	m_keyCodeTable[ASCII_ENTER] =	DIK_RETURN;
	m_keyCodeTable[ASCII_ESC] =		DIK_ESCAPE;
	//m_keyCodeTable[ASCII_SP] =	DIK_SPACE;
	m_keyCodeTable[' '] =			DIK_SPACE;
	m_keyCodeTable[ASCII_DELETE] =	DIK_DELETE;

	/* ######################################################## */
	/*                     */
	/*   AGH 固有のコード  */
	/*                     */
	/* ######################################################## */


	m_keyCodeTable[AGH_KEYCODE_UP]		=	DIK_UP;
	m_keyCodeTable[AGH_KEYCODE_DOWN]	=	DIK_DOWN;
	m_keyCodeTable[AGH_KEYCODE_LEFT]	=	DIK_LEFT;
	m_keyCodeTable[AGH_KEYCODE_RIGHT]	=	DIK_RIGHT;

	m_keyCodeTable[AGH_KEYCODE_LCTRL]	=	DIK_LCONTROL;
	m_keyCodeTable[AGH_KEYCODE_RCTRL]	=	DIK_RCONTROL;
	m_keyCodeTable[AGH_KEYCODE_LSHIFT]	=	DIK_LSHIFT;
	m_keyCodeTable[AGH_KEYCODE_RSHIFT]	=	DIK_RSHIFT;
	m_keyCodeTable[AGH_KEYCODE_LALT]	=	DIK_LALT;
	m_keyCodeTable[AGH_KEYCODE_RALT]	=	DIK_RALT;
	m_keyCodeTable[AGH_KEYCODE_LWIN]	=	DIK_LWIN;
	m_keyCodeTable[AGH_KEYCODE_RWIN]	=	DIK_RWIN;
	m_keyCodeTable[AGH_KEYCODE_MENU]	=	DIK_RMENU;

	m_keyCodeTable[AGH_KEYCODE_CAPSLOCK]=	DIK_CAPSLOCK;
	m_keyCodeTable[AGH_KEYCODE_KANJI]	=	DIK_KANJI;
	m_keyCodeTable[AGH_KEYCODE_KANA]	=	DIK_KANA;
	m_keyCodeTable[AGH_KEYCODE_MUHENKAN]=	DIK_NOCONVERT;
	m_keyCodeTable[AGH_KEYCODE_HENKAN]	=	DIK_CONVERT;

	m_keyCodeTable[AGH_KEYCODE_INSERT]	=	DIK_INSERT;
	m_keyCodeTable[AGH_KEYCODE_HOME]	=	DIK_HOME;
	m_keyCodeTable[AGH_KEYCODE_END]		=	DIK_END;
	m_keyCodeTable[AGH_KEYCODE_PGDOWN]	=	DIK_PGDN;
	m_keyCodeTable[AGH_KEYCODE_PGUP]	=	DIK_PGUP;

	m_keyCodeTable[AGH_KEYCODE_F1]		=	DIK_F1;
	m_keyCodeTable[AGH_KEYCODE_F2]		=	DIK_F2;
	m_keyCodeTable[AGH_KEYCODE_F3]		=	DIK_F3;
	m_keyCodeTable[AGH_KEYCODE_F4]		=	DIK_F4;
	m_keyCodeTable[AGH_KEYCODE_F5]		=	DIK_F5;
	m_keyCodeTable[AGH_KEYCODE_F6]		=	DIK_F6;
	m_keyCodeTable[AGH_KEYCODE_F7]		=	DIK_F7;
	m_keyCodeTable[AGH_KEYCODE_F8]		=	DIK_F8;
	m_keyCodeTable[AGH_KEYCODE_F9]		=	DIK_F9;
	m_keyCodeTable[AGH_KEYCODE_F10]		=	DIK_F10;
	m_keyCodeTable[AGH_KEYCODE_F11]		=	DIK_F11;
	m_keyCodeTable[AGH_KEYCODE_F12]		=	DIK_F12;
	m_keyCodeTable[AGH_KEYCODE_F13]		=	DIK_F13;
	m_keyCodeTable[AGH_KEYCODE_F14]		=	DIK_F14;
	m_keyCodeTable[AGH_KEYCODE_F15]		=	DIK_F15;
	//m_keyCodeTable[AGH_KEYCODE_F16]	=	DIK_F16;	//	DirectInputでは定義されていないようだ

	m_bKeyCodeTableInited = true;
}

///////////////////////////////////////////////////////////////////////////

//	コンストラクタ
CAugustKeyboardInput::CAugustKeyboardInput()
{
	m_pCore = new CAugustKeyboardCore();
}

//	デストラクタ
CAugustKeyboardInput::~CAugustKeyboardInput()
{
	delete m_pCore;
}




