#include "pch.h"
#include "CComboMove01.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CMeshRender.h>
#include <Engine/CMovement.h>

#include <Scripts/CLDScript.h>
#include <Scripts/CLDHitBox.h>

CComboMove01::CComboMove01()
	:CState(COMBOMOVE01)
{
}

CComboMove01::~CComboMove01()
{
}


void CComboMove01::finaltick()
{
	if (KEY_TAP(KEY::LBTN))
	{
		IsClicked = true;
	}


	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		if (IsClicked)
		{
			ChangeState(L"ComboMove02");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}

}

void CComboMove01::Enter()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	pScript->SetLock(true);

	GetOwnerObj()->Animator2D()->Play(L"LD_COMBOMOVE01", false);
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);

	GetOwnerObj()->Movement()->SetVelocityX(0.f);

	CLDHitBox* HitBoxScript = GetOwnerObj()->GetChild(L"LD_Att")->GetScript<CLDHitBox>();
	if (HitBoxScript != nullptr)
	{
		HitBoxScript->On();
	}


	IsClicked = false;
}

void CComboMove01::Exit()
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
}

