#include "pch.h"
#include "CPlatformScript.h"

#include "CUnitScript.h"

#include <Engine\CMovement.h>
#include "CLDScript.h"

CPlatformScript::CPlatformScript()
	:CScript(PLATFORMSCRIPT)
	, m_SideCollision(false)
	, m_PermitRange(0.f)
{
	AddScriptParam(SCRIPT_PARAM::BOOL, "Side Collision", &m_SideCollision);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Permit Range", &m_PermitRange);
}

CPlatformScript::CPlatformScript(const CPlatformScript& _OriginScript)
	: CScript(_OriginScript)
	, m_SideCollision(_OriginScript.m_SideCollision)
	, m_PermitRange(_OriginScript.m_PermitRange)
{
	AddScriptParam(SCRIPT_PARAM::BOOL, "Side Collision", &m_SideCollision);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Permit Range", &m_PermitRange);
}

CPlatformScript::~CPlatformScript()
{
}

void CPlatformScript::begin()
{
}

void CPlatformScript::tick()
{
}

void CPlatformScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	// Unit이 아니거나 Movement가 없다면 return
	if (nullptr == _OtherObj->GetScript<CUnitScript>() || !(_OtherObj->Movement()))
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

	// 위에서 아래로 충돌
	if ((ObjDir & MV_DOWN) && PlatformLT.y < PrevPos.y - ObjColScale.y / 2.f)
	{
 		UpCollision(_OtherObj, PlatformLT.y, ObjColScale.y);
	}
	// 아래서 위로 충돌
	else if ((ObjDir & MV_UP) && PlatformRB.y >= PrevPos.y + ObjColScale.y / 2.f)
	{
		DownCollision(_OtherObj, PlatformRB.y, ObjColScale.y);
	}
	else
	{
		// 허용 범위안에서 플랫폼을 넘어갈 때
		if ((PlatformLT.y - m_PermitRange < PrevPos.y - ObjColScale.y / 2.f) && (PlatformLT.y + m_PermitRange > PrevPos.y - ObjColScale.y / 2.f))
		{
			UpCollision(_OtherObj, PlatformLT.y, ObjColScale.y);
		}
		else if (m_SideCollision)
		{
			// Left 충돌
			if ((ObjDir & MV_RIGHT) && PlatformLT.x >= PrevPos.x + ObjColScale.x / 2.f)
			{
				LeftCollision(_OtherObj, PlatformLT.x, ObjColScale.x);
			}
			// Right 충돌
			else if ((ObjDir & MV_LEFT) && PlatformRB.x <= PrevPos.x - ObjColScale.x / 2.f)
			{
				RightCollision(_OtherObj, PlatformRB.x, ObjColScale.x);
			}
		}
	}

}

void CPlatformScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	// Unit이 아니거나 Movement가 없다면 return
	if (nullptr == _OtherObj->GetScript<CUnitScript>() || !(_OtherObj->Movement()))
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


	// 아래서 위 충돌
	if ((ObjDir & MV_UP) && PlatformRB.y >= PrevPos.y + ObjColScale.y / 2.f)
	{
		DownCollision(_OtherObj, PlatformRB.y, ObjColScale.y);
	}

	if (m_SideCollision)
	{
		// Left 충돌
		if ((ObjDir & MV_RIGHT) && PlatformLT.x >= PrevPos.x + ObjColScale.x / 2.f)
		{
			LeftCollision(_OtherObj, PlatformLT.x, ObjColScale.x);
		}
		// Right 충돌
		else if ((ObjDir & MV_LEFT) && PlatformRB.x <= PrevPos.x - ObjColScale.x / 2.f)
		{
			RightCollision(_OtherObj, PlatformRB.x, ObjColScale.x);
		}
	}

}

void CPlatformScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (nullptr == _OtherObj->GetScript<CUnitScript>() || !(_OtherObj->Movement()))
	{
		return;
	}

	CUnitScript* UnitScript = _OtherObj->GetScript<CUnitScript>();
	UnitScript->SubOverlapGround(GetOwner());

	CLDScript* ObjScript = _OtherObj->GetScript<CLDScript>();
	ObjScript->SetDownCollision(false);

	if (UnitScript->GetOverlapGround() <= 0)
	{
		_OtherObj->Movement()->SetGround(false);
	}
}

void CPlatformScript::SaveToFile(FILE* _File)
{
	fwrite(&m_SideCollision, sizeof(bool), 1, _File);
	fwrite(&m_PermitRange, sizeof(float), 1, _File);
}

void CPlatformScript::LoadFromFile(FILE* _File)
{
	fread(&m_SideCollision, sizeof(bool), 1, _File);
	fread(&m_PermitRange, sizeof(float), 1, _File);
}

void CPlatformScript::UpCollision(CGameObject* _Obj, float _PlatformTop, float _ObjColScaleY)
{		
	float NewY = _PlatformTop + _ObjColScaleY / 2.f;

	NewY -= _Obj->Collider2D()->GetOffset().y;


	Vec3 ObjPos = _Obj->Transform()->GetRelativePos();
	ObjPos.y = NewY;

	_Obj->Transform()->SetRelativePos(ObjPos);

	CUnitScript* UnitScript = _Obj->GetScript<CUnitScript>();
	UnitScript->AddOverlapGround(GetOwner());

	if (UnitScript->GetOverlapGround() > 0)
	{
		_Obj->Movement()->SetGround(true);
	}
}

void CPlatformScript::DownCollision(CGameObject* _Obj, float _PlatformBottom, float _ObjColScaleY)
{
	float NewY = _PlatformBottom - _ObjColScaleY / 2.f;
	NewY -= _Obj->Collider2D()->GetOffset().y;

	CLDScript* ObjScript = _Obj->GetScript<CLDScript>();
	ObjScript->SetDownCollision(true);

	Vec3 ObjPos = _Obj->Transform()->GetRelativePos();
	ObjPos.y = NewY;

	_Obj->Transform()->SetRelativePos(ObjPos);
}

void CPlatformScript::LeftCollision(CGameObject* _Obj, float _PlatformLeft, float _ObjColScaleX)
{
	float NewX = _PlatformLeft - _ObjColScaleX / 2.f;
	NewX -= _Obj->Collider2D()->GetOffset().x;

	Vec3 ObjPos = _Obj->Transform()->GetRelativePos();
	ObjPos.x = NewX;

	_Obj->Transform()->SetRelativePos(ObjPos);

}

void CPlatformScript::RightCollision(CGameObject* _Obj, float _PlatformRight, float _ObjColScaleX)
{
	float NewX = _PlatformRight + _ObjColScaleX / 2.f;
	NewX -= _Obj->Collider2D()->GetOffset().x;

	Vec3 ObjPos = _Obj->Transform()->GetRelativePos();
	ObjPos.x = NewX;

	_Obj->Transform()->SetRelativePos(ObjPos);
}