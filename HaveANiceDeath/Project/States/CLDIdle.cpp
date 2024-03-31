#include "pch.h"
#include "CLDIdle.h"

#include <Scripts\CLDScript.h>

CLDIdle::CLDIdle()
	: CState(LDIDLE)
{
}

CLDIdle::~CLDIdle()
{
}

void CLDIdle::finaltick()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	if (pScript->IsDirChanged())
	{
		ChangeState(L"IdleUTurn");
	}

}

void CLDIdle::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_IDLE", true);
}

void CLDIdle::Exit()
{
}