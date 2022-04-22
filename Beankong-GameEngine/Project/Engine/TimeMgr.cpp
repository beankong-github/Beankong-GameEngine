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
	// 초당 카운팅 횟수
	QueryPerformanceFrequency(&m_liFrequency);

	// 카운트를 받아 놓는다
	QueryPerformanceCounter(&m_liPrevCount);
}

void TimeMgr::update()
{
	/* DT 구하기 */
	// 현재 카운트 값
	QueryPerformanceCounter(&m_liCurCount);

	// 이전 카운팅과 현재 카운팅 값의 차이를 초당 카운팅 수로 나눠 1프레임이 샐행되는 동안 걸린 시간(DeltaTime)을 구한다
	m_fDT = (float)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (float)m_liFrequency.QuadPart;

#ifdef _DEBUG
	// 디버그 모드에서는 강제로 최소 60FPS를 확보해둔다.
	if (m_fDT > (1.f / 60.f))
	{
		m_fDT = 1.f / 60.f;
	}
#endif // _DEBUG
	
	// 현재 카운팅 값을 이전 카운팅 값으로 저장
	m_liPrevCount.QuadPart = m_liCurCount.QuadPart;


	/* FPS 구하기 */
	// Frame 카운팅
	++m_iFPS;

	// 시간 누적
	m_fAddTime += m_fDT;

	if (m_fAddTime >= 1.f)
	{
		// AddTime 재설정
		m_fAddTime -= 1.f;

		// window bar에 현재 프레임 기록하기
		wchar_t szStr[256] = L"";
		wsprintf(szStr, L"FPS: %d", m_iFPS);
		SetWindowTextW(CCore::GetInst()->GetMainHwnd(), szStr);

		// FPS 초기화
		m_iFPS = 0;
	}
	
	/* 현재 시간 구하기 */
	m_fCurTime += m_fDT;
}