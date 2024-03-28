#pragma once
#include "ComponentUI.h"

class UIMovement :
    public ComponentUI
{
public:
    virtual void render_update() override;

public:
    UIMovement();
    ~UIMovement();
};

