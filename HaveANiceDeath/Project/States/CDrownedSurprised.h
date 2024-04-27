#pragma once
#include <Engine/CState.h>
class CDrownedSurprised :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedSurprised();
    ~CDrownedSurprised();
};

