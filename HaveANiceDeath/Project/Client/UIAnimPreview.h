#pragma once
#include "UI.h"
#include <Engine/CGameObject.h>
// =======================================
// UIAnimPreview: 제작 중인 Animation 미리 재생
// =======================================

#include <Engine\CAnim.h>

class UIAnimPannel;
class UIAnimDetail;

class UIAnimPreview :
    public UI
{
private:
    UIAnimPannel*       m_MainPannel;
    UIAnimDetail*       m_DetailPannel;

    Ptr<CTexture>       m_AtlasTex;
    tAnimFrm*           m_CurFrm;
    int                 m_FrmSize;
    int                 m_CurFrmIdx;
    float               m_AccTime;
    bool                m_bPrevActive;

    float               m_ZoomFactor;

public:
    virtual void tick() override;
    virtual void begin() override;
    virtual void render_update() override;

    void Clear();

public:
    void SetAtlas(Ptr<CTexture> _atlas) { m_AtlasTex = _atlas; }
    void SetFrmSize(int _FrmSize) { m_FrmSize = _FrmSize; }
    void Init(tAnimFrm& _Frm) { m_CurFrm = &_Frm; m_CurFrmIdx = 0; m_AccTime = 0; }

private:
    void DrawCrosshair(const ImVec2& center, float size, ImDrawList* drawList);

public:
    UIAnimPreview();
    ~UIAnimPreview();
};

