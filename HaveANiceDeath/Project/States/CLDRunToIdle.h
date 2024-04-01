#pragma once
#include <Engine\CState.h>
class CLDRunToIdle :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDRunToIdle();
    ~CLDRunToIdle();
};

