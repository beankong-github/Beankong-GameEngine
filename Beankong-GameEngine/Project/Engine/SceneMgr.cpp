#include "pch.h"
#include "SceneMgr.h"

#include "CScene.h"
#include "CLayer.h" 

#include "CGameObject.h"

SceneMgr::SceneMgr()
	:m_pCurScene(nullptr)
{
}

SceneMgr::~SceneMgr()
{
	SAFE_DELETE(m_pCurScene);
}

void SceneMgr::Init()
{
	m_pCurScene = new CScene;

	// Set Layer Name
	m_pCurScene->SetLayerName(0, L"Tile");
	m_pCurScene->SetLayerName(1, L"Default");
	m_pCurScene->SetLayerName(2, L"Player");
	m_pCurScene->SetLayerName(3, L"Monster");


}

void SceneMgr::Progress()
{
	m_pCurScene->Update();
	m_pCurScene->LateUpdate();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::SpawnObject(CGameObject* _pSpawnObj, Vec3 _vWorldPos, wstring _strName, UINT _iLayerIdx)
{
}

void SceneMgr::SpawnObject(CGameObject* _pSpawnObj, UINT _iLayerIdx)
{
}

void SceneMgr::AddChild(CGameObject* _pParentObj, CGameObject* _pChildObject)
{
}

void SceneMgr::ClearAllLayer()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_pCurScene->GetLayer(i)->Clear();
	}
}
