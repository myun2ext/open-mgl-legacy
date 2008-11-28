#include "stdafx.h"
#include "MglKeyboardInput.h"

#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

int CMglKeyboardInput::m_kbFastRtAry[FAST_RT_ARY_SIZE];
bool CMglKeyboardInput::m_kbFastRtAryInited = false;

//	�֘A�t���z��̐���
void CMglKeyboardInput::GenRtAry()
{
	if ( m_kbFastRtAryInited == true )
		return;

	ZeroMemory( m_kbFastRtAry, sizeof(m_kbFastRtAry) );

	//	�z��̐���
	m_kbFastRtAry['0'] = DIK_0;
	m_kbFastRtAry['1'] = DIK_1;
	m_kbFastRtAry['2'] = DIK_2;
	m_kbFastRtAry['3'] = DIK_3;
	m_kbFastRtAry['4'] = DIK_4;
	m_kbFastRtAry['5'] = DIK_5;
	m_kbFastRtAry['6'] = DIK_6;
	m_kbFastRtAry['7'] = DIK_7;
	m_kbFastRtAry['8'] = DIK_8;
	m_kbFastRtAry['9'] = DIK_9;

	m_kbFastRtAry['A'] = DIK_A;
	m_kbFastRtAry['B'] = DIK_B;
	m_kbFastRtAry['C'] = DIK_C;
	m_kbFastRtAry['D'] = DIK_D;
	m_kbFastRtAry['E'] = DIK_E;
	m_kbFastRtAry['F'] = DIK_F;
	m_kbFastRtAry['G'] = DIK_G;
	m_kbFastRtAry['H'] = DIK_H;
	m_kbFastRtAry['I'] = DIK_I;
	m_kbFastRtAry['J'] = DIK_J;
	m_kbFastRtAry['K'] = DIK_K;
	m_kbFastRtAry['L'] = DIK_L;
	m_kbFastRtAry['M'] = DIK_M;
	m_kbFastRtAry['N'] = DIK_N;
	m_kbFastRtAry['O'] = DIK_O;
	m_kbFastRtAry['P'] = DIK_P;
	m_kbFastRtAry['Q'] = DIK_Q;
	m_kbFastRtAry['R'] = DIK_R;
	m_kbFastRtAry['S'] = DIK_S;
	m_kbFastRtAry['T'] = DIK_T;
	m_kbFastRtAry['U'] = DIK_U;
	m_kbFastRtAry['V'] = DIK_V;
	m_kbFastRtAry['W'] = DIK_W;
	m_kbFastRtAry['X'] = DIK_X;
	m_kbFastRtAry['Y'] = DIK_Y;
	m_kbFastRtAry['Z'] = DIK_Z;

	//	�L���n  2007/01/02
	m_kbFastRtAry['-'] = DIK_MINUS;
	m_kbFastRtAry[','] = DIK_COMMA;
	m_kbFastRtAry['.'] = DIK_PERIOD;
	m_kbFastRtAry['/'] = DIK_SLASH;
	m_kbFastRtAry[';'] = DIK_SEMICOLON;
	m_kbFastRtAry[':'] = DIK_COLON;
	m_kbFastRtAry['@'] = DIK_AT;
	m_kbFastRtAry['['] = DIK_LBRACKET;
	m_kbFastRtAry[']'] = DIK_RBRACKET;
	m_kbFastRtAry['\\'] = DIK_YEN;
	m_kbFastRtAry['^'] = DIK_CIRCUMFLEX;
	//m_kbFastRtAry['?'] = DIK_SLASH;	//	�_�~�[

	m_kbFastRtAry['a'] = DIK_A;
	m_kbFastRtAry['b'] = DIK_B;
	m_kbFastRtAry['c'] = DIK_C;
	m_kbFastRtAry['d'] = DIK_D;
	m_kbFastRtAry['e'] = DIK_E;
	m_kbFastRtAry['f'] = DIK_F;
	m_kbFastRtAry['g'] = DIK_G;
	m_kbFastRtAry['h'] = DIK_H;
	m_kbFastRtAry['i'] = DIK_I;
	m_kbFastRtAry['j'] = DIK_J;
	m_kbFastRtAry['k'] = DIK_K;
	m_kbFastRtAry['l'] = DIK_L;
	m_kbFastRtAry['m'] = DIK_M;
	m_kbFastRtAry['n'] = DIK_N;
	m_kbFastRtAry['o'] = DIK_O;
	m_kbFastRtAry['p'] = DIK_P;
	m_kbFastRtAry['q'] = DIK_Q;
	m_kbFastRtAry['r'] = DIK_R;
	m_kbFastRtAry['s'] = DIK_S;
	m_kbFastRtAry['t'] = DIK_T;
	m_kbFastRtAry['u'] = DIK_U;
	m_kbFastRtAry['v'] = DIK_V;
	m_kbFastRtAry['w'] = DIK_W;
	m_kbFastRtAry['x'] = DIK_X;
	m_kbFastRtAry['y'] = DIK_Y;
	m_kbFastRtAry['z'] = DIK_Z;

	//	�������͂ǂ�����E�E�E�H
	/*
	if ( m_bCaptialReverse )
	{
		m_kbFastRtAry['a'] = DIK_A;
		m_kbFastRtAry['b'] = DIK_B;
		m_kbFastRtAry['c'] = DIK_C;
		m_kbFastRtAry['d'] = DIK_D;
		m_kbFastRtAry['e'] = DIK_E;
		m_kbFastRtAry['f'] = DIK_F;
		m_kbFastRtAry['g'] = DIK_G;
			:
			:
	*/

	//	GetOnKeyList �p�̒ǉ����X�g 2007/01/01
	m_kbFastRtAry[ASCII_BS] =	DIK_BACKSPACE;
	//m_kbFastRtAry[ASCII_TAB] =DIK_TAB;
	m_kbFastRtAry['\t'] =		DIK_TAB;
	m_kbFastRtAry[ASCII_ENTER] =DIK_RETURN;
	m_kbFastRtAry[ASCII_ESC] =	DIK_ESCAPE;
	//m_kbFastRtAry[ASCII_SP] =	DIK_SPACE;
	m_kbFastRtAry[' '] =		DIK_SPACE;
	m_kbFastRtAry[ASCII_DELETE]=DIK_DELETE;

	m_kbFastRtAryInited = true;
}

//	������Ă���L�[�̃��X�g���擾�iDIK�Łj
//	keyListOut �̃T�C�Y��Ԃ�
int CMglKeyboardInput::GetPressDikeyList( vector<BYTE> &keyListOut )
{
	//	�ꉞ�N���A
	keyListOut.clear();

	//	�X�V
	UpdateStateBuf();

	//	m_stateBuf �����[�v
	for( int i=0; i<STATEBUF_SIZE; i++ )
	{
		//	������Ă�H
		if ( IsPressKey(i) )	//	m_stateBuf�Ƃ̔�r
			keyListOut.push_back(i);	//	DIK�萔��ǉ�����
	}

	//	�T�C�Y��Ԃ�
	return keyListOut.size();
}

//	������Ă���L�[�̃��X�g���擾�iASCII�Łj
//	keyListOut �̃T�C�Y��Ԃ�
int CMglKeyboardInput::GetPressKeyList( vector<char> &keyListOut )
{
	//	�ꉞ�N���A
	keyListOut.clear();

	//	�X�V
	UpdateStateBuf();

	//	m_kbFastRtAry �����[�v
	for( int i=0; i<FAST_RT_ARY_SIZE; i++ )
	{
		//	�ݒ肳��Ă��Ȃ����̂̓X�L�b�v
		if ( m_kbFastRtAry[i] == DIK_NULL )
			continue;

		//	������Ă�H
		if ( IsPressKey( m_kbFastRtAry[i] ) )
			keyListOut.push_back(i);	//	ASCII�R�[�h��ǉ�����
	}

	//	�T�C�Y��Ԃ�
	return keyListOut.size();
}

//	�����ꂽ�u�Ԃ��擾�iDIK�j
/*int CMglKeyboardInput::GetOnDikey( BYTE bDik )
{
	//	Update���Ă͂��߁I

	//	������Ă�H
	if ( IsPressKey(bDik) )
	{
		//	�O�񂪉�����Ă��Ȃ������ꍇ�̂�
		if ( PRESSKEY(m_prevStateBuf[bDik]) == 0 )
			return bDik;
	}
	return DIK_ERR;
}*/

//	�����ꂽ�u�Ԃ��擾�iDIK�j
int CMglKeyboardInput::GetOnDikey()
{
	//	Update���Ă͂��߁I

	//	m_stateBuf �����[�v
	for( int i=0; i<STATEBUF_SIZE; i++ )
	{
		//	������Ă�H
		if ( GetOnDikey(i) != DIK_ERR )
			return i;
	}
	return DIK_ERR;
}


//	�����ꂽ�u�Ԃ��擾�iASCII�j
int CMglKeyboardInput::GetOnKey( char cAsciiKeyCode )
{
	/*
	//	?�̏���
	if ( cAsciiKeyCode == '?' )
	{
		if ( GetOnDikey(DIK_SLASH) &&
			(IsPressDikey(DIK_LSHIFT) ||
			 IsPressDikey(DIK_RSHIFT)) )
		{
			return cAsciiKeyCode;
		}
	}
	//	����ȊO
	else
	{
	*/
	//	������Ă�H
	if ( GetOnDikey( m_kbFastRtAry[cAsciiKeyCode] ) != DIK_ERR )
		return cAsciiKeyCode;
	return ASCII_NULL;
}

//	�����ꂽ�u�Ԃ��擾�iASCII�j
int CMglKeyboardInput::GetOnKey()
{
	//	m_kbFastRtAry �����[�v
	for( int i=0; i<FAST_RT_ARY_SIZE; i++ )
	{
		//	�ݒ肳��Ă��Ȃ����̂̓X�L�b�v
		if ( m_kbFastRtAry[i] == DIK_NULL )
			continue;

		//	������Ă�H
		if ( GetOnKey(i) != ASCII_NULL )
			return i;
	}
	return ASCII_NULL;
}
