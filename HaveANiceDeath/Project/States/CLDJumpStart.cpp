#include "pch.h"
#include "CLDJumpStart.h"

#include <Engine\CMovement.h>
#include <Scripts/CLDScript.h>

CLDJumpStart::CLDJumpStart()
	:CState(LDJUMPSTART)
{
}

CLDJumpStart::~CLDJumpStart()
{
}


void CLDJumpStart::finaltick()
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


	if ((KEY_NONE(KEY::SPACE) || KEY_RELEASED(KEY::SPACE)) && m_Acc > 0.08f)
	{
		Vec3 Vel = GetOwnerObj()->Movement()->GetVelocity();

		GetOwnerObj()->Movement()->SetVelocityY(Vel.y/3.f);
		ChangeState(L"JumpFall");
	}

	if (GetOwnerObj()->Movement()->GetVelocity().y < 0.f)
	{
		ChangeState(L"JumpFall");
	}

	m_Acc += DT;

	if (KEY_TAP(KEY::LBTN))
	{
		LDScript->PlayComboStand();
	}

	if (KEY_TAP(KEY::LBTN) && KEY_PRESSED(KEY::W))
	{
		ChangeState(L"ComboUp");
	}

	if (GetOwnerObj()->Movement()->IsGround())
	{
		ChangeState(L"JumpLanding");
	}

}

void CLDJumpStart::Enter()
{
	m_Acc = 0.f;

	GetOwnerObj()->Animator2D()->Play(L"LD_JUMPSTART", false);
	GetOwnerObj()->Movement()->SetGround(false);
	
	GetOwnerObj()->Movement()->SetVelocityY(2000.f);
}

void CLDJumpStart::Exit()
{


}

