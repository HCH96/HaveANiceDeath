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


	// 애니메이션 목록 헤더
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

			// 리스트 중 해당 항목이 클릭되면 하이라이트 걸어줌
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndListBox();
	}
	// 버튼 너비 설정
	float buttonWidth = 150.0f;

	// 버튼을 오른쪽 정렬하여 배치
	float posX = ImGui::GetWindowWidth() - buttonWidth * 2 - ImGui::GetStyle().ItemSpacing.x;
	ImGui::SetCursorPosX(posX);

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 0)); // 버튼 간 간격 조정


	if (ImGui::Button("Add Animation", ImVec2(buttonWidth, 0)))
	{
		AddAnimation();
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
	// Animation 파일 가져와서 저장
	wchar_t szSelect[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szSelect;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szSelect);
	ofn.lpstrFilter = L"ALL\0*.*\0Anim\0*.anim";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	// 탐색창 초기 위치 지정
	wstring strInitPath = CPathMgr::GetContentPath();
	strInitPath += L"animation\\";
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	// 파일 선택
	if (GetOpenFileName(&ofn))
	{
		// 파일이름 분석
		wchar_t szFileName[128] = {};
		wchar_t szExt[16] = {};
		_wsplitpath_s(ofn.lpstrFile, nullptr, 0, nullptr, 0, szFileName, 128, szExt, 16);
		wstring relativePath = CPathMgr::GetRelativePath(ofn.lpstrFile);

		// open save file
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, (CPathMgr::GetContentPath() + relativePath).c_str(), L"rb");

		// save
		CAnim* pAnim = new CAnim;
		pAnim->LoadFromFile(pFile);

		GetTargetObject()->Animator2D()->AddAnimation(pAnim);

		// close save file
		fclose(pFile);
	}

}

void Animator2DUI::DeleteAnimation(const wstring& _strAnimationName)
{
	GetTargetObject()->Animator2D()->DeleteAnim(_strAnimationName);
}

