#include "pch.h"
#include "SceneOutliner.h"

#include <Engine/CSceneMgr.h>
#include <Engine/CScene.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>

#include <Engine/CEventMgr.h>

#include "TreeUI.h"
#include "CImGuiMgr.h"
#include "InspectorUI.h"

SceneOutliner::SceneOutliner()
	: UI("SceneOutliner")
{
	m_TreeUI = new TreeUI(true);
	m_TreeUI->SetTitle("SceneOutliner");
	m_TreeUI->UseFrame(true);
	m_TreeUI->ShowDummyRoot(false);

	AddChild(m_TreeUI);

	// Click Delegate ���
	m_TreeUI->SetClickedDelegate(this, (CLICKED)&SceneOutliner::ObjectSelected);

	// Key Delegate ���
	m_TreeUI->SetKeyBinding(KEY::DEL, this, (KEY_FUNC)&SceneOutliner::OnPressDelete);

	Reset();
}

SceneOutliner::~SceneOutliner()
{
}



void SceneOutliner::update()
{
	if (CEventMgr::GetInst()->HasOBJEventOccured())
	{
		Reset();
	}

	UI::update();
}

void SceneOutliner::render_update()
{
}

void SceneOutliner::Reset()
{
	m_TreeUI->Clear();

	// ���� Scene�� �����´�
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Layer���� ��ȸ�ϸ鼭 Tree�� Node�� �߰��Ѵ�.
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurScene->GetLayer(i);

		vector<CGameObject*>& vecRoots = pLayer->GetRootObjects();

		for (size_t i = 0; i < vecRoots.size(); ++i)
		{
			AddGameObjectToTree(vecRoots[i], m_TreeUI->GetDummyNode());
		}
	}

}

void SceneOutliner::ObjectSelected(DWORD_PTR _dw)
{
	TreeNode* pNode = (TreeNode*)_dw;

	// ������ ��忡 �ش��ϴ� object�� ���Ѵ�
	string strKey = pNode->GetName();
	CGameObject* pObject = (CGameObject*)pNode->GetData();

	assert(pObject);

	// InspectorUI �� ����
	InspectorUI* pInspectorUI = (InspectorUI*)CImGuiMgr::GetInst()->FindUI("Inspector");

	// Inspector�� Target object�� ������ obj�� ����
	pInspectorUI->SetTargetObject(pObject);
}

void SceneOutliner::AddGameObjectToTree(CGameObject* _pObject, TreeNode* _pDestNode)
{
	// Tree�� Obj �߰�
	TreeNode* pNode = m_TreeUI->AddTreeNode(_pDestNode
		, string(_pObject->GetName().begin(), _pObject->GetName().end())
		, (DWORD_PTR)_pObject);

	// Child Obj�� �߰�
	const vector<CGameObject*>& vecChild = _pObject->GetChild();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddGameObjectToTree(vecChild[i], pNode);
	}
}

void SceneOutliner::OnPressDelete(DWORD_PTR _dw)
{
	// ���õ� Object Destroy
	TreeNode* pNode = (TreeNode*)_dw;

	if (nullptr == pNode)
		return;

	CGameObject* pTargetObj = (CGameObject*)pNode->GetData();
	pTargetObj->Destroy();

	// InspectorUI �� ã�Ƽ� Object �� nullptr �� �����Ѵ�.

	InspectorUI* pInspectorUI = (InspectorUI*)CImGuiMgr::GetInst()->FindUI("Inspector");
	pInspectorUI->SetTargetObject(nullptr);
}
