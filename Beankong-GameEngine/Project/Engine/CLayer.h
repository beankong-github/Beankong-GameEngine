#pragma once
#include "CEntity.h"

class CLayer :
    public CEntity
{
private:
    int m_iLayerIdx;                    // Scene에서 현재 레이어의 인덱스
    
    vector<CGameObject*> m_vecRoot;     // 레이어에 속한 최상위 부모 오브젝트
    vector<CGameObject*> m_vecObjects;  // 매 프레임 마다 파악되는 레이어 소속 모든 오브젝트

public:
    int GetLayerIdx() { return m_iLayerIdx; }

public:
    void AddRootObject(CGameObject* _pObj);     // 최상위 오브젝트를 추가
    void RegisterObject(CGameObject* _pObj);    // 오브젝트를 이 레이어에 등록
    void DeregisterObject(CGameObject* _pObj);  // 오브젝트를 레이어에서 등록 해제
    void Clear() { m_vecObjects.clear(); }

    vector<CGameObject*>& GetRootObjects() { return m_vecRoot; }
    vector<CGameObject*>& GetObjects() { return m_vecObjects; }

    CLONE(CLayer);

public:
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
    void Render();

public:
    CLayer();
    ~CLayer();

    friend class CScene;
};

