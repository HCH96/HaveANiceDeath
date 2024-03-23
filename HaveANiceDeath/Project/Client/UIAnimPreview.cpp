#include "pch.h"
#include "UIAnimPreview.h"
#include "UIAnimPannel.h"
#include "UIAnimDetail.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CAnim.h>
#include <Engine\CKeyMgr.h>
#include <Engine\CTimeMgr.h>

UIAnimPreview::UIAnimPreview()
	: UI("Preview", "##Animation Tool_Preview")
	, m_FrmSize(0)
	, m_CurFrmIdx(-1)
	, m_AccTime(0)
	, m_ZoomFactor(1.f)
{
	Deactivate();
}

UIAnimPreview::~UIAnimPreview()
{
}

void UIAnimPreview::begin()
{
	m_DetailPannel = (UIAnimDetail*)CImGuiMgr::GetInst()->FindUI("##Animation Tool_Detail");
	m_MainPannel = (UIAnimPannel*)CImGuiMgr::GetInst()->FindUI("##Animation Tool_Main");
}

void UIAnimPreview::tick()
{
	if (not m_AtlasTex.Get() || m_CurFrmIdx == -1)
		return;

	// frame 재생
	m_AccTime += DT_ENGINE;
	if (m_AccTime > (*m_CurFrm).Duration)
	{
		++m_CurFrmIdx;

		if (m_CurFrmIdx >= m_FrmSize)
		{
			m_CurFrmIdx = 0;
		}

		m_CurFrm = &m_DetailPannel->GetFrmByIdx(m_CurFrmIdx);
		m_AccTime = 0.f;
	}

	// detect close
	if (m_bPrevActive && not IsActivate())
	{
		m_MainPannel->Deactivate();
	}
	m_bPrevActive = IsActivate();


	// Zoom Factor 조절

	if (KEY_PRESSED(KEY::LEFT))
	{
		m_ZoomFactor -= 1.f * DT_ENGINE;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_ZoomFactor += 1.f * DT_ENGINE;
	}

	ImVec2 mousePosition = ImGui::GetMousePos();

	// 마우스가 영역 안에 있다면
	if (mousePosition.x >= m_WndStartPos.x && mousePosition.y >= m_WndStartPos.y
		&& mousePosition.x <= m_WndStartPos.x + m_WndSize.x && mousePosition.y <= m_WndStartPos.y + m_WndSize.y)
	{
		// 마우스 드래그
		if (KEY_PRESSED(KEY::LBTN) && CKeyMgr::GetInst()->GetMouseDrag() != Vec2(0.f, 0.f))
		{
			Vec2 DragScale = CKeyMgr::GetInst()->GetMouseDrag();
			Vec2 GlobalOffset = m_DetailPannel->GetGlobalOffset();
			DragScale.y *= -1;

			GlobalOffset -= DragScale;
			m_DetailPannel->SetGlobalOffset(GlobalOffset);
		}
	}
	


}

void UIAnimPreview::render_update()
{
	if (not m_AtlasTex.Get() || m_CurFrmIdx == -1)
		return;

	// draw img
	ImGui::BeginChild("##Prevew Image");
	m_WndStartPos = ImGui::GetWindowPos();

	// size: grid
	static float previewScaling = 0.5f;
	ImVec2 atlasSize = ImVec2(m_AtlasTex->GetWidth(), m_AtlasTex->GetHeight());
	ImVec2 Size = ImVec2(m_CurFrm->vSlice.x, m_CurFrm->vSlice.y) * atlasSize;
	ImGuiIO& io = ImGui::GetIO();

	if (io.MouseWheel != 0.0f && ImGui::IsWindowHovered())
	{
		float zoomSpeed = 0.5f;
		float zoomDelta = io.MouseWheel * zoomSpeed;
		previewScaling += zoomDelta;
		if (previewScaling < 0) previewScaling = 0;
	}
	Size *= previewScaling;

	// Global Offset 가져오기
	Vec2 GlobalOffset = m_DetailPannel->GetGlobalOffset();
	GlobalOffset.x /= atlasSize.x;
	GlobalOffset.y /= atlasSize.y;

	// 그리는 좌표: offset 계산 (y축 좌표 반대로)
	ImVec2 CenterPos = ImGui::GetWindowContentRegionMax() * 0.5f;
	m_WndSize = ImGui::GetWindowContentRegionMax();

	ImVec2 ImgPos = CenterPos - (Size * 0.5) - ImVec2(m_CurFrm->vOffset.x + GlobalOffset.x, -(m_CurFrm->vOffset.y+ GlobalOffset.y)) * atlasSize * previewScaling;
	ImGui::SetCursorPos(ImgPos);
	ImVec2 LeftTopUV = ImVec2(m_CurFrm->vLeftTop.x, m_CurFrm->vLeftTop.y);
	ImVec2 RightBottomUV = LeftTopUV + ImVec2(m_CurFrm->vSlice.x, m_CurFrm->vSlice.y);

	ImGui::Image(m_AtlasTex->GetSRV().Get(), Size, LeftTopUV, RightBottomUV);

	// cross hair
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	DrawCrosshair(ImGui::GetWindowPos() + CenterPos, 30.f, drawList);

	ImGui::EndChild();

}

void UIAnimPreview::Clear()
{
	m_AtlasTex = nullptr;
	m_CurFrm = nullptr;
	m_CurFrmIdx = -1;
	m_FrmSize = 0;
	m_AccTime = 0;
}


void UIAnimPreview::DrawCrosshair(const ImVec2& center, float size, ImDrawList* drawList) 
{
	float halfSize = size * 0.5f;
	ImVec2 topLeft = ImVec2(center.x - halfSize, center.y - halfSize);
	ImVec2 bottomRight = ImVec2(center.x + halfSize, center.y + halfSize);

	drawList->AddLine(ImVec2(topLeft.x, center.y), ImVec2(bottomRight.x, center.y), IM_COL32(0, 0, 0, 255), 6);
	drawList->AddLine(ImVec2(center.x, topLeft.y), ImVec2(center.x, bottomRight.y), IM_COL32(0, 0, 0, 255), 6);
	drawList->AddLine(ImVec2(topLeft.x, center.y), ImVec2(bottomRight.x, center.y), IM_COL32(255, 255, 255, 255), 3);
	drawList->AddLine(ImVec2(center.x, topLeft.y), ImVec2(center.x, bottomRight.y), IM_COL32(255, 255, 255, 255), 3);
}