#include "pch.h"
#include "CResource.h"


CResource::CResource()
    : m_iRefCount(0)
{
}

CResource::~CResource()
{
}

bool CResource::CheckFail(HRESULT _hr)
{
    // Texture Load 성공 여부를 체크한다. 
    if (FAILED(_hr))
    {
        int iErr = GetLastError();
        wchar_t szText[256] = {};
        wsprintf(szText, L"에러코드 : %d", iErr);
        MessageBox(nullptr, szText, L"텍스쳐 로딩 실패!!", MB_OK);

        return true;
    }

    return false;
}
