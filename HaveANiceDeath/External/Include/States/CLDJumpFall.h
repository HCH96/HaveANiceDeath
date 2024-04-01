#pragma once
#include <Engine\CState.h>

class CLDJumpFall :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDJumpFall();
    ~CLDJumpFall();

};

