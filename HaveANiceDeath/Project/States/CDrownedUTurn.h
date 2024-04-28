#pragma once
#include <Engine/CState.h>
class CDrownedUTurn :
    public CState
{

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedUTurn();
    ~CDrownedUTurn();
};

