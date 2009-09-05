#ifndef __MyuReleaseBase_H__
#define __MyuReleaseBase_H__

//	クラス宣言
class IMyuReleasable // 特に現状エクスポートするものは無いんだが、将来的な事を見越してDLL_EXPつけとく
{
private:

public:
	virtual void Release()=0;
};

//	クラス宣言
class CMyuReleaseBase : public IMyuReleasable
{
private:

public:
	//virtual ~CMyuReleaseBase(){ Release(); }
};

typedef CMyuReleaseBase CMglReleaseBase;


/////////////////////////////////////////////////////////////////////////////////
/*
//	クラス宣言
class DLL_EXP IMyuReleasable2 // 特に現状エクスポートするものは無いんだが、将来的な事を見越してDLL_EXPつけとく
{
private:

public:
	virtual void Release()=0;
};

//	クラス宣言
class CMyuReleaseBase2 : public IMyuReleasable2
{
private:

public:
	virtual ~CMyuReleaseBase2(){ Release(); }
};
*/

//typedef CMyuReleaseBase CMyuReleasable, CMyuReleaseable, CMglReleasable, CMglReleaseable;
//typedef IMyuReleaseBase IMyuReleasable, IMyuReleaseable, IMglReleasable, IMglReleaseable;

#endif//__MyuReleaseBase_H__
