#include "pch.h"
#include "CComboStand02.h"

#include <Engine/CMovement.h>
#include <Engine/CMeshRender.h>

#include <Scripts/CLDScript.h>
#include <Scripts/CLDHitBox.h>

CComboStand02::CComboStand02()
	: CState(COMBOSTAND02)
{
}

CComboStand02::~CComboStand02()
{
}


void CComboStand02::finaltick()
{
	CLDScript* LDScript = GetOwnerObj()->GetScript<CLDScript>();

	if (m_IsClicked == false && KEY_TAP(KEY::LBTN))
	{
		m_IsClicked = true;
	}

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
		if (m_IsClicked)
		{
			LDScript->PlayComboStand();
		}
		else
		{
			ChangeState(L"JumpFall");
		}
	}


}

void CComboStand02::Enter()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	pScript->SetLock(true);

	m_Dir = pScript->GetDir();
	m_IsClicked = false;


	GetOwnerObj()->Animator2D()->Play(L"LD_COMBOMOVE01", false);
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);

	GetOwnerObj()->Movement()->SetGround(true);

	CLDHitBox* HitBoxScript = GetOwnerObj()->GetChild(L"LD_Att")->GetScript<CLDHitBox>();
	if (HitBoxScript != nullptr)
	{
		HitBoxScript->On();
	}

}

void CComboStand02::Exit()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();

	pScript->SetLock(false);

	if ((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D))
	{
		pScript->SetDir(ANIM_DIR::LEFT);
	}

	if ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A))
	{
		pScript->SetDir(ANIM_DIR::RIGHT);
	}

	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 0);

	GetOwnerObj()->Movement()->SetGround(false);

}

