#include "pch.h"
#include "CDrownedIdle.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

#include <Engine/CTransform.h>

#include <Scripts/CDrownedScript.h>

CDrownedIdle::CDrownedIdle()
	:CState(DROWNEDIDLE)
	, m_Target(nullptr)
	, m_DetectionRange(800.f)
	, m_AttRange(200.f)
{
}

CDrownedIdle::~CDrownedIdle()
{
}

void CDrownedIdle::finaltick()
{
	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		Vec3 CurPos = GetOwnerObj()->Transform()->GetRelativePos();
		Vec3 TargetPos = m_Target->Transform()->GetRelativePos();
		TargetPos.z = CurPos.z;

		Vec3 Dir = TargetPos - CurPos;

		float Dist = Dir.Length();

		if (Dist < m_AttRange)
		{	
			ANIM_DIR CurDir = GetOwnerObj()->GetScript<CDrownedScript>()->GetUnitInfo().Dir;
			//  같은 방향
			if (Dir.x * (int)CurDir > 0)
			{
				ChangeState(L"Attack01");
			}
			else
			{
				ChangeState(L"UTurn");
			}

			return;
		}


		if (Dist < m_DetectionRange)
		{
			ANIM_DIR CurDir = GetOwnerObj()->GetScript<CDrownedScript>()->GetUnitInfo().Dir;

			//  같은 방향
			if (Dir.x * (int)CurDir > 0)
			{
				ChangeState(L"Run");
			}
			else
			{
				ChangeState(L"UTurn");
			}
		}
	}

}

void CDrownedIdle::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"DROWNED_IDLE", true);

	CLayer* PlayerLayer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(L"Player");
	m_Target = PlayerLayer->GetObjectByName(L"LD");

}

void CDrownedIdle::Exit()
{
}
