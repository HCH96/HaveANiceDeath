#pragma once

#include <Engine\CState.h>

class CLDJumpStart :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDJumpStart();
    ~CLDJumpStart();

};

