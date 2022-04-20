#include "pch.h"
#include "PathMgr.h"



PathMgr::PathMgr()
	: m_strContentPath{}
{}

PathMgr::~PathMgr()
{}

void PathMgr::init()
{
	// .exe 파일의 경로를 반환
	GetCurrentDirectory(256, m_strContentPath);
	
	// OutputFile 폴더로 이동
	int iLen = (int)wcslen(m_strContentPath);
	for (int i = iLen-1; 0 <= i; --i)
	{
		if (L'\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = L'\0';
			break;
		}
	}
	// content 폴더 경로를 붙인다.
	wcscat_s(m_strContentPath, L"\\bin\\content\\");

}
