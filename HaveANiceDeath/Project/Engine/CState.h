#pragma once
#include "CEntity.h"

class CFSM;
class CStateMachine;

class CState :
    public CEntity
{
private:
    CFSM* m_FSM;

public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

protected:
    CFSM* GetFSM() { return m_FSM; }
    void* GetBlackboardData(const wstring& _strKey);

    void ChangeState(const wstring& _strStateName);


public:
    CLONE_DISABLE(CState);

    CState();
    ~CState();

    friend class CFSM;
};
