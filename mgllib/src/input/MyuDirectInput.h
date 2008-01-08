//////////////////////////////////////////////////////////
//
//	MyuDirectInput
//		- DirectInput�N���X
//
//////////////////////////////////////////////////////////

#ifndef __MyuDirectInput_H__
#define __MyuDirectInput_H__

#include "MyuKeyboardInput.h"
#include "MyuTimer.h"

#define RELATE_NAME_MAX	(64)	//	�֘A�t�����T�C�Y
#define RELATE_MAX		(256)	//	�ő�֘A�t���\���̐�

//	�֘A�t���\���̕��N���X
//	�i�\���̂��ƃN���X�����ĂȂ��̂Łc�j
//typedef struct
class DLL_EXP INPUT_RELATE
{
public:
	char szInputName[RELATE_NAME_MAX];
	BYTE keyCode;
	/* �W���C�p�b�h�� */

	BOOL oldKeyPush;
	BOOL keyPool;
	CMyuTimer timer;
};

//	�֘A�t���\����
/*typedef struct
{
	char szInputName[RELATE_NAME_MAX];
	BYTE keyCode;
	/* �W���C�p�b�h�� *

	BOOL oldKeyPush;
	BOOL keyPool;

} INPUT_RELATE;
*/

////////////////////////////////////////////
//
//		�N���X�錾
//
class DLL_EXP CMyuDirectInput : public CMyuKeyboardInput
{
protected:
	INPUT_RELATE relate[RELATE_MAX];
	int nRelateCnt;
	BOOL m_autoGetBuf;

	//	�������\�b�h
	INPUT_RELATE* GetRelate( const char *szInputName );

public:
	CMyuDirectInput();
	virtual ~CMyuDirectInput();

	void Init( HWND hWnd, BOOL in_autoGetBuf=FALSE );
	void ClearList();

	void RelateKey( const char *szInputName, BYTE keyCode );
	BOOL IsDownKey( const char *szInputName );
	//BOOL IsUpKey( const char *szInputName );
	BOOL IsPushKey( const char *szInputName );
	void GetBuf();
};


#endif//__MyuDirectInput_H__