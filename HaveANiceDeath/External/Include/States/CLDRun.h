#pragma once
#include <Engine\CState.h>

class CLDRun :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDRun();
    ~CLDRun();

};

