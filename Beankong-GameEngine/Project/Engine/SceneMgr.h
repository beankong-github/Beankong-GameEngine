#pragma once
#include "singleton.h"

class CScene;
class CGameObject;

class SceneMgr :
    public Singleton<SceneMgr>
{
    SINGLE(SceneMgr);

private:
    CScene* m_pCurScene;

public:
    CScene* GetCurScene() { return m_pCurScene; }

    void SpawnObject(CGameObject* _pSpawnObj, Vec3 _vWorldPos, wstring _strName, UINT _iLayerIdx);
    void SpawnObject(CGameObject* _pSpawnObj, UINT _iLayerIdx);
    void AddChild(CGameObject* _pParentObj, CGameObject* _pChildObject);

    void ClearAllLayer();


public:
    void Init();
    void Progress();

};

