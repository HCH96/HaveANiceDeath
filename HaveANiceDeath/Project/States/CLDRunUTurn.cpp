#include "pch.h"
#include "CLDRunUTurn.h"

#include <Scripts\CLDScript.h>

CLDRunUTurn::CLDRunUTurn()
	:CState(LDRUNUTURN)
{
}

CLDRunUTurn::~CLDRunUTurn()
{
}

void CLDRunUTurn::finaltick()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();

	if (pScript->IsDirChanged())
	{
		ChangeState(L"Run");
	}

	// 애니메이션이 종료 되었다면
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		if (KEY_TAPORPRESS(KEY::A) || KEY_TAPORPRESS(KEY::D))
		{
			ChangeState(L"Run");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}

	if (KEY_TAP(KEY::LSHIFT) && !(pScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"JumpStart");
	}

	if (KEY_TAP(KEY::LBTN))
	{
		ChangeState(L"ComboMove01");
	}

}

void CLDRunUTurn::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_RUNUTURN", true);
}

void CLDRunUTurn::Exit()
{
}
