#include "pch.h"
#include "CDrownedHit.h"



CDrownedHit::CDrownedHit()
	:CState(DROWNEDHIT)
{
}

CDrownedHit::~CDrownedHit()
{
}

void CDrownedHit::finaltick()
{
	if(GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}

}

void CDrownedHit::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_HIT", true);
}

void CDrownedHit::Exit()
{
}
