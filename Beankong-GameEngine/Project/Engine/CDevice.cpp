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
		MessageBox(nullptr, L"��ġ �ʱ�ȭ ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	UINT iQuality = 0;
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &iQuality);

	if (0 == iQuality)
	{
		MessageBox(nullptr, L"��Ƽ���� ����üũ ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// SwapChain ����
	if (FAILED(CreateSwapchain()))
	{
		MessageBox(nullptr, L"����ü�� ���� ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// View
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"�� ���� ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// RenderTargetView, DepthStencilView ����
	// Render �� ��� ���� �� ���̹��� ����
	m_pDeviceContext->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());


	// ViewPort
	// �����쿡 ��� �� ����Ʈ ������ ��ġ ����
	m_tViewPort.TopLeftX = 0;
	m_tViewPort.TopLeftY = 0;

	m_tViewPort.Width = m_vRenderResolution.x;
	m_tViewPort.Height = m_vRenderResolution.y;

	m_tViewPort.MinDepth = 0;
	m_tViewPort.MaxDepth = 1;

	m_pDeviceContext->RSSetViewports(1, &m_tViewPort);


	// �����Ͷ����� ������Ʈ ����
	if (FAILED(CreateRasterizerState()))
	{
		return E_FAIL;
	}

	// �X�����ٽ� ������Ʈ ����
	if (FAILED(CreateDepthStencilState()))
	{
		return E_FAIL;
	}

	// ������� ����
	if (FAILED(CreateConstBuffer()))
	{
		return E_FAIL;
	}

	// Sampler ����
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