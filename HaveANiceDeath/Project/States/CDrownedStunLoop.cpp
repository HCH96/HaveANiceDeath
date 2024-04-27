#include "pch.h"
#include "CDrownedStunLoop.h"

#include <Engine/CTimeMgr.h>

CDrownedStunLoop::CDrownedStunLoop()
	:CState(DROWNEDSTUNLOOP)
	, m_Duration(2.f)
{
}

CDrownedStunLoop::~CDrownedStunLoop()
{
}

void CDrownedStunLoop::finaltick()
{
	m_Acc += DT;

	if (m_Acc > m_Duration)
	{
		ChangeState(L"StunEnd");
	}
}

void CDrownedStunLoop::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_STUNLOOP", true);

	m_Acc = 0.f;
}

void CDrownedStunLoop::Exit()
{
}
