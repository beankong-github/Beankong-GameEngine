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
	Ptr& operator = (T* _ptr)
	{
	}
	
};