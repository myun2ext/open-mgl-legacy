#ifndef __MyuReleaseBase_H__
#define __MyuReleaseBase_H__

//	�N���X�錾
class IMyuReleasable // ���Ɍ���G�N�X�|�[�g������͖̂����񂾂��A�����I�Ȏ������z����DLL_EXP���Ƃ�
{
private:

public:
	virtual void Release()=0;
};

//	�N���X�錾
class CMyuReleaseBase : public IMyuReleasable
{
private:

public:
	//virtual ~CMyuReleaseBase(){ Release(); }
};

typedef CMyuReleaseBase CMglReleaseBase;


/////////////////////////////////////////////////////////////////////////////////
/*
//	�N���X�錾
class DLL_EXP IMyuReleasable2 // ���Ɍ���G�N�X�|�[�g������͖̂����񂾂��A�����I�Ȏ������z����DLL_EXP���Ƃ�
{
private:

public:
	virtual void Release()=0;
};

//	�N���X�錾
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
