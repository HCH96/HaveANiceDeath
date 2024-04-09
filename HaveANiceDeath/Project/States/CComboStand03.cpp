#include "pch.h"
#include "CComboStand03.h"


#include <Engine/CMovement.h>
#include <Engine/CMeshRender.h>

#include <Scripts/CLDScript.h>
#include <Scripts/CLDHitBox.h>

CComboStand03::CComboStand03()
	: CState(COMBOSTAND03)
{
}

CComboStand03::~CComboStand03()
{
}


void CComboStand03::finaltick()
{
	if (m_Dir == ANIM_DIR::LEFT)
	{
		GetOwnerObj()->Movement()->SetVelocityX(-200.f);
	}
	else
	{
		GetOwnerObj()->Movement()->SetVelocityX(200.f);
	}


	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		ChangeState(L"JumpFall");	
	}

}

void CComboStand03::Enter()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	pScript->SetLock(true);

	m_Dir = pScript->GetDir();

	GetOwnerObj()->Animator2D()->Play(L"LD_COMBOMOVE03", false);
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);

	GetOwnerObj()->Movement()->SetGround(true);

	CLDHitBox* HitBoxScript = GetOwnerObj()->GetChild(L"LD_Att")->GetScript<CLDHitBox>();
	if (HitBoxScript != nullptr)
	{
		HitBoxScript->On();
	}
}

void CComboStand03::Exit()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();

	pScript->SetLock(false);

	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 0);

	GetOwnerObj()->Movement()->SetGround(false);
}

