//////////////////////////////////////////////////////////
//
//	MglStandardTypes
//
//////////////////////////////////////////////////////////

#ifndef __MglStandardTypes_H__
#define __MglStandardTypes_H__

namespace mgl{

//	”’lƒNƒ‰ƒX
class CInteger
{
protected:
	int m_val;
public:
	CInteger(){m_val=0;}
	CInteger(int v){m_val=v;}
	CInteger(const char* s){m_val=atoi(s);}
	virtual ~CInteger(){}
	
	operator int(){ return m_val; }
	int get(){ return m_val; }

	//operator ++
};

}

#endif//__MglStandardTypes_H__