#pragma once
#include <Engine/CState.h>

class CComboUp :
    public CState
{
private:
    float m_StartPos;
    bool m_IsDown;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CComboUp();
    ~CComboUp();
};

