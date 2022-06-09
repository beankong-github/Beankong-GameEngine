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

	// Click Delegate 등록
	m_TreeUI->SetClickedDelegate(this, (CLICKED)&SceneOutliner::ObjectSelected);

	// Key Delegate 등록
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

	// 현재 Scene을 가져온다
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Layer들을 순회하면서 Tree에 Node를 추가한다.
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

	// 선택한 노드에 해당하는 object를 구한다
	string strKey = pNode->GetName();
	CGameObject* pObject = (CGameObject*)pNode->GetData();

	assert(pObject);

	// InspectorUI 를 얻어옴
	InspectorUI* pInspectorUI = (InspectorUI*)CImGuiMgr::GetInst()->FindUI("Inspector");

	// Inspector의 Target object를 선택한 obj로 설정
	pInspectorUI->SetTargetObject(pObject);
}

void SceneOutliner::AddGameObjectToTree(CGameObject* _pObject, TreeNode* _pDestNode)
{
	// Tree에 Obj 추가
	TreeNode* pNode = m_TreeUI->AddTreeNode(_pDestNode
		, string(_pObject->GetName().begin(), _pObject->GetName().end())
		, (DWORD_PTR)_pObject);

	// Child Obj도 추가
	const vector<CGameObject*>& vecChild = _pObject->GetChild();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddGameObjectToTree(vecChild[i], pNode);
	}
}

void SceneOutliner::OnPressDelete(DWORD_PTR _dw)
{
	// 선택된 Object Destroy
	TreeNode* pNode = (TreeNode*)_dw;

	if (nullptr == pNode)
		return;

	CGameObject* pTargetObj = (CGameObject*)pNode->GetData();
	pTargetObj->Destroy();

	// InspectorUI 를 찾아서 Object 를 nullptr 로 세팅한다.

	InspectorUI* pInspectorUI = (InspectorUI*)CImGuiMgr::GetInst()->FindUI("Inspector");
	pInspectorUI->SetTargetObject(nullptr);
}
