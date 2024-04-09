#include "pch.h"
#include "CComboUp.h"

#include <Engine/CMovement.h>
#include <Engine/CTransform.h>

#include <Scripts/CLDScript.h>

CComboUp::CComboUp()
	: CState(COMBOUP)
{
}

CComboUp::~CComboUp()
{
}

void CComboUp::finaltick()
{
	CLDScript* OwnerSciprt = GetOwnerObj()->GetScript<CLDScript>();
	if (OwnerSciprt->IsDownCollision())
	{
		m_IsDown = true;
	}


	float CurY = GetOwnerObj()->Transform()->GetWorldPos().y;

	float MoveDistY = CurY - m_StartPos;

	if (MoveDistY > 400.f || m_IsDown)
	{
		GetOwnerObj()->Movement()->SetVelocityY(0.f);
	}
	else
	{
		GetOwnerObj()->Movement()->SetVelocityY(5000.f);
	}

	GetOwnerObj()->Movement()->SetVelocityX(0.f);


	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"JumpFall");
	}

	if (KEY_TAP(KEY::LBTN))
	{
		OwnerSciprt->PlayComboStand();
	}

	if (GetOwnerObj()->Movement()->IsGround())
	{
		ChangeState(L"JumpLanding");
	}
}

void CComboUp::Enter()
{
	m_IsDown = false;

	m_StartPos = GetOwnerObj()->Transform()->GetWorldPos().y;

	GetOwnerObj()->Animator2D()->Play(L"LD_COMBOUP", false);
	GetOwnerObj()->Movement()->SetGround(false);
	GetOwnerObj()->Movement()->SetVelocityY(5000.f);

	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);
}

void CComboUp::Exit()
{
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 0);
}

