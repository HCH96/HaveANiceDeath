#pragma once
#include <Engine/CState.h>


class CComboMove02 :
    public CState
{
private:
    bool IsClicked;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CComboMove02();
    ~CComboMove02();
};

