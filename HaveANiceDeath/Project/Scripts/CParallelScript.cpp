#include "pch.h"
#include "CParallelScript.h"

#include "CCamCtrlScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>


CParallelScript::CParallelScript()
	: CScript(PARALLELSCRIPT)
	, m_vAirColor(Vec4(174, 184, 169, 255))
	, m_fMaxDepth(1200.f)
	, m_MainCamCtrl(nullptr)
	, m_bAirPerspective(true)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Max Depth", &m_fMaxDepth);
	AddScriptParam(SCRIPT_PARAM::VEC4, "Air Color", &m_vAirColor);
	AddScriptParam(SCRIPT_PARAM::BOOL, "Use AirPerspective", &m_bAirPerspective);
}

CParallelScript::CParallelScript(const CParallelScript& _Origin)
	: CScript(PARALLELSCRIPT)
	, m_vAirColor(_Origin.m_vAirColor)
	, m_fMaxDepth(_Origin.m_fMaxDepth)
	, m_MainCamCtrl(nullptr)
	, m_bAirPerspective(_Origin.m_bAirPerspective)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Max Depth", &m_fMaxDepth);
	AddScriptParam(SCRIPT_PARAM::VEC4, "Air Color", &m_vAirColor);
	AddScriptParam(SCRIPT_PARAM::BOOL, "Use AirPerspective", &m_bAirPerspective);
}


CParallelScript::~CParallelScript()
{
}

void CParallelScript::begin()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* CurLayer = pLevel->GetLayer(L"Default");

	if (CurLayer)
	{
		m_MainCamCtrl = CurLayer->GetObjectByName(L"MainCamera")->GetScript<CCamCtrlScript>();
	}

	Ptr<CMaterial> pMat = GetOwner()->MeshRender()->GetDynamicMaterial();
	pMat->SetScalarParam(SCALAR_PARAM::INT_0, m_bAirPerspective);
	pMat->SetScalarParam(SCALAR_PARAM::VEC4_0, m_vAirColor / 255.f);
	pMat->SetScalarParam(SCALAR_PARAM::FLOAT_0, Transform()->GetRelativePos().z);
}

void CParallelScript::tick()
{
	if (!m_MainCamCtrl)
		return;

	Vec3 vCamMove = m_MainCamCtrl->GetMove();
	Vec3 vUpdatePos = GetOwner()->Transform()->GetRelativePos();
	if (vCamMove == Vec3() || vUpdatePos.z == 0.f)
		return;

	// case: z > 0
	// - ���� Ŀ������: ī�޶��� ����������� �о���
	// - (�ָ� ��������, ī�޶� �������� �̹����� ������ ��ó�� ����)
	if (vUpdatePos.z > 0)
		vUpdatePos.x += vCamMove.x * (vUpdatePos.z / m_fMaxDepth);

	// case: z < 0
	// - ���� �������� : ī�޶� ��������� �ݴ�� �о���
	// - (������ ��������, ī�޶� ���� �������� �̹����� ��ȭ���� ŭ)
	else
		vUpdatePos.x += vCamMove.x / m_fMaxDepth * (1.f / vUpdatePos.z);

	GetOwner()->Transform()->SetRelativePos(vUpdatePos);
	GetOwner()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, vUpdatePos.z); // @TODO : release, Ȥ�� ���� �Ϸ�� �����
}

void CParallelScript::SaveToFile(FILE* _File)
{
	fwrite(&m_vAirColor, 1, sizeof(Vec4), _File);
}

void CParallelScript::LoadFromFile(FILE* _File)
{
	fread(&m_vAirColor, 1, sizeof(Vec4), _File);
}