#include "pch.h"
#include "CLDScript.h"

#include <Engine\CKeyMgr.h>



CLDScript::CLDScript()
	: CUnitScript(LDSCRIPT)
	, m_DirChanged(false)
{
	m_CurUnitInfo.Dir = ANIM_DIR::RIGHT;
}

CLDScript::~CLDScript()
{
}


void CLDScript::begin()
{
	CUnitScript::begin();

	// Dynamic Mtrl ����
	GetRenderComponent()->GetDynamicMaterial();

	StateMachine()->GetDynamicFSM()->ChangeState(L"Idle");
}

void CLDScript::tick()
{
	// ���� ������ ���� ����

	if (!IsLock())
	{
		CUnitScript::tick();

		if ((KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A)) && KEY_NONE(KEY::D))
		{
			m_CurUnitInfo.Dir = ANIM_DIR::LEFT;
			
			Movement()->SetVelocityX(-500.f);
		}

		if ((KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D)) && KEY_NONE(KEY::A))
		{
			m_CurUnitInfo.Dir = ANIM_DIR::RIGHT;

			Movement()->SetVelocityX(500.f);
		}

		// ���� �����ӿ� ������ �ٲ����
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

	// Anim ���� ���� ���� -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void CLDScript::SaveToFile(FILE* _File)
{

}

void CLDScript::LoadFromFile(FILE* _File)
{
}

