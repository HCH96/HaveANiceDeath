#pragma once
#include <Engine/CState.h>


class CComboMove01 :
    public CState
{
private:
    bool IsClicked;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CComboMove01();
    ~CComboMove01();


};

