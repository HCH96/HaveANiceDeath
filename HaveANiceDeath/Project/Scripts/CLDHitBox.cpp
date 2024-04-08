#include "pch.h"
#include "CLDHitBox.h"

#include <States/CStateMgr.h>

#include "CLDScript.h"

#include "CMonsterScript.h"
#include "CLDScript.h"

CLDHitBox::CLDHitBox()
	: CScript(LDHITBOX)
	, m_Acc(0.f)
	, m_Active(false)
	, m_Duration(0.f)
	, m_Damage(0.f)
	, m_StartTime(0.f)
	, m_IsColliderActive(false)
{
}

CLDHitBox::CLDHitBox(const CLDHitBox& _Origin)
	: CScript(LDHITBOX)
	, m_Acc(0.f)
	, m_Active(false)
	, m_Duration(0.f)
	, m_Damage(0.f)
	, m_StartTime(0.f)
	, m_IsColliderActive(false)
{
}

CLDHitBox::~CLDHitBox()
{
}


void CLDHitBox::On()
{
	m_Active = true;

	CGameObject* LD = GetOwner()->GetParent();
	ANIM_DIR Dir = LD->GetScript<CLDScript>()->GetDir();

	wstring CurStateName = CStateMgr::GetStateName(GetOwner()->GetParent()->StateMachine()->GetDynamicFSM()->GetCurState());
	CCollider2D* HitBox = GetOwner()->Collider2D();

	// On된 순간 Player의 정보를 가져와 자신의 Offset, Scale 세팅
	if(CurStateName == L"CComboMove01")
	{
		HitBox->SetOffset(Vec3(100.f, 100.f, 0.f));
		HitBox->SetScale(Vec3(100.f, 100.f, 1.f));

		m_Damage = 10.f;

		m_StartTime = 0.f;
		m_Duration = 0.5f;
	}

	if (CurStateName == L"CComboMove02")
	{
		HitBox->SetOffset(Vec3(100.f, 100.f, 0.f));
		HitBox->SetScale(Vec3(100.f, 100.f, 1.f));

		m_Damage = 10.f;

		m_StartTime = 0.f;
		m_Duration = 2.f;
	}

	if (CurStateName == L"CComboMove03")
	{
		HitBox->SetOffset(Vec3(100.f, 100.f, 0.f));
		HitBox->SetScale(Vec3(100.f, 100.f, 1.f));

		m_Damage = 10.f;

		m_StartTime = 0.f;
		m_Duration = 2.f;
	}

	if (CurStateName == L"CComboMove04")
	{
		HitBox->SetOffset(Vec3(100.f, 100.f, 0.f));
		HitBox->SetScale(Vec3(100.f, 100.f, 1.f));

		m_Damage = 10.f;

		m_StartTime = 0.f;
		m_Duration = 2.f;
	}

	// 방향이 반대인 경우 뒤집어주기
	if (Dir == ANIM_DIR::LEFT)
	{
		Vec3 Offset = HitBox->GetOffset();
		Offset.x *= -1;

		HitBox->SetOffset(Offset);
	}
}

void CLDHitBox::Off()
{
	GetOwner()->Collider2D()->Deactivate();
	m_Active = false;

	m_Acc = 0.f;
	m_Duration = 0.f;
	m_StartTime = 0.f;
	m_Damage = 0.f;

	m_IsColliderActive = false;
}

void CLDHitBox::Activate()
{
	// Collider 활성화
	GetOwner()->Collider2D()->Activate();
	m_IsColliderActive = true;
}

void CLDHitBox::begin()
{
	GetOwner()->Collider2D()->Deactivate();
	GetOwner()->Collider2D()->SetAbsolute(true);

	Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
	Transform()->SetAbsolute(true);

	m_Active = false;
}

void CLDHitBox::tick()
{
	// HitBox가 활성화 중이 아니라면 return
	if (!m_Active)
		return;

	m_Acc += DT;

	// Start Time이 지났고, Collider가 Active상태가 아니라면 켜준다.
	if (m_Acc >= m_StartTime && m_IsColliderActive == false)
	{
		Activate();
	}

	if (m_Acc-m_StartTime >= m_Duration)
	{
		Off();
	}
}

void CLDHitBox::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	// Monster가 아니라면 return
	CMonsterScript* MonScript = _OtherObj->GetScript<CMonsterScript>();
	
	if (MonScript == nullptr)
		return;


	tUnitInfo& Info = MonScript->GetUnitInfo();
	Info.HP -= m_Damage;
}

void CLDHitBox::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CLDHitBox::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CLDHitBox::SaveToFile(FILE* _File)
{
}

void CLDHitBox::LoadFromFile(FILE* _File)
{
}

