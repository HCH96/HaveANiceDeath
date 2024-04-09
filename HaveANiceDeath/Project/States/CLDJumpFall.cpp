#include "pch.h"
#include "CLDJumpFall.h"

#include <Scripts/CLDScript.h>
#include <Engine\CMovement.h>

CLDJumpFall::CLDJumpFall()
	:CState(LDJUMPFALL)
{
}

CLDJumpFall::~CLDJumpFall()
{
}


void CLDJumpFall::finaltick()
{
	CLDScript* LDScript = GetOwnerObj()->GetScript<CLDScript>();

	GetOwnerObj()->Movement()->SetVelocityX(0.f);

	if ((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D))
	{
		GetOwnerObj()->Movement()->SetVelocityX(-900.f);
	}

	if ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A))
	{
		GetOwnerObj()->Movement()->SetVelocityX(900.f);
	}

	if (KEY_TAP(KEY::LBTN) && KEY_PRESSED(KEY::W) && false == LDScript->IsComboUp())
	{
		ChangeState(L"ComboUp");
	}
	else if (KEY_TAP(KEY::LBTN))
	{
		LDScript->PlayComboStand();
	}

	if (KEY_TAP(KEY::LSHIFT) && !(LDScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}


	if (GetOwnerObj()->Movement()->IsGround())
	{
		ChangeState(L"JumpLanding");
	}

}

void CLDJumpFall::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_JUMPFALL", true);
}

void CLDJumpFall::Exit()
{
}

