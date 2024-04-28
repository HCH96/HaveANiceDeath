#include "pch.h"
#include "CMonsterHitBoxScript.h"

#include "CLDScript.h"

CMonsterHitBoxScript::CMonsterHitBoxScript()
	: CScript(MONSTERHITBOXSCRIPT)
	, m_Acc(0.f)
	, m_Active(false)
	, m_Duration(0.f)
	, m_Damage(0.f)
	, m_ColOffset(Vec3(0.f,0.f,0.f))
    , m_ColScale(Vec3(0.f,0.f,0.f))
{
	AddScriptParam(SCRIPT_PARAM::VEC3, "Col Offset ", &m_ColOffset);
	AddScriptParam(SCRIPT_PARAM::VEC3, "Col Scale ", &m_ColScale);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Damage ", &m_Damage);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Duration ", &m_Duration);
}

CMonsterHitBoxScript::CMonsterHitBoxScript(const CMonsterHitBoxScript& _Origin)
	: CScript(MONSTERHITBOXSCRIPT)
	, m_Acc(0.f)
	, m_Active(_Origin.m_Active)
	, m_Duration(_Origin.m_Duration)
	, m_Damage(_Origin.m_Damage)
	, m_ColOffset(_Origin.m_ColOffset)
	, m_ColScale(_Origin.m_ColScale)
{
	AddScriptParam(SCRIPT_PARAM::VEC3, "Col Offset(Right) ", &m_ColOffset);
	AddScriptParam(SCRIPT_PARAM::VEC3, "Col Scale ", &m_ColScale);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Damage ", &m_Damage);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Duration ", &m_Duration);
}

CMonsterHitBoxScript::~CMonsterHitBoxScript()
{
}

void CMonsterHitBoxScript::Activate()
{
	CGameObject* OwnerObject = GetOwner()->GetParent();

	if (!OwnerObject)
		return;

	CUnitScript* UnitScript = OwnerObject->GetScript<CUnitScript>();
	
	if (!UnitScript)
		return;

	ANIM_DIR CurAnimDir = UnitScript->GetDir();

	if (CurAnimDir == ANIM_DIR::LEFT)
	{
		GetOwner()->Collider2D()->SetOffset(-m_ColOffset);
	}
	else
	{
		GetOwner()->Collider2D()->SetOffset(m_ColOffset);
	}

	m_Active = true;
	m_Acc = 0.f;
	GetOwner()->Collider2D()->Activate();
}

void CMonsterHitBoxScript::begin()
{
	GetOwner()->Collider2D()->SetScale(m_ColScale);
	GetOwner()->Collider2D()->Deactivate();
}

void CMonsterHitBoxScript::tick()
{ 
	if (!m_Active)
		return;

	m_Acc += DT;

	if (m_Duration < m_Acc)
	{
		GetOwner()->Collider2D()->Deactivate();
		m_Active = false;
	}
}

void CMonsterHitBoxScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CLDScript* pScript = _OtherObj->GetScript<CLDScript>();

	if (nullptr == pScript)
	{
		return;
	}

	pScript->Hit(m_Damage);
}

void CMonsterHitBoxScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMonsterHitBoxScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMonsterHitBoxScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Duration, sizeof(float), 1, _File);
	fwrite(&m_Damage, sizeof(float), 1, _File);
	fwrite(&m_ColOffset, sizeof(Vec3), 1, _File);
	fwrite(&m_ColScale, sizeof(Vec3), 1, _File);
}

void CMonsterHitBoxScript::LoadFromFile(FILE* _File)
{
	fread(&m_Duration, sizeof(float), 1, _File);
	fread(&m_Damage, sizeof(float), 1, _File);
	fread(&m_ColOffset, sizeof(Vec3), 1, _File);
	fread(&m_ColScale, sizeof(Vec3), 1, _File);
}


