#include "pch.h"
#include "Animator2DUI.h"

#include "CImGuiMgr.h"


#include "UIAnimDetail.h"
#include "UIAnimPannel.h"
#include "UIAnimPreview.h"

Animator2DUI::Animator2DUI()
	: ComponentUI("Animator2D", "##Animator2D", COMPONENT_TYPE::ANIMATOR2D)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComopnentTitle("Animator2D");
}

Animator2DUI::~Animator2DUI()
{
}


void Animator2DUI::render_update()
{
	ComponentUI::render_update();

	if (ImGui::Button("Create Animation"))
	{

		UIAnimDetail* pUIAnimDetail = (UIAnimDetail*)CImGuiMgr::GetInst()->FindUI("##Animation Tool_Detail");
		pUIAnimDetail->Activate();

		UIAnimPannel* pUIAnimPannel = (UIAnimPannel*)CImGuiMgr::GetInst()->FindUI("##Animation Tool_Main");
		pUIAnimPannel->Activate();

		UIAnimPreview* pUIAnimPreview = (UIAnimPreview*)CImGuiMgr::GetInst()->FindUI("##Animation Tool_Preview");
		pUIAnimPreview->Activate();
	}



}