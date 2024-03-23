#include "pch.h"
#include "TransformUI.h"

#include <Engine/CTransform.h>

TransformUI::TransformUI()
	: ComponentUI("Transform", "##Transform", COMPONENT_TYPE::TRANSFORM)	
{
	SetSize(ImVec2(0.f, 140.f));
	SetComopnentTitle("Transform");
}

TransformUI::~TransformUI()
{

}

void TransformUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	Vec3 vPos = GetTargetObject()->Transform()->GetRelativePos();
	Vec3 vScale = GetTargetObject()->Transform()->GetRelativeScale();
	Vec3 vRot = GetTargetObject()->Transform()->GetRelativeRotation();
	vRot.ToDegree();

	float startPosX = 100.0f;

	ImGui::Text("Position"); ImGui::SameLine(startPosX);  ImGui::DragFloat3("##Relative Position", vPos);
	ImGui::Text("Scale"); ImGui::SameLine(startPosX); ImGui::DragFloat3("##Relative Scale", vScale);
	ImGui::Text("Rotation"); ImGui::SameLine(startPosX); ImGui::DragFloat3("##Relative Rotation", vRot);

	vRot.ToRadian();
	GetTargetObject()->Transform()->SetRelativePos(vPos);
	GetTargetObject()->Transform()->SetRelativeScale(vScale);
	GetTargetObject()->Transform()->SetRelativeRotation(vRot);

	// Absolute °ª 
	bool bAbsolute = GetTargetObject()->Transform()->IsAbsolute();
	ImGui::Text("Scale Absolute"); ImGui::SameLine(); ImGui::Checkbox("##TransformAbsolute", &bAbsolute);
	GetTargetObject()->Transform()->SetAbsolute(bAbsolute);
}
