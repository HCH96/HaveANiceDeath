#include "pch.h"
#include "UIMovement.h"

#include <Engine/CMovement.h>

UIMovement::UIMovement()
	: ComponentUI("Movement", "##Movement", COMPONENT_TYPE::MOVEMENT)
{
	SetSize(ImVec2(0.f, 210.f));
	SetComopnentTitle("Movement");
}

UIMovement::~UIMovement()
{
}

void UIMovement::render_update()
{
	if (not GetTargetObject())
		return;

	ComponentUI::render_update();
	CMovement* pMovement = GetTargetObject()->Movement();

	// get object data
	//Vec3  vForce;
	//Vec3  vAccel;
	//Vec3  vVelocity;
	Vec3  vGravityForce = pMovement->GetGravityForce();
	float fMass = pMovement->GetMass();
	float fInitSpeed = pMovement->GetInitSpeed();
	float fMaxSpeed_Ground = pMovement->GetMaxSpeed_Ground();
	float fMaxSpeed_InAir = pMovement->GetMaxSpeed_InAir();
	float fFrictionScale = pMovement->GetFrictionScale();
	bool  bUseGravity = pMovement->IsUseGravity();
	bool  bGround = pMovement->IsGround();

	// draw
	ImGui::Text("Mass");			ImGui::SameLine(130); ImGui::DragFloat("##Mass", &fMass);
	ImGui::Text("Initial Speed");		ImGui::SameLine(130); ImGui::DragFloat("##InitialSpeed", &fInitSpeed);
	ImGui::Text("Max Speed (Ground)");	ImGui::SameLine(130); ImGui::DragFloat("##MaxSpeed_Ground", &fMaxSpeed_Ground);
	ImGui::Text("Max Speed (InAir)");	ImGui::SameLine(130); ImGui::DragFloat("##MaxSpeed_inAir", &fMaxSpeed_InAir);
	ImGui::Text("Friction");			ImGui::SameLine(130); ImGui::DragFloat("##FrictionScale", &fFrictionScale);
	ImGui::Text("Gravity Force");		ImGui::SameLine(130); ImGui::DragFloat3("##FrictionScale", vGravityForce);
	ImGui::Text("Use Gravity");			ImGui::SameLine(130); ImGui::Checkbox("##UseGravity", &bUseGravity);
	ImGui::Text("Ground");				ImGui::SameLine(130); ImGui::Checkbox("##IsGround", &bGround);

	// set obect data
	pMovement->SetGravityForce(vGravityForce);
	pMovement->SetMass(fMass);
	pMovement->SetInitSpeed(fInitSpeed);
	pMovement->SetMaxSpeed_Ground(fMaxSpeed_Ground);
	pMovement->SetMaxSpeed_InAir(fMaxSpeed_InAir);
	pMovement->SetFrictionScale(fFrictionScale);
	pMovement->UseGravity(bUseGravity);
	pMovement->SetGround(bGround);
}