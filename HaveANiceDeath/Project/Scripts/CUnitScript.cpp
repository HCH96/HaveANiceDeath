#include "pch.h"
#include "CUnitScript.h"

// �Ⱦ��� ��
CUnitScript::CUnitScript()
	: CScript(UNITSCRIPT)
{

}

CUnitScript::CUnitScript(UINT _ScriptType)
	: CScript(_ScriptType)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Anim Dir", &m_CurUnitInfo.Dir);
}

CUnitScript::~CUnitScript()
{
}

void CUnitScript::begin()
{
	m_CurUnitInfo = m_NextUnitInfo;
}

void CUnitScript::tick()
{
	m_CurUnitInfo = m_NextUnitInfo;
}

void CUnitScript::SaveToFile(FILE* _File)
{
}

void CUnitScript::LoadFromFile(FILE* _File)
{
}