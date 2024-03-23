#include "pch.h"
#include "Collider2DUI.h"

#include <Engine\CCollider2D.h>

Collider2DUI::Collider2DUI()
	: ComponentUI("Collider2D", "##Collider2D", COMPONENT_TYPE::COLLIDER2D)
{
	SetSize(ImVec2(0.f, 145.f));
	SetComopnentTitle("Collider2D");
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	CCollider2D* pCol = GetTargetObject()->Collider2D();
	
	Vec3 vOffset = pCol->GetOffset();
	Vec3 vScale = pCol->GetScale();
	Vec3 vRot = pCol->GetRotation();
	vRot.ToDegree();

	float startPosX = 100.0f;

	ImGui::Text("Offset"); ImGui::SameLine(startPosX);  ImGui::DragFloat3("##Relative Position", vOffset);
	ImGui::Text("Scale"); ImGui::SameLine(startPosX); ImGui::DragFloat3("##Relative Scale", vScale);
	ImGui::Text("Rotation"); ImGui::SameLine(startPosX); ImGui::DragFloat3("##Relative Rotation", vRot);

	vRot.ToRadian();
	pCol->SetOffset(vOffset);
	pCol->SetScale(vScale);
	pCol->SetRotationZ(vRot.z);

	// Absolute 값 
	bool bAbsolute = pCol->IsAbsolute();
	ImGui::Text("Scale Absolute"); ImGui::SameLine(); ImGui::Checkbox("##Collider2DAbsolute", &bAbsolute);
	pCol->SetAbsolute(bAbsolute);

	ImGui::SameLine(250);

	// 충돌중인 충돌체 개수
	int OverlapCount = pCol->GetOverlapCount();
	ImGui::Text("OverlapCount : %d", OverlapCount);

}