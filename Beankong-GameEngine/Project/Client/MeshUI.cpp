#include "pch.h"
#include "MeshUI.h"

#include <Engine\CMesh.h>

MeshUI::MeshUI()
	: ResInfoUI("Mesh", RES_TYPE::MESH)
{
}

MeshUI::~MeshUI()
{
}

void MeshUI::update()
{
	// To do
	ResInfoUI::update();
}

void MeshUI::render_update()
{
	ResInfoUI::render_update();

	// To do
	CMesh* pMesh = dynamic_cast<CMesh*>(GetTargetRes());
	assert(pMesh);

	// Mesh Key(Name)
	string strKey = string(pMesh->GetKey().begin(), pMesh->GetKey().end());

	ImGui::Text("Mesh");
	ImGui::SameLine(100);
	ImGui::InputText("##MeshName", (char*)strKey.c_str(), strKey.capacity(), ImGuiInputTextFlags_ReadOnly);

}

