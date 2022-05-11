#pragma once
#include "singleton.h"
#include "CScene.h"

class SceneMgr :
    public Singleton<SceneMgr>
{
    SINGLE(SceneMgr);

private:
    CScene* curScene;

public:
    CScene* GetCurScene() { return curScene; }

public:
    void init();
    void Update();

};

