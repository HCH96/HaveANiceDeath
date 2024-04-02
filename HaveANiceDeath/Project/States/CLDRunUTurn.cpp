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

	// �ִϸ��̼��� ���� �Ǿ��ٸ�
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

}

void CLDRunUTurn::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_RUNUTURN", true);
}

void CLDRunUTurn::Exit()
{
}