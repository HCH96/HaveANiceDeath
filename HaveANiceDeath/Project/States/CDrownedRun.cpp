#include "pch.h"
#include "CDrownedRun.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include <Scripts/CUnitScript.h>

CDrownedRun::CDrownedRun()
	:CState(DROWNEDRUN)
{
}

CDrownedRun::~CDrownedRun()
{
}

void CDrownedRun::finaltick()
{
	ANIM_DIR m_Dir = GetOwnerObj()->GetScript<CUnitScript>()->GetDir();

	if (m_Dir == ANIM_DIR::LEFT)
	{
		GetOwnerObj()->Movement()->SetVelocityX(-150.f);
	}
	else
	{
		GetOwnerObj()->Movement()->SetVelocityX(150.f);
	}

	Vec3 CurPos = GetOwnerObj()->Transform()->GetRelativePos();
	Vec3 TargetPos = m_Target->Transform()->GetRelativePos();
	TargetPos.z = CurPos.z;

	Vec3 Dir = TargetPos - CurPos;

	// 다른 방향에 있을경우
	if (Dir.x * (int)m_Dir < 0)
	{
		ChangeState(L"Idle");
	}

	float Dist = Dir.Length();

	if (Dist < 200.f)
	{
		if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
		{
			ChangeState(L"Idle");
		}
	}

}

void CDrownedRun::Enter()
{
	CLayer* PlayerLayer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(L"Player");
	m_Target = PlayerLayer->GetObjectByName(L"LD");

	GetOwnerObj()->Animator2D()->Play(L"DROWNED_RUN", true);
}

void CDrownedRun::Exit()
{
	GetOwnerObj()->Movement()->SetVelocityX(0.f);



	CMovement* Test = GetOwnerObj()->Movement();

}
