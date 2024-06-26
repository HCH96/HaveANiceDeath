#include "pch.h"
#include "CLevelMgr.h"

#include "CDevice.h"

#include "CAssetMgr.h"
#include "CTaskMgr.h"
#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLayer.h"


CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}

void CLevelMgr::init()
{
	// TO DO: 충돌 설정 해줘야 됨


	//CLevel* pLevel = CLevelSaveLoad::LoadLevel(L"level\\temp.lv");
	//CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);
}

void CLevelMgr::ChangeLevel(CLevel* _NextLevel, LEVEL_STATE _NextLevelStartState)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVEL;
	task.Param_1 = (DWORD_PTR)_NextLevel;
	task.Param_2 = (DWORD_PTR)_NextLevelStartState;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevelMgr::ChangeLevelState(LEVEL_STATE _State)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVELSTATE;
	task.Param_1 = (DWORD_PTR)m_CurLevel;
	task.Param_2 = (DWORD_PTR)_State;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevelMgr::ChangeLevel_Task(CLevel* _NextLevel, LEVEL_STATE _NextLevelState)
{
	assert(!(m_CurLevel == _NextLevel));

	if (nullptr != m_CurLevel)
		delete m_CurLevel;

	m_CurLevel = _NextLevel;

	if (nullptr != m_CurLevel)
		m_CurLevel->ChangeState(_NextLevelState);
}


void CLevelMgr::tick()
{
	if (nullptr == m_CurLevel)
		return;

	// 이전 프레임에 등록된 오브젝트들 clear
	m_CurLevel->clear();

	// 레벨이 Play 상태일 경우에만 tick() 호출
	if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
	{
		m_CurLevel->tick();
	}

	m_CurLevel->finaltick();

	// 충돌 처리
	CCollisionMgr::GetInst()->tick();
}