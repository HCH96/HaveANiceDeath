#include "pch.h"
#include "CLDRunToIdle.h"

#include <Scripts\CLDScript.h>

CLDRunToIdle::CLDRunToIdle()
	:CState(LDRUNTOIDLE)
{
}

CLDRunToIdle::~CLDRunToIdle()
{
}


void CLDRunToIdle::finaltick()
{
	GetOwnerObj()->Movement()->SetVelocityX(0.f);

	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();

	if (((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D)) || ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A)))
	{
		if (pScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"Run");
		}
	}


	// �ִϸ��̼��� ���� �Ǿ��ٸ�
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}
}

void CLDRunToIdle::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_RUNTOIDLE", true);
}

void CLDRunToIdle::Exit()
{
}
