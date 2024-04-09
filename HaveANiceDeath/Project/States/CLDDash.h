#pragma once
#include <Engine\CState.h>
class CLDDash :
    public CState
{
private:
    float m_StartPos;


public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CLDDash();
    ~CLDDash();
};

