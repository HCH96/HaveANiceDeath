#include "pch.h"
#include "ObjectController.h"

#include <Engine\CRenderMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>

#include <Engine\CCamera.h>

#include "UI.h"

ObjectController::ObjectController()
	: m_CurLayer("[All]")
{
}

ObjectController::~ObjectController()
{
}

void ObjectController::tick()
{
}

void ObjectController::render()
{

	if (!CRenderMgr::GetInst()->IsEditorMode())
	{
		return;
	}

	ImGui::Text("Layer"); ImGui::SameLine(150);
	//if (true)
	//{
	//	ImGui::SetNextWindowPos(ImVec2(100, 100)); // 절대 좌표 (100, 100)으로 설정
	//	ImGui::Begin("CustomTooltip", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings);

	//	static const char* items[] = { "Item 1", "Item 2", "Item 3" };
	//	static int selectedItem = -1;

	//	for (int i = 0; i < IM_ARRAYSIZE(items); i++)
	//	{
	//		if (ImGui::Selectable(items[i], selectedItem == i))
	//			selectedItem = i;
	//	}

	//	ImGui::End();
	//}



	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	m_vecLayerName.push_back("[All]");
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		wstring layerName = pLevel->GetLayer(i)->GetName();
		string strLayerName = string(layerName.begin(), layerName.end());
		if (strLayerName == "")
		{
			strLayerName = std::to_string(i);
		}

		m_vecLayerName.push_back("[" + std::to_string(i) + "]" + " " + strLayerName);
	}


	if (ImGui::BeginCombo("##LayerCombo", m_CurLayer.data())) {

		for (int i = 0; i < m_vecLayerName.size(); ++i)
		{
			if (ImGui::Selectable(m_vecLayerName[i].c_str())) 
			{
				m_CurLayer = m_vecLayerName[i];
			}
		}

		ImGui::EndCombo();
	}

	CCamera* EditorCam = CRenderMgr::GetInst()->GetEditorCamera();

	if (m_CurLayer == "[All]")
	{
		EditorCam->LayerCheckAll();
		EditorCam->LayerCheck(L"UI", false);
	}
	else
	{
		int LayerIdx = -1;

		size_t start_pos = m_CurLayer.find("[") + 1;
		size_t end_pos = m_CurLayer.find("]");
		if (start_pos != std::string::npos && end_pos != std::string::npos) 
		{
			std::string num_str = m_CurLayer.substr(start_pos, end_pos - start_pos);
			LayerIdx = std::stoi(num_str);
		}

		EditorCam->LayerCheckOffAll();
		EditorCam->LayerCheck(LayerIdx,true);
	}





	m_vecLayerName.clear();
}