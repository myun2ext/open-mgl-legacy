#ifndef __MglException_H__
#define __MglException_H__

/*#include "MglCommonException.h"

//	�N���X�錾
class CMglException : public MglCommonException
{
public:

private:

};*/


/*#define MGL_H_ASSERT(CALL)	\
	MyuAssert( CALL, S_OK,	\
		"%s", typeid (*this).name());*/

#define MGL_H_ASSERT(CALL)	\
	MglAssert2( __FILE__, __LINE__, CALL, S_OK,	\
		"%s �Ɏ��s�B", # CALL );

#define MGL_H_ASSERT2(CALL,FROM)	\
	MglAssert2( CALL, S_OK,	\
		"%s  %s �Ɏ��s�B"	\
		"\r\n%s:%d", FROM, # CALL, __FILE__, __LINE__);

/*
#define MGL_H_ASSERT(CALL)	\
	MyuAssert( CALL, S_OK,	\
		"%s �Ɏ��s�B"	\
		"\r\n%s:%d", # CALL, __FILE__, __LINE__);

#define MGL_H_ASSERT2(CALL,FROM)	\
	MyuAssert( CALL, S_OK,	\
		"%s  %s �Ɏ��s�B"	\
		"\r\n%s:%d", FROM, # CALL, __FILE__, __LINE__);
*/

#endif//__MglException_H__
