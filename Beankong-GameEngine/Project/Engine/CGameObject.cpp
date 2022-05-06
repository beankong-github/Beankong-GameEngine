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
	// �ڽ� ������Ʈ ���� ����
	for (size_t i = 0; i < _origin.m_vecChild.size(); ++i)
	{
		AddChild(_origin.m_vecChild[i]->Clone());
	}
}

CGameObject::~CGameObject()
{
	Safe_Del_Vec(m_vecChild);
}

void CGameObject::start()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->start();
	}
}

void CGameObject::update()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->update();
	}
}

void CGameObject::lateupdate()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->lateupdate();
	}
}

void CGameObject::finalupdate()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finalupdate();
	}
}

void CGameObject::render()
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
			return;	// erase �� �ٷ� return�ϱ� ������ �ݺ����� ++iter�ص� ������.
		}
	}

}

void CGameObject::AddChild(CGameObject* _pChild)
{
}
