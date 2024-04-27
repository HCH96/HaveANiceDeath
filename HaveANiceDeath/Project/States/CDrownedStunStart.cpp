#include "pch.h"
#include "CDrownedStunStart.h"

CDrownedStunStart::CDrownedStunStart()
	:CState(DROWNEDSTUNSTART)
{
}

CDrownedStunStart::~CDrownedStunStart()
{
}

void CDrownedStunStart::finaltick()
{
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"StunLoop");
	}
}

void CDrownedStunStart::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_STUNSTART", true);
}

void CDrownedStunStart::Exit()
{
}
