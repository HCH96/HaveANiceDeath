#include "pch.h"
#include "UIAnimDetail.h"
#include "UIAnimPannel.h"

#include "Engine/CAnimator2D.h"
#include "Engine/CAnim.h"

UIAnimDetail::UIAnimDetail()
	: UI("Detail", "##Animation Tool_Detail")
	, m_AnimName("Untitled")
	, m_NumCellsX(1)
	, m_NumCellsY(1)
	, m_FPS(32)
{
	buf1[0] = '1';
	buf2[0] = '1';
	buf3[0] = '3'; buf3[1] = '2';
	Deactivate();
}

UIAnimDetail::~UIAnimDetail()
{
}

void UIAnimDetail::begin()
{
	m_MainPannel = (UIAnimPannel*)CImGuiMgr::GetInst()->FindUI("##Animation Tool_Main");
	m_PreviewPannel = (UIAnimPreview*)CImGuiMgr::GetInst()->FindUI("##Animation Tool_Preview");
}

void UIAnimDetail::tick()
{
	// detect close
	if (m_bPrevActive && not IsActivate())
	{
		m_MainPannel->Deactivate();
	}
	m_bPrevActive = IsActivate();
}

void UIAnimDetail::render_update()
{
	// ---------------------이름------------------------
	if (ImGui::CollapsingHeader("Naiming", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Animation Name "); ImGui::SameLine(130); ImGui::InputText("##AnimationNaming", m_AnimName, 32);
	}

	// ---------------------칸수------------------------
	if (ImGui::CollapsingHeader("Grid", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Num Cells X    "); ImGui::SameLine(130); ImGui::InputText("##AtlasNumCellsX", buf1, 10, ImGuiInputTextFlags_CharsDecimal);
		ImGui::Text("Num Cells Y    "); ImGui::SameLine(130); ImGui::InputText("##AtlasNumCellsY", buf2, 10, ImGuiInputTextFlags_CharsDecimal);
		m_NumCellsX = (string(buf1) == "") ? 0 : stoi(string(buf1));
		m_NumCellsY = (string(buf2) == "") ? 0 : stoi(string(buf2));
	}

	// ---------------------프레임------------------------
	if (ImGui::CollapsingHeader("Sprites", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// Global Offset 입력
		float fOffset[2] = {m_GlobalOffset.x, m_GlobalOffset.y};
		ImGui::Text("Global Offset"); ImGui::SameLine(130); ImGui::DragFloat2("##Relative Position", fOffset);
		m_GlobalOffset.x = fOffset[0]; m_GlobalOffset.y = fOffset[1];


		// Frame Run 입력
		ImGui::Text("FPS"); ImGui::SameLine(130); ImGui::InputText("##AnimationFrame", buf3, 10, ImGuiInputTextFlags_CharsDecimal);
		m_FPS = (string(buf3) == "") ? 32 : stoi(string(buf3));
		ImGui::Separator();

		// 각 frame 별 정보 출력
		if (not m_Atlas.Get() || m_vecAnimUV.empty())
			return;

		for (int i = 0; i < m_vecAnimUV.size(); ++i)
		{
			// draw img
			ImVec2 UV;
			UV.x = m_vecAnimUV[i].vLeftTop.x;
			UV.y = m_vecAnimUV[i].vLeftTop.y;
			ImGui::Image(m_Atlas->GetSRV().Get(), ImVec2(70, 70), UV, UV + ImVec2(m_vecAnimUV[i].vSlice.x, m_vecAnimUV[i].vSlice.y), ImVec4(1, 1, 1, 1), ImVec4(0.8f, 0.8f, 0.8f, 0.8f));

			// offset input
			Vec3 vOffset = Vec3(m_vecAnimUV[i].vOffset.x * (float)m_Atlas->GetWidth(), m_vecAnimUV[i].vOffset.y * (float)m_Atlas->GetHeight(), 0.f);

			string ID = "##detail" + std::to_string(i);
			ImGui::SameLine();

			ImGui::BeginChild(ID.c_str(), ImVec2(0, 70));

			ImGui::Text("[ %i ]", i);
			ImGui::Text("Offset  "); ImGui::SameLine(); ImGui::DragFloat2(ID.c_str(), vOffset, 0.1f);

			// frame input
			int fFps = 1.f / m_vecAnimUV[i].Duration;
			ImGui::Text("FPS     "); ImGui::SameLine(); ImGui::DragInt(ID.c_str(), &fFps, 0.1f);

			ImGui::EndChild();
			ImGui::Separator();

			// current anim vec update (owenr: UIAnimDeatil)
			m_vecAnimUV[i].vOffset = Vec2(vOffset.x / (float)m_Atlas->GetWidth(), vOffset.y / (float)m_Atlas->GetHeight());
			m_vecAnimUV[i].Duration = 1.f / fFps;
		}
	}
}

void UIAnimDetail::Activate()
{
	if (m_MainPannel && not m_MainPannel->IsActivate())
		m_MainPannel->Activate();
	else
		UI::Activate();
}

void UIAnimDetail::Deactivate()
{
	if (m_MainPannel && m_MainPannel->IsActivate())
		m_MainPannel->Deactivate();
	else
		UI::Deactivate();
}

void UIAnimDetail::Clear()
{
	m_GlobalOffset = Vec2(0.f, 0.f);
	m_Atlas = nullptr;
	m_vecAnimUV.clear();
	sprintf_s(m_AnimName, "%s", "Untitled");
	m_NumCellsX = 1;
	m_NumCellsY = 1;
	sprintf_s(buf1, "%s", "1");
	sprintf_s(buf1, "%s", "1");
}

void UIAnimDetail::UpdateFrm(vector<tAnimFrm>& _vec)
{
	Vec2 AtlasSize = Vec2(m_MainPannel->GetAtlas().Get()->GetWidth(), m_MainPannel->GetAtlas().Get()->GetHeight());
	m_vecAnimUV.clear();

	for (int i = 0; i < _vec.size(); ++i)
	{
		// UV값으로 세팅
		tAnimFrm frm = {};
		frm.vSlice = Vec2(_vec[i].vSlice.x / (float)AtlasSize.x, _vec[i].vSlice.y / (float)AtlasSize.y);
		frm.vLeftTop = Vec2(_vec[i].vLeftTop.x / (float)AtlasSize.x, _vec[i].vLeftTop.y / (float)AtlasSize.y);
		frm.vOffset = Vec2(_vec[i].vOffset.x / (float)AtlasSize.x, _vec[i].vOffset.y / (float)AtlasSize.y);
		frm.Duration = 1.f / m_FPS;
		frm.vBackground = Vec2(_vec[i].vBackground.x / (float)AtlasSize.x, _vec[i].vBackground.y / (float)AtlasSize.y);

		m_vecAnimUV.push_back(frm);
	}
}