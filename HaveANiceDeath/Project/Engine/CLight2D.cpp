#include "pch.h"
#include "CLight2D.h"

#include "CRenderMgr.h"
#include "CTransform.h"

CLight2D::CLight2D()
	: CComponent(COMPONENT_TYPE::LIGHT2D)
{
}

CLight2D::~CLight2D()
{
}

void CLight2D::SaveToFile(FILE* _File)
{
	fwrite(&m_Info, sizeof(tLightInfo), 1, _File);
}

void CLight2D::LoadFromFile(FILE* _File)
{
	fread(&m_Info, sizeof(tLightInfo), 1, _File);
}

void CLight2D::finaltick()
{
	// ���� ��ġ���� LightInfo �ɹ��� �����س��´�.
	Vec3 vWorldPos = Transform()->GetWorldPos();
	m_Info.vWorldPos = vWorldPos;

	// ���� ���
	CRenderMgr::GetInst()->RegisterLight2D(this);
}