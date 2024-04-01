#include "pch.h"
#include "CLDIdleToRun.h"

CLDIdleToRun::CLDIdleToRun()
	:CState(LDIDLETORUN)
{
}

CLDIdleToRun::~CLDIdleToRun()
{
}


void CLDIdleToRun::finaltick()
{
	// �ִϸ��̼��� ���� �Ǿ��ٸ�
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		if (((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D)) || ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A)))
		{
			ChangeState(L"Run");
		}
		else
		{
			ChangeState(L"RunToIdle");
		}
	}
}

void CLDIdleToRun::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_IDLETORUN", true);
}

void CLDIdleToRun::Exit()
{
}

