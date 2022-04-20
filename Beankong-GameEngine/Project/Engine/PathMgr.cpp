#include "pch.h"
#include "PathMgr.h"



PathMgr::PathMgr()
	: m_strContentPath{}
{}

PathMgr::~PathMgr()
{}

void PathMgr::init()
{
	// .exe ������ ��θ� ��ȯ
	GetCurrentDirectory(256, m_strContentPath);
	
	// OutputFile ������ �̵�
	int iLen = (int)wcslen(m_strContentPath);
	for (int i = iLen-1; 0 <= i; --i)
	{
		if (L'\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = L'\0';
			break;
		}
	}
	// content ���� ��θ� ���δ�.
	wcscat_s(m_strContentPath, L"\\bin\\content\\");

}
