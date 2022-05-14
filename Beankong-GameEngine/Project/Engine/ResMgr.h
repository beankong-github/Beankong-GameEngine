#pragma once
#include "singleton.h"

#include "CResource.h"


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
    void CreateEngineShader();
    void CreateEngineComputeShader();
    void CreateEngineMaterial();
    void MakeInputLayoutInfo();

public:
    template<typename type>
    RES_TYPE GetResType();

    template<typename type>
    Ptr<type> Load(const wstring& _strKey, const wstring);

    template<typename type>
    Ptr<type> FindRes(const wstring& _strKey);

    template<typename type>
    void AddRes(const wstring& _strKey, type* _pRes);

};

