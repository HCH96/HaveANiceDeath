#pragma once
#include "UI.h"


class MenuUI :
    public UI
{
public:
    virtual void render() override;
    virtual void render_update() override;

public:
    void Tool();

private:
    void File();
    void Level();
    void GameObject();
    void Asset();


public:
    MenuUI();
    ~MenuUI();
};

