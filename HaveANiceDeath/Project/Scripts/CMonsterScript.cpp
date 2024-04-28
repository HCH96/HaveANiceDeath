#include "pch.h"
#include "CMonsterScript.h"

CMonsterScript::CMonsterScript()
	: CUnitScript(MONSTERSCRIPT)
	, m_Duration(0.2f)
	, m_IsVariation(false)
	, m_Acc(0.f)
	, m_VarColor(1.f,0.f,0.f,0.8f)
{
}

CMonsterScript::CMonsterScript(UINT _ScriptType)
	: CUnitScript(_ScriptType)
	, m_Duration(0.3f)
	, m_IsVariation(false)
	, m_Acc(0.f)
	, m_VarColor(1.f, 0.f, 0.f, 0.8f)
{
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::Variation()
{
	m_IsVariation = true;
	m_Acc = 0.f;
}

void CMonsterScript::begin()
{
	CUnitScript::begin();
}

void CMonsterScript::tick()
{
	CUnitScript::tick();

	if (m_IsVariation)
	{
		m_Acc += DT;

		if (m_Duration < m_Acc)
		{
			m_IsVariation = false;
			GetOwner()->MeshRender()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_1, Vec4(0.f, 0.f, 0.f, 0.f));
		}
		else
		{
			float Ratio = m_Acc/m_Duration;
			Ratio *= 2.f;

			// 절반이 넘었다면 알파값을 뒤집는다 0 ~ 1 , 1 ~ 0
			if (Ratio > 1.f)
			{
				Ratio = 2.f - Ratio;
			}

			//Ratio = sinf(Ratio * XM_PI / 2.f);
			//Ratio = powf(Ratio, 0.1);

			
			Vec4 VarColor = m_VarColor;
			VarColor.w *= Ratio;

			GetOwner()->MeshRender()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_1, VarColor);
		}
	}

}

void CMonsterScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMonsterScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMonsterScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CMonsterScript::SaveToFile(FILE* _File)
{
}

void CMonsterScript::LoadFromFile(FILE* _File)
{
}

