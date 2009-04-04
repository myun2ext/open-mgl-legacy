//////////////////////////////////////////////////////////
//
//	MglAugustFactory
//
//////////////////////////////////////////////////////////

#ifndef __MglAugustFactory_H__
#define __MglAugustFactory_H__

#include "agh.h"

//	auto_ptr辺りを使って管理しましょう

//	クラス宣言  /////////////////////////////////////////////////////////

//	いや、これやっぱ駄目だわ・・・（継承出来ないんでNG）
class DLL_EXP CMglAugustFactory
{
public:
	static agh::CImageBase* GetImage();
};

/////////////////////////////////////////////

/*		// TEMPLATE CLASS auto_ptr
template<class _Ty>
	class auto_ptr {
public:
	typedef _Ty element_type;
	explicit auto_ptr(_Ty *_P = 0) _THROW0()
		: _Owns(_P != 0), _Ptr(_P) {}
	auto_ptr(const auto_ptr<_Ty>& _Y) _THROW0()
		: _Owns(_Y._Owns), _Ptr(_Y.release()) {}
	auto_ptr<_Ty>& operator=(const auto_ptr<_Ty>& _Y) _THROW0()
		{if (this != &_Y)
			{if (_Ptr != _Y.get())
				{if (_Owns)
					delete _Ptr;
				_Owns = _Y._Owns; }
			else if (_Y._Owns)
				_Owns = true;
			_Ptr = _Y.release(); }
		return (*this); }
	~auto_ptr()
		{if (_Owns)
			delete _Ptr; }
	_Ty& operator*() const _THROW0()
		{return (*get()); }
	_Ty *operator->() const _THROW0()
		{return (get()); }
	_Ty *get() const _THROW0()
		{return (_Ptr); }
	_Ty *release() const _THROW0()
		{((auto_ptr<_Ty> *)this)->_Owns = false;
		return (_Ptr); }
private:
	bool _Owns;
	_Ty *_Ptr;
	};
*/
/*
template <typename T> class august_auto_ptr
{
private:
	typedef T* _P;
	operator T (){return *this;}	//	コピー出来ないように
protected:
	_P m_p;
public:
	august_auto_ptr(){ m_p = NULL; }
	explicit august_auto_ptr(T* p){ m_p = p; }

	void set(T* p){ m_p = p; }
	operator T* (){ return m_p; }
	T* get(){ return m_p; }
};
*/


#endif//__MglAugustFactory_H__
