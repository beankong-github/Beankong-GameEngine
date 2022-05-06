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

	// ���� ������
	Ptr& operator = (T* _ptr)
	{ 
		// m_pRes�� ������ �����ϰ� �ִ� ���ҽ��� �ִٸ� ������ ���ҽ� ī��Ʈ�� ����.
		if (nullptr != m_pRes)
			m_pRes->SubRef();

		// �� ���ҽ� ����
		m_pRes = _ptr;

		// �� ���ҽ��� ���ҽ� ī��Ʈ ����
		if (nullptr != m_pRes)
			m_pRes->AddRef();
	
		return *this;
	}
	Ptr& operator = (const Ptr<T>& _otherPtr)
	{
		// m_pRes�� ������ �����ϰ� �ִ� ���ҽ��� �ִٸ� ������ ���ҽ� ī��Ʈ�� ����.
		if (nullptr != m_pRes)
			m_pRes->SubRef();

		// �� ���ҽ� ����
		m_pRes = _otherPtr.Get();

		// �� ���ҽ��� ���ҽ� ī��Ʈ ����
		if (nullptr != m_pRes)
			m_pRes->AddRef();

		return *this;
	}

	// ������ ���� ������
	T* operator -> ()
	{
		return m_pRes;
	}

	// �� ������
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