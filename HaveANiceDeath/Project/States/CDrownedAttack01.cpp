#include "pch.h"
#include "CDrownedAttack01.h"

#include <Engine/CAnim.h>

#include <Scripts/CMonsterHitBoxScript.h>

CDrownedAttack01::CDrownedAttack01()
	:CState(DROWNEDATTACK01)
{
}

CDrownedAttack01::~CDrownedAttack01()
{
}

void CDrownedAttack01::finaltick()
{
	m_CurFrame = GetOwnerObj()->Animator2D()->GetCurAnimInst()->GetCurAnimIdx();

	if (m_PrevFrame == 14 && m_CurFrame == 15)
	{
		CMonsterHitBoxScript* HitBoxScript = GetOwnerObj()->GetChild(L"Drowned_Att")->GetScript<CMonsterHitBoxScript>();
		if(nullptr != HitBoxScript)
			HitBoxScript->Activate();
	}

	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}

	m_PrevFrame = m_CurFrame;
}

void CDrownedAttack01::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_ATTACK01", true);

	m_PrevFrame = 0;
	m_CurFrame = 0;
}

void CDrownedAttack01::Exit()
{
}
