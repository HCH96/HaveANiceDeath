#include "pch.h"
#include "Animator2DUI.h"

#include <Engine\CAnimator2D.h>
#include <Engine\CAnim.h>

#include "CImGuiMgr.h"

#include "UIAnimDetail.h"
#include "UIAnimPannel.h"
#include "UIAnimPreview.h"

Animator2DUI::Animator2DUI()
	: ComponentUI("Animator2D", "##Animator2D", COMPONENT_TYPE::ANIMATOR2D)
{
	SetSize(ImVec2(0.f, 200.f));
	SetComopnentTitle("Animator2D");
}

Animator2DUI::~Animator2DUI()
{
}


void Animator2DUI::render_update()
{
	ComponentUI::render_update();


    // �ִϸ��̼� ��� ���
    ImGui::Text("Animations:");

    const map<wstring, CAnim*> CurAnimList = GetTargetObject()->Animator2D()->GetAnimations();

    vector<string> items;
    items.reserve(CurAnimList.size());

    for (const auto& iter : CurAnimList)
    {
        items.push_back(ToString(iter.first).c_str());
    }

    static int item_current_idx = 0; // Here we store our selection data as an index.
    if (ImGui::BeginListBox("##AnimationList", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
    {
        for (int i = 0; i < items.size(); i++)
        {
            const bool is_selected = (item_current_idx == i);

            if (ImGui::Selectable(items[i].c_str(), is_selected))
                item_current_idx = i;

            // ����Ʈ �� �ش� �׸��� Ŭ���Ǹ� ���̶���Ʈ �ɾ���
            if (is_selected)
                ImGui::SetItemDefaultFocus();

        }
        ImGui::EndListBox();
    }
    // ��ư �ʺ� ����
    float buttonWidth = 150.0f;

    // ��ư�� ������ �����Ͽ� ��ġ
    float posX = ImGui::GetWindowWidth() - buttonWidth*2 - ImGui::GetStyle().ItemSpacing.x;
    ImGui::SetCursorPosX(posX);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 0)); // ��ư �� ���� ����


    if (ImGui::Button("Add Animation", ImVec2(buttonWidth, 0)))
    {


    }


    ImGui::SameLine(0, ImGui::GetStyle().ItemSpacing.x);

    if (ImGui::Button("Delete Animation", ImVec2(buttonWidth, 0)))
    {
        wstring SelectedAnimKey = ToWString(items[item_current_idx]);
        DeleteAnimation(SelectedAnimKey);
    }
    ImGui::PopStyleVar();
}

void Animator2DUI::AddAnimation()
{
}

void Animator2DUI::DeleteAnimation(const wstring& _strAnimationName)
{
    GetTargetObject()->Animator2D()->DeleteAnim(_strAnimationName);
}

