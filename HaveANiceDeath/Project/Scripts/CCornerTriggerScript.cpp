#include "pch.h"
#include "CCornerTriggerScript.h"

#include <States/CStateMgr.h>

#include "CLDScript.h"


CCornerTriggerScript::CCornerTriggerScript()
	:CScript(SCRIPT_TYPE::CORNERTRIGGERSCRIPT)
{
}

CCornerTriggerScript::CCornerTriggerScript(const CCornerTriggerScript& _OriginScript)
	: CScript(_OriginScript)
{
}

CCornerTriggerScript::~CCornerTriggerScript()
{
}


void CCornerTriggerScript::begin()
{

}

void CCornerTriggerScript::tick()
{
}

void CCornerTriggerScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	// Player가 아니거나 Movement가 없다면 return
	if (nullptr == _OtherObj->GetScript<CLDScript>() || !(_OtherObj->Movement()))
	{
		return;
	}

	Ptr<CFSM> pFSM = _OtherObj->StateMachine()->GetDynamicFSM();
	if (L"CLDDash" != CStateMgr::GetStateName(pFSM->GetCurState()))
	{
		pFSM->ChangeState(L"CornerTrigger");
	}

	CUnitScript* UnitScript = _OtherObj->GetScript<CUnitScript>();
	UnitScript->AddOverlapGround(GetOwner());

	if (UnitScript->GetOverlapGround() > 0)
	{
		_OtherObj->Movement()->SetGround(true);
	}
}

void CCornerTriggerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	// Player가 아니거나 Movement가 없다면 return
	if (nullptr == _OtherObj->GetScript<CLDScript>() || !(_OtherObj->Movement()))
	{
		return;
	}

	// Platform 
	Vec3 ColPos, ColScale;
	Vec2 PlatformLT, PlatformRB;

	ColPos = _Collider->GetFinalPos();

	// Object
	Vec3 ObjColPos, ObjColScale;
	Vec2 ObjLT, ObjRB;

	ObjColPos = _OtherCollider->GetFinalPos();

	if (_Collider->IsAbsolute())
	{
		ColScale = _Collider->GetScale();
	}
	// 조부모 오브젝트가 있을경우 안맞을 듯
	else
	{
		ColScale = _Collider->Transform()->GetWorldScale();
	}

	if (_OtherCollider->IsAbsolute())
	{
		ObjColScale = _OtherCollider->GetScale();
	}
	// 조부모 오브젝트가 있을경우 안맞을 듯
	else
	{
		ObjColScale = _OtherCollider->Transform()->GetWorldScale();
	}


	PlatformLT = Vec2(ColPos.x - ColScale.x / 2.f, ColPos.y + ColScale.y / 2.f);
	PlatformRB = Vec2(ColPos.x + ColScale.x / 2.f, ColPos.y - ColScale.y / 2.f);

	// Object의 방향 구하기
	_OtherObj->Movement()->CalDir();
	MovementDir ObjDir = _OtherObj->Movement()->GetDir();

	// Object Collider의 PrevPos
	Vec3 PrevPos = _OtherObj->Collider2D()->GetPrevFinalPos();


	Ptr<CFSM> pFSM = _OtherObj->StateMachine()->GetDynamicFSM();
	wstring CurState = CStateMgr::GetStateName(pFSM->GetCurState());

	// CornerTrigger
	if (PlatformRB.y <= PrevPos.y - ObjColScale.y / 2.f)
	{
		if ((CurState == L"CLDCornerTrigger"|| CurState == L"CLDDash") && (PlatformLT.y - 1.f >= PrevPos.y - ObjColScale.y / 2.f && (ObjDir & MV_RIGHT) | (ObjDir & MV_LEFT)))
		{
			float upVelocity = fabs(_OtherObj->Movement()->GetVelocity().x) * DT;
			Vec3 CurPos = _OtherObj->Transform()->GetRelativePos();

			_OtherObj->Transform()->SetRelativePos(Vec3(CurPos.x, CurPos.y + upVelocity, CurPos.z));
		}
	}
	// wall grap
	else if (ObjDir & MV_DOWN)
	{

	}
}

void CCornerTriggerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	// Player가 아니거나 Movement가 없다면 return
	if (nullptr == _OtherObj->GetScript<CLDScript>() || !(_OtherObj->Movement()))
	{
		return;
	}

	CUnitScript* UnitScript = _OtherObj->GetScript<CUnitScript>();
	UnitScript->SubOverlapGround(GetOwner());

	if (UnitScript->GetOverlapGround() <= 0)
	{
		_OtherObj->Movement()->SetGround(false);
	}
}

void CCornerTriggerScript::SaveToFile(FILE* _File)
{
}

void CCornerTriggerScript::LoadFromFile(FILE* _File)
{
}

