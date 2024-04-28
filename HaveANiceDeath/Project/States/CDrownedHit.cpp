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

}

void CDrownedHit::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_HIT", true);

}

void CDrownedHit::Exit()
{
}
