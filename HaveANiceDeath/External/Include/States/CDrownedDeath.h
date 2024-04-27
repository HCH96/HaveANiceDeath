#pragma once
#include <Engine/CState.h>
class CDrownedDeath :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedDeath();
    ~CDrownedDeath();
};

