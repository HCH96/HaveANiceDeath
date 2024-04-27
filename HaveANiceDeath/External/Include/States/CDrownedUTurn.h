#pragma once
#include <Engine/CState.h>
class CDrownedUTurn :
    public CState
{
private:
    int m_StartDir;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedUTurn();
    ~CDrownedUTurn();
};

