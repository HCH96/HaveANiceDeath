#include "pch.h"
#include "Light2DUI.h"

#include <Engine\CLight2D.h>

Light2DUI::Light2DUI()
	: ComponentUI("Light2D", "##Light2D", COMPONENT_TYPE::LIGHT2D)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComopnentTitle("Light2D");
}

Light2DUI::~Light2DUI()
{
}


void Light2DUI::render_update()
{
	if (ImGui::CollapsingHeader(this->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		SetSize(m_vSize);

		// get collider member vars
		int item_currentType = (int)GetTargetObject()->Light2D()->GetLightType();
		Vec4 vColor = GetTargetObject()->Light2D()->GetLightColor();
		Vec4 vSpecular = GetTargetObject()->Light2D()->GetSpecular();
		Vec4 vAmbient = GetTargetObject()->Light2D()->GetAmbient();
		float	fRadius = GetTargetObject()->Light2D()->GetRadius();
		float	fAngle = GetTargetObject()->Light2D()->GetAngle();

		// UI render
		const char* items[] = { "Directional", "Point", "Spot" };
		static ImGuiComboFlags flags = 0;
		ImGui::Text("Type"); ImGui::SameLine(80);
		if (ImGui::BeginCombo(" ", items[item_currentType], flags))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				const bool is_selected = (item_currentType == n);
				if (ImGui::Selectable(items[n], is_selected))
					item_currentType = n;

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::Text("Radius"); ImGui::SameLine(80); ImGui::DragFloat("##Collider Radius", &fRadius);
		ImGui::Text("Angle"); ImGui::SameLine(80); ImGui::DragFloat("##Collider Angle", &fAngle);

		ImGui::Text("Color"); ImGui::SameLine(80);
		float w = 200.f;
		ImGui::SetNextItemWidth(w);
		ImGui::ColorPicker3("##Light Color", (float*)&vColor, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

		ImGui::Text("Specular "); ImGui::SameLine(80);
		ImGui::SetNextItemWidth(w);
		ImGui::ColorPicker3("##Light Specular", (float*)&vSpecular, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

		ImGui::Text("Ambient  "); ImGui::SameLine(80);
		ImGui::SetNextItemWidth(w);
		ImGui::ColorPicker3("##Light Ambient", (float*)&vAmbient, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

		// set collider member vars
		GetTargetObject()->Light2D()->SetLightType((LIGHT_TYPE)item_currentType);
		GetTargetObject()->Light2D()->SetLightColor(vColor);
		GetTargetObject()->Light2D()->SetSpecular(vSpecular);
		GetTargetObject()->Light2D()->SetAmbient(vAmbient);
		GetTargetObject()->Light2D()->SetRadius(fRadius);
		GetTargetObject()->Light2D()->SetAngle(fAngle);
	}
	else
		SetSize(ImVec2(0.f, 60.f));


}
