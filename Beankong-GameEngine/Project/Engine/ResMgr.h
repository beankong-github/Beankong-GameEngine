#pragma once
#include "singleton.h"

#include "PathMgr.h"

#include "CResource.h"
#include "CPrefab.h"
#include "CMaterial.h"
#include "CMesh.h"
#include "CTexture.h"
#include "CGraphicShader.h"
#include "CComputerShader.h"


class ResMgr :
    public Singleton<ResMgr>
{
    SINGLE(ResMgr)

private:
    map<wstring, CResource*> m_Res[(UINT)RES_TYPE::END];

public:
    void Init();

private:
    void CreateEngineMesh();
    void CreateEngineTexture();
    void CreateEngineShader();
    void CreateEngineComputeShader();
    void CreateEngineMaterial();
    void MakeInputLayoutInfo();

public:
    template<typename type>
    RES_TYPE GetResType();

    template<typename type>
    Ptr<type> Load(const wstring& _strKey, const wstring& _strRelativePath, bool _bEngineRes);

    template<typename type>
    Ptr<type> FindRes(const wstring& _strKey);

    template<typename type>
    void AddRes(const wstring& _strKey, type* _pRes, bool _bEngineRes);

    //_flag : D3D11_BIND_FLAG
    Ptr<CTexture> CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight
        , DXGI_FORMAT _format, UINT _flag, bool _bEngineRes = false);

    Ptr<CTexture> CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _pTex2D, bool _bEngineRes = false);
};

template<typename type>
inline RES_TYPE ResMgr::GetResType()
{
    const type_info& info = typeid(type);

    // 입력된 클래스의 해시코드와 리소스 클래스 해시코드가 일치하면 해당 리소스 타입을 리턴해준다
    if (info.hash_code() == typeid(CPrefab).hash_code())
        return RES_TYPE::PREFAB;
    else if (info.hash_code() == typeid(CMaterial).hash_code())
        return RES_TYPE::MATERIAL;
    else if (info.hash_code() == typeid(CMesh).hash_code())
        return RES_TYPE::MESH;
    else if (info.hash_code() == typeid(CTexture).hash_code())
        return RES_TYPE::TEXTURE;
    else if (info.hash_code() == typeid(CGraphicShader).hash_code())
        return RES_TYPE::GRAPHICS_SHADER;
    else if (info.hash_code() == typeid(CComputerShader).hash_code())
        return RES_TYPE::COMPUTE_SHADER;

    return RES_TYPE::END;
}

template<typename type>
inline Ptr<type> ResMgr::Load(const wstring& _strKey, const wstring& _strRelativePath, bool _bEngineRes)
{
    RES_TYPE eType = GetResType(type);

    CResource* pRes = FindRes<type>(_strKey).Get(); // SmartPointer->Pointer
    
    if (pRes != nullptr)
        return Ptr<type>((type*)pRes);

    wstring strFilePath = PathMgr::GetInst()->GetContentPath() + _strRelativePath;
    
    pRes = new type;
    if (FAILED(pRes->Load(strFilePath)))
    {
        MessageBox(nullptr, L"리소스 로딩 실패!", L"리소스 로딩 오류", MB_OK);
        return nullptr;
    }

    pRes->SetKey(_strKey);
    pRes->SetRelativePath(_strRelativePath);
    pRes->m_bEngineRes = _bEngineRes;

    m_Res[(UINT)eType].insert(make_pair(_strKey, pRes));

    return Ptr<type>((type*)pRes);
} 

template<typename type>
inline Ptr<type> ResMgr::FindRes(const wstring& _strKey)
{
    RES_TYPE eType = GetResType(type);

    map<wstring, CResource*>::iterator iter = m_Res[(UINT)eType].find(_strKey);

    if (iter == m_Res[(UINT)eType].end())
        return nullptr;

    return (type*)iter->second;
}

template<typename type>
inline void ResMgr::AddRes(const wstring& _strKey, type* _pRes, bool _bEngineRes)
{
    RES_TYPE eType = GetResType<type>();

    Ptr<type> pRes = FindRes<type>(_strKey);

    assert(nullptr == pRes);

    _pRes->SetKey(_strKey);
    _pRes->m_bEngineRes = _bEngineRes;

    m_Res[(UINT)eType].insert(make_pair(_strKey, _pRes));
}
