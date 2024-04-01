#pragma once
#include <Engine\CState.h>
class CLDIdleToRun :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDIdleToRun();
    ~CLDIdleToRun();

};

