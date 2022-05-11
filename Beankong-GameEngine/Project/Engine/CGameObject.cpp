#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
	: m_pParent(nullptr)
	, m_bActive(true)
	, m_bDead(false)
	, m_iLayerIdx(-1)
{
}

CGameObject::CGameObject(const CGameObject& _origin)
	: CEntity(_origin)
	, m_pParent(nullptr)
	, m_bActive(true)
	, m_bDead(false)
	, m_iLayerIdx(-1)
{
	// 자식 오브젝트 벡터 복사
	for (size_t i = 0; i < _origin.m_vecChild.size(); ++i)
	{
		AddChild(_origin.m_vecChild[i]->Clone());
	}
}

CGameObject::~CGameObject()
{
	Safe_Del_Vec(m_vecChild);
}

void CGameObject::Start()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Start();
	}
}

void CGameObject::Update()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Update();
	}
}

void CGameObject::LateUpdate()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->LateUpdate();
	}
}

void CGameObject::FinalUpdate()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->FinalUpdate();
	}
}

void CGameObject::Render()
{
}

void CGameObject::DisconnectBetweenParent()
{
	assert(m_pParent);

	vector<CGameObject*>::iterator iter = m_pParent->m_vecChild.begin();
	for (;iter != m_pParent->m_vecChild.end();++iter)
	{
		if (*iter == this)
		{
			m_pParent->m_vecChild.erase(iter);
			m_pParent = nullptr;
			return;	// erase 후 바로 return하기 때문에 반복문에 ++iter해도 괜찮다.
		}
	}

}

void CGameObject::AddChild(CGameObject* _pChild)
{
}
