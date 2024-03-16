#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"

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
}