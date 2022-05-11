#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CScene :
    public CEntity
{
private:
    CLayer* m_arrLayer[MAX_LAYER];

public:
    void SetLayerName(int _iLayerIdx, const wstring& _strName);
    void AddRootObject(CGameObject* _pRootObj, int _iLayerIdx);
    void AddRootObject(CGameObject* _pRootObj, const wstring& _strLayerName);
    
    CLayer* GetLayer(int _iIdx);
    CLayer* GetLayer(const wstring* _strLayerName);

public:
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();

private:
    int GetLayerIdxFromName(const wstring& _strName);

    CLONE(CScene)

public:
    CScene();
    ~CScene();
};

