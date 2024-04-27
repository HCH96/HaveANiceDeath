#pragma once
#include <Engine/CState.h>
class CDrownedStunStart :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedStunStart();
    ~CDrownedStunStart();
};

