#pragma once
#include "singleton.h"
class ResMgr :
    public Singleton<ResMgr>
{
    SINGLE(ResMgr)

private:


public:
    void init();
};

