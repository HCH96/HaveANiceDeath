#include "pch.h"
#include "CDrownedAppear.h"

CDrownedAppear::CDrownedAppear()
	: CState(DROWNEDAPPEAR)
{
}

CDrownedAppear::~CDrownedAppear()
{
}

void CDrownedAppear::finaltick()
{
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}
}

void CDrownedAppear::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_APPEAR", true);
}

void CDrownedAppear::Exit()
{
}


