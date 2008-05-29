#ifndef __MglClassMsg_H__
#define __MglClassMsg_H__

#define MGL_CLASS_MSG_CODE_FALSE	(0)

class DLL_EXP CMglClassMsg
{
public:
	virtual int SendMessage(int nMsgCode, string strMsgParams=""){
		return MGL_CLASS_MSG_CODE_FALSE;
	}
};

#endif//__MglClassMsg_H__