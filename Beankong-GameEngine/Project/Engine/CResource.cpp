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
    // Texture Load ���� ���θ� üũ�Ѵ�. 
    if (FAILED(_hr))
    {
        int iErr = GetLastError();
        wchar_t szText[256] = {};
        wsprintf(szText, L"�����ڵ� : %d", iErr);
        MessageBox(nullptr, szText, L"�ؽ��� �ε� ����!!", MB_OK);

        return true;
    }

    return false;
}
