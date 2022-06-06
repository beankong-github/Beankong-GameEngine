#include "pch.h"
#include "GraphicsShaderUI.h"

#include <Engine\CGraphicsShader.h>

GraphicsShaderUI::GraphicsShaderUI()
	: ResInfoUI("GraphicsShader", RES_TYPE::GRAPHICS_SHADER)
{
}

GraphicsShaderUI::~GraphicsShaderUI()
{
}

void GraphicsShaderUI::update()
{	
	// To Do

	ResInfoUI::update();
}

void GraphicsShaderUI::render_update()
{
	ResInfoUI::render_update();
	
	// To Do
	CGraphicsShader* pGraphicsShader = dynamic_cast<CGraphicsShader*>(GetTargetRes());
	assert(pGraphicsShader);

	// Shader Name
	string strName = string(pGraphicsShader->GetKey().begin(), pGraphicsShader->GetKey().end());

	ImGui::Text("GraphicsShader");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	ImGui::InputText("##GraphicsShaderName", (char*)strName.c_str(), strName.capacity(), ImGuiInputTextFlags_ReadOnly);
	ImGui::Spacing();
	ImGui::Separator();

	// Rendering PipeLine ´Ü°è Function Name
	ImGui::TextColored(ImColor(0.3f, 0.3f, 0.9f), "Shader Function Name");
	ImGui::Spacing();

	strName = pGraphicsShader->GetVSName();
	ImGui::Text("VertexShader Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	ImGui::InputText("##VertexShaderName", (char*)strName.c_str(), strName.capacity(), ImGuiInputTextFlags_ReadOnly);
	if (ImGui::IsItemClicked() && "_DefaultFunc" != strName)
	{
		string path = pGraphicsShader->GetVSPath();
		path = "explorer " + path;
		system(path.c_str());
	}

	strName = pGraphicsShader->GetHSName();
	ImGui::Text("HullShader Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	ImGui::InputText("##HullShaderName", (char*)strName.c_str(), strName.capacity(), ImGuiInputTextFlags_ReadOnly);
	if (ImGui::IsItemClicked() && "_DefaultFunc" != strName)
	{
		string path = pGraphicsShader->GetHSPath();
		path = "explorer " + path;
		system(path.c_str());
	}

	strName = pGraphicsShader->GetDSName();
	ImGui::Text("DomainShader Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	ImGui::InputText("##DomainShaderName", (char*)strName.c_str(), strName.capacity(), ImGuiInputTextFlags_ReadOnly);
	if (ImGui::IsItemClicked() && "_DefaultFunc" != strName)
	{
		string path = pGraphicsShader->GetDSPath();
		path = "explorer " + path;
		system(path.c_str());
	}

	strName = pGraphicsShader->GetGSName();
	ImGui::Text("GeometryShader Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	ImGui::InputText("##GeometryShaderName", (char*)strName.c_str(), strName.capacity(), ImGuiInputTextFlags_ReadOnly);
	if (ImGui::IsItemClicked() && "_DefaultFunc" != strName)
	{
		string path = pGraphicsShader->GetGSPath();
		path = "explorer " + path;
		system(path.c_str());
	}

	strName = pGraphicsShader->GetPSName();
	ImGui::Text("PixelShader Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	ImGui::InputText("##PixelShaderName", (char*)strName.c_str(), strName.capacity(), ImGuiInputTextFlags_ReadOnly);
	if (ImGui::IsItemClicked() && "_DefaultFunc" != strName)
	{
		string path = pGraphicsShader->GetVSPath();
		path = "explorer " + path;
		system(path.c_str());
	}
	ImGui::Spacing();
	ImGui::Separator();

	// Domain Type
	ImGui::Text("Domain Type");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	if (ImGui::BeginCombo("##DomainTypes", ToString(pGraphicsShader->GetShaderDomain()), 0))
	{
		for (int i = 0; i < (int)SHADER_DOMAIN::END; i++)
		{
			if (ImGui::Selectable(ToString((SHADER_DOMAIN)i)))
			{
				pGraphicsShader->SetShaderDomain((SHADER_DOMAIN)i);
			}
		}
		ImGui::EndCombo();
	}

	// Resterizer Type
	ImGui::Text("Resterizer Type");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	if (ImGui::BeginCombo("##ResterizerTypes", ToString(pGraphicsShader->GetRSType()), 0))
	{
		for (int i = 0; i < (int)RS_TYPE::END; i++)
		{
			if (ImGui::Selectable(ToString((RS_TYPE)i)))
			{
				pGraphicsShader->SetRSType((RS_TYPE)i);
			}
		}
		ImGui::EndCombo();
	}

	// Depth-Stencil Type
	ImGui::Text("Depth-Stencil Type");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	if (ImGui::BeginCombo("##Depth-StencilTypes", ToString(pGraphicsShader->GetDSType()), 0))
	{
		for (int i = 0; i < (int)DS_TYPE::END; i++)
		{
			if (ImGui::Selectable(ToString((DS_TYPE)i)))
			{
				pGraphicsShader->SetDSType((DS_TYPE)i);
			}
		}
		ImGui::EndCombo();
	}

	// BlendState
	ImGui::Text("BlendState");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(180);
	if (ImGui::BeginCombo("##BlendState", ToString(pGraphicsShader->GetBSType()), 0))
	{
		for (int i = 0; i < (int)BS_TYPE::END; i++)
		{
			if (ImGui::Selectable(ToString((BS_TYPE)i)))
			{
				pGraphicsShader->SetBSType((BS_TYPE)i);
			}
		}
		ImGui::EndCombo();
	}





}
