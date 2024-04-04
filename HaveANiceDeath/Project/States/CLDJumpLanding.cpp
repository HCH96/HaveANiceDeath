#include "pch.h"
#include "CLDJumpLanding.h"

CLDJumpLanding::CLDJumpLanding()
	:CState(LDJUMPLANDING)
{
}

CLDJumpLanding::~CLDJumpLanding()
{
}


void CLDJumpLanding::finaltick()
{
	GetOwnerObj()->Movement()->SetVelocityX(0.f);

	if ((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D))
	{
		GetOwnerObj()->Movement()->SetVelocityX(-900.f);
	}

	if ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A))
	{
		GetOwnerObj()->Movement()->SetVelocityX(900.f);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"JumpStart");
	}

	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}
}

void CLDJumpLanding::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_JUMPLANDING", true);
}

void CLDJumpLanding::Exit()
{
}

