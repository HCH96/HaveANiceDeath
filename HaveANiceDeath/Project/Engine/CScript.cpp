#include "pch.h"
#include "CScript.h"

CScript::CScript(UINT _ScriptType)
	: CComponent(COMPONENT_TYPE::SCRIPT)
	, m_ScriptType(_ScriptType)
	, m_ScriptParam{}
{
}

CScript::CScript(const CScript& _OriginScript)
	: CComponent(_OriginScript)
	, m_ScriptType(_OriginScript.m_ScriptType)
	, m_ScriptParam{}
{
}

CScript::~CScript()
{
}

void CScript::Instantiate(Ptr<CPrefab> _Prefab, Vec3 _vWorldPos, int _LayerIdx)
{
	if (nullptr == _Prefab)
		return;

	CGameObject* pNewObj = _Prefab->Instantiate();

	pNewObj->Transform()->SetRelativePos(_vWorldPos);

	GamePlayStatic::SpawnGameObject(pNewObj, _LayerIdx);
}
