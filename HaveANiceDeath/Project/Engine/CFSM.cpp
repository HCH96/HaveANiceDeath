#include "pch.h"
#include "CFSM.h"

#include <States\CStateMgr.h>

#include "CBlackboard.h"

#include "CState.h"


CFSM::CFSM(bool _bEngine)
	: CAsset(ASSET_TYPE::FSM, _bEngine)
	, m_Master(nullptr)
	, m_StateMachine(nullptr)
{
	m_Blackboard = new CBlackboard;

}

CFSM::~CFSM()
{
	if (!m_Master)
	{
		Delete_Map(m_mapState);

		delete m_Blackboard;
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

CState* CFSM::FindState(const wstring& _StateName)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_StateName);

	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void CFSM::SetState(const wstring& _strState)
{
	m_CurState = FindState(_strState);
}

CFSM* CFSM::GetFSMIstance()
{
	CFSM* pFSMInst = new CFSM;

	pFSMInst->m_mapState = m_mapState;
	pFSMInst->m_Master = this;
	pFSMInst->m_Blackboard = m_Blackboard;
	pFSMInst->m_CurState = nullptr;

	return pFSMInst;
}

void CFSM::ChangeState(const wstring& _strStateName)
{
	if (nullptr != m_CurState)
		m_CurState->Exit();

	m_CurState = FindState(_strStateName);

	assert(m_CurState);

	m_CurState->Enter();
}

int CFSM::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	// State�� ���� ����
	size_t StateCount = m_mapState.size();
	fwrite(&StateCount, sizeof(size_t), 1, pFile);

	// State ����
	map<wstring, CState*>::iterator iter = m_mapState.begin();

	for (; iter != m_mapState.end(); ++iter)
	{
		// State Key ����
		SaveWString(iter->first, pFile);

		// State Type ����
		UINT StateType = iter->second->GetStateType();
		fwrite(&StateType, sizeof(UINT), 1, pFile);

		// State ����
		SaveWString(CStateMgr::GetStateName(iter->second), pFile);
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

	// State ���� �ε�
	size_t StateCount = 0;
	fread(&StateCount, sizeof(size_t), 1, pFile);

	// ������Ʈ �ε�
	for (size_t i = 0; i < StateCount; ++i)
	{
		// ������Ʈ Ű �ε�
		wstring StateKey;
		LoadWString(StateKey, pFile);

		// ������Ʈ Ÿ�� �ε�
		UINT StateType;
		fread(&StateType, sizeof(UINT), 1, pFile);

		// ������Ʈ ����
		CState* pState = CStateMgr::GetState(StateType);
		pState->LoadFromFile(pFile);

		pState->m_FSM = this;
		m_mapState.insert(make_pair(StateKey, pState));
	}

	fclose(pFile);

	return S_OK;
}
