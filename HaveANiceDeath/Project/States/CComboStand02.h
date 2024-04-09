#pragma once

#include <Engine/CState.h>

class CComboStand02 :
    public CState
{
private:
    ANIM_DIR m_Dir;
    bool m_IsClicked;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CComboStand02();
    ~CComboStand02();

};

