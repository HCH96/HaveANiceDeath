#include "pch.h"
#include "CDrownedUTurn.h"

#include <Scripts/CDrownedScript.h>

CDrownedUTurn::CDrownedUTurn()
	:CState(DROWNEDUTURN)
{
}

CDrownedUTurn::~CDrownedUTurn()
{
}

void CDrownedUTurn::finaltick()
{
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}
}

void CDrownedUTurn::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_UTURN", true);
}

void CDrownedUTurn::Exit()
{
	int PrevDir = (int)GetOwnerObj()->GetScript<CDrownedScript>()->GetPrevInfo().Dir;

	GetOwnerObj()->GetScript<CDrownedScript>()->GetUnitInfo().Dir = (ANIM_DIR)-PrevDir;
}
