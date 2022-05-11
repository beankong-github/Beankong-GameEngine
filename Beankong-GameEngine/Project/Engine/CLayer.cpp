#include "pch.h"
#include "CLayer.h"

#include "CGameObject.h"

CLayer::CLayer()
	:m_iLayerIdx(-1)
{
}

CLayer::~CLayer()
{
	Safe_Del_Vec(m_vecRoot);
}


void CLayer::Start()
{
	for (int i = 0; i < m_vecRoot.size(); ++i)
	{
		m_vecRoot[i]->Start();
	}
}

void CLayer::Update()
{
	for (int i = 0; i < m_vecRoot.size(); ++i)
	{
		m_vecRoot[i]->Update();
	}
}

void CLayer::LateUpdate()
{
	for (int i = 0; i < m_vecRoot.size(); ++i)
	{
		m_vecRoot[i]->LateUpdate();
	}
}

void CLayer::FinalUpdate()
{
	for (int i = 0; i < m_vecRoot.size(); ++i)
	{
		m_vecRoot[i]->FinalUpdate();
	}
}

void CLayer::Render()
{
	for (int i = 0; i < m_vecRoot.size(); ++i)
	{
		m_vecRoot[i]->Render();
	}
}


void CLayer::AddRootObject(CGameObject* _pObj)
{
	m_vecRoot.push_back(_pObj);
}

void CLayer::RegisterObject(CGameObject* _pObj)
{
	m_vecObjects.push_back(_pObj);
}

void CLayer::DeregisterObject(CGameObject* _pObj)
{
	// 부모가 있는 Object에 대해선 Deregister를 진행하지 않는다
	if (_pObj->GetParent())
		return;

	vector<CGameObject*>::iterator iter = m_vecObjects.begin();
	for (; iter != m_vecObjects.end(); ++iter)
	{
		if (*iter == _pObj)
		{
			m_vecObjects.erase(iter);
			_pObj->m_iLayerIdx = -1;
			return;
		}
	}

}
