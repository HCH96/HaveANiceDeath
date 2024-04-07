#pragma once

#include <Engine/CState.h>

class CComboMove04 :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CComboMove04();
    ~CComboMove04();
};

