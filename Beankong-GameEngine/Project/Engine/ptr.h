#pragma once

template<typename T>
class Ptr
{
private:
	T* m_pRes;

public:
	T* Get() { return m_pRes; }
	T* Get() const { return m_pRes; }

	T** GetAddressOf() { return &m_pRes; }
	T** GetAddressOf() { return &m_pRes; }

public:

	// 대입 연산자
	Ptr& operator = (T* _ptr)
	{ 
		// m_pRes가 기존에 참조하고 있던 리소스가 있다면 기존의 리소스 카운트를 감소.
		if (nullptr != m_pRes)
			m_pRes->SubRef();

		// 새 리소스 참조
		m_pRes = _ptr;

		// 새 리소스의 리소스 카운트 증가
		if (nullptr != m_pRes)
			m_pRes->AddRef();
	
		return *this;
	}
	Ptr& operator = (const Ptr<T>& _otherPtr)
	{
		// m_pRes가 기존에 참조하고 있던 리소스가 있다면 기존의 리소스 카운트를 감소.
		if (nullptr != m_pRes)
			m_pRes->SubRef();

		// 새 리소스 참조
		m_pRes = _otherPtr.Get();

		// 새 리소스의 리소스 카운트 증가
		if (nullptr != m_pRes)
			m_pRes->AddRef();

		return *this;
	}

	// 포인터 참조 연산자
	T* operator -> ()
	{
		return m_pRes;
	}

	// 비교 연산자
	bool operator == (T* _pRes)
	{
		return (m_pRes == _pRes);
	}
	
	bool operator != (T* _pRes)
	{
		return (m_pRes != _pRes)
	}

	bool operator == (const Ptr<T>& _otherPtr)
	{
		return(m_pRes == _otherPtr.Get());
	}

	bool operator != (const Ptr<T>& _otherPtr)
	{
		return(m_pRes != _otherPtr.Get());
	}
};

template<typename T>
bool operator == (void* _pRes, const Ptr<T>& _ptr)
{
	return (m_pRes == _ptr.Get());
}

template<typename T>
bool operator != (void* _pRes, const Ptr<T>& _ptr)
{
	return (m_pRes != _ptr.Get());
}