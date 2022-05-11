#pragma once
#include "CEntity.h"
class CGameObject :
    public CEntity
{
private:
    CGameObject*            m_pParent;
    vector<CGameObject*>     m_vecChild;

    int     m_iLayerIdx;

    bool    m_bActive;
    bool    m_bDead;

public:
    CGameObject();
    CGameObject(const CGameObject& _origin);
    ~CGameObject();

public:
    CLONE(CGameObject)

public:
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
    void Render();

public:
    CGameObject* GetParent()                    { return m_pParent; }
    const vector<CGameObject*>& GetChildVec()   { return m_vecChild; }

    bool IsActive()     { return m_bActive; }
    bool IsDead()       { return m_bDead; }

public:
    void DisconnectBetweenParent();
    void AddChild(CGameObject* _pChild);
};

