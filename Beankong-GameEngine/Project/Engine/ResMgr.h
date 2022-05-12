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
};

