#pragma once
#include <Engine/CState.h>
class CDrownedStunLoop :
    public CState
{
private:
    float m_Acc;
    float m_Duration;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedStunLoop();
    ~CDrownedStunLoop();
};

