#pragma once
#include "CEntity.h"

class CLayer :
    public CEntity
{
private:
    int m_iLayerIdx;                    // Scene���� ���� ���̾��� �ε���
    
    vector<CGameObject*> m_vecRoot;     // ���̾ ���� �ֻ��� �θ� ������Ʈ
    vector<CGameObject*> m_vecObjects;  // �� ������ ���� �ľǵǴ� ���̾� �Ҽ� ��� ������Ʈ

public:
    int GetLayerIdx() { return m_iLayerIdx; }

public:
    void AddRootObject(CGameObject* _pObj);     // �ֻ��� ������Ʈ�� �߰�
    void RegisterObject(CGameObject* _pObj);    // ������Ʈ�� �� ���̾ ���
    void DeregisterObject(CGameObject* _pObj);  // ������Ʈ�� ���̾�� ��� ����
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

