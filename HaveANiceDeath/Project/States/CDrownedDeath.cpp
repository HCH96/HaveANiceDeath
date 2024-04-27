#include "pch.h"
#include "CDrownedDeath.h"

CDrownedDeath::CDrownedDeath()
	:CState(DROWNEDDEATH)
{
}

CDrownedDeath::~CDrownedDeath()
{
}

void CDrownedDeath::finaltick()
{
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		GetOwnerObj()->Destroy();
	}
}

void CDrownedDeath::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_DEATH", false);
}

void CDrownedDeath::Exit()
{
}
