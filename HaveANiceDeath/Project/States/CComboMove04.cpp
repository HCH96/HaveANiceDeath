#include "pch.h"
#include "CComboMove04.h"

#include <Engine/CMeshRender.h>

#include <Scripts/CLDScript.h>
#include <Scripts/CLDHitBox.h>

CComboMove04::CComboMove04()
	:CState(COMBOMOVE04)
{
}

CComboMove04::~CComboMove04()
{
}


void CComboMove04::finaltick()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();

	int CurIdx = GetOwnerObj()->Animator2D()->GetCurAnimInst()->GetCurAnimIdx();

	if (CurIdx == 7)
	{
		GetOwnerObj()->Movement()->SetVelocityX(0.f);
	}

	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"Idle");
	}
}

void CComboMove04::Enter()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	pScript->SetLock(true);

	if (pScript->GetDir() == ANIM_DIR::LEFT)
	{
		GetOwnerObj()->Movement()->SetVelocityX(-700.f);
	}
	else
	{
		GetOwnerObj()->Movement()->SetVelocityX(700.f);
	}

	CLDHitBox* HitBoxScript = GetOwnerObj()->GetChild(L"LD_Att")->GetScript<CLDHitBox>();
	if (HitBoxScript != nullptr)
	{
		HitBoxScript->On();
	}

	GetOwnerObj()->Animator2D()->Play(L"LD_COMBOMOVE04", false);
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);
}

void CComboMove04::Exit()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	pScript->SetLock(false);

	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 0);
}

