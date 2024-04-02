#include "pch.h"
#include "CLDRun.h"

#include <Scripts\CLDScript.h>

CLDRun::CLDRun()
	: CState(LDRUN)
{
}

CLDRun::~CLDRun()
{
}


void CLDRun::finaltick()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();

	if ((KEY_NONE(KEY::A) || KEY_RELEASED(KEY::A)) && (KEY_NONE(KEY::D) || KEY_RELEASED(KEY::D)))
	{
		ChangeState(L"RunToIdle");
	}

	if (pScript->IsDirChanged())
	{
		ChangeState(L"RunUTurn");
	}

}

void CLDRun::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"LD_RUN", true);
}

void CLDRun::Exit()
{
}
