#include "pch.h"
#include "CLDScript.h"

#include <Engine\CKeyMgr.h>

CLDScript::CLDScript()
	: CUnitScript(LDSCRIPT)
	, m_DirChanged(false)
{
}

CLDScript::~CLDScript()
{
}


void CLDScript::begin()
{
	CUnitScript::begin();

	// Dynamic Mtrl 생성
	GetRenderComponent()->GetDynamicMaterial();

	StateMachine()->GetDynamicFSM()->ChangeState(L"Idle");
}

void CLDScript::tick()
{
	// 다음 프레임 방향 설정

	if (!IsLock())
	{
		CUnitScript::tick();

		if ((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && (KEY_NONE(KEY::D) || KEY_RELEASED(KEY::D)))
		{
			m_NextUnitInfo.Dir = ANIM_DIR::LEFT;
		}

		if ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && (KEY_NONE(KEY::A) || KEY_RELEASED(KEY::A)))
		{
			m_NextUnitInfo.Dir = ANIM_DIR::RIGHT;
		}

		// 다음 프레임에 방향이 바뀌는지
		if (m_CurUnitInfo.Dir != m_NextUnitInfo.Dir)
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



	// Anim 방향 정보 갱신 0: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void CLDScript::SaveToFile(FILE* _File)
{

}

void CLDScript::LoadFromFile(FILE* _File)
{
}

