//////////////////////////////////////////////////////////
//
//	mglmsg - メッセージ番号の定義
//
//////////////////////////////////////////////////////////

#ifndef __mglmsg_H__
#define __mglmsg_H__

#define MGLMSGNO_GRP(NO)		(NO+0x12000000)
#define MGLMSGNO_SOUND(NO)		(NO+0x14000000)
#define MGLMSGNO_INPUT(NO)		(NO+0x15000000)

//////////////////////////////////////////////////////////////////

#define MSGMSLNO_GLOBAL			(MGLMSGNO_GRP(0x010000))
#define MSGMSLNO_GRP_MANAGER	(MGLMSGNO_GRP(0x100000))
#define MSGMSLNO_DRAW_LINE		(MGLMSGNO_GRP(0x790000))
#define MSGMSLNO_BITMAP_DATA	(MGLMSGNO_GRP(0x800000))

//////////////////////////////////////////////////////////////////

#define MSGMSLNO_GLOBAL_HWND_DEFAULT			(MSGMSLNO_GLOBAL+1)

#define MSGMSLNO_GRP_MANAGER_MULTI_INSTANCE		(MSGMSLNO_GRP_MANAGER+6)
#define MSGMSLNO_GRP_MANAGER_D3DCREATE_FAILED	(MSGMSLNO_GRP_MANAGER+7)

#define MSGMSLNO_DRAW_LINE_DRAW_FAILED			(MSGMSLNO_DRAW_LINE+1)

#define MSGMSLNO_BITMAP_DATA_INVALID_POS		(MSGMSLNO_BITMAP_DATA+3)

#endif//__mglmsg_H__