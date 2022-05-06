#include "pch.h"
#include "CCore.h"

#include "CDevice.h"
#include "PathMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResMgr.h"


CCore::CCore()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{}

CCore::~CCore()
{}

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

	PathMgr::GetInst()->init();
	TimeMgr::GetInst()->init();
	KeyMgr::GetInst()->init();
	//CResMgr::GetInst()->init();
	//CSceneMgr::GetInst()->init();


	return S_OK;

}

void CCore::progress()
{
	/* Manager Update */
	TimeMgr::GetInst()->update();
	KeyMgr::GetInst()->update();
}