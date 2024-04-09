#pragma once

#include <Engine/CState.h>

class CComboStand03 :
    public CState
{
private:
    ANIM_DIR m_Dir;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CComboStand03();
    ~CComboStand03();

};

