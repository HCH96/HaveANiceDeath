#include "pch.h"
#include "MtrlEditorUI.h"

#include <Engine/CAssetMgr.h>

#include "ParamUI.h"

MtrlEditorUI::MtrlEditorUI()
	: UI("MtrlInspector", "##MtrlInspector")
	, m_TargetMtrl(nullptr)
	, m_MtrlPath("New Material")
	, m_INT_Desc{ "INT_0_DESC","INT_1_DESC","INT_2_DESC","INT_3_DESC" }
	, m_FLOAT_Desc{ "FLOAT_0_DESC","FLOAT_1_DESC","FLOAT_2_DESC","FLOAT_3_DESC" }
	, m_V2_Desc{ "VEC2_0_DESC","VEC2_1_DESC","VEC2_2_DESC","VEC2_3_DESC" }
	, m_V4_Desc{ "VEC4_0_DESC","VEC4_1_DESC","VEC4_2_DESC","VEC4_3_DESC" }
	, m_TEX_Desc{ "TEX_0", "TEX_1", "TEX_2", "TEX_3", "TEX_4", "TEX_5" }
	, m_DescSize(200)
	, m_InputSize(100)
{
}

MtrlEditorUI::~MtrlEditorUI()
{
}


void MtrlEditorUI::render_update()
{
	// ��ư
	if (ImGui::Button("Save", ImVec2(80.f, 30.f)))
	{
		Save();
	}
	ImGui::SameLine();
	if (ImGui::Button("Load", ImVec2(80.f, 30.f)))
	{
		Load();
	}
	ImGui::SameLine();
	if (ImGui::Button("Create", ImVec2(100.f, 30.f)))
	{
		Create();
	}
	ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();


	if (nullptr == m_TargetMtrl)
		return;

	// ���͸��� ��� 
	ImGui::Text("Material"); ImGui::SameLine(100); ImGui::InputText("##MaterialPath", m_MtrlPath.data(), 32);

	// ���̴� �̸�
	ImGui::Text("Shader"); ImGui::SameLine(100); ImGui::InputText("##ShaderName", m_ShaderName.data(), 32);
	// Shader Drop üũ
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

		if (payload)
		{
			DWORD_PTR data = *((DWORD_PTR*)payload->Data);
			CAsset* pAsset = (CAsset*)data;
			if (ASSET_TYPE::GRAPHICS_SHADER == pAsset->GetType())
			{
				m_TargetMtrl->SetShader((CGraphicsShader*)pAsset);
				m_ShaderName = ToString(m_TargetMtrl->GetShader()->GetKey());
			}
		}

		ImGui::EndDragDropTarget();
	}


	ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
	// ----------------------------------------------------------------------------------------------------------------

	ImGuiStyle& style = ImGui::GetStyle();
	style.FramePadding.x = 4;

	// =========
	// Parameter
	// =========

	// INT_PARAM
	if (ImGui::CollapsingHeader("INT_PARAM", ImGuiTreeNodeFlags_None))
	{
		ImGui::Text("INT_0"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##INT_0_Desc", m_INT_Desc[0].data(), 32); ImGui::SameLine(m_DescSize + 120); ImGui::SetNextItemWidth(m_InputSize); ImGui::InputInt("##INT_0_DATA", &m_IntArr[0]);
		ImGui::Text("INT_1"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##INT_1_Desc", m_INT_Desc[1].data(), 32); ImGui::SameLine(m_DescSize + 120); ImGui::SetNextItemWidth(m_InputSize); ImGui::InputInt("##INT_1_DATA", &m_IntArr[1]);
		ImGui::Text("INT_2"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##INT_2_Desc", m_INT_Desc[2].data(), 32); ImGui::SameLine(m_DescSize + 120); ImGui::SetNextItemWidth(m_InputSize); ImGui::InputInt("##INT_2_DATA", &m_IntArr[2]);
		ImGui::Text("INT_3"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##INT_3_Desc", m_INT_Desc[3].data(), 32); ImGui::SameLine(m_DescSize + 120); ImGui::SetNextItemWidth(m_InputSize); ImGui::InputInt("##INT_3_DATA", &m_IntArr[3]);

		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
	}


	// FLOAT_PARAM
	if (ImGui::CollapsingHeader("FLOAT_PARAM", ImGuiTreeNodeFlags_None))
	{
		ImGui::Text("FLOAT_0"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##FLOAT_0_Desc", m_FLOAT_Desc[0].data(), 32); ImGui::SameLine(m_DescSize + 120); ImGui::SetNextItemWidth(m_InputSize); ImGui::InputFloat("##FLOAT_0_DATA", &m_FloatArr[0]);
		ImGui::Text("FLOAT_1"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##FLOAT_1_Desc", m_FLOAT_Desc[1].data(), 32); ImGui::SameLine(m_DescSize + 120); ImGui::SetNextItemWidth(m_InputSize); ImGui::InputFloat("##FLOAT_1_DATA", &m_FloatArr[1]);
		ImGui::Text("FLOAT_2"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##FLOAT_2_Desc", m_FLOAT_Desc[2].data(), 32); ImGui::SameLine(m_DescSize + 120); ImGui::SetNextItemWidth(m_InputSize); ImGui::InputFloat("##FLOAT_2_DATA", &m_FloatArr[2]);
		ImGui::Text("FLOAT_3"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##FLOAT_3_Desc", m_FLOAT_Desc[3].data(), 32); ImGui::SameLine(m_DescSize + 120); ImGui::SetNextItemWidth(m_InputSize); ImGui::InputFloat("##FLOAT_3_DATA", &m_FloatArr[3]);

		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
	}

	// Vec2_Param
	if (ImGui::CollapsingHeader("VEC2_PARAM", ImGuiTreeNodeFlags_None))
	{
		ImGui::Text("VEC2_0"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##VEC2_0_Desc", m_V2_Desc[0].data(), 32); ImGui::SameLine(); ImGui::SameLine(); ImGui::Text("  X"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputFloat("##VEC2_0_DATA_X", &m_V2Arr[0].x); ImGui::SameLine(); ImGui::Text(",  Y"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputFloat("##VEC2_0_DATA_Y", &m_V2Arr[0].y);
		ImGui::Text("VEC2_1"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##VEC2_1_Desc", m_V2_Desc[1].data(), 32); ImGui::SameLine(); ImGui::SameLine(); ImGui::Text("  X"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputFloat("##VEC2_1_DATA_X", &m_V2Arr[1].x); ImGui::SameLine(); ImGui::Text(",  Y"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputFloat("##VEC2_1_DATA_Y", &m_V2Arr[1].y);
		ImGui::Text("VEC2_2"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##VEC2_2_Desc", m_V2_Desc[2].data(), 32); ImGui::SameLine(); ImGui::SameLine(); ImGui::Text("  X"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputFloat("##VEC2_2_DATA_X", &m_V2Arr[2].x); ImGui::SameLine(); ImGui::Text(",  Y"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputFloat("##VEC2_2_DATA_Y", &m_V2Arr[2].y);
		ImGui::Text("VEC2_3"); ImGui::SameLine(100); ImGui::SetNextItemWidth(m_DescSize); ImGui::InputText("##VEC2_3_Desc", m_V2_Desc[3].data(), 32); ImGui::SameLine(); ImGui::SameLine(); ImGui::Text("  X"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputFloat("##VEC2_3_DATA_X", &m_V2Arr[3].x); ImGui::SameLine(); ImGui::Text(",  Y"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputFloat("##VEC2_3_DATA_Y", &m_V2Arr[3].y);

		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
	}

	// Vec4_Param
	if (ImGui::CollapsingHeader("VEC4_PARAM", ImGuiTreeNodeFlags_None))
	{
		ImGui::Text("VEC4_0"); ImGui::SameLine(100); ImGui::InputText("##VEC4_0_Desc", m_V4_Desc[0].data(), 32);
		ImGui::Text("Data"); ImGui::SameLine(100); ImGui::InputFloat4("##VEC4_0_DATA", m_V4Arr[0]);
		ImGui::Spacing(); ImGui::Spacing();

		ImGui::Text("VEC4_1"); ImGui::SameLine(100); ImGui::InputText("##VEC4_1_Desc", m_V4_Desc[1].data(), 32);
		ImGui::Text("Data"); ImGui::SameLine(100); ImGui::InputFloat4("##VEC4_1_DATA", m_V4Arr[1]);
		ImGui::Spacing(); ImGui::Spacing();

		ImGui::Text("VEC4_2"); ImGui::SameLine(100); ImGui::InputText("##VEC4_2_Desc", m_V4_Desc[2].data(), 32);
		ImGui::Text("Data"); ImGui::SameLine(100); ImGui::InputFloat4("##VEC4_2_DATA", m_V4Arr[2]);
		ImGui::Spacing(); ImGui::Spacing();

		ImGui::Text("VEC4_3"); ImGui::SameLine(100); ImGui::InputText("##VEC4_3_Desc", m_V4_Desc[3].data(), 32);
		ImGui::Text("Data"); ImGui::SameLine(100); ImGui::InputFloat4("##VEC4_3_DATA", m_V4Arr[3]);
		ImGui::Spacing(); ImGui::Spacing();
		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
	}

	// TEX_0 Param
	if (ImGui::CollapsingHeader("TEX_0_PARAM", ImGuiTreeNodeFlags_None))
	{
		// �ش� �ؽ��� �̹��� ���
		Ptr<CTexture> pTex = m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_0);
		ImGui::Text("TEX_0 Path "); ImGui::SameLine(100);
		ImGui::InputText("##TexName", (char*)m_TEX_PATH[0].c_str(), m_TEX_PATH[0].length(), ImGuiInputTextFlags_ReadOnly);

		// Texture Drop üũ
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

			if (payload)
			{
				DWORD_PTR data = *((DWORD_PTR*)payload->Data);
				CAsset* pAsset = (CAsset*)data;
				if (ASSET_TYPE::TEXTURE == pAsset->GetType())
				{
					m_TargetMtrl->SetTexParam(TEX_PARAM::TEX_0, (CTexture*)pAsset);
					m_TEX_PATH[0] = ToString(m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_0)->GetKey());
				}
			}

			ImGui::EndDragDropTarget();
		}

		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
		if (pTex != nullptr)
		{
			ImGui::Text("TEX_0 Desc"); ImGui::SameLine(100); ImGui::InputText("##TEX_0_Desc", m_TEX_Desc[0].data(), 32);

			// �ػ� ���� ���
			float Width = pTex->GetWidth();
			float Height = pTex->GetHeight();

			ImGui::Text("Width"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_0_Width", &Width, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Height"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_0_Height", &Height, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

			static bool use_text_color_for_tint = false;
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
			ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
			ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			ImGui::Image(pTex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
		}
	}

	// TEX_1 Param
	if (ImGui::CollapsingHeader("TEX_1_PARAM", ImGuiTreeNodeFlags_None))
	{
		// �ش� �ؽ��� �̹��� ���
		Ptr<CTexture> pTex = m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_1);
		ImGui::Text("TEX_1 Path "); ImGui::SameLine(100);
		ImGui::InputText("##TexName", (char*)m_TEX_PATH[1].c_str(), m_TEX_PATH[1].length(), ImGuiInputTextFlags_ReadOnly);

		// Texture Drop üũ
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

			if (payload)
			{
				DWORD_PTR data = *((DWORD_PTR*)payload->Data);
				CAsset* pAsset = (CAsset*)data;
				if (ASSET_TYPE::TEXTURE == pAsset->GetType())
				{
					m_TargetMtrl->SetTexParam(TEX_PARAM::TEX_1, (CTexture*)pAsset);
					m_TEX_PATH[1] = ToString(m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_1)->GetKey());
				}
			}

			ImGui::EndDragDropTarget();
		}

		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
		if (pTex != nullptr)
		{
			ImGui::Text("TEX_1 Desc"); ImGui::SameLine(100); ImGui::InputText("##TEX_1_Desc", m_TEX_Desc[1].data(), 32);

			// �ػ� ���� ���
			float Width = pTex->GetWidth();
			float Height = pTex->GetHeight();

			ImGui::Text("Width"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_1_Width", &Width, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Height"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_1_Height", &Height, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

			static bool use_text_color_for_tint = false;
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
			ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
			ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			ImGui::Image(pTex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
		}
	}

	// TEX_2 Param
	if (ImGui::CollapsingHeader("TEX_2_PARAM", ImGuiTreeNodeFlags_None))
	{
		// �ش� �ؽ��� �̹��� ���
		Ptr<CTexture> pTex = m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_2);
		ImGui::Text("TEX_2 Path "); ImGui::SameLine(100);
		ImGui::InputText("##TexName", (char*)m_TEX_PATH[2].c_str(), m_TEX_PATH[2].length(), ImGuiInputTextFlags_ReadOnly);

		// Texture Drop üũ
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

			if (payload)
			{
				DWORD_PTR data = *((DWORD_PTR*)payload->Data);
				CAsset* pAsset = (CAsset*)data;
				if (ASSET_TYPE::TEXTURE == pAsset->GetType())
				{
					m_TargetMtrl->SetTexParam(TEX_PARAM::TEX_2, (CTexture*)pAsset);
					m_TEX_PATH[2] = ToString(m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_2)->GetKey());
				}
			}

			ImGui::EndDragDropTarget();
		}

		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
		if (pTex != nullptr)
		{
			ImGui::Text("TEX_2 Desc"); ImGui::SameLine(100); ImGui::InputText("##TEX_2_Desc", m_TEX_Desc[2].data(), 32);

			// �ػ� ���� ���
			float Width = pTex->GetWidth();
			float Height = pTex->GetHeight();

			ImGui::Text("Width"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_2_Width", &Width, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Height"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_2_Height", &Height, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

			static bool use_text_color_for_tint = false;
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
			ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
			ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			ImGui::Image(pTex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
		}
	}

	// TEX_3 Param
	if (ImGui::CollapsingHeader("TEX_3_PARAM", ImGuiTreeNodeFlags_None))
	{
		// �ش� �ؽ��� �̹��� ���
		Ptr<CTexture> pTex = m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_3);
		ImGui::Text("TEX_3 Path "); ImGui::SameLine(100);
		ImGui::InputText("##TexName", (char*)m_TEX_PATH[3].c_str(), m_TEX_PATH[3].length(), ImGuiInputTextFlags_ReadOnly);

		// Texture Drop üũ
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

			if (payload)
			{
				DWORD_PTR data = *((DWORD_PTR*)payload->Data);
				CAsset* pAsset = (CAsset*)data;
				if (ASSET_TYPE::TEXTURE == pAsset->GetType())
				{
					m_TargetMtrl->SetTexParam(TEX_PARAM::TEX_3, (CTexture*)pAsset);
					m_TEX_PATH[3] = ToString(m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_3)->GetKey());
				}
			}

			ImGui::EndDragDropTarget();
		}
		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
		if (pTex != nullptr)
		{
			ImGui::Text("TEX_3 Desc"); ImGui::SameLine(100); ImGui::InputText("##TEX_3_Desc", m_TEX_Desc[3].data(), 32);

			// �ػ� ���� ���
			float Width = pTex->GetWidth();
			float Height = pTex->GetHeight();

			ImGui::Text("Width"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_3_Width", &Width, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Height"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_3_Height", &Height, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

			static bool use_text_color_for_tint = false;
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
			ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
			ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			ImGui::Image(pTex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
		}
	}

	// TEX_4 Param
	if (ImGui::CollapsingHeader("TEX_4_PARAM", ImGuiTreeNodeFlags_None))
	{
		// �ش� �ؽ��� �̹��� ���
		Ptr<CTexture> pTex = m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_4);
		ImGui::Text("TEX_4 Path "); ImGui::SameLine(100);
		ImGui::InputText("##TexName", (char*)m_TEX_PATH[4].c_str(), m_TEX_PATH[4].length(), ImGuiInputTextFlags_ReadOnly);

		// Texture Drop üũ
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

			if (payload)
			{
				DWORD_PTR data = *((DWORD_PTR*)payload->Data);
				CAsset* pAsset = (CAsset*)data;
				if (ASSET_TYPE::TEXTURE == pAsset->GetType())
				{
					m_TargetMtrl->SetTexParam(TEX_PARAM::TEX_4, (CTexture*)pAsset);
					m_TEX_PATH[4] = ToString(m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_4)->GetKey());
				}
			}

			ImGui::EndDragDropTarget();
		}
		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
		if (pTex != nullptr)
		{
			ImGui::Text("TEX_4 Desc"); ImGui::SameLine(100); ImGui::InputText("##TEX_4_Desc", m_TEX_Desc[4].data(), 32);

			// �ػ� ���� ���
			float Width = pTex->GetWidth();
			float Height = pTex->GetHeight();

			ImGui::Text("Width"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_4_Width", &Width, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Height"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_4_Height", &Height, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

			static bool use_text_color_for_tint = false;
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
			ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
			ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			ImGui::Image(pTex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
		}
	}

	// TEX_5 Param
	if (ImGui::CollapsingHeader("TEX_5_PARAM", ImGuiTreeNodeFlags_None))
	{
		// �ش� �ؽ��� �̹��� ���
		Ptr<CTexture> pTex = m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_5);
		ImGui::Text("TEX_5 Path "); ImGui::SameLine(100);
		ImGui::InputText("##TexName", (char*)m_TEX_PATH[5].c_str(), m_TEX_PATH[5].length(), ImGuiInputTextFlags_ReadOnly);

		// Texture Drop üũ
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

			if (payload)
			{
				DWORD_PTR data = *((DWORD_PTR*)payload->Data);
				CAsset* pAsset = (CAsset*)data;
				if (ASSET_TYPE::TEXTURE == pAsset->GetType())
				{
					m_TargetMtrl->SetTexParam(TEX_PARAM::TEX_5, (CTexture*)pAsset);
					m_TEX_PATH[5] = ToString(m_TargetMtrl->GetTexParam(TEX_PARAM::TEX_5)->GetKey());
				}
			}

			ImGui::EndDragDropTarget();
		}
		ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
		if (pTex != nullptr)
		{
			ImGui::Text("TEX_5 Desc"); ImGui::SameLine(100); ImGui::InputText("##TEX_5_Desc", m_TEX_Desc[5].data(), 32);

			// �ػ� ���� ���
			float Width = pTex->GetWidth();
			float Height = pTex->GetHeight();

			ImGui::Text("Width"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_5_Width", &Width, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Height"); ImGui::SameLine(100); ImGui::InputFloat("##TEX_5_Height", &Height, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

			static bool use_text_color_for_tint = false;
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
			ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
			ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			ImGui::Image(pTex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
		}
	}
}

void MtrlEditorUI::Save()
{
}

void MtrlEditorUI::Load()
{
}

void MtrlEditorUI::Create()
{
	Ptr<CMaterial> pMtrl = new CMaterial(false);
	m_TargetMtrl = pMtrl;
}

