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
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	
	GetOwnerObj()->Movement()->SetVelocityX(200.f * (int)pScript->GetDir());

	if ((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D))
	{
		GetOwnerObj()->Movement()->SetVelocityX(-900.f);
	}

	if ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A))
	{
		GetOwnerObj()->Movement()->SetVelocityX(900.f);
	}

	// 애니메이션이 종료 되었다면
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		if (((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D))||((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A)))
		{
			ChangeState(L"IdleToRun");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"JumpStart");
	}
}

void CLDIdleUTurn::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_IDLEUTURN", true);
}

void CLDIdleUTurn::Exit()
{
}

