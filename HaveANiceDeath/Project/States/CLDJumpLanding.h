#pragma once
#include <Engine\CState.h>
class CLDJumpLanding :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDJumpLanding();
    ~CLDJumpLanding();

};

