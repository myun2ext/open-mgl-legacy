#ifndef __MglException_H__
#define __MglException_H__

/*#include "MglCommonException.h"

//	ÉNÉâÉXêÈåæ
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
		"%s Ç…é∏îsÅB", # CALL );

#define MGL_H_ASSERT2(CALL,FROM)	\
	MglAssert2( CALL, S_OK,	\
		"%s  %s Ç…é∏îsÅB"	\
		"\r\n%s:%d", FROM, # CALL, __FILE__, __LINE__);

/*
#define MGL_H_ASSERT(CALL)	\
	MyuAssert( CALL, S_OK,	\
		"%s Ç…é∏îsÅB"	\
		"\r\n%s:%d", # CALL, __FILE__, __LINE__);

#define MGL_H_ASSERT2(CALL,FROM)	\
	MyuAssert( CALL, S_OK,	\
		"%s  %s Ç…é∏îsÅB"	\
		"\r\n%s:%d", FROM, # CALL, __FILE__, __LINE__);
*/

#endif//__MglException_H__
