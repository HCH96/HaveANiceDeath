#pragma once

#include <Engine/CState.h>


class CDrownedAppear :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedAppear();
    ~CDrownedAppear();
};

