#pragma once

#include <Engine\CState.h>

class CLDIdleUTurn :
    public CState
{
private:


public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDIdleUTurn();
    ~CLDIdleUTurn();
};

