#pragma once
#include "singleton.h"

#include "CAssetMgr.h"

class CGameObject;
class CCamera;
class CLight2D;
class CStructuredBuffer;

class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);
private:
    // renderCamera
    vector<CCamera*>        m_vecCam;
    CCamera*                m_EditorCam;

    // PostProcess
    Ptr<CTexture>           m_PostProcessTex;

    // 광원
    CStructuredBuffer*      m_Light2DBuffer;
    vector<CLight2D*>       m_vecLight2D;

    // Debug
    list<tDebugShapeInfo>   m_DbgShapeInfo;
    CGameObject*            m_pDebugObj;
    bool                    m_DebugPosition;

    // NoiseTexture
    vector<Ptr<CTexture>>   m_vecNoiseTex;

    // render function pointer
    typedef void(CRenderMgr::* RENDER_FUNC)(void);
    RENDER_FUNC             m_RenderFunc;
    bool                    m_isEditorMode;

    // RenderTarget Copy Texture
    Ptr<CTexture>           m_RTCopyTex;

    // ============
    // Bloom Effect
    // ============

    // Bloom Level
    int                     m_BloomLevel;

    // GlowTexture
    Ptr<CTexture>           m_RTGlow;
    vector<Ptr<CTexture>>   m_BloomFirst;
    vector<Ptr<CTexture>>   m_BloomSecond;

public:
    CCamera* GetEditorCamera() { return m_EditorCam; }
    Ptr<CTexture> GetRTCopyTex() { return m_RTCopyTex; }
    Ptr<CTexture> GetRTGlow() { return m_RTGlow; }
    Ptr<CTexture> GetPostProcessTex() { return m_PostProcessTex; }
    const vector<CCamera*>& GetCameras() { return m_vecCam; }
    bool IsEditorMode() { return m_isEditorMode; }

    //camera
    void RegisterCamera(CCamera* _Cam, int _Idx);
    void RegisterEditorCamera(CCamera* _Cam) { m_EditorCam = _Cam; }
    void ClearCamera() { m_vecCam.clear(); }

    // debug
    void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_DbgShapeInfo.push_back(_info); }
    void SetDebugPosition(bool _OnOff) { m_DebugPosition = _OnOff; }
    bool IsDebugPosition() { return m_DebugPosition; }

    // 광원
    void RegisterLight2D(CLight2D* _Light2D) { m_vecLight2D.push_back(_Light2D); }

    // post process
    void CopyRenderTargetToPostProcessTarget();

    // Render mode
    void ActiveEditorMode(bool _bActive);

    void CopyRenderTargetToImGuiRenderTexture();

public:
    void init();
    void tick();

private:
    void render_play();
    void render_editor();

    void render_debug();

    // 리소스 바인딩
    void UpdateData();

    // 리소스 클리어
    void Clear();

    // Bloom
    void CreateBloomTex();

};
