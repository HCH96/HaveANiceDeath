#pragma once

#include <Engine/CState.h>

class CDrownedAttack01 :
    public CState
{
private:
    int m_PrevFrame;
    int m_CurFrame;


public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedAttack01();
    ~CDrownedAttack01();

};

