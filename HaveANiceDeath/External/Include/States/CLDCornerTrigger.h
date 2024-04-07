#pragma once
#include <Engine\CState.h>
class CLDCornerTrigger :
    public CState
{


public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDCornerTrigger();
    ~CLDCornerTrigger();


};

