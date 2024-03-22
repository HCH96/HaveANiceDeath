#pragma once
#include "CEntity.h"

class CFSM;
class CStateMachine;

class CState :
    public CEntity
{
private:

    const UINT              m_StateType;
    CFSM*                   m_FSM;

public:
    UINT GetStateType() { return m_StateType; }

public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

protected:
    CFSM* GetFSM() { return m_FSM; }
    void* GetBlackboardData(const wstring& _strKey);

    void ChangeState(const wstring& _strStateName);

    virtual void SaveToFile(FILE* _File) {}
    virtual void LoadFromFile(FILE* _File) {}

public:
    CLONE_DISABLE(CState);

    CState(UINT StateType);
    ~CState();

    friend class CFSM;
};
