#include "pch.h"
#include "CScriptTemplate.h"

CScriptTemplate::CScriptTemplate()
	: CScript(SCRIPTTEMPLATE)
{
}

CScriptTemplate::~CScriptTemplate()
{
}


void CScriptTemplate::begin()
{
}

void CScriptTemplate::tick()
{
}

void CScriptTemplate::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CScriptTemplate::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CScriptTemplate::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}


void CScriptTemplate::SaveToFile(FILE* _File)
{
}

void CScriptTemplate::LoadFromFile(FILE* _File)
{
}

