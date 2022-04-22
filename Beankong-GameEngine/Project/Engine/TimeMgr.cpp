#include "pch.h"
#include "TimeMgr.h"

#include "CCore.h"

TimeMgr::TimeMgr()
	: m_liCurCount()
	, m_liFrequency()
	, m_liPrevCount()
	, m_iFPS(0)
	, m_fDT(0.f)
	, m_fAddTime(0.f)
	, m_fCurTime(0.f)
{}

TimeMgr::~TimeMgr()
{}

void TimeMgr::init()
{
	// �ʴ� ī���� Ƚ��
	QueryPerformanceFrequency(&m_liFrequency);

	// ī��Ʈ�� �޾� ���´�
	QueryPerformanceCounter(&m_liPrevCount);
}

void TimeMgr::update()
{
	/* DT ���ϱ� */
	// ���� ī��Ʈ ��
	QueryPerformanceCounter(&m_liCurCount);

	// ���� ī���ð� ���� ī���� ���� ���̸� �ʴ� ī���� ���� ���� 1�������� ����Ǵ� ���� �ɸ� �ð�(DeltaTime)�� ���Ѵ�
	m_fDT = (float)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (float)m_liFrequency.QuadPart;

#ifdef _DEBUG
	// ����� ��忡���� ������ �ּ� 60FPS�� Ȯ���صд�.
	if (m_fDT > (1.f / 60.f))
	{
		m_fDT = 1.f / 60.f;
	}
#endif // _DEBUG
	
	// ���� ī���� ���� ���� ī���� ������ ����
	m_liPrevCount.QuadPart = m_liCurCount.QuadPart;


	/* FPS ���ϱ� */
	// Frame ī����
	++m_iFPS;

	// �ð� ����
	m_fAddTime += m_fDT;

	if (m_fAddTime >= 1.f)
	{
		// AddTime �缳��
		m_fAddTime -= 1.f;

		// window bar�� ���� ������ ����ϱ�
		wchar_t szStr[256] = L"";
		wsprintf(szStr, L"FPS: %d", m_iFPS);
		SetWindowTextW(CCore::GetInst()->GetMainHwnd(), szStr);

		// FPS �ʱ�ȭ
		m_iFPS = 0;
	}
	
	/* ���� �ð� ���ϱ� */
	m_fCurTime += m_fDT;
}