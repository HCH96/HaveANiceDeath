#pragma once
#include <Engine/CState.h>


class CComboMove03 :
    public CState
{
private:
    bool IsClicked;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CComboMove03();
    ~CComboMove03();


};

