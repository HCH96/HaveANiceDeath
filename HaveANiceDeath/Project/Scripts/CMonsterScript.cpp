#include "pch.h"
#include "CMonsterScript.h"

CMonsterScript::CMonsterScript()
	:CUnitScript(MONSTERSCRIPT)
{
}

CMonsterScript::CMonsterScript(UINT _ScriptType)
	:CUnitScript(_ScriptType)
{
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::begin()
{
}

void CMonsterScript::tick()
{
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

