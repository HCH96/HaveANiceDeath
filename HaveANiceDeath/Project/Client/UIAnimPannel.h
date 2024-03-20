#pragma once
#include "UI.h"
#include <Engine/CAnimator2D.h>
#include <Engine/CAsset.h>
#include <Engine/CTexture.h>

// =======================================
// UIAnimPannel: Animation Tool Pannel, Atlas ���ú�
// =======================================

#include <Engine\CAnim.h>

class ComponentUI;
class CAnim;
class UIAnimDetail;
class UIAnimPreview;

class UIAnimPannel :
    public UI
{
private:
    UIAnimDetail*           m_DetailPannel;
    UIAnimPreview*          m_PreviewPannel;

    Ptr<CTexture>           m_Atlas;
    wstring                 m_AtlasKey;
    ImVec2                  m_vAtlasRenderSize;
    ImVec2                  m_vGridNum;
    ImVec2                  m_vGridSize;
    vector<vector<bool>>    m_vecGridSelect;    // �ش� ĭ ���� ���
    vector<tAnimFrm>        m_vecAnim;          // ������ frame
    vector<Vec2>            m_vecOffset;

    bool                    m_bPrevActive;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render_update() override;

    virtual void Activate() override;
    virtual void Deactivate() override;

public:
    vector<tAnimFrm>& GetAnimVec() { return m_vecAnim; }
    Ptr<CTexture> GetAtlas() { return m_Atlas; }
    ImVec2 GetGridSize() { return m_vGridSize; }


private:
    // btn
    void Compile();
    void Save();
    void OpenFileWindow();
    void LoadAtlas(const wstring& _RelativePath);
    void ClearOffset();

    // inner
    void DrawGrid();
    void CreateFAnim(Vec2 _vLeftTop, Vec2 _vBackground);
    bool SelectionRect(ImVec2* start_pos, ImVec2* end_pos, ImGuiMouseButton mouse_button = ImGuiMouseButton_Left);
    void ResetSelectVec(bool _bool = false);
    void Clear();

public:
    UIAnimPannel();
    ~UIAnimPannel();
};