#include "pch.h"
#include "CFSM.h"

#include <States\CStateMgr.h>

#include "CTaskMgr.h"
#include "CStateMachine.h"

#include "CBlackboard.h"

#include "CState.h"


CFSM::CFSM(CFSM* _Origin, bool _bEngine)
	: CAsset(ASSET_TYPE::FSM, _bEngine)
	, m_Master(_Origin)
	, m_Blackboard(nullptr)
	, m_StateMachine(nullptr)
	, m_CurState(nullptr)
{
	// case: original FSM
	if (!m_Master)
		m_Blackboard = new CBlackboard();
	else
		m_Blackboard = _Origin->m_Blackboard;


}

CFSM::~CFSM()
{
	// case: original FSM
	if (!m_Master)
	{
		Delete_Map(m_mapState);
		if (m_Blackboard)
		{
			delete m_Blackboard;
		}
	}
}
void CFSM::finaltick()
{
	if (m_CurState)
	{
		m_CurState->m_FSM = this;
		m_CurState->finaltick();
	}
}

void CFSM::AddState(const wstring& _StateName, CState* _State)
{
	assert(!(FindState(_StateName)));

	_State->m_FSM = this;
	m_mapState.insert(make_pair(_StateName, _State));
}

void CFSM::DeleteState(const wstring& _StateKey)
{
	CState* pState = FindState(_StateKey);

	if (pState == nullptr)
	{
		MessageBoxA(nullptr, "해당 키를 가진 스테이트가 없습니다.", "Delete State Failed", MB_OK);
		return;
	}

	delete pState;
	m_mapState.erase(_StateKey);
}

CState* CFSM::FindState(const wstring& _StateName)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_StateName);

	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}


void CFSM::AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _pData)
{
	m_Blackboard->AddBlackboardData(_strKey, _Type, _pData);
}

void* CFSM::GetBlackboardData(const wstring& _strKey)
{
	return m_Blackboard->GetBlackboardData(_strKey);
}

CFSM* CFSM::GetFSMIstance()
{
	CFSM* pFSMInst = new CFSM(this, true);

	pFSMInst->m_mapState = m_mapState;

	return pFSMInst;

}

void CFSM::ChangeState(const wstring& _strStateName)
{

	// 1. next state check
	CState* pNextState = FindState(_strStateName);
	assert(pNextState);

	// 현재 스테이트와 같다면 리턴
	if (pNextState == m_CurState)
		return;

	// 2. adjust task to taskMgr
	// Param1: Parent Object    |   Param2: Next State
	tTask pTask = {};
	pTask.Type = TASK_TYPE::CHANGE_STATE;
	pTask.Param_1 = (UINT_PTR)m_StateMachine->GetOwner();
	pTask.Param_2 = (UINT_PTR)pNextState;

	CTaskMgr::GetInst()->AddTask(pTask);
}

void CFSM::ChangeState_proc(CState* _pNextState)
{
	if (m_CurState)
	{
		m_CurState->m_FSM = this;
		m_CurState->Exit();
	}

	m_PrevState = m_CurState;
	m_CurState = _pNextState;
	m_CurState->m_FSM = this;
	m_CurState->Enter();

}

int CFSM::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	// State의 개수 저장
	size_t StateCount = m_mapState.size();
	fwrite(&StateCount, sizeof(size_t), 1, pFile);

	// State 저장
	map<wstring, CState*>::iterator iter = m_mapState.begin();

	for (; iter != m_mapState.end(); ++iter)
	{
		// State Key 저장
		SaveWString(iter->first, pFile);

		// State Name 저장
		wstring StrName = CStateMgr::GetStateName(iter->second);

		SaveWString(StrName,pFile);

		iter->second->SaveToFile(pFile);
	}

	fclose(pFile);

	return S_OK;
}

int CFSM::Load(const wstring& _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
		return E_FAIL;

	// State 개수 로드
	size_t StateCount = 0;
	fread(&StateCount, sizeof(size_t), 1, pFile);

	// 스테이트 로드
	for (size_t i = 0; i < StateCount; ++i)
	{
		// 스테이트 키 로드
		wstring StateKey;
		LoadWString(StateKey, pFile);

		// 스테이트 Name 로드
		wstring StateName;
		LoadWString(StateName, pFile);

		// 스테이트 생성
		CState* pState = CStateMgr::GetState(StateName);
		pState->LoadFromFile(pFile);

		pState->m_FSM = this;
		m_mapState.insert(make_pair(StateKey, pState));
	}

	fclose(pFile);

	return S_OK;
}
