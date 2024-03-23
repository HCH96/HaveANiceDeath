#pragma once
#include "UI.h"
// =======================================
// UIAnimDetail: Animation per Frame UI
// =======================================

#include <Engine\CAnim.h>

class UIAnimPannel;
class UIAnimPreview;

class UIAnimDetail :
    public UI
{
private:
    UIAnimPannel*       m_MainPannel;
    UIAnimPreview*      m_PreviewPannel;

    Ptr<CTexture>       m_Atlas;
    vector<tAnimFrm>    m_vecAnimUV;
    char                m_AnimName[32];
    int                 m_NumCellsX;
    int                 m_NumCellsY;
    int                 m_FPS;
    char                buf1[10];        // NumCellsX Input Buff
    char                buf2[10];        // NumCellsY Input Buff
    char                buf3[10];        // FPS Input Buff
    bool                m_bPrevActive;

    Vec2                m_GlobalOffset;

public:
    Vec2 GetGlobalOffset() { return m_GlobalOffset; }

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render_update() override;

    virtual void Activate() override;
    virtual void Deactivate() override;
    void Clear();

    void SetAtlas(Ptr<CTexture> _atlas) { m_Atlas = _atlas; }
    void SetFrm(vector<tAnimFrm> _vec) { m_vecAnimUV = _vec; }
    void UpdateFrm(vector<tAnimFrm>& _vec);

    string GetAniName() { return string(m_AnimName); }
    ImVec2 GetGridNum() { return ImVec2(m_NumCellsX, m_NumCellsY); }
    int GetFPS() { return m_FPS; }
    tAnimFrm& GetFrmByIdx(int idx) { return m_vecAnimUV[idx]; }
    vector<tAnimFrm>& GetFrms() { return m_vecAnimUV; }

public:
    UIAnimDetail();
    ~UIAnimDetail();
};