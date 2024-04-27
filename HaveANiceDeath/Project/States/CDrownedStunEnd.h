#pragma once
#include <Engine/CState.h>
class CDrownedStunEnd :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedStunEnd();
    ~CDrownedStunEnd();
};

