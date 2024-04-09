#include "pch.h"
#include "CComboMove02.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CMeshRender.h>
#include <Engine/CAnim.h>


#include <Scripts/CLDScript.h>
#include <Scripts/CLDHitBox.h>


CComboMove02::CComboMove02()
	:CState(COMBOMOVE02)
{
}

CComboMove02::~CComboMove02()
{
}


void CComboMove02::finaltick()
{
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();

	int CurIdx = GetOwnerObj()->Animator2D()->GetCurAnimInst()->GetCurAnimIdx();

	if (KEY_TAP(KEY::LBTN))
	{
		IsClicked = true;
	}

	if (CurIdx == 5)
	{
		GetOwnerObj()->Movement()->SetVelocityX(0.f);
	}


	if (GetOwnerObj()->Animator2D()->IsCurAnimFinished())
	{
		if (IsClicked)
		{
			ChangeState(L"ComboMove03");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}
}

void CComboMove02::Enter()
{	
	// Dir Lock
	CLDScript* pScript = GetOwnerObj()->GetScript<CLDScript>();
	pScript->SetLock(true);

	if (pScript->GetDir() == ANIM_DIR::LEFT)
	{
		GetOwnerObj()->Movement()->SetVelocityX(-500.f);
	}
	else
	{
		GetOwnerObj()->Movement()->SetVelocityX(500.f);
	}

	CLDHitBox* HitBoxScript = GetOwnerObj()->GetChild(L"LD_Att")->GetScript<CLDHitBox>();
	if (HitBoxScript != nullptr)
	{
		HitBoxScript->On();
	}


	// Animation
	GetOwnerObj()->Animator2D()->Play(L"LD_COMBOMOVE02", false);
	GetOwnerObj()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);

	// Clicked ¼¼ÆÃ
	IsClicked = false;
}

void CComboMove02::Exit()	
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

