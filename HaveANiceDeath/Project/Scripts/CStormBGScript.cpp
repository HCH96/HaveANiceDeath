#include "pch.h"
#include "CStormBGScript.h"


CStormBGScript::CStormBGScript()
	:CScript(STORMBGSCRIPT)
{
}

CStormBGScript::~CStormBGScript()
{
}

void CStormBGScript::begin()
{
	Vec3 ImgSize = GetOwner()->Transform()->GetRelativeScale();


	GetOwner()->MeshRender()->GetDynamicMaterial();
	GetOwner()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, ImgSize.x);
	GetOwner()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, ImgSize.y);
}

void CStormBGScript::tick()
{
}

void CStormBGScript::SaveToFile(FILE* _File)
{
}

void CStormBGScript::LoadFromFile(FILE* _File)
{
}


