#pragma once
#include <Engine\CState.h>
class CCrushDown :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CCrushDown();
    ~CCrushDown();

};

