#include "pch.h"
#include "ObjectController.h"


#include <Engine\CTimeMgr.h>
#include <Engine\CRenderMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CKeyMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>

#include <Engine\CTransform.h>
#include <Engine\CCamera.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include <Engine\CGameObject.h>

#include "UI.h"

ObjectController::ObjectController()
	: m_CurLayer("[All]")
	, m_ClickedObject(nullptr)
{
}

ObjectController::~ObjectController()
{
}

void ObjectController::FocusObject(CGameObject* _Object)
{
	CCamera* pEditCam = CRenderMgr::GetInst()->GetEditorCamera();

	if (nullptr == pEditCam)
		return;

	Vec3 ObjectPos = _Object->Transform()->GetRelativePos();
	Vec3 EditCamPos = pEditCam->Transform()->GetRelativePos();
	
	pEditCam->Transform()->SetRelativePos(Vec3(ObjectPos.x, ObjectPos.y, EditCamPos.z));
}

void ObjectController::tick()
{
	CCamera* pCurCam = nullptr;
	if (CRenderMgr::GetInst()->IsEditorMode())
	{
		pCurCam = CRenderMgr::GetInst()->GetEditorCamera();
	}
	else
	{
		vector<CCamera*> vecCams = CRenderMgr::GetInst()->GetCameras();
		if (vecCams.size() > 0)
		{
			pCurCam = vecCams[0];
		}
	}

	// 카메라가 없다면 return
	if (nullptr ==  pCurCam)
	{
		return;
	}

	// mouse pos
	ImVec2 mousePosition = ImGui::GetMousePos();

	// 마우스가 영역 안에 있다면
	if (mousePosition.x >= m_ViewportStart.x && mousePosition.y >= m_ViewportStart.y
		&& mousePosition.x <= m_ViewportStart.x + m_ViewportSize.x && mousePosition.y <= m_ViewportStart.y + m_ViewportSize.y)
	{
		// 해당 마우스 Pos -> World Pos로 변환 
		// 해당 영역의 중앙
		ImVec2 WinCenter = ImVec2(m_ViewportStart.x + m_ViewportSize.x/2.f, m_ViewportStart.y + m_ViewportSize.y/2.f);

		// Window 좌표계라 y축 뒤집어 줘야 함
		ImVec2 diffVec =  mousePosition - WinCenter;
		diffVec.y *= -1;
		
		Vec2 MouseWorldPos = pCurCam->GetWorldPosInWindow(Vec2(diffVec.x, diffVec.y));


		// 마우스가 클릭 되었다면
		if (KEY_TAP(KEY::LBTN))
		{
			CGameObject* pObject = FindObject(MouseWorldPos);

			Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
			pInspector->SetTargetObject(pObject);
			m_ClickedObject = pObject;

		}

		if (nullptr != m_ClickedObject)
		{
			// 현재 타겟된 오브젝트 정보 가져오기
			Vec3 TargetPos = m_ClickedObject->Transform()->GetWorldPos();
			Vec3 TargetScale = m_ClickedObject->Transform()->GetWorldScale();

			// 마우스가 오브젝트 범위 안에 있다면
			if (MouseWorldPos.x >= TargetPos.x - TargetScale.x / 2.f && MouseWorldPos.x <= TargetPos.x + TargetScale.x / 2.f
				&& MouseWorldPos.y >= TargetPos.y - TargetScale.y / 2.f && MouseWorldPos.y <= TargetPos.y + TargetScale.y / 2.f)
			{
				// 마우스가 클릭 되었다면
				if (KEY_PRESSED(KEY::LBTN))
				{
					// 오브젝트 이동
					Vec2 Drag = CKeyMgr::GetInst()->GetMouseDrag();

					if (Drag.Length() < 100.f)
					{
						float CamScale = pCurCam->GetScale();

						TargetPos.x += Drag.x * CamScale;
						TargetPos.y -= Drag.y * CamScale;

						m_ClickedObject->Transform()->SetRelativePos(TargetPos);
					}


				}
			}
		}

		// 키보드 이동
		if (nullptr != m_ClickedObject)
		{
			// 현재 타겟된 오브젝트 정보 가져오기
			Vec3 TargetPos = m_ClickedObject->Transform()->GetWorldPos();
			Vec3 TargetScale = m_ClickedObject->Transform()->GetWorldScale();

			if (KEY_PRESSED(KEY::LEFT))
			{
				TargetPos.x += -100.f * DT_ENGINE;

				m_ClickedObject->Transform()->SetRelativePos(TargetPos);
			}

			if (KEY_PRESSED(KEY::RIGHT))
			{
				TargetPos.x += 100.f * DT_ENGINE;

				m_ClickedObject->Transform()->SetRelativePos(TargetPos);
			}

			if (KEY_PRESSED(KEY::UP))
			{
				TargetPos.y += 100.f * DT_ENGINE;

				m_ClickedObject->Transform()->SetRelativePos(TargetPos);
			}

			if (KEY_PRESSED(KEY::DOWN))
			{
				TargetPos.y += -100.f * DT_ENGINE;

				m_ClickedObject->Transform()->SetRelativePos(TargetPos);
			}
		}

		//// 현재 타겟된 오브젝트가 없다면
		//if (nullptr == m_ClickedObject)
		//{
		//	// 마우스가 클릭 되었다면
		//	if (KEY_TAP(KEY::LBTN))
		//	{
		//		CGameObject* pObject = FindObject(MouseWorldPos);

		//		if (pObject != nullptr)
		//		{
		//			Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
		//			pInspector->SetTargetObject(pObject);
		//		}
		//	}
		//}
		//// 현재 타겟된 오브젝트가 있다면
		//else
		//{
		//	// 현재 타겟된 오브젝트 정보 가져오기
		//	Vec3 TargetPos = m_ClickedObject->Transform()->GetWorldPos();
		//	Vec3 TargetScale = m_ClickedObject->Transform()->GetWorldScale();

		//	// 마우스가 오브젝트 범위 안에 있다면
		//	if (MouseWorldPos.x >= TargetPos.x - TargetScale.x / 2.f && MouseWorldPos.x <= TargetPos.x + TargetScale.x / 2.f
		//		&& MouseWorldPos.y >= TargetPos.y - TargetScale.y / 2.f && MouseWorldPos.y <= TargetPos.y + TargetScale.y / 2.f)
		//	{
		//		// 마우스가 클릭 되었다면
		//		if (KEY_PRESSED(KEY::LBTN))
		//		{
		//			// 오브젝트 이동
		//			Vec2 Drag = CKeyMgr::GetInst()->GetMouseDrag();
		//			float CamScale = pCurCam->GetScale();

		//			TargetPos.x += Drag.x * CamScale;
		//			TargetPos.y -= Drag.y * CamScale;

		//			m_ClickedObject->Transform()->SetRelativePos(TargetPos);
		//		}
		//	}
		//	// 마우스가 오브젝트 범위 밖에 있다면
		//	else 
		//	{
		//		// 마우스가 클릭 되었다면
		//		if (KEY_TAP(KEY::LBTN))
		//		{
		//			CGameObject* pObject = FindObject(MouseWorldPos);


		//			if (pObject != nullptr)
		//			{
		//				Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
		//				pInspector->SetTargetObject(pObject);
		//			}
		//		}
		//	}
		//}

	}

	m_vecObject.clear();

}

void ObjectController::render()
{

	if (!CRenderMgr::GetInst()->IsEditorMode())
	{
		return;
	}

	ImGui::Text("Layer"); ImGui::SameLine(150);

	m_vecLayerName.push_back("[All]");

	const vector<string>& LayerName = CImGuiMgr::GetInst()->GetLayerName();

	for (int i = 0; i < LayerName.size(); ++i)
	{
		m_vecLayerName.push_back(LayerName[i]);
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

void ObjectController::FindObject(vector<CGameObject*>& _OutObject, Vec2 _MouseWorldPos)
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = nullptr;


	for (int i = 0; i < LAYER_MAX; ++i)
	{
		pLayer = CurLevel->GetLayer(i);

		// Layer의 오브젝트 가져오기
		const vector<CGameObject*> LayerObject = pLayer->GetLayerObjects();

		for (int j = 0; j < LayerObject.size(); ++j)
		{
			Vec3 ObjPos = LayerObject[j]->Transform()->GetWorldPos();
			Vec3 ObjScale = LayerObject[j]->Transform()->GetWorldScale();

			// 마우스 범위 안에 있다면
			if (_MouseWorldPos.x >= ObjPos.x - ObjScale.x / 2.f && _MouseWorldPos.x <= ObjPos.x + ObjScale.x / 2.f
				&& _MouseWorldPos.y >= ObjPos.y - ObjScale.y / 2.f && _MouseWorldPos.y <= ObjPos.y + ObjScale.y / 2.f)
			{
				_OutObject.push_back(LayerObject[j]);
			}
		}
	}
}

CGameObject* ObjectController::FindObject(Vec2 _MouseWorldPos)
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = nullptr;

	CGameObject* pTarget = nullptr;
	float minDepth = 100000.f;

	for (int i = 0; i < LAYER_MAX; ++i)
	{
		pLayer = CurLevel->GetLayer(i);

		// Layer의 오브젝트 가져오기
		const vector<CGameObject*> LayerObject = pLayer->GetLayerObjects();

		for (int j = 0; j < LayerObject.size(); ++j)
		{
			Vec3 ObjPos = LayerObject[j]->Transform()->GetWorldPos();
			Vec3 ObjScale = LayerObject[j]->Transform()->GetWorldScale();

			// 마우스 범위 안에 있다면
			if (_MouseWorldPos.x >= ObjPos.x - ObjScale.x / 2.f && _MouseWorldPos.x <= ObjPos.x + ObjScale.x / 2.f
				&& _MouseWorldPos.y >= ObjPos.y - ObjScale.y / 2.f && _MouseWorldPos.y <= ObjPos.y + ObjScale.y / 2.f)
			{

				// 가장 앞에 있는 오브젝트틀 타겟으로 함
				if (LayerObject[j]->Transform()->GetWorldPos().z < minDepth)
				{
					pTarget = LayerObject[j];
					minDepth = LayerObject[j]->Transform()->GetWorldPos().z;
				}
			}
		}
	}

	return pTarget;
}
