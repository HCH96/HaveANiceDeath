#pragma once
#include "CRenderComponent.h"

class CMeshRender :
    public CRenderComponent
{
public:
    virtual void finaltick() override;
    virtual void render() override;
    virtual void UpdateData() override;

public:
    CLONE(CMeshRender);
    CMeshRender();
    ~CMeshRender();
};
