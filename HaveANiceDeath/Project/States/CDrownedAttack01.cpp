#include "pch.h"
#include "CDrownedAttack01.h"

CDrownedAttack01::CDrownedAttack01()
	:CState(DROWNEDATTACK01)
{
}

CDrownedAttack01::~CDrownedAttack01()
{
}

void CDrownedAttack01::finaltick()
{
}

void CDrownedAttack01::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_ATTACK01", true);
}

void CDrownedAttack01::Exit()
{
}
