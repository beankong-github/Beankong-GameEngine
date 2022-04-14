#include "pch.h"
#include "CCore.h"

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	// 윈도우 크기 설정
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// Manager 초기화
	if (FAILED(CDevice::GetInst()->init(m_hWnd, Vec2((float)m_ptResolution.x, (float)m_ptResolution.y))))
	{
		return E_FAIL;
	}


	return 0;
}

void CCore::progress()
{
}

CCore::CCore()
{}

CCore::~CCore()
{}