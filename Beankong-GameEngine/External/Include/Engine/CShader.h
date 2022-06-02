#pragma once
#include "CResource.h"
class CShader :
    public CResource
{
protected:
    ComPtr<ID3DBlob>    m_ErrBlob;


public:
    virtual int Load(const wstring& _strFilePath) { return S_OK; };

public:
    CShader();
    ~CShader();
};

