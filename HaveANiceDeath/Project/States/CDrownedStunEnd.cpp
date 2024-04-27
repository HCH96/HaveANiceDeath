#include "pch.h"
#include "CDrownedStunEnd.h"

CDrownedStunEnd::CDrownedStunEnd()
	:CState(DROWNEDSTUNEND)
{
}

CDrownedStunEnd::~CDrownedStunEnd()
{
}

void CDrownedStunEnd::finaltick()
{
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}
}

void CDrownedStunEnd::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_STUNEND", true);
}

void CDrownedStunEnd::Exit()
{
}
