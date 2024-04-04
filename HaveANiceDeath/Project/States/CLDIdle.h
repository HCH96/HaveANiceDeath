#pragma once

#include <Engine\CState.h>

class CLDIdle :
    public CState
{

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDIdle();
    ~CLDIdle();
};

