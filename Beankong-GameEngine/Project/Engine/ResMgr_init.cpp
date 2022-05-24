#include "pch.h"
#include "ResMgr.h"

void ResMgr::Init()
{}

void ResMgr::CreateEngineMesh()
{
}

void ResMgr::CreateEngineTexture()
{
}

void ResMgr::CreateEngineShader()
{
}

void ResMgr::CreateEngineComputeShader()
{
}

void ResMgr::CreateEngineMaterial()
{
}

void ResMgr::MakeInputLayoutInfo()
{
}

Ptr<CTexture> ResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight, DXGI_FORMAT _format, UINT _flag, bool _bEngineRes)
{
	return Ptr<CTexture>();
}

Ptr<CTexture> ResMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _pTex2D, bool _bEngineRes)
{
	return Ptr<CTexture>();
}
