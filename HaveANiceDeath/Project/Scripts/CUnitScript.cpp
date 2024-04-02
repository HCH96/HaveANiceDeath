#include "pch.h"
#include "CUnitScript.h"

// 안쓰는 거
CUnitScript::CUnitScript()
	: CScript(UNITSCRIPT)
	, m_DirLock(false)
	, m_OverlapGround(0)
	, m_Ground{}

{

}

CUnitScript::CUnitScript(UINT _ScriptType)
	: CScript(_ScriptType)
	, m_DirLock(false)
	, m_OverlapGround(0)
	, m_Ground{}
{
	AddScriptParam(SCRIPT_PARAM::INT, "Anim Dir", &m_CurUnitInfo.Dir);
	AddScriptParam(SCRIPT_PARAM::INT, "OverlapGround", &m_OverlapGround);
}

CUnitScript::CUnitScript(const CUnitScript& _Origin)
	: CScript(_Origin)
	, m_DirLock(_Origin.m_DirLock)
	, m_OverlapGround(0)
	, m_Ground{}
{
	AddScriptParam(SCRIPT_PARAM::INT, "Anim Dir", &m_CurUnitInfo.Dir);
	AddScriptParam(SCRIPT_PARAM::INT, "OverlapGround", &m_OverlapGround);
}

CUnitScript::~CUnitScript()
{
}



void CUnitScript::begin()
{
	m_PrevUnitInfo = m_CurUnitInfo;
}

void CUnitScript::tick()
{
	m_PrevUnitInfo = m_CurUnitInfo;
}

void CUnitScript::SaveToFile(FILE* _File)
{
}

void CUnitScript::LoadFromFile(FILE* _File)
{
}

void CUnitScript::AddOverlapGround(CGameObject* _pObejct)
{
	m_Ground.push_back(_pObejct);

	m_OverlapGround = m_Ground.size();
}

void CUnitScript::SubOverlapGround(CGameObject* _pObejct)
{
	vector<CGameObject*>::iterator iter = m_Ground.begin();

	for (; iter != m_Ground.end();)
	{
		if (*iter == _pObejct)
		{
			iter = m_Ground.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	m_OverlapGround = m_Ground.size();
}