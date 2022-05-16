#include "pch.h"
#include "CCore.h"

#include "CDevice.h"
#include "PathMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"


CCore::CCore()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{}

CCore::~CCore()
{}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	// 윈도우 크기 설정
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// Manager 초기화
	if (FAILED(CDevice::GetInst()->Init(m_hWnd, Vec2((float)m_ptResolution.x, (float)m_ptResolution.y))))
	{
		return E_FAIL;
	}

	PathMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	
	ResMgr::GetInst()->Init();
	SceneMgr::GetInst()->Init();


	return S_OK;

}

void CCore::Progress()
{
	/* Manager Update */
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
}