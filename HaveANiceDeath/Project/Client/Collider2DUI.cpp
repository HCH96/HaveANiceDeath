#include "pch.h"
#include "Collider2DUI.h"

#include <Engine\CCollider2D.h>

Collider2DUI::Collider2DUI()
	: ComponentUI("Collider2D", "##Collider2D", COMPONENT_TYPE::COLLIDER2D)
{
	SetSize(ImVec2(0.f, 120.f));
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

	//CCollider2D* pCol = GetTargetObject()->Collider2D();


	//Vec3 ColPos = pCol->GetOffset();
	//float fColPos[2] = {ColPos.x,ColPos.y};

	//Vec3 ColScale = pCol->GetOffset();
	//float fColScale[2] = { ColScale.x,ColScale.y };

	//ImGui::Text("Pos"); ImGui::SameLine();  ImGui::DragFloat2("##Collider Pos", fColPos);
	//ImGui::Text("Scale"); ImGui::SameLine();  ImGui::DragFloat2("##Collider Sclae", fColScale);

	//
	//GetTargetObject()->Collider2D()->SetOffset(Vec3(fColPos[0], fColPos[1],0.f));
	//GetTargetObject()->Collider2D()->SetScale(Vec3(fColScale[0], fColScale[1],1.f));



}