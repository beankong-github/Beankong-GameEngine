#pragma once
#include "CResource.h"

class CMesh :
    public CResource
{
private:
    ComPtr<ID3D11Buffer>    m_VB;  // vertex buffer
    ComPtr<ID3D11Buffer>    m_IB;  // Index buffer

    D3D11_BUFFER_DESC       m_tVBDesc;
    D3D11_BUFFER_DESC       m_tIBDesc;

    UINT                    m_iVtxCount;
    UINT                    m_iIdxCount;

    void*                   m_pVtxSys;
    void*                   m_pIdxSys;

public:
    Vtx* GetVtxSysMem() { return (Vtx*)m_pVtxSys; }

public:
    virtual int Load(const wstring& _strFilePath) { return S_OK; }
    int Create(void* _pVtxSys, UINT _iVtxCount, void* _pIdxSys, UINT _iIdxCount);   // 정점 버퍼, 인덱스 버퍼 생성
    
    virtual void UpdateData() override;

public:
    void Render();
    void Render_Particle(UINT _iCount);

public:
    CMesh();
    ~CMesh();
};

