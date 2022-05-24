#include "pch.h"
#include "ResMgr.h"

ResMgr::ResMgr()
{}

ResMgr::~ResMgr()
{
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Del_Map(m_Res[i]);
	}
}

Ptr<CTexture> ResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight, DXGI_FORMAT _format, UINT _flag, bool _bEngineRes)
{
	return Ptr<CTexture>();
}

Ptr<CTexture> ResMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _pTex2D, bool _bEngineRes)
{
	return Ptr<CTexture>();
}

