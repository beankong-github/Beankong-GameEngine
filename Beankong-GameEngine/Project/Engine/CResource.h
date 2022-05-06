#pragma once
#include "CEntity.h"

#include "ResMgr.h"

class CResource :
    public CEntity
{
private:
    wstring m_strKey;
    wstring m_strRelativePath;
    UINT    m_iRefCount;

protected:  
    void SetKey(const wstring& _strKey)             { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strPath)   { m_strRelativePath = _strPath; }
    bool CheckFail(HRESULT _hr);

public:
    const wstring& GetKey()             { return m_strKey; }
    const wstring& GetRelativePath()    { return m_strRelativePath; }

protected:
    virtual int Load(const wstring& _strFilepath) = 0;
    CLONE_DISABLE(CResource)

private:
    void AddRef() { ++m_iRefCount; }
    void SubRef() { --m_iRefCount; }

public:
    CResource();
    virtual ~CResource();

    friend class ResMgr;

};

