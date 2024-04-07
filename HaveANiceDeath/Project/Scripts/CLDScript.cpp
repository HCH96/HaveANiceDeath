#include "pch.h"
#include "CLDScript.h"

#include <Engine\CKeyMgr.h>

#include <States/CStateMgr.h>


CLDScript::CLDScript()
	: CUnitScript(LDSCRIPT)
	, m_DirChanged(false)
{
	m_CurUnitInfo.Dir = ANIM_DIR::RIGHT;

}

CLDScript::CLDScript(const CLDScript& _Origin)
	: CUnitScript(_Origin)
	, m_DirChanged(false)
{
	m_CurUnitInfo.Dir = ANIM_DIR::RIGHT;
}

CLDScript::~CLDScript()
{
}


void CLDScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CLDScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CLDScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CLDScript::begin()
{
	CUnitScript::begin();

	// Dynamic Mtrl 생성
	GetRenderComponent()->GetDynamicMaterial();

	// glow Effect 설정
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, 0.5f);
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_0, Vec4(0.3f, 0.2f, 0.4f, 1.f));


	StateMachine()->GetDynamicFSM()->ChangeState(L"Idle");
}

void CLDScript::tick()
{
	// 다음 프레임 방향 설정

	if (!IsLock())
	{
		CUnitScript::tick();

		if ((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D))
		{
			m_CurUnitInfo.Dir = ANIM_DIR::LEFT;
			
			Movement()->SetVelocityX(-900.f);
		}

		if ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A))
		{
			m_CurUnitInfo.Dir = ANIM_DIR::RIGHT;

			Movement()->SetVelocityX(900.f);
		}

		// 다음 프레임에 방향이 바뀌는지
		if (m_CurUnitInfo.Dir != m_PrevUnitInfo.Dir)
		{
			m_DirChanged = true;
		}
		else
		{
			m_DirChanged = false;
		}

	}
	else
	{
		m_DirChanged = false;
	}

	// Glow Effect UpdateData
	CState* CurState = StateMachine()->GetDynamicFSM()->GetCurState();
	wstring CurStateName = CStateMgr::GetStateName(CurState);

	if (CurStateName == L"CComboMove01" || CurStateName == L"CComboMove02" || CurStateName == L"CComboMove03" || CurStateName == L"CComboMove04")
	{

	}
	else
	{
		GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, 0);
	}


	// Anim 방향 정보 갱신 -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void CLDScript::SaveToFile(FILE* _File)
{

}

void CLDScript::LoadFromFile(FILE* _File)
{
}

