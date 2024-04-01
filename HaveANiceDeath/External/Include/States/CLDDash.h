#pragma once
#include <Engine\CState.h>
class CLDDash :
    public CState
{

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDDash();
    ~CLDDash();
};

