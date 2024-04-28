#pragma once
#include <Engine/CState.h>
class CDrownedRun :
    public CState
{
private:
    CGameObject* m_Target;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedRun();
    ~CDrownedRun();
};

