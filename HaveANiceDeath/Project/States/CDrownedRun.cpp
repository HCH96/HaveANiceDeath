#include "pch.h"
#include "CDrownedRun.h"

CDrownedRun::CDrownedRun()
	:CState(DROWNEDRUN)
{
}

CDrownedRun::~CDrownedRun()
{
}

void CDrownedRun::finaltick()
{
}

void CDrownedRun::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_RUN", true);
}

void CDrownedRun::Exit()
{
}
