#include "pch.h"
#include "CDevice.h"



CDevice::CDevice()
	: m_hWnd(nullptr)
	, m_tSwapChainDesc{}
	, m_tViewPort{}
	, m_arrRS{}
	, m_arrCB{}
{}

CDevice::~CDevice()
{}

int CDevice::init(HWND _hWnd, Vec2 _vRenderResolution)
{
	// ������ �ڵ�, ȭ�� �ػ󵵸� �޾� ����� ����
	m_hWnd = _hWnd;
	m_vRenderResolution = _vRenderResolution;

	// Device, Device Context ����
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
	
	// ��Ƽ ���� ���� üũ
	// -> FEATURE_LEVEL_11 ��ġ�� ��� ���� ��� ���Ŀ� ���� 4x MSAA�� �����ϴ��� üũ ( ���� ���� ��ġ�� DirectX11�� ������ �� �ִ��� üũ)
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

	// View ����
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"�� ���� ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// RenderTargetView, DepthStencilView ����
	// Render�� ��¹��� �� ���̹��� �����ϱ� ����
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

	// �������ٽ� ������Ʈ ����
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
	// Target VieW �����
	m_pDeviceContext->ClearRenderTargetView(m_RTV.Get(), Vec4(1.f, 1.f, 1.f, 1.f));	// RT�� Clear�ϸ鼭 ä������ ��(����) ����
	m_pDeviceContext->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.f, 0);
}

int CDevice::CreateSwapchain()
{
	// SwapChain Description ä���
	DXGI_SWAP_CHAIN_DESC desc = {};

	desc.BufferCount = 1;																			// Front ���۸� �⺻���� ������ �־� ���� ī��Ʈ�� 1�� �Ѵ�.
	desc.BufferDesc.Width = (UINT)m_vRenderResolution.x;											// ������ ũ��� ������ �ػ󵵿� ���ƾ��Ѵ�.
	desc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;											// �ȼ� ����(�ȼ� ����): 32bit�� RGBA �ȼ�
	desc.BufferDesc.RefreshRate.Denominator = 1;													// RefreshRate: �ʴ� ȭ�� ���� Ƚ��
	desc.BufferDesc.RefreshRate.Numerator = 60;														// ��Denominator(�и�): 1, Numerator(����):60 => �ʴ� 60ȸ 
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;							// 
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// �ȼ��� �������ϴ� ���� ( ex: ��->��, ��->�� )

	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			// ���� ��� �뵵: ���� Ÿ��
	desc.Flags = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;					// �� ���� ���� �� FB�� ������ �ִ� ������ ��� �� �� ����. Discard => ����

	desc.SampleDesc.Count = 1;									// �ȼ� �� ��Ƽ ���� �� ( ��Ƽ ���ø� ) : 1�� ��� ��Ƽ ���ø� off
	desc.SampleDesc.Quality = 0;								// �̹��� ǰ�� ���� ( ������ ���� ���� ���� ����) 
																// ��Ƽ�ٸ������ ���� �⺻ ���÷� ����� Count�� 1�̰� Quality�� 0

	desc.OutputWindow = m_hWnd;									// ���۰� ���� ������ ����� ��� ������ �ڵ�
	desc.Windowed = true;										// â��� : true

	// ����ü�� �����ϱ�
	ComPtr<IDXGIDevice> pDXGIDevice = nullptr;		// IDXGIDevice �������̽��� �̹��� �����͸� �����ϴ� DXGI ��ü�� ���� �Ļ� Ŭ������ ����	
	ComPtr<IDXGIAdapter> pDXGIAdaptor = nullptr;	// IDXGIAdapter �������̽��� ���÷��� ���� �ý���(�ϳ� �̻��� GPU, DAC �� ���� �޸� ��)�� ����
	ComPtr<IDXGIFactory> pDXGIFactory = nullptr;	// IDXGIFactory �������̽��� ��ü ȭ�� ��ȯ�� ó���ϴ� DXGI ��ü�� �����ϴ� �޼��带 ����

	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());	// Device���� DXGIDevice�� ���´�.
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdaptor.GetAddressOf());	// DXGIDevice�� �θ� DXGIAdapter�� ���´�.
	pDXGIAdaptor->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf());	// DXGIAdapter�� �θ� DXGIFactory�� ���´�

	pDXGIFactory->CreateSwapChain(m_pDevice.Get(), &desc, m_pSwapChain.GetAddressOf());		// DXGIFactory�� ���� ���� ü���� �����Ѵ�.

	if (nullptr == m_pSwapChain)
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateView()
{
	// ===========
	//	 RTV ����
	// =========== 
	// Render Target View : ���� Ÿ���� GPU�� �����ϴ� ����
	// 1. ����ü�ο��� Render Target(����)�� ������
	ComPtr<ID3D11Texture2D> pBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBuffer.GetAddressOf());
	// 2. ������ ���۸� ����� RTV ���� 
	m_pDevice->CreateRenderTargetView(pBuffer.Get(), nullptr, m_RTV.GetAddressOf());

	if (nullptr == m_RTV)
		return E_FAIL;

	// ===========
	//	 DSV ����
	// =========== 
	// Depth Stencil View : Depth Stencil�� GPU�� �����ϴ� ����
	// 1. Depth Stencil Target(����)���� ����� �ؽ�ó�� ����
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width = (UINT)m_vRenderResolution.x;						// ���� ũ��� �����ϰ� �ؽ�ó ����
	desc.Height = (UINT)m_vRenderResolution.y;
	desc.MipLevels = 0;												// ������ �ִ� �θ�
	desc.ArraySize = 1;												// �ؽ�ó �迭 ũ��

	desc.CPUAccessFlags = 0;										// CPU Access ��� ����(D3D11_CPU_ACCESS_FLAG)�� ���ϴ� �÷���. CPU ������ �ʿ� ���� ��� 0
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;		// ���������� �ܰ迡 ���ε��ϱ� ���� �ؽ�ó ��� �뵵�� �����ϴ� �÷���
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;					// �ؽ�ó�� �а� ���� ����� �ĺ��ϱ� ���� ��
	desc.MiscFlags = 0;												// �Ϲ������� ���� �ٸ� ���ҽ� �ɼ��� �ĺ��ϴ� �÷���

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;					// Texture format, 24bit�� ���� ����, 8bit�� ���ٽ� ������ �����ϴ� 32bit z-buffer Ÿ�� �ؽ�ó�̴�.

	m_pDevice->CreateTexture2D(&desc, nullptr, m_pDepthStencilTarget.GetAddressOf());	// �ؽ�ó ����

	if (nullptr == m_pDepthStencilTarget)
		return E_FAIL;

	// 2. ������  Depth Stencil Target �̿��� DSV ����
	m_pDevice->CreateDepthStencilView(m_pDepthStencilTarget.Get(), nullptr, m_DSV.GetAddressOf());

	if (nullptr == m_DSV)
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	HRESULT hr = S_OK;

	// 1. CULL_BACK (Defuatl)
	// �ݽð�(�޸�) ����, �ð����(�ո�) ���
	m_arrRS[(UINT)RS_TYPE::CULL_BACK] = nullptr;


	// 2. CULL_FRONT
	// �ݽð�(�޸�) ���, �ð����(�ո�) ����
	desc.CullMode = D3D11_CULL_FRONT;
	desc.FillMode = D3D11_FILL_SOLID;
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());
	if (FAILED(hr))
		return E_FAIL;

	// 3. CULL_NONE
	// ��� ��� �׸���, (�ַ� �ܸ� ������ �޽��� �� �ڿ��� �� �� ���)
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());
	if (FAILED(hr))
		return E_FAIL;

	// 4. WIRE_FRAME
	// ��� ��� �׸���, ���� �ȼ��� ������
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_WIREFRAME;
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());
	if (FAILED(hr))
		return E_FAIL;


	return S_OK;
}

int CDevice::CreateDepthStencilState()
{// ���ٽ� �ɼ��� ���� ������� ����
	/*
	desc.StencilEnable = false;
	desc.BackFace;
	desc.FrontFace;
	desc.StencilReadMask;
	desc.StencilWriteMask;
	*/


	// 1. Less (Default)
	// ���� ���� �� ���� (�� �տ� �ִ�) ��ü �켱 ���
	m_arrDS[(UINT)DS_TYPE::LESS] = nullptr;


	// 2. LessEqual
	D3D11_DEPTH_STENCIL_DESC desc = {};

	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf())))
		return E_FAIL;


	// 3. Greater
	// ���� ���� �� ū (�� �տ� �ִ�) ��ü �켱 ���
	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_GREATER;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::GREATER].GetAddressOf())))
		return E_FAIL;

	// 4. GreaterEqual
	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::GREATER_EQUAL].GetAddressOf())))
		return E_FAIL;


	// 5. No Test
	// ���� �� �׽�Ʈ x, ���� ��� o ( �ٸ� ��ü���� No Test�� ��ü�� ���� ���� ������ ���� )
	desc.DepthEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::NO_TEST].GetAddressOf())))
		return E_FAIL;


	// 6. No Write
	// ���� �� �׽�Ʈ o, ���� ��� x ( �ٸ� ��ü���� ���� ���� ������ ������ ������ ���� ���� )
	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::NO_WRITE].GetAddressOf())))
		return E_FAIL;


	// 7. No Test No Write
	// ���� �� �׽�Ʈ x, ���� ��� x
	desc.DepthEnable = false;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf())))
		return E_FAIL;

	return S_OK;
}


int CDevice::CreateConstBuffer()
{
	return 0;
}

void CDevice::CreateSamplerState()
{
	D3D11_SAMPLER_DESC tDesc = {};

	tDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;

	DEVICE->CreateSamplerState(&tDesc, m_arrSam[0].GetAddressOf());


	tDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;

	DEVICE->CreateSamplerState(&tDesc, m_arrSam[1].GetAddressOf());

	CONTEXT->VSSetSamplers(0, 1, m_arrSam[0].GetAddressOf());
	CONTEXT->HSSetSamplers(0, 1, m_arrSam[0].GetAddressOf());
	CONTEXT->DSSetSamplers(0, 1, m_arrSam[0].GetAddressOf());
	CONTEXT->GSSetSamplers(0, 1, m_arrSam[0].GetAddressOf());
	CONTEXT->PSSetSamplers(0, 1, m_arrSam[0].GetAddressOf());

	CONTEXT->VSSetSamplers(1, 1, m_arrSam[1].GetAddressOf());
	CONTEXT->HSSetSamplers(1, 1, m_arrSam[1].GetAddressOf());
	CONTEXT->DSSetSamplers(1, 1, m_arrSam[1].GetAddressOf());
	CONTEXT->GSSetSamplers(1, 1, m_arrSam[1].GetAddressOf());
	CONTEXT->PSSetSamplers(1, 1, m_arrSam[1].GetAddressOf());

}

int CDevice::CreateBlendState()
{
	// 1. DEFAULT
	// SrcRGB * (1) + DestRGB * (0)
	m_arrBS[(UINT)BS_TYPE::DEFAULT] = nullptr;

	// 2. ALPHA_BLEND
	// SrcRGB * (SrcAlpha) + DestRGB * (1 - SrcAlpha)
	D3D11_BLEND_DESC desc = {};

	desc.AlphaToCoverageEnable = false;		// Ŀ�������� �ɼ� ��� ����
	desc.IndependentBlendEnable = false;	// ����Ÿ�� ���彺���̵� ��������

	desc.RenderTarget[0].BlendEnable = true;			// ���� ������Ʈ ���
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;	// ���� ȥ��
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // SrcRGB ���� ��� ==> (SrcA)
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // DestRGB ���� ��� ==> (1 - SrcA)	

	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(DEVICE->CreateBlendState(&desc, m_arrBS[(UINT)BS_TYPE::ALPHA_BLEND].GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}
