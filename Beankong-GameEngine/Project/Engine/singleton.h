#pragma once

template<typename T>
class Singleton
{
	typedef void(*DESTORY)(void);

private:
	static T* m_Inst;

public:
	static T* GetInst()
	{
		if (nullptr == m_Inst)
		{
			m_Inst = new T;
		}

		return m_Inst;
	}

	static void Destroy()
	{
		if (nullptr != m_Inst)
		{
			delete m_Inst;
			m_Inst = nullptr;
		}
	}

public:
	Singleton()
	{
		// atexit: ���α׷��� ����� �� ȣ��� �Լ��� ����Ѵ�.
		atexit((DESTORY)Singleton<T>::Destroy);
	}

	virtual ~Singleton()
	{

	}
};

// instance �ʱ�ȭ
template<typename T>
T* Singleton<T>::m_Inst = nullptr;