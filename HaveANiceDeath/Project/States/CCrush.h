#pragma once
#include <Engine\CState.h>
class CCrush :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CCrush();
    ~CCrush();

};

