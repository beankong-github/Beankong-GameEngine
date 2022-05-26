#include "pch.h"
#include "CGraphicsShader.h"

#include "PathMgr.h"
#include "CDevice.h"

#ifdef _DEBUG
UINT g_iFlag = D3DCOMPILE_DEBUG;
#else
UINT g_iFlag = 0;
#endif

vector<D3D11_INPUT_ELEMENT_DESC> CGraphicsShader::g_vecLayout;

CGraphicsShader::CGraphicsShader()
	: m_eDomain(SHADER_DOMAIN::DOMAIN_FORWARD)
	, m_eRSType(RS_TYPE::CULL_BACK)
	, m_eDSType(DS_TYPE::LESS)
	, m_eBSType(BS_TYPE::DEFAULT)
	, m_eTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

CGraphicsShader::~CGraphicsShader()
{
}

void CGraphicsShader::AddInputLayout(D3D11_INPUT_ELEMENT_DESC _desc)
{
	g_vecLayout.push_back(_desc);
}

void CGraphicsShader::AddScalarParamInfo(const wstring& _strDesc, SCALAR_PARAM _eParamType)
{
	m_vecScalarParamInfo.push_back(tScalarParamInfo{ _strDesc, _eParamType });
}

void CGraphicsShader::AddTexParamInfo(const wstring& _strDesc, TEX_PARAM _eParamType)
{
	m_vecTexParamInfo.push_back(tTexParamInfo{ _strDesc ,_eParamType });
}


int CGraphicsShader::CreateVertexShader(const wstring& _strRelativePath, const string& _strFunc)
{
	// 쉐이더 파일(.fx) 경로
	wstring strShaderPath = PathMgr::GetInst()->GetContentPath() + _strRelativePath;
	
	// VertexShader(HLSL) 컴파일
	HRESULT hr = D3DCompileFromFile(strShaderPath.c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, _strFunc.c_str(), "vs_5_0", g_iFlag, 0
		, m_VSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf());

	// 쉐이더 컴파일 실패
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Vertex Shader Compile Failed!!", MB_OK);
		return E_FAIL;
	}

	// 컴파일 된 코드로 VertexShader 객체 만들기
	if (FAILED(DEVICE->CreateVertexShader(m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize()
		, nullptr, m_VS.GetAddressOf())))
	{
		return E_FAIL;
	}
	
	// InputLayour Description들로 InputLayout 만들기 
	if (FAILED(DEVICE->CreateInputLayout(g_vecLayout.data(), (UINT)g_vecLayout.size()
		, m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize()
		, m_InputLayout.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CGraphicsShader::CreateGeometryShader(const wstring& _strRelativePath, const string& _strFunc)
{
	// 쉐이더 파일(.fx) 경로
	wstring strShaderPath = PathMgr::GetInst()->GetContentPath() + _strRelativePath;

	// GeometryShader(HLSL) 컴파일
	HRESULT hr = D3DCompileFromFile(strShaderPath.c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, _strFunc.c_str(), "gs_5_0", g_iFlag, 0
		, m_GSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Geometry Shader Compile Failed!!", MB_OK);
		return E_FAIL;
	}

	// 컴파일 된 코드로 GeometryShader 객체 만들기
	if (FAILED(DEVICE->CreateGeometryShader(m_GSBlob->GetBufferPointer(), m_GSBlob->GetBufferSize()
		, nullptr, m_GS.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CGraphicsShader::CreatePixelShader(const wstring& _strRelativePath, const string& _strFunc)
{	
	// 쉐이더 파일(.fx) 경로
	wstring strShaderPath = PathMgr::GetInst()->GetContentPath() + _strRelativePath;

	// PixelShader(HLSL) 컴파일
	HRESULT hr = D3DCompileFromFile(strShaderPath.c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, _strFunc.c_str(), "ps_5_0", g_iFlag, 0
		, m_PSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Pixel Shader Compile Failed!!", MB_OK);
		return E_FAIL;
	}

	// 컴파일 된 코드로 PixelShader 객체 만들기
	if (FAILED(DEVICE->CreatePixelShader(m_PSBlob->GetBufferPointer(), m_PSBlob->GetBufferSize()
		, nullptr, m_PS.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CGraphicsShader::UpdateData()
{
	// Input Layout, Shader, Render state 등 렌더링에 필요한 데이터들을 DeviceContext에 실어둔다.

	CONTEXT->IASetInputLayout(m_InputLayout.Get());
	CONTEXT->IASetPrimitiveTopology(m_eTopology);

	CONTEXT->VSSetShader(m_VS.Get(), 0, 0);
	CONTEXT->HSSetShader(m_HS.Get(), 0, 0);
	CONTEXT->DSSetShader(m_DS.Get(), 0, 0);
	CONTEXT->GSSetShader(m_GS.Get(), 0, 0);
	CONTEXT->PSSetShader(m_PS.Get(), 0, 0);

	CONTEXT->RSSetState(CDevice::GetInst()->GetRS(m_eRSType).Get());
	CONTEXT->OMSetDepthStencilState(CDevice::GetInst()->GetDS(m_eDSType).Get(), 0);
	CONTEXT->OMSetBlendState(CDevice::GetInst()->GetBS(m_eBSType).Get(), Vec4(), 0xffffffff);
}
