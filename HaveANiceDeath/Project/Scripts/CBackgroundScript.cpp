#include "pch.h"
#include "CBackgroundScript.h"

#include <Engine/CKeyMgr.h>
#include <Engine\CAssetMgr.h>

void CBackgroundScript::SaveToFile(FILE* _File)
{
}

void CBackgroundScript::LoadFromFile(FILE* _File)
{
}

CBackgroundScript::CBackgroundScript()
	: CScript(SCRIPT_TYPE::BACKGROUNDSCRIPT)
{
}

CBackgroundScript::~CBackgroundScript()
{
}

void CBackgroundScript::begin()
{
	MeshRender()->GetDynamicMaterial();
	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg"));
}

void CBackgroundScript::tick()
{

	static int i = 0;
	if (KEY_TAP(KEY::T))
	{
		i ? MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1) : MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 0);
		i = !i;
	}
}
