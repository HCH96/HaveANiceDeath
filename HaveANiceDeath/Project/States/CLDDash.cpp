#include "pch.h"
#include "CLDDash.h"

#include <Engine/CMovement.h>
#include <Engine/CTransform.h>
#include <Engine/CAnim.h>

#include <Scripts/CLDScript.h>

CLDDash::CLDDash()
	:CState(LDDASH)
{
}

CLDDash::~CLDDash()
{
}


void CLDDash::finaltick()
{
	GetOwnerObj()->Movement()->SetVelocityY(0.f);

	int CurIdx = GetOwnerObj()->Animator2D()->GetCurAnimInst()->GetCurAnimIdx();

	if (CurIdx > 1)
	{
		if (KEY_TAP(KEY::LBTN))
			m_IsTapLBTN = true;
	}

	if(CurIdx == 4)
		GetOwnerObj()->Movement()->SetVelocityX(0.f);

	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		if (GetOwnerObj()->Movement()->IsGround())
		{
			if (m_IsTapLBTN)
			{
				ChangeState(L"ComboMove01");
			}
			else if (m_IsTapLBTN && KEY_PRESSED(KEY::W))
			{
				ChangeState(L"ComboUp");
			}
			else if (KEY_TAP(KEY::SPACE)|| KEY_PRESSED(KEY::SPACE))
			{
				ChangeState(L"JumpStart");
			}
			else
			{
				ChangeState(L"Idle");
			}
		}
		else
		{
			ChangeState(L"JumpFall");
		}
	}





}

void CLDDash::Enter()
{
	CLDScript* LDScript = GetOwnerObj()->GetScript<CLDScript>();
	LDScript->SetDash(true);
	LDScript->SetLock(true);

	m_IsTapLBTN = false;

	GetOwnerObj()->Animator2D()->Play(L"LD_DASH", false);

	if (LDScript->GetDir() == ANIM_DIR::LEFT)
	{
		GetOwnerObj()->Movement()->SetVelocityX(-4500.f);
	}
	else
	{
		GetOwnerObj()->Movement()->SetVelocityX(4500.f);
	}

	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);

	m_StartPos = GetOwnerObj()->Transform()->GetCurPos().x;

}

void CLDDash::Exit()
{
	CLDScript* LDScript = GetOwnerObj()->GetScript<CLDScript>();
	LDScript->SetLock(false);

	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 0);
}

