#pragma once
#include <Engine/CState.h>
class CDrownedHit :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedHit();
    ~CDrownedHit();
};

