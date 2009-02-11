//////////////////////////////////////////////////////////
//
//	mglmsg - メッセージ番号の定義
//
//////////////////////////////////////////////////////////

#ifndef __mglmsg_H__
#define __mglmsg_H__

#define MGLMSGNO_COMMON(NO)		(NO+0x10000000)
#define MGLMSGNO_SYSTEM(NO)		(NO+0x11000000)
#define MGLMSGNO_GRP(NO)		(NO+0x12000000)
#define MGLMSGNO_3D(NO)			(NO+0x14000000)
#define MGLMSGNO_SOUND(NO)		(NO+0x20000000)
#define MGLMSGNO_INPUT(NO)		(NO+0x21000000)
#define MGLMSGNO_WINDOW(NO)		(NO+0x30000000)

//////////////////////////////////////////////////////////////////

//	グラフィック
#define MGLMSGNO_GRP_MANAGER	(MGLMSGNO_GRP(0x100000))
#define MGLMSGNO_DRAW_LINE		(MGLMSGNO_GRP(0x790000))
#define MGLMSGNO_BITMAP_DATA	(MGLMSGNO_GRP(0x800000))

//	3Dグラフィックス
#define MGLMSGNO_LIGHT(NO)		(MGLMSGNO_3D(0x240000)+NO)

#define MGLMSGNO_3DSQUARE(NO)	(MGLMSGNO_3D(0x660000)+NO)

#define MGLMSGNO_MESH(NO)		(MGLMSGNO_3D(0x810000)+NO)

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