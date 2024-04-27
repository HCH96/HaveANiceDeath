#include "pch.h"
#include "CDrownedSurprised.h"

CDrownedSurprised::CDrownedSurprised()
	:CState(DROWNEDSURPRISED)
{
}

CDrownedSurprised::~CDrownedSurprised()
{
}

void CDrownedSurprised::finaltick()
{
}

void CDrownedSurprised::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_SUPRISED", true);
}

void CDrownedSurprised::Exit()
{
}
