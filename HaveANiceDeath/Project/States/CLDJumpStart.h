#pragma once

#include <Engine\CState.h>

class CLDJumpStart :
    public CState
{
private:
    float m_Acc;


public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDJumpStart();
    ~CLDJumpStart();

};

