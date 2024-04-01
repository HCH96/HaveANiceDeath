#pragma once
#include <Engine\CState.h>
class CLDRunUTurn :
    public CState
{

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDRunUTurn();
    ~CLDRunUTurn();
};

