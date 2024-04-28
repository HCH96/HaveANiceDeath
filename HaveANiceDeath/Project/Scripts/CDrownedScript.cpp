#include "pch.h"
#include "CDrownedScript.h"

#include <Engine/CState.h>

#include <States/CStateMgr.h>


CDrownedScript::CDrownedScript()
	:CMonsterScript(DROWNEDSCRIPT)
{
}

CDrownedScript::~CDrownedScript()
{
}

void CDrownedScript::Hit(float _Damage)
{
	Variation();

	const wstring& Curstate = CStateMgr::GetStateName(GetOwner()->StateMachine()->GetDynamicFSM()->GetCurState());
	
	if (Curstate == L"CDrownedDeath")
		return;

	m_CurUnitInfo.HP -= _Damage;

	// Stun �����϶��� ���� ���� X
	if (Curstate == L"CDrownedStunStart" || Curstate == L"CDrownedStunLoop" || Curstate == L"CDrownedStunEnd")
	{
		return;
	}

	GetOwner()->StateMachine()->GetDynamicFSM()->ChangeState(L"Hit");
}

void CDrownedScript::begin()
{
	CMonsterScript::begin();

	// UnitInfo ����
	m_CurUnitInfo.HP = 50.f;
	m_CurUnitInfo.Dir = ANIM_DIR::LEFT;

	// Dynamic Mtrl ����
	GetRenderComponent()->GetDynamicMaterial();

	// glow Effect ����
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 1);
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, 0.7f);
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_0, Vec4(0.f, 0.3f, 0.3f, 0.7f));


	StateMachine()->GetDynamicFSM()->ChangeState(L"Appear");
}

void CDrownedScript::tick()
{
	CMonsterScript::tick();

	float CurDamage = m_PrevUnitInfo.HP - m_CurUnitInfo.HP;


	//if (CurDamage > 0)
	//{
	//	GetOwner()->StateMachine()->GetDynamicFSM()->ChangeState(L"Hit");
	//	GetOwner()->StateMachine()->GetDynamicFSM()->ChangeState(L"StunStart");
	//}

	// Death State
	if (m_CurUnitInfo.HP <= 0)
	{
		GetOwner()->StateMachine()->GetDynamicFSM()->ChangeState(L"Death");
	}

	
	// Anim ���� ���� ���� -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void CDrownedScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDrownedScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDrownedScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDrownedScript::SaveToFile(FILE* _File)
{
}

void CDrownedScript::LoadFromFile(FILE* _File)
{
}

