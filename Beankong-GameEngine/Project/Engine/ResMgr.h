#pragma once
#include "pch.h"

#include "PathMgr.h"

class ResMgr :
    public Singleton<ResMgr>
{
    SINGLE(ResMgr)

private:

public:
    void Init();
};

