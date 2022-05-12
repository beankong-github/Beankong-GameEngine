#include "pch.h"
#include "CScene.h"

#include "CLayer.h"
#include "CGameObject.h"

CScene::CScene()
	: m_arrLayer{}
{
	// Layer 생성
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i] = new CLayer;
		m_arrLayer[i]->m_iLayerIdx = i;
	}
}

CScene::~CScene()
{
	Safe_Del_Arr(m_arrLayer);
}

void CScene::Start()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->Start();
	}
}

void CScene::Update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->Update();
	}
}

void CScene::LateUpdate()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->LateUpdate();
	}
}

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->FinalUpdate();
	}
}


int CScene::GetLayerIdxFromName(const wstring& _strName)
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (m_arrLayer[i]->GetName() == _strName)
			return m_arrLayer[i]->GetLayerIdx();
	}

	return -1;
}

void CScene::SetLayerName(int _iLayerIdx, const wstring& _strName)
{
	assert(0 <= _iLayerIdx && _iLayerIdx < MAX_LAYER);
	m_arrLayer[_iLayerIdx]->SetName(_strName);
}

void CScene::AddRootObject(CGameObject* _pRootObj, int _iLayerIdx)
{
	// LayerIdx가 범위를 벗어났거나 부모 오브젝트가 아닌 경우 assert
	assert(0 <= _iLayerIdx && _iLayerIdx < MAX_LAYER);
	assert(!_pRootObj->GetParent());

	// 부모 오브젝트를 레이어에 넣어준다
	m_arrLayer[_iLayerIdx]->AddRootObject(_pRootObj);

	// 부모 ~ 자식 오브젝트들을 순회하며 layer가 없는 object 대상으로 layer idx를 설정해준다.
	list<CGameObject*> queue;
	queue.push_back(_pRootObj);

	while (!queue.empty())
	{
		CGameObject* pTargetObj = queue.front();
		queue.pop_front();

		if (-1 == pTargetObj->m_iLayerIdx)
			pTargetObj->m_iLayerIdx = _iLayerIdx;
	
		const vector<CGameObject*>& vecChild = pTargetObj->GetChildVec();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}
}

void CScene::AddRootObject(CGameObject* _pRootObj, const wstring& _strLayerName)
{
	int iLayerIdx = GetLayerIdxFromName(_strLayerName);

	assert(iLayerIdx != -1);
	assert(!_pRootObj->m_pParent);

	m_arrLayer[iLayerIdx]->AddRootObject(_pRootObj);
}

CLayer* CScene::GetLayer(int _iIdx)
{
	assert(0 <= _iIdx && _iIdx < MAX_LAYER);
	return m_arrLayer[_iIdx];
}

CLayer* CScene::GetLayer(const wstring& _strLayerName)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (_strLayerName == m_arrLayer[i]->GetName())
		{
			return m_arrLayer[i];
		}
	}

	return nullptr;
}