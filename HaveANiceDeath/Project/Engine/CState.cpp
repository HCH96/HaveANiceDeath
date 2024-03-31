#include "pch.h"
#include "CState.h"

#include "CStateMachine.h"
#include "CFSM.h"


CState::CState(UINT _StateType)
	: m_FSM(nullptr)
	, m_StateType(_StateType)
{
}

CState::~CState()
{
}

void* CState::GetBlackboardData(const wstring& _strKey)
{
	CStateMachine* pSM = m_FSM->GetStateMachine();
	return pSM->GetBlackboardData(_strKey);
}

CGameObject* CState::GetOwnerObj()
{
	return m_FSM->GetStateMachine()->GetOwner();;
}

void CState::ChangeState(const wstring& _strStateName)
{
	assert(m_FSM);
	m_FSM->ChangeState(_strStateName);
}
