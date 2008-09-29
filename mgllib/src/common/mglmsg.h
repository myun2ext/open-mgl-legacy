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

//	グラフィック
#define MGLMSGNO_GRP_MANAGER	(MGLMSGNO_GRP(0x100000))
#define MGLMSGNO_DRAW_LINE		(MGLMSGNO_GRP(0x790000))
#define MGLMSGNO_BITMAP_DATA	(MGLMSGNO_GRP(0x800000))

//////////////////////////////////////////////////////////////////

//	入力
#define MGLMSGNO_INPUT_MOUSE(NO)	((NO)+MGLMSGNO_INPUT(0x400000))

//////////////////////////////////////////////////////////////////

//	その他
#define MGLMSGNO_GLOBAL			(MGLMSGNO_GRP(0x010000))

//////////////////////////////////////////////////////////////////

//	ひとつひとつ
#define MGLMSGNO_GLOBAL_HWND_DEFAULT			(MGLMSGNO_GLOBAL+1)

#define MGLMSGNO_GRP_MANAGER_MULTI_INSTANCE		(MGLMSGNO_GRP_MANAGER+6)
#define MGLMSGNO_GRP_MANAGER_D3DCREATE_FAILED	(MGLMSGNO_GRP_MANAGER+7)

#define MGLMSGNO_DRAW_LINE_DRAW_FAILED			(MGLMSGNO_DRAW_LINE+1)

#define MGLMSGNO_BITMAP_DATA_INVALID_POS		(MGLMSGNO_BITMAP_DATA+3)

#endif//__mglmsg_H__