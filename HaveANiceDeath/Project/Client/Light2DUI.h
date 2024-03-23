#pragma once
#include "ComponentUI.h"

class Light2DUI :
    public ComponentUI
{
private:
    ImVec2 m_vSize;

public:
    virtual void render_update() override;
public:
    Light2DUI();
    ~Light2DUI();
};

