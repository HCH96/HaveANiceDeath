#pragma once
#include "UI.h"

class Inspector;

class UIGamePlayPannel :
    public UI
{
private:
    Inspector*  m_Inspector;
    ImVec2              m_BtnSize;
    float               m_ShowLayerWidth;
    Ptr<CTexture>       m_PlayIcon[2];
    Ptr<CTexture>       m_PauseIcon[2];
    Ptr<CTexture>       m_StopIcon;

public:
    virtual void begin() override;
    virtual void render_update() override;

public:
    UIGamePlayPannel();
    ~UIGamePlayPannel();
};

