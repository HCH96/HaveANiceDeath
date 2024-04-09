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
	GetOwnerObj()->Movement()->SetVelocityX(0.f);

	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();

	if ((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D))
	{
		if (pScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"IdleToRun");
		}
	}

	if ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A))
	{
		if (pScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"IdleToRun");
		}
	}

	
	if (KEY_TAP(KEY::LSHIFT) && !(pScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}


	if (KEY_TAP(KEY::LBTN))
	{
		ChangeState(L"ComboMove01");
	}

	if (KEY_TAP(KEY::LBTN) && KEY_PRESSED(KEY::W))
	{
		ChangeState(L"ComboUp");
	}
	else if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"JumpStart");
	}


}

void CLDIdle::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_IDLE", true);
}

void CLDIdle::Exit()
{
}