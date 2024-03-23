#pragma once
#include "ComponentUI.h"
class Animator2DUI :
    public ComponentUI
{
    virtual void render_update() override;

private:
    void AddAnimation();
    void DeleteAnimation(const wstring& _strAnimationName);


public:
    Animator2DUI();
    ~Animator2DUI();
};

