#include "pch.h"
#include "CLDIdleUTurn.h"

#include <Scripts\CLDScript.h>

CLDIdleUTurn::CLDIdleUTurn()
	:CState(LDIDLEUTURN)
{
}

CLDIdleUTurn::~CLDIdleUTurn()
{
}


void CLDIdleUTurn::finaltick()
{
	// 애니메이션이 종료 되었다면
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}
}

void CLDIdleUTurn::Enter()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	pScript->SetLock(true);

	GetOwnerObj()->Animator2D()->Play(L"LD_IDLEUTURN", true);
}

void CLDIdleUTurn::Exit()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	pScript->SetLock(false);
}

