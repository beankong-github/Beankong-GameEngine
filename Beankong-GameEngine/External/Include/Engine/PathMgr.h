#pragma once
#include "singleton.h"

class PathMgr :
    public Singleton<PathMgr>
{
    SINGLE(PathMgr)

private:
	wchar_t m_strContentPath[256];

public:
	void init();


public:
	const wchar_t* GetContentPath() { return m_strContentPath; }

};

