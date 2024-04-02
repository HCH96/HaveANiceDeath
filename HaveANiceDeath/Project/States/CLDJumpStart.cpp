#include "pch.h"
#include "CLDJumpStart.h"

#include <Engine\CMovement.h>

CLDJumpStart::CLDJumpStart()
	:CState(LDJUMPSTART)
{
}

CLDJumpStart::~CLDJumpStart()
{
}


void CLDJumpStart::finaltick()
{
	ChangeState(L"Idle");
}

void CLDJumpStart::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_IDLE", true);
	GetOwnerObj()->Movement()->SetVelocityY(100.f);
	
}

void CLDJumpStart::Exit()
{
}

