#pragma once
#include <Engine/CState.h>
class CDrownedRun :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedRun();
    ~CDrownedRun();
};

