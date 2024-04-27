#pragma once
#include <Engine/CState.h>

class CGameObject;

class CDrownedIdle :
    public CState
{
private:
    CGameObject*        m_Target;
    float               m_DetectionRange;
    float               m_AttRange;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();


public:
    CDrownedIdle();
    ~CDrownedIdle();
};

