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
	// 윈도우 핸들, 화면 해상도를 받아 멤버에 저장
	m_hWnd = _hWnd;
	m_vRenderResolution = _vRenderResolution;

	// Device, Device Context 생성
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
	
	// 멀티 샘플 레벨 체크
	// -> FEATURE_LEVEL_11 장치가 모든 렌더 대상 형식에 대해 4x MSAA를 지원하는지 체크 ( 쉽게 말해 장치가 DirectX11을 지원할 수 있는지 체크)
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

	// View 생성
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"뷰 생성 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// RenderTargetView, DepthStencilView 전달
	// Render시 출력버퍼 및 깊이버퍼 지정하기 위함
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

	// 뎁스스텐실 스테이트 생성
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
	// Target VieW 지우기
	m_pDeviceContext->ClearRenderTargetView(m_RTV.Get(), Vec4(1.f, 1.f, 1.f, 1.f));	// RT를 Clear하면서 채워넣을 색(배경색) 전달
	m_pDeviceContext->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.f, 0);
}

int CDevice::CreateSwapchain()
{
	// SwapChain Description 채우기
	DXGI_SWAP_CHAIN_DESC desc = {};

	desc.BufferCount = 1;																			// Front 버퍼를 기본으로 가지고 있어 버퍼 카운트는 1로 한다.
	desc.BufferDesc.Width = (UINT)m_vRenderResolution.x;											// 버퍼의 크기는 렌더링 해상도와 같아야한다.
	desc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;											// 픽셀 포멧(픽셀 정보): 32bit의 RGBA 픽셀
	desc.BufferDesc.RefreshRate.Denominator = 1;													// RefreshRate: 초당 화면 갱신 횟수
	desc.BufferDesc.RefreshRate.Numerator = 60;														// ㄴDenominator(분모): 1, Numerator(분자):60 => 초당 60회 
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;							// 
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// 픽셀을 렌더링하는 순서 ( ex: 좌->우, 상->하 )

	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			// 버퍼 사용 용도: 렌더 타겟
	desc.Flags = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;					// 두 버퍼 스왑 후 FB가 가지고 있던 정보를 어떻게 할 지 설정. Discard => 버림

	desc.SampleDesc.Count = 1;									// 픽셀 당 멀티 샘플 수 ( 멀티 샘플링 ) : 1일 경우 멀티 샘플링 off
	desc.SampleDesc.Quality = 0;								// 이미지 품질 수준 ( 수준이 높을 수록 성능 저하) 
																// 앤티앨리어싱이 없는 기본 샘플러 모드의 Count는 1이고 Quality는 0

	desc.OutputWindow = m_hWnd;									// 버퍼가 가진 내용을 출력할 대상 윈도우 핸들
	desc.Windowed = true;										// 창모드 : true

	// 스왑체인 생성하기
	ComPtr<IDXGIDevice> pDXGIDevice = nullptr;		// IDXGIDevice 인터페이스는 이미지 데이터를 생성하는 DXGI 객체에 대한 파생 클래스를 구현	
	ComPtr<IDXGIAdapter> pDXGIAdaptor = nullptr;	// IDXGIAdapter 인터페이스는 디스플레이 하위 시스템(하나 이상의 GPU, DAC 및 비디오 메모리 등)을 구현
	ComPtr<IDXGIFactory> pDXGIFactory = nullptr;	// IDXGIFactory 인터페이스는 전체 화면 전환을 처리하는 DXGI 개체를 생성하는 메서드를 구현

	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());	// Device에서 DXGIDevice를 얻어온다.
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdaptor.GetAddressOf());	// DXGIDevice의 부모 DXGIAdapter를 얻어온다.
	pDXGIAdaptor->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf());	// DXGIAdapter의 부모 DXGIFactory를 얻어온다

	pDXGIFactory->CreateSwapChain(m_pDevice.Get(), &desc, m_pSwapChain.GetAddressOf());		// DXGIFactory를 통해 스왑 체인을 생성한다.

	if (nullptr == m_pSwapChain)
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateView()
{
	// ===========
	//	 RTV 생성
	// =========== 
	// Render Target View : 렌더 타겟을 GPU에 전달하는 역할
	// 1. 스왑체인에서 Render Target(버퍼)을 가져옴
	ComPtr<ID3D11Texture2D> pBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBuffer.GetAddressOf());
	// 2. 가져온 버퍼를 사용해 RTV 생성 
	m_pDevice->CreateRenderTargetView(pBuffer.Get(), nullptr, m_RTV.GetAddressOf());

	if (nullptr == m_RTV)
		return E_FAIL;

	// ===========
	//	 DSV 생성
	// =========== 
	// Depth Stencil View : Depth Stencil을 GPU에 전달하는 역할
	// 1. Depth Stencil Target(버퍼)으로 사용할 텍스처를 생성
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width = (UINT)m_vRenderResolution.x;						// 렌더 크기와 동일하게 텍스처 생성
	desc.Height = (UINT)m_vRenderResolution.y;
	desc.MipLevels = 0;												// 생성할 최대 민맵
	desc.ArraySize = 1;												// 텍스처 배열 크기

	desc.CPUAccessFlags = 0;										// CPU Access 허용 유형(D3D11_CPU_ACCESS_FLAG)을 정하는 플래그. CPU 접근이 필요 없을 경우 0
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;		// 파이프라인 단계에 바인딩하기 위해 텍스처 사용 용도를 지정하는 플래그
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;					// 텍스처를 읽고 쓰는 방법을 식별하기 위한 값
	desc.MiscFlags = 0;												// 일반적이지 않은 다른 리소스 옵션을 식별하는 플래그

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;					// Texture format, 24bit는 깊이 정보, 8bit는 스텐실 정보를 저장하는 32bit z-buffer 타입 텍스처이다.

	m_pDevice->CreateTexture2D(&desc, nullptr, m_pDepthStencilTarget.GetAddressOf());	// 텍스처 생성

	if (nullptr == m_pDepthStencilTarget)
		return E_FAIL;

	// 2. 생성한  Depth Stencil Target 이용해 DSV 생성
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
	// 반시계(뒷면) 제외, 시계방향(앞면) 통과
	m_arrRS[(UINT)RS_TYPE::CULL_BACK] = nullptr;


	// 2. CULL_FRONT
	// 반시계(뒷면) 통과, 시계방향(앞면) 제외
	desc.CullMode = D3D11_CULL_FRONT;
	desc.FillMode = D3D11_FILL_SOLID;
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());
	if (FAILED(hr))
		return E_FAIL;

	// 3. CULL_NONE
	// 양면 모두 그리기, (주로 단면 형태의 메쉬를 앞 뒤에서 볼 때 사용)
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());
	if (FAILED(hr))
		return E_FAIL;

	// 4. WIRE_FRAME
	// 양면 모두 그리기, 뼈대 픽셀만 렌더링
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_WIREFRAME;
	hr = DEVICE->CreateRasterizerState(&desc, m_arrRS[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());
	if (FAILED(hr))
		return E_FAIL;


	return S_OK;
}

int CDevice::CreateDepthStencilState()
{// 스텐실 옵션은 아직 사용하지 않음
	/*
	desc.StencilEnable = false;
	desc.BackFace;
	desc.FrontFace;
	desc.StencilReadMask;
	desc.StencilWriteMask;
	*/


	// 1. Less (Default)
	// 깊이 값이 더 작은 (더 앞에 있는) 물체 우선 통과
	m_arrDS[(UINT)DS_TYPE::LESS] = nullptr;


	// 2. LessEqual
	D3D11_DEPTH_STENCIL_DESC desc = {};

	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf())))
		return E_FAIL;


	// 3. Greater
	// 깊이 값이 더 큰 (더 앞에 있는) 물체 우선 통과
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
	// 깊이 값 테스트 x, 깊이 기록 o ( 다른 물체들이 No Test한 물체의 깊이 값에 영향을 받음 )
	desc.DepthEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::NO_TEST].GetAddressOf())))
		return E_FAIL;


	// 6. No Write
	// 깊이 값 테스트 o, 깊이 기록 x ( 다른 물체들의 깊이 값의 영향을 받으나 영향을 주지 않음 )
	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	if (FAILED(DEVICE->CreateDepthStencilState(&desc, m_arrDS[(UINT)DS_TYPE::NO_WRITE].GetAddressOf())))
		return E_FAIL;


	// 7. No Test No Write
	// 깊이 값 테스트 x, 깊이 기록 x
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

	desc.AlphaToCoverageEnable = false;		// 커버레이지 옵션 사용 유무
	desc.IndependentBlendEnable = false;	// 렌더타겟 블랜드스테이드 독립실행

	desc.RenderTarget[0].BlendEnable = true;			// 블랜딩 스테이트 사용
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;	// 가산 혼합
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // SrcRGB 블랜드 계수 ==> (SrcA)
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // DestRGB 블랜드 계수 ==> (1 - SrcA)	

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
