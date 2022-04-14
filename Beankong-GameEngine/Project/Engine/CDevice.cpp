#include "pch.h"
#include "CDevice.h"

int CDevice::init(HWND _hWnd, Vec2 _vRenderResolution)
{
	_hWnd = _hWnd;
	m_vRenderResolution = _vRenderResolution;

	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL iFeautureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, 0
		, iFlag, nullptr, 0, D3D11_SDK_VERSION
		, m_pDevice.GetAddressOf(), &iFeautureLevel, m_pDeviceContext.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"장치 초기화 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	UINT iQuality = 0;
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &iQuality);

	if (0 == iQuality)
	{
		MessageBox(nullptr, L"멀티셈플 레벨체크 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// SwapChain 생성
	if (FAILED(CreateSwapchain()))
	{
		MessageBox(nullptr, L"스왑체인 생성 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// View
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"뷰 생성 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// RenderTargetView, DepthStencilView 전달
	// Render 시 출력 버퍼 및 깊이버퍼 지정
	m_pDeviceContext->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());


	// ViewPort
	// 윈도우에 출력 될 프론트 버퍼의 위치 설정
	m_tViewPort.TopLeftX = 0;
	m_tViewPort.TopLeftY = 0;

	m_tViewPort.Width = m_vRenderResolution.x;
	m_tViewPort.Height = m_vRenderResolution.y;

	m_tViewPort.MinDepth = 0;
	m_tViewPort.MaxDepth = 1;

	m_pDeviceContext->RSSetViewports(1, &m_tViewPort);


	// 래스터라이저 스테이트 생성
	if (FAILED(CreateRasterizerState()))
	{
		return E_FAIL;
	}

	// 뎊스스텐실 스테이트 생성
	if (FAILED(CreateDepthStencilState()))
	{
		return E_FAIL;
	}

	// 상수버퍼 생성
	if (FAILED(CreateConstBuffer()))
	{
		return E_FAIL;
	}

	// Sampler 생성
	CreateSamplerState();

	return S_OK;
}


void CDevice::ClearTarget()
{
}

int CDevice::CreateSwapchain()
{
	return 0;
}

int CDevice::CreateView()
{
	return 0;
}

int CDevice::CreateRasterizerState()
{
	return 0;
}

int CDevice::CreateDepthStencilState()
{
	return 0;
}

int CDevice::CreateConstBuffer()
{
	return 0;
}

void CDevice::CreateSamplerState()
{
}

CDevice::CDevice()
{}

CDevice::~CDevice()
{}